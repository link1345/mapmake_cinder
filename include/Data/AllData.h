#pragma once

#include "Tree.h"

#include "LayerData.h"


namespace MapMakeData {

	class AllData {
	public:
		AllData() {
			// �������������ˁI
		}

		// ���C���[���B������_�������c
		LayerData layerData;

		// �\��
		// GUI����̂��߂̕ϐ��Ȃǂ��܂ށB
	};

	// �O���[�o���ϐ��B
	extern AllData MainData;

}