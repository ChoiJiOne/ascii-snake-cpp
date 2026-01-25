#pragma once

enum class ETile
{
	EMPTY = 0x00,
	WALL  = 0x01,
	BODY  = 0x02,
	HEAD  = 0x03,
	FOOD  = 0x04,
};

enum class EMoveDirection
{
	NONE  = 0x00,
	LEFT  = 0x01,
	RIGHT = 0x02,
	UP    = 0x03,
	DOWN  = 0x04,
};

enum class EMoveResult
{
	BLOCKED = 0x00,
	MOVED   = 0x01,
	CONSUME = 0x02, // ∏‘¿Ã∏¶ ∏‘¿Ω
};