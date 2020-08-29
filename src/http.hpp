#ifndef HTTP_HPP_INCLUDED
#define HTTP_HPP_INCLUDED

#include <iostream>
#include <list>
#include <string>
#include <curlpp/Options.hpp>

bool http_set_oauth_token(std::string token);
size_t http_write_callback(void * ptr, size_t size, size_t nmemb);

curlpp::options::WriteFunction * http_use_write_callback();
std::list<std::string> http_header_create();

std::string http_get(std::string url);
std::string http_post(std::string url, std::string data = "");
std::string http_put(std::string url, std::string data = "");
std::string http_post_http_response(std::string url, std::string data = "");

#endif // HTTP_HPP_INCLUDED
