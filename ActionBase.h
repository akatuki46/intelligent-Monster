#ifndef ACTION_BASE_H_
#define ACTION_BASE_H_

class GameObject;

// �s���������N���X
class ActionBase
{
public:
	// ���s���
	enum STATE
	{
		RUN,		// ���s��
		FAILED,		// ���s���s
		COMPLETE,	// ���s����
	};

	// ���s����(�������z�֐�)
	virtual STATE Run(GameObject *enemy) = 0;
};

#endif
