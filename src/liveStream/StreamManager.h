#ifndef STREAM_MANAGER_H
#define STREAM_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <thread>

class StreamManager
{
public:
    // 构造函数：输入流和输出目录
    StreamManager(const std::string &input_stream, const std::string &output_dir);

    // 启动转码
    void start_transcoding(const std::string &stream_key);

private:
    // 转码每个流
    void transcode_stream(const std::string &stream_key);

    // 执行命令
    bool run_command(const std::string &command);

private:
    std::string input_stream_; // 输入流地址
    std::string output_dir_;   // 输出目录
};

#endif // STREAM_MANAGER_H

