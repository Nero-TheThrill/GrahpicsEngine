#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


#include "Application.h"


void Camera::View(glm::vec3 v)
{
    view=  glm::translate(view, v);
}

void Camera::Projection(float radian, float near, float far)
{
    glm::vec2 window_size=APPLICATION->GetWindowSize();
    projection=glm::perspective(glm::radians(radian), window_size.x / window_size.y, near, far);
}

glm::mat4 Camera::GetViewMatrix()
{
    return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projection;
}
