#pragma once
#include <VoxelEngine.h>

using BlockId = uint8_t;

enum class BlockType : BlockId {
	Air,
	Grass,
	Stone
};

struct Block {
	Block() = default;

	Block(BlockType blockType)
		: type(blockType)
	{
	}

	BlockType type = BlockType::Air;
	bool Visible = false;
};