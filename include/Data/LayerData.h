/*! @addtogroup サブデータ
	@file       LayerData.h
	@brief		レイヤー画面で使用されるデータ保管
	@date       2020/06/27
*/

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

// ----------------------------------------
// * 以下のヘッダーは将来使わなくなります * 
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

		/*! @brief	レイヤー情報の詳細情報を保持するためのクラス
			@sa classLayerData(同ファイル)が、直に関係している。
		*/
		class LayerBoxData {
		public:
			LayerBoxData() {
				this->name = u8"";
				this->image2d = gl::Texture2dRef();
				this->image3d = gl::Texture2dRef();

				// デフォルトペンを設定する。
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

			/*! @brief	レイヤー名
			*/
			std::string name;

			/*! @brief	レイヤーイメージ図 2D
			*/
			gl::Texture2dRef image2d;
			
			/*! @brief	レイヤーイメージ図 3D
			*/
			gl::Texture2dRef image3d;

			/*! @brief	使用しているペンの種類
			*/
			TerrainPen::Sub::Key penKey;


			/*! @brief	選択中であるか true=選択中
			*/
			bool selectflag;

			/*! @brief	shiftキーを用いた選択中であるか true=選択中
			*/
			bool shift_selectflag;

			/*! @brief	フォルダであるか true=yes
			*/
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

		/*! @brief	レイヤー情報を保持するためのクラス
			@sa class LayerWindow(ImGui)は、この情報を直に関係している。
			他にもマップイメージ図の構築にも使用されている。
		*/
		class LayerData {
		public:
			LayerData();
			~LayerData() {};

			/*! @brief	=オペレータ
				@note	動作があやしぃ…かも
			*/
			LayerData operator =(const LayerData obj){
				return *this;
			}


			/*! @brief	サンプルデータ作成用関数
			*/
			void setSampleData(int mode);


			/*! @brief	木構造データ
			*/
			Tree<Sub::LayerBoxData> layerTreeData;

			/*! @brief	キャンバスサイズ
			*/
			int canvasSize;


			/*! @brief	レイヤー情報の補正用関数
				@note	レイヤーツリーを投げると、子供を持っているノードは、フォルダとしてのフラグが立ち上がる。
			*/
			void layerFolderCorrection() {
				layerFolderCorrection_s(this->layerTreeData.pRoot);
			}

		private:
			/*! @brief	this->layerFolderCorrection()の木構造参照関数
			*/
			void layerFolderCorrection_s(Node<Sub::LayerBoxData>& tree);

		};

	}
}