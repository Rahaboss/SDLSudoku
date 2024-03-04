workspace "SDLSudoku"
	architecture "x86_64" -- x86 for 32-bit
	configurations {
		"Debug", -- Regular debug build
		"Release", -- Build optimizations and debug information
		"Dist" -- Build optimizations and no debug information
	}

	startproject "SDLSudoku"
	targetdir "bin/%{cfg.buildcfg}"
	objdir "int/%{cfg.buildcfg}/%{prj.name}"

	filter "configurations:Debug"
		symbols "On" -- Enable debug symbols
		optimize "Off" -- Disable optimizations

	filter "configurations:Release"
		symbols "On"
		optimize "On" -- Enable optimizations

	filter "configurations:Dist"
		symbols "Off" -- Disable debug symbols
		optimize "Speed"
		defines {
			"NDEBUG"
		}

	project "SDLSudoku"
		kind "ConsoleApp" -- .exe with no console
		cppdialect "C++17"
		location "src" -- Project file location

		pchheader "pch.h"
		pchsource "src/pch.cpp" -- Must be defined relative to the script
		forceincludes "pch.h"

		-- Source files
		files {
			"src/**.h",
			"src/**.cpp"
		}

		-- .lib locations
		libdirs {
			"bin/lib/%{cfg.buildcfg}"
		}

		-- .lib links
		links {
			"SDL3"
		}

		-- Header include directories
		includedirs {
			"lib/SDLPremake/SDL/include",
			"lib/SDLPremake/SDL/src"
		}

		filter "configurations:Dist"
			kind "WindowedApp" -- Regular Windows .exe

	include "lib/SDLPremake"
