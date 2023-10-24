#pragma once
#include "Object.h"
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();
public:
    void Update() override;
private:
    float m_fDir; 
};

