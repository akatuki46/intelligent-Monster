#include "Prism.h"
#include "main.h"
#include "renderer.h"
#include "Scene.h"
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "TextureContainer.h"

#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

//----- プリズム面モデル定義
//　（注意）法線ベクトル、テクスチャ座標は計算で求める
static VERTEX_3D prism_vertex[] = {
	//	Position						Normal				Diffuse						TexCoord
	{	{   0.0f,    0.0f, -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面０（右上）
	{	{   2.5f,    0.0f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
	{	{   0.0f,    2.5f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２

	{	{   0.0f,    0.0f, -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面１（右下）
	{	{   0.0f,    2.5f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
	{	{  -2.5f,    0.0f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２

	{	{   0.0f,    0.0f,  -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面２（左下）
	{	{  -2.5f,    0.0f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
	{	{   0.0f,   -2.5f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２

	{	{   0.0f,    0.0f, -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面３（左上）
	{	{   2.5f,    0.0f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
	{	{   0.0f,   -2.5f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２
};

void Prism::Init()
{


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//←ここと
	bd.ByteWidth = sizeof(VERTEX_3D) * 12;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない

	D3D11_SUBRESOURCE_DATA sd{};
	//ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = prism_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	// モデル角度、位置の初期化
	g_Prism.rotation = { 0, 0, 0 };
	g_Prism.position = { 0, 0, 0 };

	D3DXVECTOR3		v0, v1, v2;				// プリズム面の法線ベクトル計算用

	// プリズム面の法線ベクトルを計算・設定
	for (int i = 0; i < 4; i++)
	{
		v0 = prism_vertex[i * 3 + 1].Position - prism_vertex[i * 3].Position;
		v1 = prism_vertex[i * 3 + 2].Position - prism_vertex[i * 3].Position;
		D3DXVec3Cross(&v2, &v0, &v1);
		D3DXVec3Normalize(&v2, &v2);	// 正規化
		prism_vertex[i * 3].Normal =
		prism_vertex[i * 3 + 1].Normal =
		prism_vertex[i * 3 + 2].Normal = v2;
	}

	m_Name = "Prism";

}

void Prism::Uninit()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void Prism::Update()
{
	D3DXMATRIX		matRotateX;				// Ｘ軸回転マトリックス
	D3DXMATRIX		matRotateY;				// Ｙ軸回転マトリックス
	D3DXMATRIX		matRotateZ;				// Ｚ軸回転マトリックス
	D3DXMATRIX		matTrans;				// 平行移動マトリックス
	D3DXMATRIX		matRotation;			// 回転マトリックス（合成後）
	D3DXVECTOR3		v_norm;					// 法線ベクトル
	D3DXVECTOR3		v_norm2;				// 法線ベクトル（回転後）
	D3DXVECTOR3		v_vtx;					// モデルの頂点への位置ベクトル
	D3DXVECTOR3		v_vtx2;					// モデルの頂点への位置ベクトル（回転後）
	D3DXVECTOR3		v_view2;				// 頂点から視点へのベクトル
	D3DXVECTOR3		v_ref;					// 屈折ベクトル
	D3DXVECTOR3		v_tmp;					// テンポラリ
	D3DXVECTOR3		bg_norm;				// ＢＧ面の法線ベクトル
	D3DXVECTOR3		v_pos;					// 屈折ベクトルとテクスチャ面との交点
	D3DXVECTOR3		v0, v1, v2;				// プリズム面の法線ベクトル計算用
	float		ref_rate_v, ref_rate_t;	// 屈折ベクトル計算用一時変数
	float		rrv_rrt, rrv2_rrt2;
	float		ans_InnerProduct;
	float		tmp0;
	float		n;
	int			i;

	// キーによる視点位置およびプリズムモデルの移動
	if (GetKeyboardPress(DIK_UP)) g_Prism.position[1] += 0.1f;	// カーソル（上）
	if (GetKeyboardPress(DIK_DOWN)) g_Prism.position[1] -= 0.1f;	// カーソル（下）
	if (GetKeyboardPress(DIK_LEFT)) g_Prism.position[0] -= 0.1f;	// カーソル（左）
	if (GetKeyboardPress(DIK_RIGHT)) g_Prism.position[0] += 0.1f;	// カーソル（右）
	// 自動的に回転
	g_Prism.rotation.z += 0.01f;

	// ワールドマトリックスを合成
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matRotateX, g_Prism.rotation.x);	// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, g_Prism.rotation.y);	// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, g_Prism.rotation.z);	// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans,
		g_Prism.position.x, g_Prism.position.y, g_Prism.position.z);	// 平行移動マトリックスを生成

	// 行列積の左右関係がOpenGLと逆
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixMultiply(&matRotation, &matRotateX, &matRotation);	// 回転マトリックスを合成
	D3DXMatrixMultiply(&matRotation, &matRotateY, &matRotation);	// 回転マトリックスを合成
	D3DXMatrixMultiply(&matRotation, &matRotateZ, &matRotation);	// 回転マトリックスを合成
	D3DXMatrixMultiply(&matWorld, &matRotation, &matTrans);			// ワールドマトリックスを合成

	Scene* scene = Manager::GetScene();
	GameObject *camera = scene->GetGameObject("Camera", scene->CAMERA_LAYER);

	for (i = 0; i < 3 * 4; i++)		// モデルは３頂点＊４面
	{
		// プリズムモデルの頂点にある法線ベクトルをワールド空間へ「回転」
		v_norm = prism_vertex[i].Normal;
		D3DXVec3TransformCoord(&v_norm2, &v_norm, &matRotation);
		D3DXVec3Normalize(&v_norm2, &v_norm2);	// 正規化

		// モデルの頂点をワールド空間へ変換し、視点への方向ベクトルを求める
		v_vtx = prism_vertex[i].Position;
		D3DXVec3TransformCoord(&v_vtx2, &v_vtx, &matWorld);
		v_view2 = camera->GetPosition() - v_vtx2;
		D3DXVec3Normalize(&v_view2, &v_view2);	// 正規化

		//========================================================================
		//
		//    ここに以下のようなプログラムを追加する
		//
		//    ＊　屈折の計算式から屈折ベクトルを求める　＊
		//　　１：屈折率（２個）を変数に設定（ 1.0 と 1.2 を使用）
		//　　２：屈折の計算式中にある「内積」値を計算
		//　　　　（使用する値は先に求めてある v_norm2 と v_view2 を利用）
		//　　３：屈折率、計算値を使って屈折ベクトル v_ref を求める
		//
		//========================================================================
		// （解答例）*************************************************************
		// 屈折の計算式から屈折ベクトルを求める
		ref_rate_v = 1.0f;
		ref_rate_t = 1.2f;
		rrv_rrt = ref_rate_v / ref_rate_t;
		rrv2_rrt2 = (ref_rate_v * ref_rate_v) / (ref_rate_t * ref_rate_t);
		ans_InnerProduct = D3DXVec3Dot(&v_norm2, &v_view2);
		tmp0 = rrv_rrt * ans_InnerProduct - sqrtf(1.0f - rrv2_rrt2 * (1.0f - ans_InnerProduct * ans_InnerProduct));
		v_ref = tmp0 * v_norm2 - rrv_rrt * v_view2;
		//************************************************************************

		// 屈折ベクトルの線上とテクスチャ面との交点を求める
		//
		// (公式)
		// 位置ベクトルx0の点からベクトルmの方向に直線を延ばすとき
		// 平面の法線ベクトルがn、平面上の任意の点の位置ベクトルをxとすると
		// 直線と平面の交点の位置ベクトルは
		//		x0 + ((x-x0)・n / m・n)m	※「・」はベクトル同士の内積
		// で求められる
		// https://risalc.info/src/line-plane-intersection-point.html
		//
		// OpenGL(右手座標系)とDirectX(左手座標系)の違い(Zが逆)に注意
		v_tmp = D3DXVECTOR3(0.0f, 0.0f, -80.0f) - v_vtx2;	// ここの定数は適当
		bg_norm = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// ＢＧのテクスチャ面の法線ベクトル
		n = D3DXVec3Dot(&v_tmp, &bg_norm) / D3DXVec3Dot(&v_ref, &bg_norm);
		v_pos = v_vtx2 + n * v_ref;

		// 交点座標を実際のテクスチャ座標に変換
		prism_vertex[i].TexCoord.x = 0.5f + v_pos.x * 0.001f;
		prism_vertex[i].TexCoord.y = 0.5f + v_pos.y * 0.001f;

		// テクスチャ座標もOpenGLと上下が逆
		prism_vertex[i].TexCoord.y = 1 - prism_vertex[i].TexCoord.y;
	}
}

void Prism::Draw()
{
	// 描画
// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// 頂点バッファ(テクスチャ座標)更新
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, prism_vertex, sizeof(VERTEX_3D) * 12);
	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// ワールドマトリックスの設定
	Renderer::SetWorldMatrix(&matWorld);

	TextureContainer::ModelDraw("Prism",12);
}
