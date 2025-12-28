#pragma once

#include "IManager.h"

class GameContext;
class ConsoleManager;

class RenderManager : public IManager<RenderManager>
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager);

	void Startup();
	virtual void Shutdown() override;

	void Render(GameContext* ctx); // TODO: 나중에 다른 Renderer로 분리 예정 (RenderManager는 Renderer를 관리하는 구조로 변경 예정)

private:
	friend class IManager<RenderManager>;

	RenderManager() = default;
	virtual ~RenderManager() = default;

private:
	ConsoleManager* _consoleMgr = nullptr;
};