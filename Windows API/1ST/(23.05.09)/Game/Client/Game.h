#pragma once

class Game : public BTSEngine
{
public:
	Game();
	virtual ~Game();

public:
	virtual void Init()	override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

