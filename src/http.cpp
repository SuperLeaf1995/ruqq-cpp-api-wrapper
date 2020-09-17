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

static std::string oauth_token;
static std::string cookie;
static std::string h_useragent;

void http_set_oauth_token(std::string token) {
	oauth_token = token;
}

void http_set_cookie(std::string cookieval) {
	cookieval = cookie;
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

/**
Check HTTP response codes
*/
void http_error_check(long int http_status) {
	if(http_status > 299 || http_status < 199) {
		switch(http_status) {
			case 525:
				throw std::runtime_error("SSL Handshake Error");
			case 505:
				throw std::runtime_error("HTTP Version Not Supported");
			case 503:
				throw std::runtime_error("Service Unavailable");
			case 500:
				throw std::runtime_error("Internal Server Error");
			case 451:
				throw std::runtime_error("Unavailable for Legal Reasons");
			case 418:
				throw std::runtime_error("I'm a Teapot");
			case 405:
				throw std::runtime_error("Method not Allowed");
			case 404:
				throw std::runtime_error("Not found");
			case 403:
				throw std::runtime_error("Forbidden");
			case 401:
				throw std::runtime_error("Unauthorized");
			default:
				throw std::runtime_error("Invalid response code "+std::to_string(http_status));
		}
	}
	return;
}

std::list<std::string> http_header_create() {
	// HTTP Header
	std::list<std::string> header;
	header.push_back("User-Agent: libruqquscpp/1.0");
	header.push_back("X-Poster-Type: bot");
	header.push_back("X-API-Library: ruqqus-cpp");
	if(!oauth_token.empty()) {
		header.push_back("Authorization: Bearer "+oauth_token);
	}
	if(!cookie.empty()) {
		header.push_back("Set-Cookie: session_ruqqus="+cookie+"; Domain=.ruqqus.com; Path=/; Secure; HttpOpnly");
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
	
	long int http_status = curlpp::infos::ResponseCode::get(*easy_handle);
	delete easy_handle;
	http_error_check(http_status);
	
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
	
	long int http_status = curlpp::infos::ResponseCode::get(*easy_handle);
	delete easy_handle;
	http_error_check(http_status);
	
	return write_buffer;
}

std::string http_form_post(std::string url, std::map<std::string,std::string> data) {
	// Write function
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	curlpp::Forms form;
	
	// Perform request
	std::list<std::string> header = http_header_create();
	//header.push_back("Content-Type: application/x-www-form-urlencoded");

	easy_handle->setOpt(http_use_write_callback());
	easy_handle->setOpt(new curlpp::options::Url(url));
	easy_handle->setOpt(new curlpp::options::HttpHeader(header));

	// Iterate over form data
	std::map<std::string,std::string>::iterator i = data.begin();
	while(i != data.end()) {
		std::string k = i->first;
		std::string v = i->second;
		form.push_back(new curlpp::FormParts::Content(k,v));

		std::cout << k << ":" << v << std::endl;

		i++;
	}

	easy_handle->setOpt(new curlpp::options::HttpPost(form));
	easy_handle->perform();
	
	long int http_status = curlpp::infos::ResponseCode::get(*easy_handle);
	delete easy_handle;
	http_error_check(http_status);
	
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
	
	long int http_status = curlpp::infos::ResponseCode::get(*easy_handle);
	delete easy_handle;
	http_error_check(http_status);
	
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
	delete easy_handle;
	http_error_check(http_status);

	return write_buffer;
}
