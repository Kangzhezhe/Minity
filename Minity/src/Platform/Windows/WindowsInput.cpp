#include "WindowsInput.h"
#include "GLFW/glfw3.h"

namespace Minity {

    Input* Input::s_Instance = new WindowsInput();
    

    bool WindowsInput::IsKeyPressedImpl(int keycode) {
        auto window = glfwGetCurrentContext();
        return glfwGetKey(window, keycode) == GLFW_PRESS;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button) {
        auto window = glfwGetCurrentContext();
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl() {
        double xpos, ypos;
        auto window = glfwGetCurrentContext();
        glfwGetCursorPos(window, &xpos, &ypos);
        return { static_cast<float>(xpos), static_cast<float>(ypos) };
    }

    float WindowsInput::GetMouseXImpl() {
        return GetMousePositionImpl().first;
    }

    float WindowsInput::GetMouseYImpl() {
        return GetMousePositionImpl().second;
    }

    float WindowsInput::GetMouseScrollXImpl() {
        // Not implemented in this example
        return 0.0f;
    }

    float WindowsInput::GetMouseScrollYImpl() {
        // Not implemented in this example
        return 0.0f;
    }
}  // namespace Minity

    