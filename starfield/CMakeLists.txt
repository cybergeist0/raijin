project(starfield C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add display driver library
add_subdirectory(displaylib_16bit_PICO/library displaylib)

# Add executable
add_executable(starfield main.cpp)

pico_set_program_name(starfield "starfield")
pico_set_program_version(starfield "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(starfield 0)
pico_enable_stdio_usb(starfield 1)

# Add the standard library to the build
target_link_libraries(starfield
        pico_stdlib
        hardware_spi
        displaylib_16)

# Add the standard include files to the build
target_include_directories(starfield PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        displaylib_16bit_PICO/include)

pico_add_extra_outputs(starfield)