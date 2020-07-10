#pragma once

#include "cinder/CinderImGui.h"

namespace GUI {

	/*!	@brief	GUI Window�֌W�̊��N���X
	*/
	class WindowBase {
	public :
		WindowBase() {
			this->openFlag = true;
		};
		~WindowBase() {};

		/*! @brief �`��֐�
		*/
		virtual void draw() {
			if (ImGui::Begin("test", &this->openFlag), ImGuiWindowFlags_AlwaysAutoResize) {
				
				ImGui::Text("testtesttesttest");

				ImGui::End();
			}
		};

		/*! @brief �E�B���h�E�̕���{�^����������Ă��邩�H
		*/
		bool openFlag;
	};
}