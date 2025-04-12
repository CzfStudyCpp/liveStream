cmake_minimum_required(VERSION 3.3)

# 项目名称
project(UserService)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

# 设置 hiredis 路径
set(HIREDIS_INCLUDE_DIR "/usr/include/hiredis")
set(HIREDIS_LIB_DIR "/usr/lib/x86_64-linux-gnu")

# 设置 ppconsul 路径
set(PPCONSUL_INCLUDE_DIR "/usr/local/include")
set(PPCONSUL_LIB_DIR "/usr/local/lib")

# 查找 OpenSSL 和 cpprestsdk 库
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

# 查找 libcurl 库，用于 HTTP 请求
find_package(CURL REQUIRED)

# 检查是否设置成功
message(STATUS "CURL include dir: ${CURL_INCLUDE_DIRS}")
message(STATUS "CURL libraries: ${CURL_LIBRARIES}")
message(STATUS "ppconsul include dir: ${PPCONSUL_INCLUDE_DIR}")
message(STATUS "ppconsul lib dir: ${PPCONSUL_LIB_DIR}")

# 查找 MySQL Connector 库
# 手动设置 MySQL 头文件和库文件路径
set(MySQL_INCLUDE_DIR "/usr/include/mysql")
set(MySQL_LIBRARIES "/usr/lib/x86_64-linux-gnu/libmysqlclient.so")

# 检查是否设置成功
message(STATUS "MySQL include dir: ${MySQL_INCLUDE_DIR}")
message(STATUS "MySQL libraries: ${MySQL_LIBRARIES}")
message(STATUS "hiredis include dir: ${HIREDIS_INCLUDE_DIR}")
message(STATUS "hiredis lib dir: ${HIREDIS_LIB_DIR}")

# 设置库路径
set(LIBRARY_PATHS
    /usr/local/lib
    ${HIREDIS_LIB_DIR}  # 添加 hiredis 库路径
	${PPCONSUL_LIB_DIR} # 添加 ppconsul 库路径
)

set(SERVER_SRC
    src/UserService.cpp
    src/sqlConnect.cpp
    src/user.cpp
	src/redisConnect.cpp
    # 添加其他源文件
)
set(REGISTER
     src/ServiceRegistrar.cpp
	 src/register.cpp
)
#add_subdirectory(src)
# 添加可执行文件
add_executable(user_service src/server.cpp ${PROTO_SRC} ${SERVER_SRC})
add_executable(httpServer src/httpServer.cpp src/controller.cpp ${PROTO_SRC})
add_executable(client src/client.cpp ${PROTO_SRC})
add_executable(register ${REGISTER})
# 设置头文件路径
target_include_directories(user_service PRIVATE ${PROTO_INCLUDE_PATHS} ${MySQL_INCLUDE_DIR} ${HIREDIS_INCLUDE_DIR})
target_include_directories(httpServer PRIVATE ${PROTO_INCLUDE_PATHS} )
target_include_directories(client PRIVATE ${PROTO_INCLUDE_PATHS}  )
target_include_directories(register PRIVATE ${PPCONSUL_INCLUDE_DIR})
# 设置库文件路径
target_link_directories(user_service PRIVATE ${LIBRARY_PATHS})
target_link_directories(httpServer PRIVATE ${LIBRARY_PATHS})
target_link_directories(client PRIVATE ${LIBRARY_PATHS})
target_link_directories(register PRIVATE ${LIBRARY_PATHS})  # 添加 register 的库文件路径


# 链接 Protobuf, gRPC, cpprestsdk, MySQL Connector 和 hiredis 库
target_link_libraries(user_service
    protobuf
    grpc++
    absl_synchronization
    pthread
    OpenSSL::Crypto
    OpenSSL::SSL
    cpprest
    ${MySQL_LIBRARIES}
    hiredis
)

target_link_libraries(httpServer
    protobuf
    grpc++
    absl_synchronization
    pthread
    OpenSSL::Crypto
    OpenSSL::SSL
    cpprest
    ${MySQL_LIBRARIES}
    hiredis
)

target_link_libraries(client
    protobuf
    grpc++
    absl_synchronization
    pthread
    OpenSSL::Crypto
    OpenSSL::SSL
    cpprest
    ${MySQL_LIBRARIES}
    hiredis
)

# 链接 register 到 libcurl
target_link_libraries(register 
    ${CURL_LIBRARIES}  
	ppconsul
)
# 安装时设置安装路径
install(TARGETS user_service DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS httpServer DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS client DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# 创建一个 "run" 目标，用于运行所有可执行文件
add_custom_target(run_all
    COMMAND ./user_service
    COMMAND ./client
    COMMAND ./httpServer
    DEPENDS user_service client httpServer
)
