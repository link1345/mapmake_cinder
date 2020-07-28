#pragma once

#include <cinder/CinderFwd.h>

#include "cinder/app/MouseEvent.h"

namespace tools {

	//! Enables user interaction with a 2D canvas via the mouse.
	class CanvasUi_ImGui {
	public:
		CanvasUi_ImGui()
		{
			mIsDirty = false;
			mIsInvDirty = false;
			mEnabled = true;
			mAnchor = vec2();
			mPosition = vec2();
			mScale = 1;
			mMouseWheelMultiplier = 0.1f;
		}
		~CanvasUi_ImGui() {  }
		
		CanvasUi_ImGui& operator=(const CanvasUi_ImGui& rhs)
		{
			mScale = rhs.mScale;
			mMouse = rhs.mMouse;
			mClick = rhs.mClick;
			mAnchor = rhs.mAnchor;
			mPosition = rhs.mPosition;
			mOriginal = rhs.mOriginal;
			mModelMatrix = rhs.mModelMatrix;
			mIsDirty = rhs.mIsDirty;
			mMouseWheelMultiplier = rhs.mMouseWheelMultiplier;
			mEnabled = rhs.mEnabled;
			return *this;
		}
		
		//! Sets whether the CanvasUi will modify its transform matrix either through its Window signals or through the various mouse*() member functions.
		void enable(bool enable = true) { mEnabled = enable; }
		//! Prevents the CanvasUi from modifying its transform matrix either through its Window signals or through the various mouse*() member functions.
		void disable() { mEnabled = false; }
		//! Returns whether the CanvasUi will modify its transform matrix either through its Window signals or through the various mouse*() member functions.
		bool isEnabled() const { return mEnabled; }
		//! Returns the current position and scale as a transform matrix.
		const ci::mat4& getModelMatrix() const
		{
			if (mIsDirty) { // ‚¢‚ç‚È‚¢‚©‚à
				// Update model matrix.
				mModelMatrix = glm::translate(ci::vec3(mPosition, 0));
				mModelMatrix *= glm::scale(ci::vec3(mScale));
				mModelMatrix *= glm::translate(ci::vec3(-mAnchor, 0));
				mIsInvDirty = true;
				mIsDirty = false; // ‚¢‚ç‚È‚¢‚©‚à
			}

			return mModelMatrix;
		}
		//! Returns the inverse of the current transform matrix. Can be used to convert coordinates. See also `CanvasUi::toLocal`.
		const ci::mat4& getInverseModelMatrix() const
		{
			if (mIsInvDirty) {
				mInvModelMatrix = glm::inverse(mModelMatrix);
				mIsInvDirty = false;
			}

			return mInvModelMatrix;
		}
		//! Converts a given point \a pt from world to object space, effectively undoing the canvas transformations.
		ci::vec2 toLocal(const ci::vec2& pt)
		{
			auto& m = getInverseModelMatrix();
			return ci::vec2(m * ci::vec4(pt, 0, 1));
		}

		void mouseDown(const ci::vec2& mousePos)
		{
			if (!mEnabled)
				return;

			reposition(mousePos);

			mClick = mousePos;
			mOriginal = mPosition;
		}
		void mouseDrag(const ci::vec2& mousePos)
		{
			if (!mEnabled)
				return;

			mMouse = mousePos;
			mPosition = mOriginal + mMouse - mClick;
			mIsDirty = true;
		}
		void mouseWheel(const ci::vec2& mousePos, float increment)
		{
			if (!mEnabled)
				return;

			reposition(mousePos);

			mMouse = mousePos;
			mScale *= 1.0f + mMouseWheelMultiplier * increment;
			mIsDirty = true;
		}

		//! Sets the multiplier on mouse wheel zooming. Larger values zoom faster. Negative values invert the direction. Default is \c 0.1.
		void setMouseWheelMultiplier(float multiplier) { mMouseWheelMultiplier = multiplier; }
		//! Returns the multiplier on mouse wheel zooming. Default is \c 0.1.
		float getMouseWheelMultiplier() const { return mMouseWheelMultiplier; }
		
	private:
		
		void reposition(const ci::vec2& mouse)
		{
			// Convert mouse to object space.
			ci::vec2 anchor = ci::vec2(getInverseModelMatrix() * ci::vec4(mouse, 0, 1));

			// Calculate new position, anchor and scale.
			mPosition += ci::vec2(mModelMatrix * ci::vec4(anchor - mAnchor, 0, 0));
			mAnchor = anchor;
		}
		
	private:
		
		float		mScale;
		float		mMouseWheelMultiplier;
		ci::vec2	mMouse, mClick;
		ci::vec2	mAnchor, mPosition, mOriginal;
		
		mutable bool	mIsDirty, mIsInvDirty;
		bool		mEnabled;
	
		mutable glm::mat4 mModelMatrix = glm::mat4();
		mutable glm::mat4 mInvModelMatrix = glm::mat4();
	};

}