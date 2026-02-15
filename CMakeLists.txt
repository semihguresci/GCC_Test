cmake_minimum_required(VERSION 3.20)
project(GCCTest VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)
target_sources(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
source_group("include" FILES ${HEADER_FILES})


include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.16.0 
)

FetchContent_MakeAvailable(googletest)


include(CTest)      
include(GoogleTest)  

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

function(create_test_executable test_name source_files)
    add_executable(${test_name} ${source_files})
    target_include_directories(${test_name} PRIVATE include)
    target_link_libraries(${test_name} PRIVATE gtest gtest_main) 
    add_test(NAME ${test_name} COMMAND ${test_name})
    gtest_discover_tests(${test_name}
        DISCOVERY_TIMEOUT 30
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endfunction()

set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${TESTS_DIR}/Test*.cpp")

foreach(test_src IN LISTS TEST_SOURCES)
    get_filename_component(test_name "${test_src}" NAME_WE)
    create_test_executable("${test_name}" "${test_src}")
endforeach()









