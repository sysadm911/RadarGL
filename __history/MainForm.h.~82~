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
#include "RzGroupBar.hpp"
#include "RzLstBox.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include "RzTabs.hpp"
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define Pi M_PI

typedef struct Target {
	String Name;
	float S;
	float Velocity;
	float Distance;
	float Beta;
	float Length;
	float Height;
	float X, Y;
	float Ampl;
	int Time;
} Target;

typedef struct TRecFreqPackage {
	int Period, CntIZ, CntDskr, EnumKpp;
} TRecFreqPackage;

struct TRecRadar {
	int WaveLength;
	int PulseLength;
	int Deviation;
	int I_F;
	float wDN;
	int ADCClock;
	int ADCWidth;
	int LFMlength;
	TRecFreqPackage PackRec[4];
};

struct TtmpItemRec {
	double Beta, Time, Ampl, TimeBack;
	int ZapID, PackID, PckgID;
	void* BackItem, *Parent, *ArrData;
};

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TRzStatusBar *RzStatusBar1;
	TImageList *ImageList1;
	TRzPanel *RzPanel1;
	TRzClockStatus *RzClockStatus1;
	TRzFieldStatus *RzMapInfo;
	TColorDialog *ColorDialog1;
	TTimer *Timer1;
	TRzPanel *RzPanel2;
	TRzGroupBox *RzGroupBox1;
	TRzLabel *lbl_epr;
	TRzLabel *lbl_speed;
	TRzMaskEdit *edt_epr;
	TRzMaskEdit *edt_speed;
	TRzGroupBox *rzgrpbx_coord3;
	TRzLabel *lbl_beta3;
	TRzLabel *lbl_D3;
	TRzMaskEdit *edt_beta3;
	TRzMaskEdit *edt_D3;
	TRzGroupBox *rzgrpbx_coord0;
	TRzLabel *lbl_beta0;
	TRzLabel *lbl_D0;
	TRzMaskEdit *edt_beta0;
	TRzMaskEdit *edt_D0;
	TRzGroupBox *rzgrpbx_coord1;
	TRzLabel *lbl_beta1;
	TRzLabel *lbl_D1;
	TRzMaskEdit *edt_beta1;
	TRzMaskEdit *edt_D1;
	TRzGroupBox *rzgrpbx_coord2;
	TRzLabel *lbl_beta2;
	TRzLabel *lbl_D2;
	TRzMaskEdit *edt_beta2;
	TRzMaskEdit *edt_D2;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnUtilities;
	TRzToolButton *BtnExecute;
	TRzToolButton *BtnRefresh;
	TRzToolButton *BtnOK;
	TMemo *Memo1;
	TTreeView *TV;
	TRzToolButton *BtnAttach;
	TRzPageControl *RzPageControl1;
	TRzTabSheet *TabSheet1;
	TRzTabSheet *TabSheet2;
	TChart *Chart1;
	TLineSeries *Series1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall RzPanel1Paint(TObject *Sender);
	void __fastcall RzPanel1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall BtnUtilitiesClick(TObject *Sender);
	void __fastcall RzPanel1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall BtnExecuteClick(TObject *Sender);
	void __fastcall lbl_beta0Change(TObject *Sender);
	void __fastcall lbl_beta0KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnRefreshClick(TObject *Sender);
	void __fastcall TVClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnAttachClick(TObject *Sender);
	void __fastcall RzPageControl1PageChange(TObject *Sender);

private: // User declarations

	void DrawSweep();
	void PaintPoint();
	void AddPoint();
	void PaintBezier();
	void SetDCPixelFormat(HDC hdc);
	void PaintGrid();
	void PaintTarget();
	void InitViewProection(float x, float y, float dXX, float dYY);
	void PaintCurrentCircle();
	void DrawAxis();

	HWND hwnd1;
	HGLRC hrc1;
	HDC dc1;

	GLfloat MCGrid[4];
	GLfloat MCPoint[4];
	GLfloat MCTarget[4];
	GLfloat tX, tY, DX, DY;

public: // User declarations

	float PosZoomX1, PosZoomY1, PosZoomX2, PosZoomY2, Diagonal, Zoom;

	void __fastcall TForm1::Textout(char* str, GLfloat x, GLfloat y, GLfloat *color);

	TRecRadar Radar;
	Target currentTarget;
	TtmpItemRec *tmpItem;
	int *TimeArr;
	float *BetaArr;
	int TimeOfPacket;
	float BetaOfPacket;

	int GetCountPulsesOfPacket(void);
	TTreeNode* AddNodeRoot(void);
	TTreeNode* AddNodePackage(TTreeNode *Parent, int i);
	TTreeNode* AddNodePulses(TTreeNode *Parent, int i);
	Target* AddTarget();

	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
