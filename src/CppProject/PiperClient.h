#pragma once

#include <string>
#include <stdexcept>
#include <optional>
#include "stringhelper.h"

class PiperClient final
{
public:
	static void SendDelete(const std::wstring &file);

	static void SendMove(const std::wstring &tempFile, const std::wstring &targetFile, const std::wstring &exe, const std::wstring &arguments, bool canKill, std::optional<int> &processId);

private:
	static void Send(const std::wstring &payload);

	static void HandleSendException(const std::wstring &payload, std::runtime_error exception);

	static void InnerSend(const std::wstring &payload);
};
