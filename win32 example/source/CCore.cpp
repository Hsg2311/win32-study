#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"

CCore::CCore( )
	: m_hWnd{ 0 }
	, m_ptResolution{ 0, 0 }
	, m_hDC{ 0 }
	, m_hBit{ 0 }
	, m_memDC{ 0 }
	, m_arrBrush{ }
	, m_arrPen{ }
{

}

CCore::~CCore( )
{
	ReleaseDC( m_hWnd, m_hDC );

	DeleteDC( m_memDC );
	DeleteObject( m_hBit );

	for ( int i = 0; i < (UINT)PEN_TYPE::EOE; ++i )
	{
		DeleteObject( m_arrPen[ i ] );
	}
}

int CCore::init( HWND _hWnd, POINT _ptResolution )
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도 크기에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect( &rt, WS_OVERLAPPEDWINDOW, true );
	SetWindowPos( m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0 );

	m_hDC = GetDC( m_hWnd );

	// 더블 버퍼링 용도의 비트맵과 DC 생성
	m_hBit = CreateCompatibleBitmap( m_hDC, m_ptResolution.x, m_ptResolution.y );
	m_memDC = CreateCompatibleDC( m_hDC );

	HBITMAP hDefaultBit = (HBITMAP)SelectObject( m_memDC, m_hBit );
	DeleteObject( hDefaultBit );

	// 자주 사용할 펜 및 브러쉬 생성
	CreateBrushPen( );

	// Manager 초기화
	CPathMgr::GetInst( )->init( );
	CTimeMgr::GetInst( )->init( );
	CKeyMgr::GetInst( )->init( );
	CSceneMgr::GetInst( )->init( );

	return S_OK;
}

void CCore::progress( )
{
	// ==============
	// Manager update
	// ==============
	CTimeMgr::GetInst( )->update( );
	CKeyMgr::GetInst( )->update( );
	CCamera::GetInst( )->update( );
	
	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst( )->update( );

	// Collsion Handling
	CCollisionMgr::GetInst( )->update( );

	// ==========
	// Rendering
	// ==========
	// 화면 Clear
	Rectangle( m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1 );

	CSceneMgr::GetInst( )->render( m_memDC );

	BitBlt( m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY );

	CTimeMgr::GetInst( )->render( );

	// ===============
	// 이벤트 지연처리
	// ===============
	CEventMgr::GetInst( )->update( );
}

void CCore::CreateBrushPen( )
{
	// hollow brush
	m_arrBrush[ (UINT)BRUSH_TYPE::HOLLOW ] = (HBRUSH)GetStockObject( HOLLOW_BRUSH );

	// red, green, blue pen
	m_arrPen[ (UINT)PEN_TYPE::RED ] = (HPEN)CreatePen( PS_SOLID, 1, RGB( 255, 0, 0 ) );
	m_arrPen[ (UINT)PEN_TYPE::GREEN ] = (HPEN)CreatePen( PS_SOLID, 1, RGB( 0, 255, 0 ) );
	m_arrPen[ (UINT)PEN_TYPE::BLUE ] = (HPEN)CreatePen( PS_SOLID, 1, RGB( 0, 0, 255 ) );
}
