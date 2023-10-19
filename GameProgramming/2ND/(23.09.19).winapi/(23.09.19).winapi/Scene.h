#pragma once

class Object;
class Scene
{
public:
	Scene();
	~Scene();

private:
	//Object*	m_obj;
	vector<Object*> m_vecObj[(UINT)OBJECT_GROUP::END]l
};

