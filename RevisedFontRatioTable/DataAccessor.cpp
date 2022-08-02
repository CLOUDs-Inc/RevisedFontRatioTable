#include "pch.h"

DataAccessor::DataAccessor(HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	this->hinstDLL = hinstDLL;
	this->lpvReserved = lpvReserved;
}

/// <summary>
/// SDK�̃v���W�F�N�g���̎擾�E�i�[
/// </summary>
/// <param name="aatData">�f�[�^�Ǘ��I�u�W�F�N�g</param>
/// <returns>��������</returns>
bool DataAccessor::GetProjectInfo(SdkData& data)
{
	// �v���W�F�N�g�t�@�C���p�X���擾
	char* pProjectPath;
	pProjectPath = MxPluginPort_Project_GetContentsPath();
	if (pProjectPath == NULL) {
		return false;
	}

	// �v���W�F�N�g�����擾
	char* pProjectName;
	pProjectName = MxPluginPort_Project_GetContentsName();
	if (pProjectName == NULL) {
		return false;
	}

	// �v���W�F�N�g�t�@�C���p�X��ێ�
	data.projectPath = string(pProjectPath);
	// �v���W�F�N�g����ێ�
	data.projectName = string(pProjectName);

	return true;
}

void DataAccessor::GetTextCastNames(SdkData& data)
{
	const int CAST_TYPE = ct_Text;
	int api_ret = 0;

	data.textCastNames.clear();

	// �e�L�X�g�L���X�g�́i�u�����N���܂񂾁j�����擾����
	data.textCastCount = MxPluginPort_Cast_GetCastCount(CAST_TYPE);

	// �L���X�g�ԍ��̍ő�l�܂ŃL���X�g�ԍ����O����C���N�������g���Ȃ��瑖��
	for (int castIndex = 0; castIndex < data.textCastCount; castIndex++)
	{
		// �e�L�X�g�L���X�g���̎擾
		char name_buffer[MAX_PATH] = { 0 };

		api_ret = MxPluginPort_Cast_GetCastName(CAST_TYPE, castIndex, name_buffer, MAX_PATH);

		// �e�L�X�g�L���X�g���̋󗓂��c������K�v������̂ŁA
		// �擾�Ɏ��s�����ꍇ�A�����O�̕�����Ƃ���

		string castname = string(name_buffer);
		data.textCastNames.push_back(castname);
	}

	return;
}

bool DataAccessor::WriteRatioDataTableScript(WriteData& writeData)
{
	bool result = true;
	int mxResult;
	int castNo;

	// �������O�̃X�N���v�g�L���X�g�̗L�����m�F����
	mxResult = MxPluginPort_Cast_FindCast(ct_Script, (char*)writeData.scriptName.c_str());
	if (mxResult >= 0) {
		// ��������
		// �L���X�g�ԍ���ݒ�
		castNo = mxResult;
	}
	else
	{
		// �L���X�g��������Ȃ�

		// �X�N���v�g�L���X�g�́i�u�����N���܂񂾁j�����擾����
		mxResult = MxPluginPort_Cast_GetCastCount(ct_Script);
		if (mxResult < 0) {
			// �L���X�g�ԍ����Ȃ�
			result = false;
			goto FUNC_ERROR;
		}

		// �L���X�g�ԍ��Ƃ��Ė����Ɉ�u�����N���󂯂��ԍ����w�肷��
		castNo = mxResult + 1;

		// �X�N���v�g�L���X�g�̍쐬
		mxResult = MxPluginPort_Cast_CreateScript(castNo, (char*)writeData.scriptName.c_str());
		if (mxResult < 0) {
			// �L���X�g�쐬���s
			result = false;
			goto FUNC_ERROR;
		}
	}

	// �R�[�h��������
	mxResult = MxCast_Script_SetCode(castNo, (void*)writeData.tableScriptCode.c_str());
	if (mxResult < 0) {
		result = false;
		goto FUNC_ERROR;
	}


FUNC_ERROR:

	return result;
}
