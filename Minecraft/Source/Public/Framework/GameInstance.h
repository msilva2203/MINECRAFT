#pragma once

#include "Object.h"

class UGameInstance : public UObject
{
public:
    virtual bool IsTickable() const override;
};
