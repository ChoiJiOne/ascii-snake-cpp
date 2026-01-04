#pragma once

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class FoodView : public IActor
{
public:
	FoodView(GameContext* context);
	virtual ~FoodView();

	DISALLOW_COPY_AND_ASSIGN(FoodView);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	GameContext* _context = nullptr;
	ConsoleManager* _consoleMgr = nullptr;

	Position _countViewPosition = { 0, 0 };
	bool _isDirty = false;
	int32_t _count = 0;
};