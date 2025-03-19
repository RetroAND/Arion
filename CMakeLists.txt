# CMakeList.txt : CMake project for Arion, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (Arion LANGUAGES CXX)

include(FetchContent)

#add_subdirectory(dependencies/FloppyLib)
#add_subdirectory(dependencies/wxWidgets)

find_library(FloppyLib NAMES FloppyLib.dll PATHS dependencies/FloppyLib NO_SYSTEM_ENVIRONMENT_PATH)
include_directories(dependencies/FloppyLib/include)

# Add source to this project's executable.
add_executable (Arion "Arion.cpp" "commands.cpp")
target_link_libraries(Arion PRIVATE FloppyLib)

set(wxBUILD_SHARED OFF)

message(STATUS "Fetching wxWidgets...")

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

add_executable(arion_gui "arion_gui.cpp" "ArionApp.cpp" "ArionFrame.cpp" "DiskStatsPanel.cpp" "DiskVolumeInfoPanel.cpp" "SectorInfoPanel.cpp")
target_link_libraries(arion_gui PUBLIC FloppyLib wx::net wx::core wx::base)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Arion PROPERTY CXX_STANDARD 20)
  set_property(TARGET arion_gui PROPERTY CXX_STANDARD 20)
endif()