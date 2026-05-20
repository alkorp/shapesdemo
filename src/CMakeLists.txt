file(GLOB_RECURSE SOURCES *.cpp)

add_executable(shapes ${SOURCES})

message("ADDED SRC")

target_compile_features(shapes PRIVATE cxx_std_17)
target_link_libraries(shapes PRIVATE SFML::Graphics)
target_include_directories(shapes PRIVATE ${CMAKE_BINARY_DIR}/include)
