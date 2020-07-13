// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzStatus"
#pragma link "RzPanel"
#pragma link "RzStatus"
#pragma link "RzButton"
#pragma link "RzSplit"
#pragma link "RzGroupBar"
#pragma link "RzLstBox"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzTabs"
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
TForm1 *Form1;

const GLuint grid_list = 0, axis_list = 1, bezier_list = 2;
short sweep_az;

GLdouble modelMatrix[16];
GLdouble projMatrix[16];
GLint viewport[4];
GLdouble objx, objy, objz = 0;
TPoint *targetArr = new TPoint[100];
float D, Az = 0;
GLfloat BezierColor[4] = {0, 1, 0, 1};
GLfloat PointColor[4] = {1, 0, 0, 1};
GLfloat TargetColor[4] = {1, 0, 1, 1};
GLfloat ColorArr[4] = {1, 1, 0, 1};
int IndexPoint = 0;
GLfloat OGLpoints[4][3];
GLfloat TrCoords[4][3];
bool bezier_ready = false;
bool point_ready = false;
int Dmax = 450000;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	targetArr[0].X = 0;
	targetArr[0].Y = 0;
	targetArr[1].X = 10;
	targetArr[1].Y = 0;
	targetArr[2].X = 100;
	targetArr[2].Y = 100;
	targetArr[3].X = 300;
	targetArr[3].Y = 200;
}

// ---------------------------------------------------------------------------
void TForm1::SetDCPixelFormat(HDC hdc) {

	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat = 0;

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED | PFD_SUPPORT_GDI;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, nPixelFormat, &pfd);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	hwnd1 = RzPanel1->Handle;
	dc1 = GetDC(hwnd1);
	SetDCPixelFormat(dc1);
	hrc1 = wglCreateContext(dc1);
	wglMakeCurrent(dc1, hrc1);

	glEnable(GL_DEPTH_TEST); // ��������� ���� �������
	glEnable(GL_LIGHTING); // ��������� ������ � �������������
	glEnable(GL_LIGHT0); // �������� �������� ����� 0

	Zoom = 1;
	DecimalSeparator = 0x2e;

	Radar.WaveLength = 100;
	Radar.I_F = 24000000;
	Radar.ADCClock = 32000000;
	Radar.PulseLength = 1500;
	Radar.wDN = 2;
	Radar.ADCWidth = 8;
	Radar.PackRec[0].Period = 890987;
	Radar.PackRec[0].CntIZ = 16;
	Radar.PackRec[0].CntDskr = 509;
	Radar.PackRec[0].EnumKpp = 3;
	Radar.PackRec[1].Period = 954391;
	Radar.PackRec[1].CntIZ = 15;
	Radar.PackRec[1].CntDskr = 547;
	Radar.PackRec[1].EnumKpp = 2;
	Radar.PackRec[2].Period = 1027805;
	Radar.PackRec[2].CntIZ = 14;
	Radar.PackRec[2].CntDskr = 591;
	Radar.PackRec[2].EnumKpp = 1;
	Radar.PackRec[3].Period = 1214679;
	Radar.PackRec[3].CntIZ = 13;
	Radar.PackRec[3].CntDskr = 703;
	Radar.PackRec[3].EnumKpp = 0;
	currentTarget.Name = "Mig-29";
	currentTarget.S = 10;
	currentTarget.Velocity = 0;
	currentTarget.Distance = 50000;
	currentTarget.Beta = 90;
	currentTarget.Length = 10;
	currentTarget.Height = 1000;

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc1);
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::RzPanel1Paint(TObject *Sender) {

	int i = 0, j = 0;
	float x = 0.0, y = 0.0, a = 0.0;
	unsigned int Cl;
	if (ColorDialog1->Color == 0) // Cl = ColorToRGB(clGreen);
			Cl = RGB(55, 53, 74);
	else
		Cl = ColorToRGB(ColorDialog1->Color);
	glClearColor(double(LOBYTE(Cl)) / 255, double(HIBYTE(Cl)) / 255, double(LOBYTE(HIWORD(Cl))) / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PaintGrid();
	DrawAxis();
	DrawSweep();

	glEnable(GL_BLEND);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, TargetColor);
	// PaintTarget();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PointColor);
	if (IndexPoint != 5)
		PaintPoint();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BezierColor);

	if (bezier_ready) {
		PaintPoint();
		PaintBezier();
	}

	SwapBuffers(dc1);
}

// ---------------------------------------------------------------------------
void TForm1::PaintBezier() {
	if (edt_beta0 != "" && edt_beta1 != "" && edt_beta2 != "" && edt_beta3 != "" && edt_D0 != "" && edt_D1 != "" && edt_D2 != "" &&
		edt_D3 != "") {

		OGLpoints[0][0] = (StrToFloat(edt_D0->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta0->Text) / 180.0);
		OGLpoints[0][1] = (StrToFloat(edt_D0->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta0->Text) / 180.0);

		OGLpoints[1][0] = (StrToFloat(edt_D1->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta1->Text) / 180.0);
		OGLpoints[1][1] = (StrToFloat(edt_D1->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta1->Text) / 180.0);

		OGLpoints[2][0] = (StrToFloat(edt_D2->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta2->Text) / 180.0);
		OGLpoints[2][1] = (StrToFloat(edt_D2->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta2->Text) / 180.0);

		OGLpoints[3][0] = (StrToFloat(edt_D3->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta3->Text) / 180.0);
		OGLpoints[3][1] = (StrToFloat(edt_D3->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta3->Text) / 180.0);

	}
	glShadeModel(GL_FLAT);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &OGLpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_STRIP);
	for (GLint i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat) i / 30.0);
	glEnd();

}

// ---------------------------------------------------------------------------
void TForm1::PaintGrid() {

	glNewList(grid_list, GL_COMPILE_AND_EXECUTE);
	const int nSec = 40;
	int i = 0, j = 0;
	float a = 0.0, x = 0.0, y = 0.0, k = 0.0, Cl = 0.0, ClMax = 0.0, ClMin = 0.0;
	int n = 0;
	n = 100;
	glLineWidth(1);
	MCGrid[0] = 1;
	MCGrid[1] = 1;
	MCGrid[2] = 1;
	MCGrid[3] = 1;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MCGrid);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	k = 2;

	Cl = 0.15 * k; // * FGridOpacity;
	ClMax = 0.25 * k; // * FGridOpacity;
	ClMin = 0.03 * k; // * FGridOpacity;
	for (int j = 0; j <= nSec; j++) {
		if (Frac(j / 5.0) == 0)
			MCGrid[3] = Cl;
		else
			MCGrid[3] = ClMin;
		if (Frac(double(j) / 10) == 0)
			MCGrid[3] = ClMax;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MCGrid);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < n; i++) {
			a = i * 2 * Pi / n;
			x = j * sin(a) / nSec;
			y = j * cos(a) / nSec;
			glVertex3f(x, y, 0.01);
		}
		a = 0 * 2 * Pi / n;
		x = j * sin(a) / nSec;
		y = j * cos(a) / nSec;
		glVertex3f(x, y, 0.01);
		glEnd();
	}
	j = 60;
	for (int i = 0; i <= j; i++) {
		if (Frac(i / 5.0) == 0)
			MCGrid[3] = Cl;
		else
			MCGrid[3] = ClMin;
		if (Frac(double(i) / 15) == 0)
			MCGrid[3] = ClMax;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MCGrid);
		glBegin(GL_LINE_STRIP);
		a = 2 * Pi * i / j;
		x = sin(a);
		y = cos(a);
		glVertex3f(x * 6. / 450, y * 6. / 450, 0.02);
		glVertex3f(x, y, 0.02);

		glEnd();

	}
	glEndList();

}

// ---------------------------------------------------------------------------
void TForm1::PaintTarget() {
	glPointSize(7);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	tX = tY = 0.5;
	glVertex2f(tX, tY);
	glEnd();
}

void TForm1::InitViewProection(float x, float y, float dXX, float dYY) {
	float tmpX = 0.0, tmpY = 0.0;
	Diagonal = RzPanel1->Width / RzPanel1->Height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * Diagonal / Zoom, 1.0 * Diagonal / Zoom, -1.0 / Zoom, 1.0 / Zoom, -1.0, 1.0);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled) {
	float tmpX, tmpY, X, Y;

	X = (MousePos.X - RzPanel1->Width / 2) / (RzPanel1->Width / 2) * Diagonal;
	Y = -(MousePos.Y - RzPanel1->Height / 2) / (RzPanel1->Height / 2);
	tmpX = X / Zoom - DX / Zoom;
	tmpY = Y / Zoom - DY / Zoom;

	if (WheelDelta < 0)
		Zoom = Zoom * 1.05;
	else
		Zoom = Zoom / 1.05;

	InitViewProection(X, Y, tmpX, tmpY);
}
// ---------------------------------------------------------------------------

void TForm1::DrawAxis() {
	glNewList(axis_list, GL_COMPILE_AND_EXECUTE);
	// --------Axis X--------------------
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	// --------Axis Y--------------------
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	// --------Axis Z--------------------
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 1);
	glEnd();

	glEndList();
}

void __fastcall TForm1::RzPanel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y) {

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	gluUnProject(X, (float)viewport[3] - Y, 0, modelMatrix, projMatrix, viewport, &objx, &objy, &objz);

	D = sqrt(objy * objy + objx * objx) * 450;
	Az = ArcTan2(objy, objx);

	if (Az > 0)
		Az = 180 / Pi * Az;
	else
		Az = 360 + (180 / Pi * Az);

	RzMapInfo->Caption = Format("%3.3f ��,  %3.0f", ARRAYOFCONST((D, Az))) + " \xB0";
	Caption = Format("OpenGL X_coord = %3.3f,  Y_coord = %3.3f,  Z_coord = %3.3f", ARRAYOFCONST((objx, objy, objz)));

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnUtilitiesClick(TObject *Sender) {
	ColorDialog1->Execute();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RzPanel1Click(TObject *Sender) {

	point_ready = true;

	if (IndexPoint > 4) {
		IndexPoint = 0;
	}
	AddPoint();
}
// ---------------------------------------------------------------------------

void TForm1::AddPoint() {

	OGLpoints[IndexPoint][0] = objx;
	OGLpoints[IndexPoint][1] = objy;
	TrCoords[IndexPoint][0] = Az;
	TrCoords[IndexPoint][1] = D;
	if (IndexPoint == 0) {
		edt_beta0->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[0][0])));
		edt_D0->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[0][1])));

	}
	else if (IndexPoint == 1) {
		edt_beta1->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[1][0])));
		edt_D1->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[1][1])));
	}
	else if (IndexPoint == 2) {
		edt_beta2->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[2][0])));
		edt_D2->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[2][1])));
	}
	else if (IndexPoint == 3) {
		edt_beta3->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[3][0])));
		edt_D3->Text = Format("%2.2f", ARRAYOFCONST((TrCoords[3][1])));
	}
	else {

		// IndexPoint = 0;
		BtnRefreshClick(this);

	}

	IndexPoint++;

}

// ---------------------------------------------------------------------------
void TForm1::PaintPoint() {
	if (point_ready) {
		glPointSize(7);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);
		for (int i = 0; i < IndexPoint; i++) {
			glVertex2f(OGLpoints[i][0], OGLpoints[i][1]);
		}
		glEnd();
	}
	else {
		bezier_ready = false;
	}
}

// ---------------------------------------------------------------------------
void TForm1::DrawSweep() {

	glLineWidth(1.0);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(sin(Pi*sweep_az / 180), sin(Pi*(90 - sweep_az) / 180));
	glEnd();

	sweep_az++;
	if (sweep_az > 360) {
		sweep_az = 0;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {

	InvalidateRect(hwnd1, 0, false);

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Textout(char* str, GLfloat x, GLfloat y, GLfloat *color) {

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glRasterPos2f(x, y);
	int i = 0;
	while (str[i] != '\0') {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
		i++;
	}
}

void __fastcall TForm1::BtnExecuteClick(TObject *Sender) {
	if (edt_beta0->Text != "" && edt_beta1->Text != "" && edt_beta2->Text != "" && edt_beta3->Text != "" && edt_D0->Text != "" &&
		edt_D1->Text != "" && edt_D2->Text != "" && edt_D3->Text != "") {

		bezier_ready = true;
		InvalidateRect(hwnd1, NULL, false);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::lbl_beta0Change(TObject *Sender) {
	// float Az_text, D_text;
	// Az_text = StrToFloat(edt_beta0->Text);
	// if ((Az_text != 0.0 ) && (Az_text > 360.0)) {
	//
	// ShowMessage("������� �������� ����� 0 � 360 ��������");
	////		lbl_beta0->Text = "";
	// }
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::lbl_beta0KeyPress(TObject *Sender, wchar_t &Key) {
	// if (!Key in [#8, '0'..'9', DecimalSeparator]) then
	// begin
	// ShowMessage('Please enter a number.  Wrong input: ' + Key);
	// Key := #0;
	// end//End first if.
	// else
	// if (Key = DecimalSeparator) and (Pos(Key, Edit1.Text) > 0) then
	// begin
	// ShowMessage('Please enter a number.  Wrong input: ' + Key);
	// Key := #0;
	// end;//End second if.
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::BtnRefreshClick(TObject *Sender) {
	Memo1->Clear();
	bezier_ready = false;
	point_ready = false;
	IndexPoint = 4;
	edt_beta0->Clear();
	edt_D0->Clear();
	edt_beta1->Clear();
	edt_D1->Clear();
	edt_beta2->Clear();
	edt_D2->Clear();
	edt_beta3->Clear();
	edt_D3->Clear();
	InvalidateRect(hwnd1, NULL, true);
}

// ---------------------------------------------------------------------------

int TForm1::GetCountPulsesOfPacket(void) {
	int PulsesOfPacket = 0;
	for (int i = 0; i < 4; i++)
		PulsesOfPacket = PulsesOfPacket + Radar.PackRec[i].CntIZ;

	return PulsesOfPacket;
}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodeRoot() {
	TTreeNode * result;
	result = TV->Items->Add(NULL, " ����� ");
	result->SelectedIndex = 0;
	return result;
}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodePackage(TTreeNode * Parent, int i) {
	TTreeNode * result;
	result = TV->Items->AddChild(Parent, " ����� �" + IntToStr(i + 1));
	result->SelectedIndex = 0;
	return result;
}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodePulses(TTreeNode * Parent, int i) {
	TTreeNode * result;
	result = TV->Items->AddChild(Parent, " ������ �" + IntToStr(i + 1));
	result->SelectedIndex = 0;
	return result;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::TVClick(TObject *Sender) {
	// TtmpItemRec *tmpR;
	// for (int i = 0; i < TV->Items->Count; i++) {
	// Memo2->Lines->Clear();
	// if (TV->Items->Item[i]->Level == 2) {
	// Memo2->Lines->BeginUpdate();

	// Memo2->Lines->Add("	TV->SelectionCount =  " + IntToStr((int)TV->SelectionCount));
	// TV->
	//
	// Memo2->Lines->Add("tmpItem->ZapID =  " + IntToStr(tmpItem->ZapID));
	// Memo2->Lines->Add("tmpItem->PackID =  " + IntToStr(tmpItem->PackID));
	// Memo2->Lines->Add("tmpItem->PckgID =  " + IntToStr(tmpItem->PckgID));
	// Memo2->Lines->Add("tmpItem->Time =  " + FloatToStr(tmpItem->Time));
	// Memo2->Lines->Add("tmpItem->Beta =  " + FloatToStr(tmpItem->Beta));
	// Memo2->Lines->Add("tmpItem->TimeBack =  " + FloatToStr(tmpItem->TimeBack));
	// Memo2->Lines->EndUpdate();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnOKClick(TObject *Sender) {
	int i, j, ii;
	TTreeNode * Root, *NodePackage, *NodePulses, *PulsesData;
	TV->Items->Clear();

	int PulsesOfPacket = GetCountPulsesOfPacket();
	TimeArr = new int[PulsesOfPacket];
	BetaArr = new float[PulsesOfPacket];
	int step = 0, currentPulse = 0;

	Root = AddNodeRoot();
	// ������ �� ������
	Memo1->Clear();
	Memo1->Lines->BeginUpdate();
	for (j = 0; j < 4; j++) {

		NodePackage = AddNodePackage(Root, j);
		Memo1->Lines->Add("����� #" + IntToStr(j + 1));
		Memo1->Lines->Add("");
		// ������ �� ��������
		for (ii = 0; ii < Radar.PackRec[j].CntIZ; ii++) {
			NodePulses = AddNodePulses(NodePackage, ii);
			TimeArr[currentPulse] = step;
			BetaArr[currentPulse] = TimeArr[currentPulse] * 1.0e-9 * 360.0 / 10.0;
			// PulsesData = AddChild( NodePulses, ii);
			tmpItem = new TtmpItemRec;
			tmpItem->ZapID = ii;
			tmpItem->PackID = 1;
			tmpItem->PckgID = j;

			tmpItem->Time = TimeArr[currentPulse];
			Chart1->Series[0]->AddY(TimeArr[currentPulse]);
			Chart1->Series[0]->AddX(currentPulse);
			tmpItem->Beta = BetaArr[currentPulse] + currentTarget.Beta;
			tmpItem->TimeBack = tmpItem->Time + 2 * currentTarget.Distance / 3.0e8;
			NodePulses->Data = tmpItem;

			// Memo2->Lines->Add("PckgID" + IntToStr(((TtmpItemRec*)NodePulses->Data)->PckgID));
			Memo1->Lines->Add(" ������[" + IntToStr(ii + 1) + "] = " + IntToStr(step) + "  ��");
			step = step + Radar.PackRec[j].Period;
			currentPulse++;

		}

		Memo1->Lines->Add("");
	}
	Memo1->Lines->EndUpdate();

	TimeOfPacket = TimeArr[PulsesOfPacket - 1];
	BetaOfPacket = TimeOfPacket * 1.0e-9 * 360.0 / 10.0;

	Memo1->Lines->Add(" ���-�� �������� ��� ������ 6 ��. = " + IntToStr(GetCountPulsesOfPacket()));
	Memo1->Lines->Add(" ����� ������ = " + IntToStr(TimeOfPacket) + " ns");
	Memo1->Lines->Add(" ������� ������� �� ����� ������ = " + FloatToStr(BetaOfPacket) + " ��������");
	Memo1->Lines->Delete(Memo1->Lines->Count);
	// TV->FullExpand();
	delete[]TimeArr;
	delete[]BetaArr;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnAttachClick(TObject *Sender) {

	if (edt_beta0 != "" && edt_D0 != "" && edt_epr != "" && edt_speed != "")
		Memo1->Lines->Add((AddTarget())->Time);
}

// ---------------------------------------------------------------------------
Target* TForm1::AddTarget() {

	Target *Tr = (Target*) malloc(sizeof(Target));

	Tr->Beta = StrToFloat(edt_beta0->Text); // (int) (frac(GetTickCount() * 1.0 / 10000) * 360);
	Tr->Distance = 50000;
	Tr->Height = 1000;
	Tr->Length = 10;
	Tr->S = StrToFloat(edt_epr->Text);
	Tr->Velocity = StrToFloat(edt_speed->Text); // 100;
	Tr->Ampl = -21;
	Tr->Time = GetTickCount();
	// Tr->Y = Tr->D * 1.0 / DMax * cos(Tr->b * 1.0 / 180 * pi);
	// Tr->X = Tr->D * 1.0 / DMax * sin(Tr->b * 1.0 / 180 * pi);

	Tr->X = (StrToFloat(edt_D0->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta0->Text) / 180.0);
	Tr->Y = (StrToFloat(edt_D0->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta0->Text) / 180.0);

	return Tr;

}

void __fastcall TForm1::RzPageControl1PageChange(TObject *Sender) {
	if (RzPageControl1->ActivePage == TabSheet2)
		Chart1->Visible = True;
	else
		Chart1->Visible = False;

}
// ---------------------------------------------------------------------------
