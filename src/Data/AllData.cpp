#include "Resources.h"

#include "Data/AllData.h"

#include "Data/ToolBox/ImageTool.h"

namespace MapMakeData {

	AllData::AllData() {
		this->init();
	}

	void AllData::init() {

		this->groundData = MapMakeData::Ground::GroundData();
		//this->layerData.layerTreeData.clear();
		
		this->windowData = MapMakeData::Window::WindowData();

		this->terrainData = MapMakeData::Terrain::TerrainData();

	}

	void iconReset(map<Icon, gl::Texture2dRef>& icon , gl::Texture2dRef& nullimage) {
		// nullアイコン登録
		Surface s = Surface(loadImage(app::loadResource(RES_ICON_NULL)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		nullimage = gl::Texture::create(s);

		// 最初に全てのアイコンをnullアイコンで初期化しておく。(万が一のアイコン未設定対応)
		for (int i = 0; i < (int)Icon::Conut; i++) {
			icon[(Icon)i] = nullimage;
		}

		// アイコン登録
		s = Surface(loadImage(app::loadResource(RES_ICON_File)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_File] = gl::Texture::create(s);

		s = Surface(loadImage(app::loadResource(RES_ICON_FileNodata)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_FileNodata] = gl::Texture::create(s);

		s = Surface(loadImage(app::loadResource(RES_ICON_FileSearch)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_FileSearch] = gl::Texture::create(s);

		s = Surface(loadImage(app::loadResource(RES_ICON_FolderClose)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_FolderClose] = gl::Texture::create(s);

		s = Surface(loadImage(app::loadResource(RES_ICON_FolderOpen)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_FolderOpen] = gl::Texture::create(s);

		s = Surface(loadImage(app::loadResource(RES_ICON_Mountain)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_Mountain] = gl::Texture::create(s);

		s = Surface(loadImage(app::loadResource(RES_ICON_Brush)));
		ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
		icon[Icon::ICON_Brush] = gl::Texture::create(s);

	}

	void AllData::reset() {
		this->init();
		
		iconReset(this->icon, this->NullImage);
	}

	void AllData::setSampleData(int mode) {
		this->reset();

		//this->layerData.setSampleData(mode);
		this->groundData.setSampleData();

		this->terrainData.setSampleData(0);


	}

}
