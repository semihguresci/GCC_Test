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

enable_testing()

function(create_test_executable test_name source_files)
    add_executable(${test_name} ${source_files})
    target_include_directories(${test_name} PRIVATE include)
    target_link_libraries(${test_name} PRIVATE gtest gtest_main) 
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

create_test_executable(TestMaxProduct tests/TestMaxProduct.cpp)
create_test_executable(TestUniquePathsWithObstacles tests/TestUniquePathsWithObstacles.cpp)
create_test_executable(TestDijkstraShortestPath tests/TestDijkstraShortestPath.cpp)
create_test_executable(TestBellmanFordShortestPath tests/TestBellmanFordShortestPath.cpp)
create_test_executable(TestSearchRotatedArray tests/TestSearchRotatedArray.cpp)
create_test_executable(TestValidateBTSInOrder tests/TestValidateBTSInOrder.cpp)
create_test_executable(TestNQueensProblem tests/TestNQueensProblem.cpp)
create_test_executable(TestGreedyAlgorithm tests/TestGreedyAlgorithm.cpp)
create_test_executable(TestRangesMap tests/TestRangesMap.cpp)
create_test_executable(TestValueRangeMap tests/TestValueRangeMap.cpp)
create_test_executable(TestSegmentMap tests/TestSegmentMap.cpp)
create_test_executable(TestMOsAlgorithm tests/TestMOsAlgorithm.cpp)
create_test_executable(TestPower tests/TestPower.cpp)
create_test_executable(TestFibonacci tests/TestFibonacci.cpp)
create_test_executable(TestPuzzle tests/TestPuzzle.cpp)
create_test_executable(TestDynamicProgramming tests/TestDynamicProgramming.cpp)
create_test_executable(TestBinarySearch tests/TestBinarySearch.cpp)








