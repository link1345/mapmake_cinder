
#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

#include <cinder/CameraUi.h>

// my
#include "Data/AllData.h"
#include "GUI/Widgets/BoxWidgets.h"

#include "GUI/Widgets/WindowBase.h"

#include "GUI/Widgets/CanvasUi_ImGui.h"

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace ci::log;



namespace GUI {
	namespace SubWindow {

		namespace Sub {

		}

		class MaskWindow : public GUI::WindowBase {
		public:
			MaskWindow() : WindowBase() {
				itemID = NodeNumber();
				this->groundKey = "";

				this->listMouse.clear();
				this->listMesh.clear();
				this->mPoly.clear();

				this->defaultSize = ImVec2(1000.0f * MapMakeData::MainData.groundData.canvasSize, 1000.0f * (1 - MapMakeData::MainData.groundData.canvasSize));
				this->oldWindowSize = defaultSize;
				
				this->image = Surface((int)this->oldWindowSize.x, (int)this->oldWindowSize.y, false);
				this->resize_run(this->oldWindowSize, this->mFbo);

				this->startFlag = true;

			}

			MaskWindow(string groundKey, NodeNumber ID) : WindowBase() {
				this->groundKey = groundKey;
				this->itemID = ID;

				this->listMouse.clear();
				this->listMesh.clear();
				this->mPoly.clear();

				//this->defaultSize = ImVec2(1000.0f * ((float)MapMakeData::MainData.groundData.canvasSize / 100.0f),
				//	1000.0f * ( 1.0f - (float)MapMakeData::MainData.groundData.canvasSize / 100.0f));
				this->defaultSize = ImVec2(1000.0f * ((float)MapMakeData::MainData.groundData.canvasSize / 100.0f),
					1000.0f * ( 1.0f - (float)MapMakeData::MainData.groundData.canvasSize / 100.0f));

				
				this->oldWindowSize = defaultSize;

				this->image = Surface((int)this->oldWindowSize.x, (int)this->oldWindowSize.y, false);
				this->resize_run(this->oldWindowSize, this->mFbo);
								

				this->Convert_multiPoly();

				this->startFlag = true;

			}
			~MaskWindow() {};

			void draw(string mID) override;
			void update(string mID) override;

			bool startFlag;


			string groundKey;
			NodeNumber itemID;

			ImVec2 defaultSize;
			ImVec2 oldWindowSize;

			gl::FboRef mFbo;

			Surface image ;
		
			// ポリゴン
			vector<vec2> listMouse;

			vector<gl::VboMeshRef> listMesh;

			vector<PolyLine2f> mPoly;
			vector<PolyLine2f> mHolePoly;

			// 仮の筆の大きさ
			float penThick = 20;

			// mouse zoom
			tools::CanvasUi_ImGui ui = tools::CanvasUi_ImGui();



			void Convert_Fbo(vector<polygon>& aPoly);

			void Convert_multiPoly();

			void resize_run (ivec2 Size, gl::FboRef& mFbo)
			{
				this->resize_run(Size,vec2(),mFbo);

				return;
			};

			void resize_run(ivec2 Size , ivec2 minSize, gl::FboRef& mFbo)
			{
				vec2 tSize = vec2(Size.x - minSize.x, Size.y - minSize.y);

				auto format = gl::Fbo::Format().attachment(GL_COLOR_ATTACHMENT0, gl::Texture2d::create((int)tSize.x, (int)tSize.y));
				mFbo = gl::Fbo::create((int)tSize.x, (int)tSize.y, format);

				return;
			};


			// マウスの軌跡を渡すと、そのデータを使ってデータとして出してくれる。
			void image_f(ivec2 moniterSize, gl::FboRef& mFbo, vector<vec2> nowMouse);

			template <class T>
			gl::VboMeshRef MeshAdd(vec2 pos, T shape) {

				vector<gl::VboMesh::Layout> bufferLayout = {
				gl::VboMesh::Layout().usage(GL_DYNAMIC_DRAW).attrib(geom::Attrib::POSITION, 2),
				gl::VboMesh::Layout().usage(GL_STATIC_DRAW).attrib(geom::Attrib::TEX_COORD_0, 2)
				};

				auto mVboMesh = gl::VboMesh::create(shape, bufferLayout);
				
				auto mappedPosAttrib = mVboMesh->mapAttrib2f(geom::Attrib::POSITION, false);
				
				for (uint32_t i = 0; i < mVboMesh->getNumVertices(); i++) {
					vec2& mPos = *mappedPosAttrib;
					mappedPosAttrib->x = mPos.x + pos.x;
					mappedPosAttrib->y = mPos.y + pos.y;
					++mappedPosAttrib;
				}
				
				mappedPosAttrib.unmap();
				
				return mVboMesh;
			}


			template <class T>
			void pointAdd(vec2 pos, T shape) {

				float pen = 0;

				// 範囲外処理を抜いて置く。
				//if (pen <= pos.x &&
				//	pen <= pos.y &&
				//	ImGui::GetItemRectSize().x - pen >= pos.x &&
				//	ImGui::GetItemRectSize().y - pen >= pos.y) {

					if (ImGui::IsItemHovered()) {

						this->listMouse.push_back(pos);
						this->listMesh.push_back(this->MeshAdd(pos, shape));

					}

				//}

			}


			template <class T>
			void linearInterpolation(vec2 pos, T shape) {
				// 線形補間した上で頂点追加
				auto pos2 = listMouse.at(listMouse.size() - 1);

				// 2は2次元であるという意味。
				ublas::vector<float> v(2);
				v[0] = pos.x - pos2.x;
				v[1] = pos.y - pos2.y;

				int dot = 5;
				// ノルムで2次元上の直線を引く。
				auto ler = dot / ublas::norm_2(v);

				// 1.0f以下なら、頂点をましましにする。
				bool hit = false;
				for (auto sler = ler; sler <= 1.0f; sler = sler + ler) {
					auto p = lerp(pos2, pos, sler);

					this->pointAdd(p, shape);

					hit = true;
				}
				if (!hit) {
					this->pointAdd(pos, shape);					
				}

			}


		};

	}
}