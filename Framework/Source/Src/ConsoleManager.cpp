#include <Windows.h>

#include "ConsoleManager.h"

Result<void> ConsoleManager::Startup()
{
	if (_isInitialized)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::ALREADY_INITIALIZED, "FAILED_TO_STARTUP_CONSOLE_MANAGER"));
	}

	_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_outputHandle == INVALID_HANDLE_VALUE)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_GET_STANDARD_OUTPUT_HANDLE"));
	}

	_isInitialized = true;
	return Result<void>::Success();
}

Result<void> ConsoleManager::Shutdown()
{
	if (!_isInitialized)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::NOT_INITIALIZED, "FAILED_TO_SHUTDOWN_INPUT_MANAGER"));
	}

	_outputHandle = nullptr;
	_isInitialized = false;
	return Result<void>::Success();
}

Result<void> ConsoleManager::MoveCursor(int32_t x, int32_t y)
{
	COORD cursorPos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	if (!SetConsoleCursorPosition(_outputHandle, cursorPos))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_SET_CURSOR_POSITION"));
	}

	return Result<void>::Success();
}

Result<void> ConsoleManager::SetVisibleCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO info;

	if (!GetConsoleCursorInfo(_outputHandle, &info))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_GET_CURSOR_INFO"));
	}

	info.bVisible = isVisible;
	if (!SetConsoleCursorInfo(_outputHandle, &info))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_SET_CURSOR_INFO"));
	}

	return Result<void>::Success();
}

Result<void> ConsoleManager::SetTitle(const std::string_view& title)
{
	if (!SetConsoleTitle(title.data()))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_SET_TITLE"));
	}

	return Result<void>::Success();
}

Result<void> ConsoleManager::Clear()
{
	COORD topLeftPos = { 0 ,0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	if (!GetConsoleScreenBufferInfo(_outputHandle, &screen))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_GET_CONSOLE_SCREEN_BUFFER_INFO"));
	}

	if (!FillConsoleOutputCharacterA(_outputHandle, WHITE_SPACE, screen.dwSize.X * screen.dwSize.Y, topLeftPos, &written))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_FILL_OUTPUT_CHARACTER"));
	}

	if (!FillConsoleOutputAttribute(
		_outputHandle,
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y,
		topLeftPos,
		&written
	))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_FILL_OUTPUT_ATTRIBUTE"));
	}

	if (!SetConsoleCursorPosition(_outputHandle, topLeftPos))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_SET_CURSOR_POSITION"));
	}

	return Result<void>::Success();
}

Result<void> ConsoleManager::ClearRegion(int32_t x, int32_t y, int32_t width, int32_t height)
{
	width = width < 0 ? -width : width;
	height = height < 0 ? -height : height;

	for (int32_t dx = 0; dx < width; ++dx)
	{
		for (int32_t dy = 0; dy < height; ++dy)
		{
			Result<void> result = Print(x + dx, y + dy, WHITE_SPACE);
			if (!result.IsSuccess())
			{
				return result;
			}
		}
	}

	return Result<void>::Success();
}

Result<void> ConsoleManager::Print(int32_t x, int32_t y, char c)
{
	Result<void> result = MoveCursor(x, y);
	if (!result.IsSuccess())
	{
		return result;
	}

	if (!WriteConsoleA(_outputHandle, &c, CHAR_SIZE, nullptr, nullptr))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_WRITE_CONSOLE"));
	}

	return Result<void>::Success();
}

Result<void> ConsoleManager::Print(int32_t x, int32_t y, const std::string_view& str)
{
	Result<void> result = MoveCursor(x, y);
	if (!result.IsSuccess())
	{
		return result;
	}

	if (!WriteConsoleA(_outputHandle, reinterpret_cast<const void*>(str.data()), static_cast<DWORD>(str.size()), nullptr, nullptr))
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::PLATFORM_API_FAILED, "FAILED_TO_WRITE_CONSOLE"));
	}

	return Result<void>::Success();
}