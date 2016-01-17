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

// compiling for x86, most recent gcc 4.7 used
// android nkd 9 now comes with gcc 4.8 - cool
//#ifdef USE_SDL

#define CPP11_OVERRIDE	override
#define CPP11_FINAL		final

#define CPP11_CONSTEXPR_OPTIONAL	
#define CPP11_CONSTEXPR				const

//#else

//#define CPP11_OVERRIDE
//#define CPP11_FINAL

//#endif
