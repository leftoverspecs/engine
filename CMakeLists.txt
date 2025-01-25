cmake_minimum_required(VERSION 3.30)
project(engine CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_net REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(protobuf REQUIRED CONFIG)
find_package(absl REQUIRED)

add_subdirectory(assets)

add_library(engine STATIC
    audio/audio.cpp
    audio/audio.hpp
    audio/chunk.cpp
    audio/chunk.hpp
    audio/initialize.cpp
    audio/initialize.hpp
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
    opengl/font.cpp
    opengl/font.hpp
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
    sdl/controller.hpp
    sdl/controller.cpp
    sdl/initialize.hpp
    sdl/initialize.cpp
    sdl/keyboard.hpp
    sdl/keyboard.cpp
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
    OpenGL::GL)
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

add_executable(sprite_test WIN32 examples/sprite_test.cpp examples/sprite_test.rc)
target_link_libraries(sprite_test PRIVATE engine SDL2::SDL2main)
target_assets(sprite_test PRIVATE examples/test_sprite.png)

add_executable(music_test WIN32 examples/music_test.cpp)
target_link_libraries(music_test PRIVATE engine SDL2::SDL2main)
target_assets(music_test PRIVATE examples/test_music.mp3 examples/blib.wav)

add_library(message STATIC examples/message.hpp examples/message.cpp)
protobuf_generate(TARGET message PROTOS examples/example.proto)
target_include_directories(message PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(message PUBLIC protobuf::libprotobuf absl::log_internal_check_op)

add_executable(test_server examples/test_server.cpp)
target_link_libraries(test_server PRIVATE engine message)

add_executable(test_client examples/test_client.cpp)
target_link_libraries(test_client PRIVATE engine message)
