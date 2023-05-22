#pragma once

#include "Elysium/Core/Memory.h"

#include <string>
#include <entt.hpp>

namespace Elysium
{
	class Entity;

	class Scene
	{
	public:
		enum SceneMask : uint16_t
		{
			_3D,
			_3DDepthOnly,
			Transparent,
			Particle,
			Sprite,
			_2D,
			_2DDepthOnly,
			Gizmo3D,
			Gizmo2D
		};
	private:
		Unique<entt::registry> m_registry;
		Unique<class Renderer2D> m_renderer2D;
		Unique<class RendererGizmo> m_rendererGizmo;

		friend Entity;
	public:
		Scene();
		~Scene();
	public:
		Entity CreateEntity(const std::string& name = "");
		void DestroyEntity(Entity entity);

		void Computations();
		void Draw(SceneMask mask);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		template<typename T>
		void OnComponentRemove(Entity entity, T& component);
	};
}
