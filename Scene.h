#pragma once
#include <list>     //���X�g���p�̂��߂ɂ͕K�v
#include <vector> //vector�^���p�̂��߂ɂ͕K�v
#include <typeinfo>   //�^�𒲂ׂ邽�߂ɂ͕K�v
#include "GameObject.h"
#include <functional>
#include <map>

class Scene
{
protected:
	std::list<GameObject*>   m_GameObject[3];  //STL�̃��X�g�\��

public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;//�������z�֐�
	virtual void InitLoad(std::function<void(void)> function) = 0;//�������z�֐�


	typedef enum
	{
		CAMERA_LAYER = 0,
		PLAY_LAYER,
		UI_LAYER,
		LAYER_MAX,
	}OBJECTLAYER;

	GameObject* AddGameObject(GameObject* obj,OBJECTLAYER Layer)
	{
		m_GameObject[Layer].push_back(obj);

		return obj;
	}

	//tag����v���Ă��āA���C���[��GameObject�����݂��Ă��邩
	//���݂��Ă���΂��̒��g�������Ă���
	GameObject* GetGameObject(std::string tag,OBJECTLAYER Layer)
	{
		//object�̒���m_GameObject�����[�v���Ƃɐ擪������
		//�I���܂ŌJ��Ԃ�
		for (GameObject* object : m_GameObject[Layer])
		{
			//<typeinfo>�K�v
			//�^�����������ׂ�
			if (object->GetTag() == tag)
			{
				//�����Ȃ�^��Ԃ�
				return object;
			}
		}
		return NULL;
	}

	//GetGameObject�֐��Ƃ͈Ⴂ�A�����̃I�u�W�F�N�g�̏���������Ă���֐�
	//vecter�^�Ŕz������A���̒���T�^�Ɠ����^�̏������Ă���
	//Enemy�^�Ȃ炷�ׂĂ�Enemy�̏��𓾂���(Bullet,Item�����l)
	std::vector<GameObject*>GetGameObjects(std::string tag,OBJECTLAYER Layer)
	{
		//STL�̔z��
		std::vector<GameObject*>objects;
		for (GameObject* object : m_GameObject[Layer])
		{
			if (object->GetTag() == tag)
			{
				objects.push_back(object);
			}
		}
		return objects;
	}

	//���C���[���Ƃɂ��ׂẴI�u�W�F�N�g����
	std::vector<GameObject*> GetAllGameObjects(int layar)
	{
		std::vector<GameObject*> object;
		for (int i = 0; i < LAYER_MAX; i++)
		{
			if (layar == i)
			{
				for (GameObject* obj : m_GameObject[layar])
				{
					object.push_back(obj);
				}
			}
		}
		return object;
	}

	//���C���[�֌W�Ȃ����ׂẴI�u�W�F�N�g����
	std::vector<GameObject> AllObject()
	{
		std::vector<GameObject> object;
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* obj : m_GameObject[i])
			{
				object.push_back(*obj);
			}

		}
		return object;
	}

	//�e�̖��O����q��������
	std::vector<GameObject*> GetChildren(std::string ParentName,int layar)
	{
		std::vector<GameObject*> object;

		if (ParentName == "")
			return object;

		for (GameObject* obj : m_GameObject[layar])
		{
			if (obj->GetParent() == ParentName)
			{
				object.push_back(obj);
			}

		}

		return object;
	}



	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{				
				object->Uninit();         //���_�o�b�t�@��e�N�X�`���̉��
				delete object;            //�I�u�W�F�N�g�̃|�C���^����ꕨ������
			}
			m_GameObject[i].clear();         //���X�g�̃N���A  3�i�K�ŏ����Ă���
		}

	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{

				object->Update();

			}

			//�����_��
			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
	
};

