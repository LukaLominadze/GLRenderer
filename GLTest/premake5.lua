project "GLTest"
	kind "ConsoleApp"
	staticruntime "off"

	language "C++"
	cppdialect "C++20"

	targetdir ("../bin/" ..outputdir.. "/%{prj.name}")
	objdir ("../bin-int/" ..outputdir.. "/%{prj.name}")

	defines { "GL_PLATFORM_WINDOWS", "_CONSOLE" }
	
	files {
		"src/**.h",
		"src/**.cpp"
	}

	vpaths {
		["Source Files"] = "src/**.cpp",
		["Header Files"] = "src/**.h",
		["Resource Files"] = { "src/res/textures/**.png",
							   "src/shaders/**.shader" }
	}

	includedirs { "src",
				  "../GLRenderer",
				  "../GLRenderer/src",
				  "../GLRenderer/src/vendor",
				  "../Dependencies/GLFW/include",
				  "../Dependencies/GLEW/include" }
	libdirs { "../Dependencies/GLFW/lib-vc2022",
			  "../Dependencies/GLEW/lib/Release/x64" }

	links { "glew32s.lib",
			"glfw3.lib",
			"opengl32.lib" }

	configurations {
		"Debug",
		"Release"
	}

	filter "system:windows"
		cppdialect "C++20"
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
		
		kind "WindowedApp"

		defines { "DISTRIBUTION" }

		architecture "x64"
		optimize "on"