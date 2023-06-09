//このファイルは他のシェーダーファイルへインクルードされます
//各種マトリクスを受け取る変数を用意
cbuffer WorldBuffer : register(b0)//定数バッファ0番
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)//定数バッファ1番
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)//定数バッファ2番
{
	matrix Projection;
}

cbuffer CameraBuffer : register(b5) //バッファの５番とする
{
	float4 CameraPosition; //カメラ座標を受けとる変数
}

struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}



//頂点シェーダーへ入力されるデータを構造体の形で表現
//これは頂点バッファの内容そのもの
struct VS_IN
{
	float4 Position      :POSITION0;//セマンティクスは頂点レイアウトに対応
	float4 Normal        :NORMAL0;
	float4 Diffuse       :COLOR0;
	float2 TexCoord      :TEXCOORD0;

};


//ピクセルシェーダーへ入力されるデータを構造体の形で表現
struct PS_IN
{
	float4 Position : SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

//ライトオブジェクト構造体とコンスタントバッファ
struct LIGHT
{
	bool Enable;
	bool3 Dummy; //配置アドレスを4の倍数にすると効率がいいので調整用
	float4 Direction; //実はC言語でも同じでVisualStudioがやってくれている。
	float4 Diffuse;
	float4 Ambient;
};

cbuffer LightBuffer : register(b4)//コンスタントバッファ４番とする
{
	LIGHT Light; //ライト構造体
}
