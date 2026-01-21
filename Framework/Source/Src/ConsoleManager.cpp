#include <Windows.h>

#include "ConsoleManager.h"

EErrorCode ConsoleManager::Startup()
{
	if (_isInitialized)
	{
		return EErrorCode::ALREADY_INITIALIZED;
	}

	_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_outputHandle == INVALID_HANDLE_VALUE)
	{
		return EErrorCode::PLATFORM_API_FAILED;
	}

	_isInitialized = true;
}

EErrorCode ConsoleManager::Shutdown()
{
	if (!_isInitialized)
	{
		return EErrorCode::NOT_INITIALIZED;
	}

	_outputHandle = nullptr;
	_isInitialized = false;
}

EErrorCode ConsoleManager::MoveCursor(int32_t x, int32_t y)
{
	COORD cursorPos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };

	EErrorCode errorCode = EErrorCode::SUCCESS;
	if (!SetConsoleCursorPosition(_outputHandle, cursorPos))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
	}

	return errorCode;
}

EErrorCode ConsoleManager::SetVisibleCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO info;

	EErrorCode errorCode = EErrorCode::SUCCESS;
	if (!GetConsoleCursorInfo(_outputHandle, &info))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	info.bVisible = isVisible;
	if (!SetConsoleCursorInfo(_outputHandle, &info))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	return errorCode;
}

EErrorCode ConsoleManager::SetTitle(const std::string_view& title)
{
	EErrorCode errorCode = EErrorCode::SUCCESS;
	if (!SetConsoleTitle(title.data()))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	return errorCode;
}

EErrorCode ConsoleManager::Clear()
{
	COORD topLeftPos = { 0 ,0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	EErrorCode errorCode = EErrorCode::SUCCESS;
	if (!GetConsoleScreenBufferInfo(_outputHandle, &screen))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	if (!FillConsoleOutputCharacterA(_outputHandle, WHITE_SPACE, screen.dwSize.X * screen.dwSize.Y, topLeftPos, &written))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	if (!FillConsoleOutputAttribute(
		_outputHandle,
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y,
		topLeftPos,
		&written
	))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	if (!SetConsoleCursorPosition(_outputHandle, topLeftPos))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	return errorCode;
}

EErrorCode ConsoleManager::ClearRegion(int32_t x, int32_t y, int32_t width, int32_t height)
{
	width = width < 0 ? -width : width;
	height = height < 0 ? -height : height;

	for (int32_t dx = 0; dx < width; ++dx)
	{
		for (int32_t dy = 0; dy < height; ++dy)
		{
			EErrorCode errorCode = Print(x + dx, y + dy, WHITE_SPACE);
			if (errorCode != EErrorCode::SUCCESS)
			{
				return errorCode;
			}
		}
	}

	return EErrorCode::SUCCESS;
}

EErrorCode ConsoleManager::Print(int32_t x, int32_t y, char c)
{
	EErrorCode errorCode = MoveCursor(x, y);
	if (errorCode != EErrorCode::SUCCESS)
	{
		return errorCode;
	}

	if (WriteConsoleA(_outputHandle, &c, CHAR_SIZE, nullptr, nullptr))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	return errorCode;
}

EErrorCode ConsoleManager::Print(int32_t x, int32_t y, const std::string_view& str)
{
	EErrorCode errorCode = MoveCursor(x, y);
	if (errorCode != EErrorCode::SUCCESS)
	{
		return errorCode;
	}

	if (WriteConsoleA(_outputHandle, reinterpret_cast<const void*>(str.data()), static_cast<DWORD>(str.size()), nullptr, nullptr))
	{
		errorCode = EErrorCode::PLATFORM_API_FAILED;
		return errorCode;
	}

	return errorCode;
}