#include "rrpch.h"
#include "Project.h"

#include <yaml-cpp/yaml.h>

namespace RoseRoot {
	Project::Project(std::filesystem::path path)
		: m_Path(path)
	{
		std::filesystem::create_directory(m_Path);
		std::filesystem::path assetPath = m_Path / "assets";
		std::filesystem::create_directory(assetPath);

		bool couldLoad = false;
		for (auto& directoryEntry : std::filesystem::directory_iterator(m_Path))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, m_Path);
			std::string filenameString = relativePath.filename().string();

			size_t LastDot = filenameString.find_last_of(".");

			if (LastDot != std::string::npos) {
				if (filenameString.substr(LastDot) == ".rproj") {
					if(OpenProject(path))
						couldLoad = true;
				}
			}
		}
		if (!couldLoad)
			SaveProject();
	}

	Project::~Project()
	{
	}

	void Project::SaveProject()
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Project" << YAML::Value << "UntitledProject";
		out << YAML::Key << "Path" << YAML::Value << m_Path.string();
		out << YAML::EndMap;

		std::ofstream fout(m_Path / "UntitledProject.rproj");
		fout << out.c_str();
	}
	bool Project::OpenProject(std::filesystem::path path)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(path.string());
		}
		catch (YAML::ParserException e)
		{
			return false;
		}

		if (!data["Project"])
			return false;

		std::string projectName = data["Project"].as<std::string>();
		RR_CORE_TRACE("Deserializing project '{0}'", projectName);

		m_Path = path.parent_path();
	}
}