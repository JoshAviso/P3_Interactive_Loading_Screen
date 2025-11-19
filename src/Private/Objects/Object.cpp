#include <Objects/Object.h>

#include <Components/Renderers/IRenderer.h>

bool Object::Intersects(Vec2 position) {
	if (!Enabled) return false;
	for (const auto& component : _components)
	{
		if (IRenderer* renderer = dynamic_cast<IRenderer*>(component.get())) {
			if (renderer->Intersects(position)) return true;
		}
	}
	return false;
}
