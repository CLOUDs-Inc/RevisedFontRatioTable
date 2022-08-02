#include "pch.h"

//--------------------
// Wrapper DLL�Ƃ�IF
//--------------------
WrapperIf::WrapperIf(HWND hWnd, HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	this->hWnd = hWnd;
	this->hinstDLL = hinstDLL;
	this->lpvReserved = lpvReserved;
}

/// <summary>
/// ����������
/// </summary>
/// <returns>����</returns>
bool WrapperIf::init()
{
	bool result = true;

	// wrapper.dll�̃��[�h LoadLibrary
	// -------------------------------
	wchar_t ModulePath[MAX_PATH + 1];
	GetModuleFileName(hinstDLL, ModulePath, MAX_PATH);

	wchar_t* slash_pos = wcsrchr(ModulePath, '\\');
	*slash_pos = 0;

	// Plug-in DLL�̃t�@�C���p�X�����b�p�[DLL�ɕϊ�
	wcscat_s(ModulePath, MAX_PATH, MANAGED_WRAPPER_DLL);

	// ModulePath�`�F�b�N
	size_t pathSize = wcslen(ModulePath) + 1;
	size_t convertedChars = 0;
	char* pathStr = new char[pathSize * 2];
	wcstombs_s(&convertedChars, pathStr, pathSize * 2, ModulePath, _TRUNCATE);
	delete[] pathStr;

	// DLL�t�@�C���̃��[�h
	hModule = LoadLibrary(ModulePath);
	if (hModule == NULL) {
		MessageBox(this->hWnd, L"Wrapper DLL read failed.", L"Error", MB_OK);
		result = false;
		goto INIT_ERROR;
	}

	// DLL�̊֐��A�^�b�`
	PROC_ATTACH(CreateWrapper, PProcCreateWrapper, hModule, result, INIT_ERROR);
	PROC_ATTACH(BeginProcess, PProcBeginProcess, hModule, result, INIT_ERROR);

	PROC_ATTACH(UploadProjectInfo, PProcUploadProjectInfo, hModule, result, INIT_ERROR);
	PROC_ATTACH(UploadTextCastNames, PProcUploadTextCastNames, hModule, result, INIT_ERROR);

	PROC_ATTACH(DownloadString, PProcDownloadString, hModule, result, INIT_ERROR);

INIT_ERROR:

	return result;
}

/// <summary>
/// ���������c�[���������s
/// </summary>
void WrapperIf::execute()
{
	BOOL result = TRUE;

	bool create_wrapper_result = false;
	bool process_result = false;

	// CreateWrapper
	create_wrapper_result = CreateWrapper();
	if (!create_wrapper_result) {
		MessageBox(this->hWnd, L"GUI DLL read failed.", L"Error", MB_OK);
		return;
	}

	// SDK�A�N�Z�X�I�u�W�F�N�g
	DataAccessor dataAccessor(hinstDLL, lpvReserved);

	// SDK����v���W�F�N�g�����擾���A.net���ɃA�b�v����
	dataAccessor.GetProjectInfo(sdkData);

	// (char*�ɐ؂�ւ���)�v���W�F�N�g����.NET���ɓ]��
	UploadProjectInfo(sdkData.projectPath.c_str(), sdkData.projectName.c_str());

	// SDK����e�L�X�g�L���X�g�����擾���A.net���ɃA�b�v����
	dataAccessor.GetTextCastNames(sdkData);

	// vector<string>����vector<char*>�ɕϊ�
	vector<char*> namePointers;
	for (size_t idx = 0; idx < sdkData.textCastNames.size(); idx++) {
		char* pc = (char*)sdkData.textCastNames[idx].c_str();
		namePointers.push_back(pc);
	}

	// ���M�p�e�L�X�g�L���X�g���|�C���^�z��
	char** sentNamePointers = nullptr;
	// �e�L�X�g�L���X�g���̎��f�[�^�����蓖��
	if (0 < namePointers.size()) {
		sentNamePointers = &(namePointers[0]);
	}

	// (char*�ɐ؂�ւ����e�L�X�g�L���X�g����.NET���ɓ]��)
	UploadTextCastNames(namePointers.size(), sentNamePointers);

	execute_output_ratio_data_array(dataAccessor);


}


/// <summary>
/// ���������c�[���������s
/// </summary>
void WrapperIf::execute_output_ratio_data_array(DataAccessor& dataAccessor)
{
	BOOL result = TRUE;
	bool create_wrapper_result = false;
	bool process_result = false;

	// UI���ɐ��������J�n���˗�
	process_result = BeginProcess();
	if (!process_result) {
		return;
	}

	// SDK�ւ̏������ݗp�f�[�^
	WriteData writeData;

	// �o�̓X�N���v�g�L���X�g���擾
	char* pScriptName = DownloadString("DownloadTableScriptName");
	writeData.scriptName = string(pScriptName);
	delete[] pScriptName;

	// �o�̓X�N���v�g�L���X�g�R�[�h�擾
	char* pScriptCode = DownloadString("DownloadTableScriptCode");
	writeData.tableScriptCode = string(pScriptCode);
	delete[] pScriptCode;

	// �o�̓X�N���v�g�L���X�g�R�[�h��SDK�ŏ�������
	bool write_result = dataAccessor.WriteRatioDataTableScript(writeData);
	if (!write_result) {
		MessageBox(this->hWnd, L"Writing script cast failed.", L"Error", MB_OK);
	}
	else {
		MessageBox(this->hWnd, L"Writing script cast succeeded.", L"Error", MB_OK);
	}

	return;
}


/// <summary>
/// Wrapper IF�N���[�Y����
/// </summary>
void WrapperIf::cleanUp() {

	// dll�̃A�����[�h FreeLibrary
	if (hModule != NULL)
		FreeLibrary(hModule);

	return;
}
