project(game1 C CXX ASM)

add_executable(game1 
        main.cpp
        sprite.cpp
        collider.cpp
)

pico_set_program_name(game1 "game1")
pico_set_program_version(game1 "0.1")

pico_enable_stdio_uart(game1 0)
pico_enable_stdio_usb(game1 1)

target_link_libraries(game1
        pico_stdlib
        hardware_spi
        displaylib_16
)

target_include_directories(game1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ../displaylib_16bit_PICO/include)

pico_add_extra_outputs(game1)