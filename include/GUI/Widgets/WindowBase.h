#pragma once

#include <string>

#include "cinder/CinderImGui.h"

namespace GUI {

	/*!	@brief	GUI Window関係の基底クラス
	*/
	class WindowBase {
	public :
		WindowBase() {
			this->openFlag = true;
		};
		~WindowBase() {};

		/*! @brief 描画関数
		*/
		virtual void draw(std::string mID) {
			if (ImGui::Begin("test##0", &this->openFlag), ImGuiWindowFlags_AlwaysAutoResize) {
				
				ImGui::Text("testtesttesttest");

				ImGui::End();
			}
		};

		/*! @brief マウスカーソルをドラッグした時の関数
		*/
		virtual void update(std::string mID) {
		};

		/*! @brief マウスカーソルをドラッグした時の関数
		*/
		virtual void mouseDrag(std::string mID, MouseEvent event) {
		};


		/*! @brief ウィンドウの閉じるボタンが押されているか？
		*/
		bool openFlag;
	};
}