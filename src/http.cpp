#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Types.hpp>
#include <mutex>

#include "http.hpp"

std::string write_buffer;
std::mutex http_write_callback_mutex;
size_t http_write_callback(void * ptr, size_t size, size_t nmemb) {
	std::lock_guard<std::mutex> guard(http_write_callback_mutex);
	write_buffer += (char *)ptr;
	return size*nmemb;
}

std::string http_get(std::string url) {
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	curlpp::types::WriteFunctionFunctor functor(&http_write_callback);
	curlpp::options::WriteFunction * write_cb_opt = new curlpp::options::WriteFunction(functor);
	easy_handle->setOpt(write_cb_opt);
	easy_handle->setOpt(new curlpp::options::Url(std::string(url)));
	easy_handle->setOpt(new curlpp::options::UserAgent(std::string("NeverGonnaGiveYouUp/3.4")));
	easy_handle->setOpt(new curlpp::options::HttpGet(true));
	easy_handle->perform();
	return write_buffer;
}

std::string http_post(std::string url, std::string data) {
	write_buffer = "";
	curlpp::Easy * easy_handle = new curlpp::Easy();
	curlpp::types::WriteFunctionFunctor functor(&http_write_callback);
	curlpp::options::WriteFunction * write_cb_opt = new curlpp::options::WriteFunction(functor);
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
