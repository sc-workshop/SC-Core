require("cmake")

project "Core"
    kind "StaticLib"

    language "C++"
    cppdialect "C++17"
	
	files {
		"source/**.cpp",
		"include/**.h"
	}

    includedirs
	{
		"./",
	}