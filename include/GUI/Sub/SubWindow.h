/*! @addtogroup [GUI管理]サブウィンドウ系処理
	@file       SubWindow.h
	@brief      サブウィンドウ処理周りについて
	@note		メインメニューバーと背景以外のGUI処理に関するもの
				\n上位にGUI.hがある。
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
			@brief ウィンドウの種別の列挙型
			@attention 新しいウィンドウ種別が出来たら、必ずここに追加してください。
			*/
			enum class SubWindowType {
				LayerWindow,
				TerrainToolWindow
			};

			/*!
			@brief ウィンドウIDの保存
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
				bool operator==(const WindowNumber& other) // コピー代入
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
		@brief ウィンドウの一覧を管理するクラス
		@attention このクラスは、ウィンドウの枠を作成するクラスの管理であって、openglの描画管理ではありません。\n
		また、中の処理の変数に関する点については、外部と連携が必要な場合のみ、グローバルMapMakeData::MainDataに記述するようにしてください。
		@sa グローバルMapMakeData::MainDataと関係している
		*/
		class General {
		public:
			General() {
				this->Windows.clear();

				this->LimitPop[Sub::SubWindowType::LayerWindow] = 1;
				this->LimitPop[Sub::SubWindowType::TerrainToolWindow] = 1;
			}

			/*!
			@brief ウィンドウ一覧
			@note  (※ 今のところ記述済みのバージョンを使おうと考えていますが、難解なプログラムになるようなら、下記のを使います。　2020/06/24)
			@note Key=IDデータ , 値 = variantに登録してある変数の型なら何でも
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
			ここにwindows変数のdrawを行う処理についてを書く。
			*/
			void draw();

		private:
			/*! ウィンドウ種別ごとに起動していい数を決める (0 = 無限) */
			std::map<Sub::SubWindowType, int> LimitPop;
			/*! 現在起動しているウィンドウ種別の数 */
			std::map<Sub::SubWindowType, int> NowPop;

		};

	}
}
