#include "AppHost.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	AppHost appHost;
	Game game;

	Result<void> result = appHost.Startup();
	if (!result.IsSuccess())
	{
		return 0;
	}

	result = appHost.Run(game);
	if (!result.IsSuccess())
	{
		return 0;
	}

	result = appHost.Shutdown();
	if (!result.IsSuccess())
	{
		return 0;
	}

	return 0;
}