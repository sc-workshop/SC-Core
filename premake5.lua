project "SupercellCore"
    kind "StaticLib"

    language "C++"
    cppdialect "C++17"
	
	files {
		"source/**.cpp"
	}

    includedirs
	{
		"include",
	}