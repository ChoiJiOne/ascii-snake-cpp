#include "GameAssert.h"
#include "MathUtils.h"
#include "LevelInfo.h"

LevelInfo::LevelInfo(int32_t level, int32_t minScore, int32_t maxScore, float intervalTime)
{
	GAME_CHECK(_level >= 1);
	_level = level;

	GAME_CHECK(minScore != maxScore);
	_minScore = MathUtils::Min(minScore, maxScore);
	_maxScore = MathUtils::Max(minScore, maxScore);

	GAME_CHECK(intervalTime > 0.0f);
	_intervalTime = intervalTime;
}

LevelInfo::LevelInfo(LevelInfo&& instance) noexcept
	: _level(instance._level)
	, _minScore(instance._minScore)
	, _maxScore(instance._maxScore)
	, _intervalTime(instance._intervalTime)
{
}

LevelInfo::LevelInfo(const LevelInfo& instance) noexcept
	: _level(instance._level)
	, _minScore(instance._minScore)
	, _maxScore(instance._maxScore)
	, _intervalTime(instance._intervalTime)
{
}

LevelInfo& LevelInfo::operator=(LevelInfo&& instance) noexcept
{
	if (this == &instance) return *this;

	_level = instance._level;
	_minScore = instance._minScore;
	_maxScore = instance._maxScore;
	_intervalTime = instance._intervalTime;

	return *this;
}

LevelInfo& LevelInfo::operator=(const LevelInfo& instance) noexcept
{
	if (this == &instance) return *this;

	_level = instance._level;
	_minScore = instance._minScore;
	_maxScore = instance._maxScore;
	_intervalTime = instance._intervalTime;

	return *this;
}