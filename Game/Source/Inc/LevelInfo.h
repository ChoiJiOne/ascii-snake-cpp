#pragma once

#include <cstdint>

enum class EScoreState
{
	BELOW_MIN = 0x00,
	IN_RANGE = 0x01,
	ABOVE_MAX = 0x02,
};

class LevelInfo
{
public:
	LevelInfo(int32_t level, int32_t minScore, int32_t maxScore, float intervalTime);
	LevelInfo(LevelInfo&& instance) noexcept;
	LevelInfo(const LevelInfo& instance) noexcept;

	LevelInfo& operator=(LevelInfo&& instance) noexcept;
	LevelInfo& operator=(const LevelInfo& instance) noexcept;

	const int32_t& GetLevel() const { return _level; }
	const int32_t& GetMinScore() const { return _minScore; }
	const int32_t& GetMaxScore() const { return _maxScore; }
	const float& GetIntervalTime() const { return _intervalTime; }
	EScoreState GetScoreState(int32_t score) const;

private:
	int32_t _level = 0;
	int32_t _minScore = 0;
	int32_t _maxScore = 0;
	float _intervalTime = 0.0f;
};