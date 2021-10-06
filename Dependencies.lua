
-- RoseRoot Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/RoseRoot/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/RoseRoot/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/RoseRoot/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/RoseRoot/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/RoseRoot/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/RoseRoot/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/RoseRoot/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/RoseRoot/vendor/entt/include"
IncludeDir["shaderc"] = "%{wks.location}/RoseRoot/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/RoseRoot/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/RoseRoot/vendor/VulkanSDK/Lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/RoseRoot/vendor/VulkanSDK/Bin"


Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"