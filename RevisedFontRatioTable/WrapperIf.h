#pragma once
#include "pch.h"

#define PROC_ATTACH(pfunc, functype, hmodule, result, label) \
    pfunc = (functype)GetProcAddress(hmodule, #pfunc); \
    if (pfunc == nullptr) { \
		DWORD errorCode = GetLastError(); \
		result = false; \
        goto label;\
	}

#define DELETE_CODE_INFO(pInfo) \
	delete[] (pInfo)->code; \
	delete[] (pInfo)->name; \
	delete pInfo;


typedef bool(*PProcCreateWrapper)();
typedef bool(*PProcBeginProcess)();
typedef bool(*PProcBeginProcessOutputFontScale)();

typedef void(*PProcUploadProjectInfo)(const char* filepath, const char* projectName);
typedef void(*PProcUploadTextCastNames)(int names_len, char** names);

typedef char* (*PProcDownloadString)(const std::string& methodName);


using namespace std;

/// <summary>
/// Wrapper DLL�Ƃ�IF
/// </summary>
class WrapperIf {

	// function pointer
	PProcCreateWrapper CreateWrapper = nullptr;
	PProcBeginProcess BeginProcess = nullptr;

	PProcUploadProjectInfo UploadProjectInfo = nullptr;
	PProcUploadTextCastNames UploadTextCastNames = nullptr;

	PProcDownloadString DownloadString = nullptr;


	HWND hWnd;
	HINSTANCE hinstDLL;
	LPVOID lpvReserved;

	// SDK����̕K�v�f�[�^
	SdkData sdkData;

	HMODULE hModule = 0;


public:
	WrapperIf(HWND hWnd, HINSTANCE hinstDLL, LPVOID lpvReserved);
	~WrapperIf() = default;

	bool init();
	void execute();
	void cleanUp();

private:
	void execute_output_ratio_data_array(DataAccessor& dataAccessor);
};
