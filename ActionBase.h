#ifndef ACTION_BASE_H_
#define ACTION_BASE_H_

class GameObject;

// 行動処理基底クラス
class ActionBase
{
public:
	// 実行情報
	enum STATE
	{
		RUN,		// 実行中
		FAILED,		// 実行失敗
		COMPLETE,	// 実行成功
	};

	// 実行処理(純粋仮想関数)
	virtual STATE Run(GameObject *enemy) = 0;
};

#endif
