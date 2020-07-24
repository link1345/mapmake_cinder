/*! @addtogroup �f�[�^
	@file       AllData.h
	@brief      �ŏ�ʂɑ��݂���f�[�^�Ǘ��p�̏���
	@date       2020/06/25
*/

#pragma once

#if defined(GLOBAL_HERE)
#define EXT
#define DEF(x) = (x)
#else
#define EXT extern
#define DEF(x)
#endif

#include <cinder/gl/Texture.h>
#include <cinder/Surface.h>

#include "Data/Basis/Tree.h"

#include "Data/GroundData.h"

#include "TerrainData.h"

#include "WindowData.h"
#include "FileData.h"

#include "IconData.h"

namespace MapMakeData {

	class AllData {
	public:
		AllData();
		~AllData() {};

		void init();

		/*! @brief �܂�����ȏ�����Ԃɂ���֐�
			@note ���ɂȂ�
		*/
		void reset();

		/*! @brief Cinder����̏������֐�
			@note ImGui�������֐��Ȃǂ̌�Ɏ��s���Ă��������B
		*/
		//void CinderLoad();

		/*! @brief �e�X�g�p�̃f�[�^�Z�b�g�֐�
			@param[in]	mode	�f�[�^���[�h�̐ݒ�
			@note ���ɂȂ��B(��ŏ���)
		*/
		void setSampleData(int mode);

		/*! @brief �E�B���h�E���
			@note  window�X���ł̓J�o�[�ł��Ȃ��͈͂̃f�[�^�ۊǏ�
		 */
		MapMakeData::Window::WindowData windowData;

		/*! @brief ��n��� */
		//std::map<std::string, Layer::LayerData> layerData;
		MapMakeData::Ground::GroundData groundData;

		/*! @brief �n�`�y����� */
		MapMakeData::Terrain::TerrainData terrainData;

		/*! @brief �t�@�C��������� */
		MapMakeData::File::FileData fileData;

		/*! @brief �k���C���[�Wgeter
			@return         this->NullImage
			@exception      none
		*/
		gl::Texture2dRef nullImage() { return this->NullImage; };

		map<Icon, gl::Texture2dRef> icon;

		string license;

	private:
		/*! @brief �k���C���[�W
			@note ���̃f�[�^�̃Q�b�^�[
			@relates this->nullImage();
		*/
		gl::Texture2dRef NullImage;


	};



	// �O���[�o���ϐ��B
	/*! �S�̂𓝊�����O���[�o���ϐ� */
	EXT AllData MainData;

}