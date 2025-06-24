#pragma once

#include "pch.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

#define BIT(x) (int)(1 << x)

namespace Minity {

	enum class EventType {
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,

		AppTick,
		AppUpdate,
		AppRender,

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class Event {
	private:
	public:
		bool Handled = false;

		Event(){};
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;

		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) const {
			return GetCategoryFlags() & (category);
		}
	};

#define EVENT_CLASS_TYPE(type)                                   \
	static EventType GetStaticType() { return EventType::type; } \
	virtual EventType GetEventType() const override {            \
		return GetStaticType();                                  \
	}                                                            \
	virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetCategoryFlags() const override { return category; }

	class EventDispatcher {
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		Event& m_Event;

	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		~EventDispatcher() = default;

		template <typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	};

}  // namespace Minity

template <typename T>
struct fmt::formatter<T, char, std::enable_if_t<std::is_base_of<Minity::Event, T>::value>>
    : fmt::ostream_formatter {};
