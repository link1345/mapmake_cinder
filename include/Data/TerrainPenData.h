#pragma once

#include <string>
#include <list>

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>


namespace MapMakeData {

	namespace TerrainPen {

		namespace Sub {

			class Key {
			public:
				Key() {
					this->name = "";
				};
				~Key() {};
				std::string name;
			};


			class Pen {
			public:
				Pen() {
					this->gaussianFilter = 0;
					this->bezierCurve.clear();
				};
				~Pen() {};

				// ���̑�

				/*!	@brief	�K�E�V�A���t�B���^�̒l
				*/
				int gaussianFilter;

				/*!	@brief	�x�W�F�Ȑ��̒l
				*/
				std::list<cinder::vec2> bezierCurve;
			};


		}


		class TerrainPenData {
		public:
			TerrainPenData() { this->pen.clear(); };
			~TerrainPenData() {};

			std::map<Sub::Key,Sub::Pen> pen;

		};
	}
	
}