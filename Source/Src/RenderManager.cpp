#include <cassert>

#include "ConsoleManager.h"
#include "GameContext.h"
#include "RenderManager.h"

void RenderManager::Startup()
{
	if (_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요.
	}

	_consoleMgr = ConsoleManager::GetPtr();
}

void RenderManager::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요
	}

	// CHECKME: 여기에서 리소스 정리.
	_consoleMgr = nullptr;
	_isInitialized = false;
}

void RenderManager::Render(GameContext* ctx)
{
	if (!ctx->IsDirty())
	{
		return;
	}

	_consoleMgr->MoveCursor(0, 0);

	const std::map<ETile, char>& tileCharMap = ctx->GetTileCharMap();
	int32_t rowSize = ctx->GetRowSize();
	int32_t colSize = ctx->GetColSize();

	for (int32_t y = 0; y < rowSize; ++y)
	{
		for (int32_t x = 0; x < colSize; ++x)
		{
			auto it = tileCharMap.find(ctx->GetTile(x, y));
			if (it != tileCharMap.end())
			{
				_consoleMgr->Print(x, y, it->second);
			}
		}
	}

	ctx->SetDirty(false);
}