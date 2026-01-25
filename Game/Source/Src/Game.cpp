#include "Game.h"

Game::Game()
	: _renderer(ConsoleManager::GetPtr(), &_context)
{}

Result<void> Game::OnStartup(const AppContext& appCtx)
{
	ConsoleManager* consoleMgr = appCtx.GetConsoleManager();
	if (consoleMgr == nullptr)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::INVALID_ARGUMENT, "INVALID_CONSOLE_MANAGER_FROM_APP_CONTEXT"));
	}

	consoleMgr->SetVisibleCursor(false);
	consoleMgr->SetTitle("Snake"); // TODO: 하드 코딩 제거 필요.
	consoleMgr->Clear();

	_context.Reset();

	return Result<void>::Success();
}

void Game::OnTick(const AppContext& appCtx, float deltaSeconds)
{
	InputManager* inputMgr = appCtx.GetInputManager();
	ConsoleManager* consoleMgr = appCtx.GetConsoleManager();

	if (inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		appCtx.RequestQuit();
	}

	_renderer.Render();
}

Result<void> Game::OnShutdown(const AppContext& appCtx)
{
	ConsoleManager* consoleMgr = appCtx.GetConsoleManager();
	if (consoleMgr == nullptr)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::INVALID_ARGUMENT, "INVALID_CONSOLE_MANAGER_FROM_APP_CONTEXT"));
	}

	consoleMgr->SetVisibleCursor(true);

	return Result<void>::Success();
}