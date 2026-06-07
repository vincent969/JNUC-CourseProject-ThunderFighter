cmake_minimum_required(VERSION 3.10)
project(ThunderFighter LANGUAGES CXX)

# ========== C++11 标准 ==========
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========== 收集所有源文件 ==========
file(GLOB SOURCES "src/*.cpp")

# ========== 生成可执行文件 ==========
add_executable(flyfight ${SOURCES})

# ========== 头文件路径 ==========
target_include_directories(flyfight PRIVATE include)

# ========== UTF-8 编译（解决中文乱码）==========
target_compile_options(flyfight PRIVATE
    -finput-charset=UTF-8
    -fexec-charset=UTF-8
)

# ========== Windows 控制台程序（不弹 GUI 窗口）==========
if(WIN32)
    set_target_properties(flyfight PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()
