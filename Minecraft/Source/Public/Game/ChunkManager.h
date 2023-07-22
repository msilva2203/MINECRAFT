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
    X_NEG, X_POS,
    Y_NEG, Y_POS,
    Z_NEG, Z_POS
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
