#pragma once

#include "AppContext.h"
#include "IApp.h"

#include "GameContext.h"
#include "GameRenderer.h"

class App : public IApp
{
public:
	App();
	virtual ~App() {}

	DISALLOW_COPY_AND_ASSIGN(App);

	virtual Result<void> OnStartup(const AppContext& appCtx) override;
	virtual void OnPreTick(const AppContext& appCtx, float deltaSeconds) override;
	virtual void OnTick(const AppContext& appCtx, float deltaSeconds) override;
	virtual void OnPostTick(const AppContext& appCtx, float deltaSeconds) override;
	virtual Result<void> OnShutdown(const AppContext& appCtx) override;

private:
	GameContext _ctx;
	GameRenderer _renderer;

	std::vector<IActor*> _actors;
};