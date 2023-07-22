#pragma once

#include "Entity.h"

#include "Game/ChunkManager.h"


class Block : public AEntity
{
    typedef AEntity Super;
public:
    Block();
    ~Block();
    
    virtual void InitObject() override;
    virtual void TerminateObject() override;

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

public:
    void SetChunkLocation(const glm::vec3 NewLocation) { ChunkLocation = NewLocation; }
    glm::vec3 GetChunkLocation() const { return ChunkLocation; }
    void SetUpdatedDirection(const bool bNewValue, const EDirection Direction);
    bool HasDirectionBeenUpdated(const EDirection Direction);
    bool HasBeenUpdated();
    bool IsSolid() const;

private:
    glm::vec3 ChunkLocation;

    bool bUpdatedX_NEG = false;
    bool bUpdatedX_POS = false;
    bool bUpdatedY_NEG = false;
    bool bUpdatedY_POS = false;
    bool bUpdatedZ_NEG = false;
    bool bUpdatedZ_POS = false;
};
