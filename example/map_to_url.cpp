#include <iostream>
#include <string>
#include <map>

std::string map_to_url(std::map<std::string,std::string> map) {
	std::string final_str;
	bool use_ampere = false;
	
	for(std::map<std::string,std::string>::iterator i = map.begin(); i != map.end(); i++) {
		// Obtain pairs from map
		std::string k = i->first;
		std::string v = i->second;
		
		// Only append if not empty
		if(!k.empty() && !v.empty()) {
			// Result appended will be k=v
			final_str += ((use_ampere == true)?"&":"?");
			final_str += k+"="+v;
			
			// Next calls will use the & operator
			use_ampere = true;
		}
	}
	return final_str;
}

int main(void) {
	std::cout << "Test" << std::endl;
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("device","cam"));
	data.insert(std::pair<std::string,std::string>("console","atari"));
	data.insert(std::pair<std::string,std::string>("no","yes"));
	
	std::string end = map_to_url(data);
	
	std::cout << "END RESULT: " << "https://example.com/page" << end << std::endl;
}
