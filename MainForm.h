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
#include "RzSplit.hpp"
#include <Dialogs.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#define Pi M_PI


// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TRzStatusBar *RzStatusBar1;
	TRzToolbar *RzToolbar1;
	TRzFieldStatus *RzGL_Vendor;
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
	TRzPanel *RzPanel1;
	TRzClockStatus *RzClockStatus1;
	TRzFieldStatus *RzMapInfo;
	TColorDialog *ColorDialog1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall RzPanel1Paint(TObject *Sender);
	void __fastcall RzPanel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall BtnUtilitiesClick(TObject *Sender);

private: // User declarations

	void __fastcall SetDCPixelFormat(HDC hdc);
	void __fastcall PaintGrid();
	void __fastcall PaintTarget();
	void __fastcall InitViewProection(float x, float y, float dXX, float dYY);
	void __fastcall PaintCurrentCircle();
	void __fastcall DrawAxis();

	HWND hwnd1;
	HGLRC hrc1;
	HDC dc1;

	GLfloat MCGrid[4];
	GLfloat MCPoint[4];
	GLfloat MCTarget[4];
	GLfloat tX, tY, DX, DY;

public: // User declarations

	float PosZoomX1, PosZoomY1, PosZoomX2, PosZoomY2, Diagonal, Zoom;

	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
