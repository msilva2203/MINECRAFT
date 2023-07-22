#pragma once
#include <vector>

#include "Entity.h"

#include "Game/Block.h"
#include "Game/ChunkManager.h"

#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"

#define CHUNK_SIZE       16
#define CHUNK_HEIGHT     24


class Chunk : public AEntity
{
    typedef AEntity Super;
public:
    Chunk(UChunkManager* ChunkManager, glm::ivec2 position);
    ~Chunk();
    virtual void InitObject() override;;
    virtual void TerminateObject() override;

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

public:
    void UpdateChunk();
    Block& GetBlock(const glm::ivec3& location);
    void UpdateBlock(const glm::ivec3& location, const EDirection Direction);
    bool HasNeighbor(const glm::ivec3& location, const EDirection Direction);
    bool IsBlockSolid(unsigned int BlockIndex);

    void AddData(const std::array<unsigned int, 4>& vertex);
    unsigned int GetBlockVertex(const glm::ivec3& location, unsigned int xOffset, unsigned int yOffset, unsigned int zOffset, float xUv, float yUv);
    void SetMVP();

    const glm::ivec2& GetChunkPosition() const { return ChunkPosition; }
    
private:
    // X - Y - Z
    Block Blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    glm::ivec2 ChunkPosition;
    
    std::vector<unsigned int> Vertex;
    std::vector<unsigned int> Indices;
    unsigned int IndiceCount;

    UChunkManager* Manager;

    VertexArray* vao;
    VertexBuffer* vbo;
    IndexBuffer* ibo;
    
};
