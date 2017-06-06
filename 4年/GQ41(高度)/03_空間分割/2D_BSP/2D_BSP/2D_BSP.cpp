//=======================================================================================
//
//	  [ 2D_BSP ] : Binary Space Partitioning
//
//=======================================================================================

//----- �C���N���[�h�t�@�C��
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>

//----- �萔��`
#define SCREEN_WIDTH			800				// �X�N���[���@��
#define SCREEN_HEIGHT			600				// �X�N���[���@����
#define AXIS_X_OFFSET			SCREEN_WIDTH/2	// �w���W�I�t�Z�b�g
#define AXIS_Y_OFFSET			SCREEN_HEIGHT/2	// �x���W�I�t�Z�b�g

POINT	poly_vertex[] = {			// ���_���W
	//  x    y
	{-150, 150},		// 0
	{ -50,   0},		// 1
	{ 150, 150},		// 2
	{ 300,   0},		// 3
	{ 150,-150},		// 4
	{  50,   0},		// 5
	{-150,-150},		// 6
	{-300,   0},		// 7

	{-150, 150},		// 8
};
#define POLY_MAX	8				// �ʐ�

//----- �\���̒�`
typedef struct {
	POINT	p0, p1;			// ���W
	float	nx, ny;			// �@���x�N�g��
} FACE;

struct BSPnode {
	BSPnode	*front;			// �\���A�����m�[�h�ւ̃|�C���^
	BSPnode	*back;			// �\���A�����m�[�h�ւ̃|�C���^
	int		face;			// ������
	int		*front_face;	// �\���ʃ��X�g�ւ̃|�C���^
	int		*back_face;		// �����ʃ��X�g�ւ̃|�C���^
	int		front_num;		// �\���̖ʐ�
	int		back_num;		// �����̖ʐ�
};

//----- �O���[�o���ϐ�
const TCHAR szClassName[] = _T("2D_BSP");
const TCHAR szAppName[]   = _T("[ 2D_BSP ] Binary Space Partitioning");

FACE		g_Face[POLY_MAX * POLY_MAX];		// �ʏ��
int			g_FaceIndex[POLY_MAX * POLY_MAX];	// �ʎg�p�����
BSPnode		*g_BSPnode;							// ���[�g�m�[�h�p�|�C���^

HWND		g_hWndApp;					// �E�B���h�E�n���h��
HDC			g_hMemDC;					// ����ʂc�b
HBITMAP		g_hBitmap;					// ����ʃr�b�g�}�b�v
bool		g_bOnInfo;					// �x�N�g���E���l���\���X�C�b�`

int			g_DispTreeX;				// �a�r�o�c���[�\���w���W
int			g_DispTreeY;				// �a�r�o�c���[�\���x���W

//----- �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void MainModule();
void RemakeBSPtree();
void DrawGrid();
void DrawPolygon();
void DrawPoint();
void DispInfo();
void CalcNormal();
int CheckFrontBack(FACE *face0, FACE *face1);
void MakeBSPtree(BSPnode *node, int *face_list, int face_num);
void DeleteBSPtree(BSPnode *node);
void DispBSPtree(BSPnode *node, int indent);
void DispFace();

//---------------------------------------------------------------------------------------
// ���C��
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR args, int cmdShow)
{
	MSG		msg;

	// �ϐ�������
	g_bOnInfo = true;			// ���\���X�C�b�`���n�e�e
	g_BSPnode = NULL;

	// �E�B���h�E�N���X��o�^
	WNDCLASS wndClass = {
		0, WndProc, 0, 0, hInst,
		LoadIcon(hInst, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		0, NULL, szClassName
	};
	if (RegisterClass(&wndClass) == 0) return false;

	// �E�C���h�E���쐬
	g_hWndApp = CreateWindow(
		szClassName, szAppName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH  + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL, NULL, hInst, NULL);
	if (!g_hWndApp) return false;
	ShowWindow(g_hWndApp, cmdShow);
	UpdateWindow(g_hWndApp);

	// ���C�����[�v
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

//-----------------------------------------------------------------------------
// ���b�Z�[�W����
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC				hdc;
	int				i, mx, my;
	PAINTSTRUCT		ps;
	static bool		MouseButtonFlg;
	static int		PointMoveFlg;

	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);
		g_hMemDC = CreateCompatibleDC(hdc);		// ����ʂ̍쐬
		g_hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
		SelectObject(g_hMemDC, g_hBitmap);
		SetBkMode(g_hMemDC, TRANSPARENT);
		SetTextColor(g_hMemDC, RGB(0, 0, 0));
		ReleaseDC(hWnd, hdc);

		// �e�평���l�ݒ�
		MouseButtonFlg = false;
		PointMoveFlg = -1;
		for (i = 0; i < POLY_MAX; i++) {
			g_Face[i].p0.x = poly_vertex[i  ].x;
			g_Face[i].p0.y = poly_vertex[i  ].y;
			g_Face[i].p1.x = poly_vertex[i+1].x;
			g_Face[i].p1.y = poly_vertex[i+1].y;
		}
		RemakeBSPtree();						// �a�r�o�c���[�č\�z
		InvalidateRect(g_hWndApp, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:			// �L�[�������ꂽ
		switch (wParam) {
		case VK_ESCAPE:	DestroyWindow(hWnd);	return 0;	// �I��
		case 'I':				// ���\���X�C�b�`�̐؂�ւ�
			g_bOnInfo = !g_bOnInfo;
			InvalidateRect(g_hWndApp, NULL, TRUE);
			return 0;
		}
		break;
	case WM_MOUSEMOVE:			// �}�E�X��������
		if (MouseButtonFlg) {
			mx =  (short)LOWORD(lParam) - AXIS_X_OFFSET;
			my = ((short)HIWORD(lParam) - AXIS_Y_OFFSET) * -1;		
			g_Face[PointMoveFlg].p0.x = mx;
			g_Face[PointMoveFlg].p0.y = my;
			if (PointMoveFlg == 0) {
				g_Face[POLY_MAX - 1].p1.x = mx;	// �擪�̃|�C���g�Ȃ�I�[�����낦��K�v����
				g_Face[POLY_MAX - 1].p1.y = my;
			} else {
				g_Face[PointMoveFlg - 1].p1.x = mx;
				g_Face[PointMoveFlg - 1].p1.y = my;
			}
			RemakeBSPtree();						// �a�r�o�c���[�č\�z
			InvalidateRect(g_hWndApp, NULL, TRUE);
			return 0;
		}
		break;
	case WM_LBUTTONDOWN:		// �}�E�X���{�^���������ꂽ
		mx =  (short)LOWORD(lParam) - AXIS_X_OFFSET;
		my = ((short)HIWORD(lParam) - AXIS_Y_OFFSET) * -1;		
		PointMoveFlg = -1;
		// ���W���N���b�N�������`�F�b�N���ăt���O���Z�b�g
		for (i = 0; i < POLY_MAX; i++) {
			if (g_Face[i].p0.x - 8 < mx && g_Face[i].p0.x + 8 > mx && 
				g_Face[i].p0.y - 8 < my && g_Face[i].p0.y + 8 > my) {
				PointMoveFlg = i;
				break;
			}
		}
		InvalidateRect(g_hWndApp, NULL, TRUE);
		MouseButtonFlg = true;
		return 0;
	case WM_LBUTTONUP:			// �}�E�X���{�^���������ꂽ
		MouseButtonFlg = false;
		return 0;
	case WM_PAINT:				// �`��
		hdc = BeginPaint(hWnd, &ps);
		PatBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
		DrawGrid();					// �O���b�h��`��
		DrawPolygon();				// ���p�`��`��
		if (g_bOnInfo) DispInfo();	// ���\��
		BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if (g_BSPnode) DeleteBSPtree(g_BSPnode);	// �a�r�o�c���[���폜
		DeleteObject(g_hBitmap);
		DeleteDC(g_hMemDC);
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//---------------------------------------------------------------------------------------
// �a�r�o�c���[�č\�z���W���[��
//---------------------------------------------------------------------------------------
void RemakeBSPtree()
{
	int		i;

	if (g_BSPnode) DeleteBSPtree(g_BSPnode);		// �a�r�o�c���[���폜

	g_BSPnode = new BSPnode;						// ���[�g�m�[�h�𐶐�
	ZeroMemory(g_BSPnode, sizeof(BSPnode));			// �����o��S�N���A

	for (i = 0; i < POLY_MAX * POLY_MAX; i++) {
		g_FaceIndex[i] = -1;						// ���g�p�t���O����������S�ĂɃZ�b�g
	}
	for (i = 0; i < POLY_MAX; i++) {
		g_FaceIndex[i] = i;							// �g�p���t���O�������|���S���ɑ΂��ăZ�b�g
	}
	CalcNormal();									// �S�Ă̖ʂ̖@���x�N�g�����v�Z

	MakeBSPtree(g_BSPnode, g_FaceIndex, POLY_MAX);	// �a�r�o�c���[�\�z
	CalcNormal();									// �@���x�N�g�����Čv�Z
}

//---------------------------------------------------------------------------------------
// �O���b�h�\�����W���[��
//---------------------------------------------------------------------------------------
void DrawGrid()
{
	HPEN	PenGrid0, PenGrid1;		// �O���b�h�̃y�� 
	PenGrid0 = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	PenGrid1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	// �g��`��
	int		x, y;
	SelectObject(g_hMemDC, PenGrid0);
	for (x = 0; x < SCREEN_WIDTH; x += 20) {
		MoveToEx(g_hMemDC, x, 0, NULL);
		LineTo(g_hMemDC, x, SCREEN_HEIGHT);
	}
	for (y = 0; y < SCREEN_HEIGHT; y += 20) {
		MoveToEx(g_hMemDC, 0, y, NULL);
		LineTo(g_hMemDC, SCREEN_WIDTH, y);
	}
	SelectObject(g_hMemDC, PenGrid1);
	MoveToEx(g_hMemDC, 0, AXIS_Y_OFFSET, NULL);
	LineTo(g_hMemDC, SCREEN_WIDTH, AXIS_Y_OFFSET);
	MoveToEx(g_hMemDC, AXIS_X_OFFSET, 0, NULL);
	LineTo(g_hMemDC, AXIS_X_OFFSET, SCREEN_HEIGHT);

	DeleteObject(PenGrid1);
	DeleteObject(PenGrid0);
}

//---------------------------------------------------------------------------------------
// ���p�`�`�惂�W���[��
//---------------------------------------------------------------------------------------
void DrawPolygon()
{
	TCHAR	str[256];
	HPEN	PenBand, oldpen;
	int		px0, py0, px1, py1;
	int		nx0, ny0, nx1, ny1;
	int		len;

	PenBand = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	oldpen   = (HPEN)SelectObject(g_hMemDC, PenBand);

	for (int i = 0; i < POLY_MAX * POLY_MAX; i++) {
		if (g_FaceIndex[i] > -1) {
			// �ӂ�`��
			px0 = AXIS_X_OFFSET + g_Face[i].p0.x;
			py0 = AXIS_Y_OFFSET - g_Face[i].p0.y;
			px1 = AXIS_X_OFFSET + g_Face[i].p1.x;
			py1 = AXIS_Y_OFFSET - g_Face[i].p1.y;
			MoveToEx(g_hMemDC, px0, py0, NULL);
			LineTo(g_hMemDC, px1, py1);
			// �@����`��
			nx0 = (px0 + px1) / 2;
			ny0 = (py0 + py1) / 2;
			nx1 = nx0 + (int)(g_Face[i].nx * 50);
			ny1 = ny0 - (int)(g_Face[i].ny * 50);
			MoveToEx(g_hMemDC, nx0, ny0, NULL);
			LineTo(g_hMemDC, nx1, ny1);
			// �C���f�b�N�X��`��
			len = _stprintf(str, _T("%2d"), i);
			TextOut(g_hMemDC, (px1 + px0) / 2, (py1 + py0) / 2, str, len);
		}
	}

	SelectObject(g_hMemDC, oldpen);
	DeleteObject(PenBand);
}

//---------------------------------------------------------------------------------------
// ���\�����W���[��
//---------------------------------------------------------------------------------------
void DispInfo()
{
	g_DispTreeX = 0;
	g_DispTreeY = 0;
	DispBSPtree(g_BSPnode, 0);			// �a�r�o�c���[��`��
	DispFace();							// �ʏ���`��
}

//---------------------------------------------------------------------------------------
// �@���v�Z���W���[��
//---------------------------------------------------------------------------------------
void CalcNormal()
{
	int vx, vy, vz;
	int wx, wy, wz;
	float mg;
	for (int i = 0; i < POLY_MAX * POLY_MAX; i++) {
		if (g_FaceIndex[i] > -1) {
			// �@�����v�Z�i�R�c�x�N�g�������ĊO�ς��狁�߂�j
			vx = g_Face[g_FaceIndex[i]].p1.x - g_Face[g_FaceIndex[i]].p0.x;
			vy = g_Face[g_FaceIndex[i]].p1.y - g_Face[g_FaceIndex[i]].p0.y;
			vz = 0;
			wx = 0;
			wy = 0;
			wz = 1;
			g_Face[g_FaceIndex[i]].nx = (float)(vy * wz - vz * wy);
			g_Face[g_FaceIndex[i]].ny = (float)(vz * wx - vx * wz);
			mg = sqrtf(g_Face[g_FaceIndex[i]].nx * g_Face[g_FaceIndex[i]].nx + g_Face[g_FaceIndex[i]].ny * g_Face[g_FaceIndex[i]].ny);
			g_Face[g_FaceIndex[i]].nx /= mg;
			g_Face[g_FaceIndex[i]].ny /= mg;
		}
	}
}

//---------------------------------------------------------------------------------------
// �������m�̕\���ʒu���胂�W���[��
//
// in  : FACE *face0 ���肷��m�[�h
//       FACE *face1 ����̃x�[�X�ƂȂ�m�[�h�i���̃m�[�h�̕\���𔻒�j
// out : int 0 = face0 �� face1 �̕\��
//           1 = face0 �� face1 �̗���
//           2 = face0 �� face1 �ƌ���
//
//---------------------------------------------------------------------------------------
int CheckFrontBack(FACE *face0, FACE *face1)
{
	int	ans0, ans1;
	ans0 = (int)((face0->p0.x - face1->p0.x) * face1->nx + (face0->p0.y - face1->p0.y) * face1->ny); 
	ans1 = (int)((face0->p1.x - face1->p0.x) * face1->nx + (face0->p1.y - face1->p0.y) * face1->ny); 
	if((ans0 * ans1) < 0) return 2;		// �������قȂ�̂Ō���
	if(ans0 > 0 || ans1 > 0) return 0;	// �\��
	else return 1;						// ����
}
	
//---------------------------------------------------------------------------------------
// �a�r�o�c���[�\�z
//
// in  : BSPnode *node �Ώۃm�[�h
//       int *face_list �m�[�h�Ɋ܂܂��ʔԍ��z��
//       int face_num �m�[�h�Ɋ܂܂��ʂ̐�
//---------------------------------------------------------------------------------------
void MakeBSPtree(BSPnode *node, int *face_list, int face_num)
{
	//==========================================================================
	//
	//�@�@�����ɂa�r�o�c���[�\�z�v���O����������
	//
	//==========================================================================
}

//---------------------------------------------------------------------------------------
// �a�r�o�c���[�폜
//---------------------------------------------------------------------------------------
void DeleteBSPtree(BSPnode *node)
{
	if (node->front != NULL) DeleteBSPtree(node->front);	// �\���Ƀm�[�h������΂������č폜
	if (node->back  != NULL) DeleteBSPtree(node->back );	// �����Ƀm�[�h������΂������č폜
	// �ʃ��X�g�����������
	if (node->front_face) delete[] node->front_face;
	if (node->back_face ) delete[] node->back_face;
	// �m�[�h���g�����
	delete node;
}

//---------------------------------------------------------------------------------------
// �a�r�o�c���[�\��
//---------------------------------------------------------------------------------------
void DispBSPtree(BSPnode *node, int indent)
{
	TCHAR	str[256];
	int		len;

	// �m�[�h�̖ʔԍ���`��
	len = _stprintf(str, _T("[%2d] F%d, B%d"), node->face, node->front_num, node->back_num);
	TextOut(g_hMemDC, g_DispTreeX + indent, g_DispTreeY, str, len);
	g_DispTreeY += 20;

	// �\��
	if (node->front != NULL) {
		// �\���Ƀm�[�h�����݂��Ă���̂ł���ɂ�����
		DispBSPtree(node->front, indent + 20);
	} else {
		// ����ȏ�\���Ƀm�[�h�����݂��Ȃ��̂ŏI�[�\�����s��
		len = _stprintf(str, _T("( F)"));
		TextOut(g_hMemDC, g_DispTreeX + indent + 20, g_DispTreeY, str, len);
		g_DispTreeY += 20;
	}
	if (node->back  != NULL) {
		// �����Ƀm�[�h�����݂��Ă���̂ł���ɂ�����
		DispBSPtree(node->back , indent + 20);
	} else {
		// ����ȏ㗠���Ƀm�[�h�����݂��Ȃ��̂ŏI�[�\�����s��
		len = _stprintf(str, _T("( B)"));
		TextOut(g_hMemDC, g_DispTreeX + indent + 20, g_DispTreeY, str, len);
		g_DispTreeY += 20;
	}
}
	
//---------------------------------------------------------------------------------------
// �ʏ��\��
//---------------------------------------------------------------------------------------
void DispFace()
{
	TCHAR	str[256];
	int		py, len;

	py = 0;
	for (int i = 0; i < POLY_MAX * POLY_MAX; i++) {
		if (g_FaceIndex[i] > -1) {
			// �ʏ���`��
			len = _stprintf(str, _T("[%2d] (%4d, %4d)-(%4d, %4d) N(%4.1f, %4.1f)"),
				i, g_Face[i].p0.x, g_Face[i].p0.y, g_Face[i].p1.x, g_Face[i].p1.y,
				g_Face[i].nx, g_Face[i].ny);
			TextOut(g_hMemDC, 450, py, str, len);
			py += 20;		// �P�s����
		}
	}
}

//=======================================================================================
//	end
//=======================================================================================
