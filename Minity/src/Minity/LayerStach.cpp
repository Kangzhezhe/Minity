#include "LayerStack.h"

namespace Minity {
	void LayerStack::PushLayer(Layer* layer) {
		m_layers.emplace(m_layers.begin() + m_LayerInsertIndex, layer);
		++m_LayerInsertIndex;
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_layers.begin(),
							m_layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_layers.begin() + m_LayerInsertIndex) {
			m_layers.erase(it);
			--m_LayerInsertIndex;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_layers.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_layers.begin() + m_LayerInsertIndex,
							m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
		}
	}

	void LayerStack::OnUpdate() {
		for (auto& layer : m_layers) {
			layer->OnUpdate();
		}
	}

	void LayerStack::OnEvent(Event& event) {
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
			if (event.Handled) {
				break;
			}
			(*it)->OnEvent(event);
		}
	}
}  // namespace Minity