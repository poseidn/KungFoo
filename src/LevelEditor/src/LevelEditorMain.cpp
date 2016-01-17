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

#include <DescentLogic/src/DescentFramework.h>

int main(int argc, const char* argv[]) {

	if (argc < 2) {
		std::cout << "Usage: LevelEditor <level name>" << std::endl;
		return 0;
	}
	std::string levelName(argv[1]);
	std::cout << "Loading level " << levelName << std::endl;

	DescentFramework f(true, // level editor
			false, // demo mode
			true // muted
			);
	f.m_levelName = levelName;

	SDLInterfaceInitData sdlInitData(Vector2UInt(800, 600), false);
	f.initRenderEngine(sdlInitData);

	f.execute();

	return 0;
}
