// 3Dオブジェクト クラス実装
#include "C3DObj.h"
#include "SceneBase.h"

// 検索
CObjectBase* C3DObj::Find(UINT uID, CObjectBase* p)
{
	int Number;
	if (p) {
		Number = p->GetNumber();
	} else {
		Number = 0;
	}
	if (m_pScene)
		return m_pScene->Find(uID, Number);
	return NULL;
}

// コンストラクタ
C3DObj::C3DObj(CSceneBase* pScene){
	m_uID = ID_3DOBJ;
	m_dwDamage = 0;
	D3DXMatrixIdentity(&m_world);
	m_pScene = pScene;
	//m_world._41 = position.x;
	//m_world._42 = position.y;
	//m_world._43 = position.z;
}

// デストラクタ
C3DObj::~C3DObj(void)
{
}

// 初期化
void C3DObj::Init()
{
	//m_pScene->Add(this);
}

// 更新
void C3DObj::Update() {
	m_speed += m_accel;
	m_world._41 += m_speed.x;
	m_world._42 += m_speed.y;
	m_world._43 += m_speed.z;
	UpdateDamage();
}

// 更新
void C3DObj::PostUpdate() {

}

void C3DObj::PreDraw() {
}

// 表示
void C3DObj::Draw()
{
}

// 半透明表示
void C3DObj::DrawAlpha()
{
}

// 終了処理
void C3DObj::Fin()
{
	m_pScene->Del(GetNumber());
}

// 座標取得
D3DXVECTOR3 C3DObj::GetPos()
{
	D3DXVECTOR3 pos(m_world._41, m_world._42, m_world._43);
	return pos;
}

// 前方ベクトル取得
D3DXVECTOR3 C3DObj::GetForward()
{
	D3DXVECTOR3 fwd(m_world._31, m_world._32, m_world._33);
	return fwd;
}

// 右ベクトル取得
D3DXVECTOR3 C3DObj::GetRight()
{
	D3DXVECTOR3 right(m_world._11, m_world._12, m_world._13);
	return right;
}

// 上方ベクトル取得
D3DXVECTOR3 C3DObj::GetUp()
{
	D3DXVECTOR3 up(m_world._21, m_world._22, m_world._23);
	return up;
}

// 境界球半径取得
float C3DObj::GetRadius()
{
	return m_fRadius;
}

// 境界球中心座標取得
D3DXVECTOR3& C3DObj::GetCenter()
{
	return m_center;
}

// 境界ボックス取得
D3DXVECTOR3& C3DObj::GetBBox()
{
	return m_bbox;
}

// 境界球同士の当たり判定
bool C3DObj::CollisionBSphere(C3DObj* pObj)
{
	// ワールド空間上の境界球中心座標を求める
	D3DXVECTOR3 vPos1, vPos2;
	D3DXVec3TransformCoord(&vPos1,
		&GetCenter(), &GetWorld());
	D3DXVec3TransformCoord(&vPos2,
		&pObj->GetCenter(), &pObj->GetWorld());

	// 距離の2乗と半径の和の2乗と比較
	float fR = GetRadius() + pObj->GetRadius();
	return D3DXVec3LengthSq(&(vPos2 - vPos1))
		<= fR * fR;
}

// AABB同士の当たり判定
bool C3DObj::CollisionAABB(C3DObj* pObj)
{
	// ワールド空間上の境界ボックス中心座標を求める
	D3DXVECTOR3 vPos1, vPos2;
	D3DXVec3TransformCoord(&vPos1,
		&GetCenter(), &GetWorld());
	D3DXVec3TransformCoord(&vPos2,
		&pObj->GetCenter(), &pObj->GetWorld());
	// AABB同士の当たり判定
	D3DXVECTOR3& vR1 = GetBBox();
	D3DXVECTOR3& vR2 = pObj->GetBBox();
	return (vPos1.x - vR1.x <= vPos2.x + vR2.x) &&
		(vPos2.x - vR2.x <= vPos1.x + vR1.x) &&
		(vPos1.y - vR1.y <= vPos2.y + vR2.y) &&
		(vPos2.y - vR2.y <= vPos1.y + vR1.y) &&
		(vPos1.z - vR1.z <= vPos2.z + vR2.z) &&
		(vPos2.z - vR2.z <= vPos1.z + vR1.z);
}
// OBB同士の当たり判定
bool C3DObj::CollisionOBB(C3DObj* pObj) {
	// ワールドマトリックス取得
	D3DXMATRIX& mW1 = GetWorld();
	D3DXMATRIX& mW2 = pObj->GetWorld();
	// ワールド空間上の境界ボックス中心座標を求める
	D3DXVECTOR3 vPos1, vPos2;
	D3DXVec3TransformCoord(&vPos1, &GetCenter(), &mW1);
	D3DXVec3TransformCoord(&vPos2, &pObj->GetCenter(), &mW2);
	// 中心座標間のベクトルを求める
	D3DXVECTOR3 vD = vPos2 - vPos1;

	// モデル座標軸を求める
	D3DXVECTOR3 vN[6];
	vN[0] = D3DXVECTOR3(mW1._11, mW1._12, mW1._13);
	vN[1] = D3DXVECTOR3(mW1._21, mW1._22, mW1._23);
	vN[2] = D3DXVECTOR3(mW1._31, mW1._32, mW1._33);
	vN[3] = D3DXVECTOR3(mW2._11, mW2._12, mW2._13);
	vN[4] = D3DXVECTOR3(mW2._21, mW2._22, mW2._23);
	vN[5] = D3DXVECTOR3(mW2._31, mW2._32, mW2._33);
	// OBBの大きさ(半分)の長さを掛けたベクトルを求める
	D3DXVECTOR3& vBBox1 = GetBBox();
	D3DXVECTOR3& vBBox2 = pObj->GetBBox();
	D3DXVECTOR3 vL[6];
	vL[0] = vN[0] * vBBox1.x;
	vL[1] = vN[1] * vBBox1.y;
	vL[2] = vN[2] * vBBox1.z;
	vL[3] = vN[3] * vBBox2.x;
	vL[4] = vN[4] * vBBox2.y;
	vL[5] = vN[5] * vBBox2.z;

	// 分離軸候補はモデル座標軸
	float fL, fD;
	for (int i = 0; i < 6; ++i) {
		D3DXVECTOR3& vS = vN[i];// 分離軸候補
								// OBBの影(半分)の合計
		fL = 0.0f;
		for (int j = 0; j < 6; ++j) {
			fL += fabsf(D3DXVec3Dot(&vS, &vL[j]));
		}
		// 影と中心間の距離の比較
		fD = fabsf(D3DXVec3Dot(&vS, &vD));
		if (fL < fD) {
			return false;	// 当たっていない
		}
	}
	// 分離軸候補は2辺から生成
	D3DXVECTOR3 vS;	// 分離軸候補
	for (int i = 0; i < 3; ++i) {
		for (int j = 3; j < 6; ++j) {
			// 分離軸候補を計算
			D3DXVec3Cross(&vS, &vN[i], &vN[j]);
			D3DXVec3Normalize(&vS, &vS);
			// OBBの影(半分)の合計
			fL = 0.0f;
			for (int k = 0; k < 6; ++k) {
				fL += fabsf(D3DXVec3Dot(&vS, &vL[k]));
			}
			// 影と中心間の距離の比較
			fD = fabsf(D3DXVec3Dot(&vS, &vD));
			if (fL < fD) {
				return false;	// 当たっていない
			}
		}
	}
	return true;	// 当たっている
}

// カメラからの距離を比較
int C3DObj::CmpDepth(const void* pLeft, const void* pRight) {
	C3DObj** ppLeft = (C3DObj**)pLeft;
	C3DObj** ppRight = (C3DObj**)pRight;
	// カメラからの距離の降順でソート
	float fDiff = (*ppLeft)->m_fDepth - (*ppRight)->m_fDepth;
	if (fabsf(fDiff) <= FLT_EPSILON) {
		return (*ppRight)->m_synthetic - (*ppLeft)->m_synthetic;
	}
	if ((*ppLeft)->m_fDepth < (*ppRight)->m_fDepth) {
		return 1;
	}
	if ((*ppLeft)->m_fDepth >(*ppRight)->m_fDepth) {
		return -1;
	}
	return 0;
}