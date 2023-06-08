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

	//�E�F�C�|�C���g�̐ݒ�
	for (int y = 0; y <= NaviDepthPoint; y++)
	{
		for (int x = 0; x <= NaviWidthPoint; x++)
		{
			m_Node[y][x].Position = D3DXVECTOR3((NaviWidth / NaviWidthPoint) * x - (NaviWidth / 2),
				0.0f, (NaviDepth / NaviDepthPoint) * -y + (NaviDepth / 2));

			//�t�B�[���h�Ƃ̓����蔻��
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
				//�ǂƂ̓����蔻��
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
			//�אڃZ���̎w��@�㉺���E
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

			// �אڃm�[�h�̒ǉ�
			for (auto cell : adjacent_cells)
			{
				//�u���b�N�̉��ɃE�F�C�|�C���g������ȊO�Ƀu���b�N�ɂ��������Ă���ꍇ���l��
				if (IsCellWithinTheRange(cell.X, cell.Y) == true &&
					m_Node[cell.Y][cell.X].IsAdvence)
				{                    //�m�[�h�̏I�_                      //�m�[�h�̎n�_
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
							//�אڃm�[�h��ݒ�				
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
	//���I�Ƀi�r���b�V�����ς�鏈���͏d���̂ň�U�ۗ�

}

bool Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost)
	{
		return true;
	}

	return false;
}

//�i�r���b�V�����ɂ��邩�i�퓬���͌o�H�T�����g�p���Ȃ��̂Ŏc���j
bool NaviMeshAI::CollisionNavi(GameObject* obj)
{
	//�i�r���b�V�����ɂ���Ȃ�True
	if (m_ParentObject->GetPosition().x + m_ParentObject->GetScale().x >= fabs(obj->GetPosition().x) &&
		m_ParentObject->GetPosition().z + m_ParentObject->GetScale().z >= fabs(obj->GetPosition().z))
	{
		return true;
	}

	return false;
}

//�E�F�C�|�C���g���͈͓���
bool NaviMeshAI::IsCellWithinTheRange(int x, int y)
{
	//�E�F�C�|�C���g���͈͓��ł���
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


	// �X�V�����m�[�h�ʒu�ۑ��p
	D3DXVECTOR3 last_update_cells[NaviDepthPoint + 1][NaviWidthPoint + 1];

	// �X�^�[�g�m�[�h�̎w��
	open_list.push_back(&m_Node[StartPointZ][StartPointX]);

	// �I�[�v�����X�g���Ȃ��Ȃ�܂ŉ�
	while (open_list.empty() == false)
	{
		Node* search_node = (*open_list.begin());
		// �T�����X�g���珜�O
		open_list.erase(open_list.begin());

		if (search_node->Position == D3DXVECTOR3(1.0f, 0.0f, -4.0f))
		{
			int k = 0;
			k++;
		}

		// �S�[���ɓ��B������I���
		if (IsEqualCell(search_node->Position, GoalPos) == true)
		{
			// �N���[�Y���X�g�ɍŌ�̃m�[�h��ǉ�����
			close_list.push_back(search_node);
			break;
		}
		int adjaCnt = 0;
		for (auto adjacent_node : search_node->Adjacent)
		{
			adjaCnt++;
			// �v�Z���s���Ă��Ȃ������ꍇ�����v�Z
			if (adjacent_node.first->HeuristicCost == MUGEN)
			{
				// �q���[���X�e�B�N�X�R�X�g�v�Z
				adjacent_node.first->HeuristicCost = CalculateHeuristic(adjacent_node.first->Position, goal_node->Position);
			}

			// �m�[�h�ԃR�X�g
			float edge_cost = adjacent_node.second;
			// �擾�m�[�h�̃g�[�^���R�X�g
			float node_cost = search_node->TotalCost;
			/*
				�g�[�^���R�X�g�Z�o
					�m�[�h�ԃR�X�g + �q���[���X�e�B�b�N�R�X�g + �擾�m�[�h�̃g�[�^���R�X�g
			*/
			float total_cost = edge_cost + adjacent_node.first->HeuristicCost + node_cost;

			// �m�[�h�ǉ�
			if (AddAdjacentNode(open_list, close_list, adjacent_node.first, total_cost) == true)
			{
				// �g�[�^���R�X�g���X�V
				adjacent_node.first->TotalCost = total_cost;

				// �o�H���X�V�����Z����ۑ�
				last_update_cells[(int)((-(m_NaviSize.z / 2) + adjacent_node.first->Position.z) / -(m_NaviSize.x / NaviDepthPoint))]
					[(int)(((m_NaviSize.x / 2) + adjacent_node.first->Position.x) / (m_NaviSize.x / NaviWidthPoint))] = search_node->Position;
			}
		}
		
		bool is_add_close = true;

		// �N���[�Y���X�g�`�F�b�N
		for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
		{
			// �m�[�h�Ɠ����Z�������邩���ׂ�
			if (IsEqualCell(search_node->Position, (*itr)->Position) == true)
			{
				is_add_close = false;
				break;
			}
		}

		// �����m�[�h�����������̂Œǉ�
		if (is_add_close == true)
		{
			// ���̃m�[�h�̒T���I��
			close_list.push_back(search_node);
		}

		// �����\�[�g
		open_list.sort(Less);
	}

	// �o�H����
	std::list<D3DXVECTOR3> route_list;

	// �S�[���Z�����畜������
	route_list.push_back(m_Node[GoalPointZ][GoalPointX].Position);

	if (!m_Node[GoalPointZ][GoalPointX].IsAdvence)
	{
		route_list.clear();
		return route_list;
	}

	while (route_list.empty() == false)
	{
		D3DXVECTOR3 route = route_list.front();

		// �X�^�[�g�Z���Ȃ�I��
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
				// �ǉ�
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
	//y���v�Z���Ă��܂��\������@�������y��0�Ƃ��ċ��ʉ����Ă����Ȃ��Ƃ����Ȃ�
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
		// ���X�g�ɓ����m�[�h�������ă��X�g�̕��̃R�X�g�������Ȃ�폜
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
	// �N���[�Y���X�g�`�F�b�N
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// �m�[�h�Ɠ����Z�������邩���ׂ�
		if (IsEqualCell(new_node->Position, (*itr)->Position) == true)
		{
			// �R�X�g�̔�r
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
