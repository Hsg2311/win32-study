#include "pch.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene( )
{

}

CScene::~CScene( )
{
	for ( UINT i = 0; i < (UINT)GROUP_TYPE::END_OF_ENUM_CLASS; ++i )
	{
		for ( size_t j = 0; j < m_arrObj[ i ].size( ); ++j )
		{
			// m_arrObj[i] �׷� ������ j ��ü ����
			delete m_arrObj[ i ][ j ];
		}
	}
}

void CScene::update( )
{
	for ( UINT i = 0; i < (UINT)GROUP_TYPE::END_OF_ENUM_CLASS; ++i )
	{
		for ( size_t j = 0; j < m_arrObj[ i ].size( ); ++j )
		{
			m_arrObj[ i ][ j ]->update( );
		}
	}
}

void CScene::render( HDC _dc )
{
	for ( UINT i = 0; i < (UINT)GROUP_TYPE::END_OF_ENUM_CLASS; ++i )
	{
		for ( size_t j = 0; j < m_arrObj[ i ].size( ); ++j )
		{
			m_arrObj[ i ][ j ]->render( _dc );
		}
	}
}