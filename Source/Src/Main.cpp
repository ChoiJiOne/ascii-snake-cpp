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
		context.Render();
	}
	
	return 0;
}