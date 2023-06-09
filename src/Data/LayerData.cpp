#include "Data/LayerData.h"

typedef class MapMakeData::Layer::Sub::LayerBoxData LData;

namespace MapMakeData::Layer {

	LayerData::LayerData() {
		this->layerTreeData.clear();
		this->explanation = "";
	}

	void LayerData::setSampleData(int mode) {

		// 
		// テスト用画像
		Surface s = Surface(loadImage(app::loadResource(RES_ICON_NULL)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);

		auto texture1 = gl::Texture::create( s );

		// TextureクラスからSurfaceに戻せるよ！
		//s = texture1->createSource();

		// treeを作成
		if (mode == 1) {
			auto s1 = NodeNumber();
			auto data = LData(u8"山1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false,u8"○○山");
			layerTreeData.newID(s1, u8"LayerImage");
			layerTreeData.add(layerTreeData.rootID, Node<LData>(s1, data));

			auto s2 = NodeNumber();
			data = LData(u8"平地1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s2, u8"関東平地の情報");
			layerTreeData.add(layerTreeData.rootID, Node<LData>(s2, data));
			auto s3 = NodeNumber();
			data = LData(u8"平地2", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s3, u8"関西の情報");
			layerTreeData.add(layerTreeData.rootID, Node<LData>(s3, data));

		}
		else if (mode == 0) {
			
			auto s1 = NodeNumber();
			auto data = LData(u8"山1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"××山");
			layerTreeData.newID(s1, u8"LayerImage");
			layerTreeData.add(layerTreeData.rootID, Node<LData>(s1, data));
			
			auto s2 = NodeNumber();
			data = LData(u8"平地1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s2, u8"関東平地の情報");
			layerTreeData.add(layerTreeData.rootID, Node<LData>(s2, data));
			auto s3 = NodeNumber();
			data = LData(u8"平地1-1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s3, u8"千葉の情報");
			layerTreeData.add(s2, Node<LData>(s3, data));
			auto s4 = NodeNumber();
			data = LData(u8"平地1-1-1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s4, u8"LayerImage");
			layerTreeData.add(s3, Node<LData>(s4, data));

			auto s5 = NodeNumber();
			data = LData(u8"平地2", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s5, u8"LayerImage");
			layerTreeData.add(layerTreeData.rootID, Node<LData>(s5, data));
			auto s6 = NodeNumber();
			data = LData(u8"平地2-1", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s6, u8"LayerImage");
			layerTreeData.add(s5, Node<LData>(s6, data));
			auto s7 = NodeNumber();
			data = LData(u8"平地2-2", texture1, texture1, MapMakeData::TerrainPen::Sub::Key(), false, false, false, u8"平地");
			layerTreeData.newID(s7, u8"LayerImage");
			layerTreeData.add(s5, Node<LData>(s7, data));
			
		}

		// 補正を掛ける
		layerFolderCorrection();
	}

	
	void LayerData::layerFolderCorrection_s(Node<Sub::LayerBoxData>& tree) {
		if (tree.pNext.size() == 0) {
			tree.data.layerfolder_flag = false;
		}
		else tree.data.layerfolder_flag = true;

		for (auto& leaf : tree.pNext) {
			layerFolderCorrection_s(leaf);
		}
	}

}
