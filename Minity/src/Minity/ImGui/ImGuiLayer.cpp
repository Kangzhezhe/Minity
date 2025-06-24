#include "Minity/ImGui/ImGuiLayer.h"

#include "Core.h"
#include "Log.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Minity {

	void ImGuiLayer::OnAttach() {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		// ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void ImGuiLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		// ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate() {
		ImGui_ImplOpenGL3_NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize =
			ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 示例窗口
		static bool show_demo_window = true;
		static bool show_another_window = false;
		static float f = 0.0f;
		static int counter = 0;
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("Hello, world!");
		ImGui::Text("This is some useful text.");
		ImGui::Checkbox("Demo Window", &show_demo_window);
		ImGui::Checkbox("Another Window", &show_another_window);
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Button")) counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
					1000.0f / ImGui::GetIO().Framerate,
					ImGui::GetIO().Framerate);
		ImGui::End();

		if (show_another_window) {
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me")) show_another_window = false;
			ImGui::End();
		}

		ImGui::Render();
		int display_w, display_h;
		// glfwGetFramebufferSize(m_Window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w,
					 clear_color.y * clear_color.w,
					 clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e) {
		if ((e.GetCategoryFlags()) &
			(EventCategoryMouseButton | EventCategoryMouse |
			 EventCategoryKeyboard)) {
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<MouseButtonPressedEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
			dispatcher.Dispatch<MouseButtonReleasedEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
			dispatcher.Dispatch<MouseMovedEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
			dispatcher.Dispatch<MouseScrolledEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
			dispatcher.Dispatch<KeyPressedEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
			dispatcher.Dispatch<KeyReleasedEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
			dispatcher.Dispatch<KeyTypedEvent>(
				MN_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
			MN_CORE_INFO("ImGuiLayer event:{0}", e);
		}
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		if (e.GetMouseButton() >= 0 &&
			e.GetMouseButton() < ImGuiMouseButton_COUNT)
			io.AddMouseButtonEvent(e.GetMouseButton(), GLFW_PRESS);
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		if (e.GetMouseButton() >= 0 &&
			e.GetMouseButton() < ImGuiMouseButton_COUNT)
			io.AddMouseButtonEvent(e.GetMouseButton(), GLFW_RELEASE);
		return false;
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent((float)e.GetX(), (float)e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent((float)e.GetXOffset(), (float)e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey imgui_key = GlfwKeyToImGuiKey(e.GetKeyCode());
		io.AddKeyEvent(imgui_key, true);
		return false;
	}

	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey imgui_key = GlfwKeyToImGuiKey(e.GetKeyCode());
		io.AddKeyEvent(imgui_key, false);
		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter((unsigned int)e.GetKeyCode());
		return false;
	}

	ImGuiKey GlfwKeyToImGuiKey(int keycode) {
		switch (keycode) {
			case GLFW_KEY_TAB:
				return ImGuiKey_Tab;
			case GLFW_KEY_LEFT:
				return ImGuiKey_LeftArrow;
			case GLFW_KEY_RIGHT:
				return ImGuiKey_RightArrow;
			case GLFW_KEY_UP:
				return ImGuiKey_UpArrow;
			case GLFW_KEY_DOWN:
				return ImGuiKey_DownArrow;
			case GLFW_KEY_PAGE_UP:
				return ImGuiKey_PageUp;
			case GLFW_KEY_PAGE_DOWN:
				return ImGuiKey_PageDown;
			case GLFW_KEY_HOME:
				return ImGuiKey_Home;
			case GLFW_KEY_END:
				return ImGuiKey_End;
			case GLFW_KEY_INSERT:
				return ImGuiKey_Insert;
			case GLFW_KEY_DELETE:
				return ImGuiKey_Delete;
			case GLFW_KEY_BACKSPACE:
				return ImGuiKey_Backspace;
			case GLFW_KEY_SPACE:
				return ImGuiKey_Space;
			case GLFW_KEY_ENTER:
				return ImGuiKey_Enter;
			case GLFW_KEY_ESCAPE:
				return ImGuiKey_Escape;
			case GLFW_KEY_APOSTROPHE:
				return ImGuiKey_Apostrophe;
			case GLFW_KEY_COMMA:
				return ImGuiKey_Comma;
			case GLFW_KEY_MINUS:
				return ImGuiKey_Minus;
			case GLFW_KEY_PERIOD:
				return ImGuiKey_Period;
			case GLFW_KEY_SLASH:
				return ImGuiKey_Slash;
			case GLFW_KEY_SEMICOLON:
				return ImGuiKey_Semicolon;
			case GLFW_KEY_EQUAL:
				return ImGuiKey_Equal;
			case GLFW_KEY_LEFT_BRACKET:
				return ImGuiKey_LeftBracket;
			case GLFW_KEY_BACKSLASH:
				return ImGuiKey_Backslash;
			case GLFW_KEY_WORLD_1:
				return ImGuiKey_Oem102;
			case GLFW_KEY_WORLD_2:
				return ImGuiKey_Oem102;
			case GLFW_KEY_RIGHT_BRACKET:
				return ImGuiKey_RightBracket;
			case GLFW_KEY_GRAVE_ACCENT:
				return ImGuiKey_GraveAccent;
			case GLFW_KEY_CAPS_LOCK:
				return ImGuiKey_CapsLock;
			case GLFW_KEY_SCROLL_LOCK:
				return ImGuiKey_ScrollLock;
			case GLFW_KEY_NUM_LOCK:
				return ImGuiKey_NumLock;
			case GLFW_KEY_PRINT_SCREEN:
				return ImGuiKey_PrintScreen;
			case GLFW_KEY_PAUSE:
				return ImGuiKey_Pause;
			case GLFW_KEY_KP_0:
				return ImGuiKey_Keypad0;
			case GLFW_KEY_KP_1:
				return ImGuiKey_Keypad1;
			case GLFW_KEY_KP_2:
				return ImGuiKey_Keypad2;
			case GLFW_KEY_KP_3:
				return ImGuiKey_Keypad3;
			case GLFW_KEY_KP_4:
				return ImGuiKey_Keypad4;
			case GLFW_KEY_KP_5:
				return ImGuiKey_Keypad5;
			case GLFW_KEY_KP_6:
				return ImGuiKey_Keypad6;
			case GLFW_KEY_KP_7:
				return ImGuiKey_Keypad7;
			case GLFW_KEY_KP_8:
				return ImGuiKey_Keypad8;
			case GLFW_KEY_KP_9:
				return ImGuiKey_Keypad9;
			case GLFW_KEY_KP_DECIMAL:
				return ImGuiKey_KeypadDecimal;
			case GLFW_KEY_KP_DIVIDE:
				return ImGuiKey_KeypadDivide;
			case GLFW_KEY_KP_MULTIPLY:
				return ImGuiKey_KeypadMultiply;
			case GLFW_KEY_KP_SUBTRACT:
				return ImGuiKey_KeypadSubtract;
			case GLFW_KEY_KP_ADD:
				return ImGuiKey_KeypadAdd;
			case GLFW_KEY_KP_ENTER:
				return ImGuiKey_KeypadEnter;
			case GLFW_KEY_KP_EQUAL:
				return ImGuiKey_KeypadEqual;
			case GLFW_KEY_LEFT_SHIFT:
				return ImGuiKey_LeftShift;
			case GLFW_KEY_LEFT_CONTROL:
				return ImGuiKey_LeftCtrl;
			case GLFW_KEY_LEFT_ALT:
				return ImGuiKey_LeftAlt;
			case GLFW_KEY_LEFT_SUPER:
				return ImGuiKey_LeftSuper;
			case GLFW_KEY_RIGHT_SHIFT:
				return ImGuiKey_RightShift;
			case GLFW_KEY_RIGHT_CONTROL:
				return ImGuiKey_RightCtrl;
			case GLFW_KEY_RIGHT_ALT:
				return ImGuiKey_RightAlt;
			case GLFW_KEY_RIGHT_SUPER:
				return ImGuiKey_RightSuper;
			case GLFW_KEY_MENU:
				return ImGuiKey_Menu;
			case GLFW_KEY_0:
				return ImGuiKey_0;
			case GLFW_KEY_1:
				return ImGuiKey_1;
			case GLFW_KEY_2:
				return ImGuiKey_2;
			case GLFW_KEY_3:
				return ImGuiKey_3;
			case GLFW_KEY_4:
				return ImGuiKey_4;
			case GLFW_KEY_5:
				return ImGuiKey_5;
			case GLFW_KEY_6:
				return ImGuiKey_6;
			case GLFW_KEY_7:
				return ImGuiKey_7;
			case GLFW_KEY_8:
				return ImGuiKey_8;
			case GLFW_KEY_9:
				return ImGuiKey_9;
			case GLFW_KEY_A:
				return ImGuiKey_A;
			case GLFW_KEY_B:
				return ImGuiKey_B;
			case GLFW_KEY_C:
				return ImGuiKey_C;
			case GLFW_KEY_D:
				return ImGuiKey_D;
			case GLFW_KEY_E:
				return ImGuiKey_E;
			case GLFW_KEY_F:
				return ImGuiKey_F;
			case GLFW_KEY_G:
				return ImGuiKey_G;
			case GLFW_KEY_H:
				return ImGuiKey_H;
			case GLFW_KEY_I:
				return ImGuiKey_I;
			case GLFW_KEY_J:
				return ImGuiKey_J;
			case GLFW_KEY_K:
				return ImGuiKey_K;
			case GLFW_KEY_L:
				return ImGuiKey_L;
			case GLFW_KEY_M:
				return ImGuiKey_M;
			case GLFW_KEY_N:
				return ImGuiKey_N;
			case GLFW_KEY_O:
				return ImGuiKey_O;
			case GLFW_KEY_P:
				return ImGuiKey_P;
			case GLFW_KEY_Q:
				return ImGuiKey_Q;
			case GLFW_KEY_R:
				return ImGuiKey_R;
			case GLFW_KEY_S:
				return ImGuiKey_S;
			case GLFW_KEY_T:
				return ImGuiKey_T;
			case GLFW_KEY_U:
				return ImGuiKey_U;
			case GLFW_KEY_V:
				return ImGuiKey_V;
			case GLFW_KEY_W:
				return ImGuiKey_W;
			case GLFW_KEY_X:
				return ImGuiKey_X;
			case GLFW_KEY_Y:
				return ImGuiKey_Y;
			case GLFW_KEY_Z:
				return ImGuiKey_Z;
			case GLFW_KEY_F1:
				return ImGuiKey_F1;
			case GLFW_KEY_F2:
				return ImGuiKey_F2;
			case GLFW_KEY_F3:
				return ImGuiKey_F3;
			case GLFW_KEY_F4:
				return ImGuiKey_F4;
			case GLFW_KEY_F5:
				return ImGuiKey_F5;
			case GLFW_KEY_F6:
				return ImGuiKey_F6;
			case GLFW_KEY_F7:
				return ImGuiKey_F7;
			case GLFW_KEY_F8:
				return ImGuiKey_F8;
			case GLFW_KEY_F9:
				return ImGuiKey_F9;
			case GLFW_KEY_F10:
				return ImGuiKey_F10;
			case GLFW_KEY_F11:
				return ImGuiKey_F11;
			case GLFW_KEY_F12:
				return ImGuiKey_F12;
			case GLFW_KEY_F13:
				return ImGuiKey_F13;
			case GLFW_KEY_F14:
				return ImGuiKey_F14;
			case GLFW_KEY_F15:
				return ImGuiKey_F15;
			case GLFW_KEY_F16:
				return ImGuiKey_F16;
			case GLFW_KEY_F17:
				return ImGuiKey_F17;
			case GLFW_KEY_F18:
				return ImGuiKey_F18;
			case GLFW_KEY_F19:
				return ImGuiKey_F19;
			case GLFW_KEY_F20:
				return ImGuiKey_F20;
			case GLFW_KEY_F21:
				return ImGuiKey_F21;
			case GLFW_KEY_F22:
				return ImGuiKey_F22;
			case GLFW_KEY_F23:
				return ImGuiKey_F23;
			case GLFW_KEY_F24:
				return ImGuiKey_F24;
			default:
				return ImGuiKey_None;
		}
	}

}  // namespace Minity
