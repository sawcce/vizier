cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17" )

project(vizier VERSION 0.1.0)

add_executable(vizier main.cpp)

# find libraries
find_package(LLVM REQUIRED CONFIG)
find_package(fmt  REQUIRED CONFIG)

add_subdirectory(lexer)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${LLVM_INCLUDE_DIRS}
        ${FMT_INCLUDE_DIRS}
        lexer
)

add_definitions(${LLVM_DEFINITIONS} ${FMT_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs
     Analysis
     Core
     ExecutionEngine
     InstCombine
     Object
     OrcJIT
     RuntimeDyld
     ScalarOpts
     Support
     native
)

#target_link_directories(${PROJECT_NAME}
#        PRIVATE external/lexy/src
#        PRIVATE lexer
#)

target_link_libraries(${PROJECT_NAME}
    ${llvm_libs}
    fmt::fmt
    lexer
)