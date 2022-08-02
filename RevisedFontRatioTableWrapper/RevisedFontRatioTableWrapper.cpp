#define WRAPPER

#include "RevisedFontRatioTableWrapper.h"
#pragma managed

#include <iostream>
#include <string>
#include <gcroot.h>
#include <tchar.h>
#include <msclr/marshal_cppstd.h>

#using <System.dll>
#using <System.Core.dll>
#using <System.Linq.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#using <System.Reflection.dll>
#using <mscorlib.dll>
#using <netstandard.dll>
#using <System.Runtime.dll>

using namespace msclr::interop;
using namespace System;
using namespace System::IO;
using namespace System::Linq;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Reflection;
using namespace System::Collections::Generic;

//void DEBUG_LOG(System::String^ msg) {
//	StreamWriter^ sw = nullptr;
//	try{
//		String^ path = Environment::GetFolderPath(Environment::SpecialFolder::Personal);
//		DirectoryInfo^ dirInfo = gcnew DirectoryInfo(path);
//		//dirInfo = dirInfo->Parent;
//		String^ logPath = dirInfo->ToString() + "\\..\\OutlineBuilder\\sgwrap.log";
//		sw = gcnew StreamWriter(logPath, true);
//
//		sw->WriteLine("[" + System::DateTime::Now + "]" + msg);
//		sw->Flush();
//	}
//	catch (Exception^)
//	{
//
//	}
//	finally{
//		if (sw != nullptr) {
//			sw->Close();
//		}
//	}
//}

namespace RevisedFontRatioTableWrapper
{

	public class WrapperImpl : public Wrapper
	{
		const char* GUI_DLL = "\\RevisedFontRatioTableDotNet.dll";

	public:
		/// <summary>
		/// ���b�o�[�����N���X�R���X�g���N�^
		/// </summary>
		/// <returns></returns>
		WrapperImpl()
		{
			//DEBUG_LOG("WrapperImpl::WrapperImpl start");
			//MessageBox::Show("WrapperImpl::WrapperImpl start");

			System::String^ loc = Assembly::GetExecutingAssembly()->Location;
			loc = Path::GetDirectoryName(loc) + gcnew System::String(GUI_DLL);
			//DEBUG_LOG("Asm Location: " + loc);
			//MessageBox::Show(loc, "Asm Location");

			Assembly^ assembly;
			try {
				assembly = Assembly::UnsafeLoadFrom(loc);
			}
			catch (System::Exception^) {
				//DEBUG_LOG("WrapperImpl::WrapperImpl LoadForm error: " + e->ToString());
				throw std::exception("DLL Load Error");
			}
			Type^ type = assembly->GetType("RevisedFontRatioTableDotNet.ManagedClass");
			Object^ obj = Activator::CreateInstance(type);

			managedObject = obj;
			managedType = type;
			//DEBUG_LOG("WrapperImpl::WrapperImpl end");
			//MessageBox::Show("WrapperImpl::WrapperImpl end");
		}

		/// <summary>
		/// �c�[�����O�����J�n
		/// </summary>
		/// <returns></returns>
		bool BeginProcess() override {
			MethodInfo^ methodInfo = managedType->GetMethod("BeginProcess");
			Object^ retObj = methodInfo->Invoke(managedObject, nullptr);
			bool result = safe_cast<bool>(retObj);

			return result;
		}

		/// <summary>
		/// UI���ւ̃v���W�F�N�g�t�@�C���p�X�A���̂̓]��
		/// </summary>
		/// <param name="filepath"></param>
		/// <param name="projectname"></param>
		void UploadProjectInfo(char* filepath, char* projectname) override {
			MethodInfo^ methodInfo = managedType->GetMethod("UploadProjectInfo");

			String^ filepathStr = nullptr;
			if (filepath != nullptr) {
				filepathStr = gcnew String(filepath);
			}
			String^ projectnameStr = nullptr;
			if (projectname != nullptr) {
				projectnameStr = gcnew String(projectname);
			}

			array<Object^>^ arg = gcnew array<Object^>(2);
			arg[0] = filepathStr;
			arg[1] = projectnameStr;
			methodInfo->Invoke(managedObject, arg);

			return;
		}

		/// <summary>
		/// .NET���ւ̃r�b�g�}�b�v�L���X�g�����X�g�̓]��
		/// </summary>
		/// <param name="names_len">���X�g��</param>
		/// <param name="names">�X�N���v�g�����X�g</param>
		void UploadTextCastNames(int names_len, char** names) override {
			MethodInfo^ methodInfo = managedType->GetMethod("UploadTextCastNames");

			array<String^>^ nameArray = gcnew array<String^>(names_len);
			for (int i = 0; i < names_len; i++) {
				nameArray[i] = gcnew String(names[i]);
			}

			array<Object^>^ arg = gcnew array<Object^>(1);
			arg[0] = nameArray;
			methodInfo->Invoke(managedObject, arg);
		}

		/// <summary>
		/// .NET����蕶����f�[�^�̎擾�i���ʏ����A�߂�l�󂯎�葤��delete[]���K�v
		/// </summary>
		/// <param name="methodName">������擾���\�b�h��</param>
		/// <returns>������f�[�^</returns>
		char* DownloadString(const std::string& methodName) override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>(methodName);
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			String^ stringManaged = safe_cast<String^>(obj);

			std::string stringUnmanaged = marshal_as<std::string>(stringManaged);
			size_t bufLen = stringUnmanaged.length() + 1;
			char* pStr = new char[bufLen];
			strcpy_s(pStr, bufLen, stringUnmanaged.c_str());

			return pStr;
		}

	private:
		gcroot<Object^> managedObject;
		gcroot<Type^> managedType;
	};

	/// <summary>
	/// GUI�Ƃ�IF���b�p�[�̐����擾
	/// </summary>
	/// <returns></returns>
	std::unique_ptr<Wrapper> CreateWrapper()
	{
		std::unique_ptr<Wrapper> wrapperImpl;
		try {
			wrapperImpl = std::make_unique<WrapperImpl>();

		}
		catch (std::exception& e) {
			throw e;
		}
		return wrapperImpl;
	}
}

std::unique_ptr<RevisedFontRatioTableWrapper::Wrapper> wrapper = nullptr;

/// <summary>
/// ���b�p�[����
/// </summary>
/// <returns></returns>
bool CreateWrapper() {
	bool result = false;

	try {
		//DEBUG_LOG("::CreateWrapper start");
		wrapper = RevisedFontRatioTableWrapper::CreateWrapper();
		result = true;
	}
	catch (std::exception&) {
		wrapper = nullptr;
		result = false;
	}

	return result;
}

/// <summary>
/// �c�[�����O�����J�n
/// </summary>
/// <returns></returns>
bool BeginProcess()
{
	if (wrapper != nullptr)
	{
		return wrapper->BeginProcess();
	}
	return false;
}

/// <summary>
/// UI���ւ̃v���W�F�N�g�t�@�C���p�X�A���̂̓]��
/// </summary>
/// <param name="filepath">�v���W�F�N�g�t�@�C���p�X</param>
/// <param name="projectname">�v���W�F�N�g��</param>
void UploadProjectInfo(char* filepath, char* projectname)
{
	if (wrapper != nullptr)
	{
		wrapper->UploadProjectInfo(filepath, projectname);
	}
}

/// <summary>
/// .NET�ւ̃e�L�X�g�L���X�g���]������
/// </summary>
/// <param name="names_len">�L���X�g���O��</param>
/// <param name="names">�L���X�g���z��</param>
void UploadTextCastNames(int names_len, char** names)
{
	if (wrapper != nullptr)
	{
		wrapper->UploadTextCastNames(names_len, names);
	}
}

/// <summary>
/// .NET������̕�����̎擾
/// </summary>
/// <param name="methodName">.NET��������o�̓��\�b�h��</param>
/// <returns>������</returns>
char* DownloadString(const std::string& methodName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadString(methodName);
	}
	return nullptr;
}
