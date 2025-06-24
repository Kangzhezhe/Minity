#pragma once

#include "Events/Event.h"

namespace Minity {
	class ApplicationEvent : public Event {
	private:
	public:
		ApplicationEvent(/* args */) {}
		~ApplicationEvent() {}

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
			return "WindowResizeEvent: " + std::to_string(m_Width) + ", " +
				   std::to_string(m_Height);
		}
	};

	class WindowFocusEvent : public ApplicationEvent {
	public:
		WindowFocusEvent() {}
		EVENT_CLASS_TYPE(WindowFocus)
	};

	class WindowLostFocusEvent : public ApplicationEvent {
	public:
		WindowLostFocusEvent() {}
		EVENT_CLASS_TYPE(WindowLostFocus)
	};

	class WindowMovedEvent : public ApplicationEvent {
	private:
		int m_X, m_Y;

	public:
		WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}
		int GetX() const { return m_X; }
		int GetY() const { return m_Y; }
		EVENT_CLASS_TYPE(WindowMoved)
		std::string ToString() const override {
			return "WindowMovedEvent: " + std::to_string(m_X) + ", " +
				   std::to_string(m_Y);
		}
	};

	class AppTickEvent : public ApplicationEvent {
	public:
		AppTickEvent() {}
		EVENT_CLASS_TYPE(AppTick)
	};

	class AppUpdateEvent : public ApplicationEvent {
	public:
		AppUpdateEvent() {}
		EVENT_CLASS_TYPE(AppUpdate)
	};

	class AppRenderEvent : public ApplicationEvent {
	public:
		AppRenderEvent() {}
		EVENT_CLASS_TYPE(AppRender)
	};

}  // namespace Minity
