#pragma once

#include <string>
#include "stringbuilder.h"

class JsonEscaping final
{
private:
	static bool NeedEscape(const std::wstring &src, int i);

public:
	static std::wstring JsonEscape(const std::wstring &contents);
};
