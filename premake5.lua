workspace "GLRenderer"
	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	architecture "x64"

	startproject "GLTest"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "GLRenderer"
include "GLTest"

