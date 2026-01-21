#pragma once

#include "Error.h"

#define MAKE_ERROR(code, message) Error((code), (message), __FILE__, __LINE__, __func__)

template <typename T>
class Result
{
public:
	static Result Success(T value) { return Result(std::move(value)); }
	static Result Fail(Error error) { return Result(std::move(error)); }

	bool IsSuccess() const { return _isSuccess; }
	const Error& GetError() const { return _error; }

private:
	explicit Result(T value) : _isSuccess(true), _value(std::move(value)) {}
	explicit Result(Error error) : _isSuccess(false), _error(std::move(error)) {}

private:
	bool _isSuccess = false;
	T _value;
	Error _error;
};

template <>
class Result<void>
{
public:
	static Result Success() { return Result(true, Error()); }
	static Result Fail(Error error) { return Result(false, std::move(error)); }

	bool IsSuccess() const { return _isSuccess; }
	const Error& GetError() const { return _error; }

private:
	explicit Result(bool isOk, Error error) : _isSuccess(isOk), _error(std::move(error)) {}

private:
	bool _isSuccess = false;
	Error _error;
};
