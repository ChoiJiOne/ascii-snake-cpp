#include <Windows.h>

#include "ConsoleManager.h"
#include "InputManager.h"

#include "GameContext.h"

int main(void)
{
	ConsoleManager::Get().Startup();
	InputManager::Get().Startup();

	ConsoleManager::Get().SetVisibleCursor(false);
	ConsoleManager::Get().SetTitle("Snake");

	GameContext context;

	bool isDone = false;
	while (!isDone)
	{
		InputManager::Get().Tick();

		EPress press = InputManager::Get().GetKeyPress(EKey::SPACE);
		if (press == EPress::NONE)
		{
			ConsoleManager::Get().Print(0, 0, "NONE!!!");
		}
		if (press == EPress::PRESSED)
		{
			ConsoleManager::Get().Print(0, 0, "PRESSED!!!");
		}
		if (press == EPress::HELD)
		{
			ConsoleManager::Get().Print(0, 0, "HELD!!!");
		}
		if (press == EPress::RELEASED)
		{
			ConsoleManager::Get().Print(0, 0, "RELEASED!!!");
		}
	}

	//int32_t x = 10;
	//int32_t y = 10;

	//// 임시 테스트용 코드.
	//context.SetTile(x, y, ETile::HEAD);

	//bool isDone = false;
	//bool isPressed = false;
	//while (!isDone)
	//{
	//	isPressed = false;
	//	int32_t newX = x;
	//	int32_t newY = y;

	//	if (HIBYTE(GetAsyncKeyState(VK_DOWN)))
	//	{
	//		isPressed = true;
	//		newY++;
	//	}
	//	if (HIBYTE(GetAsyncKeyState(VK_UP)))
	//	{
	//		isPressed = true;
	//		newY--;
	//	}
	//	if (HIBYTE(GetAsyncKeyState(VK_LEFT)))
	//	{
	//		isPressed = true;
	//		newX--;
	//	}
	//	if (HIBYTE(GetAsyncKeyState(VK_RIGHT)))
	//	{
	//		isPressed = true;
	//		newX++;
	//	}

	//	if (HIBYTE(GetAsyncKeyState(VK_ESCAPE)))
	//	{
	//		ConsoleManager::Get().Clear();
	//	}
	//	if (HIBYTE(GetAsyncKeyState(VK_SPACE)))
	//	{
	//		isPressed = true;
	//	}

	//	if (context.IsValidTile(newX, newY) &&  isPressed)
	//	{
	//		const ETile& tile = context.GetTile(x, y);
	//		
	//		context.SetTile(x, y, ETile::EMPTY);

	//		x = newX;
	//		y = newY;
	//		context.SetTile(x, y, ETile::HEAD);
	//	}

	//	context.Render();
	//}

	ConsoleManager::Get().SetVisibleCursor(true);

	InputManager::Get().Shutdown();
	ConsoleManager::Get().Shutdown();

	return 0;
}