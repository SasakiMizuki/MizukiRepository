//=======================================================================================
//
//	  [ 2D_CONCAVITY ] : 凹多角形と点との衝突判定
//
//=======================================================================================

//----- インクルードファイル
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <tchar.h>
#include <windows.h>
#include <stdio.h>

//----- 定数定義
#define SCREEN_WIDTH			800				// スクリーン　幅
#define SCREEN_HEIGHT			600				// スクリーン　高さ
#define AXIS_X_OFFSET			SCREEN_WIDTH/2	// Ｘ座標オフセット
#define AXIS_Y_OFFSET			SCREEN_HEIGHT/2	// Ｙ座標オフセット

POINT	poly_vertex[] = {
	{   0, 100},
	{ 200, 200},
	{ 200,   0},
	{   0,-200},
	{-200,   0},
	{-200, 200},

	{   0, 100},
};
#define POLY_MAX 6

//----- グローバル変数
const TCHAR szClassName[] = _T("2DConcavity");
const TCHAR szAppName[]   = _T("[ 2D_CONCAVITY ] 凹多角形と点との衝突判定");

POINT		g_Point;
int			g_PointMoveFlg;
int			g_HitCount;
bool		g_bOnHit;					// ヒット確認フラグ
int			g_Vx, g_Vy;
int			g_PolyHit[POLY_MAX];

HWND		g_hWndApp;					// ウィンドウハンドル
int			g_iClientWidth;				// クライアント領域サイズ
int			g_iClientHeight;			// クライアント領域サイズ
RECT		g_ClientRect;				// クライアント領域
HDC			g_hMemDC;					// 裏画面ＤＣ
HBITMAP		g_hBitmap;					// 裏画面ビットマップ
bool		g_bOnInfo;					// ベクトル・数値情報表示スイッチ

//----- プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void MainModule();
bool HitCheck();
void DrawGrid();
void DrawPolygon();
void DrawPoint();
void DispInfo();

//---------------------------------------------------------------------------------------
// メイン
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR args, int cmdShow)
{
	MSG			msg;

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

	// 変数初期化
	g_bOnInfo = true;			// 情報表示スイッチをＯＦＦ
	g_bOnHit  = false;			// ヒットしていない
	g_PointMoveFlg = -1;

	g_Point.x = 300;
	g_Point.y = 200;
	for (int i = 0; i < POLY_MAX; i++) g_PolyHit[i] = 0;
	g_HitCount = HitCheck();		// 衝突判定
	InvalidateRect(g_hWndApp, NULL, true);

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

	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);
		g_hMemDC = CreateCompatibleDC(hdc);		// 裏画面の作成
		g_hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
		SelectObject(g_hMemDC, g_hBitmap);
		SetBkMode(g_hMemDC, TRANSPARENT);
		SetTextColor(g_hMemDC, RGB(0, 0, 0));
		ReleaseDC(hWnd, hdc);
		MouseButtonFlg = false;
		break;
	case WM_KEYDOWN:			// キーが押された
		switch (wParam) {
		case VK_ESCAPE:	DestroyWindow(hWnd);	return 0;	// 終了
		case 'I':		g_bOnInfo = !g_bOnInfo;	return 0;	// 情報表示スイッチの切り替え
		}
		break;
	case WM_MOUSEMOVE:			// マウスが動いた
		if (MouseButtonFlg == true) {
			mx =  LOWORD(lParam) - AXIS_X_OFFSET;
			my = (HIWORD(lParam) - AXIS_Y_OFFSET) * -1;		
			if (g_PointMoveFlg != -1) {
				poly_vertex[g_PointMoveFlg].x = mx;
				poly_vertex[g_PointMoveFlg].y = my;
				if (g_PointMoveFlg == 0) {
					poly_vertex[POLY_MAX].x = mx;	// 先頭のポイントなら終端もそろえる必要あり
					poly_vertex[POLY_MAX].y = my;
				}
			} else {
				g_Point.x = mx;
				g_Point.y = my;
			}
			InvalidateRect(g_hWndApp, NULL, TRUE);
			g_bOnHit = HitCheck();		// 衝突判定
		}
		break;
	case WM_LBUTTONDOWN:		// マウス左ボタンが押された
		mx =  (short)LOWORD(lParam) - AXIS_X_OFFSET;
		my = ((short)HIWORD(lParam) - AXIS_Y_OFFSET) * -1;		
		g_PointMoveFlg = -1;
		for (i = 0; i < POLY_MAX; i++) {
			if (poly_vertex[i].x - 4 < mx && poly_vertex[i].x + 4 > mx && 
				poly_vertex[i].y - 4 < my && poly_vertex[i].y + 4 > my) {
				g_PointMoveFlg = i;
			}
		}
		if (g_PointMoveFlg == -1) {
			g_Point.x = mx;
			g_Point.y = my;
		}
		InvalidateRect(g_hWndApp, NULL, TRUE);
		g_bOnHit = HitCheck();		// 衝突判定
		MouseButtonFlg = true;
		break;
	case WM_LBUTTONUP:			// マウス左ボタンが離された
		MouseButtonFlg = false;
		break;
	case WM_PAINT:				// 描画
		hdc = BeginPaint(hWnd, &ps);
		PatBlt(g_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
		DrawGrid();					// グリッドを描画
		DrawPolygon();				// 多角形を描画
		DrawPoint();				// 直線を描画
		if (g_bOnInfo) DispInfo();	// 情報表示
		BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteObject(g_hBitmap);
		DeleteDC(g_hMemDC);
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//---------------------------------------------------------------------------------------
// 衝突判定チェックモジュール
// in  : ---
// out : bool TRUE = ヒットした , FALSE = ヒットしなかった
//---------------------------------------------------------------------------------------
bool HitCheck()
{
	/*************************************************************************

	ここに衝突判定のプログラムを追加する

	・凹多角形の各辺とポイントから水平に伸ばしたラインとの交点を求める
	・すべての辺とのチェックが終了した後、交点の合計数が奇数なら
	　ヒット確認フラグを立てる

	（補足）
	・ヒットしたら TRUE 、ヒットしなかったら FALSE でリターンするように

	*************************************************************************/
	g_HitCount = 0;
	for (int i = 0; i < POLY_MAX; i++) {
		g_PolyHit[i] = 0;
		if (poly_vertex[i].y == poly_vertex[i + 1].y) {
			continue;
		}
		if (!(g_Point.y < poly_vertex[i].y && g_Point.y >= poly_vertex[i + 1].y) &&
			!(g_Point.y > poly_vertex[i].y && g_Point.y <= poly_vertex[i + 1].y)) {
			continue;
		}
		float t = ((poly_vertex[i + 1].x - poly_vertex[i].x)*(g_Point.y - poly_vertex[i].y))
			/ (poly_vertex[i + 1].y - poly_vertex[i].y) - (g_Point.x - poly_vertex[i].x);
		if (t > 0) {
			g_HitCount ++;
			g_PolyHit[i] = 1;
		}
	}

	if (g_HitCount % 2)
		return TRUE;
	return FALSE;		// 仮
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
	TCHAR		 str[256];
	LOGBRUSH	br;
	HPEN		PenBand, oldpen;
	HBRUSH		brush, oldbrush;
	int			i, len;

	br.lbStyle = BS_SOLID;
	br.lbColor = (g_bOnHit)? RGB(255, 128, 128): RGB(0, 255, 255);

	PenBand = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	brush = CreateBrushIndirect(&br);
	oldpen   = (HPEN)SelectObject(g_hMemDC, PenBand);
	oldbrush = (HBRUSH)SelectObject(g_hMemDC, brush);

	POINT poly[POLY_MAX+1];
	for (i = 0; i <= POLY_MAX; i++) {
		poly[i].x = AXIS_X_OFFSET + poly_vertex[i].x;
		poly[i].y = AXIS_Y_OFFSET - poly_vertex[i].y;
	}
	Polygon(g_hMemDC, &poly[0], POLY_MAX);

	for (i = 0; i < POLY_MAX; i++) {
		len = _stprintf(str, _T("%2d"), i);
		TextOut(g_hMemDC, (poly[i+1].x + poly[i].x) / 2, (poly[i+1].y + poly[i].y) / 2, str, len);
	}

	SelectObject(g_hMemDC, oldpen  );
	SelectObject(g_hMemDC, oldbrush);
	DeleteObject(PenBand);
	DeleteObject(brush);
}

//---------------------------------------------------------------------------------------
// ポイント描画モジュール
//---------------------------------------------------------------------------------------
void DrawPoint()
{
	HPEN	PenBand;
	PenBand = CreatePen(PS_SOLID, 5, RGB(255, 0, 255));
	SelectObject(g_hMemDC, PenBand);

	Rectangle(g_hMemDC, AXIS_X_OFFSET + g_Point.x - 3, AXIS_Y_OFFSET - g_Point.y - 3,
						AXIS_X_OFFSET + g_Point.x + 3, AXIS_Y_OFFSET - g_Point.y + 3);

	DeleteObject(PenBand);
}

//---------------------------------------------------------------------------------------
// 情報表示モジュール
//---------------------------------------------------------------------------------------
void DispInfo()
{
	TCHAR	str[256];
	int		len;

	len = _stprintf(str, _T("POINT   (%4d,%4d)"), g_Point.x, g_Point.y);
	TextOut(g_hMemDC, 0, 0, str, len);

	len = _stprintf(str, _T("HIT COUNT = %3d"), g_HitCount);
	TextOut(g_hMemDC, 0, 20, str, len);

	for (int i = 0; i < POLY_MAX; i++) {
		len = _stprintf(str, _T("POLY HIT [%2d] = %2d"), i, g_PolyHit[i]);
		TextOut(g_hMemDC, 0, 40 + i * 20, str, len);
	}
}


//=======================================================================================
//	end
//=======================================================================================