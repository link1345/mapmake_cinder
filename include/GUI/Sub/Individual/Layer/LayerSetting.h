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
#include "GUI/Widgets/NoTextTreeNodeWidgets.h"

#include "GUI/Widgets/WindowBase.h"

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace ci::log;


typedef class MapMakeData::Layer::Sub::LayerBoxData MLData;

namespace GUI {
	namespace SubWindow {

		namespace Sub {
		}

		class LayerSettingWindow : public GUI::WindowBase {
		public:
			LayerSettingWindow() : WindowBase() {
				this->startFlag = true;

				//this->inputLayerName = u8"�O�����h�L���j�I��";
				this->s = 0;

				this->addFlag = false;

				this->NameErrorFlag = false;

				
				this->sendData = MLData(u8"", MapMakeData::MainData.nullImage(), MapMakeData::MainData.nullImage(),
					MapMakeData::TerrainPen::Sub::Key()
					, false, false, false, u8"");

			}
			LayerSettingWindow(NodeNumber frontNumber, bool addFlag = false, int s = 0) : WindowBase() {
				this->startFlag = true;

				this->node = frontNumber;
				this->s = s;

				this->addFlag = addFlag;

				this->NameErrorFlag = false;


				this->sendData = MLData(u8"", MapMakeData::MainData.nullImage(), MapMakeData::MainData.nullImage(),
					MapMakeData::TerrainPen::Sub::Key()
					, false, false, false, u8"");
			}


			~LayerSettingWindow() {};

			void draw(string mID) override;

			bool startFlag;

			MLData sendData;

			/*! �ǉ���̏�� */
			NodeNumber node;
			int s;

			/*! �������̏��� */
			ImGuiTextFilter filter;

			/*! �y���̑I��ID */
			//MapMakeData::TerrainPen::Sub::Key item_current_idx;

			/*! �ǉ������邩�H true=add , false=insert */
			bool addFlag;

			/*! NameErrorFlag */
			bool NameErrorFlag;
		};

	}
}