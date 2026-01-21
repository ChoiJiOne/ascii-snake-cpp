#include <Windows.h>

#include "GenericAssert.h"
#include "InputManager.h"

EErrorCode InputManager::Startup()
{
	if (_isInitialized)
	{
		return EErrorCode::ALREADY_INITIALIZED;
	}

	_keys =
	{
		EKey::NONE,
		EKey::SPACE,
		EKey::LEFT,
		EKey::UP,
		EKey::RIGHT,
		EKey::DOWN,
		EKey::ESCAPE,
	};

	for (const auto& key : _keys)
	{
		_prevKeyPressMap[key] = false;
		_currKeyPressMap[key] = false;
	}
		
	_isInitialized = true;
	return EErrorCode::SUCCESS;
}

EErrorCode InputManager::Shutdown()
{
	if (!_isInitialized)
	{
		return EErrorCode::NOT_INITIALIZED;
	}

	_isInitialized = false;
	return EErrorCode::SUCCESS;
}

void InputManager::Tick()
{
	for (const auto& key : _keys)
	{
		_prevKeyPressMap[key] = _currKeyPressMap[key];
		_currKeyPressMap[key] = (GetAsyncKeyState(static_cast<int32_t>(key)) & 0x8000);
	}
}

EPress InputManager::GetKeyPress(const EKey& key)
{
	EPress press = EPress::NONE;

	if (IsPressKey(_prevKeyPressMap, key))
	{
		if (IsPressKey(_currKeyPressMap, key))
		{
			press = EPress::HELD;
		}
		else
		{
			press = EPress::RELEASED;
		}
	}
	else
	{
		if (IsPressKey(_currKeyPressMap, key))
		{
			press = EPress::PRESSED;
		}
		else
		{
			press = EPress::NONE;
		}
	}

	return press;
}

bool InputManager::IsPressKey(const std::map<EKey, bool>& keyPressMap, const EKey& key)
{
	auto it = keyPressMap.find(key);
	CHECK(it != keyPressMap.end());
	return it->second;
}