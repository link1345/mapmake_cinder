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
				/*! @brief	�C���[�W�f�[�^
				*/
				cinder::Surface surface;

				/*! @brief	�Y�[���x
				*/
				float zoomNum;

				/*!	@brief	�����_
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


						// �Ȃ񂩂��ɂ傲�ɂ債�āAMaskOnly::getSurface();��NoiseOnly::getSurface();��
						// ��g���āAthis->surface;�Ɋ�������������B
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