//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include <XInput.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�{�^���ꗗ

// XINPUT_GAMEPAD_DPAD_UP			�\���L�[��
// XINPUT_GAMEPAD_DPAD_DOWN			�\���L�[��
// XINPUT_GAMEPAD_DPAD_LEFT			�\���L�[��
// XINPUT_GAMEPAD_DPAD_RIGHT		�\���L�[�E
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		L�X�e�B�b�N��������
// XINPUT_GAMEPAD_RIGHT_THUMB		R�X�e�B�b�N��������
// XINPUT_GAMEPAD_LEFT_SHOULDER		L�{�^��
// XINPUT_GAMEPAD_RIGHT_SHOULDER	R�{�^��
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//�X�e�B�b�N�͈̔�
// X�� ��-32768�@�E 32767
// Y�� �� 32767�@��-32768

//�g���K�[�͈̔�
// 0 �` 255

// �o�C�u���[�V�����͈̔�
// 0 �` 255

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPadInput(HINSTANCE hInst, HWND hWnd);
void UninitPadInput(void);
void UpdatePadInput(void);

int GetThumbLeftX(int padNo);
int GetThumbLeftY(int padNo);
int GetThumbRightX(int padNo);
int GetThumbRightY(int padNo);

void SetLeftVibration(int padNo, int speed);
void SetRightVibration(int padNo, int speed);
void SetVibration(int padNo, int speed);
void StopVibration(int padNo);

int GetLeftTrigger(int padNo);
int GetRightTrigger(int padNo);

BOOL IsButtonXinputPressed(int padNo, DWORD button);
BOOL IsButtonXinputTriggered(int padNo, DWORD button);

