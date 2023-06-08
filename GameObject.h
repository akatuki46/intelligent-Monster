#pragma once
#include <list>
#include <typeinfo>   //型を調べるためには必要
#include "Component.h"
#include "main.h"
#include "BehaviorTree.h"
#include <cmath>
#include <random>

#define LIMIT_RATE 0.1f
#define LIMIT_OF_LIMIT 0.1f

class GameObject
{
protected:
	bool m_Destroy = false;
	std::string   m_Name = "";

	std::string   m_ParentName = "";

	//アニメーション用変数
	std::string   m_AnimetionName = "";
	std::string   m_NextAnimetionName = "";

	//コリジョン判定をするかしないか
	bool m_isCollision = true;

	std::list<Component*> m_ComponentList;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_LimitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 m_OldPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//2D親子関係用の親子間の距離
	D3DXVECTOR3 m_Interval = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


public:
	GameObject(){}
	~GameObject(){
		for (auto Com : m_ComponentList)
			delete Com;
	}


	void Update()
	{
		auto Buff = m_ComponentList;
		for (auto Com : Buff)
		{
			Com->Update();
		}
	}

	void Draw()
	{
		auto Buff = m_ComponentList;
		for (auto Com : Buff)
		{
			Com->Draw();
		}
	}

	void Uninit()
	{
		auto Buff = m_ComponentList;
		for (auto Com : Buff)
		{
			Com->Uninit();
		}
	}

	//子供追加
	void SetParent(std::string name)
	{
		m_ParentName = name;
	}

	//親の名前ゲッター
	std::string GetParent()
	{
		return m_ParentName;
	}

	std::string  GetAnimetionName()
	{
		return m_AnimetionName;
	}

	std::string  GetNextAnimetionName()
	{
		return m_NextAnimetionName;
	}

	void SetCollsionNone(bool flag) { m_isCollision = flag; }

	bool GetCollsionNone() {return m_isCollision; }


	void SetAnimetionName(std::string AnimeName) { m_AnimetionName = AnimeName; }

	void SetNextAnimetionName(std::string NextAnime) { m_NextAnimetionName = NextAnime;}

	std::list<Component*> GetComponentList() { return m_ComponentList; }

	template<class T>
	T* GetComponent()
	{		for (auto Com : m_ComponentList)
		{
			if (typeid(*Com) == typeid(T))
			{
				return (T*)Com;
			}

		}
		return nullptr;
	}

	template<class T>
	T* AddComponent()
	{
		T* component = new T();
		component->m_ParentObject = this;
		m_ComponentList.push_back(component);

		return component;
	}
	
	//直値を入れたい用
	void SetPosition(D3DXVECTOR3 Position){
		m_Position = Position;
	}
	void SetRotation(D3DXVECTOR3 Rotation) {
		m_Rotation = Rotation;
	}
	void SetScale(D3DXVECTOR3 Scale) {
		m_Scale = Scale;
	}
	void SetInterval(D3DXVECTOR3 Interval) {
		m_Interval = Interval;
	}
	void SetOldPosition(D3DXVECTOR3 OldPosition) {
		m_OldPosition = OldPosition;
	}
	void SetVelocity(D3DXVECTOR3 Velocity) {
		m_Velocity = Velocity;
	}

	void AddPosition(D3DXVECTOR3 pos) { m_Position += pos; }
	void AddRotation(D3DXVECTOR3 rot) { m_Rotation += rot; }
	void AddScale(D3DXVECTOR3 scale) { m_Scale += scale; }
	void AddVelocity(D3DXVECTOR3 vel) { m_Velocity += vel; }
	void AddInterval(D3DXVECTOR3 interval) { m_Interval += interval; }
	void AddOldPosition(D3DXVECTOR3 oldpos) { m_OldPosition += oldpos; }



	void SetDestroy() { m_Destroy = true; }

	void SetPositionX(float setpos) { m_Position.x = setpos; }
	void SetPositionY(float setpos) { m_Position.y = setpos; }
	void SetPositionZ(float setpos) { m_Position.z = setpos; }

	void SetRotationX(float setRot) { m_Rotation.x = setRot; }
	void SetRotationY(float setRot) { m_Rotation.y = setRot; }
	void SetRotationZ(float setRot) { m_Rotation.z = setRot; }

	void SetScaleX(float setScale) { m_Scale.x = setScale; }
	void SetScaleY(float setScale) { m_Scale.y = setScale; }
	void SetScaleZ(float setScale) { m_Scale.z = setScale; }

	void SetVelocityX(float setvel) { m_Position.x = setvel; }
	void SetVelocityY(float setvel) { m_Position.y = setvel; }
	void SetVelocityZ(float setvel) { m_Position.z = setvel; }

	void AddPositionX(float addpos) { m_Position.x += addpos; }
	void AddPositionY(float addpos) { m_Position.y += addpos; }
	void AddPositionZ(float addpos) { m_Position.z += addpos; }

	void AddRotationX(float addRot) { m_Rotation.x += addRot; }
	void AddRotationY(float addRot) { m_Rotation.y += addRot; }
	void AddRotationZ(float addRot) { m_Rotation.z += addRot; }

	void AddScaleX(float addScale) { m_Scale.x += addScale; }
	void AddScaleY(float addScale) { m_Scale.y += addScale; }
	void AddScaleZ(float addScale) { m_Scale.z += addScale; }

	void AddVelocityX(float addvel) { m_Velocity.x += addvel; }
	void AddVelocityY(float addvel) { m_Velocity.y += addvel; }
	void AddVelocityZ(float addvel) { m_Velocity.z += addvel; }

	void SetTag(std::string Name) { m_Name = Name; }
	std::string GetTag() { return m_Name; }

	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }
	D3DXVECTOR3 GetInteval() { return m_Interval; }
	D3DXVECTOR3 GetOldPosition() { return m_OldPosition; }
	D3DXVECTOR3 GetVelocity() { return m_Velocity; }

	//前方向ベクトル取得
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		//マトリクス
		//11,12,13 右方向ベクトル
		//21,22,23 上方向ベクトル
		//31.32.33 前方向ベクトル
		//どの値を代入するかによってオブジェクトの方向ベクトルを取得できる
		

		return forward;
	}

	//右方向ベクトル取得
	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;
	}

	//上方向ベクトル取得
	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._21;
		forward.y = rot._22;
		forward.z = rot._23;

		return forward;
	}

	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;
	}

	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._31;
		vx.y = world._32;
		vx.z = world._33;

		return vx * 0.5f;
	}

	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._21;
		vx.y = world._22;
		vx.z = world._23;

		return vx * 0.5f;
	}

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

	bool SetPosTrans(D3DXVECTOR3 pos, D3DXVECTOR3 CurentPos)
	{
		if (m_LimitPos == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_LimitPos = pos - CurentPos;
		}

		if (abs(m_LimitPos.x) < LIMIT_OF_LIMIT &&
			abs(m_LimitPos.y) < LIMIT_OF_LIMIT &&
			abs(m_LimitPos.z) < LIMIT_OF_LIMIT)
		{

			m_Position = D3DXVECTOR3(m_Position.x + m_LimitPos.x,
				m_Position.y, m_Position.z + m_LimitPos.z);
			m_LimitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			return true;
		}
		else
		{
			m_Position.x += m_LimitPos.x * LIMIT_RATE;

			m_Position.z += m_LimitPos.z * LIMIT_RATE;

			m_LimitPos = m_LimitPos * (1 - LIMIT_RATE);

			return false;
		}

	}


};

