#include "ObjectBase.h"



CObjectBase::CObjectBase() :
	m_speed(0.0f, 0.0f, 0.0f),
	m_accel(0.0f, 0.0f, 0.0f),
	m_fRadius(0.5f),
	m_center(0.0f, 0.0f, 0.0f),
	m_bbox(0.5f, 0.5f, 0.5f),
	m_fHP(0.0f){
}


CObjectBase::~CObjectBase() {
}

void CObjectBase::Init() {

}

void CObjectBase::Update() {

}

void CObjectBase::PostUpdate() {
}

void CObjectBase::PreDraw() {
}

void CObjectBase::Draw(CShader* pShader) {

}

void CObjectBase::DrawAlpha() {

}

void CObjectBase::Fin() {

}
