#pragma once

#include "events/Event.h"
#include "glcore/Renderer.h"

class Layer {
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnEvent(Event& evnet) {}
	virtual void OnUpdate(float timestep) {}
	virtual void OnRender(Renderer& renderer) {}
	virtual void OnImGuiRender() {}
};