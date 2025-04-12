# 用户模块 (User Service)

## 项目目标

本项目的目标是实现一个高效且可扩展的流媒体推送系统，支持 **RTMP** 和 **HLS** 协议。用户模块作为系统中的一个核心部分，负责处理用户信息管理、用户认证和会话管理等功能。

目前，包括：
- 用户查询
- 手机验证码登录
- 生成登录 Token
- 发送短信验证码
- 实现直播推流和分发
- 实现服务注册与发现

同时，通过 **gRPC** 作为服务之间的通信框架，使用 **C++ REST SDK** 处理外部 HTTP 请求，已成功实现与 gRPC 服务的交互。

## 当前成果

- **用户模块（User Service）** 已完成实现：
  - 提供查询用户信息、短信验证码发送、手机登录、生成登录 Token 等功能。
  - 使用 **gRPC** 实现服务间通信。
  - 使用 **C++ REST SDK** 实现 HTTP 接口与前端交互。

- **nginx** rtmp模块代理已完成，作为直播服务器代理
  使用rtmp模块进行推流 ，并转码为hls
  使用ffmpeg进行视频的转码，适应不同带宽情况

- **集成consul**
  注册运行服务实例
  提供服务发现

- **系统架构：**
  - 服务端使用 **gRPC** 进行高效的服务间通信。
  - 控制器层处理 HTTP 请求，将请求转化为相应的 gRPC 服务调用。

- **实现细节：**
  - 已实现用户信息查询，支持查询用户的昵称、头像等基本信息。
  - 支持基于手机号码的验证码登录，并生成唯一的登录 Token。
  - 使用 **protobuf** 定义了用户模块的 API 接口。



## 如何运行

### 1. 编译和安装

- **依赖项**：
  - gRPC 和 Protobuf
  - C++ REST SDK
  - OpenSSL（用于加密通信）
  - absl 库
  - libcur
  - MySQL dev
  - hiredis
  - consul
  - ppconsul
  - 

- **步骤**：
  1. 下载并安装 [gRPC](https://grpc.io/) 。
  2. 安装 **C++ REST SDK** ， **absl**，**protobuf** ,absl和protobuf在grpc的第三方库里直接编译即可，单独下载安装版本有可能不适配，造成编译运行时的错误。
  4. 其他库也一并进行安装，最好使用cmake的方式进行安装，这样方便进行库的管理
  5. 在项目根目录下运行以下命令来构建项目：

     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```

### 2. 启动服务器

- 启动 **gRPC** 服务端和 **HTTP** 服务端：

  ```bash
  ./server
  ./httpServer
  ./client  client模拟前端客户向客户端发起http请求，然后客户端向gRPC服务器转发请求数据
  ./liveStream 进行转码
  ```

### 3. 测试接口

#### 查询用户信息： 使用 POST 请求访问 http://localhost:8080/user/queryUser，传入 JSON 请求体：

```json
{
  "user_id": 123
}
返回的响应将包含用户信息，如昵称和头像等。
```

##### 发送短信验证码： 使用 POST 请求访问 http://localhost:8080/user/sendSMS，传入 JSON 请求体：

```json

{
  "mobile": "1234567890"
}
返回的响应表示短信是否发送成功。
```

##### 手机验证码登录： 使用 POST 请求访问 http://localhost:8080/user/mobileLogin，传入手机号码和验证码：

```json
{
  "mobile": "1234567890",
  "code": 1234
}
如果验证码正确，将返回一个包含登录状态和 Token 的响应。

```

##### 生成登录 Token： 使用 POST 请求访问 http://localhost:8080/user/createLoginToken，传入用户 ID：

```json
{
  "user_id": 123
}
返回的响应将包含生成的登录 Token。

```

### 4、依赖项

C++ REST SDK - 用于处理 HTTP 请求和响应。

gRPC 和 Protobuf - 用于微服务间的高效通信。

OpenSSL - 用于安全通信。

absl - 提供高效的库和工具支持。


