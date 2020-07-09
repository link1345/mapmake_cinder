/*! @addtogroup GUI�T�u�E�B���h�E
	@file       TerrainTool.h
	@brief      �n�`����c�[��(ImGUI)�Ɋւ��鏈���Q
	@note		��ʂ�SubWindow.h������B
	@date       2020/06/25
*/


#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <cinder/CinderImGui.h>

#include "GUI/Widgets/WindowBase.h"

namespace GUI {
namespace SubWindow {

	// �n�`�c�[����ʂɂ���
	class TerrainToolWindow : public GUI::WindowBase{
	public:
		void draw() override;

	};

}
}