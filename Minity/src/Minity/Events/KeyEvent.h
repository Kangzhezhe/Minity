#pragma once
#include "Events/Event.h"

namespace Minity {

	class KeyEvent : public Event {
	protected:
		int m_KeyCode;
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

	public:
		int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class KeyPressedEvent : public KeyEvent {
	private:
		int m_RepeatCount;

	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		int GetRepeatCount() const { return m_RepeatCount; }
		EVENT_CLASS_TYPE(KeyPressed)
		std::string ToString() const override {
			return "KeyPressedEvent: " + std::to_string(m_KeyCode) + " (" +
				   std::to_string(m_RepeatCount) + " repeats)";
		}
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KeyReleased)
		std::string ToString() const override {
			return "KeyReleasedEvent: " + std::to_string(m_KeyCode);
		}
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KeyTyped)
		std::string ToString() const override {
			return "KeyTypedEvent: " + std::to_string(m_KeyCode);
		}
	};

}  // namespace Minity