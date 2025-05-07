-- premake5.lua
workspace "httpServer"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "server"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "server"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   toolset "clang"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",
      "include",
      "bin"
   }

   targetdir ("./Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("./Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   defines { }
   libdirs {"lib"}

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"       
       links{
            
        }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       links{
        
    }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       links{
        
    }