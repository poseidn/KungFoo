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
