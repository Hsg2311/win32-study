#pragma once

#define SINGLETON( type ) public:\
							static type* GetInst( )\
							{\
								static type mgr;\
								return &mgr;\
							}\
						 private:\
							type( );\
							~type( );

#define DT CTimeMgr::GetInst( )->GetDT( )
#define fDT CTimeMgr::GetInst( )->GetfDT( )

#define KEY_CHECK( key, state ) CKeyMgr::GetInst( )->GetKeyState( key ) == state
#define KEY_HOLD( key ) KEY_CHECK( key, KEY_STATE::HOLD )
#define KEY_TAP( key ) KEY_CHECK( key, KEY_STATE::TAP )
#define KEY_AWAY( key ) KEY_CHECK( key, KEY_STATE::AWAY )
#define KEY_NONE( key ) KEY_CHECK( key, KEY_STATE::NONE )
#define MOUSE_POS CKeyMgr::GetInst( )->GetMousePos( )

#define TILE_SIZE 64

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	PLAYER,
	MONSTER,
	PROJECTILE_P,
	PROJECTILE_M,

	EOE	// END_OF_ENUM_CLASS
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	EOE
};

enum class BRUSH_TYPE
{
	HOLLOW,

	EOE
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	EOE
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	EOE
};