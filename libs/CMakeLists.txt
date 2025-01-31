# GLEW
option(glew-cmake_BUILD_SHARED "Build shared glew library" OFF)
set(glew-cmake_BUILD_SHARED OFF)
option(glew-cmake_BUILD_MULTI_CONTEXT "Build the multi-context glew library" OFF)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF)
add_subdirectory(glew)

# Recast
option(RECASTNAVIGATION_DEMO "Build demo" OFF)
set(RECASTNAVIGATION_DEMO OFF)
option(RECASTNAVIGATION_TESTS "Build tests" OFF)
set(RECASTNAVIGATION_TESTS OFF)
option(RECASTNAVIGATION_EXAMPLES "Build examples" OFF)
set(RECASTNAVIGATION_EXAMPLES OFF)
add_subdirectory(recast)

# Apply Recast patch
find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE} apply ${CMAKE_CURRENT_SOURCE_DIR}/patches/recast.patch
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/recast
)

# GLFW
option(GLFW_BUILD_DOCS "Build docs" OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

# Other libs
add_subdirectory(llvm)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(stb)
add_subdirectory(cxxopts)
