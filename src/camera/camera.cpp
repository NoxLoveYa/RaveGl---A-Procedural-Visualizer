/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** camera.cpp
*/

#include "camera.hpp"

glm::mat4 Camera::GetViewMatrix() { return glm::lookAt(Position, Position + Front, Up); }

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front   = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(
        Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more
                          // you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

void handleMouseDragging(GLFWwindow* window, MouseState& mouseState, Camera& camera) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (!mouseState.isDragging) {
            mouseState.lastX      = static_cast<float>(xpos);
            mouseState.lastY      = static_cast<float>(ypos);
            mouseState.isDragging = true;
        }

        float xoffset = static_cast<float>(xpos) - mouseState.lastX;
        float yoffset =
            mouseState.lastY -
            static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top

        mouseState.lastX = static_cast<float>(xpos);
        mouseState.lastY = static_cast<float>(ypos);

        camera.ProcessMouseMovement(xoffset, yoffset);
    } else {
        mouseState.isDragging = false;
    }
}