#include "TextureContainer.h"
#include <tchar.h> 

// ���f���f�[�^�{��
std::unordered_map<std::string, TextureData::Data*> TextureContainer::Texure;

void TextureContainer::Init()
{
	AddTexture("title", "asset/texture/title.png",D3DXVECTOR2(1.0f,1.0f), TextureData::Tag::Title);
	AddTexture("GameButton", "asset/texture/Button3.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Title);
	AddTexture("MakeButton", "asset/texture/Button2.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Title);

	AddTexture("Pore", "asset/texture/pore.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Title);

	AddTexture("Field", "asset/texture/fieldtest.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	
	AddTexture("HPOverRay", "asset/texture/HPOverRay.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("HP", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("RedHP", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("StaminaOverRay", "asset/texture/StaminaOverRay.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("Stamina", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("WorldClock", "asset/texture/Time.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("WorldTimer", "asset/texture/SecondHand.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("MiniMap", "asset/texture/MiniMap.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("PlayerPos", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("EnemyPos", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("Cloth", "asset/texture/TitleLogo.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Title);

	AddTexture("GameClear", "asset/texture/Gameclear.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Result);
	AddTexture("GameOver", "asset/texture/GameOver.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Result);

	AddTexture("Potion", "asset/texture/Potion.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("PotionG", "asset/texture/PotionG.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("MaxPotion", "asset/texture/MaxPotion.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("ItemOverRay", "asset/texture/ItemOverRay.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("Number", "asset/texture/number1.png", D3DXVECTOR2(5.0f, 5.0f), TextureData::Tag::Game);

	AddTexture("None", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("LoadLogo", "asset/texture/title.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_N", "asset/texture/Loading_N.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_O", "asset/texture/Loading_O.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_W", "asset/texture/Loading_W.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_L", "asset/texture/Loading_L.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_A", "asset/texture/Loading_A.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_D", "asset/texture/Loading_D.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_I", "asset/texture/Loading_I.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);
	AddTexture("Loading_G", "asset/texture/Loading_G.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Loading);



	AddTexture("Particle", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("Potion_Name", "asset/texture/Potion_Name.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("PotionG_Name", "asset/texture/PotionG_Name.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("MaxPotion_Name", "asset/texture/MaxPotion_Name.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("Fade", "asset/texture/fade_white.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Any);
	AddTexture("Start", "asset/texture/Start.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("StartTimerUI", "asset/texture/StartTimerUI.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("DethText", "asset/texture/DethText.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("LosText", "asset/texture/LosText.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("BackText", "asset/texture/BackText.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("OverText", "asset/texture/OverText.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("BaseCampMap", "asset/texture/BaseCampMap.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

	AddTexture("TargetText", "asset/texture/TargetText.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);
	AddTexture("ClearText", "asset/texture/ClearText.png", D3DXVECTOR2(1.0f, 1.0f), TextureData::Tag::Game);

}

// ���f���f�[�^�擾
void TextureContainer::ModelDraw(std::string name, int Vertex_Num)
{
	// ���f���f�[�^���擾
	TextureData::Data* data = Texure[name];

	// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
	if (!data->GetLoaded()) { return; }

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, data->GetTexture());

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(Vertex_Num, 0);

	
}

// ���f���f�[�^�擾
void TextureContainer::ModelDrawIndex(std::string name, int Vertex_Num)
{
	// ���f���f�[�^���擾
	TextureData::Data* data = Texure[name];

	// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
	if (!data->GetLoaded()) { return; }

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, data->GetTexture());

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed(Vertex_Num, 0, 0);


}


D3DXVECTOR2 TextureContainer::GetTextureDivi(std::string name)
{
	// ���f���f�[�^���擾
	TextureData::Data* data = Texure[name];

	// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
	if (!data->GetLoaded()) { return D3DXVECTOR2(0.0f,0.0f); }

	return data->GetDivision();
}

// ���f���f�[�^�ǂݍ���
void TextureContainer::Load(TextureData::Tag LoadModelTag)
{
	// ���f���f�[�^�{�̂�����
	for (auto data : Texure)
	{
		// �ǂݍ��ރ^�O�ƈ�v����ꍇ
		if (data.second->GetTag() == LoadModelTag)
		{
			// ���f���ǂݍ��ݍς݂̏ꍇ�͏������I��
			if (data.second->GetLoaded()) { continue; }

			// ���f���̓ǂݍ��ݏ������s��
			data.second->TextureLoad();
		}
	}
}

// ���f���f�[�^�j��
void TextureContainer::Unload(TextureData::Tag LoadModelTag)
{
	// ���f���f�[�^�{�̂�����
	for (auto data : Texure)
	{
		// �ǂݍ��ރ^�O�ƈ�v����ꍇ
		if (data.second->GetTag() == LoadModelTag)
		{
			// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
			if (!data.second->GetLoaded()) { continue; }

			// ���f���̓ǂݍ��ݏ������s��
			data.second->TextureUnload();
		}
	}
}

// ���f���f�[�^�j��
void TextureContainer::Uninit()
{
	// ���f���f�[�^�{�̂�����
	for (auto data : Texure)
	{

		// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
		if (data.second->GetLoaded()) {
			// ���f���̓ǂݍ��ݏ������s��
			data.second->TextureUnload();
		}

		delete data.second;
	}
}

// ���f���ǉ�
void TextureContainer::AddTexture(std::string modelName, std::string modelPass,D3DXVECTOR2 Division, TextureData::Tag modelTag)
{
	// ���f���f�[�^��o�^
	Texure[modelName] = new TextureData::Data(modelName, modelPass,Division, modelTag);
}
