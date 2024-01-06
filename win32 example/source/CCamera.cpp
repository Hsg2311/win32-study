#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera( )
	: m_pTargetObj{ nullptr }
	, m_Time{ 1.f }
	, m_Speed{ 0.f }
	, m_AccTime{ 0.f }
{

}

CCamera::~CCamera( )
{

}

void CCamera::update( )
{
	if ( m_pTargetObj )
	{
		if ( m_pTargetObj->IsDead( ) )
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_LookAt = m_pTargetObj->GetPos( );
		}
	}

	if ( KEY_HOLD( KEY::W ) )
	{
		m_LookAt.y -= 300.f * fDT;
	}
	if ( KEY_HOLD( KEY::S ) )
	{
		m_LookAt.y += 300.f * fDT;
	}
	if ( KEY_HOLD( KEY::A ) )
	{
		m_LookAt.x -= 300.f * fDT;
	}
	if ( KEY_HOLD( KEY::D ) )
	{
		m_LookAt.x += 300.f * fDT;
	}

	// ȭ�� �߾� ��ǥ�� ī�޶� LookAt ��ǥ ���� ���̰� ���
	CalcDiff( );
}

void CCamera::CalcDiff( )
{
	// prevLookAt�� LookAt�� ���̰��� �����ؼ� curLookAt�� ���Ѵ�.

	m_AccTime += fDT;

	if ( m_Time <= m_AccTime )
	{
		m_curLookAt = m_LookAt;
	}
	else
	{
		Vec2 LookDir = m_LookAt - m_prevLookAt;	// prevLookAt���� LookAt���� ���� �� ���� ���Ͱ� ����
		m_curLookAt = m_prevLookAt + LookDir.Nomalize( ) * m_Speed * fDT;
	}


	Vec2 resolution = CCore::GetInst( )->GetResolution( );
	Vec2 center = resolution / 2.f;

	m_Diff = m_curLookAt - center;

	m_prevLookAt = m_curLookAt;
}