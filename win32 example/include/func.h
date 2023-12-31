#pragma once

class CObject;

void CreateObject( CObject* _other, GROUP_TYPE _eGroup );
void DeleteObject( CObject* _other );
void ChangeScene( SCENE_TYPE _eNext );

template<class T>
void Safe_Delete_Vec( std::vector<T>& _vec )
{
	for ( size_t i = 0; i < _vec.size( ); ++i )
	{
		if ( _vec[ i ] != nullptr )
		{
			delete _vec[ i ];
		}
	}

	_vec.clear( );
}

template<class T1, class T2>
void Safe_Delete_Map( std::map<T1, T2>& _map )
{
	typename std::map<T1, T2>::iterator iter = _map.begin( );

	for ( ; iter != _map.end( ); ++iter )
	{
		if ( iter->second != nullptr )
		{
			delete iter->second;
		}
	}

	_map.clear( );
}