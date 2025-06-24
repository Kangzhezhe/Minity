#include "Minity/Application.h"

#include "Minity/Log.h"
#include "Minity/Window.h"
#include "pch.h"
#include "Core.h"


namespace Minity {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
        s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(MN_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			m_LayerStack.OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MN_BIND_EVENT_FN(Application::OnWindowClose));
		MN_CORE_INFO("Event {0}", e);

		m_LayerStack.OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

}  // namespace Minity
