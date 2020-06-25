/*! @addtogroup ���C������
    @file       main.h
    @brief      ��ԏ�ʂɈʒu����w�b�_�[
	@date       2020/06/25
*/

#pragma once

// cinder
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

// �g���̂����O����\��Q
//#include "cinder/CameraUi.h"
//#include "cinder/CinderImGui.h"
//#include "cinder/ObjLoader.h"
//#include "cinder/ImageIo.h"
//#include "cinder/gl/Texture.h"

// my
#include "GUI/GUI.h"
#include "Data/AllData.h"

using namespace ci;
using namespace ci::app;
using namespace ci::log;
using namespace std;

/*!
 @brief ��ԏ�ʂ̃N���X
 @attention ��ԍŏ��ɌĂ΂�܂��B����ɂ́AApp�N���X���p������Ă���Aquit�Ȃǂ̃R�}���h���g�p���邱�Ƃ��ł��܂��B
 @sa �O���[�o��MapMakeData::MainData�Ɗ֌W���Ă���
 */
class BasicApp : public App {
public:

	void setup() override;
	void update() override;
	void draw() override;
	
	void resize() override;

	void mouseDown(MouseEvent event) override;
	void mouseMove(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseWheel(MouseEvent event) override;

private:

	/*! ImGui�̏���������
		@return         �߂�l�Ȃ�
		@exception      none
	*/
	void InitImGui();

	/*! �\�t�g�I������
		@par            �Q�ƃO���[�o���ϐ�
		- MapMakeData::MainData��getQuit
		@return         �߂�l�Ȃ�
		@exception      none
	*/
	void updateQuit();

	/*! GUI����̓����ϐ� */
	GUI::MainGUI gui;

	/*! �h�L�������g�e�X�g�p
		@param[out]     var1    var1�̐���
		@param[in]      var2    var2�̐���
		@param[in,out]  var3    var3�̐���
		@par            Refer
		- �Q�Ƃ���O���[�o���ϐ� global_var1
		- �Q�Ƃ���O���[�o���ϐ� global_var2
		@par            Modify
		- �ύX����O���[�o���ϐ� global_var3
		- �ύX����O���[�o���ϐ� global_var4
		@return         ���� 0, ���s 0 �ȊO �Ȃ�
		@exception      ��O�B�s�v�ł����none���L�q
	*/
	void doctest() {};

};
