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

	SDLInterfaceInitData sdlInitData(Vector2Uint(800, 600), false);
	f.initRenderEngine(sdlInitData);

	f.execute();

	return 0;
}
