#pragma once
#include "Object.h"

class Player :
    public Object
{
public:
    void Update() override;
    //void Render(HDC _dc) override;
private:
    void CreateBullet();
};

