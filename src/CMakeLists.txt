cmake_minimum_required(VERSION 3.3)

# 项目名称
project(LiveStreamTranscoding)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# 设置头文件路径
set(PROTO_INCLUDE_PATHS
    /usr/local/include/google   # Protobuf 头文件路径
    /usr/local/include/grpcpp   # gRPC 头文件路径
)

# 查找 OpenSSL 和 cpprestsdk 库
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

# 设置库路径
set(LIBRARY_PATHS
    /usr/local/lib
)

# 添加源文件
set(SOURCE_FILES
    liveStream/liveStream.cpp            # 主程序文件
    liveStream/StreamManager.cpp   # 转码管理类文件
)

# 添加可执行文件
add_executable(liveStreamTranscoding ${SOURCE_FILES})

# 设置头文件路径
target_include_directories(liveStreamTranscoding PRIVATE ${PROTO_INCLUDE_PATHS})

# 设置库文件路径
target_link_directories(liveStreamTranscoding PRIVATE ${LIBRARY_PATHS})

# 链接必要的库（如OpenSSL, cpprestsdk等）
target_link_libraries(liveStreamTranscoding
    OpenSSL::Crypto
    OpenSSL::SSL
    cpprest
    pthread
)

# 安装时设置安装路径
install(TARGETS liveStreamTranscoding DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# 创建一个 "run" 目标，用于运行可执行文件
add_custom_target(run
    COMMAND ./liveStreamTranscoding
    DEPENDS liveStreamTranscoding
)

