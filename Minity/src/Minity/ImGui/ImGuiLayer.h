#pragma once

#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Minity/Application.h"
#include "Minity/Layer.h"
#include "imgui.h"

namespace Minity {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer() : Layer("ImGuiLayer") {
			m_Window =
				(GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		}

		virtual void OnAttach() override;

		virtual void OnDetach() override;

		virtual void OnUpdate() override;

		virtual void OnEvent(Event& event) override;

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);

	private:
		GLFWwindow* m_Window;
	};

	ImGuiKey GlfwKeyToImGuiKey(int keycode);

}  // namespace Minity
