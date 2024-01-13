# ~ LibMath
cmake_minimum_required(VERSION 3.24 FATAL_ERROR) # PATH_EQUAL

option(LIB_MATH_UNIT_TEST "" ON)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_CURRENT_SOURCE_DIR} PATH_EQUAL ${CMAKE_SOURCE_DIR})
	# Create project if build directly
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	project(${PROJECT_NAME} LANGUAGES CXX)
else()
	# Put all target a folder if build from add_subdirectory()
	set(CMAKE_FOLDER ${PROJECT_NAME})
endif()

add_subdirectory(LibMath)

if (${LIB_MATH_UNIT_TEST})
	add_subdirectory(UnitTest)

	if(MSVC)
		set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UnitTest)
	endif()
endif()