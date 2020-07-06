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
	// DecimalSeparator = 0x2e;
	edt_epr->ClearSelection();

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
	PaintPoint();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BezierColor);

	if (bezier_ready) {
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
	if (IndexPoint > 4)
		IndexPoint = 0;
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

		BtnRefreshClick(this);

	}

	IndexPoint++;

}

// ---------------------------------------------------------------------------
void TForm1::PaintPoint() {
	if (IndexPoint != 5) {
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < IndexPoint; i++) {
			glVertex2f(OGLpoints[i][0], OGLpoints[i][1]);
		}
		glEnd();
	}
	else
		bezier_ready = false;
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
	if (edt_beta0 != "" && edt_beta1 != "" && edt_beta2 != "" && edt_beta3 != "" && edt_D0 != "" && edt_D1 != "" && edt_D2 != "" &&
		edt_D3 != "") {

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
	bezier_ready = false;
	edt_beta0->Clear();
	edt_D0->Clear();
	edt_beta1->Clear();
	edt_D1->Clear();
	edt_beta2->Clear();
	edt_D2->Clear();
	edt_beta3->Clear();
	edt_D3->Clear();
}
// ---------------------------------------------------------------------------
