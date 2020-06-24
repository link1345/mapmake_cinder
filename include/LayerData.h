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

		// 各レイヤー情報
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

		// ツリーで処理するときに必要なオペレータ
		inline bool operator==(const Node<LayerBoxData>& lhs, const Node<LayerBoxData>& rhs) {
			if (lhs.ID == rhs.ID) {
				return true;
			}
			else {
				return false;
			}
		};

	}

	// レイヤー周りのデータ保存場所。
	class LayerData {
	public:
		LayerData() {
			this->layerTreeData.clear();
		}

		// サンプルデータ用
		void setSampleData(int mode);


		// 木構造のレイヤー情報
		Tree<Sub::LayerBoxData> layerTreeData;


		// 補正用関数。
		// == レイヤーツリーを投げると、子供を持っているノードは、フォルダとしてのフラグが立ち上がる。
		void layerFolderCorrection() {
			layerFolderCorrection_s(this->layerTreeData.pRoot);
		}

	private:
		void layerFolderCorrection_s(Node<Sub::LayerBoxData>& tree);

	};

}