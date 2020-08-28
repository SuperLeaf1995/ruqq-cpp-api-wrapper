echo "Compiling...";

echo "http.cpp"
g++ -Wall -Wextra -std=c++17 -fpic -g -c http.cpp -o obj/http.o
echo "log.cpp"
g++ -Wall -Wextra -std=c++17 -fpic -g -c log.cpp -o obj/log.o
echo "ruqqus.cpp"
g++ -Wall -Wextra -std=c++17 -fpic -g -c ruqqus.cpp -o obj/ruqqus.o
echo "libruqqus.so"
g++ -shared -o obj/libruqqus.so obj/http.o obj/log.o obj/ruqqus.o

echo "Done!";
