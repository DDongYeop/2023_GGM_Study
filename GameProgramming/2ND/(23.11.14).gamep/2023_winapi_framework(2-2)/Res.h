#pragma once
class Res
{
public:
	Res();
	~Res();
public:
	void SetKey(const wstring& _StrKey) 
	{	m_strKey = _StrKey;	}
	void SetRelativePath(const wstring& _StrPath)
	{
		m_strRelativePath = _StrPath;
	}
	const wstring& GetKey() const { return m_strKey; }
	const wstring& GetRelativePath() const { return m_strRelativePath; }

private:
	wstring m_strKey; // 키
	wstring m_strRelativePath; // 상대경로
};

