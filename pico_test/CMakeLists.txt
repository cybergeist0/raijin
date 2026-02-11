project(pico_test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(pico_test main.c )

pico_set_program_name(pico_test "pico_test")
pico_set_program_version(pico_test "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico_test 0)
pico_enable_stdio_usb(pico_test 1)

# Add the standard library to the build
target_link_libraries(pico_test
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(pico_test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(pico_test)