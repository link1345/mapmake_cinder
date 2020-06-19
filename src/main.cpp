#include "main.h"

#include "Resources.h"


#include "cinder/gl/Context.h"
#include "imgui/imgui_impl_opengl3.h"

// == レイヤーツリーを投げると、子供を持っているノードは、フォルダとしてのフラグが立ち上がる。

void layerFolderCorrection_s(Node<LayerBoxData>& tree) {
	if (tree.pNext.size() == 0) {
		tree.data.layerfolder_flag = false;
	}else tree.data.layerfolder_flag = true;

	for (auto& leaf : tree.pNext){
		layerFolderCorrection_s(leaf);
	}
}

void layerFolderCorrection(Tree<LayerBoxData>& tree) {
	layerFolderCorrection_s(tree.pRoot);
}

// ===

void BasicApp::setup()
{	
	setFrameRate(10000.0f);

	mCam.lookAt(vec3(3, 3, 3), vec3(0));
	mCamUi = CameraUi(&mCam, getWindow() );
	
	ImGui::Initialize();
	ImGuiIO& io = ImGui::GetIO();
	static ImWchar font_japanese[0xFFFF];
	for (int i = 1; i < 0xFFFE; i++) {
		font_japanese[i - 1] = i;
	}

	io.Fonts->AddFontFromFileTTF(u8"C:\\Windows\\Fonts\\meiryo.ttc", 30.0f, NULL, font_japanese);
	
	
	getWindow()->getSignalDraw().connect(
		[this] {
			ShowMainMenuBar();
			ShowSubWindow();
			ShowLayerWindow();
		}
	);
	
	// ---

	//auto img = loadImage(loadAsset("image.jpg"));
	//texture1 = gl::Texture2d::create(img);
	texture1= gl::Texture::create(loadImage(loadAsset("Icon.png")));

	// treeを作成
	/*
	auto s1 = NodeNumber();
	auto data = LayerBoxData(u8"山1", texture1, texture1, false, false, false);
	layerTreeData.newID(s1, u8"LayerImage");
	layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s1, data));

	auto s2 = NodeNumber();
	data = LayerBoxData(u8"平地1", texture1, texture1, false, false, false);
	layerTreeData.newID(s2, u8"関東平地の情報");
	layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s2, data));
	auto s3 = NodeNumber();
	data = LayerBoxData(u8"平地2", texture1, texture1, false, false, false);
	layerTreeData.newID(s3, u8"関西の情報");
	layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s3, data));
	*/
	
	auto s1 = NodeNumber();
	auto data = LayerBoxData(u8"山1", texture1, texture1, false, false, false);
	layerTreeData.newID(s1, u8"LayerImage");
	layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s1, data));
	
	auto s2 = NodeNumber();
	data = LayerBoxData(u8"平地1", texture1, texture1, false, false, false);
	layerTreeData.newID(s2, u8"関東平地の情報");
	layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s2, data));
	auto s3 = NodeNumber();
	data = LayerBoxData(u8"平地1-1", texture1, texture1, false, false, false);
	layerTreeData.newID(s3, u8"千葉の情報");
	layerTreeData.add(s2, Node<LayerBoxData>(s3, data));
	auto s4 = NodeNumber();
	data = LayerBoxData(u8"平地1-1-1", texture1, texture1, false, false, false);
	layerTreeData.newID(s4, u8"LayerImage");
	layerTreeData.add(s3, Node<LayerBoxData>(s4, data));
	
	auto s5 = NodeNumber();
	data = LayerBoxData(u8"平地2", texture1, texture1, false, false, false);
	layerTreeData.newID(s5, u8"LayerImage");
	layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s5, data));
	auto s6 = NodeNumber();
	data = LayerBoxData(u8"平地2-1", texture1, texture1, false, false, false);
	layerTreeData.newID(s6, u8"LayerImage");
	layerTreeData.add(s5, Node<LayerBoxData>(s6, data));
	auto s7 = NodeNumber();
	data = LayerBoxData(u8"平地2-2", texture1, texture1, false, false, false);
	layerTreeData.newID(s7, u8"LayerImage");
	layerTreeData.add(s5, Node<LayerBoxData>(s7, data));
	
	// 補正を掛ける
	layerFolderCorrection(layerTreeData);
}

void BasicApp::createNewWindow()
{
}

void BasicApp::update(){	
}

void BasicApp::keyDown( KeyEvent event ) {
	if (event.getChar() == 'w') {
	}
	
}

void BasicApp::draw()
{
	gl::clear(Color(0.2f, 0.2f, 0.2f));
	gl::enableAlphaBlending();
	gl::setMatrices(mCam);

	gl::drawCube(vec3(), vec3(2));

	//Rectf drawRect(0, 0, texture1->getWidth() ,
	//	texture1->getHeight() );

	gl::setMatricesWindow(getWindowSize());

	//gl::draw(texture1,Area(ivec2(0,0), ivec2(texture1->getWidth(), texture1->getHeight())));



}

// This line tells Cinder to actually create the application
CINDER_APP(BasicApp, RendererGl )
