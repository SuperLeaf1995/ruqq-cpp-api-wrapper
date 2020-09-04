cmake_minimum_required(VERSION 3.9)
project(ruqquscpp VERSION 0.4.6 DESCRIPTION "Fanmade ruqqus API wrapper in C++")
include(GNUInstallDirs) # Use the install directories

# Include files (.hpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Library files (.cpp)
add_library(
				ruqquscpp SHARED
				
				src/ruqqus/ruqqus.cpp
				src/ruqqus/json.cpp
				src/ruqqus/user.cpp
				src/ruqqus/guild.cpp
				src/ruqqus/post.cpp
				src/ruqqus/admin.cpp
				src/ruqqus/comment.cpp
				
				src/http.cpp
			)

# Install files to the gnu dirs
install(
			TARGETS ruqquscpp
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		)
