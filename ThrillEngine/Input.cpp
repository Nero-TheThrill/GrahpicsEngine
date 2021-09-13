#include "Input.h"
#include <iostream>


std::bitset<GLFW_KEY_LAST> Input::key_pressed;
std::bitset<GLFW_KEY_LAST> Input::key_triggered;
glm::vec2 Input::mouse_position;
float Input::mouse_scroll;

void Input::Init()
{
	std::cout << "InputSystem Initialize" << std::endl;
	key_pressed.reset();
	key_triggered.reset();
	mouse_position = glm::vec2{0,0};
}

void Input::Update()
{
	key_triggered.reset();
	mouse_scroll = 0;
}

void Input::SetKeyboard(KEY_STATE keystate, int key)
{
	switch (keystate)
	{
	case KEY_STATE::UP:
		key_pressed[key] = false;
		break;
	case KEY_STATE::TRIGGERED:
		key_triggered[key] = true;
		key_pressed[key] = true;
		break;
	case KEY_STATE::DOWN:
		key_pressed[key] = true;
		break;
	}
}

bool Input::IsPressed(int key)
{
    return key_pressed[key];
}

bool Input::IsReleased(int key)
{
    return !key_pressed[key];
}

bool Input::IsTriggered(int key)
{
    return key_triggered[key];
}

void Input::Reset()
{
	key_pressed.reset();
	key_triggered.reset();
	mouse_scroll = 0;
}

void Input::SetMousePosition(float x, float y)
{
	mouse_position.x = x - APPLICATION->GetWindowSize().x / 2;
	mouse_position.y = -y + APPLICATION->GetWindowSize().y / 2;
}

glm::vec2 Input::GetMousePosition()
{
	return mouse_position;
}


void Input::SetScroll(float amount)
{
	mouse_scroll = amount;
}

float Input::GetScroll()
{
	return mouse_scroll;
}
