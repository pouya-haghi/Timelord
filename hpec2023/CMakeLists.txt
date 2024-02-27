cmake_minimum_required(VERSION 3.9.1)

project(timelord)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pedantic -lm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SOURCES src/main.cpp src/utils.cpp)
add_executable(app ${SOURCES})
target_include_directories(app PRIVATE include)



# TIMELORD Shared Object Library
set(TIMELORD_SRC src/pmpi_wrapper.cpp)
set(PREDICTOR_SRC src/pmpi_wrapper_predictor.cpp)

add_library(timelord_wrapper SHARED ${TIMELORD_SRC})
target_include_directories(timelord_wrapper PRIVATE include)



# OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(app PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(timelord_wrapper PUBLIC OpenMP::OpenMP_CXX)
endif()
        
# MPI
find_package(MPI REQUIRED)
target_link_libraries(app PUBLIC MPI::MPI_CXX)
target_link_libraries(timelord_wrapper PRIVATE MPI::MPI_CXX)

install(TARGETS timelord_wrapper
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

