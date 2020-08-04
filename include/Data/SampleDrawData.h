#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

#include "Data/ToolBox/ImageTool.h"
#include "Data/Basis/ColorPalette.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/assign/list_of.hpp>

namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<float> point;
typedef bg::model::polygon<point> polygon;
typedef bg::model::multi_polygon<polygon> multiPolygon;


namespace MapMakeData {
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
				}
				~ZoomSurface() {};
				
				/*! @brief	イメージデータ
				*/
				cinder::Surface surface;

				/*! @brief	ズーム度
				*/
				float zoomNum;

				/*!	@brief	注視点
				*/
				glm::vec2 point;
			};

			class MapImageList {
			public:
				MapImageList() {
					this->MaskOnly = ZoomSurface();
					this->MaskAndNoise = ZoomSurface();
				};
				~MapImageList() {};

				/*! @brief	マスクだけ(ぼかしつき)のデータ
				*/
				ZoomSurface MaskOnly;

				/*! @brief	マスクとノイズが乗ったデータ
				*/
				ZoomSurface MaskAndNoise;

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