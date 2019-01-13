cmake_minimum_required( VERSION 3.12 )
project( caas LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

option( ENABLE_TRACE "Enable code trace." OFF )
option( ENABLE_COLORED_LOG "Enable colored log." OFF )

add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/third_party/ecfcpp )

add_library( caas INTERFACE )
target_link_libraries( caas INTERFACE ecfcpp m )
target_include_directories( caas INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include )
if ( NOT ENABLE_TRACE )
    target_compile_definitions( caas INTERFACE NTRACE )
endif()
if ( ENABLE_COLORED_LOG )
    target_compile_definitions( caas INTERFACE COLORED_LOG )
endif()

add_executable( hw01t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_01/main.cpp )
target_link_libraries( hw01t01 PRIVATE caas )

add_executable( hw01t02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_02/main.cpp )
target_link_libraries( hw01t02 PRIVATE caas )

add_executable( hw01t03 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_03/main.cpp )
target_link_libraries( hw01t03 PRIVATE caas )

add_executable( hw01t04 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_04/main.cpp )
target_link_libraries( hw01t04 PRIVATE caas )

add_executable( hw01t05 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_05/main.cpp )
target_link_libraries( hw01t05 PRIVATE caas )

add_executable( hw01t06 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_06/main.cpp )
target_link_libraries( hw01t06 PRIVATE caas )


add_executable( hw02t01golden ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_01/golden.cpp )
target_link_libraries( hw02t01golden PRIVATE caas )

add_executable( hw02t01axis ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_01/axis.cpp )
target_link_libraries( hw02t01axis PRIVATE caas )

add_executable( hw02t01simplex ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_01/simplex.cpp )
target_link_libraries( hw02t01simplex PRIVATE caas )

add_executable( hw02t01hooke_jeeves ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_01/hooke_jeeves.cpp )
target_link_libraries( hw02t01hooke_jeeves PRIVATE caas )

add_executable( hw02t02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_02/main.cpp )
target_link_libraries( hw02t02 PRIVATE caas )

add_executable( hw02t03 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_03/main.cpp )
target_link_libraries( hw02t03 PRIVATE caas )

add_executable( hw02t04 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_04/main.cpp )
target_link_libraries( hw02t04 PRIVATE caas )

add_executable( hw02t05 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_05/main.cpp )
target_link_libraries( hw02t05 PRIVATE caas )


add_executable( hw04t01f1_decimal ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f1_decimal.cpp )
target_link_libraries( hw04t01f1_decimal PRIVATE caas )

add_executable( hw04t01f3_decimal ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f3_decimal.cpp )
target_link_libraries( hw04t01f3_decimal PRIVATE caas )

add_executable( hw04t01f6_decimal ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f6_decimal.cpp )
target_link_libraries( hw04t01f6_decimal PRIVATE caas )

add_executable( hw04t01f7_decimal ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f7_decimal.cpp )
target_link_libraries( hw04t01f7_decimal PRIVATE caas )

add_executable( hw04t01f1_binary ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f1_binary.cpp )
target_link_libraries( hw04t01f1_binary PRIVATE caas )

add_executable( hw04t01f3_binary ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f3_binary.cpp )
target_link_libraries( hw04t01f3_binary PRIVATE caas )

add_executable( hw04t01f6_binary ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f6_binary.cpp )
target_link_libraries( hw04t01f6_binary PRIVATE caas )

add_executable( hw04t01f7_binary ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_01/f7_binary.cpp )
target_link_libraries( hw04t01f7_binary PRIVATE caas )

add_executable( hw04t02f6_decimal ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_02/f6_decimal.cpp )
target_link_libraries( hw04t02f6_decimal PRIVATE caas )

add_executable( hw04t02f7_decimal ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_02/f7_decimal.cpp )
target_link_libraries( hw04t02f7_decimal PRIVATE caas )

add_executable( hw04t03f6 ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_03/f6.cpp )
target_link_libraries( hw04t03f6 PRIVATE caas )

add_executable( hw04t03f7 ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_03/f7.cpp )
target_link_libraries( hw04t03f7 PRIVATE caas )

add_executable( hw04t04 ${CMAKE_CURRENT_LIST_DIR}/src/homework_04/task_04/main.cpp )
target_link_libraries( hw04t04 PRIVATE caas )


add_executable( hw05t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_05/task_01/main.cpp )
target_link_libraries( hw05t01 PRIVATE caas )

add_executable( hw05t02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_05/task_02/main.cpp )
target_link_libraries( hw05t02 PRIVATE caas )

add_executable( hw05t03trapeze ${CMAKE_CURRENT_LIST_DIR}/src/homework_05/task_03/trapeze.cpp )
target_link_libraries( hw05t03trapeze PRIVATE caas )
target_include_directories( hw05t03trapeze PRIVATE ${CMAKE_CURRENT_LIST_DIR}/third_party/sciplot )
