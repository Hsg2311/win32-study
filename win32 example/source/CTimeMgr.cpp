#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr( )
	: m_PrevCount{ }
	, m_CurCount{ }
	, m_Frequency{ }
	, m_dDT{ 0. }
	, m_dAcc{ 0. }
	, m_iCallCount{ 0 }
	, m_iFPS{ 0 }
{

}

CTimeMgr::~CTimeMgr( )
{

}

void CTimeMgr::init( )
{
	// 현재 카운트
	QueryPerformanceCounter( &m_PrevCount );

	// 초당 카운트 횟수
	QueryPerformanceFrequency( &m_Frequency );
}

void CTimeMgr::update( )
{
	QueryPerformanceCounter( &m_CurCount );

	m_dDT = ( (double)m_CurCount.QuadPart - (double)m_PrevCount.QuadPart ) / (double)m_Frequency.QuadPart;

	m_PrevCount = m_CurCount;

#ifdef _DEBUG	// 디버그 모드에서 DT 고정
	if ( m_dDT > ( 1. / 60. ) )
		m_dDT = ( 1. / 60. );
#endif
}

void CTimeMgr::render( )
{
	++m_iCallCount;

	m_dAcc += m_dDT;

	if ( m_dAcc >= 1. )
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		WCHAR szBuffer[ 255 ];
		swprintf_s( szBuffer, L"FPS : %d, DT : %lf", m_iFPS, m_dDT );
		SetWindowText( CCore::GetInst( )->GetMainHWND( ), szBuffer );
	}
}
