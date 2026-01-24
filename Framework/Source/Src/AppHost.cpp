#include "AppHost.h"

AppHost::~AppHost()
{
	if (_isInitialized)
	{
		Shutdown();
	}
}

Result<void> AppHost::Startup()
{
	if (_isInitialized)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::ALREADY_INITIALIZED, "FAILED_TO_STARTUP_FRAMEWORK_APP"));
	}

	ConsoleManager& consoleMgr = ConsoleManager::Get();
	Result<void> consoleMgrStartupResult = consoleMgr.Startup();
	if (!consoleMgrStartupResult.IsSuccess())
	{
		return consoleMgrStartupResult;
	}

	InputManager& inputMgr = InputManager::Get();
	Result<void> inputMgrStartupResult = inputMgr.Startup();
	if (!inputMgrStartupResult.IsSuccess())
	{
		return inputMgrStartupResult;
	}

	ActorManager& actorMgr = ActorManager::Get();
	Result<void> actorMgrStartupResult = actorMgr.Startup();
	if (!actorMgrStartupResult.IsSuccess())
	{
		return actorMgrStartupResult;
	}

	_isInitialized = true;
	return Result<void>::Success();
}

Result<void> AppHost::Run(IGame& game)
{
	AppContext context(ActorManager::GetPtr(), ConsoleManager::GetPtr(), InputManager::GetPtr());
	context.SetRequestQuit([this]() { _isQuit = true; });

	Result<void> startupResult = game.OnStartup(context);
	if (!startupResult.IsSuccess())
	{
		return startupResult;
	}

	while (!_isQuit)
	{
		UpdateTick(context.GetInputManager());
		game.OnUpdate(context, _timer.GetDeltaSeconds());
	}

	Result<void> shutdownResult = game.OnShutdown(context);
	if (!shutdownResult.IsSuccess())
	{
		return shutdownResult;
	}

	return Result<void>::Success();
}

Result<void> AppHost::Shutdown()
{
	if (!_isInitialized)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::NOT_INITIALIZED, "FAILED_TO_SHUTDOWN_FRAMEWORK_APP"));
	}

	ActorManager& actorMgr = ActorManager::Get();
	Result<void> actorMgrShutdownResult = actorMgr.Shutdown();
	if (!actorMgrShutdownResult.IsSuccess())
	{
		return actorMgrShutdownResult;
	}

	InputManager& inputMgr = InputManager::Get();
	Result<void> inputMgrShutdownResult = inputMgr.Shutdown();
	if (!inputMgrShutdownResult.IsSuccess())
	{
		return inputMgrShutdownResult;
	}

	ConsoleManager& consoleMgr = ConsoleManager::Get();
	Result<void> consoleMgrShutdownResult = consoleMgr.Shutdown();
	if (!consoleMgrShutdownResult.IsSuccess())
	{
		return consoleMgrShutdownResult;
	}

	_isInitialized = false;
	return Result<void>::Success();
}

void AppHost::UpdateTick(InputManager* inputMgr)
{
	_timer.Tick();
	if (inputMgr != nullptr)
	{
		inputMgr->Tick();
	}
}