#pragma once

#include <cstdint>
#include <string>

#include "Error.h"

void ReportAssertion(const char* expression, const char* file, uint32_t line, const std::string& description = "");