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

			/*! @brief	�C���[�W�쐬����ۂɎg���|���S�����
			*/
			class TerrainPolygon {
			public:
				/*! @brief	���O
				*/
				std::string name;

				/*! @brief	������
				*/
				std::string explanation;

				/*! @brief	�|���S���f�[�^
				*/
				multiPolygon line;

				/*! @brief	���̐F
				*/
				MapMakeData::KeyColorName keyColor;
			};

			/*! @brief	Surface���(�Y�[���@�\���ꍇ�p)
			*/
			class ZoomSurface {
			public :
				ZoomSurface() {
					this->surface = cinder::Surface();
					this->zoomNum = 1.0f;
					this->point = glm::vec2();
				}
				~ZoomSurface() {};
				
				/*! @brief	�C���[�W�f�[�^
				*/
				cinder::Surface surface;

				/*! @brief	�Y�[���x
				*/
				float zoomNum;

				/*!	@brief	�����_
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

				/*! @brief	�}�X�N����(�ڂ�����)�̃f�[�^
				*/
				ZoomSurface MaskOnly;

				/*! @brief	�}�X�N�ƃm�C�Y��������f�[�^
				*/
				ZoomSurface MaskAndNoise;

			};
		}


		/*! @brief	��ʏ�ɕ`�悷��m�F�p�̃f�[�^
		*/
		class SampleDrawData {
		public:
			SampleDrawData() {
				this->allMap = Sub::MapImageList();
				this->zoomMap = Sub::MapImageList();
			};
			~SampleDrawData() {};

			/*	@brief	�S�̂��猩�����̃}�X�N�E�B���h�E�C���[�W
			*/
			Sub::MapImageList allMap;

			/*! @brief	�Y�[�����K�p���ꂽ�Ƃ��̃E�B���h�E�C���[�W
			*/
			Sub::MapImageList zoomMap;


			// �C�ݐ��́A�}�X�N�|���S�������g�����������B

			/*! @brief	��������������f�[�^
			*/
			std::vector<Sub::TerrainPolygon> Contour;

			/*!	@brief	�n�`��ʐ���������f�[�^
				@note	����multiPolygon�ɂȂ��Ă��邯�ǁA��ŁA�����Ƃ������̂ɏ��������Ēu��
			*/
			std::vector<Sub::TerrainPolygon> TerrainClassLine;

		};
	}
}