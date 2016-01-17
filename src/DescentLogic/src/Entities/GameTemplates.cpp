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

#include "GameTemplates.h"

#include <sstream>

#include <DescentEngine/src/EntityEngine/EntityEngine.h>
#include <DescentEngine/src/ResourceEngine/ResourceEngine.h>
#include <DescentLogic/src/Config/PlayerMovement.h>
#include <DescentLogic/src/Config/EnemyBehaviour.h>
#include <DescentLogic/src/Entities/TextureIds.h>

PreloadState GameTemplates::preload(EntityEngine & entNg, ResourceEngine & re, PreloadState pl) {

	size_t i = 0;
	for (auto const & tmplPair : entNg.getTemplateMap()) {
		if (i == pl.nextLoad) {
			auto const& tmpl = tmplPair.second;

			for (auto const& texConfig : tmpl.Textures) {
				for (std::string fname : texConfig.FileName) {
					re.loadImage(fname, texConfig.Frames);
				}
			}
		}
		i++;
	}

	return PreloadState(pl.nextLoad + 1, i);
}

void GameTemplates::registerTemplates(EntityEngine & entNg) {
	const size_t DefaultFrameCount = 1;
	const size_t DefaultFrameCountAnimation = 8;
	const float DefaultFrameTiming = .05f;
	const float WalkAnimationFrameTiming = .04f;

	const float DeviceEnableHeight = 0.8f;
	const float DeviceEnableWidth = 2.7f;

	const float DeviceIconHeight = 1.6f;
	const float DeviceIconWidth = 2.2f;

	const float JumpFrameTiming = PlayerMovement::JumpTime / float(DefaultFrameCountAnimation);
	const float KickFrameTiming = PlayerMovement::KickTime / float(DefaultFrameCountAnimation);
	const float EnemyHitFrameTiming = EnemyBehaviour::HitTime / float(DefaultFrameCountAnimation);

	const Rectangle2 DefaultFighterBoundingBox(1.0, 1.0);
	const Rectangle2 DefaultFighterImageBox(3.6, 3.6);

	auto registerFullTurn = []( EntityTemplate::TextureNames & texConfigs,
			TextureId firstId,
			std::string const& prefixName,
			size_t frameCount,
			float animationTiming ) {

		for ( size_t i = 0; i < 8; i++) {
			std::stringstream fullname;
			fullname << prefixName << "_" << ( i * 45);
			texConfigs.push_back( EntityTemplate::TextureConfig( firstId + i,
							{	fullname.str()},
							frameCount,
							animationTiming ));
		}
	};

	auto registerPlayer =
			[&]( std::string const& name, std::string const& texturePrefix, bool withDead, bool withBiking, bool withHit,
					Rectangle2 const& boundingBox, Rectangle2 const& imageBox ) {
				EntityTemplate::TextureNames texConfigs;
				registerFullTurn ( texConfigs,DescentTextureIds::Walk_0, texturePrefix + "_walk",
						DefaultFrameCountAnimation, WalkAnimationFrameTiming );
				registerFullTurn ( texConfigs,DescentTextureIds::Stand_0, texturePrefix + "_stand",
						DefaultFrameCountAnimation, WalkAnimationFrameTiming );
				registerFullTurn ( texConfigs,DescentTextureIds::Kick_0, texturePrefix + "_kick",
						DefaultFrameCountAnimation, WalkAnimationFrameTiming );
				registerFullTurn ( texConfigs,DescentTextureIds::Jump_0, texturePrefix + "_jump",
						DefaultFrameCountAnimation, WalkAnimationFrameTiming );
				if ( withBiking)
				{	registerFullTurn ( texConfigs,DescentTextureIds::Biking_0, texturePrefix + "_biking",
							DefaultFrameCountAnimation, WalkAnimationFrameTiming );}
				if ( withDead)
				{	registerFullTurn ( texConfigs,DescentTextureIds::Dead_0, texturePrefix + "_dead",
							DefaultFrameCount, WalkAnimationFrameTiming );}
				if ( withHit)
				{	registerFullTurn ( texConfigs,DescentTextureIds::Hit_0, texturePrefix + "_hit",
							DefaultFrameCountAnimation, WalkAnimationFrameTiming );}

				entNg.addTemplate(name, EntityTemplate( texConfigs, boundingBox,
								imageBox, LayerPriorityTopMost,
								CollisionMode::AlwaysCollide,
								true) );
			};

	auto registerPlayerEqualNames =
			[&] ( std::string const& name, std::string const& texPrefix, bool withDead, bool withBiking, bool withHit, Rectangle2 const& boundingBox,
					Rectangle2 const& imageBox ) {
				registerPlayer( name, texPrefix, withDead, withBiking, withHit, boundingBox, imageBox );
			};

	auto registerStaticEx = [&] ( std::string const& name,
			Rectangle2 const& boundingBox,
			Rectangle2 const& imageBox,
			LayerPriority prio,
			CollisionMode colMode,
			float transparency ) {

		EntityTemplate::TextureConfig texConfig(DescentTextureIds::Dummy,
				{	name},
				DefaultFrameCount );

		entNg.addTemplate(name, EntityTemplate( {texConfig}, boundingBox,
						imageBox, prio,
						colMode,
						false,
						transparency) );
	};

	auto registerStatic = [&] ( std::string const& name,
			Rectangle2 const& boundingBox,
			Rectangle2 const& imageBox,
			LayerPriority prio,
			CollisionMode colMode ) {
		registerStaticEx ( name, boundingBox, imageBox, prio, colMode, 1.0f);
	};

	auto registerStaticMultiTex = [&] ( std::string const& name,
			std::vector< std::string > const& fileNames,
			Rectangle2 const& boundingBox,
			Rectangle2 const& imageBox,
			LayerPriority prio,
			CollisionMode colMode ) {

		EntityTemplate::TextureConfig texConfig(DescentTextureIds::Dummy,
				fileNames,
				DefaultFrameCount );

		entNg.addTemplate(name, EntityTemplate( {texConfig}, boundingBox,
						imageBox, prio,
						colMode,
						false) );
	};

	auto registerUiElementEx = [&] ( std::string const& name,
			Rectangle2 const& boundingBox, float transparency , LayerPriority prio )
	{	registerStaticEx ( name, boundingBox, boundingBox, prio,
				CollisionMode::NeverCollide, transparency );

	};

	auto registerUiElement = [&] ( std::string const& name,
			Rectangle2 const& boundingBox )
	{
		registerUiElementEx ( name, boundingBox,
				1.0f, LayerPriority::LayerPriorityTopMost );
	};

	registerPlayerEqualNames("player1", "player1", false, true, false, DefaultFighterBoundingBox,
			DefaultFighterImageBox);
	registerPlayerEqualNames("player2", "player2", false, true, false, DefaultFighterBoundingBox,
			DefaultFighterImageBox);
	registerPlayerEqualNames("player3", "player3", false, true, false, DefaultFighterBoundingBox,
			DefaultFighterImageBox);
	registerPlayerEqualNames("player4", "player4", false, true, false, DefaultFighterBoundingBox,
			DefaultFighterImageBox);

	// todo: enemy hat ein bissle anderes bounding box
	registerPlayerEqualNames("enemy1", "enemy1", true, false, true, DefaultFighterBoundingBox, { 2.7f, 2.7f });
	registerPlayerEqualNames("enemy2", "enemy2", true, false, true, DefaultFighterBoundingBox, { 3.3f, 3.3f });

	// walls
	registerStatic("wall_wood_side1", { .25f, 2.0f }, { .5f, .5f }, LayerPriorityWallsTop,
			CollisionMode::AlwaysCollide);
	registerStatic("wall_wood_front1", { 3.0f, 2.0f }, { 3.0f, 2.0f }, LayerPriorityWallsBottom,
			CollisionMode::AlwaysCollide);
	registerStatic("wall_wood_top1", { 3.0f, 2.0f }, { 3.0f, 2.0f }, LayerPriorityWallsBottom,
			CollisionMode::AlwaysCollide);
	registerStatic("wall_wood_top2", { 3.0f, 0.5f }, { 3.0f, 0.5f }, LayerPriorityWallsBottom,
			CollisionMode::AlwaysCollide);
	registerStatic("wall_paper_front1", { 2.0f, 2.0f }, { 2.0f, 2.0f }, LayerPriorityWallsBottom,
			CollisionMode::AlwaysCollide);
	registerStatic("wall_paper_front2", { 2.0f, 2.0f }, { 2.0f, 2.0f }, LayerPriorityWallsBottom,
			CollisionMode::AlwaysCollide);

	// floor
	registerStaticMultiTex("floor_wood2", { "floor_wood2", "floor_wood3", "floor_wood2", "floor_wood3",
			"floor_wood4" }, { 2.0f, 2.0f }, { 2.0f, 2.0f }, LayerPriorityFloorTiles, CollisionMode::NeverCollide);

	registerStaticMultiTex("floor_gras1", { "gras1", "gras2" }, { 2.0f, 2.0f }, { 2.0f, 2.0f },
			LayerPriorityFloorTiles, CollisionMode::NeverCollide);

	registerStaticMultiTex("floor_water1", { "water1" }, { 2.0f, 2.0f }, { 2.0f, 2.0f }, LayerPriorityFloorTiles,
			CollisionMode::AlwaysCollide);

	// stuff
	registerStatic("cabinet1", { 2.0f, 1.5f }, { 2.0f, 1.5f }, LayerPriorityFurnitureTransparent,
			CollisionMode::JumpNoCollide);
	registerStaticMultiTex("vase1", { "vase1", "vase2" }, { 1.0f, 2.0f }, { 1.0f, 2.0f },
			LayerPriorityFurnitureTransparent, CollisionMode::AlwaysCollide);
	registerStaticMultiTex("carpet1", { "carpet1", "carpet2" }, { 6.0f, 6.0f }, { 6.0f, 6.0f },
			LayerPriorityFurniture, CollisionMode::NeverCollide);

	// decals
	registerUiElement("blood1", { 0.2f, 0.2f });
	registerUiElement("blood2", { 0.15f, 0.15f });
	registerUiElement("blood3", { 0.15f, 0.15f });

	registerUiElement("tooth1", { 0.3f, 0.3f });

	// various overlay stuff
	registerUiElement("bullet", { 1.2f, 1.2f });
	registerUiElement("game_logo", { 8.0f, 4.0f });

	registerUiElement("intro_logo_kungfoo", { 10.0f, 5.0f });
	registerUiElement("intro_logo_maker", { 10.0f, 4.6f });
	registerUiElement("intro_logo_fist_left", { 3.0f, 5.0f });
	registerUiElement("intro_logo_fist_right", { 3.0f, 5.0f });
	registerUiElement("intro_logo_bar", { 12.0f, 1.25f });

	registerUiElement("xbox-gamepad-labels", { 4.0f, 3.0f });
	registerUiElement("xbox-gamepad", { DeviceIconWidth, DeviceIconHeight });
	registerUiElement("xbox-gamepad-passive", { DeviceIconWidth, DeviceIconHeight });

	registerUiElement("xbox-gamepad-disable", { DeviceEnableWidth, DeviceEnableHeight });
	registerUiElement("xbox-gamepad-enable", { DeviceEnableWidth, DeviceEnableHeight });

	registerUiElement("ouya-gamepad", { DeviceIconWidth, DeviceIconHeight });
	registerUiElement("ouya-gamepad-passive", { DeviceIconWidth, DeviceIconHeight });

	registerUiElement("ouya-gamepad-disable", { DeviceEnableWidth, DeviceEnableHeight });
	registerUiElement("ouya-gamepad-enable", { DeviceEnableWidth, DeviceEnableHeight });

	registerUiElement("keyboard", { DeviceIconWidth, DeviceIconHeight });
	registerUiElement("keyboard-passive", { DeviceIconWidth, DeviceIconHeight });

	registerUiElement("keyboard-disable", { DeviceEnableWidth, DeviceEnableHeight });
	registerUiElement("keyboard-enable", { DeviceEnableWidth, DeviceEnableHeight });

	registerUiElement("player_arrow", { 1.0f, 1.0f });

	registerUiElementEx("loading-screen", { 8.0f, 4.0f }, 1.0f, LayerPriorityTopTopMost);

	registerUiElementEx("dpad1", { 8.0f, 8.0f }, 0.5f, LayerPriorityTopMost);
	registerUiElementEx("vbutton1", { 4.0f, 4.0f }, 0.5f, LayerPriorityTopMost);
	registerUiElementEx("vbutton2", { 4.0f, 4.0f }, 0.5f, LayerPriorityTopMost);
}

