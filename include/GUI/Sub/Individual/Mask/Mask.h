
#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

// my
#include "Data/AllData.h"
#include "GUI/Widgets/BoxWidgets.h"

#include "GUI/Widgets/WindowBase.h"


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

				this->oldWindowSize = ImVec2(500, 500);

				this->image = Surface((int)this->oldWindowSize.x, (int)this->oldWindowSize.y, false);
				this->resize_run(this->oldWindowSize, this->mFbo);

				ImGui::SetNextWindowSize(this->oldWindowSize);
			}

			MaskWindow(string groundKey, NodeNumber ID) : WindowBase() {
				this->groundKey = groundKey;
				this->itemID = ID;

				this->listMouse.clear();
				this->listMesh.clear();
				this->mPoly.clear();

				this->oldWindowSize = ImVec2(500, 500);

				this->image = Surface((int)this->oldWindowSize.x, (int)this->oldWindowSize.y, false);
				this->resize_run(this->oldWindowSize, this->mFbo);

				ImGui::SetNextWindowSize(this->oldWindowSize);
			}
			~MaskWindow() {};

			void draw(string mID) override;
			void update(string mID) override;

			string groundKey;
			NodeNumber itemID;

			ImVec2 oldWindowSize;

			gl::FboRef mFbo;

			Surface image ;
			
			// alldataに移動予定
			vector<vec2> listMouse;

			vector<gl::VboMeshRef> listMesh;

			vector<PolyLine2f> mPoly;
			vector<PolyLine2f> mHolePoly;
			Path2d mPath;//test

			//int degree = 6;

			void Convert_multiPoly();

			void resize_run (ivec2 moniterSize, gl::FboRef& mFbo)
			{
				vec2 size = vec2(moniterSize.x, moniterSize.y);
				
				auto format = gl::Fbo::Format().attachment(GL_COLOR_ATTACHMENT0, gl::Texture2d::create((int)size.x, (int)size.y));
				mFbo = gl::Fbo::create((int)size.x, (int)size.y, format);

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
				
				for (int i = 0; i < mVboMesh->getNumVertices(); i++) {
					vec2& mPos = *mappedPosAttrib;
					mappedPosAttrib->x = mPos.x + pos.x;
					mappedPosAttrib->y = mPos.y + pos.y;
					++mappedPosAttrib;
				}
				
				mappedPosAttrib.unmap();
				
				return mVboMesh;
			}

		};

	}
}