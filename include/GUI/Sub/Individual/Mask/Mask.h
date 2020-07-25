
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


				this->oldWindowSize = ImVec2(500, 500);

				this->image = Surface(this->oldWindowSize.x, this->oldWindowSize.y, false);
				this->resize_run(this->oldWindowSize, this->mFbo);

				ImGui::SetNextWindowSize(this->oldWindowSize);
			}

			MaskWindow(string groundKey, NodeNumber ID) : WindowBase() {
				this->groundKey = groundKey;
				this->itemID = ID;
				this->listMouse.clear();


				this->oldWindowSize = ImVec2(500, 500);

				this->image = Surface(this->oldWindowSize.x, this->oldWindowSize.y, false);
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
			list<vec2> listMouse;

			// マウスの軌跡を渡すと、そのデータを使って再描画してくれる。
			void resize_run (ivec2 moniterSize, gl::FboRef& mFbo)
			{
				vec2 size = vec2(moniterSize.x, moniterSize.y);
				
				auto format = gl::Fbo::Format().attachment(GL_COLOR_ATTACHMENT0, gl::Texture2d::create((int)size.x, (int)size.y));
				mFbo = gl::Fbo::create((int)size.x, (int)size.y, format);

				return;
			};

			void image_f (ivec2 moniterSize, gl::FboRef& mFbo, list<vec2> nowMouse)
			{
				gl::ScopedFramebuffer fboScope(mFbo);
				gl::clear();
				gl::ScopedViewport viewportScope(vec2(0), mFbo->getSize());
				gl::ScopedMatrices matScope;

				gl::setMatricesWindow((int)moniterSize.x, (int)moniterSize.y);
				//console() << "fbo:" << mFbo->getSize().x << " " << mFbo->getSize().y << "  moniter:" << (int)moniterSize.x << " " << (int)moniterSize.y << endl;

				for (auto& pos : nowMouse) {
					gl::color(Color(1, 1, 1)); // red
					gl::drawSolidCircle(pos,10);
				}

				
				return ;
			};

		};

	}
}