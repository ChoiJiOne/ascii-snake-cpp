#include "GameRenderer.h"

GameRenderer::GameRenderer(ConsoleManager* consoleMgr, GameContext* gameCtx)
	: _consoleMgr(consoleMgr)
	, _gameCtx(gameCtx)
{
	_tileCharMap =
	{
		{ ETile::EMPTY, ' ' },
		{ ETile::WALL, '#' },
		{ ETile::BODY, 'o' },
		{ ETile::HEAD, '@' },
		{ ETile::FOOD, '*' },
	};
}

GameRenderer::~GameRenderer() {}

void GameRenderer::Render()
{
	if (!_gameCtx->IsDirty())
	{
		return;
	}

	_consoleMgr->MoveCursor(0, 0);
	int32_t rowSize = _gameCtx->GetRowSize();
	int32_t colSize = _gameCtx->GetColSize();

	for (int32_t y = 0; y < rowSize; ++y)
	{
		for (int32_t x = 0; x < colSize; ++x)
		{
			auto it = _tileCharMap.find(_gameCtx->GetTile(x, y));
			if (it != _tileCharMap.end())
			{
				_consoleMgr->Print(x, y, it->second);
			}
		}
	}

	_gameCtx->SetDirty(false);
}
