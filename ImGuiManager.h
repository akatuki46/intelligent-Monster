#pragma once

class ImGuiManager
{
private:
	static bool m_show_Manager;
	static int  m_DrawLayer;
public:

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};

