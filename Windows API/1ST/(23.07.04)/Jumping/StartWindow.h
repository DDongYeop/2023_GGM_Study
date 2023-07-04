#pragma once

class StartWindow : public BTSEngine
{
public:
	StartWindow();
	virtual ~StartWindow();

public:
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

