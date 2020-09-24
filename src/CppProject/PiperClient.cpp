#include "PiperClient.h"
#include "JsonEscaping.h"

void PiperClient::SendDelete(const std::wstring &file)
{
	auto payload = LR"({{
"Type":"Delete",
"File":")" + file + LR"("
}}
)";
	Send(payload);
}

void PiperClient::SendMove(const std::wstring &tempFile, const std::wstring &targetFile, const std::wstring &exe, const std::wstring &arguments, bool canKill, std::optional<int> &processId)
{
	auto payload = LR"({
"Type":"Move",
"Temp":")" + JsonEscaping::JsonEscape(tempFile) + LR"(",
"Target":")" + JsonEscaping::JsonEscape(targetFile) + LR"(",
"Exe":")" + JsonEscaping::JsonEscape(exe) + LR"(",
"Arguments":")" + JsonEscaping::JsonEscape(arguments) + LR"(",
"CanKill":)" + StringHelper::toString(canKill).ToLower();

	if (processId)
	{
		payload += L",";
		payload += L"\"ProcessId\":" + processId;
	}

	payload += L'}';
	Send(payload);
}

void PiperClient::Send(const std::wstring &payload)
{
	try
	{
		InnerSend(payload);
	}
	catch (const std::runtime_error &exception)
	{
		HandleSendException(payload, exception);
	}
}

void PiperClient::HandleSendException(const std::wstring &payload, std::runtime_error exception)
{
	Trace::WriteLine(LR"(Failed to send payload to DiffEngineTray.

Payload:
)" + payload + LR"(

Exception:
)" + exception);
}

void PiperClient::InnerSend(const std::wstring &payload)
{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var pipe = new NamedPipeClientStream(".", "DiffEngine", PipeDirection.Out, PipeOptions.None))
	{
		auto pipe = NamedPipeClientStream(L".", L"DiffEngine", PipeDirection::Out, PipeOptions::None);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new StreamWriter(pipe))
		{
			auto stream = StreamWriter(pipe);
			pipe.Connect(1000);
			stream.Write(payload);
		}
	}
}
