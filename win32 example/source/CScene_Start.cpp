#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CScene.h"

CScene_Start::CScene_Start( )
{
}

CScene_Start::~CScene_Start( )
{
}

void CScene_Start::update( )
{
	CScene::update( );

	if ( KEY_TAP( KEY::ENTER ) )
	{
		ChangeScene( SCENE_TYPE::TOOL );
	}

	if ( KEY_TAP( KEY::LBTN ) )
	{
		Vec2 LookAt = CCamera::GetInst( )->GetRealPos( MOUSE_POS );
		CCamera::GetInst( )->SetLookAt( LookAt );
	}
}

void CScene_Start::Entry( )
{
	// Player Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos( Vec2{ 640.f, 384.f } );
	pObj->SetScale( Vec2{ 100.f, 100.f } );
	AddObjcet( pObj, GROUP_TYPE::PLAYER );

	//CObject* pOtherPlayer = pObj->Clone( );
	//pOtherPlayer->SetPos( Vec2{ 840.f, 384.f } );
	//AddObjcet( pOtherPlayer, GROUP_TYPE::PLAYER );

	//CCamera::GetInst( )->SetTarget( pObj );

	// Monster Object 추가
	int iMonCount = 15;
	float fMoveDist = 50.f;
	float ObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst( )->GetResolution( );
	float fTerm = ( vResolution.x - (( fMoveDist + ObjScale / 2.f ) * 2.f )) / (float)( iMonCount - 1 );

	CMonster* pMonsterObj = nullptr;

	for ( int i = 0; i < iMonCount; ++i )
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetName( L"Monster" );
		pMonsterObj->SetPos( Vec2{ ( fMoveDist + ObjScale / 2.f ) + (float)i * fTerm, 50.f } );
		pMonsterObj->SetMonsterPos( pMonsterObj->GetPos( ) );
		pMonsterObj->SetDistance( fMoveDist );
		pMonsterObj->SetScale( Vec2{ ObjScale, ObjScale } );
		AddObjcet( pMonsterObj, GROUP_TYPE::MONSTER );
	}

	// 충돌 지정
	// ex) Player 그룹과 Monster 그룹 간의 충돌 체크
	CCollisionMgr::GetInst( )->CheckGroup( GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER );
	CCollisionMgr::GetInst( )->CheckGroup( GROUP_TYPE::MONSTER, GROUP_TYPE::PROJECTILE_P );

	// Camera Look 지정
	CCamera::GetInst( )->SetLookAt( vResolution / 2.f );
}

void CScene_Start::Exit( )
{
	DeleteAll( );

	CCollisionMgr::GetInst( )->Reset( );
}
