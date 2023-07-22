#include "Game/ChunkManager.h"

#include <thread>

#include "Game/Chunk.h"


UChunkManager::UChunkManager()
{
    shader = new Shader("Content/Shaders/chunk.shader");
    shader->Bind();
    texture = new Texture("Content/Textures/default.png");
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);
}

UChunkManager::~UChunkManager()
{
}

void UChunkManager::InitObject()
{
    Super::InitObject();

    for (int x = 0; x < CHUNK_COUNT; x++)
    {
        for (int z = 0; z < CHUNK_COUNT; z++)
        {
            //if (z == 3 && i == 3) break;
            
            Chunk* NewChunk = new Chunk(this, { x, z });
            NewChunk->InitObject();
            
            Chunks.push_back(NewChunk);
        }
    }

    for (auto& Chunk : Chunks)
        Chunk->UpdateChunk();
}

void UChunkManager::TerminateObject()
{
    Super::TerminateObject();
}

void UChunkManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (auto& Chunk : Chunks)
    {
        Chunk->Tick(DeltaTime);
    }
}

bool UChunkManager::IsTickable() const
{
    return true;
}

Chunk* UChunkManager::GetChunk(const glm::ivec2& position)
{
    for (auto& Chunk : Chunks)
    {
        if (Chunk->GetChunkPosition().x == position.x && Chunk->GetChunkPosition().y == position.y)
        {
            return Chunk;
        }
    }
    return nullptr;
}
