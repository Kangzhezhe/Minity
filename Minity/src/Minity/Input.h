#pragma once

#include "pch.h"

namespace Minity {
	class Input {
	public:
		inline static bool IsKeyPressed(int keycode) {
            return s_Instance->IsKeyPressedImpl(keycode);
        }
        inline static bool IsMouseButtonPressed(int button) {
            return s_Instance->IsMouseButtonPressedImpl(button);
        }
        inline static std::pair<float, float> GetMousePosition() {
            return s_Instance->GetMousePositionImpl();
        }
        inline static float GetMouseX() {
            return s_Instance->GetMouseXImpl();
        }
        inline static float GetMouseY() {
            return s_Instance->GetMouseYImpl();
        }
        inline static float GetMouseScrollX() {
            return s_Instance->GetMouseScrollXImpl();
        }
        inline static float GetMouseScrollY() {
            return s_Instance->GetMouseScrollYImpl();
        }

	protected:

        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        virtual float GetMouseScrollXImpl() = 0;
        virtual float GetMouseScrollYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}  // namespace Minity
