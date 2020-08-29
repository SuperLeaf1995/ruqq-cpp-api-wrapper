// curlpp
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Types.hpp>
#include <curlpp/Infos.hpp>

// multithreading
#include <mutex>

// ruqquscpp
#include "http.hpp"

std::string oauth_token;

bool http_set_oauth_token(std::string token) {
	oauth_token = token;
	return true;
}

/*
Write callback and other support functions
*/
std::string write_buffer;
std::mutex http_write_callback_mutex;
size_t http_write_callback(void * ptr, size_t size, size_t nmemb) {
	std::lock_guard<std::mutex> guard(http_write_callback_mutex);
	write_buffer += (char *)ptr;
	return (size*nmemb);
}

curlpp::options::WriteFunction * http_use_write_callback() {
	// Create and return the functor
	curlpp::types::WriteFunctionFunctor functor(&http_write_callback);
	curlpp::options::WriteFunction * write_cb_opt = new curlpp::options::WriteFunction(functor);
	return write_cb_opt;
}

std::list<std::string> http_header_create() {
	// HTTP Header
	std::list<std::string> header;
	header.push_back("User-Agent: ruqqusCpp/3.5");
	if(!oauth_token.empty()) {
		header.push_back("Authorization: Bearer "+oauth_token);
	}
	return header;
}

/*
HTTP Requests Functions
*/

std::string http_get(std::string url) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	
	// Perform request
	easy_handle->setOpt(http_use_write_callback());
	easy_handle->setOpt(new curlpp::options::Url(url));
	easy_handle->setOpt(new curlpp::options::HttpHeader(http_header_create()));
	easy_handle->setOpt(new curlpp::options::HttpGet(true));
	easy_handle->perform();
	return write_buffer;
}

std::string http_post(std::string url, std::string data) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	
	// Perform request
	easy_handle->setOpt(http_use_write_callback());
	easy_handle->setOpt(new curlpp::options::Url(url));
	easy_handle->setOpt(new curlpp::options::HttpHeader(http_header_create()));
	easy_handle->setOpt(new curlpp::options::PostFields(data));
	easy_handle->setOpt(new curlpp::options::PostFieldSize(data.length()));
	easy_handle->perform();
	return write_buffer;
}

std::string http_put(std::string url, std::string data) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	
	// Perform request
	easy_handle->setOpt(http_use_write_callback());
	easy_handle->setOpt(new curlpp::options::Url(url));
	easy_handle->setOpt(new curlpp::options::HttpHeader(http_header_create()));
	easy_handle->setOpt(new curlpp::options::CustomRequest("PUT"));
	easy_handle->setOpt(new curlpp::options::PostFields(data));
	easy_handle->setOpt(new curlpp::options::PostFieldSize(data.length()));
	easy_handle->perform();
	return write_buffer;
}

/**
Sends a POST request AND validates that the HTTP response is OK (no errors).
*/
std::string http_post_http_response(std::string url, std::string data) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	
	// Perform request
	easy_handle->setOpt(http_use_write_callback());
	easy_handle->setOpt(new curlpp::options::Url(url));
	easy_handle->setOpt(new curlpp::options::HttpHeader(http_header_create()));
	easy_handle->setOpt(new curlpp::options::PostFields(data));
	easy_handle->setOpt(new curlpp::options::PostFieldSize(data.length()));
	easy_handle->perform();

	long int http_status = curlpp::infos::ResponseCode::get(*easy_handle);
	if(http_status > 299 || http_status < 199) {
		throw std::runtime_error("Invalid response code "+std::to_string(http_status));
	}

	return write_buffer;
}