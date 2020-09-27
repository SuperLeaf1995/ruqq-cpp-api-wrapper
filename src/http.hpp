#ifndef HTTP_HPP_INCLUDED
#define HTTP_HPP_INCLUDED

#include <iostream>
#include <list>
#include <string>
#include <curlpp/Options.hpp>

void http_set_header_useragent(std::string useragent);
void http_set_oauth_token(std::string token);
void http_set_cookie(std::string cookieval);

size_t http_write_callback(void * ptr, size_t size, size_t nmemb);

curlpp::options::WriteFunction * http_use_write_callback();
std::list<std::string> http_header_create();

std::string http_get(std::string url, std::map<std::string,std::string> map);
std::string http_post(std::string url, std::map<std::string,std::string> map);
std::string http_form_post(std::string url, std::map<std::string,std::string> map);

#endif // HTTP_HPP_INCLUDED
