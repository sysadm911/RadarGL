// ---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <stdio.h>
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
#pragma link "RzRadGrp"
#pragma link "RzRadGrp"
#pragma link "RzCmboBx"
#pragma link "cspin"
#pragma link "RzSpnEdt"
#pragma link "Spin"
#pragma resource "*.dfm"
TForm1 *Form1;

// const GLuint grid_list = 0, axis_list = 1, bezier_list = 2;
short sweep_az;

GLdouble modelMatrix[16];
GLdouble projMatrix[16];
GLint viewport[4];
GLdouble objx, objy, objz = 0;
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
bool target_ready = false;
int Dmax = 450000;
int CDOSWidth = 16384;
float virezDD = 25;
// deltaDD = 250.0;
float deltaDD = 3E8 * 32 / 19178720 / 2;
float virezKm = virezDD * deltaDD;
bool IsPulse = false;
bool isDrawRoute = false;
bool restart = false;
float SArrLFMup[8192] = {0};
float SArrLFMdown[8192] = {0};
float ArrRe[32768] = {0};
DynamicArray<int>ArrBig;
DynamicArray<float>Pulses;
bool TVready = false;
// float lineArrRe[32768] = {0};
GLuint grid_list, grid_list2;
TList *ListPulses = new TList;

int startX, startY = 0;

double deltaTime = 0, deltaBeta = 0, deltaDistance = 0, D_start = 0, D_startX = 0, D_startY = 0, D_end = 0, D_endX = 0, D_endY = 0,
	Decart_Route_Start = 0, Decart_Route_End = 0, Decart_Route = 0;

float zpos, xpos, ypos = 0;

#define frac(X) (X)-int(X)

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	ArrBig.Length = 10;
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
	glEnable(GL_DEPTH_TEST); // разрешаем тест глубины
	glEnable(GL_LIGHTING); // разрешаем работу с освещенностью
	glEnable(GL_LIGHT0); // включаем источник света 0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Zoom = 1.0;
	DecimalSeparator = 0x2e;
	Radar.WaveLength = 100;
	Radar.I_F = 4794680;
	Radar.ADCClock = 19178720;
	Radar.PulseLength = 1668;
	Radar.wDN = 2;
	Radar.ADCWidth = 8;
	Radar.Noise = -60;
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
	currentTarget.Velocity = StrToFloat(edt_speed->Text);
	currentTarget.Distance = 50000;
	currentTarget.Beta = 90;
	currentTarget.Length = 10;
	currentTarget.Height = 1000;
	ResultShiftScene.X = 0;
	ResultShiftScene.Y = 0;
	ListTr = new TList;
	RzPageControl1->ActivePage = TabSheet1;

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc1);
}

// ---------------------------------------------------------------------------
void TForm1::DrawSweep() {

	glLineWidth(Zoom*1.0);
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
void TForm1::PaintBezier() {
	if (edt_beta0 != "" && edt_beta1 != "" && edt_beta2 != "" && edt_beta3 != "" && edt_D0 != "" && edt_D1 != "" && edt_D2 != "" &&
		edt_D3 != "") {

		OGLpoints[0][0] = (StrToFloat(edt_D0->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta0->Text) / 180.0);
		OGLpoints[0][1] = (StrToFloat(edt_D0->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta0->Text) / 180.0);

		OGLpoints[1][0] = (StrToFloat(edt_D1->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta1->Text) / 180.0);
		OGLpoints[1][1] = (StrToFloat(edt_D1->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta1->Text) / 180.0);

		OGLpoints[2][0] = (StrToFloat(edt_D2->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta2->Text) / 180.0);
		OGLpoints[2][1] = (StrToFloat(edt_D2->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta2->Text) / 180.0);

		OGLpoints[3][0] = (StrToFloat(edt_D3->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta3->Text) / 180.0);
		OGLpoints[3][1] = (StrToFloat(edt_D3->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta3->Text) / 180.0);

	}
	glShadeModel(GL_FLAT);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &OGLpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(Zoom*1);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_STRIP);
	for (GLint i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat) i / 30.0);
	glEnd();

}

// ---------------------------------------------------------------------------
void TForm1::PaintGrid() {

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
	// glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MCGrid);

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
		a = 1 * 2 * Pi / n;
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
}

// ---------------------------------------------------------------------------
void TForm1::InitViewProection() {

	double tmpX = 0, tmpY = 0;
	Diagonal = (float)RzPanel1->Width / RzPanel1->Height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * Diagonal / Zoom, 1.0 * Diagonal / Zoom, -1.0 / Zoom, 1.0 / Zoom, -1.0, 1.0);

	if (MousePosMove.State == siManualDrag) {
		tmpX = MousePosMove.X - MousePosDown.X;
		tmpY = MousePosMove.Y - MousePosDown.Y; ;
		ResultShiftScene.X = tmpX;
		ResultShiftScene.Y = tmpY;

	}
	if (MousePosMove.State == siNone) {
		tmpX = ResultShiftScene.X;
		tmpY = ResultShiftScene.Y;

	}
	if (!restart)
		glTranslatef(tmpX, tmpY, 0);
	// glViewport(0, 0, RzPanel1->Width, RzPanel1->Height);
	glMatrixMode(GL_MODELVIEW);

}

void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled) {
	float tmpX, tmpY, X, Y;

	X = (MousePos.X - RzPanel1->Width / 2.0) / (RzPanel1->Width / 2.0) * Diagonal;
	Y = -(MousePos.Y - RzPanel1->Height / 2.0) / (RzPanel1->Height / 2.0);
	tmpX = X / Zoom - DX / Zoom;
	tmpY = Y / Zoom - DY / Zoom;

	if (WheelDelta < 0)
		Zoom = Zoom * 1.05;
	else
		Zoom = Zoom / 1.05;

	Diagonal = (float)RzPanel1->Width / RzPanel1->Height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * Diagonal / Zoom, 1.0 * Diagonal / Zoom, -1.0 / Zoom, 1.0 / Zoom, -1.0, 1.0);
	glTranslatef(xpos, ypos, zpos);
	glMatrixMode(GL_PROJECTION);
	InvalidateRect(hwnd1, 0, false);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnBackgroundClick(TObject *Sender) {
	ColorDialog1->Execute();
	InvalidateRect(hwnd1, 0, true);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RzPanel1Click(TObject *Sender) {

	// if (MousePosMove.State != siManualDrag) {
	point_ready = true;

	if (IndexPoint > 4) {
		IndexPoint = 0;
	}
	if (D < 451)
		AddPoint();
	InvalidateRect(hwnd1, 0, false);

	// }

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
	IndexPoint++;
}

// ---------------------------------------------------------------------------
void TForm1::PaintPoint() {
	if (point_ready) {

		glPointSize(Zoom*2);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);
		for (int i = 0; i < IndexPoint; i++) {
			glVertex2f(OGLpoints[i][0], OGLpoints[i][1]);
		}
		glEnd();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnRouteClick(TObject *Sender) {
	if (edt_beta0->Text != "" && edt_beta1->Text != "" && edt_beta2->Text != "" && edt_beta3->Text != "" && edt_D0->Text != "" &&
		edt_D1->Text != "" && edt_D2->Text != "" && edt_D3->Text != "") {

		bezier_ready = true;
		InvalidateRect(hwnd1, NULL, false);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnRestartClick(TObject *Sender) {
	Memo1->Clear();
	bezier_ready = false;
	point_ready = false;
	IndexPoint = 5;
	edt_beta0->Clear();
	edt_D0->Clear();
	edt_beta1->Clear();
	edt_D1->Clear();
	edt_beta2->Clear();
	edt_D2->Clear();
	edt_beta3->Clear();
	edt_D3->Clear();
	Zoom = 1;
	MousePosMove.X = MousePosMove.Y = 0;
	MousePosDown.X = MousePosDown.Y = 0;
	MousePosUp.X = MousePosUp.Y = 0;
	restart = true;
	glMatrixMode(GL_MODELVIEW);
	TVready = false;
	glLoadIdentity();
	glOrtho(-1.0 * Diagonal, 1.0 * Diagonal, -1.0, 1.0, -1.0, 1.0);
	InvalidateRect(hwnd1, 0, true);

}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodeRot(int i) {
	TTreeNode * result;
	result = TV->Items->Add(NULL, " Оборот №" + IntToStr(i + 1));
	result->SelectedIndex = 0;
	return result;
}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodePacket(TTreeNode * Parent, int i) {
	TTreeNode * result;
	result = TV->Items->AddChild(Parent, " Пакет №" + IntToStr(i + 1));
	result->SelectedIndex = 0;
	return result;
}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodePackage(TTreeNode * Parent, int i) {
	TTreeNode * result;
	result = TV->Items->AddChild(Parent, " Пачка №" + IntToStr(i + 1));
	result->SelectedIndex = 0;
	return result;
}

// ---------------------------------------------------------------------------
TTreeNode * TForm1::AddNodePulses(TTreeNode * Parent, int i) {
	TTreeNode * result;
	result = TV->Items->AddChild(Parent, " Запуск №" + IntToStr(i + 1));
	result->SelectedIndex = 0;
	return result;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::BtnAddTargetClick(TObject *Sender) {

	if (edt_beta0 != "" && edt_D0 != "" && edt_epr != "" && edt_speed != "")
		Memo1->Lines->Add((AddTarget())->Time);
}

// ---------------------------------------------------------------------------
Target* TForm1::AddTarget() {
	Target *Tr = (Target*) malloc(sizeof(Target));
	FormatSettings.DecimalSeparator = 0x2e;
	Tr->Beta = StrToFloat(Trim(edt_beta0->Text), FormatSettings);
	Tr->Distance = 50000;
	Tr->Height = 1000;
	Tr->Length = 10;
	Tr->S = StrToFloat(edt_epr->Text);
	Tr->Velocity = StrToFloat(edt_speed->Text) * 1000.0 / 3600.0; // 100;
	Tr->Ampl = -21;
	Tr->Time = GetTickCount() * 1e-3;

	Tr->X = (StrToFloat(edt_D0->Text) / 450.0) * cos(Pi * StrToFloat(edt_beta0->Text) / 180.0);
	Tr->Y = (StrToFloat(edt_D0->Text) / 450.0) * sin(Pi * StrToFloat(edt_beta0->Text) / 180.0);

	return Tr;
}

int TForm1::GetCountSamplesOfPulse() {

	return ceil((32.0 / Radar.ADCClock) * Radar.ADCClock);

}

int TForm1::GetCountSamplesOfPulseLFM() {

	return GetCountSamplesOfPulse() * 52; // Radar.LFMlength;

}

void __fastcall TForm1::edt_beta1Enter(TObject *Sender) {
	PaintBezier();
}

// ---------------------------------------------------------------------------
TPoint TForm1::FQ(double Arr[], float Scale) {
	TPoint result;
	double a = 0.0, AA = 0.0, b = 0.0, BB = 0.0, C = 0.0, CC = 0.0, D = 0.0, DD = 0.0, Re = 0.0, Im = 0.0, F = 0.0;
	int i = 0, Cnt = 0;
	Cnt = GetCountSamplesOfPulse();
	for (i = 0; i < Cnt / 8; i++) {
		a = a + (Arr[i * 8]);
		b = b + (Arr[i * 8 + 1]);
		C = C + (Arr[i * 8 + 2]);
		D = D + (Arr[i * 8 + 3]);
		AA = AA + (Arr[i * 8 + 4]);
		BB = BB + (Arr[i * 8 + 5]);
		CC = CC + (Arr[i * 8 + 6]);
		DD = DD + (Arr[i * 8 + 7]);
	}
	F = a - C + AA - CC;
	Re = F - b + D - BB + DD;
	Im = F + b - D + BB - DD;
	Re = Re * Scale;
	Im = Im * Scale;
	result = Point(floor(Re), floor(Im));
	return result;
}

void __fastcall TForm1::TVClick(TObject *Sender) {
	TtmpItemRec *tmpR;

	if (TV->Selected->Level == 2) {
		Memo1->Lines->Clear();
		for (int i = 0; i < TV->Selected->Count; i++) {
			tmpR = (TtmpItemRec*)TV->Selected->Item[i]->Data;
			Memo1->Lines->BeginUpdate();
			Memo1->Lines->Add("ZapID =  " + IntToStr(tmpR->ZapID));
			Memo1->Lines->Add("PckgID =  " + IntToStr(tmpR->PckgID));
			Memo1->Lines->Add("PackID =  " + IntToStr(tmpR->PackID));
			Memo1->Lines->Add("Beta =  " + FloatToStr(tmpR->Beta));
			Memo1->Lines->Add("Time =  " + FloatToStr(tmpR->Time));
			Memo1->Lines->Add("TimeBack =  " + FloatToStr(tmpR->TimeBack));
			Memo1->Lines->Add("deltaDistance =  " + FloatToStr(tmpR->deltaDistance));
			Memo1->Lines->Add("deltaTime =  " + FloatToStr(tmpR->deltaTime));
			Memo1->Lines->Add("tmpItem->X =  " + FloatToStr(tmpR->X));
			Memo1->Lines->Add("tmpItem->Y =  " + FloatToStr(tmpR->Y));
			Memo1->Lines->Add(" ");
			Memo1->Lines->EndUpdate();

		}

	}
	else if (TV->Selected->Level == 3) {
		Memo1->Lines->Clear();

		tmpR = (TtmpItemRec*)TV->Selected->Data;
		Memo1->Lines->BeginUpdate();
		Memo1->Lines->Add("ZapID =  " + IntToStr(tmpR->ZapID));
		Memo1->Lines->Add("PckgID =  " + IntToStr(tmpR->PckgID));
		Memo1->Lines->Add("PackID =  " + IntToStr(tmpR->PackID));
		Memo1->Lines->Add("Beta =  " + FloatToStr(tmpR->Beta));
		Memo1->Lines->Add("Time =  " + FloatToStr(tmpR->Time));
		Memo1->Lines->Add("TimeBack =  " + FloatToStr(tmpR->TimeBack));
		Memo1->Lines->Add("deltaDistance =  " + FloatToStr(tmpR->deltaDistance));
		Memo1->Lines->Add("deltaTime =  " + FloatToStr(tmpR->deltaTime));
		Memo1->Lines->Add("tmpItem->X =  " + FloatToStr(tmpR->X));
		Memo1->Lines->Add("tmpItem->Y =  " + FloatToStr(tmpR->Y));
		Memo1->Lines->EndUpdate();
	}

	InvalidateRect(hwnd1, 0, false);
}
// ---------------------------------------------------------------------------

int TForm1::DistanceToDiskret(float Distance) {
	int result = 0;
	double test = 0.0;
	test = (Distance / (3E8 / 2 * (32.0 / Radar.ADCClock)));
	if (test >= 0)
		result = floor(test);
	else
		result = -1;
	return result;
}

float TForm1::DiskretToDistance(int Diskret) {
	float result = 0.0;
	result = 2 * (32.0 / Radar.ADCClock) * 3E8;
	return result;
}

int TForm1::GetShiftADCClock(float dT) {
	float test1, test2, test;
	test1 = 32 / Radar.ADCClock;
	test = dT / test1;
	return int(frac(test) * GetCountSamplesOfPulse());
}

void TForm1::FillListPulses(int &Index, TList * ListPulses) {
	ListPulses->Clear();
	Index = Index + 1;
	while (Index < TV->Items->Count) {
		if (TV->Items->Item[Index]->Level == 2) {
			if (TV->Items->Item[Index]->Data != NULL) {
				ListPulses->Add(TV->Items->Item[Index]->Data);
			}
		}
		if (TV->Items->Item[Index]->Level == 1) {
			return;
		}
		Index++;
	}
}

void TForm1::UpdateListPulses() {
	int i = 0, j = 0, ii = 0, itr = 0;

	Target *Ptr;
	TtmpItemRec *RN = NULL, *tmpRN = NULL, *tmp = NULL;
	bool resdata = false;
	if (TV->Items->Count == 0)
		return;
	while (i < TV->Items->Count)
		if (true) {
			// Ptr = (Target*) ListTr->Items[itr];

			FillListPulses(i, ListPulses);
			// Заливка списками запусков для этой цели-itr

			for (ii = 0; ii < ListPulses->Count; ii++) {
				RN = (TtmpItemRec*)ListPulses->Items[ii];
				j = ii + 1;
				tmpRN = RN;
				resdata = true;
				while (RN->TimeBack > (tmpRN->Time + Radar.PackRec[tmpRN->PckgID].Period * 1e-9)) {
					if (j > ListPulses->Count - 1) {
						resdata = false;
						break;
					}
					tmpRN = (TtmpItemRec*)ListPulses->Items[j];
					j++;
				}
				if ((j <= ListPulses->Count) && resdata) {
					tmp = (TtmpItemRec*)ListPulses->Items[j - 1];
					RN->BackItem = tmp; // запись потомка с откликом
					tmp->Parent = RN; // запись предка-излучателя в потомке
				}
			}
			// itr++;
			// }
			// else {
		}

	i++;
}

void __fastcall TForm1::BtnDataClick(TObject *Sender) {
	TtmpItemRec *tmpR, *tmpPar;
	// double *NoiseBufferRe;
	DynamicArray<double>NoiseBufferRe;
	int Dskr, Cnt, CntDskr, HiddenDiskret, shft, x, pulsesID;
	TPoint Q;
	float LevN = Power(10, Radar.Noise / 20.0);
	float LevADC = Power(2, double(Radar.ADCWidth - 1));
	float noiseL = int(LevADC * LevN);
	float LevTrAmp = Power(10, currentTarget.Ampl / 20.0);
	float Scale = double(CDOSWidth) / (LevADC * GetCountSamplesOfPulse());
	int ii = 0;
	Cnt = 0;
	for (int i = 0; i < 4; i++) {
		Cnt = Cnt + Radar.PackRec[i].CntDskr * Radar.PackRec[i].CntIZ;
	}
	ArrBig.Length = Cnt;

	for (int i = 0; i < TV->Items->Count; i++) {
		if (TV->Items->Item[i]->Level == 2) {

			tmpR = (TtmpItemRec*)TV->Items->Item[i]->Data;
			tmpPar = (TtmpItemRec*)tmpR->Parent;
			CntDskr = Radar.PackRec[tmpR->PckgID].CntDskr;
			Dskr = DistanceToDiskret(3E8 / 2 * (tmpPar->TimeBack - tmpR->Time) - virezKm);
		}
	}
	shft = GetShiftADCClock(tmpPar->TimeBack - tmpR->Time);

	// IsPulse = not(pulsesID+1/3 == 0)

	NoiseBufferRe.Length = CntDskr * GetCountSamplesOfPulse() + 32;
	for (int k = 0; k < CntDskr * GetCountSamplesOfPulse() + 32; k++) {
		NoiseBufferRe[k] = (1.0 * (Random(65536) - 32768.0) / 65536.0);
		// Memo6->Lines->Add(NoiseBufferRe[k]);
	}

	tmpR->ArrData = &ArrBig[ii];

	if (Dskr < 0) {
		HiddenDiskret = 0;

	}

	// Memo6->Lines->BeginUpdate();
	for (int k = 0; k < CntDskr; k++) {
		if ((k >= HiddenDiskret) && (k < Dskr + Radar.LFMlength)) {
			for (int j = 0; j < GetCountSamplesOfPulse(); j++) {
				x = (k - Dskr) * GetCountSamplesOfPulse() + j;
				NoiseBufferRe[k * 32 + j] = NoiseBufferRe[k * 32 + j] + SArrLFMup[x] * LevADC * LevTrAmp;
			}
		}
		Q = FQ(&NoiseBufferRe[k * GetCountSamplesOfPulse()], Scale);
		Memo7->Lines->Add(Q.X);
		// Memo8->Lines->Add(Q.Y);
		ArrBig[ii] = MAKELONG(Q.Y, Q.X);
		Memo6->Lines->Add(ArrBig[ii]);
		ii++;
	}
	// Memo6->Lines->EndUpdate();

	// pulsesID++ ;

	// Chart3->Series[0]->Clear();
	// Chart3->LeftAxis->Maximum = 32000;
	// Chart3->LeftAxis->Minimum = 0;
	//
	// unsigned char b0, b1, b2, b3 = 0;
	// for (int i = 0; i < ArrBig.Length; i++) {
	// b0 = LOBYTE(ArrBig[i]);
	// b1 = HIBYTE(ArrBig[i]);
	// b2 = LOBYTE(HIWORD(ArrBig[i]));
	// b3 = HIBYTE(HIWORD(ArrBig[i]));
	// ArrBig[i] = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
	//
	// Chart3->Series[0]->Add(sqrt(abs(LOWORD(ArrBig[i])*LOWORD(ArrBig[i]) + HIWORD(ArrBig[i])*HIWORD(ArrBig[i]))));
	//
	// }
	// WriteToBittware(ArrBig, Mode2Turn);

	RzPageControl1->ActivePage = TabSheet3;
}

// ---------------------------------------------------------------------------
void TForm1::DarwModuleDiskrets(TtmpItemRec *RN) {
	int Arr[32768];
	int i, Cnt;
	int Re, Im;
	unsigned char b0, b1, b2, b3;

	{
		Chart3->Series[0]->Clear();
		Chart3->LeftAxis->Maximum = 32000;
		Chart3->LeftAxis->Minimum = 0;
	}

	if (RN->ArrData == 0)
		return;

	Cnt = Radar.PackRec[RN->PckgID].CntDskr;
	// MoveMemory(@ Arr[0], RN.ArrData, Cnt * 4);
	memcpy(Arr, RN->ArrData, Cnt * 4);

	for (int i = 0; i < Cnt; i++) {
		b0 = LOBYTE(Arr[i]);
		b1 = HIBYTE(Arr[i]);
		b2 = LOBYTE(HIWORD(Arr[i]));
		b3 = HIBYTE(HIWORD(Arr[i]));
		Arr[i] = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
	}

	for (int i = 0; i < Cnt; i++) {
		Re = LOWORD(Arr[i]);
		Im = HIWORD(Arr[i]);
		Chart3->Series[0]->Add(sqrt(Re*Re + Im*Im));
	}

}

// ---------------------------------------------------------------------------
void TForm1::ADCGenerateTargetLFM(bool EnPulses, TLFMMode UpDown, double Arr[], float dbKu, float DeltaTimePulse, float Deviation,
	float Phase, float dbNoise, int Shift) {
	Target *Tr = NULL;
	int i = 0, tlength = 0, wArr = 0, w = 0;
	float a = 0.0, dskr = 0.0, df = 0.0, dFd = 0.0, Ku = 0.0, Knoise = 0.0, K = 0.0;
	double tmp = 0.0;
	DynamicArray<double>S2Arr, NoiseArr;
	Tr = &currentTarget;
	a = (2 * Tr->Velocity * DeltaTimePulse) / (Radar.WaveLength * 1E-3);
	a = Frac(a);
	a = a * 2 * M_PI + Phase;
	Ku = pow(10, dbKu / 20);
	Knoise = pow(10, dbNoise / 20);
	K = pow(2, Radar.ADCWidth - 1) - 1;
	Randomize();
	S2Arr.Length = 8192;
	NoiseArr.Length = 8192;
	for (int i = 0; i < GetCountSamplesOfPulseLFM() + Shift + GetCountSamplesOfPulse(); i++) {
		Arr[i] = 0;
		S2Arr[i] = 0;
	}
	dFd = Deviation / GetCountSamplesOfPulseLFM();
	if (EnPulses) {
		if (UpDown == lfmUp) {

			for (int i = 0; i < GetCountSamplesOfPulseLFM(); i++) {
				dskr = double(Radar.ADCClock) / ((Radar.I_F - Deviation) + dFd * i);
				tmp = sin(2 * M_PI * i / dskr + a);
				S2Arr[i + Shift] = tmp;
			}
		}
		if (UpDown == lfmDown) {
			for (int i = 0; i < GetCountSamplesOfPulseLFM(); i++) {
				dskr = double(Radar.ADCClock) / ((Radar.I_F + Deviation) - dFd * i);
				tmp = (sin(2 * M_PI * i / dskr + a));
				S2Arr[i + Shift] = tmp;
			}
		}
	}
	for (int i = 0; i < GetCountSamplesOfPulseLFM() + Shift + GetCountSamplesOfPulse(); i++) {
		NoiseArr[i] = 0 * RandG(0, K * Knoise);
		Arr[i] = S2Arr[i];
	}
}

void TForm1::GetADCPulseLFM(bool EnPulses, TtmpItemRec RN, double IArr[], int Shift) {
	TLFMMode typeLFM;
	if (RzRadioGroup1->ItemIndex == 0) {
		typeLFM = lfmUp;
	}
	else {
		typeLFM = lfmDown;
	}
	ADCGenerateTargetLFM(EnPulses, typeLFM, IArr, RN.Ampl, RN.TimeBack, Radar.Deviation, 0, Radar.Noise, Shift);
}

void __fastcall TForm1::RzPanel1MouseMove(TObject * Sender, TShiftState Shift, int X, int Y) {

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	gluUnProject(X, (float)viewport[3] - Y, 0, modelMatrix, projMatrix, viewport, &objx, &objy, &objz);

	D = sqrt(objy * objy + objx * objx) * 450;
	// Az = ArcTan2(objy, objx);
	Az = ArcTan2(objx, objy);

	if (Az > 0)
		Az = 180 / Pi * Az;
	else
		Az = 360 + (180 / Pi * Az);

	RzMapInfo->Caption = Format("%3.3f км,  %3.0f", ARRAYOFCONST((D, Az))) + " \xB0";
	Caption = Format("OpenGL X_coord = %.6f,  Y_coord = %.6f,  Z_coord = %.6f", ARRAYOFCONST((objx, objy, objz)));

	if (Shift.Contains(ssRight)) {

		// MousePosMove.X = MousePosMove.X + objx;
		// MousePosMove.Y = MousePosMove.Y + objy;
		// MousePosMove.State = siManualDrag;
		// InvalidateRect(hwnd1, 0, false);

		// glTranslatef(xpos, ypos, zpos);

	}
	else
		MousePosMove.State = siNone;

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RzPanel1Paint(TObject * Sender) {
	PAINTSTRUCT ps;
	BeginPaint(hwnd1, &ps);
	// InitViewProection();
	restart = false;
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

	// DrawSweep();
	glEnable(GL_BLEND);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, PointColor);

	if (IndexPoint != 5)
		PaintPoint();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, BezierColor);

	if (bezier_ready) {
		PaintBezier();
	}
	if (TVready) {
		glCallList(grid_list);
	}

	glCallList(grid_list2);
	SwapBuffers(dc1);
	EndPaint(hwnd1, &ps);
}

float TForm1::GetTimePacket() {
	float result = 0.0;
	int stop = GetCountPackages();
	for (int i = 0; i < stop; i++) {
		result = result + (Radar.PackRec[i].CntIZ) * (Radar.PackRec[i].Period) * 1E-9;
	}
	return result;
}

int TForm1::GetCountPackages() {
	int result = 0;
	result = 4; // Radar.PackRec.Length;
	return result;
}

float TForm1::GetTimePackage(int PackageID) {
	float result = 0.0;
	int i = 0;
	result = Radar.PackRec[PackageID].Period * Radar.PackRec[PackageID].CntIZ * 1E-9;
	return result;
}

float TForm1::PulseToTime(int PacketID, int PackageID, int PulseId) {
	float result = 0.0;
	int i = 0, Cnt = 0;
	result = PacketID;
	i = PackageID; // - 1;
	while (i > 0) {
		result = result + GetTimePackage(i);
		i--;
	}
	result = result + PulseId * Radar.PackRec[PackageID].Period * 1E-9;
	return result;
}

int TForm1::GetCountPulsesOfPacket() {
	int result = 0;
	int i = 0;
	result = 0;
	int stop = GetCountPackages();
	for (int i = 0; i < stop; i++) {
		result = result + Radar.PackRec[i].CntIZ;
	}
	return result;
}

int TForm1::GetCountRotation() {
	int result = 0;
	result = 1 * 6;
	return result;
}

int TForm1::GetCountPacketOfRotaion() {
	int result = 0;
	result = int(60.0 / GetCountRotation() / GetTimePacket());
	return result;
}

float TForm1::GetAzimutOfTime(float Time) {
	float result = 0.0;
	result = Time * 6.0 / 60.0 * 360.0;

	return result;
}

// void __fastcall TForm1::BtnDebugClick(TObject *Sender) {
//
// // glBegin(GL_LINES);
// //
// // float fx0, fy0, fx1, fy1 = 0.0;
// //
// // D_startX = StrToFloat(edt_D0->Text) * 1000.0 * sin(Pi * StrToFloat(edt_beta0->Text) / 180);
// // D_startY = StrToFloat(edt_D0->Text) * 1000.0 * cos(Pi * StrToFloat(edt_beta0->Text) / 180);
// //
// // D_endX = StrToFloat(edt_D3->Text) * 1000.0 * sin(Pi * StrToFloat(edt_beta3->Text) / 180);
// // D_endY = StrToFloat(edt_D3->Text) * 1000.0 * cos(Pi * StrToFloat(edt_beta3->Text) / 180);
// //
// // fx0 = D_startX / 450000.0;
// // fx1 = D_endX / 450000.0;
// // fy0 = D_startY / 450000.0;
// // fy1 = D_endY / 450000.0;
// //
// // glVertex2f(fx0, fy0);
// // glVertex2f(fx1, fy1);
// //
// // glEnd();
// //
// // SwapBuffers(dc1);
//
// Memo1->Lines->Add("GetTimePacket = " + FloatToStr(GetTimePacket()));
//
// }

// ---------------------------------------------------------------------------
void __fastcall TForm1::RzPanel1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	gluUnProject(X, (float)viewport[3] - Y, 0, modelMatrix, projMatrix, viewport, &objx, &objy, &objz);
	MousePosDown.X = objx;
	MousePosDown.Y = objy;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RzPanel1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	gluUnProject(X, (float)viewport[3] - Y, 0, modelMatrix, projMatrix, viewport, &objx, &objy, &objz);
	MousePosUp.X = objx;
	MousePosUp.Y = objy;
}

void __fastcall TForm1::FormKeyPress(TObject *Sender, wchar_t &Key) {

	Diagonal = (float)RzPanel1->Width / RzPanel1->Width;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-1.0 * Diagonal / Zoom, 1.0 * Diagonal / Zoom, -1.0 / Zoom, 1.0 / Zoom, -1.0, 1.0);

	switch (Key) {

	case 'a':
		xpos = xpos + 0.02;
		glTranslatef(xpos, ypos, zpos);
		break;

	case 'd':
		xpos = xpos - 0.02;
		glTranslatef(xpos, ypos, zpos);
		break;

	case 'w':
		ypos = ypos - 0.02;
		glTranslatef(xpos, ypos, zpos);
		break;

	case 's':
		ypos = ypos + 0.02;
		glTranslatef(xpos, ypos, zpos);
		break;

	case 'z':
		Zoom = Zoom - 0.02;

		break;

	case 'x':
		Zoom = Zoom + 0.05;

		break;

	}
	glOrtho(-1.0 / Zoom, 1.0 / Zoom, -1.0 / Zoom, 1.0 / Zoom, -1.0, 1.0);
	glTranslatef(xpos, ypos, zpos);
	InvalidateRect(hwnd1, 0, false);

}

// ---------------------------------------------------------------------------

void __fastcall TForm1::BtnAddTVClick(TObject * Sender) {

	if (edt_beta3->Text != "" && edt_beta0->Text != "") {
		Screen->Cursor = crHourGlass;
		int i, j, ii, irot;

		TVready = false;
		TTreeNode * Root, *NodeRot, *NodePacket, *NodePackage, *NodePulses, *PulsesData, *tmp, *tmp2;

		TV->Items->Clear();
		TV->Items->BeginUpdate();

		int PulsesOfPacket = GetCountPulsesOfPacket(); // 58
		int CntPack = GetCountPacketOfRotaion(); // 170
		TimeArr = new int[PulsesOfPacket];
		BetaArr = new float[PulsesOfPacket];
		int step = 0, currentPulse = 0;

		currentTarget.Velocity = StrToFloat(edt_speed->Text) * 1000.0 / 3600.0;
		currentTarget.Distance = StrToFloat(edt_D0->Text) * 1000;
		currentTarget.Beta = StrToFloat(edt_beta0->Text);

		float t1 = StrToFloat(edt_beta0->Text);
		float t2 = StrToFloat(edt_beta3->Text);

		D_start = StrToFloat(edt_D0->Text) * 1000.0;
		D_end = StrToFloat(edt_D3->Text) * 1000.0;

		D_startX = D_start * sin(Pi * StrToFloat(edt_beta0->Text) / 180);
		D_startY = D_start * cos(Pi * StrToFloat(edt_beta0->Text) / 180);

		D_endX = D_end * sin(Pi * StrToFloat(edt_beta3->Text) / 180);
		D_endY = D_end * cos(Pi * StrToFloat(edt_beta3->Text) / 180);

		// FILE *F;
		// if ((F = fopen("C:\\Users\\user\\Desktop\\RadarGL.txt", "w+")) == NULL)
		// ShowMessage("Cannot open input file.\n");

		grid_list = glGenLists(1);
		glNewList(grid_list, GL_COMPILE_AND_EXECUTE);
		glPointSize(Zoom*2);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);

		if (D_start < D_end) {

			irot = 0;
			currentPulse = 0;
			while (D_start < D_end) {

				NodeRot = AddNodeRot(irot);
				irot++;

				for (i = 0; i < CntPack; i++) {

					NodePacket = AddNodePacket(NodeRot, i);
					for (j = 0; j < 4; j++) {

						NodePackage = AddNodePackage(NodePacket, j);
						for (ii = 0; ii < Radar.PackRec[j].CntIZ; ii++) {
							NodePulses = AddNodePulses(NodePackage, ii);

							tmpItem = new TtmpItemRec;
							tmpItem->ZapID = ii;
							tmpItem->PackID = i;
							tmpItem->PckgID = j;
							tmpItem->Time = PulseToTime(i, j, ii);
							tmpItem->Beta = GetAzimutOfTime(tmpItem->Time) + currentTarget.Beta;
							if (t1 < t2) {
								if (!((tmpItem->Beta >= t1) && (tmpItem->Beta <= t2))) {
									tmpItem->Beta = currentTarget.Beta;

								}
							}

							if (t1 > t2) {
								if (!((tmpItem->Beta >= t2) && (tmpItem->Beta <= t1))) {
									tmpItem->Beta = currentTarget.Beta;

								}
							}

							tmpItem->TimeBack = tmpItem->Time + 2.0 * D_start / 3.0e8;
							tmpItem->deltaTime = tmpItem->TimeBack - tmpItem->Time;
							tmpItem->deltaDistance = currentTarget.Velocity * (tmpItem->deltaTime);
							tmpItem->X = (D_start / 450000.0) * sin(Pi * tmpItem->Beta / 180.0);
							tmpItem->Y = (D_start / 450000.0) * cos(Pi * tmpItem->Beta / 180.0);

							glVertex2f(tmpItem->X, tmpItem->Y);

							tmpItem->Parent = NULL;

							NodePulses->Data = tmpItem;

							// step = step + Radar.PackRec[j].Period;
							currentPulse++;

							D_start += tmpItem->deltaDistance;
							// fprintf(F, "Beta = %17.15f  PackID =%3d   PckgID =%3d   ZapID =%3d   X =%17.15f Y =%17.15f D_start = %17.15f\n",
							// tmpItem->Beta, tmpItem->PackID, tmpItem->PckgID, tmpItem->ZapID, tmpItem->X, tmpItem->Y, D_start);

						}

					}
				}
			}
			TVready = true;
			// UpdateListPulses();
			Memo1->Lines->Add("IZ count = " + FloatToStr(currentPulse));
		}
		else {

			irot = 0;
			currentPulse = 0;
			while (D_start > D_end) {

				NodeRot = AddNodeRot(irot);
				irot++;

				for (i = 0; i < CntPack; i++) {

					NodePacket = AddNodePacket(NodeRot, i);
					for (j = 0; j < 4; j++) {

						NodePackage = AddNodePackage(NodePacket, j);
						for (ii = 0; ii < Radar.PackRec[j].CntIZ; ii++) {
							NodePulses = AddNodePulses(NodePackage, ii);

							tmpItem = new TtmpItemRec;
							tmpItem->ZapID = ii;
							tmpItem->PackID = i;
							tmpItem->PckgID = j;
							tmpItem->Time = PulseToTime(i, j, ii);
							tmpItem->Beta = GetAzimutOfTime(tmpItem->Time) + currentTarget.Beta;
							// while (tmpItem->Beta >= 360)
							// tmpItem->Beta = tmpItem->Beta - 360.0;
							if (t1 < t2) {
								if (!((tmpItem->Beta >= t1) && (tmpItem->Beta <= t2))) {
									tmpItem->Beta = currentTarget.Beta;

								}
							}

							if (t1 > t2) {
								if (!((tmpItem->Beta >= t2) && (tmpItem->Beta <= t1))) {
									tmpItem->Beta = currentTarget.Beta;

								}
							}

							tmpItem->TimeBack = tmpItem->Time + 2.0 * D_start / 3.0e8;
							tmpItem->deltaTime = tmpItem->TimeBack - tmpItem->Time;
							tmpItem->deltaDistance = currentTarget.Velocity * (tmpItem->deltaTime);
							tmpItem->X = (D_start / 450000.0) * sin(Pi * tmpItem->Beta / 180.0);
							tmpItem->Y = (D_start / 450000.0) * cos(Pi * tmpItem->Beta / 180.0);

							glVertex2f(tmpItem->X, tmpItem->Y);

							tmpItem->Parent = NULL;

							NodePulses->Data = tmpItem;

							currentPulse++;

							D_start -= tmpItem->deltaDistance;
							// fprintf(F, "Beta = %17.15f  PackID =%3d   PckgID =%3d   ZapID =%3d   X =%17.15f Y =%17.15f D_start = %17.15f\n",
							// tmpItem->Beta, tmpItem->PackID, tmpItem->PckgID, tmpItem->ZapID, tmpItem->X, tmpItem->Y, D_start);
						}
					}
				}
			}
			TVready = true;
			// UpdateListPulses();
			Memo1->Lines->Add("IZ count = " + FloatToStr(currentPulse));
		}
		TV->Items->EndUpdate();
		// fclose(F);
		Memo1->Lines->Add("N of Rotation = " + FloatToStr(irot));
	}
	Screen->Cursor = crDefault;
	delete[]TimeArr;
	delete[]BetaArr;
	glEnd();
	glEndList();
	SwapBuffers(dc1);
}

void __fastcall TForm1::BtnDebugClick(TObject *Sender) {

	if (edt_beta3->Text != "" && edt_beta0->Text != "") {
		Screen->Cursor = crHourGlass;
		int i, j, ii, irot;

		int PulsesOfPacket = GetCountPulsesOfPacket(); // 58
		int CntPack = GetCountPacketOfRotaion(); // 170
		int step = 0, currentPulse = 0;

		currentTarget.Velocity = StrToFloat(edt_speed->Text) * 1000.0 / 3600.0;
		currentTarget.Distance = StrToFloat(edt_D0->Text) * 1000;

		float t1 = StrToFloat(edt_beta0->Text);
		float t2 = StrToFloat(edt_beta3->Text);

		D_start = StrToFloat(edt_D0->Text) * 1000.0;
		D_end = StrToFloat(edt_D3->Text) * 1000.0;

		double Route = sqrt(D_start * D_start + D_end * D_end - 2 * D_start * D_end * (cos(Pi * (t2 - t1) / 180.0)));
		double RouteTime = Route / currentTarget.Velocity;
		Memo1->Lines->Clear();
		Memo1->Lines->Add("Путь который проходит цель в метрах = " + FloatToStr(Route));
		Memo1->Lines->Add("");
		Memo1->Lines->Add("Время наблюдения цели = " + FloatToStr(RouteTime));
		Memo1->Lines->Add("");
		if (t2 > t1)
			Memo1->Lines->Add("Угол между начальным и конечным положением цели = " + FloatToStr(t2 - t1));
		if (t2 < t1)
			Memo1->Lines->Add("Угол между начальным и конечным положением цели = " + FloatToStr(t1 - t2));

		Memo1->Lines->Add("");

		Memo1->Lines->Add("Количество оборотов антенны которое совершает антенна за время наблюдения цели= " + FloatToStr(RouteTime / 10));
		Memo1->Lines->Add("");
		Memo1->Lines->Add("Угол между начальным и конечным положением цели = " + FloatToStr(t2 - t1));
		Memo1->Lines->Add("");
		Memo1->Lines->Add("За время одного оборота цель пролетит расстояние = " + FloatToStr(currentTarget.Velocity * 10));

		Memo1->Lines->Add("");
		Memo1->Lines->Add("Угол teta = " + FloatToStr
			(180 / Pi * (acos((D_start*D_start + Route*Route - D_end*D_end) / (2*D_start*Route)))));

		deltaDD = currentTarget.Velocity * 10;

		Memo1->Lines->Add("");
		Memo1->Lines->Add("D_start_next = " + FloatToStr(sqrt(D_start*D_start + deltaDD*deltaDD -
			2*D_start*deltaDD * cos((D_start*D_start + Route*Route - D_end*D_end) / (2*D_start*Route)))));

		grid_list2 = glGenLists(1);

		glNewList(grid_list2, GL_COMPILE_AND_EXECUTE);

		glPointSize(Zoom*2);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);

		double teta = acos((D_start * D_start + Route * Route - D_end * D_end) / (2 * D_start * Route));

		double D_start_next = 0;
		double X, Y = 0.0;
		int counter = 0;

		glVertex2f((D_start / 450000.)*sin(Pi*t1 / 180), (D_start / 450000.)*cos(Pi*t1 / 180));
		glVertex2f((D_end / 450000.)*sin(Pi*t2 / 180), (D_end / 450000.)*cos(Pi*t2 / 180));

		double beta_rad = t2 * Pi / 180;
		double alfa = 0;

		while (Route > 0) {

			double teta = acos((D_start * D_start + Route * Route - D_end * D_end) / (2 * D_start * Route));
			D_start_next = sqrt(D_start * D_start + deltaDD * deltaDD - 2 * D_start * deltaDD * cos(teta));

			alfa = alfa + acos((D_start * D_start + D_start_next * D_start_next - deltaDD * deltaDD) / (2 * D_start * D_start_next));

			X = (D_start_next / 450000.0) * sin(alfa + Pi * t1 / 180.0);
			Y = (D_start_next / 450000.0) * cos(alfa + Pi * t1 / 180.0);

			glVertex2f(X, Y);

			Route = Route - deltaDD;
			D_start = D_start_next;

			counter++;
		}
		Screen->Cursor = crDefault;
		glEnd();
		glEndList();
		ShowMessage(FloatToStr(counter));
		InvalidateRect(hwnd1, 0, true);
	}
}

void __fastcall TForm1::edt_D0Change(TObject *Sender) {
	// edt_D0->Text =edt_D0->Text;
}
// ---------------------------------------------------------------------------
