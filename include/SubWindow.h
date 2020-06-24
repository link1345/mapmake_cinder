#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <variant>
#include <vector>
#include <map>

#include "AllData.h"

#include "TerrainTool.h"
#include "LayerBox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace GUI {
	namespace General_SubWindow {

		namespace Sub {

			enum class SubWindowType {
				LayerWindow,
				TerrainToolWindow
			};

			struct WindowNumber {
				string nodeName;
				size_t nodeID;
				SubWindowType type;

				WindowNumber() {
					this->nodeName = "";
					this->nodeID = 0;
					SubWindowType type = SubWindowType::TerrainToolWindow;
				}
				WindowNumber(string nodeName, size_t nodeID, SubWindowType type) {
					this->nodeName = nodeName;
					this->nodeID = nodeID;
					this->type = type;
				}
				bool operator==(const WindowNumber& other) // �R�s�[���
				{
					if (this->nodeID == other.nodeID &&
						this->nodeName == other.nodeName &&
						this->type == other.type ) {
						return true;
					}
					else return false;
				}
			};

			/*
			struct Window
			{
				WindowNumber ID;

				std::variant <
					GUI::SubWindow::TerrainToolWindow,
					GUI::SubWindow::LayerWindow
				> subWindow;
			};
			*/

		}

		class General {
		public:
			General() {
				this->Windows.clear();

				this->LimitPop[Sub::SubWindowType::LayerWindow] = 1;
				this->LimitPop[Sub::SubWindowType::TerrainToolWindow] = 1;
			}

			// �E�B���h�E�ꗗ
			// (�� ���̂Ƃ��뉺�̃o�[�W�������g�����ƍl���Ă��܂����A����ȃv���O�����ɂȂ�悤�Ȃ�A��̂��g���܂��B�@2020/06/24)
			//std::vector<Sub::Window> Windows;
			std::map<Sub::WindowNumber, 
				std::variant <
				GUI::SubWindow::TerrainToolWindow,
				GUI::SubWindow::LayerWindow
				>
			> Windows;
			
			// �E�B���h�E��ʂ��ƂɋN�����Ă����A�������߂� (0 = ����)
			std::map<Sub::SubWindowType, int> LimitPop;
			// ���݋N�����Ă���E�B���h�E��ʂ̐�
			std::map<Sub::SubWindowType, int> NowPop;

		};

	}
}
