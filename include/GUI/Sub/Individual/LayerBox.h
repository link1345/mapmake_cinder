/*! @addtogroup GUIサブウィンドウ
	@file       LayerBox.h
	@brief      ImGuiを使ったレイヤーウィンドウ処理について書いている
	@note		上位にSubWindow.hがある。
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

		class LayerWindow {
		public:
			void draw();

			float menu_size;
		};

	}
}