#pragma once

#include "IApp.h"

class GameApp : public IApp
{
public:
	GameApp() = default;
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual EErrorCode Startup() override;
	virtual EErrorCode Shutdown() override;

private:
	void ProcessTick(float deltaSeconds);
};