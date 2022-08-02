#pragma once

using namespace std;

/// <summary>
/// SDK�f�[�^�A�N�Z�X�N���X
/// </summary>
class DataAccessor {

	HINSTANCE hinstDLL;
	LPVOID lpvReserved;
	std::vector<string> writeFailedModules;

public:
	DataAccessor(HINSTANCE hinstDLL, LPVOID lpvReserved);
	~DataAccessor() = default;

	bool GetProjectInfo(SdkData& data);
	void GetTextCastNames(SdkData& data);

	bool WriteRatioDataTableScript(WriteData& data);
};
