#include <Windows.h>

#include "GameContext.h"

int main(void)
{
	GameContext context;
	
	int32_t x = 10;
	int32_t y = 10;

	// 임시 테스트용 코드.
	context.SetTile(x, y, ETile::HEAD);

	bool isDone = false;
	while (!isDone)
	{
		int32_t newX = x;
		int32_t newY = y;

		if (HIBYTE(GetAsyncKeyState(VK_DOWN)))
		{
			newY++;
		}
		if (HIBYTE(GetAsyncKeyState(VK_UP)))
		{
			newY--;
		}
		if (HIBYTE(GetAsyncKeyState(VK_LEFT)))
		{
			newX--;
		}
		if (HIBYTE(GetAsyncKeyState(VK_RIGHT)))
		{
			newX++;
		}

		if (context.IsValidTile(newX, newY))
		{
			const ETile& tile = context.GetTile(x, y);
			
			context.SetTile(x, y, ETile::EMPTY);

			x = newX;
			y = newY;
			context.SetTile(x, y, ETile::HEAD);
		}

		context.Render();
	}
	
	return 0;
}