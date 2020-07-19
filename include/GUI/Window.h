#pragma once

#include <variant>
#include <vector>
#include <map>

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <cinder/CinderImGui.h>

#include "GUI/System/Individual/StartWindow.h"
#include "GUI/Sub/Individual/TerrainTool.h"
#include "GUI/Sub/Individual/Layer/LayerBox.h"
#include "GUI/Sub/Individual/Layer/LayerSetting.h"

#include "GUI/Sub/Individual/Ground/Ground.h"
#include "GUI/Sub/Individual/Ground/GroundSetting.h"

#include "GUI/Sub/Individual/Mask/Mask.h"


using namespace ci;
using namespace ci::app;
using namespace std;


// ----- ���������������邾���ŁA�V�E�B���h�E��ǉ��ł��܂��B ------
using VData = std::variant<
	GUI::SubWindow::TerrainToolWindow ,
	GUI::SubWindow::LayerWindow ,
	GUI::System::StartWindow ,
	GUI::SubWindow::LayerSettingWindow ,
	GUI::SubWindow::GroundWindow ,
	GUI::SubWindow::GroundSettingWindow , 
	GUI::SubWindow::MaskWindow
>;
// -----------------------------------------------------------------

namespace GUI {
	namespace General_Window {

		namespace Sub {

			/*!
			@brief �E�B���h�E�̎�ʂ̗񋓌^(��)
			@attention �V�����E�B���h�E��ʂ��o������A�K�������ɒǉ����Ă��������B
			*/
			using WindowType = size_t;

			/*!
			@brief �E�B���h�EID�̕ۑ�
			*/
			struct WindowNumber {
				string nodeName;
				size_t nodeID;
				WindowType type;

				WindowNumber() {
					this->nodeName = "";
					this->nodeID = 0;
					this->type = 0;
				}
				WindowNumber(string nodeName, size_t nodeID, WindowType type) {
					this->nodeName = nodeName;
					this->nodeID = nodeID;
					this->type = type;
				}
				bool operator==(const WindowNumber& other) // �R�s�[���
				{
					if (this->nodeID == other.nodeID &&
						this->nodeName == other.nodeName &&
						this->type == other.type) {
						return true;
					}
					else return false;
				}
				bool operator<(const WindowNumber& right) const {
					if (this->nodeID < right.nodeID) {
						return true;
					}
					else if (this->nodeID == right.nodeID) {
						if (this->nodeName < right.nodeName) {
							return true;
						}
						else if (this->nodeName == right.nodeName) {
							if (this->type < right.type) {
								return true;
							}
						}
					}
					return false;

				}
			};
		}


		/*!
		@brief �E�B���h�E�̈ꗗ���Ǘ�����N���X
		@attention ���̃N���X�́A�E�B���h�E�̘g���쐬����N���X�̊Ǘ��ł����āAopengl�̕`��Ǘ��ł͂���܂���B\n
		�܂��A���̏����̕ϐ��Ɋւ���_�ɂ��ẮA�O���ƘA�g���K�v�ȏꍇ�̂݁A�O���[�o��MapMakeData::MainData�ɋL�q����悤�ɂ��Ă��������B
		@sa �O���[�o��MapMakeData::MainData�Ɗ֌W���Ă���
		*/
		class General {
		public:
			General() {
				this->Windows.clear();

				this->NowPop.clear();
				this->LimitPop.clear();
				
				this->LimitPop[typeid(GUI::System::StartWindow).hash_code()] = 1;

				this->LimitPop[typeid(GUI::SubWindow::GroundWindow).hash_code()] = 1;
				this->LimitPop[typeid(GUI::SubWindow::LayerWindow).hash_code()] = 1;
				this->LimitPop[typeid(GUI::SubWindow::TerrainToolWindow).hash_code()] = 1;
			}

			/*!	@brief	�E�B���h�E�`��֐�
			*/
			void draw();

			/*!	@brief	�E�B���h�E��ǉ�
			*/
			void add(Sub::WindowNumber key, VData data);

			/*!	@brief	�E�B���h�E���폜
			*/
			void remove(Sub::WindowNumber key);

			/*!
			@brief �E�B���h�E�ꗗ
			@note  (�� ���̂Ƃ���L�q�ς݂̃o�[�W�������g�����ƍl���Ă��܂����A����ȃv���O�����ɂȂ�悤�Ȃ�A���L�̂��g���܂��B�@2020/06/24)
			@note Key=ID�f�[�^ , �l = variant�ɓo�^���Ă���ϐ��̌^�Ȃ牽�ł�
			@code std::vector<Sub::Window> Windows;
			*/
			std::map<Sub::WindowNumber, VData > Windows;

			/*! @brief �E�B���h�E��ʂ��ƂɋN�����Ă����������߂� (0 = ����) */
			std::map<Sub::WindowType, int> LimitPop;

			/*! @brief ���݋N�����Ă���E�B���h�E��ʂ̐� */
			std::map<Sub::WindowType, int> NowPop;

		};

	}
}