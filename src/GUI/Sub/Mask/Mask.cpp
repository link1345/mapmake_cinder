#include "GUI/Sub/Individual/Mask/Mask.h"

#include "GUI/Widgets/HelpMarker.h"

namespace GUI::SubWindow {

	void MaskWindow::draw(string mID) {
		
		if (MapMakeData::MainData.groundData.select == false ||
			groundKey != MapMakeData::MainData.groundData.selectKey) {
			this->openFlag = false;
			return;
		}

		// �f�[�^�擾
		MapMakeData::Layer::Sub::LayerBoxData data = 
			MapMakeData::MainData.groundData.gData[
				MapMakeData::MainData.groundData.selectKey
			].layerTreeData.at(itemID).data;
		
		string gID = u8"[" + data.name;
		gID = gID +  u8"]�}�X�N�E�B���h�E##" + mID;
		if (ImGui::Begin(gID.c_str(),&this->openFlag)) {

			// �E�B���h�E�T�C�Y���ύX���ꂽ��ĕ`��
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
			if (ImGui::BeginChild(iamgeTitle.c_str(), ImVec2((int)this->oldWindowSize.x, (int)this->oldWindowSize.y))) {

				// �`�悵����ɉ摜(texture)�ύX����Ǝ��ʂ̂ŁA�����ŕϊ����Ă����B
				auto texture = this->mFbo->getTexture2d(GL_COLOR_ATTACHMENT0);

				ImGui::Image(texture, this->mFbo->getSize(), vec2(0, 1), vec2(1, 0));

				ImGui::ItemDrag(iamgeTitle.c_str());

				// �}�E�X�{�^���������ꂽ�u��
				if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
					// �ȑO�������|���S�����܂߂Č�����������

				}
				// �}�E�X�{�^���������Ă��鎞 & �{�^�����ŏ��ɉ����ꂽ�u�� 
				else if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsItemHovered() || 
					ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)	) {

					pos = vec2(
						ImGui::GetMousePos().x - ImGui::GetItemRectMin().x,
						ImGui::GetMousePos().y - ImGui::GetItemRectMin().y
					);

					// �X�v���C�g�Œ��_���
					// ******

					// ���_�ǉ�
					this->listMouse.push_back(pos);
					
				}

				ImGui::EndChild();
			}

		}

		ImGui::End();
	}	

	void MaskWindow::update(string mID) {
		this->image_f(this->oldWindowSize, this->mFbo, this->listMouse);

	}

}