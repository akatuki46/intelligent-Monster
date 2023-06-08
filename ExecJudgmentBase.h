#ifndef EXEC_JUDGMENT_BASE_H_
#define EXEC_JUDGMENT_BASE_H_

class GameObject;

// é¿çsîªíË
class ExecJudgmentBase
{
public:
	virtual bool Judgment(GameObject *enemy) = 0;
};

#endif
