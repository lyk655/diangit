cmake_minimum_required(VERSION 3.29)
project(diangit C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
add_subdirectory(zlib-1.3.1)
add_executable(diangit
        src/main.c
        src/command.c
        src/compress.c
        src/sha1.c
        src/step1.c
        src/step2.c
        src/step3.c
        src/step4.c
        src/step5.c
        src/step6.c
        src/tool.c
)

target_link_libraries(diangit PRIVATE zlib)