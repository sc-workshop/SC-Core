project "SupercellCore"
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

		"stb/**.h",
	}

    includedirs
	{
		"./",
	}