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

#pragma once

#include <gtest/gtest.h>

#include <DescentEngine/src/Signals.h>

TEST(Signals, RegisterAndCall)
{
	//typedef std::function<void(int)> MessagingFunc;

	slots::Slot<int> s;

	struct MyMessager
	{
		MyMessager(int i) :
				myVal(i)
		{

		}
		void callMe(int i)
		{
			myVal += i;
		}
		int myVal;
	};
	MyMessager myMessengerOne(0);
	MyMessager myMessengerTwo(-23);

	// both work, it is simply about handling the call to a member function,
	// which must be performed binded
	s.subscribe([&myMessengerOne] ( int i )
	{	myMessengerOne.callMe(i);});

	s.subscribe(
			std::bind(&MyMessager::callMe, &myMessengerTwo,
					std::placeholders::_1));

	//s.subscribe(boost::bind(&MyMessager::callMe, myMessengerTwo, _1));
	s.signal(23);

	EXPECT_EQ(23, myMessengerOne.myVal);
	EXPECT_EQ(0, myMessengerTwo.myVal);

}

/*
 *
 * fix this somehow to have a test keyboard
 *S
 *
 class TestKeyboard
 {
 public:
 virtual bool isKeyDown(OIS::KeyCode key) const
 {
 return false;
 }

 virtual const std::string& getAsString(OIS::KeyCode kc)
 {
 return defaultReturn;
 }

 virtual void copyKeyStates(char keys[256]) const
 {

 }


 virtual void setBuffered(bool buffered)
 {

 }


 virtual void capture()
 {

 }


 virtual OIS::Interface* queryInterface(OIS::Interface::IType type)
 {
 return CPP11_NULLPTR;
 }


 virtual void _initialize()
 {

 }

 const std::string defaultReturn ="";
 };

 TEST(BuildingAspects, KeyboardControlAspect)
 {
 stuck::BuildingState buildingState;
 stuck::InputState< TestKeyboard > inpState( new TestKeyboard() );

 stuck::ExternalState extState ( inpState , 1.0f);

 // make this a button press
 inpState.m_bLeftMBPressed = true;

 stuck::KeyboardControlAspect asp;
 EXPECT_EQ( stuck::Transitions::ToCurrent,  asp.transform ( buildingState, extState ) );
 EXPECT_EQ( size_t(1), buildingState.getIntents().size() );
 }

 */
