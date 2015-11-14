#pragma once

enum LayerPriority {
	LayerPriorityRandom = 1,
	LayerPriorityBottomMinusOne = 2,

	LayerPriorityFloorTiles = 3,
	LayerPriorityCarpet = 4,

	LayerPriorityWallsBottom = 5,
	LayerPriorityWallsTop = 6,
	LayerPriorityFurniture = 7,
	LayerPriorityFurnitureTransparent = 8,
	LayerPriorityBottom = 9,
	LayerPriorityTopMost = 10,
	LayerPriorityTopTopMost = 11,

	LayerPriorityDebug = 12,
	LayerPriorityMax = 13
};

class LayerTools {
public:
	static float computeZ(LayerPriority pr) {
		return float(pr) / float(LayerPriorityMax * 1.2f);
	}
};
