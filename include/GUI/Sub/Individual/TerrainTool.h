/*! @addtogroup [GUIサブウィンドウ]地形操作ツール処理
	@file       TerrainTool.h
	@brief      地形操作ツール(ImGUI)に関する処理群
	@note		上位にSubWindow.hがある。
	@date       2020/06/25
*/


#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <cinder/CinderImGui.h>

namespace GUI {
namespace SubWindow {

	// 地形ツール画面について
	class TerrainToolWindow {
	public:
		void draw();

	};

}
}