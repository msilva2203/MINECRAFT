workspace "Minecraft"
    architecture "x32"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Minecraft"
    location "Minecraft"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/Source/Vendor",
        "%{prj.name}/Source/Public",
        "Dependencies/GLEW/include",
        "Dependencies/GLFW/include"
    }

    libdirs
    {
        "Dependencies/GLFW/lib-vc2019",
        "Dependencies/GLEW/lib/Release/Win32"
    }

    links
    {
        "opengl32",
        "glfw3",
        "glew32s",
        "kernel32",
        "user32",
        "gdi32",
        "winspool",
        "comdlg32",
        "advapi32",
        "shell32",
        "ole32",
        "oleaut32",
        "uuid",
        "odbc32",
        "odbccp32"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "MINECRAFT_PLATFORM_WINDOWS",
            "GLEW_STATIC",
            "WIN32"
        }

    filter "configurations:Debug"
        defines "MINECRAFT_CONFIG_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "MINECRAFT_CONFIG_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        defines "MINECRAFT_CONFIG_DIST"
        runtime "Release"
        optimize "On"
        