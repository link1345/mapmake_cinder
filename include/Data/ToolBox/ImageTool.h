#pragma once

#include <cinder/gl/Texture.h>
#include <cinder/Surface.h>
#include <cinder/CinderImGui.h>

namespace ToolBox {
	namespace Image {
		/*! @brief �w�肳�ꂽ�F���甽�]�������摜��Ԃ��֐�
			@param[in]	icon	�摜
			@param[in]	backcolor	���]���ɂȂ�F
			@note ���ɂȂ��B
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

		/*! @brief �w�肳�ꂽ�F�ɒ��F���ĉ摜��Ԃ��֐�
			@param[in]	icon	�摜
			@param[in]	backcolor	�ύX��̐F
			@note ���ɂȂ��B
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
