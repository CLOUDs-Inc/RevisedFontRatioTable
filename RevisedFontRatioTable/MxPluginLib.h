#ifndef	D_MXPLUGINLIB_H
#define	D_MXPLUGINLIB_H

#pragma once

typedef float MXPLUGIN_VALUE;
typedef struct _MXPLUGIN_VECTOR3D {
	float x;
	float y;
	float z;
} MXPLUGIN_VECTOR3D;

//===============================================
//MxPluginPort_System_GetSDKVersion�Ŏg�p�����`
//===============================================
#define		gsv_EXEVersion	(0)		// EXE���\�[�X�̃o�[�W�������(64bit)���擾
#define		gsv_FuncVersion	(1)		// 0����n�܂�o�[�W�����ԍ�(32bit)���擾
typedef enum TSDKVersionList_t {
	svl_Unassigned = 0,
	svl_20160125 = 1,			// 2016.01.25��SDK�̏ꍇ
	svl_20200100 = 2,			// 2020�N01����SDK�̏ꍇ
	svl_20200300 = 3				// 2020�N03����SDK�̏ꍇ
} TSDKVersionList;

//========================================
//MxPluginPort_System_AddMemu�Ŏg�p�����`
//========================================
#define		am_Import				(0)
#define		am_Export				(1)
#define		am_Runtime				(2)
#define		am_RootScore			(3)
#define		am_SubScore				(4)
#define		am_AnyScore				(5)
#define		am_Tool_Root			(6)
#define		am_Tool_Plugin			(7)
#define		am_Event_SaveMXPFile	(0x100)
#define		am_Event_SaveProject	(0x100)
#define		am_Event_LoadProject	(0x101)
#define		am_Event_CloseProject	(0x102)
#define		am_Event_NewProject		(0x103)
#define		am_Event_CastRename		(0x200)
#define		am_Event_CastDelete		(0x201)
#define		am_When_Running			(0x20000000)
#define		am_When_Anytime			(0x40000000)
#define		am_PreEvent				(0x80000000)

//==========================================
//MxPluginPort_System_Progress�Ŏg�p�����`
//==========================================
typedef enum TSetProgressCommand_t {
	spg_SetVisible = 0x00,
	spg_SetProgress = 0x01,
	spg_SetMaxValue = 0x02,
	spg_SetMessage = 0x03
} TSetProgressCommand;

//========================================
//MxPluginPort_Project_Init�Ŏg�p�����`
//========================================
#define		pi_Blank		0			//���S�Ƀu�����N�̃R���e���c
#define		pi_ScoreOnly	1			//���[�g�X�R�A�݂̂̃R���e���c
#define		pi_ScoreCast	2			//���[�g�X�R�A�ƃJ�����Ɗ���
#define		pi_NonDialog	0x80000000	//�x���_�C�A���O��\�����Ȃ�

//================================================
//MxPluginPort_Project_LoadCabinet�Ŏg�p�����`
//================================================
#define		lc_Cast_OverWrite		0x00000001	//�L���X�g�����d�������ꍇ�A�ォ�烍�[�h�����L���X�g�ŏ㏑������
#define		lc_Cast_Rename			0x00000002	//�L���X�g�����d�������ꍇ�A�ʖ��Ń��[�h����
#define		lc_Cast_UseOldRename	0x00000003	//�L���X�g�����d�������ꍇ�A�����̃f�[�^���g�p���A�ʖ��Ń��[�h����
#define		lc_Cast_UseOldRelease	0x00000004	//�L���X�g�����d�������ꍇ�A�����̃f�[�^���g�p���A�L���r�l�b�g���̃L���X�g�͔j������

#define		lc_Score_OverWrite		0x00010000	//�X�R�A�����d�������ꍇ�A�ォ�烍�[�h�����X�R�A�ŏ㏑������
#define		lc_Score_Rename			0x00020000	//�X�R�A�����d�������ꍇ�A�ʖ��Ń��[�h����
#define		lc_Score_UseOldRelease	0x00040000	//�X�R�A�����d�������ꍇ�A�����̃f�[�^���g�p���A�L���r�l�b�g���̃X�R�A�͔j������

#define		lc_Track_SelectScoreNum 0x80000000	//MxPluginPort_Project_LoadCabinetEx��p:

//========================================
//MxPluginPort_Cast_CreateLight�Ŏg�p�����`
//========================================
#define		lt_Directional	0			//���s��
#define		lt_Point		1			//�_����
#define		lt_Spot			2			//�X�|�b�g���C�g
#define		lt_Ambient		3			//����

//========================================
//MxPluginPort_Track_GetFrameData,
//MxPluginPort_Track_SetFrameData,
//MxPluginPort_Track_Trim�Ŏg�p�����`
//========================================
#define		fd_3DTrack		0x00		/*	TFD_3DTrackData	*/
#define		fd_CastNumber	0x01		/*	int				*/
#define		fd_2DPosition	0x02		/*	POINT			*/
#define		fd_Script		0x03		/*	int				*/
#define		fd_2DSize		0x04		/*	POINT			*/
#define		fd_2DAlpha		0x05		/*	int				*/
#define		fd_Filter		0x06		/*	int				*/
#define		fd_2DAngle		0x07		/*	float			*/

//========================================
//MxPluginPort_LoopTrack_GetValue,
//MxPluginPort_LoopTrack_SetValue�Ŏg�p�����`
//========================================
typedef enum TLoopTrackData_t {
	ld_None = 0,				//�����Ȃ�
	ld_Top = 1,				//���[�v��[
	ld_Middle = 2,				//���[�v�̒�
	ld_End = 3,				//���[�v�I�[
	ld_Single = 4				//�P�t���[���̒��Ń��[�v
} TLoopTrackData;

//========================================
//MxPluginPort_Track_SetAttribute,
//MxPluginPort_Track_GetAttribute�Ŏg�p�����`
//========================================
#define		ta_TrackVisible 0			//�g���b�N�̉��E�s��
#define		ta_TrackCanEdit	1			//�ҏW�\�E�s�\

//========================================
//�L���X�g�̌^�̒�`
//========================================
#define		ct_Model		(0)				//���f��
#define		ct_Texture		(1)				//�e�N�X�`��
#define		ct_Bitmap		(2)				//�r�b�g�}�b�v
#define		ct_Text			(3)				//�e�L�X�g
#define		ct_Wave			(4)				//���ʉ�
#define		ct_Midi			(5)				//MIDI
#define		ct_Script		(6)				//�X�N���v�g
#define		ct_Camera		(7)				//�J����
#define		ct_Light		(8)				//���C�g
#define		ct_Movie		(9)				//Movie
#define		ct_Subscore		(10)			//�T�u�X�R�A�g���b�N  (���z�L���X�g)
#define		ct_Sound3D		(11)			//3DSound
#define		ct_WaveEx		(12)			//�g��Wave�g���b�N	  (���z�L���X�g)
#define		ct_Listener		(13)			//���L���X�g
#define		ct_MovieCtrl	(14)			//MovieI����g���b�N	 (���z�L���X�g)
#define		ct_Material		(15)			//�}�e���A���g���b�N  (���z�L���X�g)
#define		ct_MovieBill	(16)			//�r���{�[�h���[�r�[  (���z�L���X�g)
#define		ct_BilTexAnm	(17)			//�r���{�[�h�e�N�X�`���̃A�j���[�V����	(���z�L���X�g)
#define		ct_TexNumAnm	(18)			//���f���̃e�N�X�`���ԍ��̃A�j���[�V����  (���z�L���X�g)
#define		ct_ModelWrap	(19)			//���f���̃e�N�X�`���}�b�s���O�̃A�j���[�V����	(���z�L���X�g)
#define		ct_ModelNum		(20)			//���f���ԍ��̃A�j���[�V���� (���z�L���X�g)
#define		ct_Transition	(21)			//�g�����W�V���� (���z�L���X�g)
#define		ct_TransForm	(ct_Transition)	//�����O�ύX
#define		ct_Procedural	(29)			//�v���V�[�W���[�L���X�g

//========================================
//3D���W�������g���b�N�̃t���[�����̒�`
//========================================
#define		kfd_Position		0x01
#define		kfd_Rotate			0x02
#define		kfd_Scale			0x04
#define		kfd_Visible			0x08
#define		kfd_PositionSmooth	0x10
#define		kfd_RotateSmooth	0x20
#define		kfd_ScaleSmooth		0x40

typedef struct	tagFD_3DTrackData {
	MXPLUGIN_VECTOR3D	Position;	//�L���X�g�̍��W//
	MXPLUGIN_VECTOR3D	Rotate;		//�L���X�g�̉�]//
	MXPLUGIN_VECTOR3D	Scale;		//�L���X�g�̃X�P�[��//
	DWORD				KeyData;
} TFD_3DTrackData;

//========================================
//�L���X�g�̃v���p�e�B����
//========================================
#define c_Cast_OverwriteFlag		(0x80000000)

//���f���L���X�g
#define c_Model_Texture				0x10	//�e�N�X�`�������蓖�Ă�
#define MxCast_Model_SetTexture(CastNum_Model,GroupNum,MultiTexNum,CastNum_Tex) MxPluginPort_CastPropety_SetDataInt(ct_Model,CastNum_Model,c_Model_Texture,CastNum_Tex,GroupNum,MultiTexNum)

//�e�N�X�`���L���X�g
#define cp_Texture_TransparentColor 0x10	//�e�N�X�`���̓��ߐF 0x0000FF=��  0x00FF00=�� 0xFF0000=�� �s����: -1

//�r�b�g�}�b�v�L���X�g
typedef enum TBitmapPropertyType_t {
	cp_Bitmap_TransparentColor = 0x10,	//�r�b�g�}�b�v�̓��ߐF 0x0000FF=��	0x00FF00=�� 0xFF0000=�� �s����: -1
	cp_Bitmap_AlphaEnabled = 0x11,	//���������@�\��L���ɂ��� 0=���� 1=�L��
	cp_Bitmap_FixSize = 0x12,	//�T�C�Y�Œ胂�[�h	0=�T�C�Y�� 1=�T�C�Y�Œ�
	cp_Bitmap_ClickEnabled = 0x13,	//�N���b�N����		0=OFF 1=ON
	cp_Bitmap_GhostMode = 0x14,	//�S�[�X�g���[�h	0=OFF 1=ON
	cp_Bitmap_DelayLoad = 0x15,	//�x���ǂݍ���		0=OFF 1=ON
	cp_Bitmap_Backward = 0x16,	//�w�i�ɔz�u		0=OFF 1=ON
	cp_Bitmap_StayOnRAM = 0x17,	//RAM�ɔz�u����		0=OFF 1=ON
	cp_Bitmap_Use16BitColor = 0x18,	//16bit bitmap���g�p����	0=OFF 1=ON
	cp_Bitmap_Use32BitColor = 0x19,	//32bit bitmap���g�p����	0=OFF 1=ON
	cp_Bitmap_PaletteLink = 0x1A,	//Palette link		�L���X�g�ԍ�
	cp_Bitmap_GetWidth = 0x1B,	//�r�b�g�}�b�v�L���X�g�̕�
	cp_Bitmap_GetHeight = 0x1C	//�r�b�g�}�b�v�L���X�g�̍���
} TBitmapPropertyType;

BOOL MxCast_Bitmap_SetDataInt(int CastNumber, TBitmapPropertyType PropertyType, int Value);	//�L���X�g�̃v���p�e�B��ݒ肷��
BOOL MxCast_Bitmap_GetDataInt(int CastNumber, TBitmapPropertyType PropertyType, int* Value);	//�L���X�g�̃v���p�e�B���擾����

//�e�L�X�g�L���X�g
typedef enum TTextPropertyType_t {
	cp_Text_FontColor = 0x10,	//�e�L�X�g�̕����̐F 0x0000FF=��  0x00FF00=�� 0xFF0000=��
	cp_Text_BackColor = 0x11,	//�e�L�X�g�̔w�i�̐F 0x0000FF=��  0x00FF00=�� 0xFF0000=��
	cp_Text_FontHeight = 0x12,	//�e�L�X�g�Ŏg�p����t�H���g�̍���
	cp_Text_FontSize = 0x13,	//�e�L�X�g�Ŏg�p����t�H���g�̃T�C�Y
	cp_Text_FontStyle = 0x14,	//�e�L�X�g�Ŏg�p����t�H���g�̃X�^�C��(TTextFontStyleType���w��ł���)
	cp_Text_FontName = 0x15,	//�e�L�X�g�Ŏg�p����t�H���g�̖��O(������ւ̃|�C���^���w��)
	cp_Text_FontCharSet = 0x16,	//�e�L�X�g�Ŏg�p����t�H���g�̃L�����N�^�Z�b�g
	cp_Text_Transparent = 0x17,	//�e�L�X�g�̔w�i�����߂��邩�ǂ������w�� 0=�s���� 1=����
	cp_Text_ItemDistance = 0x18,	//�e�L�X�g�̍s��
	cp_Text_Backward = 0x19,	//�X�e�[�W�E�B���h�E�Ō���ɔz�u���邩���w�� 0=�O���ɔz�u 1=����ɔz�u
	cp_Text_AlphaEnabled = 0x1A,	//���������@�\��L���ɂ��� 0=���� 1=�L��
	cp_Text_CenterX = 0x1B,	//��]�̒��S�ʒu X ���W
	cp_Text_CenterY = 0x1C,	//��]�̒��S�ʒu Y ���W
	cp_Text_FixSize = 0x1D,	//�T�C�Y�Œ胂�[�h 0=�T�C�Y�� 1=�T�C�Y�Œ�
	cp_Text_TextData = 0x1E,	//�e�L�X�g�̓��e���w��(������ւ̃|�C���^���w��)
	cp_Text_GetWidth = 0x1F,	//�e�L�X�g�L���X�g�S�̂̕�
	cp_Text_GetHeight = 0x20,	//�e�L�X�g�L���X�g�S�̂̍���
	cp_Text_StringEncode = 0x21,	//�����R�[�h(TTextStringEncodeType���w��ł���)
	cp_Text_Alignment = 0x22,	//�e�L�X�g�̔z�u(TTextAlignment���w��ł���)
	cp_Text_AlignmentWidth = 0x23,	//�e�L�X�g�����񂹁E�����񂹁E�E�񂹂ɂ����ۂ̃e�L�X�g��
	cp_Text_ClickEnabled = 0x24,	//�N���b�N����		0=OFF 1=ON
	cp_Text_Antialias = 0x25	//�A���`�G�C���A�X	0=OFF 1=ON
} TTextPropertyType;

typedef enum TTextStringEncodeType_t {
	set_ANSI = 0x00,
	set_UTF = 0x01
} TTextStringEncodeType;

typedef enum TTextFontStyleType_t {
	fs_Regular = 0x00,	//�ʏ핶��
	fs_Bold = 0x01,	//����
	fs_Italic = 0x02,	//�Α�
	fs_BoldItalic = 0x03	//����+�Α�
} TTextFontStyleType;

typedef enum TTextAlignment_t {
	talign_None = 0x00,		//�A���C�����g���������^�A���C�����g�����w��Ȃ�
	talign_Center = 0x01,		//����
	talign_Right = 0x02,		//�E��
	talign_Left = 0x03,		//����
	talign_Center_Default = 0x11,		//�����E�f�t�H���g�w��
	talign_Right_Default = 0x12,		//�E�񂹁E�f�t�H���g�w��
	talign_Left_Default = 0x13,		//���񂹁E�f�t�H���g�w��
	talign_Negate = 0x80		//�A���C�����g�p���ł�����
} TTextAlignment;

BOOL MxCast_Text_SetDataInt(int CastNumber, TTextPropertyType PropertyType, int  Value);	//�L���X�g�̃v���p�e�B��ݒ肷��
BOOL MxCast_Text_GetDataInt(int CastNumber, TTextPropertyType PropertyType, int* Value);	//�L���X�g�̃v���p�e�B���擾����

//�X�N���v�g�L���X�g
#define cp_Script_ScriptData		0x10	//�X�N���v�g�̓��e���w��(������ւ̃|�C���^���w��)
#define MxCast_Script_SetCode(CastNum,Value)			MxPluginPort_CastPropety_SetDataPtr (ct_Script,CastNum,cp_Script_ScriptData		,Value)
#define cp_Script_Encode			0x11
#define cp_Script_External			0x12

typedef enum TScriptEncodeType_t {
	script_encode_ANSI = 0x00,
	script_encode_UTF8 = 0x01,
	script_encode_UTF8_BOM = 0x02
} TScriptEncodeType;

typedef enum TScriptExternalFile_t {
	script_file_Internal = 0x00,
	script_file_External = 0x01
} TScriptExternalFile;


//���C�g�L���X�g
#define cp_Light_Color				0x10	//���C�g�̐F 0x0000FF=��  0x00FF00=�� 0xFF0000=��
#define cp_Light_DropOffRateA		0x11	//���C�g�̌�����A 0.0�`100.0
#define cp_Light_DropOffRateB		0x12	//���C�g�̌�����B 0.0�`100.0
#define cp_Light_DropOffRateC		0x13	//���C�g�̌�����C 0.0�`1.0
#define cp_Light_Distance			0x14	//���C�g�̓��B���� 0.0�`��
#define cp_Light_CutOffAngle		0x15	//���C�g�̓����̏Ǝˉ~���̊p�x 0�`M_PI
#define cp_Light_CutOffAnglePhi		0x16	//���C�g�̊O���̏Ǝˉ~���̊p�x 0�`M_PI
#define cp_Light_LightChannels		0x17	//���C�g�̃`�����l��
#define cp_Light_MaterialTrack		0x18	//�}�e���A���g���b�N�̉e�����󂯂邩�ǂ��� (0=�e�����󂯂Ȃ� 1=�e�����󂯂�)

#define MxCast_Light_SetColor(CastNum,Value)			MxPluginPort_CastPropety_SetDataInt  (ct_Light,CastNum,cp_Light_Color			,Value)
#define MxCast_Light_SetDropOffRateA(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_DropOffRateA	,Value)
#define MxCast_Light_SetDropOffRateB(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_DropOffRateB	,Value)
#define MxCast_Light_SetDropOffRateC(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_DropOffRateC	,Value)
#define MxCast_Light_SetDistance(CastNum,Value)			MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_Distance		,Value)
#define MxCast_Light_SetCutOffAngle(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_CutOffAngle		,Value)
#define MxCast_Light_SetCutOffAnglePhi(CastNum,Value)	MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_CutOffAnglePhi	,Value)
#define MxCast_Light_SetLightChannels(CastNum,Value)	MxPluginPort_CastPropety_SetDataInt  (ct_Light,CastNum,cp_Light_LightChannels	,Value)
#define MxCast_Light_SetMaterialTrack(CastNum,Value)	MxPluginPort_CastPropety_SetDataInt  (ct_Light,CastNum,cp_Light_MaterialTrack	,Value)

#define MxCast_Light_GetColor(CastNum,Value)			MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_Color			,Value)
#define MxCast_Light_GetDropOffRateA(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_DropOffRateA		,Value)
#define MxCast_Light_GetDropOffRateB(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_DropOffRateB		,Value)
#define MxCast_Light_GetDropOffRateC(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_DropOffRateC		,Value)
#define MxCast_Light_GetDistance(CastNum,Value)			MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_Distance			,Value)
#define MxCast_Light_GetCutOffAngle(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_CutOffAngle		,Value)
#define MxCast_Light_GetCutOffAnglePhi(CastNum,Value)	MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_CutOffAnglePhi	,Value)
#define MxCast_Light_GetLightChannels(CastNum,Value)	MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_LightChannels	,Value)
#define MxCast_Light_GetMaterialTrack(CastNum,Value)	MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_MaterialTrack	,Value)

//========================================
//�t�H���g�̃X�^�C���ݒ�
//========================================
#define fs_BOLD						0x01
#define fs_ITALIC					0x02
#define fs_UNDERLINE				0x04
#define fs_STRIKEOUT				0x08

//========================================
//�e�N�X�`����ǂݍ��ގ��̃��T�C�Y�ݒ�
//========================================
#define tr_NONE						0x00
#define tr_NEAR						0x01
#define tr_ROUNDDOWN				0x02
#define tr_ROUNDUP					0x03

//========================================
//MxPluginPort_Score_Clear��Option�̒�`
//========================================
#define	sc_Track					0x01
#define	sc_LoopTrack				0x02
#define	sc_FrameLabel				0x04

/*================================================*/
/* MxPluginPort_Cast_CreateScriptEx��Option�̒�` */
/*================================================*/
#define	cse_Encode_ANSI				0x01
#define	cse_Encode_UTF8				0x02

/*===============================================*/
/* MxPluginPort_Project_CreateRuntimeFile �̒�` */
/*===============================================*/
#define	crm_MXEFile					0x00

typedef struct TMx_Project_CreateRuntimeFile_MXEOption_t {
	int Size;
	int Options;
} TMx_Project_CreateRuntimeFile_MXEOption;

#define	pcr_MXEOption_HideSaveDialog	(0x80000000)
#define pcr_MXEOption_RecommendSetting	(0x40000000)


/*======================================*/
/* MxPluginPort_Project_LoadFile �̒�` */
/*======================================*/
#define	lff_XML							(0x01)

//==========================================
//MxPluginPort_Score_SetAnnotationEncode�Ŏg�p�����`
//==========================================
typedef enum TAnnotationEncode_t {
	sae_ANSI = 0x00,
	sae_UTF16 = 0x01,
	sae_UNSET = 0xFFFFFFFF
} TAnnotationEncode;

//========================================
//�T�[�r�X�֐��̒�`
//========================================
typedef LRESULT(_cdecl* TMxWMCOPYDATAPROC)(HWND hWnd, UINT message, WPARAM wParam, COPYDATASTRUCT* cds);

BOOL MxPluginPort_System_GetSDKEXEVersion(unsigned long long int* Version);
BOOL MxPluginPort_System_GetSDKFuncVersion(TSDKVersionList* Version);

int	 MxPluginPort_System_AddMemu(HINSTANCE hinstDLL, char* Name, int Option, void* Reserved, void* UserParam);			//MxSDK�̃��j���[�ɔC�ӂ̃��j���[��ǉ�����
HWND MxPluginPort_System_GetHWnd(void);																				//���C���E�B���h�E�̃n���h�����擾
int  MxPluginPort_System_GetSDKLanguage(void);																				//�N�����Ă���SDK���p���(0)�����{���(1)���擾
BOOL MxPluginPort_System_MenuCaption(int hinstMenu, char* Caption);														//���j���[�̕������ݒ肷��
BOOL MxPluginPort_System_MenuEnabled(int hinstMenu, BOOL Enabled);														//���j���[�̗L��/������Ԃ�ݒ肷��
BOOL MxPluginPort_System_MenuVisible(int hinstMenu, BOOL Visible);														//���j���[�̕\��/��\����Ԃ�ݒ肷��
BOOL MxPluginPort_System_Paint(void* Reserved);																	//�R���e���c���X�V�������ʂ�\���ɔ��f������
BOOL MxPluginPort_System_ProcessMessages(void);																				//Windows�̃v���Z�X���b�Z�[�W����������(�g�p�͗v����)
BOOL MxPluginPort_System_ProgressMsg(char* Msg);
BOOL MxPluginPort_System_Progress(TSetProgressCommand Command, int Param);											//�v���O���X�E�B���h�E�𐧌䂷��

BOOL MxPluginPort_System_AttachEvent(HINSTANCE hinstDLL, UINT msg, TMxWMCOPYDATAPROC lpWMCopyDataProc);					//�C�x���g�ɃA�^�b�`����
BOOL MxPluginPort_System_TrimLabelName(char* Des, char* Sou);																//

BOOL MxPluginPort_Event_GetEventType(HINSTANCE hinstDLL, int* Type);													//���������C�x���g�̌`�����擾����
BOOL MxPluginPort_Event_GetMXPFileName(HINSTANCE hinstDLL, char** FileName);												//
BOOL MxPluginPort_Event_GetPreEvent(HINSTANCE hinstDLL, BOOL* Flag);													//
BOOL MxPluginPort_Event_GetUIHandle(HINSTANCE hinstDLL, int* Handle);													//�C�x���g�̔����v���ƂȂ���UI�̃n���h�����擾����

BOOL MxPluginPort_Event_Score_GetScoreTrack(HINSTANCE hinstDLL, int* ScoreNum, int* TrackNum);									//�X�R�A(�g���b�N)�ŃC�x���g�����������ꍇ�́A�X�R�A�ԍ��E�g���b�N�ԍ����擾����
BOOL MxPluginPort_Event_Score_GetSelectedCount(HINSTANCE hinstDLL, int* SelectedCount);											//�X�R�A(�g���b�N)�ŃC�x���g�����������ꍇ�́A�I�����Ă���g���b�N�����擾����
BOOL MxPluginPort_Event_Score_GetSelectedTrack(HINSTANCE hinstDLL, int Index, int* TrackNum);										//�X�R�A(�g���b�N)�ŃC�x���g�����������ꍇ�́A�I�����Ă���g���b�N�����擾����

BOOL MxPluginPort_Event_Cast_GetCastType(HINSTANCE hinstDLL, int* CastType);												//�L���X�g�n�C�x���g�ł̃L���X�g�^�C�v
BOOL MxPluginPort_Event_Cast_GetCastNumber(HINSTANCE hinstDLL, int* CastNumber);											//�L���X�g�n�C�x���g�ł̃L���X�g�ԍ�
BOOL MxPluginPort_Event_Cast_GetOldName(HINSTANCE hinstDLL, char** OldName);												//�L���X�g�̃��l�[���C�x���g�ł̌Â��L���X�g��
BOOL MxPluginPort_Event_Cast_GetNewName(HINSTANCE hinstDLL, char** NewName);												//�L���X�g�̃��l�[���C�x���g�ł̐V�����L���X�g��

BOOL MxPluginPort_Project_Init(int InitMode);																		//�R���e���c������������
BOOL MxPluginPort_Project_LoadCabinet(char* FileName, int Mode);															//�L���r�l�b�g�t�@�C�������[�h����
BOOL MxPluginPort_Project_LoadCabinetEx(char* FileName, int Mode, int* ScoreNumber, int* TrackNumber);						//�L���r�l�b�g�t�@�C�������[�h����
BOOL MxPluginPort_Project_SetScreenSize(int width, int height);															//�X�N���[���T�C�Y��ݒ肷��
char* MxPluginPort_Project_GetContentsPath(void);																				//���݂̃R���e���c�̃p�X���擾����
char* MxPluginPort_Project_GetContentsName(void);																				//���݂̃R���e���c�̖��O���擾����
BOOL MxPluginPort_Project_GetContentsSaved(void);																				//�R���e���c���ۑ�����āA���O���m�肵�Ă��邩���擾����
BOOL MxPluginPort_Project_GetContentsChanged(void);																				//�R���e���c���ύX����Ă��邩���擾����
BOOL MxPluginPort_Project_SetContentsChanged(void);
BOOL MxPluginPort_Project_ClearContentsChanged(void);
BOOL MxPluginPort_Project_SaveContents(char* FileName);																	//�R���e���c��ۑ�����
BOOL MxPluginPort_Project_LoadContents(char* FileName);																	//�R���e���c�����[�h����
BOOL MxPluginPort_Project_CreateRuntimeFile(char* FileName, int Format, void* Options);										//�����^�C���t�@�C�����쐬����
BOOL MxPluginPort_Project_GetContentsRunning(void);																				//�R���e���c���Đ������ǂ������擾����
BOOL MxPluginPort_Project_LoadFile(char* FileName, int Format, void* Options);										//�t�@�C�������[�h����

BOOL MxPluginPort_CLang_GetEnabled(void);
BOOL MxPluginPort_CLang_GetPathSRC(char** FileName);																	// C���ꃉ�C�u�����R���e���c�̃\�[�X�R�[�h�p�X���擾����
BOOL MxPluginPort_CLang_GetPathEvent(char** FileName);																	// C���ꃉ�C�u�����R���e���c�̃C�x���g�\�[�X�R�[�h�p�X���擾����
BOOL MxPluginPort_CLang_GetPathLib(char** FileName);																	// C���ꃉ�C�u�����R���e���c��MXCPPLib�p�X���擾����
BOOL MxPluginPort_CLang_GetPathOBJ(char** FileName);																	// C���ꃉ�C�u�����R���e���c��OBJ�t�@�C���p�X���擾����
BOOL MxPluginPort_CLang_GetFileNameConst(char** FileName);																	// C���ꃉ�C�u�����R���e���c�̒萔�t�@�C����(�L���X�g�ԍ��A�X�R�A�ԍ���)���擾����
BOOL MxPluginPort_CLang_GetFileNameEventSource(char** FileName);																	// C���ꃉ�C�u�����R���e���c�̃C�x���g�\�[�X�t�@�C�������擾����
BOOL MxPluginPort_CLang_GetFileNameEventHeader(char** FileName);																	// C���ꃉ�C�u�����R���e���c�̃C�x���g�w�b�_�t�@�C�������擾����

int  MxPluginPort_Cast_FindBlank(int CastType);																		//�󔒃L���X�g����������
int  MxPluginPort_Cast_FindBlankSince(int CastType, int CastNumber);														//�C�Ӕԍ��ȍ~�̋󔒃L���X�g����������
int  MxPluginPort_Cast_GetCastCount(int CastType);																		//�L���X�g�̐����擾����
int  MxPluginPort_Cast_CreateCamera(int CastNumber, char* CastName);													//�J�����L���X�g���쐬����
int  MxPluginPort_Cast_CreateLight(int CastNumber, char* CastName, int LightType);										//���C�g�L���X�g���쐬����
BOOL MxPluginPort_Cast_Delete(int CastType, int CastNumber, int Reserved);											//�L���X�g���폜����
BOOL MxPluginPort_Cast_UseCheck(int CastType, int CastNumber);														//�L���X�g���g�p����Ă��邩�`�F�b�N
int  MxPluginPort_Cast_GetCastName(int CastType, int CastNumber, char* CastName, int NameLength);						//�L���X�g�����擾����
int  MxPluginPort_Cast_SetCastName(int CastType, int CastNumber, char* NewName, BOOL OverWrite);							//�L���X�g����ݒ肷��
BOOL MxPluginPort_Cast_SaveToFile(int CastType, int CastNumbe, char* FileName, void* Reserved);							//�L���X�g���t�@�C���ɕۑ�����
int  MxPluginPort_Cast_FindCast(int CastType, char* CastName);														//�L���X�g�𕶎���Ō�������
int  MxPluginPort_Cast_CreateWave(int CastNumber, char* CastName, char* FileName, BOOL ExternalFile);					//Wave�L���X�g���쐬����
int  MxPluginPort_Cast_CreateText(int CastNumber, char* CastName);													//Text�L���X�g���쐬����
int  MxPluginPort_Cast_CreateScript(int CastNumber, char* CastName);													//�X�N���v�g�L���X�g���쐬����
int  MxPluginPort_Cast_CreateScriptEx(int CastNumber, char* CastName, char* FileName, int Options, int Reserved);			//�X�N���v�g�L���X�g���쐬����
int  MxPluginPort_Cast_CreateTexture(int CastNumber, char* CastName, char* FileName);										//Texture�L���X�g���쐬����
int  MxPluginPort_Cast_CreateTextureEx(int CastNumber, char* CastName, char* FileName, int Option, int Reserved);				//Texture�L���X�g���쐬����
int  MxPluginPort_Cast_CreateBitmap(int CastNumber, char* CastName, char* FileName);										//Bitmap�L���X�g���쐬����
BOOL MxPluginPort_Cast_Assigned(int CastType, int CastNumber);														//�L���X�g�����݂��邩��������
int  MxPluginPort_Cast_TrimCastName(int CastType, char* SourCastName, char* DestCastName, int NameLength);				//�L���X�g����SDK�œo�^���閼�O�ɕϊ�����
BOOL MxPluginPort_Cast_TrimFileName(int CastType, int CastNumber);														//�t�@�C���p�X���L���X�g������ɂ������̂ɍ����ւ���
BOOL MxPluginPort_Cast_Exchange(int CastType, int CastNumber1, int CastNumber2);									//�L���X�g�ԍ�����������

BOOL MxTest_PluginPort_Cast_TrimCastName(void);																				//

int  MxPluginPort_Score_GetScoreName(int ScoreNumber, char* ScoreName, int NameLength);									//�X�R�A�����擾����
int  MxPluginPort_Score_GetScoreCount(void);																				//�X�R�A�̐����擾����
int  MxPluginPort_Score_GetTrackCount(int ScoreNumber);																	//�g���b�N�̐����擾����
int  MxPluginPort_Score_CreateScore(char* ScoreName, int* TrackNumber);													//�V�K�X�R�A���쐬����
int  MxPluginPort_Score_CreateTrack(int ScoreNumber, int CastType, int CastNumber);										//�V�K�g���b�N���쐬����
BOOL MxPluginPort_Score_DeleteTrack(int ScoreNumber, int TrackNumber, int Reserved);										//�g���b�N���폜����
BOOL MxPluginPort_Score_Trim(int ScoreNumber);																	//�g���b�N�𐮗�����
int  MxPluginPort_Score_GetLength(int ScoreNumber);																	//�X�R�A�̒������擾����
int  MxPluginPort_Score_Find(char* ScoreName);																	//�X�R�A�𕶎���Ō���
BOOL MxPluginPort_Score_UpdateLength(int ScoreNumber);																	//�X�R�A�̒������X�V����
BOOL MxPluginPort_Score_Exchange(int ScoreNumber, int Track1, int Track2);											//�Q�̃g���b�N�̓��e����������
BOOL MxPluginPort_Score_DeleteScore(int ScoreNumber);																	//�X�R�A���폜����
int  MxPluginPort_Score_GetLabelName(int ScoreNumber, int FrameNumber, char* LabelName, int NameLength);				//�t���[�����x�������擾����
BOOL MxPluginPort_Score_SetLabelName(int ScoreNumber, int FrameNumber, char* LabelName, int Reserved);					//�t���[�����x������ݒ肷��
int  MxPluginPort_Score_GetLabelPosMax(int ScoreNumber);																	//�t���[�����x���̍Ō�̈ʒu���擾����
int  MxPluginPort_Score_FindFrameLabel(int ScoreNumber, char* LabelName);													//�t���[�����x������������
BOOL MxPluginPort_Score_Clear(int ScoreNumber, int Options);														//�X�R�A�̓��e����������
BOOL MxPluginPort_Score_MoveTrack(int ScoreNumber, int MoveTo, int MoveFrom);										//�g���b�N���X�R�A���ňړ�����
BOOL MxTest_MxPluginPort_Score_Clear(void);

BOOL MxPluginPort_Score_SetAnnotationEncode(int ScoreNumber, TAnnotationEncode Encode);
BOOL MxPluginPort_Score_SetAnnotationData(int ScoreNumber, int Page, void* Annotation);
BOOL MxPluginPort_Score_GetAnnotationEncode(int ScoreNumber, TAnnotationEncode* Encode);
BOOL MxPluginPort_Score_GetAnnotationData(int ScoreNumber, int Page, void** Annotation);
BOOL MxPluginPort_Score_GetAnnotationCount(int ScoreNumber, int* Page);
BOOL MxPluginPort_Score_ClearAnnotation(int ScoreNumber, int Page);
int  MxPluginPort_Score_InsertAnnotationData(int ScoreNumber, int Page, void* Annotation);
BOOL MxPluginPort_Score_RemoveAnnotationData(int ScoreNumber, int Page);

BOOL MxPluginPort_Track_GetCastType(int ScoreNumber, int TrackNumber, int* CastType);									//�g���b�N�Ɋ��蓖�Ă��Ă���L���X�g�̌^���擾����
BOOL MxPluginPort_Track_GetCastNumber(int ScoreNumber, int TrackNumber, int* CastNumber);									//�g���b�N�Ɋ��蓖�Ă��Ă���L���X�g�̔ԍ����擾����
BOOL MxPluginPort_Track_SetCastNumber(int ScoreNumber, int TrackNumber, int CastNumber);									//�g���b�N�Ɋ��蓖�Ă��Ă���L���X�g�̔ԍ����擾����
int  MxPluginPort_Track_GetLength(int ScoreNumber, int TrackNumber);													//�g���b�N�̒������擾����
BOOL MxPluginPort_Track_GetParent(int ScoreNumber, int TrackNumber, int* ParentTrackNumber);							//�g���b�N�̐e�q�֌W���擾����
BOOL MxPluginPort_Track_TestSetParent(int ScoreNumber, int ParentTrack, int ChildTrack);									//�g���b�N�̐e�q�֌W��ݒ�\���ǂ����𒲍�����
BOOL MxPluginPort_Track_SetParent(int ScoreNumber, int ParentTrack, int ChildTrack);									//�g���b�N�̐e�q�֌W��ݒ肷��
BOOL MxPluginPort_Track_GetFrameData(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data);			//�t���[���̓��e���擾����
BOOL MxPluginPort_Track_SetFrameData(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data);			//�t���[���̓��e��ݒ肷��
BOOL MxPluginPort_Track_Trim(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType);					//�g���b�N�̓��e�𐮗�����
BOOL MxPluginPort_Track_Assigned(int ScoreNumber, int TrackNumber);													//�g���b�N�����蓖�Ă��Ă��邩��������
int  MxPluginPort_Track_FindBlank(int ScoreNumber);																	//�󂫃g���b�N����������
BOOL MxPluginPort_Track_SetAttribute(int ScoreNumber, int TrackNumber, int AttrType, BOOL Value);							//�g���b�N�̑�����ݒ肷��
BOOL MxPluginPort_Track_GetAttribute(int ScoreNumber, int TrackNumber, int AttrType, BOOL* Value);						//�g���b�N�̑������擾����
int  MxPluginPort_Track_GetLabelName(int ScoreNumber, int TrackNumber, char* LabelName, int NameLength);				//�g���b�N���x�������擾����
BOOL MxPluginPort_Track_SetLabelName(int ScoreNumber, int TrackNumber, char* LabelName, int Reserved);					//�g���b�N���x������ݒ肷��
int  MxPluginPort_Track_FindTrackLabel(int ScoreNumber, char* LabelName);													//�g���b�N���x������������

int  MxPluginPort_LoopTrack_GetLength(int ScoreNumbe);																	//���[�v�g���b�N�̒������擾����
BOOL MxPluginPort_LoopTrack_GetValue(int ScoreNumber, int FrameNumber, TLoopTrackData* Value);							//���[�v�g���b�N�̃t���[���̒l���擾����
BOOL MxPluginPort_LoopTrack_SetValue(int ScoreNumber, int FrameNumber, TLoopTrackData Value);								//���[�v�g���b�N�̃t���[���̒l��ݒ肷��
BOOL MxPluginPort_LoopTrack_Trim(int ScoreNumber);																	//���[�v�g���b�N�𐮗�����

BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value);						//�L���X�g�̃v���p�e�B��ݒ肷��
BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2);			//�L���X�g�̃v���p�e�B��ݒ肷��
BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2, int Value3);	//�L���X�g�̃v���p�e�B��ݒ肷��
BOOL MxPluginPort_CastPropety_SetDataPtr(int CastType, int CastNumber, int PropertyType, void* Value);							//�L���X�g�̃v���p�e�B��ݒ肷��
BOOL MxPluginPort_CastPropety_SetDataFloat(int CastType, int CastNumber, int PropertyType, float Value);							//�L���X�g�̃v���p�e�B��ݒ肷��

BOOL MxPluginPort_Script_GetEncode(int CastNumber, TScriptEncodeType* Value);
BOOL MxPluginPort_Script_GetExternal(int CastNumber, TScriptExternalFile* Value);

BOOL MxPluginPort_CastPropety_GetData(int CastType, int CastNumber, int PropertyType, void* Value);							//�L���X�g�̃v���p�e�B��ݒ肷��
#define MXVEV3 MXPLUGIN_VECTOR3D
BOOL MxPluginPort_Primitive_QuadPolygon(int CastNumber, char* CastName, MXVEV3 V1, MXVEV3 V2, MXVEV3 V3, MXVEV3 V4);			//�l���_�|���S�����쐬
#undef MXVEV3

extern "C"
{
	__declspec(dllexport) BOOL _cdecl MxPlugin_SetProcAddress(int ID, void* FuncAddr);

}

#endif	/* D_MXPLUGINLIB_H */
