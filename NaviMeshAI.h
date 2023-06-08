#pragma once
#include "Component.h"
#include "main.h"
#include <vector>
#include <map>
#include <list>

#define MUGEN 100000

// 削除結果
enum EraseResult
{
	NotFound,		// 未発見
	Erased,			// 削除
	CouldntErased	// 削除できない
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

	int X;		// 列
	int Y;		// 行
};

// ノード
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

	D3DXVECTOR3 Position;						// ノード座標
	std::map<Node*,float> Adjacent;
	float HeuristicCost;				// ヒューリスティックコスト
	float TotalCost;					// コスト(ヒューリスティックコスト込み)
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

	//セル範囲チェック関数
	bool IsCellWithinTheRange(int x, int y);

	std::list<D3DXVECTOR3> AStar(D3DXVECTOR3 CurrentPos, D3DXVECTOR3 GoalPos);

	bool IsEqualCell(const D3DXVECTOR3& a, const D3DXVECTOR3& b);

	//ヒューリスティックコスト計算（ユークリッド距離）
	float CalculateHeuristic(const D3DXVECTOR3 node, const D3DXVECTOR3 Goal);

	//オープンリストに追加
	bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);

	//ノードの削除
	EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost);


};

