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
					this->name = "defaultPen";
				};
				Key(std::string name) {
					this->name = name;
				};

				~Key() {};
				std::string name;

				bool operator<(const Key& right) const {
					if (this->name < right.name) {
						return true;
					}
					return false;

				}
			};
			

			class Pen {
			public:
				Pen() {
					this->gaussianFilter = 0;
					this->bezierCurve = DefaultBezierCurve();
					//this->name = "";
				};
				//Pen(std::string name, int gaussianFilter, std::list<cinder::vec2> bezierCurve) {
				Pen(int gaussianFilter, std::list<cinder::vec2> bezierCurve) {
					this->gaussianFilter = gaussianFilter;
					this->bezierCurve = bezierCurve;
					//this->name = name;
				};
				~Pen() {};

				static std::list<cinder::vec2> DefaultBezierCurve() {
					std::list<cinder::vec2> v;
					v.push_back(cinder::vec2(0, 0));
					v.push_back(cinder::vec2(1, 1));
					return v;
				}


				//std::string name;

				// その他

				/*!	@brief	ガウシアンフィルタの値
				*/
				int gaussianFilter;

				/*!	@brief	ベジェ曲線の値
				*/
				std::list<cinder::vec2> bezierCurve;
			};


		}


		class TerrainPenData {
		public:
			TerrainPenData() { 
				this->pen.clear();
				this->pen[Sub::Key("defaultPen")] = Sub::Pen(0, Sub::Pen::DefaultBezierCurve());
			};
			~TerrainPenData() {};

			void setSampleData() {
				this->pen[Sub::Key(u8"pen1")] =
					Sub::Pen( 10, Sub::Pen::DefaultBezierCurve());
			};

			std::map<Sub::Key,Sub::Pen> pen;

		};
	}
	
}