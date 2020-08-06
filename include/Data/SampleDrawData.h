#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/assign/list_of.hpp>

namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<float> point;
typedef bg::model::polygon<point> polygon;
typedef bg::model::multi_polygon<polygon> multiPolygon;


#include "Data/ToolBox/ImageTool.h"
#include "Data/Basis/ColorPalette.h"
#include "Data/Basis/noise.h"


namespace MapMakeData {

	using KeyColorName = std::string;

	namespace DrawImage {

		namespace Sub {

			/*! @brief	イメージ作成する際に使うポリゴン情報
			*/
			class TerrainPolygon {
			public:
				/*! @brief	名前
				*/
				std::string name;

				/*! @brief	説明文
				*/
				std::string explanation;

				/*! @brief	ポリゴンデータ
				*/
				multiPolygon line;

				/*! @brief	線の色
				*/
				MapMakeData::KeyColorName keyColor;
			};

			/*! @brief	Surface情報(ズーム機能持つ場合用)
			*/
			class ZoomSurface {
			public :
				ZoomSurface() {
					this->surface = cinder::Surface();
					this->zoomNum = 1.0f;
					this->point = glm::vec2();

					this->setupFlag = false;
				}
				~ZoomSurface() {};

				/*! @brief	
				*/
				virtual void make(float zoomNum, glm::vec2 point) {
					if (!this->getSetupFlag()) {
						return;
					}
				};

				float getZoomNum() {
					return this->getZoomNum();
				};
				glm::vec2 getPoint() {
					return this->point;
				};
				void setData(float ZoomNum, glm::vec2 Point) {
					this->zoomNum = ZoomNum;
					this->point = Point;
				}

				bool getSetupFlag() { return this->setupFlag; }
				void SetupFlag() { this->setupFlag = true; };

				cinder::Surface* getSurface() { return &this->surface; };

			private:
				/*! @brief	イメージデータ
				*/
				cinder::Surface surface;

				/*! @brief	ズーム度
				*/
				float zoomNum;

				/*!	@brief	注視点
				*/
				glm::vec2 point;

				bool setupFlag;
			};

			namespace Image {
				class MaskOnly : public ZoomSurface {
				public :
					MaskOnly() {
						this->maskPoly = NULL;					
					};
					~MaskOnly() {};

					void make(float zoomNum, glm::vec2 point) override {
						if (!this->getSetupFlag()) {
							return;
						}
						makeMask();
					}

					void makeMask(){}

					void setup(multiPolygon* maskPoly) {
						this->maskPoly = maskPoly;
						this->SetupFlag();
					};
				private:
					multiPolygon* maskPoly;

				};

				class NoiseOnly : public ZoomSurface {
				public:
					NoiseOnly() {
						this->noise = NULL;
					};
					~NoiseOnly() {};

					void make(float zoomNum, glm::vec2 point) override {
						if (!this->getSetupFlag()) {
							return;
						}
						makeNoise();
					}

					void makeNoise() {}

					void setup(NoiseData* noise) {
						this->noise = noise;
						this->SetupFlag();
					};
				private:
					NoiseData* noise;
				};


				class MaskAndNoise : protected MaskOnly , protected NoiseOnly {
				public :
					MaskAndNoise() {
						this->surface = cinder::Surface();
					};
					~MaskAndNoise() {};

					void make(float zoomNum, glm::vec2 point) override {
						if (!MaskOnly::getSetupFlag() || !NoiseOnly::getSetupFlag()) {
							return;
						}

						MaskOnly::make(zoomNum, point);
						MaskOnly::makeMask();
						MaskOnly::getSurface();

						NoiseOnly::make(zoomNum, point);
						NoiseOnly::makeNoise();
						NoiseOnly::getSurface();


						// なんかごにょごにょして、MaskOnly::getSurface();とNoiseOnly::getSurface();を
						// 駆使して、this->surface;に完成したやつ入れる。
					}

					void setup(multiPolygon* maskPoly ,NoiseData* noise) {
						MaskOnly::setup(maskPoly);
						NoiseOnly::setup(noise);
					}

					cinder::Surface* getSurface() { return &this->surface; };

				private:
					cinder::Surface surface;

				};
			}

			class MapImageList {
			public:
				Image::MaskOnly maskOnly;
				Image::NoiseOnly noiseOnly;
				Image::MaskAndNoise maskAndNoise;
			private:

			};
		}


		/*! @brief	画面上に描画する確認用のデータ
		*/
		class SampleDrawData {
		public:
			SampleDrawData() {
				this->allMap = Sub::MapImageList();
				this->zoomMap = Sub::MapImageList();
			};
			~SampleDrawData() {};

			/*	@brief	全体から見た時のマスクウィンドウイメージ
			*/
			Sub::MapImageList allMap;

			/*! @brief	ズームが適用されたときのウィンドウイメージ
			*/
			Sub::MapImageList zoomMap;


			// 海岸線は、マスクポリゴンをお使いください。

			/*! @brief	等高線が乗ったデータ
			*/
			std::vector<Sub::TerrainPolygon> Contour;

			/*!	@brief	地形区別線が乗ったデータ
				@note	今はmultiPolygonになっているけど、後で、ちゃんとしたものに書き換えて置く
			*/
			std::vector<Sub::TerrainPolygon> TerrainClassLine;

		};
	}
}