workspace "GLRenderer"
	configurations {
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	architecture "x64"

	startproject "GLTest"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GLRenderer"
	location "GLRenderer"
	kind "StaticLib"
	staticruntime "off"

	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")	
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	defines { "GL_PLATFORM_WINDOWS", "GLEW_STATIC" }
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.txt",
		"%{prj.name}/glpch.h",
		"%{prj.name}/glpch.cpp",
		"%{prj.name}/src/vendor/glm/**.hpp",
		"%{prj.name}/src/vendor/glm/**.inl"
	}

	vpaths {
		["Source Files"] = "%{prj.name}/src/**.cpp",
		["Header Files/*"] = { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp" }
	}

	removefiles { "%{prj.name}/src/vendor/glm/glm.cppm",
				  "%{prj.name}/src/vendor/imgui/main.cpp" }

	includedirs { "%{prj.name}",
				  "%{prj.name}/src",
				  "%{prj.name}/src/vendor",
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

project "GLTest"
	location "GLTest"
	kind "ConsoleApp"
	staticruntime "off"

	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	defines { "GL_PLATFORM_WINDOWS", "_CONSOLE" }
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	vpaths {
		["Source Files"] = "%{prj.name}/src/**.cpp",
		["Header Files"] = "%{prj.name}/src/**.h",
		["Resource Files"] = { "%{prj.name}/src/res/textures/**.png",
							   "%{prj.name}/src/shaders/**.shader" }
	}

	includedirs { "%{prj.name}/src",
				  "%{wks.location}/GLRenderer",
				  "%{wks.location}/GLRenderer/src",
				  "%{wks.location}/GLRenderer/src/vendor",
				  "%{wks.location}/Dependencies/GLFW/include",
				  "%{wks.location}/Dependencies/GLEW/include" }
	libdirs { "%{wks.location}/Dependencies/GLFW/lib-vc2022",
			  "%{wks.location}/Dependencies/GLEW/lib/Release/x64" }

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
