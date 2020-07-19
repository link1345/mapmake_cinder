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


// ----- ここを書き換えるだけで、新ウィンドウを追加できます。 ------
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
			@brief ウィンドウの種別の列挙型(元)
			@attention 新しいウィンドウ種別が出来たら、必ずここに追加してください。
			*/
			using WindowType = size_t;

			/*!
			@brief ウィンドウIDの保存
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


		/*!
		@brief ウィンドウの一覧を管理するクラス
		@attention このクラスは、ウィンドウの枠を作成するクラスの管理であって、openglの描画管理ではありません。\n
		また、中の処理の変数に関する点については、外部と連携が必要な場合のみ、グローバルMapMakeData::MainDataに記述するようにしてください。
		@sa グローバルMapMakeData::MainDataと関係している
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

			/*!	@brief	ウィンドウ描画関数
			*/
			void draw();

			/*!	@brief	ウィンドウを追加
			*/
			void add(Sub::WindowNumber key, VData data);

			/*!	@brief	ウィンドウを削除
			*/
			void remove(Sub::WindowNumber key);

			/*!
			@brief ウィンドウ一覧
			@note  (※ 今のところ記述済みのバージョンを使おうと考えていますが、難解なプログラムになるようなら、下記のを使います。　2020/06/24)
			@note Key=IDデータ , 値 = variantに登録してある変数の型なら何でも
			@code std::vector<Sub::Window> Windows;
			*/
			std::map<Sub::WindowNumber, VData > Windows;

			/*! @brief ウィンドウ種別ごとに起動していい数を決める (0 = 無限) */
			std::map<Sub::WindowType, int> LimitPop;

			/*! @brief 現在起動しているウィンドウ種別の数 */
			std::map<Sub::WindowType, int> NowPop;

		};

	}
}