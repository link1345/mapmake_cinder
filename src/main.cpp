#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TextTestApp : public App {
 public:
	void setup();
	void draw();
};

void TextTestApp::setup()
{	
	ImGui::Initialize();
	ImGuiIO& io = ImGui::GetIO();
	static ImWchar font_japanese[0xFFFF];
	for (int i = 1; i < 0xFFFE; i++) {
		font_japanese[i - 1] = i;
	}

	io.Fonts->AddFontFromFileTTF(u8"C:\\Windows\\Fonts\\meiryo.ttc", 30.0f, NULL, font_japanese);
}

void TextTestApp::draw()
{
	// this pair of lines is the standard way to clear the screen in OpenGL
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	gl::setMatricesWindow( getWindowSize() );

	ImGui::Text(u8"よろしくお願いいたします。(´ω｀)");
}

// This line tells Cinder to actually create the application
CINDER_APP( TextTestApp, RendererGl )
