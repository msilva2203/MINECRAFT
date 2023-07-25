#include "Game/Chunk.h"

#include "Game/Block.h"
#include "Game/ChunkManager.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Renderer.h"

#include <array>


Chunk::Chunk(UChunkManager* ChunkManager, glm::ivec2 position) :
    ChunkPosition(position),
    Manager(ChunkManager)
{
    SetEntityLocation({ position.x * 16.0f, 0.0f, position.y * 16.0f });
}

Chunk::~Chunk()
{
}

void Chunk::InitObject()
{
    Super::InitObject();

    vao = new VertexArray;
    vbo = new VertexBuffer(nullptr, 0);
    ibo = new IndexBuffer(nullptr, 0);

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            unsigned int TerrainHeight = CHUNK_HEIGHT - (int)(((glm::sin(x) + 1.0f) / 2.0f) * 5.0f);

            for (int y = CHUNK_HEIGHT - 1; y > TerrainHeight; y--)
            {
                GetBlock({ x, y, z }).SetBlockType(EBlockType::VOID);
            }
        }
    }
}

void Chunk::TerminateObject()
{
    Super::TerminateObject();
    
}

void Chunk::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Manager->shader->Bind();
    SetMVP();

    URenderer::Draw(*vao, *ibo, *Manager->shader);
}

bool Chunk::IsTickable() const
{
    return true;
}

void Chunk::UpdateChunk()
{
    Vertex.clear();
    Indices.clear();
    IndiceCount = 0;
    
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                glm::ivec3 location{ x, y, z };

                if (GetBlock(location).IsSolid())
                {
                    UpdateBlock(location, EDirection::X_NEG);
                    UpdateBlock(location, EDirection::X_POS);
                    UpdateBlock(location, EDirection::Y_NEG);
                    UpdateBlock(location, EDirection::Y_POS);
                    UpdateBlock(location, EDirection::Z_NEG);
                    UpdateBlock(location, EDirection::Z_POS);
                }
            }
        }
    }
    
    vao->Bind();
    vbo->BufferData(Vertex.data(), Vertex.size() * sizeof(GLuint));
    
    VertexBufferLayout Layout;
    Layout.Push<unsigned int>(1);
    vao->AddBuffer(*vbo, Layout);

    ibo->BufferData(Indices.data(), Indices.size());

    Manager->shader->Bind();
    Manager->shader->SetUniform4fv("u_ColorMultiplier", { 1.0f, 1.0f, 1.0f, 1.0f});
    SetMVP();
    
    Vertex.clear();
    Indices.clear();
    IndiceCount = 0;
}

Block& Chunk::GetBlock(const glm::ivec3& location)
{
    return Blocks[location.x * CHUNK_HEIGHT * CHUNK_SIZE + location.y * CHUNK_SIZE + location.z];
    //return Blocks[location.x][location.y][location.z];
}

void Chunk::UpdateBlock(const glm::ivec3& location, const EDirection Direction)
{
    if (!GetBlock(location).HasDirectionBeenUpdated(Direction))
    {
        if (!HasNeighbor(location, Direction))
        {
            switch (Direction)
            {
            case EDirection::X_NEG:
                {
                    std::array<unsigned int, 4> TempVert = {
                        GetBlockVertex(location, 0, 0, 0, 0.0f, 0.0f),
                        GetBlockVertex(location, 0, 0, 1, 1.0f, 0.0f),
                        GetBlockVertex(location, 0, 1, 1, 1.0f, 1.0f),
                        GetBlockVertex(location, 0, 1, 0, 0.0f, 1.0f)
                    };
            
                    AddData(TempVert);
                    return;
                }
            case EDirection::X_POS:
                {
                    std::array<unsigned int, 4> TempVert = {
                        GetBlockVertex(location, 1, 0, 1, 0.0f, 0.0f),
                        GetBlockVertex(location, 1, 0, 0, 1.0f, 0.0f),
                        GetBlockVertex(location, 1, 1, 0, 1.0f, 1.0f),
                        GetBlockVertex(location, 1, 1, 1, 0.0f, 1.0f)
                    };
        
                    AddData(TempVert);
                    return;
                }
            case EDirection::Y_NEG:
                {
                    std::array<unsigned int, 4> TempVert = {
                        GetBlockVertex(location, 0, 0, 0, 0.0f, 0.0f),
                        GetBlockVertex(location, 1, 0, 0, 1.0f, 0.0f),
                        GetBlockVertex(location, 1, 0, 1, 1.0f, 1.0f),
                        GetBlockVertex(location, 0, 0, 1, 0.0f, 1.0f)
                    };
        
                    AddData(TempVert);
                    return;
                }
            case EDirection::Y_POS:
                {
                    std::array<unsigned int, 4> TempVert = {
                        GetBlockVertex(location, 0, 1, 0, 0.0f, 0.0f),
                        GetBlockVertex(location, 1, 1, 0, 1.0f, 0.0f),
                        GetBlockVertex(location, 1, 1, 1, 1.0f, 1.0f),
                        GetBlockVertex(location, 0, 1, 1, 0.0f, 1.0f)
                    };
        
                    AddData(TempVert);
                    return;
                }
            case EDirection::Z_NEG:
                {
                    std::array<unsigned int, 4> TempVert = {
                        GetBlockVertex(location, 0, 0, 0, 0.0f, 0.0f),
                        GetBlockVertex(location, 1, 0, 0, 1.0f, 0.0f),
                        GetBlockVertex(location, 1, 1, 0, 1.0f, 1.0f),
                        GetBlockVertex(location, 0, 1, 0, 0.0f, 1.0f)
                    };
        
                    AddData(TempVert);
                    return;
                }
            case EDirection::Z_POS:
                {
                    std::array<unsigned int, 4> TempVert = {
                        GetBlockVertex(location, 0, 0, 1, 0.0f, 0.0f),
                        GetBlockVertex(location, 1, 0, 1, 1.0f, 0.0f),
                        GetBlockVertex(location, 1, 1, 1, 1.0f, 1.0f),
                        GetBlockVertex(location, 0, 1, 1, 0.0f, 1.0f)
                    };
        
                    AddData(TempVert);
                    return;
                }
            }
        }
    }
}

void Chunk::AddData(const std::array<unsigned int, 4>& vertex)
{
    std::array<unsigned int, 6> TempIndex = {
        IndiceCount, IndiceCount + 1, IndiceCount + 2,
        IndiceCount + 2, IndiceCount + 3, IndiceCount
    };

    IndiceCount += 4;
    Vertex.insert(Vertex.end(), vertex.begin(), vertex.end());
    Indices.insert(Indices.end(), TempIndex.begin(), TempIndex.end());
    
}

bool Chunk::HasNeighbor(const glm::ivec3& location, const EDirection Direction)
{
    switch (Direction)
    {
    case EDirection::X_NEG:
        {
            if (location.x - 1 >= 0)
            {
                // Neighbor block is from the same chunk
                Block Neighbor = GetBlock({ location.x - 1, location.y, location.z });
                if (Neighbor.IsSolid())
                {
                    GetBlock(location).SetUpdatedDirection(true, EDirection::X_NEG);
                    Neighbor.SetUpdatedDirection(true, EDirection::X_POS);
                    return true;
                }
                return false;
            }
            else
            {
                // Neighbor block is not from this chunk - needs to check neighboring chunk if it's loaded
                if (Chunk* chunk = Manager->GetChunk({ GetChunkPosition().x - 1, GetChunkPosition().y }))
                {
                    Block Neighbor = chunk->GetBlock({ 16, location.y, location.z });
                    if (Neighbor.IsSolid())
                    {
                        GetBlock(location).SetUpdatedDirection(true, EDirection::X_NEG);
                        Neighbor.SetUpdatedDirection(true, EDirection::X_POS);
                        return true;
                    }
                    return false;
                }
                return false;
            }
        }
    case EDirection::X_POS:
        {
            if (location.x + 1 < CHUNK_SIZE)
            {
                // Neighbor block is from the same chunk
                Block Neighbor = GetBlock({ location.x + 1, location.y, location.z });
                if (Neighbor.IsSolid())
                {
                    GetBlock(location).SetUpdatedDirection(true, EDirection::X_POS);
                    Neighbor.SetUpdatedDirection(true, EDirection::X_NEG);
                    return true;
                }
                return false;
            }
            else
            {
                // Neighbor block is not from this chunk - needs to check neighboring chunk if it's loaded
                if (Chunk* chunk = Manager->GetChunk({ GetChunkPosition().x + 1, GetChunkPosition().y }))
                {
                    Block Neighbor = chunk->GetBlock({ 0, location.y, location.z });
                    if (Neighbor.IsSolid())
                    {
                        GetBlock(location).SetUpdatedDirection(true, EDirection::X_NEG);
                        Neighbor.SetUpdatedDirection(true, EDirection::X_POS);
                        return true;
                    }
                    return false;
                }
                return false;
            }
        }
    case EDirection::Y_NEG:
        {
            if (location.y - 1 >= 0)
            {
                // Neighbor block is from the same chunk
                Block Neighbor = GetBlock({ location.x, location.y - 1, location.z });
                if (Neighbor.IsSolid())
                {
                    GetBlock(location).SetUpdatedDirection(true, EDirection::Y_NEG);
                    Neighbor.SetUpdatedDirection(true, EDirection::Y_POS);
                    return true;
                }
                return false;
            }
            return false;
        }
    case EDirection::Y_POS:
        {
            if (location.y + 1 < CHUNK_HEIGHT)
            {
                // Neighbor block is from the same chunk
                Block Neighbor = GetBlock({ location.x, location.y + 1, location.z });
                if (Neighbor.IsSolid())
                {
                    GetBlock(location).SetUpdatedDirection(true, EDirection::Y_POS);
                    Neighbor.SetUpdatedDirection(true, EDirection::Y_NEG);
                    return true;
                }
                return false;
            }
            return false;
        }
    case EDirection::Z_NEG:
        {
            if (location.z - 1 >= 0)
            {
                // Neighbor block is from the same chunk
                Block Neighbor = GetBlock({ location.x, location.y, location.z - 1});
                if (Neighbor.IsSolid())
                {
                    GetBlock(location).SetUpdatedDirection(true, EDirection::Z_NEG);
                    Neighbor.SetUpdatedDirection(true, EDirection::Z_POS);
                    return true;
                }
                return false;
            }
            else
            {
                // Neighbor block is not from this chunk - needs to check neighboring chunk if it's loaded
                if (Chunk* chunk = Manager->GetChunk({ GetChunkPosition().x, GetChunkPosition().y - 1 }))
                {
                    Block Neighbor = chunk->GetBlock({ location.x, location.y, 16 });
                    if (Neighbor.IsSolid())
                    {
                        GetBlock(location).SetUpdatedDirection(true, EDirection::Z_NEG);
                        Neighbor.SetUpdatedDirection(true, EDirection::Z_POS);
                        return true;
                    }
                    return false;
                }
                return false;
            }
        }
    case EDirection::Z_POS:
        {
            if (location.z + 1 < CHUNK_SIZE)
            {
                // Neighbor block is from the same chunk
                Block Neighbor = GetBlock({ location.x, location.y, location.z + 1});
                if (Neighbor.IsSolid())
                {
                    GetBlock(location).SetUpdatedDirection(true, EDirection::Z_POS);
                    Neighbor.SetUpdatedDirection(true, EDirection::Z_NEG);
                    return true;
                }
                return false;
            }
            else
            {
                // Neighbor block is not from this chunk - needs to check neighboring chunk if it's loaded
                if (Chunk* chunk = Manager->GetChunk({ GetChunkPosition().x, GetChunkPosition().y + 1 }))
                {
                    Block Neighbor = chunk->GetBlock({ location.x, location.y, 0 });
                    if (Neighbor.IsSolid())
                    {
                        GetBlock(location).SetUpdatedDirection(true, EDirection::Z_POS);
                        Neighbor.SetUpdatedDirection(true, EDirection::Z_NEG);
                        return true;
                    }
                    return false;
                }
                return false;
            }
        }
    }

    return false;
}

bool Chunk::IsBlockSolid(unsigned int BlockIndex)
{
    return true;
}

unsigned int Chunk::GetBlockVertex(const glm::ivec3& location, unsigned int xOffset, unsigned int yOffset, unsigned int zOffset, float xUv, float yUv)
{
    unsigned int Storage = 0;
    unsigned int Byte = 0;

    unsigned int x = location.x;
    unsigned int y = location.y;
    unsigned int z = location.z;

    unsigned int xUV = (unsigned int)xUv;
    unsigned int yUV = (unsigned int)yUv;

    // Byte 3 - Flags
    x += xOffset;
    if (x == 16)
    {
        Byte |= 0x1u << 2;
        x = 15;
    }

    y += yOffset;
    if (y == 256)
    {
        Byte |= 0x1u << 1;
        y = 255;
    }

    z += zOffset;
    if (z == 16)
    {
        Byte |= 0x1u << 0;
        z = 15;
    }
    
    Storage |= ((Byte << 24) & 0xFF000000u);
    Byte = 0;

    // Byte 2 - UV Coords
    Byte = (xUV << 4) | yUV;
    Storage |= ((Byte << 16) & 0x00FF0000u);
    Byte = 0;

    // Byte 1 - xzPos
    Byte = (x << 4) | z;
    Storage |= ((Byte << 8) & 0x0000FF00u);
    Byte = 0;

    // Byte 0 - yPos
    Storage |= y;

    return Storage;
}

void Chunk::SetMVP()
{
    glm::mat4 proj = URenderer::GetProjMat();
    glm::mat4 view = URenderer::GetViewMat();

    glm::mat4 rotatex = glm::rotate(glm::mat4(1.0f), glm::radians(GetEntityRotation().x), {1.0f, 0.0f, 0.0f});
    glm::mat4 rotatey = glm::rotate(rotatex, glm::radians(GetEntityRotation().y), {0.0f, 1.0f, 0.0f});
    glm::mat4 rotation = glm::rotate(rotatey, glm::radians(GetEntityRotation().z), {0.0f, 0.0f, 1.0f});
    
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), GetEntityLocation());
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), GetEntityScale());
    glm::mat4 model = translation;

    glm::mat4 mvp = proj * view * model;

    Manager->shader->SetUniformMat4f("u_MVP", mvp);
}
