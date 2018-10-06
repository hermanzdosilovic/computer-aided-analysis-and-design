cmake_minimum_required( VERSION 3.12 )
project( caas LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

option( ENABLE_TRACE "Enable code trace." OFF )

add_library( caas INTERFACE )
target_include_directories( caas INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include )
if ( NOT ENABLE_TRACE )
    target_compile_definitions( caas INTERFACE NTRACE )
endif()

add_library( eigen INTERFACE )
target_include_directories( eigen INTERFACE ${CMAKE_CURRENT_LIST_DIR}/third_party/Eigen )

add_executable( test
    ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test/matrix_test.cpp
)
target_include_directories( test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/third_party/Catch2/single_include )
target_link_libraries( test PRIVATE caas eigen )

add_executable( h01t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_01/main.cpp )
target_link_libraries( h01t01 PRIVATE caas eigen )

add_executable( h01t02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_02/main.cpp )
target_link_libraries( h01t02 PRIVATE caas eigen )
