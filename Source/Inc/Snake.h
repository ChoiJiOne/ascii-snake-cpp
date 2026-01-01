#pragma once

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class Snake : public IActor
{
public:
	Snake(GameContext* context);
	virtual ~Snake();

	DISALLOW_COPY_AND_ASSIGN(Snake);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	ConsoleManager* _consoleMgr = nullptr;
	GameContext* _context;
};