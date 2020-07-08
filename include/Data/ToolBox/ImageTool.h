#pragma once

#include <cinder/gl/Texture.h>
#include <cinder/Surface.h>
#include <cinder/CinderImGui.h>

namespace ToolBox {
	namespace Image {
		/*! @brief 指定された色から反転させた画像を返す関数
			@param[in]	icon	画像
			@param[in]	backcolor	反転元になる色
			@note 特になし。
		*/
		static void Icon_ColorInverse(cinder::Surface& icon, ImGuiCol_ backcolor) {
			auto color = ImGui::GetStyleColorVec4(backcolor);
			
			cinder::Surface::Iter iter = icon.getIter();
			while (iter.line()) {
				while (iter.pixel()) {
					iter.r() = 255 - color.x;
					iter.g() = 255 - color.y;
					iter.b() = 255 - color.z;
				}
			}
		}

		/*! @brief 指定された色に着色して画像を返す関数
			@param[in]	icon	画像
			@param[in]	backcolor	変更先の色
			@note 特になし。
		*/
		static void Icon_ColorChange(cinder::Surface& icon, ImGuiCol_ cColor) {
			auto color = ImGui::GetStyleColorVec4(cColor);

			cinder::Surface::Iter iter = icon.getIter();
			while (iter.line()) {
				while (iter.pixel()) {
					iter.r() = color.x;
					iter.g() = color.y;
					iter.b() = color.z;
				}
			}
		}
	}

}
