/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SpecialMoveDetectionAspect.h"

#include <algorithm>
#include <iomanip>
#include <DescentEngine/src/VectorTypes.h>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Util.h>
#include <DescentEngine/src/Input/InputSystem.h>
#include <DescentEngine/src/Input/InputContainer.h>

#include "../GameState.h"
#include "../../Config/PlayerMovement.h"
#include "../../Config/GameMovement.h"

#include "../../Entities/PlayerEntity.h"

#include "../../Entities/TextureIds.h"

void SpecialMoveDetectionAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "SpecialMoveDetectionAspect.step");

}

// todo: also have an acceleration phase to allow for more precise, smaller
// movements
void SpecialMoveDetectionAspect::step(GameState & gs, float deltaT) {
	// store a list of recent moves and compare them with the possible patterns uha...

	// iterate all players
	for (PlayerData & pd : gs.getPlayers()) {

		util::initMap(m_inputs, pd.Id);
		if (util::initMap(m_reports, pd.Id)) {
			// has been newly added, initialize it !
			initReport(m_reports[pd.Id]);
		}

		PlayerInput & inp = m_inputs[pd.Id];
		PlayerReport & rep = m_reports[pd.Id];

		if (inp.m_inputRecord.size() != 0)
			inp.m_inputRecord.get(0).Duration += deltaT;

		while (true) {
			InputItem newIt = extractInputItem(gs, rep, pd.Id);

			if (!newIt.isDefined())
				break;

			//logging::Info() << "Got new input pattern: " << newIt;
			inp.m_inputRecord.push(newIt);
			analyzeRingBuffer(gs, inp.m_inputRecord, pd.Id);

			inp.m_activeInputItem = newIt;
		}
	}

}

void SpecialMoveDetectionAspect::initReport(PlayerReport & rep) {
	rep.m_jumpKeyReport = Reporter<KeyPressReport>([]( InputContainer const& cont )-> bool
	{
		return cont.keyDownJump();
	}, KeyPressReport(InputItem::KeyPressEnum::KeyA));

	rep.m_kickKeyReport = Reporter<KeyPressReport>([]( InputContainer const& cont)-> bool
	{
		return cont.keyDownKick();
	}, KeyPressReport(InputItem::KeyPressEnum::KeyB));

	const float quaterPi = boost::math::constants::pi<float>() * 0.25f;

	rep.m_rightDirectionReport = Reporter<DirectionReport>([quaterPi]( InputContainer const& cont)-> bool {
		if (cont.isStickOneMoved()) {
			if (Vector2::angleBetween(Vector2::UnitX(), cont.directionStickOne())
					< quaterPi)
			return true;
		}
		return false;
	}, DirectionReport(InputItem::DirectionEnum::Right));

	// left report
	rep.m_leftDirectionReport = Reporter<DirectionReport>([quaterPi]( InputContainer const& cont)-> bool {
		if (cont.isStickOneMoved()) {
			if (Vector2::angleBetween(-Vector2::UnitX(), cont.directionStickOne())
					< quaterPi)
			return true;
		}
		return false;
	}, DirectionReport(InputItem::DirectionEnum::Left));

	// up report
	rep.m_upDirectionReport = Reporter<DirectionReport>([quaterPi]( InputContainer const& cont)-> bool {
		if (cont.isStickOneMoved()) {
			if (Vector2::angleBetween(Vector2::UnitY(), cont.directionStickOne())
					< quaterPi)
			return true;
		}
		return false;
	}, DirectionReport(InputItem::DirectionEnum::Up));

	// down report
	rep.m_downDirectionReport = Reporter<DirectionReport>([quaterPi]( InputContainer const& cont)-> bool {
		if (cont.isStickOneMoved()) {
			if (Vector2::angleBetween(-Vector2::UnitY(), cont.directionStickOne())
					< quaterPi)
			return true;
		}
		return false;
	}, DirectionReport(InputItem::DirectionEnum::Down));

}

void SpecialMoveDetectionAspect::analyzeRingBuffer(GameState & gs, InputRecordType & rec,
		PlayerId id) {

	for (auto& pat : m_patterns) {
		if (pat.match(rec)) {
			gs.slotPlayerSpecialMove.signal(gs, id);
		}
	}
}

special_move::InputItem SpecialMoveDetectionAspect::extractInputItem(GameState & gs, PlayerReport & rep,
		PlayerId id) {
	special_move::InputItem it;

	InputContainer const & cont = gs.getEngines().inputEngine().getContainerConst(id);

	if (rep.m_jumpKeyReport.report(cont, it))
		return it;
	if (rep.m_kickKeyReport.report(cont, it))
		return it;

	if (rep.m_rightDirectionReport.report(cont, it))
		return it;
	if (rep.m_leftDirectionReport.report(cont, it))
		return it;
	if (rep.m_upDirectionReport.report(cont, it))
		return it;
	if (rep.m_downDirectionReport.report(cont, it))
		return it;

	// return an undefined to signal we have nothing to report
	return InputItem();
}
