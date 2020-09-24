#include "JsonEscaping.h"

bool JsonEscaping::NeedEscape(const std::wstring &src, int i)
{
	auto c = src[i];
	return c < 32 || c == L'"' || c == L'\\' || c >= L'\uD800' && c <= L'\uDBFF' && (i == src.length() - 1 || src[i + 1] < L'\uDC00' || src[i + 1] > L'\uDFFF') || c >= L'\uDC00' && c <= L'\uDFFF' && (i == 0 || src[i - 1] < L'\uD800' || src[i - 1] > L'\uDBFF') || c == L'\u2028' || c == L'\u2029' || c == L'/' && i > 0 && src[i - 1] == L'<';
}

std::wstring JsonEscaping::JsonEscape(const std::wstring &contents)
{
	StringBuilder *builder = new StringBuilder();

	auto start = 0;
	for (auto i = 0; i < contents.length(); i++)
	{
		if (!NeedEscape(contents, i))
		{
			continue;
		}
		builder->Append(contents, start, i - start);
		switch (contents[i])
		{
			case L'\b':
				builder->append(L"\\b");
				break;
			case L'\f':
				builder->append(L"\\f");
				break;
			case L'\n':
				builder->append(L"\\n");
				break;
			case L'\r':
				builder->append(L"\\r");
				break;
			case L'\t':
				builder->append(L"\\t");
				break;
			case L'\"':
				builder->append(L"\\\"");
				break;
			case L'\\':
				builder->append(L"\\\\");
				break;
			case L'/':
				builder->append(L"\\/");
				break;
			default:
				builder->append(L"\\u");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
				builder->append((static_cast<int>(contents[i])).ToString(L"x04"));
				break;
		}

		start = i + 1;
	}

	builder->Append(contents, start, contents.length() - start);

	delete builder;
	return builder->toString();
}
