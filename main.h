#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOMINMAX
#include <windows.h>
#include <assert.h>



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#define DIRECTINPUT_VERSION 0x0800		// åxçêëŒèà
#include "dinput.h"
#include "mmsystem.h"
#pragma warning(pop)

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"


#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "xinput.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

//âÊéøå¸è„í«â¡çÄñ⁄
#define SCREEN_WINDOWMODE_RATE_WIDTH	(0.8f)
#define SCREEN_WINDOWMODE_RATE_HEIGHT	(0.8f)
#define SCREEN_RESOLUTION_WIDTH (GetSystemMetrics(SM_CXSCREEN))
#define SCREEN_RESOLUTION_HEIGHT (GetSystemMetrics(SM_CYSCREEN))
#define SCREEN_WIDTH	(float)(GetSystemMetrics(SM_CXSCREEN) * SCREEN_WINDOWMODE_RATE_WIDTH)
#define SCREEN_HEIGHT	(float)(GetSystemMetrics(SM_CYSCREEN) * SCREEN_WINDOWMODE_RATE_HEIGHT)


HWND GetWindow();
