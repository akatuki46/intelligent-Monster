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

//���𓮂������Ƃ��̔畆��1���_���̍\����
struct DEFORM_VERTEX
{
	aiVector3D    Position;
	aiVector3D    Normal;
	int           BoneNum;
	std::string   BoneName[4];//�{���̓{�[���C���f�b�N�X�ŊǗ����ׂ�
	float         BoneWeight[4];
};

//�{�[���\����
struct BONE
{
	//���̈ʒu�A�p�x���̍s��
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

	//�ό`�㒸�_�f�[�^
	std::vector<DEFORM_VERTEX>* m_DeformVertex;

	//�{�[���f�[�^�i���O�ŎQ�Ɓj
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
