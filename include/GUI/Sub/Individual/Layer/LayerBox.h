/*! @addtogroup GUIサブウィンドウ
	@file       LayerBox.h
	@brief      レイヤーウィンドウ(ImGui)に関する処理軍
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
#include "GUI/Widgets/NoTextTreeNodeWidgets.h"

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


			class Edit {
			public :
				Edit() {};
				~Edit() {};

				GUI::SubWindow::Sub::editData removeData;
				GUI::SubWindow::Sub::editData upfileData;
				GUI::SubWindow::Sub::editData addData;
				GUI::SubWindow::Sub::editData editData;
				GUI::SubWindow::Sub::moveData moveData;


			};


		}

		class LayerWindow : public GUI::WindowBase{
		public:
			LayerWindow() : WindowBase(){
				// とりあえず、初期化だけはしておく。
				this->image = MapMakeData::MainData.nullImage();
				this->groundKey = "";
			}
			LayerWindow(string groundKey) : WindowBase() {
				// とりあえず、初期化だけはしておく。
				this->image = MapMakeData::MainData.nullImage();
				this->groundKey = groundKey;
			}
			~LayerWindow() {};

			void draw(string mID) override;

			string groundKey;

			/*! @brief	使用用途予定未定の画像。とりあえず、使う予定だけはあるので…、許してちょ！
			*/
			gl::Texture2dRef image;
		};

	}
}