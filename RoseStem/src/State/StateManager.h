#pragma once
#include "RoseRoot.h"
#include "../Panels/ContentBrowserPanel.h"
#include "../Panels/SceneHierarchyPanel.h"

namespace RoseRoot {
	enum class SceneState
	{
		Edit = 0, Play = 1
	};

	struct StateManager {
		Ref<Project> Project;

		Ref<Scene> ActiveScene;
		Ref<Scene> EditorScene;

		std::filesystem::path EditorScenePath;

		SceneState SceneState = SceneState::Edit;

		//TODO Move
		glm::vec2 ViewportSize = { 0.0f, 0.0f };
		
		//TODO Remove (storing twice.)
		std::string SceneName = "Untitled";
		glm::vec2 Gravity = { 0.0, -9.8 };
	};

	static StateManager g_State;
}