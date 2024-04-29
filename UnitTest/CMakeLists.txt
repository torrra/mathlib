# UnitTest CMake

# Write current directrory name into a variable to build executable
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Run Cmake for packages that will be fetched below
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY      https://github.com/catchorg/Catch2.git      # Fetch from github
    GIT_TAG             v3.5.4                                      # Fetch latest Catch2 release
    GIT_SHALLOW         ON                                          # Only allow branch name or tag as GIT_TAG argument
)

# Do not install documentation and extra files
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "Install Catch2 documentation" FORCE)
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "Install extra files" FORCE)

# Temporarily store current CMAKE_FOLDER value
set(TEMP ${CMAKE_FOLDER})

# Set new output folder to Catch2
set(CMAKE_FOLDER Catch2)

# Populate package into Catch2 and add it to the main build
FetchContent_MakeAvailable(Catch2)

# Restore CMAKE_FOLDER to its previous value
set(CMAKE_FOLDER ${TEMP})


# Fetch glm master branch (no git tag provided)
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_SHALLOW		ON
)

# Populate glm
FetchContent_MakeAvailable(glm)


# Gather files to build executable

# Headers
file(GLOB_RECURSE TARGET_HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

# Source files
file(GLOB_RECURSE TARGET_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++
)

# Documentation
file(GLOB_RECURSE TARGET_EXTRA_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
	${CMAKE_CURRENT_SOURCE_DIR}/*.md
)

# Create variable containing all relevant files
set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES} ${TARGET_EXTRA_FILES})

# Generate visual studio filters following
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

# Set include directory variable
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Header)

# Generate executable
add_executable(${TARGET_NAME})

# Add sources to executable, only visible to itself
target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE_FILES})

# Make necessary include directories visible to the executable
target_include_directories(${TARGET_NAME}
    PRIVATE ${TARGET_INCLUDE_DIR}
    PRIVATE ${LIBMATH_INCLUDE_DIR}
    PRIVATE ${glm_SOURCE_DIR}
)


# Link necessary static libs
target_link_libraries(${TARGET_NAME}
    PRIVATE ${LIBMATH_LIB}
    PRIVATE Catch2::Catch2
)

if (MSVC)

    # Raise warning level to level 4 and treat warnings as errors
    # /Za disables MSVC compiler extensions that aren't compatible with ISO C90
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX /Za)

    # TODO remove
    # Force disable LNK2019 unresolved external linker error
    target_link_options(${TARGET_NAME} PRIVATE /FORCE:UNRESOLVED)

elseif(LINUX)

    # Raise warning level to max and treat warnings as errors
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wshadow -Wextra -Wpedantic -Werror)

endif()
