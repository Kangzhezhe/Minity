#include "Minity.h"

class ExampleLayer : public Minity::Layer {
public:
	ExampleLayer() : Layer("ExampleLayer") {}

	void OnAttach() override {}

	void OnDetach() override {}

	void OnUpdate() override {}

	void OnEvent(Minity::Event& event) override {
		MN_CORE_TRACE("ExampleLayer received event: {0}", event);
	}
};

class SandBoxApp : public Minity::Application {
private:
public:
	SandBoxApp();
	~SandBoxApp();
};

SandBoxApp::SandBoxApp() {
	PushLayer(new ExampleLayer());
	PushOverlay(new Minity::ImGuiLayer());
}

SandBoxApp::~SandBoxApp() {}

Minity::Application* Minity::CreateApplication() { return new SandBoxApp(); }