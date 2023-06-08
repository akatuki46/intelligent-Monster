#pragma once
#include "Component.h"
#include "main.h"
#include <vector>
#include <map>
#include <list>

#define MUGEN 100000

// �폜����
enum EraseResult
{
	NotFound,		// ������
	Erased,			// �폜
	CouldntErased	// �폜�ł��Ȃ�
};

struct Cell
{
	Cell() :
		X(-1),
		Y(-1)
	{
	}

	Cell(int x, int y)
	{
		X = x;
		Y = y;
	}

	int X;		// ��
	int Y;		// �s
};

// �m�[�h
struct Node
{
	Node() :
		Node(D3DXVECTOR3(0, 0,0))
	{
	}

	Node(D3DXVECTOR3 y) :
		Position( y),
		HeuristicCost(INFINITY),
		TotalCost(0),
		IsAdvence(true)
	{
		Adjacent.clear();
	}

	D3DXVECTOR3 Position;						// �m�[�h���W
	std::map<Node*,float> Adjacent;
	float HeuristicCost;				// �q���[���X�e�B�b�N�R�X�g
	float TotalCost;					// �R�X�g(�q���[���X�e�B�b�N�R�X�g����)
	bool  IsAdvence;
};


class NaviMeshAI :
    public Component
{
private:
	const static int NaviWidthPoint = 10;
	const static int NaviDepthPoint = 10;


	Node m_Node[NaviWidthPoint + 1][NaviDepthPoint + 1];
	
	D3DXVECTOR3  m_NaviSize = D3DXVECTOR3(0.0f,0.0f ,0.0f);

public:
	void Init(float NaviWidth,float NaviDepth);
	void Uninit() override;
	void Update() override;
	void Draw() override {};

	bool CollisionNavi(GameObject* obj);

	//�Z���͈̓`�F�b�N�֐�
	bool IsCellWithinTheRange(int x, int y);

	std::list<D3DXVECTOR3> AStar(D3DXVECTOR3 CurrentPos, D3DXVECTOR3 GoalPos);

	bool IsEqualCell(const D3DXVECTOR3& a, const D3DXVECTOR3& b);

	//�q���[���X�e�B�b�N�R�X�g�v�Z�i���[�N���b�h�����j
	float CalculateHeuristic(const D3DXVECTOR3 node, const D3DXVECTOR3 Goal);

	//�I�[�v�����X�g�ɒǉ�
	bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);

	//�m�[�h�̍폜
	EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost);


};

