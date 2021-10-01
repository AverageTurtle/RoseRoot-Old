#include "Chunk.h"

//Temp draw cube
void DrawCube(glm::vec3 position, glm::vec4 color, VoxelEngine::Ref<VoxelEngine::SubTexture2D> texture)
{
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.f, 0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, color, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.f, -0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, color, texture, 1.f);

	VoxelEngine::RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, 0.5f) + position, { 1.f, 1.f, 1.f }, color, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, -0.5f) + position, { 1.f, 1.f, 1.f }, color, texture, 1.f);

	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, color, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(-0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, color, texture, 1.f);
}

//CHUNK SECTION
void ChunkSection::BuildMesh()
{
	for (int x = 0; x < 32; x++)
	{
		for (int z = 0; z < 32; z++)
		{
			for (int y = 0; y < 32; y++)
			{
				SetBlockVisible(x, y, z, false);
				if (GetBlock(x + 1, y, z).type == BlockType::Air)
				{
					SetBlockVisible(x, y, z, true); continue;
				}

				if (GetBlock(x - 1, y, z).type == BlockType::Air)
				{
					SetBlockVisible(x, y, z, true); continue;
				}

				if (GetBlock(x, y + 1, z).type == BlockType::Air)
				{
					SetBlockVisible(x, y, z, true); continue;
				}

				if (GetBlock(x, y - 1, z).type == BlockType::Air)
				{
					SetBlockVisible(x, y, z, true); continue;
				}

				if (GetBlock(x, y, z + 1).type == BlockType::Air)
				{
					SetBlockVisible(x, y, z, true); continue;
				}

				if (GetBlock(x, y, z - 1).type == BlockType::Air)
				{
					SetBlockVisible(x, y, z, true); continue;
				}
			}
		}
	}
}

void ChunkSection::Draw()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{

				Block block = GetBlock(x, y, z);

				if (block.Visible)
				{
					switch (block.type)
					{
					case BlockType::Grass:
						DrawCube({ x, y, z }, { 1.f,1.f,1.f,1.f }, m_GrassTexture);
						break;
					case BlockType::Stone:
						DrawCube({ x, y, z }, { 1.f,1.f,1.f,1.f }, m_StoneTexture);
						break;
					}
				}
			}
		}
	}
}

//CHUNK
void Chunk::RegenAllMeshes()
{
	m_ChunkSections[0]->BuildMesh();
}

void Chunk::AddSection()
{
	ChunkSection* section = new ChunkSection;
	m_ChunkSections.push_back(section);
}

