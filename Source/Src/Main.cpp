#include <iostream>

// TODO: 임시로 클래스가 아닌 구조체로 선언 (나중에 class로 변경)
struct GameContext
{
	int32_t board[10][10] = { 0, };
};

int main(void)
{
	GameContext context;

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (x == 0 || x == 9 || y == 0 || y == 9)
			{
				context.board[x][y] = 1;
			}
		}
	}

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (context.board[x][y] == 1)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << " ";
			}
		}

		std::cout << "\n";
	}

	return 0;
}