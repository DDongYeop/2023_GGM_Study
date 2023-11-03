#pragma once
class Texture;
class ResMgr
{
	SINGLE(ResMgr);
public:
	Texture* TexLoad(const wstring& _StrKey, const wstring& _strRelativePath);
	Texture* TexFind(const wstring& _strKey);
	void Release();
private:
	map<wstring, Texture*> m_mapTex;
};

