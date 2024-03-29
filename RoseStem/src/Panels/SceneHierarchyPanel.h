#pragma once
#include "RoseRoot/Core/Core.h"
#include "RoseRoot/Core/Assert.h"
#include "RoseRoot/Scene/Scene.h"
#include "RoseRoot/Scene/Entity.h"

namespace Rose {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);

		void SetAssetPath(std::filesystem::path path);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}