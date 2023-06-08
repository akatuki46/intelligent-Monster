#include "NaviMeshAI.h"
#include "Scene.h"
#include "manager.h"
#include "SizeDraw2D.h"
#include "Draw2DVer3D.h"

void NaviMeshAI::Init(float NaviWidth, float NaviDepth)
{
	Scene* scene = Manager::GetScene();

	GameObject* Field = scene->GetGameObject("Field", scene->PLAY_LAYER);
	std::vector<GameObject*> Wall = scene->GetGameObjects("Wall", scene->PLAY_LAYER);

	//ウェイポイントの設定
	for (int y = 0; y <= NaviDepthPoint; y++)
	{
		for (int x = 0; x <= NaviWidthPoint; x++)
		{
			m_Node[y][x].Position = D3DXVECTOR3((NaviWidth / NaviWidthPoint) * x - (NaviWidth / 2),
				0.0f, (NaviDepth / NaviDepthPoint) * -y + (NaviDepth / 2));

			//フィールドとの当たり判定
			if (Field->GetPosition().x + Field->GetScale().x < m_Node[y][x].Position.x &&
				Field->GetPosition().x - Field->GetScale().x > m_Node[y][x].Position.x &&
				Field->GetPosition().z + Field->GetScale().z < m_Node[y][x].Position.z &&
				Field->GetPosition().z - Field->GetScale().z > m_Node[y][x].Position.z)
			{
				m_Node[y][x].IsAdvence = false;
			}
			else
			{
				m_Node[y][x].IsAdvence = true;

			}

			for (auto wall : Wall)
			{
				//壁との当たり判定
				if (wall != nullptr && wall->GetPosition().x + (wall->GetScale().x / 2) >= m_Node[y][x].Position.x &&
					wall->GetPosition().x - (wall->GetScale().x / 2) <= m_Node[y][x].Position.x &&
					wall->GetPosition().z + (wall->GetScale().z / 2) >= m_Node[y][x].Position.z &&
					wall->GetPosition().z - (wall->GetScale().z / 2) <= m_Node[y][x].Position.z)
				{
					m_Node[y][x].IsAdvence = false;
				}
				else
				{
					m_Node[y][x].IsAdvence = true;

				}

			}


			m_Node[y][x].HeuristicCost = MUGEN;
			m_Node[y][x].TotalCost = 0;
		}
	}

	for (int y = 0; y <= NaviDepthPoint; y++)
	{
		for (int x = 0; x <= NaviWidthPoint; x++)
		{
			//隣接セルの指定　上下左右
			Cell adjacent_cells[] =
			{
				Cell(x, y - 1),
				Cell(x - 1, y),
				Cell(x + 1, y),
				Cell(x, y + 1),
				Cell(x + 1,y + 1),
				Cell(x + 1,y - 1),
				Cell(x - 1,y + 1),
				Cell(x - 1,y - 1),

			};

			// 隣接ノードの追加
			for (auto cell : adjacent_cells)
			{
				//ブロックの下にウェイポイントがある以外にブロックにさえぎられている場合を考慮
				if (IsCellWithinTheRange(cell.X, cell.Y) == true &&
					m_Node[cell.Y][cell.X].IsAdvence)
				{                    //ノードの終点                      //ノードの始点
					D3DXVECTOR3 aa = m_Node[cell.Y][cell.X].Position - m_Node[y][x].Position;


					for (auto wall : Wall)
					{

						if ((aa.x > 0 && m_Node[y][x].Position.x < wall->GetPosition().x - (wall->GetScale().x / 2) &&
							m_Node[cell.Y][cell.X].Position.x > wall->GetPosition().x + (wall->GetScale().x / 2)) ||
							(aa.x < 0 && m_Node[y][x].Position.x > wall->GetPosition().x + (wall->GetScale().x / 2) &&
								m_Node[cell.Y][cell.X].Position.x < wall->GetPosition().x - (wall->GetScale().x / 2)))
						{
							m_Node[y][x].Adjacent[&m_Node[cell.Y][cell.X]] = 10000;

						}
						else
						{
							//隣接ノードを設定				
							m_Node[y][x].Adjacent[&m_Node[cell.Y][cell.X]] = D3DXVec3Length(&aa);

						}
					}
				}
			}

		}
	}

	m_NaviSize = D3DXVECTOR3(NaviWidth, 0.0f, NaviDepth);

}

void NaviMeshAI::Uninit()
{
}

void NaviMeshAI::Update()
{
	//動的にナビメッシュが変わる処理は重いので一旦保留

}

bool Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost)
	{
		return true;
	}

	return false;
}

//ナビメッシュ内にいるか（戦闘時は経路探索を使用しないので残す）
bool NaviMeshAI::CollisionNavi(GameObject* obj)
{
	//ナビメッシュ内にいるならTrue
	if (m_ParentObject->GetPosition().x + m_ParentObject->GetScale().x >= fabs(obj->GetPosition().x) &&
		m_ParentObject->GetPosition().z + m_ParentObject->GetScale().z >= fabs(obj->GetPosition().z))
	{
		return true;
	}

	return false;
}

//ウェイポイントが範囲内か
bool NaviMeshAI::IsCellWithinTheRange(int x, int y)
{
	//ウェイポイントが範囲内であり
	if (x >= 0 &&
		x < NaviWidthPoint + 1 &&
		y >= 0 &&
		y < NaviDepthPoint + 1)
	{
		return true;
	}

	return false;
}

std::list<D3DXVECTOR3> NaviMeshAI::AStar(D3DXVECTOR3 CurrentPos, D3DXVECTOR3 GoalPos)
{
	std::list<Node*> open_list;
	std::list<Node*> close_list;

	int StartPointX, StartPointZ;
	int GoalPointX, GoalPointZ;

	StartPointX = ((m_NaviSize.x / 2) + CurrentPos.x) / (m_NaviSize.x / NaviWidthPoint);
	StartPointZ = (-(m_NaviSize.z / 2) + CurrentPos.z) / -(m_NaviSize.x / NaviDepthPoint);

	GoalPointX = ((m_NaviSize.x / 2) + GoalPos.x) / (m_NaviSize.x / NaviWidthPoint);
	GoalPointZ = (-(m_NaviSize.z / 2) + GoalPos.z) / -(m_NaviSize.x / NaviDepthPoint);

	const Node* goal_node = &m_Node[GoalPointZ][GoalPointX];


	// 更新したノード位置保存用
	D3DXVECTOR3 last_update_cells[NaviDepthPoint + 1][NaviWidthPoint + 1];

	// スタートノードの指定
	open_list.push_back(&m_Node[StartPointZ][StartPointX]);

	// オープンリストがなくなるまで回す
	while (open_list.empty() == false)
	{
		Node* search_node = (*open_list.begin());
		// 探索リストから除外
		open_list.erase(open_list.begin());

		if (search_node->Position == D3DXVECTOR3(1.0f, 0.0f, -4.0f))
		{
			int k = 0;
			k++;
		}

		// ゴールに到達したら終わり
		if (IsEqualCell(search_node->Position, GoalPos) == true)
		{
			// クローズリストに最後のノードを追加する
			close_list.push_back(search_node);
			break;
		}
		int adjaCnt = 0;
		for (auto adjacent_node : search_node->Adjacent)
		{
			adjaCnt++;
			// 計算を行っていなかった場合だけ計算
			if (adjacent_node.first->HeuristicCost == MUGEN)
			{
				// ヒューリスティクスコスト計算
				adjacent_node.first->HeuristicCost = CalculateHeuristic(adjacent_node.first->Position, goal_node->Position);
			}

			// ノード間コスト
			float edge_cost = adjacent_node.second;
			// 取得ノードのトータルコスト
			float node_cost = search_node->TotalCost;
			/*
				トータルコスト算出
					ノード間コスト + ヒューリスティックコスト + 取得ノードのトータルコスト
			*/
			float total_cost = edge_cost + adjacent_node.first->HeuristicCost + node_cost;

			// ノード追加
			if (AddAdjacentNode(open_list, close_list, adjacent_node.first, total_cost) == true)
			{
				// トータルコストを更新
				adjacent_node.first->TotalCost = total_cost;

				// 経路を更新したセルを保存
				last_update_cells[(int)((-(m_NaviSize.z / 2) + adjacent_node.first->Position.z) / -(m_NaviSize.x / NaviDepthPoint))]
					[(int)(((m_NaviSize.x / 2) + adjacent_node.first->Position.x) / (m_NaviSize.x / NaviWidthPoint))] = search_node->Position;
			}
		}
		
		bool is_add_close = true;

		// クローズリストチェック
		for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
		{
			// ノードと同じセルがあるか調べる
			if (IsEqualCell(search_node->Position, (*itr)->Position) == true)
			{
				is_add_close = false;
				break;
			}
		}

		// 同じノードが無かったので追加
		if (is_add_close == true)
		{
			// このノードの探索終了
			close_list.push_back(search_node);
		}

		// 昇順ソート
		open_list.sort(Less);
	}

	// 経路復元
	std::list<D3DXVECTOR3> route_list;

	// ゴールセルから復元する
	route_list.push_back(m_Node[GoalPointZ][GoalPointX].Position);

	if (!m_Node[GoalPointZ][GoalPointX].IsAdvence)
	{
		route_list.clear();
		return route_list;
	}

	while (route_list.empty() == false)
	{
		D3DXVECTOR3 route = route_list.front();

		// スタートセルなら終了
		if (IsEqualCell(route, m_Node[StartPointZ][StartPointX].Position) == true)
		{
			for (int y = 0; y <= NaviDepthPoint; y++)
			{
				for (int x = 0; x <= NaviWidthPoint; x++)
				{
					m_Node[y][x].HeuristicCost = MUGEN;
					m_Node[y][x].TotalCost = 0;
				}
			}
			return route_list;
		}
		else
		{
			if (IsCellWithinTheRange((int)(((m_NaviSize.x / 2) + route.x) / (m_NaviSize.x / NaviWidthPoint)), (int)((-(m_NaviSize.z / 2) + route.z) / -(m_NaviSize.x / NaviDepthPoint))) == true)
			{
				// 追加
				route_list.push_front(last_update_cells[(int)((-(m_NaviSize.z / 2) + route.z) / -(m_NaviSize.x / NaviDepthPoint))][(int)(((m_NaviSize.x / 2) + route.x) / (m_NaviSize.x / NaviWidthPoint))]);
			}
			else
			{
				return route_list;
			}
		}
	}


}

bool NaviMeshAI::IsEqualCell(const D3DXVECTOR3& a, const D3DXVECTOR3& b)
{
	if (a.x == b.x &&
		a.z == b.z)
	{
		return true;
	}

	return false;
}

float NaviMeshAI::CalculateHeuristic(const D3DXVECTOR3 node, const D3DXVECTOR3 Goal)
{
	float length;
	D3DXVECTOR3 aa = Goal - node;
	//yも計算してしまう可能性あり　代入時にyは0として共通化しておかないといけない
	length = D3DXVec3Length(&aa);

	return length;
}

bool NaviMeshAI::AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost)
{
	bool can_update = true;

	std::list<Node*> node_list[] =
	{
		close_list,
		open_list
	};

	for (std::list<Node*>& list : node_list)
	{
		// リストに同じノードがあってリストの方のコストが高いなら削除
		if (EraseNode(list, adjacent_node, cost) == EraseResult::CouldntErased)
		{
			can_update = false;
		}
	}

	if (can_update == true)
	{
		open_list.push_back(adjacent_node);
		return true;
	}

	return false;

}

EraseResult NaviMeshAI::EraseNode(std::list<Node*>& list, Node* new_node, float new_cost)
{
	// クローズリストチェック
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// ノードと同じセルがあるか調べる
		if (IsEqualCell(new_node->Position, (*itr)->Position) == true)
		{
			// コストの比較
			if (new_cost < (*itr)->TotalCost)
			{
				list.erase(itr);
				return EraseResult::Erased;
			}
			else
			{
				return EraseResult::CouldntErased;
			}
		}
	}

	return EraseResult::NotFound;
}
