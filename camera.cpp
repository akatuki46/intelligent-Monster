#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "Scene.h"
#include "Player.h"
#include "input.h"
#include "Enemy.h"
#include "Prism.h"
#include "Padinput.h"

#define CIRCLE (3.14f)
#define CAMERA_SPEAD 70


//=============================================================================
// 初期化処理
//=============================================================================
void Camera::Init(bool FleeFlag)
{
	m_ParentObject->SetPosition(D3DXVECTOR3(0.0f, 3.0f, 3.0f));
	m_Positions = D3DXVECTOR3(0.0f,2.5f,0.0f);

	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Targets = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


	m_FreeFlag = FleeFlag;
}


//=============================================================================
// カメラの終了処理
//=============================================================================
void Camera::Uninit(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void Camera::Update(void)
{
	
	Scene* scene = Manager::GetScene();

	GameObject* pPlayer = scene->GetGameObject("Player",scene->PLAY_LAYER);
	GameObject* pEnemy = scene->GetGameObject("Enemy",scene->PLAY_LAYER);

	//トップビュー
	{
		//m_Position = D3DXVECTOR3(pPlayer->GetPosition().x + m_Positions.x, pPlayer->GetPosition().y + m_Positions.y,
		//	pPlayer->GetPosition().z + m_Positions.z);

		//m_Target = D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y, pPlayer->GetPosition().z);
	}

	//サードパーソンビュー
	if(pPlayer != nullptr && !m_FreeFlag && !m_DethCameraFlag)
	{
		m_ParentObject->SetPosition(pPlayer->GetPosition() - m_ParentObject->GetForward() * -4 + m_Positions);
		

		m_Target = pPlayer->GetPosition() + m_ParentObject->GetForward() * -3 + m_Targets;

		//m_Target = pEnemy->GetPosition();

		if (GetKeyboardPress(DIK_K)|| GetThumbRightX(0) < 0)
		{
			m_ParentObject->AddRotationY(-0.1f);
		}
		if (GetKeyboardPress(DIK_SEMICOLON) || GetThumbRightX(0) > 0)
		{
			m_ParentObject->AddRotationY(0.1);
		}

		if (GetKeyboardPress(DIK_O) || GetThumbRightY(0) > 0)
		{
			m_Targets.y += 0.1f;
		}
		if (GetKeyboardPress(DIK_L) || GetThumbRightY(0) < 0)
		{
			m_Targets.y -= 0.1f;
		}

		if (GetKeyboardTrigger(DIK_LCONTROL) || IsButtonXinputTriggered(0,XINPUT_GAMEPAD_LEFT_SHOULDER))
		{

			m_ParentObject->SetRotation(pPlayer->GetRotation());

		}
	}

	if (pEnemy != nullptr && pEnemy->GetComponent<Enemy>()->GetMotionStartFlag())
	{
		m_Target = pEnemy->GetPosition();
		if (m_Cnt == 0)
		{
			m_DethCameraFlag = true;

			m_ParentObject->SetPosition(pEnemy->GetPosition() + pEnemy->GetForward() * 8);
		}
		//if (m_Cnt <= 20)
		//{
		//	m_ParentObject->AddRotationY(0.03f);
		//}

		//if (m_Cnt == 20)
		//{
		//	m_ParentObject->SetPosition(pEnemy->GetPosition() + pEnemy->GetForward() * 1);
		//}
		if (m_Cnt > 30)
		{
			m_ParentObject->AddPositionY(0.05f);
		}
		m_Cnt++;
	}


	//ファーストパーソンビュー
	{
		//m_Target = pPlayer->GetPosition() + pPlayer->GetForward();
		//m_Position = pPlayer->GetPosition();
	}
	//bool Pushflag = false;
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	Pushflag = true;
	//	if (!m_FreeFlag && Pushflag)
	//	{
	//		m_FreeFlag = true;
	//		Pushflag = false;
	//	}
	//	if (m_FreeFlag && Pushflag)
	//	{
	//		m_FreeFlag = false;
	//		Pushflag = false;
	//	}
	//}

	if (m_TestFlag)
	{
		m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		float angle = atan2f(m_Target.x - m_ParentObject->GetPosition().x,
			m_Target.z - m_ParentObject->GetPosition().z);

		//三角関数での移動(前)
		if (GetKeyboardPress(DIK_W))
		{
			m_ParentObject->AddPositionX(sinf(angle) * 0.1f);
			m_ParentObject->AddPositionZ(cosf(angle) * 0.1f);

		}
		//三角関数での移動(左)
		if (GetKeyboardPress(DIK_A))
		{
			m_ParentObject->AddPositionX(-(cosf(angle) * 0.1f));
			m_ParentObject->AddPositionZ(sinf(angle) * 0.1f);
		}
		//三角関数での移動(右)
		if (GetKeyboardPress(DIK_D))
		{
			m_ParentObject->AddPositionX(cosf(angle) * 0.1f);
			m_ParentObject->AddPositionZ(-(sinf(angle) * 0.1f));
		}
		//三角関数での移動(後)
		if (GetKeyboardPress(DIK_S))
		{
			m_ParentObject->AddPositionX(-(sinf(angle) * 0.1f));
			m_ParentObject->AddPositionZ(-(cosf(angle) * 0.1f));
		}

		if (GetKeyboardPress(DIK_RSHIFT))
		{
			m_ParentObject->AddPositionY(0.1f);
		}
		if (GetKeyboardPress(DIK_RCONTROL))
		{
			m_ParentObject->AddPositionY(-0.1f);
		}

	}

	if (m_FreeFlag)
	{
		if (GetKeyboardPress(DIK_UP))
		{
			m_ParentObject->AddPositionZ(-0.5f);

		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			m_ParentObject->AddPositionZ(0.5f);
		}
		if (GetKeyboardPress(DIK_LEFT))
		{
			m_ParentObject->AddPositionX(-0.5f);
		}
		if (GetKeyboardPress(DIK_RIGHT))
		{
			m_ParentObject->AddPositionX(0.5f);
		}

		if (GetKeyboardPress(DIK_I))
		{
			m_Target.z -= 0.5f;
		}
		if (GetKeyboardPress(DIK_K))
		{
			m_Target.z += 0.5f;
		}
		if (GetKeyboardPress(DIK_J))
		{
			m_Target.x -= 0.5f;
		}
		if (GetKeyboardPress(DIK_L))
		{
			m_Target.x += 0.5f;
		}
	}

}


//=============================================================================
// カメラの更新
//=============================================================================
void Camera::Draw(void)
{
	Scene* scene = Manager::GetScene();
	// ビューマトリックス設定
	D3DXVECTOR3 pos = m_ParentObject->GetPosition();
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &pos, &m_Target,
		&up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	GameObject* prism = scene->GetGameObject("Prizm", scene->UI_LAYER);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	if (prism == nullptr)
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
			(float)SCREEN_RESOLUTION_WIDTH / SCREEN_RESOLUTION_HEIGHT, 1.0f, 1000.0f);
		Renderer::SetProjectionMatrix(&projectionMatrix);
	}
	else if (prism != nullptr)
	{
		float det;
		D3DXMatrixInverse(&m_InvViewMatrix, &det, &m_ViewMatrix);

		// プロジェクションマトリックス設定
		D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_RESOLUTION_WIDTH / (float)SCREEN_RESOLUTION_HEIGHT, 1.0f, 10000);

		Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
		Renderer::SetDepthEnable(true);
	}
	//カメラの座標をシェーダーに渡す
	Renderer::SetCameraPosition(m_ParentObject->GetPosition());

}

// 視錐台カリング
bool Camera::CheckView(D3DXVECTOR3 pos)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	//vpの逆行列の計算
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	//3次元ベクトルに行列を掛ける
	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = pos - m_ParentObject->GetPosition();

	//左面判定
	{
		v1 = wpos[0] - m_ParentObject->GetPosition();
		v2 = wpos[2] - m_ParentObject->GetPosition();
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}
	}

	//右面判定
	{
		v1 = wpos[3] - m_ParentObject->GetPosition();
		v2 = wpos[1] - m_ParentObject->GetPosition();
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}
	}

	return true;
}