#pragma once

#include <variant>
#include <vector>
#include <map>
#include <string>

#include "GUI/System/Individual/StartWindow.h"

using namespace std;

typedef std::variant<GUI::System::StartWindow> SVData;


namespace GUI {
	namespace General_SystemWindow {

		namespace Sub {

			/*!
			@brief �E�B���h�E�̎�ʂ̗񋓌^
			@attention �V�����E�B���h�E��ʂ��o������A�K�������ɒǉ����Ă��������B
			*/
			enum class SysWindowType {
				StartWindow
			};

			/*!
			@brief �E�B���h�EID�̕ۑ�
			*/
			struct WindowNumber {
				string nodeName;
				size_t nodeID;
				SysWindowType type;

				WindowNumber() {
					this->nodeName = "";
					this->nodeID = 0;
					SysWindowType type = SysWindowType::StartWindow;
				}
				WindowNumber(string nodeName, size_t nodeID, SysWindowType type) {
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




		class sysGeneral {
		public:
			sysGeneral() {
				this->Windows.clear();

				this->NowPop.clear();

			}

			/*!
			@brief �E�B���h�E�ꗗ
			@note  (�� ���̂Ƃ���L�q�ς݂̃o�[�W�������g�����ƍl���Ă��܂����A����ȃv���O�����ɂȂ�悤�Ȃ�A���L�̂��g���܂��B�@2020/06/24)
			@note Key=ID�f�[�^ , �l = variant�ɓo�^���Ă���ϐ��̌^�Ȃ牽�ł�
			@code std::vector<Sub::Window> Windows;
			*/
			std::map<Sub::WindowNumber, SVData> Windows;

			void draw();

			void add(Sub::WindowNumber key, SVData data);

			void remove(Sub::WindowNumber key);

			/*! @brief ���݋N�����Ă���E�B���h�E��ʂ̐� */
			std::map<Sub::SysWindowType, int> NowPop;

		};

	}
}

