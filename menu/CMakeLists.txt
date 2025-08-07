cmake_minimum_required(VERSION 3.10)
project(MenuProject)

# 设置C标准
set(CMAKE_C_STANDARD 23)

# 添加头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/MyMenu
    ${CMAKE_SOURCE_DIR}/multilevel_menu
    ${CMAKE_SOURCE_DIR}/main
)

# 检查编译器类型并设置适当的UTF-8标志
if(MSVC)
    # Visual Studio编译器
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # GCC编译器
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # Clang编译器
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")
endif()


# 收集所有源文件
set(SOURCES
    MyMenu/MyMenu.c
    multilevel_menu/Menu.c
    main/main.c
)

# 创建可执行文件
add_executable(menu ${SOURCES})
