#pragma once

#include <cstdint>
#include <string>

#include "IManager.h"

class ConsoleManager : public IManager<ConsoleManager>
{
public:
	DISALLOW_COPY_AND_ASSIGN(ConsoleManager);

	virtual EErrorCode Startup() override;
	virtual EErrorCode Shutdown() override;
	
	EErrorCode MoveCursor(int32_t x, int32_t y);
	EErrorCode SetVisibleCursor(bool isVisible);
	EErrorCode SetTitle(const std::string_view& title);
	EErrorCode Clear();
	EErrorCode ClearRegion(int32_t x, int32_t y, int32_t width, int32_t height);

	EErrorCode Print(int32_t x, int32_t y, char c);
	EErrorCode Print(int32_t x, int32_t y, const std::string_view& str);

private:
	friend class IManager<ConsoleManager>;

	const char WHITE_SPACE = ' ';
	const int32_t CHAR_SIZE = 1;

	ConsoleManager() = default;
	virtual ~ConsoleManager() = default; // 반드시 Shutdown을 통해 리소스 정리.

private:
	void* _outputHandle = nullptr;
};