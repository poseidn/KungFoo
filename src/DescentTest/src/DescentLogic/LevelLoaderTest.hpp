#pragma once

#include <gtest/gtest.h>

#include <DescentEngine/src/XmlTools.h>

#include <DescentLogic/src/LevelFactory.h>

#include <tinyxml2.h>

#include "../DescentEngine/Support/TestEntityFactory.h"
/*
 *
 fix this tests with the new level loader
TEST(LevelLoaderTest, loadTiles) {

	tinyxml2::XMLPrinter printer;
	printer.OpenElement("LevelFragment");
	printer.PushAttribute("size", "23,24");
	printer.PushAttribute("connectIn", "a,b");
	printer.PushAttribute("connectOut", "d,b,c");

	printer.OpenElement("Tile");
	printer.PushAttribute("repeat", "1,1");
	printer.PushAttribute("center", "2,3");
	printer.PushAttribute("entity", "floor_wood");
	printer.PushAttribute("type", "WallEntity");
	printer.PushAttribute("collides", "1");
	printer.CloseElement();

	printer.OpenElement("Tile");
	printer.PushAttribute("repeat", "3,3"); // means we have a 3x3 times large field
	printer.PushAttribute("center", "5,5");
	printer.PushAttribute("entity", "floor_wood");
	printer.PushAttribute("type", "WallEntity");
	printer.PushAttribute("collides", "1");
	printer.PushAttribute("collidesInJump", "0");
	printer.CloseElement();

	printer.OpenElement("Tile");
	// ommited on purpose
	//printer.PushAttribute("repeat", "3,3"); // means we have a 3x3 times large field
	printer.PushAttribute("center", "15,9");
	printer.PushAttribute("entity", "floor_wood");
	printer.PushAttribute("type", "WallEntity");
	printer.CloseElement();

	printer.CloseElement();

	const std::string inpString = printer.CStr();

	//const std::string jsonInput =
	// "{'tiles': [{'repeatX': 10, 'repeatY': 10, 'isBlocking': True, 'center': (2, 3), 'entity': 'floor_wood'},
	// {'floor': 45}]}";
	//		"{'tiles': 0}";
	TestGameState gs;
	TestEntityFactory testFact;
	LevelLoader lFac;
	LevelFragment frag;
	lFac.loadFragment(inpString, frag);

	ASSERT_FLOAT_EQ(frag.Size.y(), 24.0f);
	ASSERT_FLOAT_EQ(frag.Size.x(), 23.0f);
	ASSERT_EQ(frag.Tiles.size(), (unsigned int)3);
	ASSERT_EQ(frag.ConnectionsIn.size(), (unsigned int)2);
	ASSERT_EQ(frag.ConnectionsOut.size(), (unsigned int )3);
	ASSERT_EQ(frag.ConnectionsOut[0], "d");
	ASSERT_EQ(frag.Tiles[2].Entity, "floor_wood");
	ASSERT_EQ(frag.Tiles[2].Type, "WallEntity");

	lFac.applyFragment(frag, gs, testFact);

	ASSERT_EQ(testFact.createdTemplates.size(), (unsigned int )11);
	ASSERT_EQ(testFact.createdNonVisual.size(), (unsigned int )10);

	ASSERT_TRUE(std::get < 1 > (testFact.createdNonVisual[0]));
	ASSERT_FALSE(std::get < 1 > (testFact.createdNonVisual[9]));
}

TEST(LevelLoaderTest, parseVector2) {
	const std::string strVec = "345, 34";
	auto v = XmlTools::parseVector2(strVec);
	ASSERT_EQ(v.x(), 345);
	ASSERT_EQ(v.y(), 34);

	const std::string strVec2 = "23.4, 5.55";
	v = XmlTools::parseVector2(strVec2);
	ASSERT_FLOAT_EQ(23.4f, v.x());
	ASSERT_FLOAT_EQ(5.55f, v.y());
}

TEST(LevelLoaderTest, parseConnection) {
	const std::string strVec = "a,b,c";
	auto v = XmlTools::parseStringList(strVec);
	ASSERT_EQ(v.size(), (unsigned int )3);
	ASSERT_EQ(v[0], "a");
	ASSERT_EQ(v[1], "b");
	ASSERT_EQ(v[2], "c");
}
*/
