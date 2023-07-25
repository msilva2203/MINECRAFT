#pragma once
#include "Object.h"

#include <vector>

#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

#define CHUNK_COUNT 5

// Forward Declarations
class Chunk;

enum class EDirection
{
    X_NEG = 0, X_POS = 1,
    Y_NEG = 2, Y_POS = 3,
    Z_NEG = 4, Z_POS = 5
};

class UChunkManager : public UObject
{
    typedef UObject Super;
public:
    UChunkManager();
    ~UChunkManager();
    
    void InitObject() override;
    void TerminateObject() override;

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

    Chunk* GetChunk(const glm::ivec2& position);

public:
    void BindShader();

    Shader* shader;
    Texture* texture;

private:
    std::vector<Chunk*> Chunks;
};
