#include "AppHost.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	AppHost appHost;
	Game game;

	// CHECKME: 여기 main 엔트리 포인트 이후에 점검 필요
	Result<void> result = appHost.Startup();
	if (!result.IsSuccess())
	{
		return 0; // NOTE: 여기에 뭔가 로그라도 찍어줘야 하지 않을까...?
	}

	result = appHost.Run(game);
	if (!result.IsSuccess())
	{
		return 0; // NOTE: 여기에 뭔가 로그라도 찍어줘야 하지 않을까...?
	}

	result = appHost.Shutdown();
	if (!result.IsSuccess())
	{
		return 0; // NOTE: 여기에 뭔가 로그라도 찍어줘야 하지 않을까...?
	}

	return 0;
}