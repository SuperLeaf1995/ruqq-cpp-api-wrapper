#!/bin/bash
#
# Use only when you want to install the project really fast on a new enviroment
# i.e Docker
#

if [ "$1" = "apt" ]; then
	sudo apt update
	sudo apt upgrade
	sudo apt install libjsoncpp-dev libcurlpp-dev -y
elif [ "$1" = "yum" ]; then
	sudo yum install libjsoncpp-dev libcurlpp-dev
else
	echo 'Unknown package manager' && exit
fi

echo 'Executing build'
sh build.sh
sleep 10
echo 'Executing fix'
sh gcc-fix.sh
