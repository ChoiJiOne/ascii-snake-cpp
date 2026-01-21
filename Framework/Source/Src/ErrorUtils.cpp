#include <windows.h>

#include "ErrorUtils.h"
#include "StringUtils.h"

void ReportAssertion(const char* expression, const char* file, uint32_t line, const std::string& description)
{
	std::string errMsg = StringUtils::PrintF(
		"Assertion check point failed!\nFile: %s\nLine: %d\nExpression: %s\nDescription: %s", 
		file, line, expression
	);
	if (!description.empty())
	{
		errMsg += StringUtils::PrintF("\nDescription: %s\n", description.c_str());
	}

	::MessageBoxA(nullptr, errMsg.c_str(), "REPORT GENERIC ASSERTION", MB_ICONERROR | MB_OK);
}