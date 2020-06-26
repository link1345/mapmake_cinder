/*! @addtogroup [GUI�Ǘ�]�T�u�E�B���h�E�n����
	@file       SubWindow.h
	@brief      �T�u�E�B���h�E��������ɂ���
	@note		���C�����j���[�o�[�Ɣw�i�ȊO��GUI�����Ɋւ������
				\n��ʂ�GUI.h������B
	@date       2020/06/25
*/


#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <variant>
#include <vector>
#include <map>

#define GLOBAL_HERE
#include "Data/AllData.h"

#include "GUI/Sub/Individual/TerrainTool.h"
#include "GUI/Sub/Individual/LayerBox.h"

using namespace ci;
using namespace ci::app;
using namespace std;


namespace GUI {
	namespace General_SubWindow {

		namespace Sub {

			/*!
			@brief �E�B���h�E�̎�ʂ̗񋓌^
			@attention �V�����E�B���h�E��ʂ��o������A�K�������ɒǉ����Ă��������B
			*/
			enum class SubWindowType {
				LayerWindow,
				TerrainToolWindow
			};

			/*!
			@brief �E�B���h�EID�̕ۑ�
			*/
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

				this->LimitPop[Sub::SubWindowType::LayerWindow] = 1;
				this->LimitPop[Sub::SubWindowType::TerrainToolWindow] = 1;
			}

			/*!
			@brief �E�B���h�E�ꗗ
			@note  (�� ���̂Ƃ���L�q�ς݂̃o�[�W�������g�����ƍl���Ă��܂����A����ȃv���O�����ɂȂ�悤�Ȃ�A���L�̂��g���܂��B�@2020/06/24)
			@note Key=ID�f�[�^ , �l = variant�ɓo�^���Ă���ϐ��̌^�Ȃ牽�ł�
			@code std::vector<Sub::Window> Windows;
			*/
			std::map<Sub::WindowNumber, 
				std::variant <
				GUI::SubWindow::TerrainToolWindow,
				GUI::SubWindow::LayerWindow,
				int
				>
			> Windows;
			
			/*!
			@brief 
			������windows�ϐ���draw���s�������ɂ��Ă������B
			*/
			void draw();

		private:
			/*! �E�B���h�E��ʂ��ƂɋN�����Ă����������߂� (0 = ����) */
			std::map<Sub::SubWindowType, int> LimitPop;
			/*! ���݋N�����Ă���E�B���h�E��ʂ̐� */
			std::map<Sub::SubWindowType, int> NowPop;

		};

	}
}
