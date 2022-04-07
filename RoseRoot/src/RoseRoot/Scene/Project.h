#pragma once
#include "RoseRoot/Scene/Scene.h"

namespace RoseRoot {
	

	class Project {
	public:
		Project(std::filesystem::path path = "startup-project");
		~Project();
		
		std::filesystem::path GetPath() { return m_Path; }
		std::filesystem::path GetAssetPath() { std::filesystem::path path = m_Path / "assets"; return path; }

		void SetSceneToIndex(int index, std::filesystem::path path) { m_ScenePaths.at(index) = path; }
		std::filesystem::path GetScenePathFromIndex(int index) { return m_ScenePaths.at(index); }

		void SaveProject();
		bool OpenProject(std::filesystem::path path);
	private:
		//Absolute path of the project
		std::filesystem::path m_Path;

		//The relative path of all scenes in the build index
		std::unordered_map<int, std::filesystem::path> m_ScenePaths;
	};
}