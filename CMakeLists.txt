cmake_minimum_required(VERSION 3.9)
project(ruqquscpp VERSION 0.4.6 DESCRIPTION "Fanmade ruqqus API wrapper in C++")
include(GNUInstallDirs) # Use the install directories

# Include files (.hpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Library files (.cpp)
add_library(
				ruqquscpp SHARED
				
				src/ruqqus.cpp
				src/json.cpp
				src/user.cpp
				src/guild.cpp
				src/post.cpp
				src/admin.cpp
				src/comment.cpp
				src/oauth.cpp
				src/http.cpp
			)

# Install files to the gnu dirs
install(
			TARGETS ruqquscpp
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		)
