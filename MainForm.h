// ---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include "RzStatus.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Math.hpp>
#include <math.h>
#include <GL/gl.h>

struct TVertex {
	float X, Y, Z;
};

// ID- �������� ��� �������� ������ glCallList(ID)
const GLubyte Place = 1;
const GLubyte Sectors = 2;
const GLubyte Grid = 3;
const GLubyte Mas = 4;
const GLubyte CU = 5;
const GLubyte CU2 = 6;
const GLubyte TIK = 7;
const GLubyte TIK2 = 8;
const GLubyte TXT = 9;
const GLubyte TIKcu2 = 10;
int GLF_START_LIST = 1000;
int dalnost = 450000; // ��������� 400 ��
// ��� �������-�����
GLuint SelectGrid[64];
int gridSize = 20;
GLfloat grid4x4[4][4][3] = { {

		{-0.5, -0.5, 0.5}, {-0.25, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}},

	{ {-0.25, -0.25, 0.5}, {-0.25, -0.25, 0.5}, {0.25, -0.25, 0.5}, {0.5, -0.25, 0.5}},

	{ {-0.5, 0.25, -0.9}, {-0.5, 0.25, -0.9}, {0.25, 0.25, -0.9}, {0.5, 0.25, -0.9}},

	{ {-0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}, {0.25, 0.5, 0.5}, {0.5, 0.5, 0.5}}

};

int gl_cntrot = 0; // ���������� ����� �������
long double gl = 0.9; // ��������-
long double gl_inc = 0.03; // ��� ��������� ��������
long double km = 1.0; // �������
GLfloat glx = 0; // �������� �������� �� X
GLfloat gly = 0; // �������� �������� �� Y
GLfloat ry, tx, ty, rz, ang; // �������- XYZA

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TRzStatusBar *RzStatusBar1;
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TRzFieldStatus *RzGL_Vendor;
	TRzFieldStatus *RzGL_Renderer;
	TRzFieldStatus *RzGL_Version;
	TImageList *ImageList1;
	TRzToolButton *BtnExecute;
	TRzToolButton *BtnUtilities;
	TRzToolButton *BtnPost;
	TRzToolButton *BtnRefresh;
	TRzToolButton *BtnCancel;
	TRzSpacer *RzSpacer1;
	TRzSpacer *RzSpacer2;
	TRzSpacer *RzSpacer3;
	TRzSpacer *RzSpacer4;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);

private: // User declarations

	void __fastcall PaintPlace3d();
	void __fastcall texto(GLfloat x, GLfloat y, String s);
	void __fastcall PaintTXT();
	void __fastcall PaintSectors();
	void __fastcall PaintGrid();
	void __fastcall PaintMas3d(bool value);
	void __fastcall SetDCPixelFormat(HDC hdc);

	HWND hwnd1;
	HGLRC hrc1;
	HDC dc1;

public: // User declarations

	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
