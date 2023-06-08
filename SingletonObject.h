#pragma once
#include "manager.h"

// シングルトン設計のオブジェクト
template <typename T>
class SingletonObject
{
public:
	// インスタンスの生成
	static void Create()
	{
		// インスタンスが存在しない場合
		if (!m_Instance)
		{
			m_Instance = new T;
		}
	}

	// インスタンスの取得
	static T& Instance()
	{
		// インスタンスが存在しない場合
		if (!m_Instance)
		{
			// インスタンスの生成処理を行う
			Create();
		}

		// インスタンスを渡す
		return *m_Instance;
	}

	// インスタンスの削除
	void InstanceRelease()
	{
		delete m_Instance;
	}

protected:
	SingletonObject() {}
	virtual ~SingletonObject() {}

private:
	// オブジェクト本体
    static T* m_Instance;

	// 代入の制限
	SingletonObject& operator=(const SingletonObject& obj) {}

	// コピーコンストラクタの制限
	SingletonObject(const SingletonObject& obj) {}
};

// 変数の初期化
template <typename T>
T* SingletonObject<T>::m_Instance = nullptr;