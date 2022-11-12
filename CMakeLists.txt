cmake_minimum_required(VERSION 3.10)
project(
    MetalStudy
    VERSION 0.0.1
    LANGUAGES CXX
)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

add_executable(
    MetalStudy
    main.cpp
    CocoaWindow.cpp
    NSWindow.cpp
    NSView.cpp
    CAMetalLayer.cpp
)
target_compile_definitions(
    MetalStudy
    PRIVATE
    $<$<CONFIG:Release>:MetalStudy_NDEBUG>
    $<$<CONFIG:Debug>:MetalStudy_DEBUG _DEBUG>
)
target_compile_options(
    MetalStudy
    PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g -Wall -Werror -fsanitize=address>
)
target_link_options(
    MetalStudy
    PRIVATE
    $<$<CONFIG:Release>:>
    $<$<CONFIG:Debug>: -fsanitize=address>
)
target_compile_features(MetalStudy PRIVATE cxx_std_17)

target_include_directories(
    MetalStudy
    PRIVATE
    #${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
)

target_link_libraries(
    MetalStudy
    PRIVATE
    #${OPENGL_LIBRARIES}
    "-framework Cocoa"
    "-framework Foundation"
    "-framework Metal"
    "-framework QuartzCore"
    ${GLFW_LIBRARIES}
)