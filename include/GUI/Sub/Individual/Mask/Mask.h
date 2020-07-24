
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

				this->image = Surface(500, 500, false);
				this->texture = gl::Texture::create(image);

				this->oldWindowSize = ImVec2();

			}
			MaskWindow(string groundKey, NodeNumber ID) : WindowBase() {
				this->groundKey = groundKey;
				this->itemID = ID;
				this->listMouse.clear();

				this->image = Surface(500,500,false);
				this->texture = gl::Texture::create(image);

				this->oldWindowSize = ImVec2();
			}
			~MaskWindow() {};

			void draw(string mID) override;

			string groundKey;
			NodeNumber itemID;

			ImVec2 oldWindowSize;


			Surface image ;
			gl::Texture2dRef texture;

			// alldata‚ÉˆÚ“®—\’è
			list<ivec2> listMouse;

			function<Surface(ivec2, list<ivec2>&, function<void(Surface&, ivec2)>)> image_run =
				[](ivec2 mointorSize , list<ivec2>& listMouse,
					function<void(Surface&, ivec2)> surface_f) 
			{
				Surface image = Surface(mointorSize.x,mointorSize.y,false);


				cinder::Surface::Iter iter = image.getIter();

				while (iter.line()) {
					while (iter.pixel()) {
						iter.r() = 0;
						iter.g() = 0;
						iter.b() = 0;
					}
				}

				for (auto pos : listMouse) {
					surface_f(image, pos);
				}

				return image;
			};

			function<void(Surface& , ivec2)> image_f =
				[](Surface &image, ivec2 nowMouse) {

				cinder::Surface::Iter iter = image.getIter();

				while (iter.line()) {
					while (iter.pixel()) {

						if (iter.getPos().x == nowMouse.x &&
							iter.getPos().y == nowMouse.y )
						{
							iter.r() = 255;
							iter.g() = 255;
							iter.b() = 255;
						}

					}
				}
				
				return ;
			};

		};

	}
}