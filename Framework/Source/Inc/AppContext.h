#pragma once

#include <functional>

#include "ActorManager.h"
#include "ConsoleManager.h"
#include "InputManager.h"

class AppContext
{
public:
	AppContext(ActorManager* actorMgr, ConsoleManager* consoleMgr, InputManager* inputMgr);
	virtual ~AppContext();

	DISALLOW_COPY_AND_ASSIGN(AppContext);

	void SetRequestQuit(const std::function<void()>& requestQuit) { _requestQuit = requestQuit; }
	void RequestQuit() const
	{
		if (_requestQuit)
		{
			_requestQuit();
		}
	}

	ActorManager* GetActorManager() const { return _actorMgr; }
	ConsoleManager* GetConsoleManager() const { return _consoleMgr; }
	InputManager* GetInputManager() const { return _inputMgr; }

private:
	ActorManager* _actorMgr = nullptr;
	ConsoleManager* _consoleMgr = nullptr;
	InputManager* _inputMgr = nullptr;

	std::function<void()> _requestQuit;
};