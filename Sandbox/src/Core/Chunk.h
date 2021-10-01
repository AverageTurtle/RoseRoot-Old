#pragma once
#include <RoseRoot.h>
#include <array>
#include <vector>

#include "Block.h"
#include "WorldConstants.h"

class ChunkSection {
public:
	ChunkSection(uint8_t y = 0) {
		m_Y = y; 
		m_SpriteSheet = RoseRoot::Texture2D::Create("assets/textures/SpriteSheet.png");

		m_GrassTexture = RoseRoot::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 0 }, { 16, 16 });
		m_StoneTexture = RoseRoot::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 0 }, { 16, 16 });
		m_GlassTexture = RoseRoot::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 0 }, { 16, 16 });
	};

	Block GetBlock(int x, int y, int z) {
		if (x > 31 || y > 31 || z > 31)
		{
			Block block;
			block.type = BlockType::Air;
			return block;
		}
		if (x < 0 || y < 0 || z < 0)
		{
			Block block;
			block.type = BlockType::Air;
			return block;
		}
		return m_Blocks[getIndex(x, y, z)]; };
	void SetBlock(int x, int y, int z, Block block) { m_Blocks[getIndex(x, y, z)] = block; }
	void SetBlockVisible(int x, int y, int z, bool block) { m_Blocks[getIndex(x, y, z)].Visible = block; }
	void Draw();
	void BuildMesh();

	int getIndex(int x, int y, int z) { return y * CHUNK_AREA + z * CHUNK_SIZE + x; }
private:
	uint8_t m_Y;
	std::array<Block, CHUNK_VOLUME> m_Blocks;

	RoseRoot::Ref<RoseRoot::Texture2D> m_SpriteSheet;
	RoseRoot::Ref<RoseRoot::SubTexture2D> m_GrassTexture, m_StoneTexture, m_GlassTexture;
};

class Chunk {
public:
	Chunk(uint8_t startRegionY = 0) 
		: m_ChunkSections()
	{ AddSection(); }

	Block GetBlock(int x, int y, int z)
	{
		int bY = y % CHUNK_SIZE;
		Block block = m_ChunkSections[0]->GetBlock(x, bY, z);
		return block;
	}
	void SetBlock(int x, int y, int z, Block block) {
		int bY = y % CHUNK_SIZE;
		m_ChunkSections[0]->SetBlock(x, bY, z, block);
	}

	void RegenAllMeshes();

	void Draw() {	m_ChunkSections[0]->Draw();	}

private:
	void AddSection();

private:
	std::vector<ChunkSection*> m_ChunkSections;
};