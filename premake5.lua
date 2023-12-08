project "Core"
    kind "StaticLib"

    language "C++"
    cppdialect "C++17"
	
	files {
		"exception/**.h",

		"generic/**.h",
		"generic/**.cpp",

		"io/**.h",

		"math/**.h",

		"memory/**.h",
		"memory/**.cpp",

		"stb/**.h",
		"stb/**.cpp",
	}

    includedirs
	{
		"./",
	}