#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "GameMacro.h"

enum class ETile
{
	EMPTY = 0x00,
	WALL = 0x01,
	BODY = 0x02,
	HEAD = 0x03,
	FOOD = 0x04,
};

class GameContext
{
public:
	GameContext();
	virtual ~GameContext();

	DISALLOW_COPY_AND_ASSIGN(GameContext);

	void Render(); // CHECKME: 임시로 있는 것임 (나중에 렌더러가 컨텍스트 참조해서 렌더링할 예정)

	void SetTile(int32_t x, int32_t y, const ETile& tile);

	const ETile& GetTile(int32_t x, int32_t y);
	bool IsDirty() const { return _isDirty; }
	bool IsValidTile(int32_t x, int32_t y);
	bool IsOutline(int32_t x, int32_t y);

private:
	bool _isDirty = false;

	int32_t _rowSize = 20; // 세로 크기
	int32_t _colSize = 20; // 가로 크기

	std::vector<ETile> _tiles;
	std::map<ETile, char> _tileCharMap;
};
