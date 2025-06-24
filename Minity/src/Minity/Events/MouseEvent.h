#pragma once
#include "Events/Event.h"

namespace Minity {

class MouseMovedEvent : public Event {
private:
    float m_MouseX, m_MouseY;
public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    std::string ToString() const override {
        return "MouseMovedEvent: " + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY);
    }
};

class MouseScrolledEvent : public Event {
private:
    float m_XOffset, m_YOffset;
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {}
    float GetXOffset() const { return m_XOffset; }
    float GetYOffset() const { return m_YOffset; }
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    std::string ToString() const override {
        return "MouseScrolledEvent: " + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset);
    }
};

class MouseButtonEvent : public Event {
protected:
    int m_Button;
    MouseButtonEvent(int button) : m_Button(button) {}
public:
    int GetMouseButton() const { return m_Button; }
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
    EVENT_CLASS_TYPE(MouseButtonPressed)
    std::string ToString() const override {
        return "MouseButtonPressedEvent: " + std::to_string(m_Button);
    }
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
    EVENT_CLASS_TYPE(MouseButtonReleased)
    std::string ToString() const override {
        return "MouseButtonReleasedEvent: " + std::to_string(m_Button);
    }
};

} // namespace Minity