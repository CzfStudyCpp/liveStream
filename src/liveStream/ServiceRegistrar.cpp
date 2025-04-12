#include "ServiceRegistrar.h"
#include <iostream>
#include <sstream>
#include <curl/curl.h>

ServiceRegistrar::ServiceRegistrar(const std::string &service_name, const std::string &service_id, 
                                   const std::string &service_address, int port)
    : service_name_(service_name), service_id_(service_id), service_address_(service_address), port_(port) {}

bool ServiceRegistrar::send_http_request(const std::string &url, const std::string &data) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_global_cleanup();
            return false;
        }
    }

    curl_global_cleanup();
    return true;
}

bool ServiceRegistrar::register_service() {
    std::ostringstream json_data;
    json_data << "{"
              << "\"ID\": \"" << service_id_ << "\","
              << "\"Name\": \"" << service_name_ << "\","
              << "\"Address\": \"" << service_address_ << "\","
              << "\"Port\": " << port_
              << "}";

    return send_http_request(consul_url_, json_data.str());
}

bool ServiceRegistrar::deregister_service() {
    return send_http_request(deregister_url_ + service_id_, "");
}
