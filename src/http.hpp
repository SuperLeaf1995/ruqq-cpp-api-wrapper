#ifndef HTTP_HPP_INCLUDED
#define HTTP_HPP_INCLUDED

#include <iostream>
#include <string>

size_t http_write_callback(void * ptr, size_t size, size_t nmemb);
std::string http_get(std::string url);
std::string http_post(std::string url);

#endif // HTTP_HPP_INCLUDED
