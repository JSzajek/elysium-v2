#include "elysium_pch.h"
#include "Scene.h"

#include "Elysium/Scene/Time.h"

#include "Elysium/Scene/Entity.h"
#include "Elysium/Scene/CoreUniformBuffers.h"
#include "Elysium/Scene/Components.h"
#include "Elysium/Scene/2DComponents.h"

#include "Elysium/Renderer/Renderer2D.h"

namespace Elysium
{
	Scene::Scene()
		: m_registry(CreateUnique<entt::registry>())
	{
		m_renderer2D = CreateUnique<Renderer2D>();
		m_renderer2D->Initialize();
	}

	Scene::~Scene()
	{
	}

	Elysium::Entity Scene::CreateEntity(const std::string& name)
	{
		// All entity have to have a transform and tag component
		Entity entity(m_registry->create(), this);

		// TODO::Implement fix for duplicate names
		entity.AddComponent<TagComponent>(!name.empty() ? name : "Entity");
		entity.AddComponent<UUIDComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_registry->destroy(entity);
	}

	void Scene::Computations()
	{
		CoreUniformBuffers::GetTimeDataRef().m_time = Time::TotalTime();
		CoreUniformBuffers::GetTimeDataRef().m_deltaTime = Time::DeltaTime();
	}

	void Scene::Draw(SceneMask mask)
	{
		switch (mask)
		{
			case _2D:
			{
				m_renderer2D->BeginScene();

				auto panelGroup = m_registry->group(entt::get<RectTransformComponent, SpriteComponent>);
				for (auto entity : panelGroup)
				{
					auto [transform, sprite] = panelGroup.get<RectTransformComponent, SpriteComponent>(entity);
					m_renderer2D->DrawSprite(transform, sprite);
				}

				m_renderer2D->EndScene();
				break;
			}
		}
	}

#pragma region OnComponentRemove

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		ELYSIUM_CORE_ASSERT(false, "Unknown behavior of Adding An Entity To An Entity");
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<UUIDComponent>(Entity entity, UUIDComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<RectTransformComponent>(Entity entity, RectTransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
	{
	}

#pragma endregion

#pragma region OnComponentRemove

	template<typename T>
	void OnComponentRemove(Entity entity, T& component)
	{
	}

	template<>
	void Scene::OnComponentRemove<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentRemove<UUIDComponent>(Entity entity, UUIDComponent& component)
	{
	}

	template<>
	void Scene::OnComponentRemove<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentRemove<RectTransformComponent>(Entity entity, RectTransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentRemove<SpriteComponent>(Entity entity, SpriteComponent& component)
	{
	}

#pragma endregion
}