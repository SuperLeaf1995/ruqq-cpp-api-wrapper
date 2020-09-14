// std
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <regex>

// curlpp
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Types.hpp>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Ruqqus constructor

@param servername The name of the server where the API should be contacted at, very useful to set it to localhost in case of tests
*/
Ruqqus::Ruqqus(std::string servername) {
	curlpp::initialize();
	curlpp::Cleanup raii_cleanup;
	
	server = servername;
	
	// Start the OAuth chronometer
	oauth_start = std::chrono::steady_clock::now();
}

/**
Ruqqus deconstructor. Dies.
*/
Ruqqus::~Ruqqus() {
	auto_token_continue = false;
	curlpp::terminate();
}
