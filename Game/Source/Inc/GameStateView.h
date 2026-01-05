#pragma once

#include <map>
#include <string>

#include "IActor.h"
#include "GameApp.h"

class ConsoleManager;

class GameStateView : public IActor
{
public:
	GameStateView(GameApp* app);
	virtual ~GameStateView();

	DISALLOW_COPY_AND_ASSIGN(GameStateView);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	GameApp* _app = nullptr;
	ConsoleManager* _consoleMgr = nullptr;

	EGameState _state = EGameState::NONE;
	bool _isDirty = false;

	Position _stateTextViewPositon = { 0, 0 };
	int32_t _stateTextRegionWidth = 0;
	int32_t _stateTextRegionHeight = 0;
	std::map<EGameState, std::string> _stateTextMap;
};