#pragma once
#include "Events/Event.h"

namespace Minity {
	class Layer {
        std::string m_LayerName;
	public:
		Layer(const std::string& name = "Layer"): m_LayerName(name) {};
		virtual ~Layer() = default;

		virtual void OnAttach() {}

		virtual void OnDetach() {}

		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event) {}
	};
}  // namespace Minity
