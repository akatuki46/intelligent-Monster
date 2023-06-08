#include "ImGuiManager.h"
#include "Scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"

bool ImGuiManager::m_show_Manager = true;
int ImGuiManager::m_DrawLayer = 0;

void ImGuiManager::Init()
{
}

void ImGuiManager::Uninit()
{
}

void ImGuiManager::Update()
{
}

void ImGuiManager::Draw()
{

	ImGui::Begin("ImGuiManager", &m_show_Manager);                // Create a window called "Hello, world!" and append into it.

	if (ImGui::Button("CameraLayerDraw"))
		m_DrawLayer = 0;
	if (ImGui::Button("PlayLayerDraw"))
		m_DrawLayer = 1;
	if (ImGui::Button("UiLayerDraw"))
		m_DrawLayer = 2;
	Scene* scene = Manager::GetScene();

	std::vector<GameObject*> obj = scene->GetAllGameObjects(m_DrawLayer);
	for (GameObject* object : obj)
	{
		if (ImGui::TreeNode(object->GetTag().c_str()))
		{
			auto list = object->GetComponentList();
			for (auto Com : list)
			{
				ImGui::Checkbox(Com->GetName().c_str(), &Com->m_ImGuiDrawFlag);      // Edit bools storing our window open/close state

			}
			ImGui::TreePop();
			ImGui::Separator();
		}
	}

	ImGui::End();
}
