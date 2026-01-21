#pragma once

#include <functional>
#include <map>
#include <memory>

#include "ActorManager.h"
#include "ConsoleManager.h"
#include "Macro.h"
#include "GameTimer.h"
#include "InputManager.h"

class IApp
{
public:
	IApp();
	virtual ~IApp();

	virtual EErrorCode Startup();
	virtual EErrorCode Shutdown();

	void Run();
	void SetDoneLoop(bool isDoneLoop) { _isDoneLoop = isDoneLoop; }
	void SetProcessTick(const std::function<void(float)>& processTick) { _processTick = processTick; }

protected:
	bool _isInitialized = false;

	ConsoleManager* _consoleMgr = nullptr;
	InputManager* _inputMgr = nullptr;
	ActorManager* _actorMgr = nullptr;

private:
	void UpdateTick();

private:
	bool _isDoneLoop = false;
	std::function<void(float)> _processTick;
	GameTimer _timer;
};