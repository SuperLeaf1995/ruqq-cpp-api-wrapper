#ifndef HTTP_HPP_INCLUDED
#define HTTP_HPP_INCLUDED

#include <iostream>
#include <string>

bool http_set_oauth_token(std::string token);
size_t http_write_callback(void * ptr, size_t size, size_t nmemb);
std::string http_get(std::string url);
std::string http_post(std::string url, std::string data = "");

#endif // HTTP_HPP_INCLUDED
