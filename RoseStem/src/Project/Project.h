#pragma once
#include "RoseRoot/Scene/Scene.h"

namespace RoseRoot {
	

	class Project {
	public:
		Project();
		~Project();

		void SetPath(std::filesystem::path path) { m_Path = path; }
		std::filesystem::path GetPath() { return m_Path; }

		void SetSceneToIndex(int index, std::filesystem::path path) { m_ScenePaths.at(index) = path; }
		std::filesystem::path GetScenePathFromIndex(int index) { return m_ScenePaths.at(index); }
	private:
		//Absolute path of the project
		std::filesystem::path m_Path = "startup-project";

		//The relative path of all scenes in the build index
		std::unordered_map<int, std::filesystem::path> m_ScenePaths;
	};
}