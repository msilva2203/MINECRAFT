#include "Game/Block.h"

#include "Rendering/Renderer.h"

Block::Block() : 
    BlockType(EBlockType::DIRT)
{
}

Block::~Block()
{
}

void Block::InitObject()
{
    Super::InitObject();
}

void Block::TerminateObject()
{
    Super::TerminateObject();
}

void Block::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

bool Block::IsTickable() const
{
    return true;
}

void Block::SetUpdatedDirection(const bool bNewValue, const EDirection Direction)
{
    switch (Direction)
    {
    case EDirection::X_NEG:
        bUpdatedX_NEG = bNewValue;
        return;
    case EDirection::X_POS:
        bUpdatedX_POS = bNewValue;
        return;
    case EDirection::Y_NEG:
        bUpdatedY_NEG = bNewValue;
        return;
    case EDirection::Y_POS:
        bUpdatedY_POS = bNewValue;
        return;
    case EDirection::Z_NEG:
        bUpdatedZ_NEG = bNewValue;
        return;
    case EDirection::Z_POS:
        bUpdatedZ_POS = bNewValue;
        return;
    }
}

bool Block::HasDirectionBeenUpdated(const EDirection Direction)
{
    switch (Direction)
    {
    case EDirection::X_NEG:
        return bUpdatedX_NEG;
    case EDirection::X_POS:
        return bUpdatedX_POS;
    case EDirection::Y_NEG:
        return bUpdatedY_NEG;
    case EDirection::Y_POS:
        return bUpdatedY_POS;
    case EDirection::Z_NEG:
        return bUpdatedZ_NEG;
    case EDirection::Z_POS:
        return bUpdatedZ_POS;
    }
}

bool Block::HasBeenUpdated()
{
    return bUpdatedX_NEG && bUpdatedX_POS && bUpdatedY_NEG && bUpdatedY_POS && bUpdatedZ_NEG && bUpdatedZ_POS;
}

bool Block::IsSolid() const
{
    return BlockType != EBlockType::VOID;
}
