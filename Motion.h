#pragma once
#include "Component.h"
#include <unordered_map>
#include <functional>
#include "main.h"


class Motion :
    public Component
{
private:

	int m_TransChange = 0;

	//モーションするモデル保存用リスト
	std::unordered_map<std::string ,GameObject*> m_MotionModel;

	//増減値保存用マップ(rotation)
	std::unordered_map<std::string, D3DXVECTOR3> m_InOutValue;

	//増減値保存用マップ(Position)
	std::unordered_map<std::string, D3DXVECTOR3> m_InOutValuePos;

	//初期値保存用マップ(Position)
	std::unordered_map<std::string, D3DXVECTOR3> m_KeepPos;


	int m_FlameCnt = 0;
	int m_FlameCnt2 = -5;   //動きにずれを発生させたいときに使う変数 5フレームずらす
	std::string m_MotionName = "";

	bool IdleFlag = false;

	int transFlag = -1;
	int transFlag2 = -1;    //動きにずれを発生させたいときに使う変数


	//一回だけ実行したいときに使うフラグ
	bool FirstFlag = true;
	int ChangeMotion = 0;


	std::string m_OldMotion = "";

	int m_MotionFlame = 30;

	//モーションにディレイをかけたいときに使用 
	bool m_MotionDelyFlag = false;

	//複数回モーションを実行したいときに使う変数
	int m_MotionCnt = 0;

	//モーション終了を通知する変数
	bool m_MotionEnd = false;

	//ポイントを打ち、任意の場所でイベントを発生させるよう変数
	bool m_MotionPoint = false;

	int m_ShaderCnt = 0;

	//Imgui用Get,Set変数
	D3DXVECTOR3 m_ImguiPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_ImguiRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


public:

	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void MotionPlay(std::string PlayMotion);

	void SetMotion(std::string MotionName) { m_MotionName = MotionName; }

	void SetShaderCnt(int flag) { m_ShaderCnt = flag; }

	bool GetMotionEnd() { return m_MotionEnd; }
	bool GetMotionPoint() { return m_MotionPoint; }

	void SetMotionEnd(bool flag) { m_MotionEnd = flag; }
	std::string GetMotionName() { return m_MotionName; }

};

