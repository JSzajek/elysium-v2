#include "elysium_pch.h"
#include "Entity.h"

namespace Elysium
{
	Entity::Entity()
		: m_handle(entt::null), m_scene(nullptr)
	{
	}
	
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_handle(handle), m_scene(scene)
	{
	}

	Entity::Entity(const Entity& copy)
		: m_handle(copy.m_handle), m_scene(copy.m_scene)
	{
	}
}