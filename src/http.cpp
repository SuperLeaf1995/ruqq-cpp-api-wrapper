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

std::string write_buffer;
std::mutex http_write_callback_mutex;
size_t http_write_callback(void * ptr, size_t size, size_t nmemb) {
	std::lock_guard<std::mutex> guard(http_write_callback_mutex);
	write_buffer += (char *)ptr;
	return size*nmemb;
}

std::string http_get(std::string url) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	curlpp::types::WriteFunctionFunctor functor(&http_write_callback);
	curlpp::options::WriteFunction * write_cb_opt = new curlpp::options::WriteFunction(functor);
	
	// HTTP Headers
	std::list<std::string> header;
	header.push_back("User-Agent: ruqqusCpp/3.5");
	if(!oauth_token.empty()) {
		header.push_back("Authorization: Bearer "+oauth_token);
	}
	
	// Perform request
	easy_handle->setOpt(write_cb_opt);
	easy_handle->setOpt(new curlpp::options::Url(std::string(url)));
	easy_handle->setOpt(new curlpp::options::HttpHeader(header));
	easy_handle->setOpt(new curlpp::options::HttpGet(true));
	easy_handle->perform();
	return write_buffer;
}

std::string http_post(std::string url, std::string data) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	curlpp::types::WriteFunctionFunctor functor(&http_write_callback);
	curlpp::options::WriteFunction * write_cb_opt = new curlpp::options::WriteFunction(functor);
	
	// HTTP Headers
	std::list<std::string> header;
	header.push_back("User-Agent: ruqqusCpp/3.5");
	if(!oauth_token.empty()) {
		header.push_back("Authorization: Bearer "+oauth_token);
	}
	
	// Perform request
	easy_handle->setOpt(write_cb_opt);
	easy_handle->setOpt(new curlpp::options::Url(std::string(url)));
	easy_handle->setOpt(new curlpp::options::UserAgent(std::string("NeverGonnaGiveYouUp/3.4")));
	if(!data.empty()) {
		easy_handle->setOpt(new curlpp::options::PostFields(data));
		easy_handle->setOpt(new curlpp::options::PostFieldSize(data.length()));
	}
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
	curlpp::types::WriteFunctionFunctor functor(&http_write_callback);
	curlpp::options::WriteFunction * write_cb_opt = new curlpp::options::WriteFunction(functor);
	
	// HTTP Headers
	std::list<std::string> header;
	header.push_back("User-Agent: ruqqusCpp/3.5");
	if(!oauth_token.empty()) {
		header.push_back("Authorization: Bearer "+oauth_token);
	}
	
	// Perform request
	easy_handle->setOpt(write_cb_opt);
	easy_handle->setOpt(new curlpp::options::Url(std::string(url)));
	easy_handle->setOpt(new curlpp::options::UserAgent(std::string("NeverGonnaGiveYouUp/3.4")));
	if(!data.empty()) {
		easy_handle->setOpt(new curlpp::options::PostFields(data));
		easy_handle->setOpt(new curlpp::options::PostFieldSize(data.length()));
	}
	easy_handle->perform();

	long int http_status = curlpp::infos::ResponseCode::get(*easy_handle);
	if(http_status > 299 || http_status < 199) {
		throw std::runtime_error("Invalid response code "+std::to_string(http_status));
	}

	return write_buffer;
}