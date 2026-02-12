project(graph C CXX ASM)

add_executable(graph main.cpp)

pico_set_program_name(graph "graph")
pico_set_program_version(graph "0.1")

pico_enable_stdio_uart(graph 0)
pico_enable_stdio_usb(graph 1)

target_link_libraries(graph
        pico_stdlib
        hardware_spi
        displaylib_16
)

target_include_directories(graph PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ../displaylib_16bit_PICO/include)

pico_add_extra_outputs(graph)