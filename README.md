# ruqqus-cpp
Fanmade API made by me for using the ruqqus api

## Example ruqqus bot
```cpp
#include <ruqquscpp/ruqqus.hpp>
#include <ruqquscpp/http.hpp>

std::string client_id = "yourClientId";
std::string client_secret = "clientSecret";
std::string refresh_token = "refreshToken";
std::string server = "https://ruqqus.com";
Ruqqus client(server);

int main(int argc, char ** argv) {
	// Place some stuffy
	client.client_id = client_id;
	client.client_secret = client_secret;
	client.refresh_token = refresh_token;

	// Initial refresh
	client.token = client.oauth_update_token();
	std::cout << "Auto refreshed token " << client.token << std::endl;
	
	client.post_submit("https://example.com","Hello World","Hello World!","ruqqusapi");

	return 0;
}
```

## Installation

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

You're done! :)
