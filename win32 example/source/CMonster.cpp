#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster( )
	: m_vMonsterPos{ 0.f, 0.f }
	, m_fSpeed{ 200.f }
	, m_fMaxDistance{ 50.f }
	, m_iDir{ 1 }
{
	CreateCollider( );
	
	GetCollider( )->setScale( Vec2{ 40.f,40.f } );
}

CMonster::~CMonster( )
{

}

void CMonster::update( )
{
	return;
	Vec2 vMonCurPos = GetPos( );

	// 진행 방향으로 초당 m_fSpeed만큼 이동
	vMonCurPos.x += fDT * m_fSpeed * m_iDir;

	// 배회 거리 기준량을 넘어섰는지 확인
	float fDiff = abs( m_vMonsterPos.x - vMonCurPos.x ) - m_fMaxDistance;
	if ( 0.f < fDiff )
	{
		// 방향 변경
		m_iDir *= -1;
		vMonCurPos.x += fDiff * m_iDir;
	}

	SetPos( vMonCurPos );
}

void CMonster::OnCollisionEnter( CCollider* other )
{
	CObject* pOtherObj = other->GetObj( );

	if ( pOtherObj->GetName( ) == L"Projectile_P" )
	{
		DeleteObject( this );
	}
}