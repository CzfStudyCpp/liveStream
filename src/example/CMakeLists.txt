cmake_minimum_required(VERSION 3.3)

# 项目名称
project(UserService)

# 设置 Protobuf 和 gRPC 库和头文件路径
set(PROTOBUF_DIR "/usr/local")
set(GRPC_DIR "/usr/local")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁止编译器特有扩展

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# 添加生成的 Protobuf 和 gRPC 文件
set(PROTO_SRC
    src/user.pb.cc
    src/user.grpc.pb.cc
)

# 设置头文件路径
set(PROTO_INCLUDE_PATHS
    /usr/local/include/google   # Protobuf 头文件路径
    /usr/local/include/grpcpp   # gRPC 头文件路径
    /usr/local/include/absl     # absl 头文件路径
)

# 设置库路径
set(LIBRARY_PATHS
    /usr/local/lib
)

# 添加可执行文件
add_executable(user_service src/UserService.cpp ${PROTO_SRC})
add_executable(query_user src/QueryUser.cpp ${PROTO_SRC})

# 设置头文件路径
target_include_directories(user_service PRIVATE ${PROTO_INCLUDE_PATHS})
target_include_directories(query_user PRIVATE ${PROTO_INCLUDE_PATHS})

# 设置库文件路径
target_link_directories(user_service PRIVATE ${LIBRARY_PATHS})
target_link_directories(query_user PRIVATE ${LIBRARY_PATHS})

# 链接 Protobuf 和 gRPC 库
target_link_libraries(user_service
    protobuf
    grpc++
    absl_synchronization
    pthread
)

target_link_libraries(query_user
    protobuf
    grpc++
    absl_synchronization
    pthread
)

# 安装时设置安装路径
install(TARGETS user_service DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS query_user DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# 创建一个 "run" 目标，用于运行所有可执行文件
add_custom_target(run
    COMMAND ./user_service
    COMMAND ./query_user
    DEPENDS user_service query_user
)
