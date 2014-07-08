#pragma once
#include "Model.h"

///The block class represents a model that is treated as a square voxel and has it's own texture loaded in by blocktype.
class Block :
	public Model
{
	

public:
	enum BlockType
	{
		Floor = 0,
		Wall,
		Ceiling,
	};

	Block(Vector3F position, BlockType blockType);
	~Block();

	

private:
	BlockType blockType;
};

