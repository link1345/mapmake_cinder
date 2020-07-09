/*! @addtogroup GUI�T�u�E�B���h�E
	@file       LayerBox.h
	@brief      ���C���[�E�B���h�E(ImGui)�Ɋւ��鏈���R
	@note		��ʂ�SubWindow.h������B
	@date       2020/06/25
*/

#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

// my
#include "Data/AllData.h"
#include "GUI/Widgets/BoxWidgets.h"

#include "GUI/Widgets/WindowBase.h"

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace ci::log;


namespace GUI {
	namespace SubWindow {

		namespace Sub {

			class editData {
			public:
				editData() {
					flag = false;
					id = NodeNumber();
				}
				bool flag;
				NodeNumber id;
			};

			class moveData {
			public:
				moveData() {
					flag = false;
					next = NodeNumber();
					payload_n = NodeNumber();
				}
				bool flag;
				NodeNumber next;
				NodeNumber payload_n;
			};

		}

		class LayerWindow : public GUI::WindowBase{
		public:
			LayerWindow() : WindowBase(){
				// �Ƃ肠�����A�����������͂��Ă����B
				this->image = MapMakeData::MainData.nullImage();
			}
			~LayerWindow() {};

			void draw() override;

			/*! @brief �g�p�p�r�\�薢��̉摜�B�Ƃ肠�����A�g���\�肾���͂���̂Łc�A�����Ă���I
			*/
			gl::Texture2dRef image;

		};

	}
}