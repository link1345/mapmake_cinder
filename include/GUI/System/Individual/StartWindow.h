#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>


#include <cinder/CinderImGui.h>

// my
#include "Data/SystemData.h"
#include "Data/AllData.h"

#include "GUI/Widgets/HelpMarker.h"

namespace GUI {
	namespace System {
		class StartWindow {
		public:
			StartWindow() {};

			void draw();
			
			function<gl::Texture2dRef(int)> image_f = [](int boxNum) {
				vec2 size = vec2(200,200);
				double d = size.x / 100; // 画面サイズに合わせて、箱のサイズを変動させてくれる便利君。

				auto format = gl::Fbo::Format().attachment(GL_COLOR_ATTACHMENT0, gl::Texture2d::create(size.x,size.y));
				gl::FboRef mFbo = gl::Fbo::create(size.x, size.y, format);

				Surface s = Surface((100 - boxNum) * d, boxNum * d, false);
				ToolBox::Image::Icon_ColorInverse(s, ImGuiCol_::ImGuiCol_WindowBg);
				auto t = gl::Texture::create(s);

				gl::ScopedFramebuffer fboScope(mFbo);
				gl::clear();
				gl::ScopedViewport viewportScope(ivec2(0), mFbo->getSize());
				gl::ScopedMatrices matScope;

				gl::setMatricesWindow(size.x, size.y);

				gl::translate(vec2( (size.x / 2) - (t->getSize().x / 2)
					, (size.y / 2) - (t->getSize().y / 2) ));
				gl::draw(t);

				auto texture = mFbo->getTexture2d( GL_COLOR_ATTACHMENT0 );

				return texture;
			};


		};

	}
}
