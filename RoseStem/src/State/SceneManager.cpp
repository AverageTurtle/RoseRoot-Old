#include "SceneManager.h"
#include "StateManager.h"

#include "RoseRoot/Scene/SceneSerializer.h"
#include "RoseRoot/Utils/PlatformUtils.h"
#include "RoseRoot/Math/Math.h"

namespace RoseRoot {
	void SceneManager::NewScene(SceneHierarchyPanel* sceneHierarchyPanel)
	{
		g_State.ActiveScene = CreateRef<Scene>();
		g_State.ActiveScene->OnViewportResize((uint32_t)g_State.ViewportSize.x, (uint32_t)g_State.ViewportSize.y);
		sceneHierarchyPanel->SetContext(g_State.ActiveScene);
		g_State.Gravity = g_State.ActiveScene->GetGravity2D();

		g_State.EditorScene = g_State.ActiveScene;
		g_State.EditorScenePath = std::filesystem::path();
	}

	void SceneManager::OpenScene(SceneHierarchyPanel* sceneHierarchyPanel)
	{
		std::string filepath = FileDialogs::OpenFile("Rose Scene (*.rose)\0*.rose\0");
		if (!filepath.empty())
			OpenScene(filepath, sceneHierarchyPanel);
	}

	void SceneManager::OpenScene(const std::filesystem::path& path, SceneHierarchyPanel* sceneHierarchyPanel)
	{
		if (g_State.SceneState != SceneState::Edit)
			OnSceneStop(sceneHierarchyPanel);
		if (path.extension().string() != ".rose")
		{
			RR_WARN("Could not load {0} - not a scene file", path.filename().string());
			return;
		}

		Ref<Scene> newScene = CreateRef<Scene>();
		SceneSerializer serializer(newScene);
		if (serializer.Deserialize(path.string()))
		{
			g_State.EditorScene = newScene;
			g_State.EditorScene->OnViewportResize((uint32_t)g_State.ViewportSize.x, (uint32_t)g_State.ViewportSize.y);
			g_State.SceneName = g_State.EditorScene->GetName();
			g_State.Gravity = g_State.EditorScene->GetGravity2D();
			sceneHierarchyPanel->SetContext(g_State.EditorScene);

			g_State.ActiveScene = g_State.EditorScene;
			g_State.EditorScenePath = path;
		}
	}

	void SceneManager::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Rose Scene (*.rose)\0*.rose\0");
		if (!filepath.empty())
		{
			SerializeScene(g_State.ActiveScene, filepath);
			g_State.EditorScenePath = filepath;
		}
	}

	void SceneManager::SaveScene()
	{
		if (!g_State.EditorScenePath.empty())
			SerializeScene(g_State.ActiveScene, g_State.EditorScenePath);
		else
			SaveSceneAs();
	}
	void SceneManager::SerializeScene(Ref<Scene> scene, const std::filesystem::path& path)
	{
		if (g_State.SceneState != SceneState::Edit)
			return;

		SceneSerializer serializer(scene);
		serializer.Serialize(path.string());
	}

	void SceneManager::OnScenePlay(SceneHierarchyPanel* sceneHierarchyPanel)
	{
		g_State.ActiveScene = Scene::Copy(g_State.EditorScene);
		g_State.ActiveScene->OnRuntimeStart();

		sceneHierarchyPanel->SetContext(g_State.ActiveScene);
		g_State.SceneState = SceneState::Play;
	}

	void SceneManager::OnSceneStop(SceneHierarchyPanel* sceneHierarchyPanel)
	{
		g_State.ActiveScene->OnRuntimeStop();
		g_State.ActiveScene = g_State.EditorScene;

		sceneHierarchyPanel->SetContext(g_State.ActiveScene);
		g_State.SceneState = SceneState::Edit;
	}
}