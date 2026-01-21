#include "IApp.h"
#include "GenericAssert.h"

IApp::IApp()
{
}

IApp::~IApp()
{
	if (_isInitialized)
	{
		Shutdown();
	}
}

EErrorCode IApp::Startup()
{
	if (_isInitialized)
	{
		return EErrorCode::ALREADY_INITIALIZED;
	}

	_consoleMgr = ConsoleManager::GetPtr();
	_inputMgr = InputManager::GetPtr();
	_actorMgr = ActorManager::GetPtr();

	EErrorCode errorCode = EErrorCode::SUCCESS;

	errorCode = _consoleMgr->Startup();
	if (errorCode != EErrorCode::SUCCESS)
	{
		return EErrorCode::FAILED_TO_INITIALIZE;
	}

	errorCode = _inputMgr->Startup();
	if (errorCode != EErrorCode::SUCCESS)
	{
		return EErrorCode::FAILED_TO_INITIALIZE;
	}

	errorCode = _actorMgr->Startup();
	if (errorCode != EErrorCode::SUCCESS)
	{
		return EErrorCode::FAILED_TO_INITIALIZE;
	}

	return errorCode;
}

void IApp::Run()
{
	_timer.Start();
	_isDoneLoop = false;

	while (!_isDoneLoop)
	{
		UpdateTick();
		if (_processTick != nullptr)
		{
			_processTick(_timer.GetDeltaSeconds());
		}
	}
}

EErrorCode IApp::Shutdown()
{
	if (!_isInitialized)
	{
		return EErrorCode::NOT_INITIALIZED;
	}

	if (_actorMgr != nullptr)
	{
		_actorMgr->Shutdown();
		_actorMgr = nullptr;
	}

	if (_inputMgr != nullptr)
	{
		_inputMgr->Shutdown();
		_inputMgr = nullptr;
	}

	if (_consoleMgr != nullptr)
	{
		_consoleMgr->Shutdown();
		_consoleMgr = nullptr;
	}

	_isInitialized = false;
	return EErrorCode::SUCCESS;
}

void IApp::UpdateTick()
{
	_timer.Tick();
	_inputMgr->Tick();
}