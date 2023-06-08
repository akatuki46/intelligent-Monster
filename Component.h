#pragma once
#include <string>

class GameObject;

class Component
{
protected:
	bool          m_Destroy = false;
	std::string   m_Name = "";

public:
	Component(){};
	Component(GameObject* Parent) :m_ParentObject(Parent) {}
	GameObject* m_ParentObject = nullptr;

	//ImGui•\Ž¦ƒtƒ‰ƒO
	bool          m_ImGuiDrawFlag = false;

	virtual ~Component(){}
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Uninit() {};

	void SetDestroy() { m_Destroy = true; }
	
	std::string GetName() { return m_Name; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

};

