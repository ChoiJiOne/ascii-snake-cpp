#include "GameApp.h"

GameApp::~GameApp()
{
	if (_isInitialized)
	{
		Shutdown();
	}
}

EErrorCode GameApp::Startup()
{
	if (_isInitialized)
	{
		return EErrorCode::ALREADY_INITIALIZED;
	}

	IApp::Startup();

	_consoleMgr->SetVisibleCursor(false);
	_consoleMgr->SetTitle("Snake"); // TODO: 하드 코딩 제거 필요.
	_consoleMgr->Clear();

	SetProcessTick([this](float deltaSeconds) { ProcessTick(deltaSeconds); });

	_isInitialized = true;
	return EErrorCode::SUCCESS;
}

EErrorCode GameApp::Shutdown()
{
	if (!_isInitialized)
	{
		return EErrorCode::NOT_INITIALIZED;
	}

	_consoleMgr->SetVisibleCursor(true);

	IApp::Shutdown();

	return EErrorCode::SUCCESS;
}

void GameApp::ProcessTick(float deltaSeconds)
{
}
