#pragma once
#include"Application.h"
#include <bitset>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class KEY_STATE
{
    UP,
    TRIGGERED,
    DOWN
};
class Input
{
public:
    static void Init();
    static void Update();
    static void SetKeyboard(KEY_STATE keystate, int key); // mosue + keyboard

    static bool IsPressed(int key);
    static bool IsReleased(int key);
    static bool IsTriggered(int key);

    static void Reset();

    static void SetMousePosition(float x, float y);
    static glm::vec2 GetMousePosition();

    static void SetScroll(float amount);
    static float GetScroll();

private:
    static std::bitset<GLFW_KEY_LAST> key_pressed;
    static std::bitset<GLFW_KEY_LAST> key_triggered;
    static glm::vec2 mouse_position;
    static float mouse_scroll;

};









