/*! @addtogroup �T�u�f�[�^
	@file       LayerData.h
	@brief		���C���[��ʂŎg�p�����f�[�^�ۊ�
	@date       2020/06/27
*/

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

// ----------------------------------------
// * �ȉ��̃w�b�_�[�͏����g��Ȃ��Ȃ�܂� * 
#include "Resources.h"
#include "Data/ToolBox/ImageTool.h"
// ----------------------------------------

#include "Data/Basis/Tree.h"

#include "Data/TerrainData.h"

using namespace ci;
using namespace ci::app;
using namespace ci::log;
using namespace NextStd;


namespace MapMakeData {
	namespace Layer {

	namespace Sub {

		/*! @brief	���C���[���̏ڍ׏���ێ����邽�߂̃N���X
			@sa classLayerData(���t�@�C��)���A���Ɋ֌W���Ă���B
		*/
		class LayerBoxData {
		public:
			LayerBoxData() {
				this->name = u8"";
				this->image2d = gl::Texture2dRef();
				this->image3d = gl::Texture2dRef();

				// �f�t�H���g�y����ݒ肷��B
				this->penKey = TerrainPen::Sub::Key();

				this->selectflag = false;
				this->shift_selectflag = false;

				this->layerfolder_flag = false;
			}

			LayerBoxData(std::string name, gl::Texture2dRef image2d, gl::Texture2dRef image3d,
				TerrainPen::Sub::Key penKey,
				bool selectflag, bool shift_selectflag, bool layerfolder_flag) {
				this->name = name;
				this->image2d = image2d;
				this->image3d = image3d;

				this->penKey = penKey;

				this->selectflag = selectflag;
				this->shift_selectflag = shift_selectflag;

				this->layerfolder_flag = layerfolder_flag;
			}

			~LayerBoxData() {};

			/*! @brief	���C���[��
			*/
			std::string name;

			/*! @brief	���C���[�C���[�W�} 2D
			*/
			gl::Texture2dRef image2d;
			
			/*! @brief	���C���[�C���[�W�} 3D
			*/
			gl::Texture2dRef image3d;

			/*! @brief	�g�p���Ă���y���̎��
			*/
			TerrainPen::Sub::Key penKey;


			/*! @brief	�I�𒆂ł��邩 true=�I��
			*/
			bool selectflag;

			/*! @brief	shift�L�[��p�����I�𒆂ł��邩 true=�I��
			*/
			bool shift_selectflag;

			/*! @brief	�t�H���_�ł��邩 true=yes
			*/
			bool layerfolder_flag;

		};

		// �c���[�ŏ�������Ƃ��ɕK�v�ȃI�y���[�^
		inline bool operator==(const Node<LayerBoxData>& lhs, const Node<LayerBoxData>& rhs) {
			if (lhs.ID == rhs.ID) {
				return true;
			}
			else {
				return false;
			}
		};

	}

		/*! @brief	���C���[����ێ����邽�߂̃N���X
			@sa class LayerWindow(ImGui)�́A���̏��𒼂Ɋ֌W���Ă���B
			���ɂ��}�b�v�C���[�W�}�̍\�z�ɂ��g�p����Ă���B
		*/
		class LayerData {
		public:
			LayerData();
			~LayerData() {};

			/*! @brief	=�I�y���[�^
				@note	���삪���₵���c����
			*/
			LayerData operator =(const LayerData obj){
				return *this;
			}


			/*! @brief	�T���v���f�[�^�쐬�p�֐�
			*/
			void setSampleData(int mode);


			/*! @brief	�؍\���f�[�^
			*/
			Tree<Sub::LayerBoxData> layerTreeData;

			/*! @brief	�L�����o�X�T�C�Y
			*/
			int canvasSize;


			/*! @brief	���C���[���̕␳�p�֐�
				@note	���C���[�c���[�𓊂���ƁA�q���������Ă���m�[�h�́A�t�H���_�Ƃ��Ẵt���O�������オ��B
			*/
			void layerFolderCorrection() {
				layerFolderCorrection_s(this->layerTreeData.pRoot);
			}

		private:
			/*! @brief	this->layerFolderCorrection()�̖؍\���Q�Ɗ֐�
			*/
			void layerFolderCorrection_s(Node<Sub::LayerBoxData>& tree);

		};

	}
}