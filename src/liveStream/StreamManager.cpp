#include "StreamManager.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <array>
#include <memory>
StreamManager::StreamManager(const std::string &input_stream, const std::string &output_dir)
    : input_stream_(input_stream), output_dir_(output_dir)
{
}

void StreamManager::start_transcoding(const std::string &stream_key)
{
    std::cout << "Starting transcoding for stream key: " << stream_key << std::endl;
    // 使用多线程处理每个推流密钥的转码
    std::thread transcoding_thread(&StreamManager::transcode_stream, this, stream_key);
    transcoding_thread.detach(); // 启动新的线程进行转码
}

void StreamManager::transcode_stream(const std::string &stream_key)
{
    // 定义不同分辨率和码率
    std::unordered_map<std::string, std::pair<std::string, std::string>> resolutions = {
        {"480p", {"854x480", "1500k"}},
        {"720p", {"1280x720", "2500k"}},
        {"1080p", {"1920x1080", "5000k"}}
    };

    for (const auto &resolution : resolutions)
    {
        std::string resolution_name = resolution.first;
        std::string size = resolution.second.first;
        std::string bitrate = resolution.second.second;

        // 执行 FFmpeg 转码
        std::string command = "ffmpeg -i " + input_stream_ + " -c:v libx264 -preset fast -b:v " + bitrate +
                              " -s " + size + " -c:a aac -b:a 128k -f hls -hls_time 4 -hls_list_size 0 " +
                              "-hls_segment_filename " + output_dir_ + "/" + stream_key + "_" + resolution_name + "_%03d.ts " +
                              output_dir_ + "/" + stream_key + "_" + resolution_name + ".m3u8";
        run_command(command);
    }
}

bool StreamManager::run_command(const std::string &command)
{
    std::array<char, 128> buffer;
    std::string result;

    // 使用自定义删除器来关闭文件流
    auto pipe = std::shared_ptr<FILE>(popen(command.c_str(), "r"), [](FILE *f) { if (f) pclose(f); });

    if (!pipe)
    {
        return false;
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return !result.empty();
}
