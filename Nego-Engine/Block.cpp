#include "stdafx.h"
#include "Block.h"


Block::Block(Vector3F position, BlockType blockType) : Model(position)
{
	this->blockType = blockType;

	switch (blockType)
	{
		//release anthing texture may be using.
		delete mTexture;

		case Block::BlockType::Floor :
		{
			mTexture = new Bitmap("Floor.bmp");
			return;
		}
		case Block::BlockType::Wall :
		{
			mTexture = new Bitmap("Temp.bmp");
			return;
		}
		case Block::BlockType::Ceiling :
		{
			return;
		}
	}
}


Block::~Block()
{
}
