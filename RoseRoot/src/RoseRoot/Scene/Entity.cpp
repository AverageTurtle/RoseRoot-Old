#include "rrpch.h"
#include "Entity.h"

namespace RoseRoot {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}
}