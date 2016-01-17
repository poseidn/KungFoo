#pragma once

#include <string>

class VibratePatterns {
public:
	VibratePatterns() :
			EnemyPunched("enemy_punched"), PlayerJump("player_jump"), PlayerOutOfScreen(
					"player_out_of_screen") {
	}

	const std::string EnemyPunched;
	const std::string PlayerJump;
	const std::string PlayerOutOfScreen;
};
