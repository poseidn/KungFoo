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

#include "StatusAspect.h"

#include <sstream>
#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/ResourceEngine/ResourceEngine.h>

#include "../GameState.h"
#include "../../Config/GameRules.h"

void StatusAspect::init(GameState & gameState) {
	gameState.slotStep.subscribe([=] ( GameState & gs, float deltaT)
	{
		// do we have to view the respawn ?
			bool showRespawn = false;
			float smallestRespawn = GameRules::RespawnTime * 2.0f;
			for ( PlayerData & pd : gs.getPlayers( ))
			{
				if ( pd.IsDead) {
					smallestRespawn = std::min ( smallestRespawn, pd.RespawnTime);
					showRespawn = true;
				}
			}

			if ( showRespawn)
			{	std::stringstream sText;
				sText << "Respawn in " << int(smallestRespawn);
				m_respawnCounter->setText( sText.str(), gs.getEngines().renderEngine().getScreenTransform() );
			}
			m_respawnCounter->setVisible( showRespawn);
		},"StatusAspect.step");

	gameState.slotActivateState.subscribe([=] ( GameState & gs, StateChangeInfoPtr const& ci )
	{
		TexturePtr textTex = gs.getEngines().resourceEngine().loadImage("textChars");

		Vector2 topMost = gs.getEngines().renderEngine().getScreenTransform().screenSizeInTiles();
		Vector2 locationBox = Vector2(topMost.x() * 0.2f, 1.0f);

		auto textV = std14::make_unique<TextVisual>(gs.getEngines().renderEngine().getScreenTransform(), textTex,
				locationBox, "Respawn in 13");
		m_respawnCounter = textV.get();
		gs.getEngines().renderEngine().addTextVisual(std::move(textV));
	});

	gameState.slotDeactivateState.subscribe([=] ( GameState & gs )
	{
		gs.getEngines().renderEngine().removeTextVisual(m_respawnCounter);
	});

}

