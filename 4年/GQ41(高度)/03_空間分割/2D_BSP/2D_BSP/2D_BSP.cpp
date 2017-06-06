//=======================================================================================
//
//	  [ 2D_BSP ] : Binary Space Partitioning
//
//=======================================================================================

//----- インクルードファイル
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>

//----- 定数定義
#define SCREEN_WIDTH			800				// スクリーン　幅
#define SCREEN_HEIGHT			600				// スクリーン　高さ
#define AXIS_X_OFFSET			SCREEN_WIDTH/2	// Ｘ座標オフセット
#define AXIS_Y_OFFSET			SCREEN_HEIGHT/2	// Ｙ座標オフセット

POINT	poly_vertex[] = {			// 頂点座標
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
#define POLY_MAX	8				// 面数

//----- 構造体定義
typedef struct {
	POINT	p0, p1;			// 座標
	float	nx, ny;			// 法線ベクトル
} FACE;

struct BSPnode {
	BSPnode	*front;			// 表側、裏側ノードへのポインタ
	BSPnode	*back;			// 表側、裏側ノードへのポインタ
	int		face;			// 分割面
	int		*front_face;	// 表側面リストへのポインタ
	int		*back_face;		// 裏側面リストへのポインタ
	int		front_num;		// 表側の面数
	int		back_num;		// 裏側の面数
};

//----- グローバル変数
const TCHAR szClassName[] = _T("2D_BSP");
const TCHAR szAppName[]   = _T("[ 2D_BSP ] Binary Space Partitioning");

FACE		g_Face[POLY_MAX * POLY_MAX];		// 面情報
int			g_FaceIndex[POLY_MAX * POLY_MAX];	// 面使用中情報
BSPnode		*g_BSPnode;							// ルートノード用ポインタ

HWND		g_hWndApp;					// ウィンドウハンドル
HDC			g_hMemDC;					// 裏画面ＤＣ
HBITMAP		g_hBitmap;					// 裏画面ビットマップ
bool		g_bOnInfo;					// ベクトル・数値情報表示スイッチ

int			g_DispTreeX;				// ＢＳＰツリー表示Ｘ座標
int			g_DispTreeY;				// ＢＳＰツリー表示Ｙ座標

//----- プロトタイプ宣言
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
// メイン
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR args, int cmdShow)
{
	MSG		msg;

	// 変数初期化
	g_bOnInfo = true;			// 情報表示スイッチをＯＦＦ
	g_BSPnode = NULL;

	// ウィンドウクラスを登録
	WNDCLASS wndClass = {
		0, WndProc, 0, 0, hInst,
		LoadIcon(hInst, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		0, NULL, szClassName
	};
	if (RegisterClass(&wndClass) == 0) return false;

	// ウインドウを作成
	g_hWndApp = CreateWindow(
		szClassName, szAppName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH  + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL, NULL, hInst, NULL);
	if (!g_hWndApp) return false;
	ShowWindow(g_hWndApp, cmdShow);
	UpdateWindow(g_hWndApp);

	// メインループ
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

//-----------------------------------------------------------------------------
// メッセージ処理
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
		g_hMemDC = CreateCompatibleDC(hdc);		// 裏画面の作成
		g_hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
		SelectObject(g_hMemDC, g_hBitmap);
		SetBkMode(g_hMemDC, TRANSPARENT);
		SetTextColor(g_hMemDC, RGB(0, 0, 0));
		ReleaseDC(hWnd, hdc);

		// 各種初期値設定
		MouseButtonFlg = false;
		PointMoveFlg = -1;
		for (i = 0; i < POLY_MAX; i++) {
			g_Face[i].p0.x = poly_vertex[i  ].x;
			g_Face[i].p0.y = poly_vertex[i  ].y;
			g_Face[i].p1.x = poly_vertex[i+1].x;
			g_Face[i].p1.y = poly_vertex[i+1].y;
		}
		RemakeBSPtree();						// ＢＳＰツリー再構築
		InvalidateRect(g_hWndApp, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:			// キーが押された
		switch (wParam) {
		case VK_ESCAPE:	DestroyWindow(hWnd);	return 0;	// 終了
		case 'I':				// 情報表示スイッチの切り替え
			g_bOnInfo = !g_bOnInfo;
			InvalidateRect(g_hWndApp, NULL, TRUE);
			return 0;
		}
		break;
	case WM_MOUSEMOVE:			// マウスが動いた
		if (MouseButtonFlg) {
			mx =  (short)LOWORD(lParam) - AXIS_X_OFFSET;
			my = ((short)HIWORD(lParam) - AXIS_Y_OFFSET) * -1;		
			g_Face[PointMoveFlg].p0.x = mx;
			g_Face[PointMoveFlg].p0.y = my;
			if (PointMoveFlg == 0) {
				g_Face[POLY_MAX - 1].p1.x = mx;	// 先頭のポイントなら終端もそろえる必要あり
				g_Face[POLY_MAX - 1].p1.y = my;
			} else {
				g_Face[PointMoveFlg - 1].p1.x = mx;
				g_Face[PointMoveFlg - 1].p1.y = my;
			}
			RemakeBSPtree();						// ＢＳＰツリー再構築
			InvalidateRect(g_hWndApp, NULL, TRUE);
			return 0;
		}
		break;
	case WM_LBUTTONDOWN:		// マウス左ボタンが押された
		mx =  (short)LOWORD(lParam) - AXIS_X_OFFSET;
		my = ((short)HIWORD(lParam) - AXIS_Y_OFFSET) * -1;		
		PointMoveFlg = -1;
		// 座標をクリックしたかチェックしてフラグをセット
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
	case WM_LBUTTONUP:			// マウス左ボタンが離された
		MouseButtonFlg = false;
		return 0;
	case WM_PAINT:				// 描画
		hdc = BeginPaint(hWnd, &ps);
		PatBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
		DrawGrid();					// グリッドを描画
		DrawPolygon();				// 多角形を描画
		if (g_bOnInfo) DispInfo();	// 情報表示
		BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if (g_BSPnode) DeleteBSPtree(g_BSPnode);	// ＢＳＰツリーを削除
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
// ＢＳＰツリー再構築モジュール
//---------------------------------------------------------------------------------------
void RemakeBSPtree()
{
	int		i;

	if (g_BSPnode) DeleteBSPtree(g_BSPnode);		// ＢＳＰツリーを削除

	g_BSPnode = new BSPnode;						// ルートノードを生成
	ZeroMemory(g_BSPnode, sizeof(BSPnode));			// メンバを全クリア

	for (i = 0; i < POLY_MAX * POLY_MAX; i++) {
		g_FaceIndex[i] = -1;						// 未使用フラグをいったん全てにセット
	}
	for (i = 0; i < POLY_MAX; i++) {
		g_FaceIndex[i] = i;							// 使用中フラグを初期ポリゴンに対してセット
	}
	CalcNormal();									// 全ての面の法線ベクトルを計算

	MakeBSPtree(g_BSPnode, g_FaceIndex, POLY_MAX);	// ＢＳＰツリー構築
	CalcNormal();									// 法線ベクトルを再計算
}

//---------------------------------------------------------------------------------------
// グリッド表示モジュール
//---------------------------------------------------------------------------------------
void DrawGrid()
{
	HPEN	PenGrid0, PenGrid1;		// グリッドのペン 
	PenGrid0 = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	PenGrid1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	// 枠を描画
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
// 多角形描画モジュール
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
			// 辺を描画
			px0 = AXIS_X_OFFSET + g_Face[i].p0.x;
			py0 = AXIS_Y_OFFSET - g_Face[i].p0.y;
			px1 = AXIS_X_OFFSET + g_Face[i].p1.x;
			py1 = AXIS_Y_OFFSET - g_Face[i].p1.y;
			MoveToEx(g_hMemDC, px0, py0, NULL);
			LineTo(g_hMemDC, px1, py1);
			// 法線を描画
			nx0 = (px0 + px1) / 2;
			ny0 = (py0 + py1) / 2;
			nx1 = nx0 + (int)(g_Face[i].nx * 50);
			ny1 = ny0 - (int)(g_Face[i].ny * 50);
			MoveToEx(g_hMemDC, nx0, ny0, NULL);
			LineTo(g_hMemDC, nx1, ny1);
			// インデックスを描画
			len = _stprintf(str, _T("%2d"), i);
			TextOut(g_hMemDC, (px1 + px0) / 2, (py1 + py0) / 2, str, len);
		}
	}

	SelectObject(g_hMemDC, oldpen);
	DeleteObject(PenBand);
}

//---------------------------------------------------------------------------------------
// 情報表示モジュール
//---------------------------------------------------------------------------------------
void DispInfo()
{
	g_DispTreeX = 0;
	g_DispTreeY = 0;
	DispBSPtree(g_BSPnode, 0);			// ＢＳＰツリーを描画
	DispFace();							// 面情報を描画
}

//---------------------------------------------------------------------------------------
// 法線計算モジュール
//---------------------------------------------------------------------------------------
void CalcNormal()
{
	int vx, vy, vz;
	int wx, wy, wz;
	float mg;
	for (int i = 0; i < POLY_MAX * POLY_MAX; i++) {
		if (g_FaceIndex[i] > -1) {
			// 法線を計算（３Ｄベクトル化して外積から求める）
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
// 線分同士の表裏位置判定モジュール
//
// in  : FACE *face0 判定するノード
//       FACE *face1 判定のベースとなるノード（このノードの表裏を判定）
// out : int 0 = face0 は face1 の表側
//           1 = face0 は face1 の裏側
//           2 = face0 は face1 と交差
//
//---------------------------------------------------------------------------------------
int CheckFrontBack(FACE *face0, FACE *face1)
{
	int	ans0, ans1;
	ans0 = (int)((face0->p0.x - face1->p0.x) * face1->nx + (face0->p0.y - face1->p0.y) * face1->ny); 
	ans1 = (int)((face0->p1.x - face1->p0.x) * face1->nx + (face0->p1.y - face1->p0.y) * face1->ny); 
	if((ans0 * ans1) < 0) return 2;		// 符号が異なるので交差
	if(ans0 > 0 || ans1 > 0) return 0;	// 表側
	else return 1;						// 裏側
}
	
//---------------------------------------------------------------------------------------
// ＢＳＰツリー構築
//
// in  : BSPnode *node 対象ノード
//       int *face_list ノードに含まれる面番号配列
//       int face_num ノードに含まれる面の数
//---------------------------------------------------------------------------------------
void MakeBSPtree(BSPnode *node, int *face_list, int face_num)
{
	//==========================================================================
	//
	//　　ここにＢＳＰツリー構築プログラムを入れる
	//
	//==========================================================================
}

//---------------------------------------------------------------------------------------
// ＢＳＰツリー削除
//---------------------------------------------------------------------------------------
void DeleteBSPtree(BSPnode *node)
{
	if (node->front != NULL) DeleteBSPtree(node->front);	// 表側にノードがあればもぐって削除
	if (node->back  != NULL) DeleteBSPtree(node->back );	// 裏側にノードがあればもぐって削除
	// 面リストメモリを解放
	if (node->front_face) delete[] node->front_face;
	if (node->back_face ) delete[] node->back_face;
	// ノード自身を解放
	delete node;
}

//---------------------------------------------------------------------------------------
// ＢＳＰツリー表示
//---------------------------------------------------------------------------------------
void DispBSPtree(BSPnode *node, int indent)
{
	TCHAR	str[256];
	int		len;

	// ノードの面番号を描画
	len = _stprintf(str, _T("[%2d] F%d, B%d"), node->face, node->front_num, node->back_num);
	TextOut(g_hMemDC, g_DispTreeX + indent, g_DispTreeY, str, len);
	g_DispTreeY += 20;

	// 表示
	if (node->front != NULL) {
		// 表側にノードが存在しているのでさらにもぐる
		DispBSPtree(node->front, indent + 20);
	} else {
		// これ以上表側にノードが存在しないので終端表示を行う
		len = _stprintf(str, _T("( F)"));
		TextOut(g_hMemDC, g_DispTreeX + indent + 20, g_DispTreeY, str, len);
		g_DispTreeY += 20;
	}
	if (node->back  != NULL) {
		// 裏側にノードが存在しているのでさらにもぐる
		DispBSPtree(node->back , indent + 20);
	} else {
		// これ以上裏側にノードが存在しないので終端表示を行う
		len = _stprintf(str, _T("( B)"));
		TextOut(g_hMemDC, g_DispTreeX + indent + 20, g_DispTreeY, str, len);
		g_DispTreeY += 20;
	}
}
	
//---------------------------------------------------------------------------------------
// 面情報表示
//---------------------------------------------------------------------------------------
void DispFace()
{
	TCHAR	str[256];
	int		py, len;

	py = 0;
	for (int i = 0; i < POLY_MAX * POLY_MAX; i++) {
		if (g_FaceIndex[i] > -1) {
			// 面情報を描画
			len = _stprintf(str, _T("[%2d] (%4d, %4d)-(%4d, %4d) N(%4.1f, %4.1f)"),
				i, g_Face[i].p0.x, g_Face[i].p0.y, g_Face[i].p1.x, g_Face[i].p1.y,
				g_Face[i].nx, g_Face[i].ny);
			TextOut(g_hMemDC, 450, py, str, len);
			py += 20;		// １行下へ
		}
	}
}

//=======================================================================================
//	end
//=======================================================================================
