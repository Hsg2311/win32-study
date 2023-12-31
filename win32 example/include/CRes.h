#pragma once

class CRes
{
public:
	CRes( );
	virtual ~CRes( );

	void SetKey( const std::wstring& _strKey ) { m_strKey = _strKey; }
	void SetRelativePath( const std::wstring& _strPath ) { m_strRelativePath = _strPath; }

	const std::wstring& GetKey( ) { return m_strKey; }
	const std::wstring& GetRelativePath( ) { return m_strRelativePath; }

private:
	std::wstring m_strKey;				// 리소스 키값
	std::wstring m_strRelativePath;		// 리소스 상대경로
};
