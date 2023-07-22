#pragma once

#include "Entity.h"

class APawn : public AEntity
{
    typedef AEntity Super;
public:
    APawn();
    
public:
    virtual void InitObject() override;
    
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

    virtual void HandleInput();
    virtual void KeyCallback(int key, int action);
    virtual void MouseCallback(double xpos, double ypos);

private:
    float CameraAxisX, CameraAxisY;
    double LastX, LastY;
    float Speed;
};
