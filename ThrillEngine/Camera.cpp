#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Application.h"
#include "Input.h"
#include "TimeManager.h"


void Camera::View(glm::vec3 v)
{
    cam_position = v;
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::Projection(float degree, float input_near, float input_far)
{
    glm::vec2 window_size = APPLICATION->GetWindowSize();
    near = input_near;
    far = input_far;
    fov = degree;
    projection = glm::perspective(glm::radians(degree), window_size.x / window_size.y, near, far);
}

glm::mat4 Camera::GetViewMatrix()
{
    return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projection;
}

void Camera::Move(glm::vec3 v)
{
    cam_position += v* TIMEMANAGER->deltaTime * 2.5f;
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::RotateYaxis(float degree)
{
    yaw += degree;
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam_target = glm::normalize(direction);
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::RotateXaxis(float degree)
{
    pitch -= degree;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam_target = glm::normalize(direction);
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::SetPitch(float degree)
{
    pitch = degree;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::SetYaw(float degree)
{
    yaw = degree;
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam_target = glm::normalize(direction);
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::MoveForward(float amount)
{
    cam_position += glm::normalize((cam_target))*amount * TIMEMANAGER->deltaTime * 2.5f;
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::MoveSide(float amount)
{
    cam_position += -glm::normalize(glm::cross(up,cam_target))*amount * TIMEMANAGER->deltaTime * 2.5f;
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
}

void Camera::MouseMoveUpdate()
{
    glm::vec2 mouse_pos = Input::GetMousePosition();
    float xpos = mouse_pos.x;
    float ypos = mouse_pos.y;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam_target = glm::normalize(direction);
    view = glm::lookAt(cam_position, cam_position + cam_target, up);
    lastX = xpos;
    lastY = ypos;

}

void Camera::MouseScrollUpdate()
{
    if (!ImGui::GetIO().WantCaptureMouse)
    {
        float scroll = Input::GetScroll();
        fov -= scroll;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    }
    glm::vec2 window_size = APPLICATION->GetWindowSize();
    if (window_size.y != 0.0f)
        projection = glm::perspective(glm::radians(fov), window_size.x / window_size.y, near, far);
}
