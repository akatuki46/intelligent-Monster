#pragma once

#include "Scene.h"
#include <random>
#include "LodingScene.h"
#include <vector>
#include <map>
#include "GameObject.h"

class Manager
{
private:
	static class Scene* m_Scene;
	static std::map<std::string, GameObject*> m_KeepObject;

	static int m_DethCnt;
	static int m_EneHp;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static class Scene* GetScene() { return m_Scene; }

	template <typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = new T;
		m_Scene->Init();
	}

	static void SetSceneLoad(std::function<void(void)> function)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = new LodingScene;
		m_Scene->InitLoad(function);
	}


	static float randomfloat(double low, double high)
	{
		std::random_device rnd;     // 非決定的な乱数生成器でシード生成機を生成
		static std::mt19937_64 mt64(rnd());
		std::uniform_real_distribution<double> dist(low, high);
		return dist(mt64);
	}

	static int randomint(int low, int high)
	{
		std::random_device rnd;     // 非決定的な乱数生成器でシード生成機を生成
		static std::mt19937_64 mt64(rnd());
		std::uniform_int_distribution<int> dist(low, high);
		return dist(mt64);
	}

	static void  SetEneHp(int Hp) { m_EneHp = Hp; }
	static int GetEneHp() { return m_EneHp; }

	static void AddDethCnt() { m_DethCnt++; }
	static void ResetDethCnt() { m_DethCnt = 0; }
	static int GetDethCnt() { return m_DethCnt; }
};