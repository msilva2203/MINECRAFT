#pragma once

#include "Entity.h"

#include "Game/ChunkManager.h"

enum class EBlockType
{
    VOID = 0,
    DIRT
};


class Block : public UObject
{
    typedef UObject Super;
public:
    Block();
    ~Block();
    
    virtual void InitObject() override;
    virtual void TerminateObject() override;

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

public:
    void SetBlockType(const EBlockType NewType) { BlockType = NewType; }
    void SetUpdatedDirection(const bool bNewValue, const EDirection Direction);
    bool HasDirectionBeenUpdated(const EDirection Direction);
    bool HasBeenUpdated();
    bool IsSolid() const;

private:
    EBlockType BlockType;

    bool bUpdatedX_NEG = false;
    bool bUpdatedX_POS = false;
    bool bUpdatedY_NEG = false;
    bool bUpdatedY_POS = false;
    bool bUpdatedZ_NEG = false;
    bool bUpdatedZ_POS = false;
};
