#include "GameApp.h"

int main(void)
{
	std::unique_ptr<GameApp> app = std::make_unique<GameApp>();
	app->Startup();
	app->Run();
	app->Shutdown();
	return 0;
}