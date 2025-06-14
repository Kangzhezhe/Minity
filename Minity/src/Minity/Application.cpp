#include "pch.h"
#include "Minity/Application.h"

#include "Minity/Log.h"
#include "Minity/Events/ApplicationEvent.h"

namespace Minity {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {

		while (1) {
			std::cout << "Application is running." << std::endl;
		}
	}

}  // namespace Minity
