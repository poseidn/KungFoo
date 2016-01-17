#include <DescentEngine/src/Input/InputContainer.h>
#include "AndroidInput.h"

#include <cmath>
#include <sstream>
#include "../Log.h"

DeviceList AndroidInput::availableInputDevices() const {
	DeviceList devList;

	/*	for (auto i : m_registeredDevices) {
	 std::stringstream sId;
	 sId << "AndroidInput" << i;
	 devList.push_back(
	 InputDevice(InputDevice::TypeEnum::Gamepad, i, sId.str()));
	 }*/

	devList.push_back(
			InputDevice(InputDevice::TypeEnum::Touchpad, 0,
					"Android Touchpad"));

	// todo: has to be delivered by android
	return devList;
}

void AndroidInput::computeVirtualControlsPositions() {

	if (!padPositionsSet) {

		const float radiusDpad = 4.0f;

		// will always be in the lower left corner
		m_posDpad = Vector2(radiusDpad, radiusDpad);
		m_posButton1 = Vector2(m_screenTransform.screenSizeInTiles().x() - 3.0f,
				6.5f);
		m_posButton2 = Vector2(m_screenTransform.screenSizeInTiles().x() - 3.0f,
				2.0f);

		m_padCenterInPixels = m_screenTransform.vectorToScreen(m_posDpad, false,
				false);
		m_padButton1InPixels = m_screenTransform.vectorToScreen(m_posButton1,
				false, false);
		m_padButton2InPixels = m_screenTransform.vectorToScreen(m_posButton2,
				false, false);

		// todo: read dynamically
		m_padDpadRadiusInPixels = m_screenTransform.vectorToScreen(
				Vector2(radiusDpad, radiusDpad), false, false).x();

		m_padButtonRadiusInPixels = m_screenTransform.vectorToScreen(
				Vector2(2.0, 2.0), false, false).x();

		logging::Info() << "Computed Control pad center to "
				<< m_padCenterInPixels << " with radius "
				<< m_padDpadRadiusInPixels;
		logging::Info() << "Computed Button1 center to "
				<< m_padButton1InPixels;
		logging::Info() << "Computed Button2 pad center to "
				<< m_padButton2InPixels;

		padPositionsSet = true;
	}
}

float AndroidInput::upsideDownY(float fY) const {
	return m_screenTransform.screenSizeInPixel().y() - fY;
}

std::pair<bool, Vector2> AndroidInput::distanceToDPadCenter(float xpos,
		float ypos) const {
	return distanceHelper(xpos, ypos, m_padCenterInPixels,
			m_padDpadRadiusInPixels);
}

std::pair<bool, Vector2> AndroidInput::distanceToButton1Center(float xpos,
		float ypos) const {
	return distanceHelper(xpos, ypos, m_padButton1InPixels,
			m_padButtonRadiusInPixels);
}

std::pair<bool, Vector2> AndroidInput::distanceToButton2Center(float xpos,
		float ypos) const {
	return distanceHelper(xpos, ypos, m_padButton2InPixels,
			m_padButtonRadiusInPixels);
}

std::pair<bool, Vector2> AndroidInput::distanceHelper(float xpos, float ypos,
		Vector2 center, float radius) const {
	const float diff_x = xpos - center.x();
	const float diff_y = ypos - center.y();
	const float distance_to_dpad = std::sqrt(
			(diff_x * diff_x) + (diff_y * diff_y));
	return std::make_pair(distance_to_dpad < radius,
			Vector2(diff_x / radius, diff_y / radius));
}

void AndroidInput::injectTouchDown(int pointer_id, float xpos, float ypos) {
	ypos = upsideDownY(ypos);

	//logging::Info() << "touch down at " << xpos << ":" << ypos << " with id "
	//		<< pointer_id;

	computeVirtualControlsPositions();

	auto & ipC = this->getContainer(0);

	const auto dist_button1 = distanceToButton1Center(xpos, ypos);
	const auto dist_button2 = distanceToButton2Center(xpos, ypos);

	if (dist_button1.first) {
		logging::Info() << "Button1 touched";
		ipC.setKeyDownJump(true);
		return;
	}
	if (dist_button2.first) {
		logging::Info() << "Button2 touched";
		ipC.setKeyDownKick(true);
		return;
	}

	const auto dist_tuple = distanceToDPadCenter(xpos, ypos);

	// was touch inside the dpad ?
	if (dist_tuple.first) {
		// touch on our virtual analog pad ... ?
		PadFingerSet = true;
		PadFingerId = pointer_id;

		logging::Info() << "Input started on DPad";
	}
}

void AndroidInput::injectTouchMove(FingerLocationList locationList) {
	// nothing to do for us here
	if (!PadFingerSet)
		return;

	// is this the finger we are actually tracking on the dpad ?
	// search for the finger which touched the dpad !
	for (auto & loc : locationList) {
		if (PadFingerId == loc.PointerId) {
			float xpos = loc.xpos;
			float ypos = loc.ypos;
			ypos = upsideDownY(ypos);

			const auto dist_tuple = distanceToDPadCenter(xpos, ypos);

			auto & ipC = this->getContainer(0);

			// still allow for control, even if the finger left the dpad, but limit
			const float relDiffX = std::min(
					dist_tuple.second.x() * InputContainer::StickOneMax,
					InputContainer::StickOneMax);
			const float relDiffY = std::min(
					dist_tuple.second.y() * InputContainer::StickOneMax,
					InputContainer::StickOneMax);

			logging::Info() << "REL Moved on DPad " << relDiffX << " : "
					<< relDiffY;

			ipC.setDirectionStickOne(Vector2(relDiffX, relDiffY));
		}
	}
}

void AndroidInput::injectTouchUp(int pointer_id) {
	if (PadFingerSet) {
		logging::Info() << "Finger touch up and finger set, " << PadFingerId
				<< " and " << pointer_id;
		if (PadFingerId == pointer_id) {
			// reset all movements
			auto & ipC = this->getContainer(0);
			ipC.setDirectionStickOne(Vector2::Zero());
			PadFingerSet = false;
			logging::Info() << "Finger touch set to zero";
			//logging::Info() << "Input quit on DPad";
		}
	}
}
