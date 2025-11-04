all: 
	cd include && mkdir build && cd build && g++ ../termios.cpp -o termios && ./termios
