#pragma once

#include "AppContext.h"
#include "IGame.h"

#include "GameContext.h"

class Game : public IGame
{
public:
	Game() = default;
	virtual ~Game() {}

	DISALLOW_COPY_AND_ASSIGN(Game);

	virtual Result<void> OnStartup(const AppContext& appCtx) override;
	virtual void OnUpdate(const AppContext& appCtx, float deltaSeconds) override;
	virtual Result<void> OnShutdown(const AppContext& appCtx) override;

private:
	GameContext _gameCtx;
};