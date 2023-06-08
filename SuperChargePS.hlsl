#include "Common.hlsl"
//自分のやつ

Texture2D g_Texture : register(t0); //テクスチャ０番

SamplerState g_SamplerState : register(s0); //サンプラー０番

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//ピクセルの法線を正規化
	//頂点シェーダーから出力された法線は直線補間（法線の長さが違う）
	//状態なので正規化して一定の長さにする必要がある
    float4 normal = normalize(In.Normal);

	//光源計算をする
    float light = -dot(normal.xyz, Light.Direction.xyz);

	//視線ベクトルの作成
	//カメラからピクセルへ向かうベクトル
    float3 eyev = In.WorldPosition - CameraPosition;
    eyev = normalize(eyev); //正規化する

	//視線と法線の内積を明るさに変換する
    float rim = 1.0 + dot(eyev, normal.xyz);
    rim = pow(rim, 2) * 2.0f;
    rim = saturate(rim); //値をサチュレート


	//テクスチャのピクセル色を取得
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= In.Diffuse.rgb * light; //明るさを乗算
    outDiffuse.b += rim; //スペキュラ値をデフューズとして足しこむ
    outDiffuse.a = In.Diffuse.a; //αに明るさは関係ないので別計算

}