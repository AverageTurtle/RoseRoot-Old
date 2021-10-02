#pragma once

#include "entt.hpp"


#include "RoseRoot/Core/Timestep.h"

namespace RoseRoot {

	class Scene {
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		//temp
		entt::registry& Reg() { return m_Registry; };

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;
	};
}