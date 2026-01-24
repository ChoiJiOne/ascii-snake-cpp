#include "AppContext.h"

AppContext::AppContext(ActorManager* actorMgr, ConsoleManager* consoleMgr, InputManager* inputMgr)
	: _actorMgr(actorMgr)
	, _consoleMgr(consoleMgr)
	, _inputMgr(inputMgr)
{
}

AppContext::~AppContext()
{
	_actorMgr = nullptr;
	_consoleMgr = nullptr;
	_inputMgr = nullptr;
}