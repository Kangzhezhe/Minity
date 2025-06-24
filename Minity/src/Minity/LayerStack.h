#pragma once
#include "Layer.h"
#include "pch.h"

namespace Minity {

	class LayerStack {
	private:
		std::vector<Layer*> m_layers;
		unsigned int m_LayerInsertIndex = 0;

	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(Layer* layer);

		void PopLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

		void PopOverlay(Layer* overlay);

		void OnUpdate();

		void OnEvent(Event& event);
	};

}  // namespace Minity