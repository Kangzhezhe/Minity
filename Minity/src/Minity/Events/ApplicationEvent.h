#pragma once

#include "Minity/Events/Event.h"

namespace Minity {
	class ApplicationEvent : public Event {
	private:
	public:
		ApplicationEvent(/* args */){}
		~ApplicationEvent(){}

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

    class WindowCloseEvent : public ApplicationEvent {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowResizeEvent : public ApplicationEvent {
    private:
        unsigned int m_Width, m_Height;
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        EVENT_CLASS_TYPE(WindowResize)

        std::string ToString() const override {
            return "WindowResizeEvent: " + std::to_string(m_Width) + ", " + std::to_string(m_Height);
        }
    };


}  // namespace Minity
