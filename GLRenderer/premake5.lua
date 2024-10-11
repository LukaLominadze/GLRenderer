project "GLRenderer"
	kind "StaticLib"
	staticruntime "off"

	language "C++"
	cppdialect "C++20"

	targetdir ("../bin/" ..outputdir.. "/%{prj.name}")	
	objdir ("../bin-int/" ..outputdir.. "/%{prj.name}")

	defines { "GL_PLATFORM_WINDOWS", "GLEW_STATIC" }
	
	files {
		"**.h",
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
		"src/**.txt",
		"glpch.h",
		"glpch.cpp",
		"src/vendor/glm/**.hpp",
		"src/vendor/glm/**.inl"
	}

	vpaths {
		["Core"] = { "src/core/**.cpp", "src/core/**.h" },
		["Events"] = { "src/events/**.cpp", "src/events/**.h" },
		["GLCore"] = { "src/glcore/**.cpp", "src/glcore/**.h" },
		["Layers"] = { "src/layers/**.cpp", "src/layers/**.h" },
		["Utils"] = { "src/utils/**.cpp", "src/utils/**.h" },
		["Vendor"] = { "src/vendor/**.hpp", "src/vendor/**.h", "src/vendor/**.cpp" },
		["General"] = { "glpch.cpp", "glpch.h", "GLRenderer.h" }
	}

	removefiles { "src/vendor/glm/glm.cppm",
				  "src/vendor/imgui/main.cpp" }

	pchheader "glpch.h"
	pchsource "glpch.cpp"

	includedirs { "src",
				  "src/vendor",
				  "../Dependencies/GLFW/include",
				  "../Dependencies/GLEW/include" }
	libdirs { "../Dependencies/GLFW/lib-vc2022",
			  "../Dependencies/GLEW/lib/Release/x64" }

	links { "glew32s.lib",
			"glfw3.lib",
			"opengl32.lib", }

	configurations {
		"Debug",
		"Release"
	}

	filter "files:**/vendor/**.cpp"
        flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		
		defines { "_DEBUG" }
		
		architecture "x64"
		symbols "on"

	filter "configurations:Release"
		
		defines { "NDEBUG" }

		architecture "x64"
		optimize "on"
	
	filter "configurations:Distribution"

		defines { "DISTRIBUTION" }

		architecture "x64"
		optimize "on"