#include "App.h"
#include "Snake.h"

App::App()
	: _renderer(ConsoleManager::GetPtr(), &_ctx)
{}

Result<void> App::OnStartup(const AppContext& appCtx)
{
	ConsoleManager* consoleMgr = appCtx.GetConsoleManager();
	if (consoleMgr == nullptr)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::INVALID_ARGUMENT, "INVALID_CONSOLE_MANAGER_FROM_APP_CONTEXT"));
	}

	consoleMgr->SetVisibleCursor(false);
	consoleMgr->SetTitle("Snake"); // TODO: 하드 코딩 제거 필요.
	consoleMgr->Clear();

	Snake* snake = appCtx.GetActorManager()->Create<Snake>(&_ctx, 3, EMoveDirection::RIGHT);
	_actors =
	{
		snake,
	};

	std::function<void()> snakeStateResetFn = std::bind(&Snake::Reset, snake);
	_ctx.SetSnakeResetFn(snakeStateResetFn);
	_ctx.Reset();

	return Result<void>::Success();
}

void App::OnPreTick(const AppContext& appCtx, float deltaSeconds)
{
	InputManager* inputMgr = appCtx.GetInputManager();
	if (inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		appCtx.RequestQuit();
	}
}

void App::OnTick(const AppContext& appCtx, float deltaSeconds)
{
	for (auto& actor : _actors)
	{
		actor->Tick(deltaSeconds);
	}

	if (_ctx.IsGameOver())
	{
		_ctx.Reset();
	}
}

void App::OnPostTick(const AppContext& appCtx, float deltaSeconds)
{
	_renderer.Render(); // NOTE: 규칙만 갖춘다면 Game에서 렌더링 처리를 할 필요가 있을까? 프레임워크에서 해주면 안되나?
}

Result<void> App::OnShutdown(const AppContext& appCtx)
{
	ConsoleManager* consoleMgr = appCtx.GetConsoleManager();
	if (consoleMgr == nullptr)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::INVALID_ARGUMENT, "INVALID_CONSOLE_MANAGER_FROM_APP_CONTEXT"));
	}

	consoleMgr->SetVisibleCursor(true);

	return Result<void>::Success();
}