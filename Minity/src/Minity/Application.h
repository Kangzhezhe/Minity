#pragma once
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

namespace Minity {

	class Application {
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

		virtual ~Application();

		void Run();

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}  // namespace Minity
