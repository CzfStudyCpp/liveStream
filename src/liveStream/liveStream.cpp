#include <iostream>
#include <thread>
#include "StreamManager.h"

int main()
{
    
    std::string input_stream = "rtmp://192.168.31.128/hls/888";
    std::string output_dir = "/usr/local/nginx/html/hls";

    // stream_key 是由推流客户端传入的
    std::string stream_key = "888"; 

    StreamManager stream_manager(input_stream, output_dir);
    stream_manager.start_transcoding(stream_key);

    // 继续执行其他操作
    std::cout << "Transcoding started for stream key: " << stream_key << std::endl;

    // 模拟延迟
    std::this_thread::sleep_for(std::chrono::hours(1));

    return 0;
}

