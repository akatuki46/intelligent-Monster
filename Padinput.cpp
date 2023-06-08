//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Padinput.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEADZONE			8200	// �e����25%�𖳌��]�[���Ƃ���
#define MAX_CONTROLLERS     4

struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitializeXinputPad(void);			// �p�b�h������
void UpdateXinputPad(void);
void UninitXinputPad(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CONTROLER_STATE g_Controllers[MAX_CONTROLLERS];


//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitPadInput(HINSTANCE hInst, HWND hWnd)
{
	// �p�b�h�̏�����
	InitializeXinputPad();

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitPadInput(void)
{
	// �p�b�h�̏I������
	UninitXinputPad();
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdatePadInput(void)
{
	// �p�b�h�̍X�V
	UpdateXinputPad();
}

//---------------------------------------- ������
HRESULT InitializeXinputPad(void)			// �p�b�h������
{
	//������
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	XInputEnable(true);

	return true;

}

//------------------------------------------- �I������
void UninitXinputPad(void)
{
	//�p�����[�^�̃��Z�b�g
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//�o�C�u���[�V������~
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &g_Controllers[i].vibration);

	XInputEnable(false);
}

//------------------------------------------ �X�V
void UpdateXinputPad(void)
{
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &g_Controllers[i].vibration);

		g_Controllers[i].lastState = g_Controllers[i].state;

		//����FERROR_SUCCESS�@0
		//�ڑ������FERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &g_Controllers[i].state);

		//�g���K�[�쐬
		g_Controllers[i].trigger.Gamepad.wButtons = ((g_Controllers[i].lastState.Gamepad.wButtons ^ g_Controllers[i].state.Gamepad.wButtons) & g_Controllers[i].state.Gamepad.wButtons);

		//L�X�e�B�b�NX���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbLX) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbLX = 0;
		//L�X�e�B�b�NY���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbLY) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbLY = 0;
		//R�X�e�B�b�NX���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbRX) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbRX = 0;
		//R�X�e�B�b�NY���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbRY) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbRY = 0;
	}
}

//�X�e�B�b�N�͈̔�
// X ��-32768�@�E 32767
// Y �� 32767�@��-32768
int GetThumbLeftX(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbLX;
}

int GetThumbLeftY(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbLY;
}

int GetThumbRightX(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbRX;
}

int GetThumbRightY(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbRY;
}

//�g���K�[�͈̔�
// 0 �` 255
int GetLeftTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int GetRightTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// �o�C�u���[�V�����͈̔�
// 0 �` 255
void SetLeftVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
}

void SetRightVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void SetVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void StopVibration(int padNo)
{
	g_Controllers[padNo].vibration.wLeftMotorSpeed = 0;
	g_Controllers[padNo].vibration.wRightMotorSpeed = 0;
}

//�{�^��������Ԃ̎擾
BOOL IsButtonXinputPressed(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].state.Gamepad.wButtons);
}

//�{�^���p���X��Ԃ̎擾
BOOL IsButtonXinputTriggered(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].trigger.Gamepad.wButtons);
}
