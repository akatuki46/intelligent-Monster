//////////////////////////////////////////////////////////////////////
//    当たり判定用　コンポーネント
//////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "GameObject.h"
class AttaBoxComponent :
    public Component
{
private:
    //呼び出し元　生成元のGameObject　コリジョン時に除外
    GameObject* m_Caller = nullptr;

    //コリジョンしたオブジェクトに与えるダメージ量
    int m_Damage = 0;

    //当たり判定する対象の名前
    std::string m_SubjectCollision = "";

public:
    void Init(GameObject* caller, int damage,std::string name);
    void Uninit() override {};
    void Draw() override {};
    void Update()override {};

    static void CollisionAction(GameObject* obj,std::string name);
    GameObject* GetCaller() { return m_Caller; }
    std::string GetSubjectName() { return m_SubjectCollision; }

};

