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
#pragma resource "*.dfm"
TForm1 *Form1;

GLdouble modelMatrix[16];
GLdouble projMatrix[16];
GLint viewport[4];
GLdouble objx, objy, objz = 0;
TPoint *targetArr = new TPoint[100];

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::SetDCPixelFormat(HDC hdc) {

	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat = 0;

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
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

	String ch = (char *)(glGetString(GL_VENDOR));
	String ch2 = (char *)(glGetString(GL_RENDERER));
	RzGL_Vendor->Caption = ch + ", " + ch2;
	RzGL_Version->Caption = ((char *) glGetString(GL_VERSION));

	// PosZoomX1 = -1;
	// PosZoomX2 = -1;
	// PosZoomY1 = -0.5;
	// PosZoomY2 = -0.5;

	Zoom = 1;

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender) {
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

	DrawAxis();
	PaintGrid();
	PaintTarget();
	SwapBuffers(dc1);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintGrid() {
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
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintTarget() {
	float a = 0.0, x = 0.0, y = 0.0;
	int i = 0;
	glPointSize(7);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	tX = tY = -0.5;
	glVertex2f(tX, tY);
	glEnd();
}

void __fastcall TForm1::InitViewProection(float x, float y, float dXX, float dYY) {
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
	InvalidateRect(hwnd1, NULL, false);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::DrawAxis() {

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
}

void __fastcall TForm1::RzPanel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y) {
	float D, Az = 0;

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

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BtnUtilitiesClick(TObject *Sender) {
	if (ColorDialog1->Execute()) {
		InvalidateRect(hwnd1, 0, true);
	}
}
// ---------------------------------------------------------------------------
