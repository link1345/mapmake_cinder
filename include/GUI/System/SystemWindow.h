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
			@brief ウィンドウの種別の列挙型
			@attention 新しいウィンドウ種別が出来たら、必ずここに追加してください。
			*/
			enum class SysWindowType {
				StartWindow
			};

			/*!
			@brief ウィンドウIDの保存
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
				bool operator==(const WindowNumber& other) // コピー代入
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
			@brief ウィンドウ一覧
			@note  (※ 今のところ記述済みのバージョンを使おうと考えていますが、難解なプログラムになるようなら、下記のを使います。　2020/06/24)
			@note Key=IDデータ , 値 = variantに登録してある変数の型なら何でも
			@code std::vector<Sub::Window> Windows;
			*/
			std::map<Sub::WindowNumber, SVData> Windows;

			void draw();

			void add(Sub::WindowNumber key, SVData data);

			void remove(Sub::WindowNumber key);

			/*! @brief 現在起動しているウィンドウ種別の数 */
			std::map<Sub::SysWindowType, int> NowPop;

		};

	}
}

