#pragma once

#include <string>

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
		virtual void draw(std::string mID) {
			if (ImGui::Begin("test##0", &this->openFlag), ImGuiWindowFlags_AlwaysAutoResize) {
				
				ImGui::Text("testtesttesttest");

				ImGui::End();
			}
		};

		/*! @brief �}�E�X�J�[�\�����h���b�O�������̊֐�
		*/
		virtual void update(std::string mID) {
		};

		/*! @brief �}�E�X�J�[�\�����h���b�O�������̊֐�
		*/
		virtual void mouseDrag(std::string mID, MouseEvent event) {
		};


		/*! @brief �E�B���h�E�̕���{�^����������Ă��邩�H
		*/
		bool openFlag;
	};
}