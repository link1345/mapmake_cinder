#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "Tree.h"

using namespace ci;
using namespace ci::app;
using namespace ci::log;


namespace MapMakeData {
	namespace Sub {

		// �e���C���[���
		class LayerBoxData {
		public:
			LayerBoxData() {
				this->name = u8"";
				this->image2d = gl::Texture2dRef();
				this->image3d = gl::Texture2dRef();
				this->selectflag = false;
				this->shift_selectflag = false;

				this->layerfolder_flag = false;
			}

			LayerBoxData(std::string name, gl::Texture2dRef image2d, gl::Texture2dRef image3d,
				bool selectflag, bool shift_selectflag, bool layerfolder_flag) {
				this->name = name;
				this->image2d = image2d;
				this->image3d = image3d;
				this->selectflag = selectflag;
				this->shift_selectflag = shift_selectflag;

				this->layerfolder_flag = layerfolder_flag;
			}

			std::string name;
			gl::Texture2dRef image2d;
			gl::Texture2dRef image3d;
			bool selectflag;
			bool shift_selectflag;

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

	// ���C���[����̃f�[�^�ۑ��ꏊ�B
	class LayerData {
	public:
		LayerData() {
			this->layerTreeData.clear();
		}

		// �T���v���f�[�^�p
		void setSampleData(int mode);


		// �؍\���̃��C���[���
		Tree<Sub::LayerBoxData> layerTreeData;


		// �␳�p�֐��B
		// == ���C���[�c���[�𓊂���ƁA�q���������Ă���m�[�h�́A�t�H���_�Ƃ��Ẵt���O�������オ��B
		void layerFolderCorrection() {
			layerFolderCorrection_s(this->layerTreeData.pRoot);
		}

	private:
		void layerFolderCorrection_s(Node<Sub::LayerBoxData>& tree);

	};

}