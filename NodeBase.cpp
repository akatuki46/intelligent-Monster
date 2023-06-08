#include <iostream>
#include "ExecJudgmentBase.h"
#include "NodeBase.h"
#include "Enemy.h"
#include "BehaviorData.h"
#include "ActionBase.h"

// �m�[�h����
NodeBase *NodeBase::SearchNode(std::string search_name)
{
	// ���O����v
	if (m_Name == search_name)
	{
		return this;
	} else {
		// �q�m�[�h�Ō���
		for (auto itr = m_Child.begin(); itr != m_Child.end(); itr++)
		{
			NodeBase *ret = (*itr)->SearchNode(search_name);

			if (ret != NULL)
			{
				return ret;
			}
		}
	}

	return NULL;
}

// ���O�\��
void NodeBase::PrintName()
{
	std::cout << m_Name << std::endl;

	for (auto itr = m_Child.begin(); itr != m_Child.end(); itr++)
	{
		(*itr)->PrintName();
	}
}

// �m�[�h���_
NodeBase *NodeBase::Inference(GameObject *enemy, BehaviorData *data)
{
	//���s�m�[�h��������܂ŌJ��Ԃ����s�iAction������܂Łj

	std::vector<NodeBase*> list;
	NodeBase *result = NULL;

	// �q�m�[�h�Ŏ��s�\�ȃm�[�h��T���i�A�N�e�B�u�m�[�h����A�N�e�B�u�m�[�h���̔���j
	for (int i = 0; i < m_Child.size(); i++)
	{
		if (m_Child[i]->m_ExecJudgment != NULL)
		{
			if (m_Child[i]->m_ExecJudgment->Judgment(enemy) == true)
			{
				list.push_back(m_Child[i]);
			}
		} else {
			// ����N���X���Ȃ���Ζ������ɒǉ�
			list.push_back(m_Child[i]);
		}
	}

	// �I�����[���Ńm�[�h����
	switch (m_SelectRule)
	{
	// �D�揇��(�A�N�e�B�u�m�[�h���ōł��D��x�������m�[�h�����s)
	case BehaviorTree::SELECT_RULE::PRIORITY:
		result = SelectPriority(&list);
		break;
	// �I���E�I�t�i�A�N�e�B�u�m�[�h���ł܂����s���Ă��Ȃ��m�[�h�����s�j
	case BehaviorTree::SELECT_RULE::ON_OFF:
		result = SelectOnOff(&list, data);
		break;
	// �����_���i�A�N�e�B�u�m�[�h���Ń����_���Ƀm�[�h�����s�j
	case BehaviorTree::SELECT_RULE::RANDOM:
		result = SelectRandom(&list);
		break;
	// �V�[�P���X(�A�N�e�B�u�m�[�h���ŏ��ԂɎ��s)
	case BehaviorTree::SELECT_RULE::SEQUENCE:
	case BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING:
		result = SelectSequence(&list, data);
		break;
	}

	if (result != NULL)
	{
		// �s��������ΏI��
		if (result->HasAction() == true)
		{
			return result;
		} else {
			// ���܂����m�[�h�Ő��_�J�n
			result = result->Inference(enemy, data);
		}
	}

	return result;
}

// �D�揇�ʑI��
NodeBase *NodeBase::SelectPriority(std::vector<NodeBase*> *list)
{
	NodeBase *select_node = NULL;
	int priority = -10000;

	// ��ԗD�揇�ʂ������m�[�h��T��
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (priority < (*itr)->GetPriority())
		{
			select_node = (*itr);
			priority = (*itr)->GetPriority();
		}
	}

	return select_node;
}

// �I���E�I�t
NodeBase *NodeBase::SelectOnOff(std::vector<NodeBase*> *list, BehaviorData *data)
{
	std::vector<NodeBase*> off_list;

	// �g�p����Ă��Ȃ��m�[�h�����X�g�A�b�v����
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (data->IsNodeUsed((*itr)->GetName()) == false)
		{
			off_list.push_back(*itr);
		}
	}

	// ���X�g�A�b�v�������`�F�b�N
	if (off_list.size() == 0)
	{
		// �m�[�h��S�ă��Z�b�g
		data->ResetNodeUsed(&m_Child);
		off_list = *list;
	}

	// �g�p�����m�[�h��o�^
	data->EntryUsedNode(off_list[0]->GetName());

	// ���X�g�̐擪������m�[�h
	return off_list[0];
}

// �����_��
NodeBase *NodeBase::SelectRandom(std::vector<NodeBase*> *list)
{
	int select_no = rand() % list->size();

	return (*list)[select_no];
}

// �V�[�P���X
NodeBase *NodeBase::SelectSequence(std::vector<NodeBase*> *list, BehaviorData *data)
{
	// ���̃m�[�h�̃V�[�P���X�̃X�e�b�v���擾
	//���ǂ��܂Ŏ��s������
	int step = data->GetSequenceStep(GetName());

	// �V�[�P���X���I����Ă���I��
	if (step >= m_Child.size())
	{
		if (m_SelectRule != BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING)
		{
			return NULL;
		} else {
			// Looping�̏ꍇ�͓�������s
			step = 0;
		}
	}

	// ���Ԃ̃m�[�h�����s�ł��邩�̃`�F�b�N
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (m_Child[step]->GetName() == (*itr)->GetName())
		{
			// �V�[�P���X�m�[�h���L�^
			//���̏ꍇAction
			data->PushSequenceNode(this);
			// �V�[�P���X�X�e�b�v���X�V
			data->SetSequenceStep(GetName(), step + 1);
			return m_Child[step];
		}
	}

	return NULL;
}

// ����
bool NodeBase::Judgment(GameObject *enemy)
{
	//�@����N���X�������Ă���Ύ����Ȃ����true����
	if (m_ExecJudgment != NULL)
	{
		return m_ExecJudgment->Judgment(enemy);
	}
	return true;
}

// �m�[�h���s
ActionBase::STATE NodeBase::Run(GameObject *enemy)
{
	// �A�N�V�����m�[�h������Ύ��s���Č��ʂ�Ԃ��A�Ȃ���Ύ��s����
	if (m_Action != NULL)
	{
		return m_Action->Run(enemy);
	}

	return ActionBase::FAILED;
}
