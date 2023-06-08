#pragma once

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

//骨を動かしたときの皮膚の1頂点分の構造体
struct DEFORM_VERTEX
{
	aiVector3D    Position;
	aiVector3D    Normal;
	int           BoneNum;
	std::string   BoneName[4];//本来はボーンインデックスで管理すべき
	float         BoneWeight[4];
};

//ボーン構造体
struct BONE
{
	//骨の位置、角度等の行列
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 TransMatrix;
	aiMatrix4x4 OffsetMatrix;

};

class AnimetionModel 
{
private:
	const aiScene* m_AiScene = NULL;
	std::unordered_map<std::string, const aiScene*>m_Animetion;

	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;

	std::unordered_map<std::string,
		ID3D11ShaderResourceView*> m_Texture;

	//変形後頂点データ
	std::vector<DEFORM_VERTEX>* m_DeformVertex;

	//ボーンデータ（名前で参照）
	std::unordered_map<std::string, BONE> m_Bone;

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

public:
	void Load(const char* FileName);
	void LoadAnimetion(const char* FileName,
		std::string AnimationName);
	void Unload();
	void Update(std::string AnimationName1, std::string AnimationName2, float BlendRate, int Frame);
	void Draw();
};
