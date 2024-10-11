project "GLRenderer"
	kind "StaticLib"
	staticruntime "off"

	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")	
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

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
		["Source Files"] = "src/**.cpp",
		["Header Files/*"] = { "src/**.h", "src/**.hpp" }
	}

	removefiles { "src/vendor/glm/glm.cppm",
				  "src/vendor/imgui/main.cpp" }

	pchheader "glpch.h"
	pchsource "glpch.cpp"

	includedirs { "src",
				  "src/vendor",
				  "%{wks.location}/Dependencies/GLFW/include",
				  "%{wks.location}/Dependencies/GLEW/include" }
	libdirs { "%{wks.location}/Dependencies/GLFW/lib-vc2022",
			  "%{wks.location}/Dependencies/GLEW/lib/Release/x64" }

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