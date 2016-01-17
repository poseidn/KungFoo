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

#include "NavigateMenuAspect.h"

#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentEngine/src/EntityEngine/SingleVisualEntity.h>

#include "../../Common/ChangeToGameInfo.h"
#include "../../Common/GameToMenuInfo.h"
#include "../../Config/GameRules.h"
#include "../../Entities/GameTemplates.h"

void NavigateMenuAspect::init(MenuState & gs) {
	gs.slotInputSelect.subscribe(
			[=] ( MenuState & g, InputSystem::ContainerId id )
			{	this->onSelect( g, id);});

	gs.slotInputEnable.subscribe(
			[=] ( MenuState & g, InputSystem::ContainerId id )
			{	this->onEnableDisableDevice( g, id);});

	gs.slotInputMove.subscribe(
			[=] ( MenuState & g, MenuState::MovementDirection dir, InputSystem::ContainerId id )
			{	this->onMove( g, dir, id);});

	gs.slotStep.subscribe(
			[=] ( MenuState & gs, float dt )
			{
				if ( !m_preloading)
				return;

				m_lastPreload =
				GameTemplates::preload(gs.getEngines().entityEngine(), gs.getEngines().resourceEngine(), m_lastPreload);

				if ( m_lastPreload.loadDone()) {
					logging::Info() << "Preloading of resources complete";

					// TODO: the user may select this
					// reset this, once the player restarts a game etc.
					// tie this gamepad to player One
					InputSystem & inpSystem = gs.getEngines().inputEngine();

					inpSystem.resetPlayerAssignment();

					// setup input system
					InputSystem::PlayerInputId pInputId = 0;
					for (auto & it : gs.getDeviceItems()) {
						if (it.m_isEnabled) {
							it.m_isEnabled = true;
							logging::Info() << "Container " << it.m_ContainerId << " is assigned to PlayerId " << pInputId;
							inpSystem.assignPlayerToInput(pInputId, it.m_ContainerId);
							pInputId++;
						}
					}

					inpSystem.dumpPlayerAssignment();

					ChangeToGameInfo * toGame = new ChangeToGameInfo(size_t(pInputId));
					StateChangeInfoPtr changeInfo(toGame);

					gs.getLoadingPane()->getActiveVisual().get().setVisible(false);
					gs.setMenuVisible(true);
					gs.getCurrentItemPointer()->getActiveVisual().get().setVisible(true);
					// needed to show the new view
					gs.getEngines().renderEngine().render();
					m_preloading = false;
					gs.requestStateChange("game", changeInfo);
				} else {
					logging::Info() << "Preloading not done, yet";
				}
			});
}

void NavigateMenuAspect::onEnableDisableDevice(MenuState & gs,
		InputSystem::ContainerId id) {
	const size_t numEnabled = gs.activeDevices();
	logging::Info() << " Enabling/Disabling device " << id;

	for (auto & it : gs.getDeviceItems()) {
		if (it.m_ContainerId == id) {
			// found !!

			// last one enabled, cannot disable
			/*if ((numEnabled == 1) && it.m_isEnabled) {
			 logging::Info() << "Last active device, will not disable this last one";
			 break;
			 }*/

			// cannot enable much more playes
			if ((numEnabled >= GameRules::MaxPlayers) && !it.m_isEnabled) {
				logging::Info()
						<< "Maximum number of players reached, no new device";
				break;
			}

			it.m_isEnabled = !it.m_isEnabled;
			gs.updateDevices();

			break;
		}
	}

}

void NavigateMenuAspect::onSelect(MenuState & gs, InputSystem::ContainerId id) {

	autoSelectDevice(gs, id);

	// check the current selection !!
	std::string currentSel = gs.getCurrentItemId();

	if (currentSel == "") {
		// no item was selected, don't need to handle this !
		logging::Info() << "No Menu item selected";
		return;
	}

	logging::Info() << "Menu item " << currentSel << " selected";

	if (currentSel == "start") {
		logging::Info() << "will change to game";

		//todo: does not work on android. Probably because the glSwap
		// happens on the java side ...

		gs.getLoadingPane()->getActiveVisual().get().setVisible(true);
		gs.setMenuVisible(false);
		gs.getCurrentItemPointer()->getActiveVisual().get().setVisible(false);

		m_lastPreload = GameTemplates::preload(gs.getEngines().entityEngine(),
				gs.getEngines().resourceEngine(), PreloadState());

		m_preloading = true;
		// needed to show the new view
		//gs.getEngines().renderEngine().render();

		// preload textures and sound !

	} else if (currentSel == "restart") {
		logging::Info() << " going back to the main game menu";

		StateChangeInfoPtr pChange(new GameToMenuInfo());
		gs.requestStateChange("menu", pChange);

	} else if (currentSel == "config") {
		logging::Info() << "configuration not implemented yet";
	} else if (currentSel == "exit") {
		exit(0);
	} else {
		logging::Fatal() << "Cannot handle menu id " << currentSel;
	}

}

void NavigateMenuAspect::onMove(MenuState & gs,
		MenuState::MovementDirection dir, InputSystem::ContainerId id) {

	autoSelectDevice(gs, id);
	gs.moveMenuPointer(dir);
}

void NavigateMenuAspect::autoSelectDevice(MenuState & gs,
		InputSystem::ContainerId id) {

	// check if no device has been selected yet and select this one...
	const size_t numEnabled = gs.activeDevices();

	if (numEnabled == 0) {
		for (auto & it : gs.getDeviceItems()) {
			logging::Info() << "Checking container id " << it.m_ContainerId
					<< " ...";
			if (it.m_ContainerId == id) {
				it.m_isEnabled = true;
				gs.updateDevices();
				logging::Info() << "Autoselectiong device " << it.m_ContainerId
						<< " for gaming";
				break;
			}
		}
	} else {
		logging::Info() << "Already enabled " << numEnabled
				<< " devices, not autoselect of device";
	}
}

