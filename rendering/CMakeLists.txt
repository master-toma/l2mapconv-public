cmake_minimum_required(VERSION 3.22)
project(rendering)

add_library(${PROJECT_NAME}
    src/pch.cpp

    src/VertexBuffer.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Camera.cpp
    src/Texture.cpp
    src/TextureLoader.cpp

    src/EntityMesh.cpp
    src/EntityShader.cpp
    src/Entity.cpp
    src/EntityRenderer.cpp

    src/Scene.cpp

    src/GeodataMesh.cpp

    src/ShaderLoader.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)

target_link_libraries(${PROJECT_NAME}
    PRIVATE utils
    PRIVATE geometry

    PRIVATE libglew_static
    PRIVATE glm
    PRIVATE stb
)

# Compiler settings
set_target_properties(${PROJECT_NAME} PROPERTIES ${TARGET_PROPERTIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${TARGET_COMPILE_OPTIONS})
