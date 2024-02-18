cmake_minimum_required(VERSION 3.24)
project(fakeout)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.c
	src/app.c
	src/draw.c
	src/player.c
	src/ball.c
	src/block.c
)

target_link_libraries(${CMAKE_PROJECT_NAME}
	SDL2::SDL2
	SDL2_image::SDL2_image
)
