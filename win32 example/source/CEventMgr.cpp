#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr( )
{

}

CEventMgr::~CEventMgr( )
{

}

void CEventMgr::update( )
{
	// ==================================================
	// ���� �����ӿ��� ����ص� Dead Object���� �����Ѵ�.
	// ==================================================
	for ( size_t i = 0; i < m_vecDead.size( ); ++i )
	{
		delete m_vecDead[ i ];
	}
	m_vecDead.clear( );

	// ==========
	// Event ó��
	// ==========
	for ( size_t i = 0; i < m_vecEvent.size( ); ++i )
	{
		Execute( m_vecEvent[ i ] );
	}
	m_vecEvent.clear( );
}

void CEventMgr::Execute( const tEvent& _event )
{
	switch ( _event.eEvent )
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;

		CSceneMgr::GetInst( )->GetCurScene( )->AddObjcet( pNewObj, eType );
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object�� Dead ���·� ����
		// �������� Object���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_event.lParam;
		pDeadObj->SetDead( );
		m_vecDead.push_back( pDeadObj );
	}
		break;

	case EVENT_TYPE::SCENE_CHANGE:

		break;
	}
}