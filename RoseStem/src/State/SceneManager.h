#pragma once
#include "RoseRoot.h"

namespace RoseRoot {
	class SceneManager {
	public:
		static void NewScene(SceneHierarchyPanel* sceneHierarchyPanel);
		static void OpenScene(SceneHierarchyPanel* sceneHierarchyPanel);
		static void OpenScene(const std::filesystem::path& path, SceneHierarchyPanel* sceneHierarchyPanel);
		static void SaveSceneAs();
		static void SaveScene();
		static void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		static void OnScenePlay(SceneHierarchyPanel* sceneHierarchyPanel);
		static void OnSceneStop(SceneHierarchyPanel* sceneHierarchyPanel);
	private:
	};
}