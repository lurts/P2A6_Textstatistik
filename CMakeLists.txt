# CMakeList.txt : CMake project for P2A6_Textstatistik, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_definitions(-DPROJECT_DIR="${CMAKE_SOURCE_DIR}")


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("P2A6_Textstatistik")

# Add source to this project's executable.
add_executable (P2A6_Textstatistik		"main.cpp" 
										"textstatistik.h" "textstatistik.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET P2A6_Textstatistik PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
