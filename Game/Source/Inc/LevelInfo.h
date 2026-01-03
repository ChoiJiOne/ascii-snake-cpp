#pragma once

#include <cstdint>

class LevelInfo
{
public:
	LevelInfo(int32_t level, int32_t minScore, int32_t maxScore, float intervalTime);
	LevelInfo(LevelInfo&& instance) noexcept;
	LevelInfo(const LevelInfo& instance) noexcept;

	LevelInfo& operator=(LevelInfo&& instance) noexcept;
	LevelInfo& operator=(const LevelInfo& instance) noexcept;

	const int32_t& GetLevel() const { return _level; }
	const int32_t& GetMinGoal() const { return _minScore; }
	const int32_t& GetMaxGoal() const { return _maxScore; }
	const float& GetIntervalTime() const { return _intervalTime; }

private:
	int32_t _level = 0;
	int32_t _minScore = 0;
	int32_t _maxScore = 0;
	float _intervalTime = 0.0f;
};