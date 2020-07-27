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

		// データ取得
		auto& data = 
			MapMakeData::MainData.groundData.gData[
				MapMakeData::MainData.groundData.selectKey
			].layerTreeData.at(itemID).data;
		
		string gID = u8"[" + data.name;
		gID = gID +  u8"]マスクウィンドウ##" + mID;
		if (ImGui::Begin(gID.c_str(),&this->openFlag)) {

			// ウィンドウサイズが変更されたら再描画
			auto monitorSize = ImVec2(ImGui::GetWindowSize().x, 
				ImGui::GetWindowSize().y
				- (ImGui::GetFontSize() + ImGui::GetCurrentContext()->Style.FramePadding.y * 2)
				- (ImGui::GetCurrentContext()->Style.WindowPadding.y * 2));

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

				// 描画した後に画像(texture)変更すると死ぬので、ここで変換しておく。
				auto texture = this->mFbo->getTexture2d(GL_COLOR_ATTACHMENT0);

				ImGui::Image(texture, this->mFbo->getSize(), vec2(0, 1), vec2(1, 0));

				ImGui::ItemDrag(iamgeTitle.c_str());

				// マウスボタンが離された瞬間
				if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
					
					if (this->listMesh.size() != 0) {

						// 以前書いたポリゴンも含めて結合処理する

						// 変換
						
						vector<polygon> aPoly;
						for (auto aShape : this->listMesh) {
							list<point> posList;
							auto mappedPosAttrib = aShape->mapAttrib2f(geom::Attrib::POSITION, false);

							vec2 pos1 = vec2();
							for (int i = 0; i < aShape->getNumVertices(); i++) {
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

						// 結合処理
						for (auto p : aPoly) {
							multiPolygon temp;

							bg::union_(data.mask.maskPoly, p, temp);
							
							data.mask.maskPoly = temp;
						}

						// 描画できるように更新 mPoly
						this->Convert_multiPoly();

					}
					
					// 一時保存を消しておく
					this->listMouse.clear();
					this->listMesh.clear();

				}
				// マウスボタンを押している時 & ボタンが最初に押された瞬間 
				else if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsItemHovered() || 
					ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)	) {


					auto shape = geom::Circle().radius(20).subdivisions(20);
					//auto shape = geom::WireCircle().radius(20).subdivisions(10);


					pos = vec2(
						ImGui::GetMousePos().x - ImGui::GetItemRectMin().x,
						ImGui::GetMousePos().y - ImGui::GetItemRectMin().y
					);

					// 頂点追加
					if (listMouse.size() == 0) {
						this->listMouse.push_back(pos);
						this->listMesh.push_back(this->MeshAdd(pos, shape));
					}
					else if (listMouse.at(listMouse.size() - 1) != pos) {


						// 線形補間した上で頂点追加
						if (listMouse.size() == 0) {
							this->listMouse.push_back(pos);
							this->listMesh.push_back(this->MeshAdd(pos, shape));
						}
						else {
							
							auto pos2 = listMouse.at(listMouse.size()-1);

							// 2は2次元であるという意味。
							ublas::vector<float> v(2);
							v[0] = pos.x - pos2.x;
							v[1] = pos.y - pos2.y;

							int dot = 50;
							// ノルムで2次元上の直線を引く。
							auto ler = dot / ublas::norm_2(v);

							// 1.0f以下なら、頂点をましましにする。
							bool hit = false;
							for (auto sler = ler; sler <= 1.0f; sler = sler + ler) {
								auto p = lerp(pos2, pos, sler);
								this->listMouse.push_back( p );
								this->listMesh.push_back(this->MeshAdd( p , shape));

								hit = true;
							}
							if (!hit) {
								this->listMouse.push_back(pos);
								this->listMesh.push_back(this->MeshAdd(pos, shape));
							}
						}
					}
					
				}

			}
			ImGui::EndChild();

		}

		ImGui::End();

	}	

	void MaskWindow::update(string mID) {
		this->image_f(this->oldWindowSize, this->mFbo, this->listMouse);

	}

	void MaskWindow::image_f(ivec2 moniterSize, gl::FboRef& mFbo, vector<vec2> nowMouse)
	{
		// データ取得

		gl::ScopedFramebuffer fboScope(mFbo);
		gl::clear();
		gl::ScopedViewport viewportScope(vec2(0), mFbo->getSize());
		gl::ScopedMatrices matScope;

		gl::setMatricesWindow((int)moniterSize.x, (int)moniterSize.y);

		//for (auto& pos : nowMouse) {
		for (auto& mesh : this->listMesh) {
			gl::pushModelMatrix();

			//gl::translate(pos);

			gl::color(Color(1, 1, 1)); // red
			//gl::drawStrokedCircle(pos,10);
			gl::draw(mesh);

			gl::popModelMatrix();
		}

		for (auto poly : this->mHolePoly) {
			gl::pushModelMatrix();

			gl::color(Color(1, 1, 0)); // red
			gl::drawSolid(poly);
			//console() << "hole" << endl;
			gl::popModelMatrix();
		}
		
		for (auto poly : this->mPoly) {
			gl::pushModelMatrix();

			gl::color(Color(0, 1, 1)); // red
			gl::drawSolid(poly);

			gl::popModelMatrix();
		}

		/* // spline 
		auto sDegree = degree;
		if (nowMouse.size() >= 2 && (1 <= sDegree) && (sDegree <= nowMouse.size() - 1)) {
			auto sp = BSpline2f(nowMouse, sDegree, true, true);
			
			//console() << sp.getLength(0, 1) << endl;
			//console() << sp.getSpeed(0) << endl;

			auto path = Path2d(sp);

			for (auto pos : path.getPoints()) {
				gl::color(Color(1, 1, 1));
				gl::drawSolidCircle(pos, 10);
			}

		}*/

		return;
	}


	void MaskWindow::Convert_multiPoly(){
		// データ取得
		auto& data =
			MapMakeData::MainData.groundData.gData[
				MapMakeData::MainData.groundData.selectKey
			].layerTreeData.at(itemID).data;
		
		//console() << "convert data:" << data.mask.maskPoly.size() << endl;
		
		this->mPath.clear();
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

}