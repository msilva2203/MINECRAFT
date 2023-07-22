//
// Created by Marco Silva on 2023/07/09
//

#include "Framework/Input.h"

#include "Framework/PlayerController.h"
#include "Statics/GameplayStatics.h"
#include "Statics/Globals.h"

static UInput* InputObject;

UInput* UInput::GetInputObject()
{
    if (IsValid(InputObject))
        return InputObject;

    return InputObject = new UInput;
}

bool UInput::AddAxisInput(const std::string& name)
{
    if (InputMap.find(name) != InputMap.end())
        return false;

    for (const auto& Axis : Inputs)
    {
        if (Axis->Name == name)
            return false;
    }

    AxisInput* NewAxis = new AxisInput;
    Inputs.push_back(NewAxis);

    unsigned int index = Inputs.size() - 1;
    InputMap[name] = index;

    return true;
}

bool UInput::AddKeyToAxisInput(const std::string& name, const InputKey& Key)
{
    if (InputMap.find(name) == InputMap.end())
        return false;

    unsigned int index = InputMap[name];
    InputKey NewKey = Key;

    Inputs[index]->Keys.push_back(NewKey);

    return true;
}

float UInput::GetAxisValue(const std::string& name)
{
    if (InputMap.find(name) == InputMap.end())
        return 0.0f;

    float Value = 0.0f;
    unsigned int index = InputMap[name];
    for (auto& Key : Inputs[index]->Keys)
    {
        Value += (Key.bState ? Key.Value : 0.0f);
    }

    return Value;
}

void UInput::InputObjectKeyCallback(int key, int action)
{
    for (auto& Input : Inputs)
    {
        for (auto& Key : Input->Keys)
        {
            if (Key.Key == key)
            {
                if (action == INPUT_PRESS)   Key.bState = true;
                if (action == INPUT_RELEASE) Key.bState = false;
            }
        }
    }
}

void UInput::SetInputMode(int mode, int value)
{
    if (IsValid(GRenderer))
        glfwSetInputMode(GRenderer->GetWindow(), mode, value);
}

int UInput::GetKey(int key)
{
    if (IsValid(GRenderer))
        return glfwGetKey(GRenderer->GetWindow(), key);

    return 0;
}

void UInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GApp);
    if (IsValid(PlayerController))
        PlayerController->OnKeyCallback(key, action);

    if (UInput* Input = GetInputObject())
        Input->InputObjectKeyCallback(key, action);
}

void UInput::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (IsValid(GApp))
    {
        UGameplayStatics::GetPlayerController(GApp)->OnMouseCallback(xpos, ypos);
    }
}
