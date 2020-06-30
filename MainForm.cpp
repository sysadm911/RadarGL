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
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	hwnd1 = Panel1->Handle;
	dc1 = GetDC(hwnd1);
	SetDCPixelFormat(dc1);
	hrc1 = wglCreateContext(dc1);
	wglMakeCurrent(dc1, hrc1);

	RzGL_Vendor->Caption = (char *) glGetString(GL_VENDOR);
	RzGL_Renderer->Caption = (char *) glGetString(GL_RENDERER);
	RzGL_Version->Caption = (char *) glGetString(GL_VERSION);

	glClearColor(0.05, 0.05, 0.05, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PaintGrid();
	PaintSectors();
	PaintTXT();
	PaintMas3d(true);

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender) {
	wglDeleteContext(hrc1);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::SetDCPixelFormat(HDC hdc) {

	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat = 0;

	ZeroMemory(&pfd, sizeof(pfd));
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, nPixelFormat, &pfd);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintGrid() {
	GLfloat r;
	int i = 0, n = 0, k = 0;
	glNewList(Grid, GL_COMPILE);
	// вне линии-
	r = 0.5 * km;
	n = 100;
	glColor3f(0.15, 0.15, 0.15);
	glLineWidth(1.0);
	for (int stop = 10, k = 0; k <= stop; k++) {
		glBegin(GL_LINE_STRIP);
		glVertex2f(r * k / 5.0, 0);
		for (int i = 1; i <= n; i++)
			glVertex2f(r * cos(2 * M_PI / n * i) * k / 5.0, r * sin(2 * M_PI / n * i) * k / 5.0);
		glEnd();
	}
	// вне сектор-
	i = 0;
	do {
		glBegin(GL_LINE_STRIP);
		glVertex2f(km * 0.0 * sin(M_PI * (90 - i) / 180), km * 0.00 * sin(M_PI * i / 180));
		glVertex2f(km * sin(M_PI * (90 - i) / 180), km * sin(M_PI * i / 180));
		glEnd();
		i = i + 30;
	}
	while (!(i >= 360));
	glEndList();
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender) {
	glViewport(0, 0, Panel1->Width, Panel1->Height);
	glClearColor(0, 0, 0, 1.0); // цвет фона
	glClear(GL_COLOR_BUFFER_BIT); // очистка буфера цвета
	glCallList(Grid);
	glCallList(Sectors);
	glCallList(TXT);
	glCallList(Mas);
	SwapBuffers(dc1);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender) {
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// glMatrixMode(GL_MODELVIEW);
	// InvalidateRect(hwnd1, 0, false);
	Refresh();

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintSectors() {
	GLfloat r;
	int i, n, k;

	glNewList(Sectors, GL_COMPILE);
	// вну линии-
	r = 0.5 * km;
	n = 100;
	glColor3f(0.1, 0.1, 0.1);
	glLineWidth(1.0);
	for (k = 0; k <= 40; k++) {
		glBegin(GL_LINE_STRIP);
		glVertex2f(r*k / 20, 0);
		for (i = 1; i <= n; i++)
			glVertex2f(r*cos(2*M_PI / n*i)*k / 20, r*sin(2*M_PI / n*i)*k / 20);
		glEnd();
	}
	// вну сектор-
	i = 0;
	do {
		glBegin(GL_LINE_STRIP); // glVertex2f(0,0);
		glVertex2f(km*0.01*sin(M_PI*(90 - i) / 180), km*0.01*sin(M_PI*i / 180));
		glVertex2f(km*sin(M_PI*(90 - i) / 180), km*sin(M_PI*i / 180));
		glEnd();
		i = i + 6;
	}
	while (i >= 360);
	glEndList();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintTXT() {
	String S[12];
	S[0] = "0°";
	S[1] = "30°";
	S[2] = "60°";
	S[3] = "90°";
	S[4] = "120°";
	S[5] = "150°";
	S[6] = "180°";
	S[7] = "210°";
	S[8] = "240°";
	S[9] = "270°";
	S[10] = "300°";
	S[11] = "330°";
	int i = 0, j = 0, r = 0, k = 0;
	glNewList(TXT, GL_COMPILE);
	// текст- вариант1
	glColor3f(0.2, 0.2, 0.2);
	for (int i = -9; i <= 9; i++) {
		if (i / 2.0-int(i / 2.0) != 0)
			if (i != 0)
				texto((i / 10.0) + 0.005, 0.007, IntToStr(abs(i * dalnost / 10000)) + "km");
	}

	// оси-
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glScalef(0.51, 0.51, 1.0);
	r = 360 / 12;
	for (int i = 0; i < 12; i++) {
		texto(0.0, 2.11, S[i]);
		for (int j = 0; j <= 2; j++) {
			glLineWidth(1.5);
			glBegin(GL_LINES);
			glVertex3d(0, 2.0, 0.0);
			glVertex3d(0, 1.98, 0.0);
			glEnd();
			glRotatef(-2.0, 0.0, 0.0, 1.0);
			glLineWidth(0.1);
			for (int k = 1; k <= 4; k++) {
				glBegin(GL_LINES);
				glVertex3d(0, 2.0, 0.0);
				glVertex3d(0, 1.98, 0.0);
				glEnd();
				glRotatef(-2.0, 0.0, 0.0, 1.0);
			}
		}
	}
	glPopMatrix();
	glEndList();

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::texto(GLfloat x, GLfloat y, String t) {
	glRasterPos2f(x, y);
	glListBase(GLF_START_LIST);
	glCallLists(t.Length(), GL_UNSIGNED_BYTE, t.c_str());
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintMas3d(bool value) {
	GLuint i, j;
	bool fViewMas3D = value;
	if (fViewMas3D) {
		// инит сетки-
		glSelectBuffer(sizeof(SelectGrid) / sizeof(SelectGrid[0]), SelectGrid);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(gridSize, 0.0, 1.0, gridSize, 0.0, 1.0);
		glNewList(Mas, GL_COMPILE);
		glColor3f(1.0, 0.0, 0.0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 4 * 3, 4, &grid4x4[0][0][0]);
		glEvalMesh2(GL_LINE, 0, gridSize, 0, gridSize);
		glEndList();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PaintPlace3d() {
	GLfloat position[4 /* # range 0..3 */];
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 1.0;
	position[3] = 1.0;
	int i = 0, j = 0, nrm_count = 0;
	TVertex V;
	GLfloat glpr[4 /* # range 0..3 */];
	test_sinxx(true);
	glNewList(Place, GL_Compile);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glpr[0] = 1.0;
	glpr[1] = 1.0;
	glpr[2] = 1.0;

	// ПОСТРОЕНИЕ 3D ------------------------------------------------------------
	if (gl_cntrot != 0) {

		// набиваем нормали всех треугольников-
		nrm_count = 0;
		for (int i = 0; i < 499; i++)
			for (int j = 0; j < 1499; j++) {
				nrm[nrm_count] = CalcNormal(vals[i][j], vals[i + 1][j], vals[i + 1][j + 1]);
				// if smooth=2 then nrm[nrm_count]:= CalcNormal2(val[i,j],val[i+1,j],val[i+1,j+1]);
				nrm_count++;
				nrm[nrm_count] = CalcNormal(vals[i + 1][j + 1], vals[i][j + 1], vals[i][j]);
				// if smooth=2 then nrm[nrm_count]:= CalcNormal2(val[i+1,j+1],val[i,j+1],val[i,j]);
				nrm_count++;
			}

		// ----------------------------------
		// строим поверхность треугольниками-
		if (smooth == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // типа скелет-
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		gl_cnt_name = 0;
		nrm_count = 0;
		for (int i = 0; i < 499; i++)
			for (int j = 0; j < 1499; j++) {
				if ((vals[i][j].Name != "") && (vals[i + 1][j + 1].Name != "") && (vals[i + 1][j].Name != "") &&
					(vals[i][j + 1].Name != "")) { // fix- отсекаем рисование несуществующх-> за несуществующие принимаем без имени!!!

					glLoadName(strtoint(vals[i][j].Name));

					// ПОДСВЕТКА ОБНАРУЖЕНИЙ ---------------------------------------------------
					if (vals[i][j].all == 0x1) {
						glpointsize(2.5);
						glEnable(GL_POINT_SMOOTH);
						glColor3f(0.0, 1.0, 0.0);
						glBegin(GL_POINTS);
						glVertex3f(vals[i][j].X, vals[i][j].y, 0.0);
						glEnd();
					}
					// -------------------------------------------------------------------------
					if (check_DAT.Checked) {
						// прозрачность-
						glpr[3] = gl_pr + (double((vals[i][j].z + vals[i + 1][j].z + vals[i + 1][j + 1].z)) / 3);
						glColor4fv(&glpr[0]);
						// glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, @glpr);
						//
						glBegin(GL_TRIANGLES); // 1- треуг
						if ((smooth == 0) || (smooth == 1)) {
							V = nrm[nrm_count];
							nrm_count++; // CalcNormal(val[i,j],val[i+1,j],val[i+1,j+1]);
							glNormal3f(V.X, V.y, V.z);
						}
						glNormal3f(vals[i][j].y, vals[i][j].X, vals[i][j].z); // стандартный метод-
						// if smooth=5 then glNormal3f(normal[i,j].y,normal[i,j].x,normal[i,j].z); //нестандартный метод-
						glVertex3fv(&vals[i][j]); // 1- верш
						glNormal3f(vals[i + 1][j].y, vals[i + 1][j].X, vals[i + 1][j].z);
						// if smooth=5 then glNormal3f(normal[i+1,j].y,normal[i+1,j].x,normal[i+1,j].z);
						glVertex3fv(&vals[i + 1][j]); // 2
						glNormal3f(vals[i + 1][j + 1].y, vals[i + 1][j + 1].X, vals[i + 1][j + 1].z);
						// if smooth=5 then glNormal3f(normal[i+1,j+1].y,normal[i+1,j+1].x,normal[i+1,j+1].z);
						glVertex3fv(&vals[i + 1][j + 1]); // 3
						glEnd();

						// прозрачность-
						glpr[3] = gl_pr + (double((vals[i + 1][j + 1].z + vals[i][j + 1].z + vals[i][j].z)) / 3);
						glColor4fv(&glpr[0]);
						// glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, @glpr);
						//
						glBegin(GL_TRIANGLES); // 2- треуг
						if ((smooth == 0) || (smooth == 1)) {
							V = nrm[nrm_count];
							nrm_count++; // CalcNormal(val[i+1,j+1],val[i,j+1],val[i,j]);
							glNormal3f(V.X, V.y, V.z);
						}
						glNormal3f(vals[i + 1][j + 1].y, vals[i + 1][j + 1].X, vals[i + 1][j + 1].z);
						// if smooth=5 then glNormal3f(normal[i+1,j+1].y,normal[i+1,j+1].x,normal[i+1,j+1].z);
						glVertex3fv(&vals[i + 1][j + 1]);
						glNormal3f(vals[i][j + 1].y, vals[i][j + 1].X, vals[i][j + 1].z);
						// if smooth=5 then glNormal3f(normal[i,j+1].y,normal[i,j+1].x,normal[i,j+1].z);
						glVertex3fv(&vals[i][j + 1]);
						glNormal3f(vals[i][j].y, vals[i][j].X, vals[i][j].z);
						// if smooth=5 then glNormal3f(normal[i,j].y,normal[i,j].x,normal[i,j].z);
						glVertex3fv(&vals[i][j]);
						glEnd();
					}
				}
			}

		// ПОСТРОЕНИЕ 2D ------------------------------------------------------------
	}
	else
		for (int stop = Length(val0) - 1, i = 0; i <= stop; i++) {
			glLoadName(StrToInt(val0[i].Name));
			glPointSize(2.5);
			glEnable(GL_POINT_SMOOTH);
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_POINTS);
			glVertex3f(val0[i].X, val0[i].y, 0.0);
			glEnd();
		}
	//
	glDisable(GL_BLEND);
	glEndList();

}
// ---------------------------------------------------------------------------
