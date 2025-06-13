#pragma once

namespace Minity {

	class Application {
	private:
		/* data */
	public:
		Application();

		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application *CreateApplication();

}  // namespace Minity
