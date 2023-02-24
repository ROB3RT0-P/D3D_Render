#pragma once

namespace file
{

	HANDLE GetFileData(const char* const filename, void** outData, DWORD* size);
	void CloseFile(const HANDLE fileHandle);

}