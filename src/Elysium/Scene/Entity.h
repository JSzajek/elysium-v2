#pragma once

#include "Elysium/Core/Base.h"
#include "Elysium/Core/Asserts.h"

#include <entt.hpp>

namespace Elysium
{
	class Scene;

	class Entity
	{
	private:
		entt::entity m_handle;
		Scene* m_scene;
	public:
		Entity();
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& copy);
	public:
		inline operator bool() const { return m_handle != entt::null; }
		inline operator entt::entity() const { return m_handle; }
		inline operator uint32_t() const { return static_cast<uint32_t>(m_handle); }

		inline bool operator==(const Entity& r_val) const { return m_handle == r_val.m_handle && m_scene == r_val.m_scene; }
		inline bool operator!=(const Entity& r_val) const { return m_handle != r_val.m_handle || m_scene != r_val.m_scene; }
	public:
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ELYSIUM_CORE_ASSERT(!HasComponent<T>(), "Entity Already Contains Component");
			auto& component = m_scene->m_registry->emplace<T>(m_handle, std::forward<Args>(args)...);
			m_scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			ELYSIUM_CORE_ASSERT(HasComponent<T>(), "Entity Does Not Contain Component, Try Using TryGetComponent Instead.");
			return m_scene->m_registry->get<T>(m_handle);
		}

		template<typename T>
		inline T& TryGetComponent()
		{
			return m_scene->m_registry->try_get<T>(m_handle);
		}

		template<typename T>
		inline bool HasComponent()
		{
			return m_scene->m_registry->all_of<T>(m_handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			ELYSIUM_CORE_ASSERT(HasComponent<T>(), "Attempting to Remove Non-Existing Component.");
			auto& component = m_scene->m_registry->get<T>(m_handle);
			m_scene->OnComponentRemove<T>(*this, component);
			m_scene->m_registry->remove<T>(m_handle);
		}
	};
}

