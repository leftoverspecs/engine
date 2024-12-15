cmake_minimum_required(VERSION 3.30)
project(engine CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_net REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED CONFIG)
find_package(OpenGL REQUIRED)

add_subdirectory(assets)

add_library(engine STATIC
    audio/audio.cpp
    audio/audio.hpp
    audio/chunk.cpp
    audio/chunk.hpp
    audio/music.cpp
    audio/music.hpp
    audio/wave.cpp
    audio/wave.hpp
    graphics/image.cpp
    graphics/image.hpp
    networking/client.hpp
    networking/client.cpp
    networking/primitives.hpp
    networking/server.hpp
    networking/server.cpp
    networking/transmit.hpp
    networking/transmit.cpp
    networking/initialize.hpp
    networking/initialize.cpp
    opengl/box.cpp
    opengl/box.hpp
    opengl/buffer.cpp
    opengl/buffer.hpp
    opengl/destination.cpp
    opengl/destination.hpp
    opengl/framebuffer.cpp
    opengl/framebuffer.hpp
    opengl/program.cpp
    opengl/program.hpp
    opengl/renderbuffer.cpp
    opengl/renderbuffer.hpp
    opengl/shader.cpp
    opengl/shader.hpp
    opengl/spritemap.cpp
    opengl/spritemap.hpp
    opengl/spriterenderer.cpp
    opengl/spriterenderer.hpp
    opengl/texture.cpp
    opengl/texture.hpp
    opengl/vertexarray.cpp
    opengl/vertexarray.hpp
    sdl/initialize.hpp
    sdl/initialize.cpp
    sdl/openglwindow.cpp
    sdl/openglwindow.hpp
    sdl/scene.cpp
    sdl/scene.hpp
    sdl/surface.cpp
    sdl/surface.hpp
    sdl/window.cpp
    sdl/window.hpp
)
target_link_libraries(engine PUBLIC
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_net::SDL2_net
    GLEW::glew
    OpenGL::GL
    glm::glm)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_assets(engine PRIVATE
    opengl/box.frag
    opengl/box.vert
    opengl/destination.frag
    opengl/destination.vert
    opengl/sprite.frag
    opengl/sprite.vert
)

add_executable(sprite_test examples/sprite_test.cpp)
target_link_libraries(sprite_test PRIVATE engine)
target_assets(sprite_test PRIVATE examples/test_sprite.png)

add_executable(music_test examples/music_test.cpp)
target_link_libraries(music_test PRIVATE engine)
target_assets(music_test PRIVATE examples/test_music.mp3)
target_assets(music_test PRIVATE examples/blib.wav)
