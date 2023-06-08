#include "BehaviorTree.h"
#include "ActionBase.h"
#include "NodeBase.h"
#include "ExecJudgmentBase.h"
#include "Enemy.h"
#include "BehaviorData.h"

void BehaviorTree::AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgmentBase *judgment, ActionBase *action)
{
	if (search_name != "")
	{
		NodeBase *search_node = m_Root->SearchNode(search_name);

		if (search_node != NULL)
		{
			//�����K�w�̌Z��m�[�h���擾
			NodeBase* sibling = search_node->GetLastChild();
			//�m�[�h��؍\���ɑ��
			NodeBase *add_node = new NodeBase(entry_name, search_node, sibling, priority, select_rule, judgment, action, search_node->GetHirerchyNo() + 1);
			//�e�m�[�h�Ɏq�m�[�h��ǉ�
			search_node->AddChild(add_node);
		}
	} else {
		//�܂�Root�i��ԏ�̃m�[�h�j���Ȃ��ꍇ
		if (m_Root == NULL)
		{   //Root��}��
			m_Root = new NodeBase(entry_name, NULL, NULL, priority, select_rule, judgment, action, 1);
		} else {
			printf("���[�g�͊��ɓo�^����Ă��܂�\n");
		}
	}
}

void BehaviorTree::PrintTree()
{
	if (m_Root != NULL)
	{
		m_Root->PrintName();
	}
}

// ���_
NodeBase *BehaviorTree::Inference(GameObject *enemy, BehaviorData *data)
{
	// �f�[�^�����Z�b�g���ĊJ�n
	data->Init();
	return m_Root->Inference(enemy, data);
}

// �V�[�P���X�m�[�h����̐��_�J�n
NodeBase *BehaviorTree::SequenceBack(NodeBase *sequence_node, GameObject *enemy, BehaviorData *data)
{
	return sequence_node->Inference(enemy, data);
}

// �m�[�h���s
NodeBase *BehaviorTree::Run(GameObject *enemy, NodeBase *action_node, BehaviorData *data)
{
	// �m�[�h���s
	ActionBase::STATE state = action_node->Run(enemy);

	// ����I��
	if (state == ActionBase::STATE::COMPLETE)
	{
		// �V�[�P���X�̓r�����𔻒f
		//�V�[�P���X���[���Ŏ��s���Ă���ꍇ�A
		//���ԂɎ��s���čŌ�܂Ŏ��s���Ȃ���root�ɖ߂�Ȃ�����
		NodeBase *sequence_node = data->PopSequenceNode();

		// �r������Ȃ��Ȃ�I��
		if (sequence_node == NULL  )
		{
			return NULL;
		} else {
			// �r���Ȃ炻������n�߂�
			return SequenceBack(sequence_node, enemy, data);
		}
	// ���s�͏I��
	} else if (state == ActionBase::STATE::FAILED) {
		return NULL;
	}

	// ����ێ�
	return action_node;
}
