#include "GUI/Sub/Individual/Mask/Mask.h"

#include "GUI/Widgets/HelpMarker.h"


#include <boost/numeric/ublas/vector.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/assign/list_of.hpp>

namespace ublas = boost::numeric::ublas;


namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<float> point;
typedef bg::model::polygon<point> polygon;
typedef bg::model::multi_polygon<polygon> multiPolygon;
//typedef std::vector<polygon> multiPolygon;

typedef bg::model::box<point> box;

#include <cinder/GeomIo.h> 

namespace GUI::SubWindow {
	

	void MaskWindow::draw(string mID) {
		
		if (MapMakeData::MainData.groundData.select == false ||
			groundKey != MapMakeData::MainData.groundData.selectKey) {
			this->openFlag = false;
			return;
		}

		// �f�[�^�擾
		auto& data = 
			MapMakeData::MainData.groundData.gData[
				MapMakeData::MainData.groundData.selectKey
			].layerTreeData.at(itemID).data;
		
		string gID = u8"[" + data.name;
		gID = gID +  u8"]�}�X�N�E�B���h�E##" + mID;
		if (ImGui::Begin(gID.c_str(),&this->openFlag)) {

			// �E�B���h�E�T�C�Y���ύX���ꂽ��ĕ`��
			auto monitorSize = ImVec2(
				ImGui::GetWindowSize().x
				 // (�� X���ɂ́A�^�C�g���o�[���Ȃ��̂ŁA�l���ɓ���܂���B)
				- (ImGui::GetCurrentContext()->Style.WindowPadding.x * 2), // �E�B���h�E���T�C�Y
				ImGui::GetWindowSize().y
				- (ImGui::GetFontSize() + ImGui::GetCurrentContext()->Style.FramePadding.y * 2) // �^�C�g���o�[�T�C�Y
				- (ImGui::GetCurrentContext()->Style.WindowPadding.y * 2) // �E�B���h�E���T�C�Y
			);

			if (monitorSize != this->oldWindowSize) {
				this->oldWindowSize = monitorSize;
				this->resize_run(this->oldWindowSize, this->mFbo);
				this->image_f(this->oldWindowSize, this->mFbo, this->listMouse);
			}

			auto pos = vec2();

			bool s = false;
			bool sh_s = false;

			string iamgeTitle = u8"monitor" + mID;
			if (ImGui::BeginChild(iamgeTitle.c_str(), ImVec2(this->oldWindowSize.x, this->oldWindowSize.y))) {

				// �`�悵����ɉ摜(texture)�ύX����Ǝ��ʂ̂ŁA�����ŕϊ����Ă����B
				auto texture = this->mFbo->getTexture2d(GL_COLOR_ATTACHMENT0);

				ImGui::Image(texture, this->mFbo->getSize(), vec2(0, 1), vec2(1, 0));

				ImGui::ItemDrag(iamgeTitle.c_str());

				// �}�E�X�{�^���������ꂽ�u��
				if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
					
					if (this->listMesh.size() != 0) {

						// �ȑO�������|���S�����܂߂Č�����������

						// �ϊ�
						vector<polygon> aPoly;
						this->Convert_Fbo(aPoly);

						// ��������
						for (auto p : aPoly) {
							multiPolygon temp;

							bg::union_(data.mask.maskPoly, p, temp);							
							data.mask.maskPoly = temp;
						}

						multiPolygon sTemp;
						bg::simplify(data.mask.maskPoly, sTemp, 0.5);
						data.mask.maskPoly = sTemp;

						// �`��ł���悤�ɍX�V mPoly
						this->Convert_multiPoly();

					}
					
					// �ꎞ�ۑ��������Ă���
					this->listMouse.clear();
					this->listMesh.clear();

				}
				// �}�E�X�{�^���������Ă��鎞 & �{�^�����ŏ��ɉ����ꂽ�u�� 
				else if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsItemHovered() || 
					ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)	) {

					auto shape = geom::Circle().radius(penThick).subdivisions(20);

					pos = vec2(
						ImGui::GetMousePos().x - ImGui::GetItemRectMin().x,
						ImGui::GetMousePos().y - ImGui::GetItemRectMin().y
					);


					pos = ui.toLocal(pos);

					// ���_�ǉ�
					if (listMouse.size() == 0) {
						this->pointAdd(pos, shape);
					}
					else if (listMouse.at(listMouse.size() - 1) != pos) {
						this->linearInterpolation(pos, shape);						
					}
					
				}
				
				// ��ʈړ�����
				else if ( ImGui::IsItemHovered() ) {

					pos = vec2(
						ImGui::GetMousePos().x - ImGui::GetItemRectMin().x,
						ImGui::GetMousePos().y - ImGui::GetItemRectMin().y
					);

					if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right)) {
						ui.mouseDown(pos);
					}
					else if ( ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Right) ) {
						ui.mouseDrag(pos);
					}
					else if ( ImGui::GetIO().MouseWheel != 0) {
						ui.mouseWheel(pos, ImGui::GetIO().MouseWheel);
					}

				}

			}
			ImGui::EndChild();

		}
		ImGui::End();

		// �I���R�}���h���@����Ă�����A
		if (!this->openFlag) {
			// ���C���[�E�B���h�E�̕\����ύX���Ă����B
			data.selectflag = false;

		}




		ImGui::SliderFloat("pen", &this->penThick, 5, 50);

	}	

	void MaskWindow::update(string mID) {
		this->image_f(this->oldWindowSize, this->mFbo, this->listMouse);

	}

	void MaskWindow::image_f(ivec2 Size, gl::FboRef& mFbo, vector<vec2> nowMouse)
	{
		gl::ScopedFramebuffer fboScope(mFbo);
		gl::clear();



		{
			gl::ScopedViewport viewportScope(vec2(0, 0), mFbo->getSize());
			gl::ScopedMatrices matScope;

			gl::setMatricesWindow((int)Size.x, (int)Size.y);

			gl::setModelMatrix(this->ui.getModelMatrix());

			// �}�E�X���͎��̐}�`�`��
			for (auto& mesh : this->listMesh) {
				gl::pushModelMatrix();

				gl::color(Color(1, 1, 1));
				gl::draw(mesh);

				gl::popModelMatrix();
			}
		}

		// -------------------
		
		{
			gl::ScopedViewport viewportScope(vec2(0, 0), mFbo->getSize());

			gl::ScopedMatrices matScope;

			gl::setMatricesWindow((int)mFbo->getSize().x, (int)mFbo->getSize().y);

			gl::setModelMatrix(this->ui.getModelMatrix());

			// ----
			// ���͍ς݂̃f�[�^�̕`��

			gl::enableWireframe(); // ���C���[�\��

			// ���̐}�`�`��
			for (auto poly : this->mHolePoly) {
				//gl::pushModelMatrix();

				gl::color(Color(1, 1, 0)); // red


				gl::drawSolid(poly);
				//gl::popModelMatrix();
			}

			// �{�̂̐}�`�`��
			for (auto poly : this->mPoly) {
				//gl::pushModelMatrix();

				gl::color(Color(0, 1, 1)); // red
				gl::drawSolid(poly);

				//gl::popModelMatrix();
			}
			gl::disableWireframe(); // ���C���[�\��

			// ----
		}

		return;
	}


	void MaskWindow::Convert_multiPoly(){
		// �f�[�^�擾
		auto& data =
			MapMakeData::MainData.groundData.gData[
				MapMakeData::MainData.groundData.selectKey
			].layerTreeData.at(itemID).data;
		
		this->mPoly.clear();
		this->mHolePoly.clear();
		for (auto p :  data.mask.maskPoly) {

			PolyLine2f out_pLine;
			for (auto in : p.outer()) {
				out_pLine.push_back(vec2(in.x(),in.y()));
			}
			this->mPoly.push_back(out_pLine);

			for (auto sIn : p.inners()) {
				PolyLine2f pLine;
				for (auto in : sIn) {
					pLine.push_back(vec2(in.x(), in.y()));
				}
				this->mHolePoly.push_back(pLine);
			}

		}
	}

	void MaskWindow::Convert_Fbo(vector<polygon>& aPoly) {
		for (auto aShape : this->listMesh) {
			list<point> posList;
			auto mappedPosAttrib = aShape->mapAttrib2f(geom::Attrib::POSITION, false);

			vec2 pos1 = vec2();
			for (uint32_t i = 0; i < aShape->getNumVertices(); i++) {
				if (i != 0) {
					vec2& pos = *mappedPosAttrib;

					posList.push_back(point(pos.x, pos.y));
				}
				++mappedPosAttrib;
			}
			mappedPosAttrib.unmap();

			polygon poly;
			posList.reverse();
			for (auto pos : posList) {
				poly.outer().push_back(pos);
			}
			//console() << boost::geometry::dsv(poly) << endl;

			aPoly.push_back(poly);
		}
	}


}