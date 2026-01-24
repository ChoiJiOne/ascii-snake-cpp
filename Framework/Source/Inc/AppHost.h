#pragma once

#include <functional>

#include "GameTimer.h"
#include "IGame.h"

class InputManager;

class AppHost
{
public:
	AppHost() = default;
	virtual ~AppHost();

	Result<void> Startup();
	Result<void> Run(IGame& game);
	Result<void> Shutdown();

private:
	void UpdateTick(InputManager* inputMgr);

private:
	bool _isInitialized = false;
	bool _isQuit = false;

	std::function<void(float)> _processTick;
	GameTimer _timer;
};