//////////////////////////////////////////////////////////////////////
//    �����蔻��p�@�R���|�[�l���g
//////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "GameObject.h"
class AttaBoxComponent :
    public Component
{
private:
    //�Ăяo�����@��������GameObject�@�R���W�������ɏ��O
    GameObject* m_Caller = nullptr;

    //�R���W���������I�u�W�F�N�g�ɗ^����_���[�W��
    int m_Damage = 0;

    //�����蔻�肷��Ώۂ̖��O
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

