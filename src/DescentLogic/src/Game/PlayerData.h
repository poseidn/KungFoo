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

class PlayerEntity;

typedef int PlayerId;

class PlayerData {
public:
	PlayerData() = default;/*:
	 TotalScore(0), Id(-99), Entity(nullptr), IsDead(false), RespawnTime(0.0f) {
	 }*/

	PlayerData(PlayerEntity * ent, PlayerId i) :
			Entity(ent), Id(i) {

	}

	int TotalScore = 0;
	PlayerId Id = -99;
	PlayerEntity * Entity = nullptr;
	bool IsDead = false;
	float RespawnTime = 0.0f;
};
