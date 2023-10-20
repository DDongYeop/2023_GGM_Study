#pragma once

class Object;
class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Init() abstract;
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void Release();

public:
	void AddObject(Object* _pObj, OBJECT_GROUP _eType)
	{
		m_vecObj[(UINT)OBJECT_GROUP::PLAYER].push_back(_pObj);
	}

private:
	//Object*	m_obj;
	vector<Object*> m_vecObj[(UINT)OBJECT_GROUP::END];
};

