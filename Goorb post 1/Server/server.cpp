/*
MIT License

Copyright (c) 2024 bistoyek(21)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <unistd.h>
#include <time.h>

#if defined(__unix__) || defined(__APPLE__)
#include <arpa/inet.h>
#include <netdb.h>

#else
#include "win_arpa_inet.hpp"
#endif

int constexpr PORT = 10000, BUFFER_SIZE = ((1 << 30) + 2) / 3;

char buffer[BUFFER_SIZE];

int client[2];

std::string msg[2];

bool my_recv(int _){
    msg[_] = "";
    char ch = '0';
    char* c = &ch;
    int64_t sz = 0;
    while((*c) != ' '){
        sz = 10 * sz + (*c) - '0';
        int len = recv(client[_], c, 1, 0);
        msg[_] += (*c);
        if(len < 0)
            return false;
    }
    for(int i = 0; i < sz; ++i){
        recv(client[_], c, 1, 0);
        msg[_] += (*c);
    }
    return true;
}

void get_msg(){
	for(int i = 0; i < 2; ++i)
		my_recv(i);
	return;
}

void give_msg(){
	for(int i = 0; i < 2; ++i)
		if(msg[i].size())
			send(client[!i], msg[i].c_str(), msg[i].size(), 0);
	return;
}

int main(){
	std::cout << "Goorb post\n";
	std::cout << "Raz protocol\n";
	std::cout << "Created by: 21\n";
	std::cout << "____________________________________________________\n\n";
    #if !defined(__unix__) && !defined(__APLLE__)
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    #endif
	char host[256];
	gethostname(host, sizeof(host));
	std::cout << "Server IP: " << inet_ntoa(*((struct in_addr*)gethostbyname(host)->h_addr_list[0])) << '\n';
	std::cout << "Running on port: " << PORT << '\n';
	std::cout << "-------------\n\n";
	int server_socket, client_socket;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket == -1){
		std::cerr << "Failed to create socket" << std::endl;
		return 1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		std::cerr << "Failed to bind socket" << std::endl;
		return 1;
	}
	if(listen(server_socket, 2) == -1){
		std::cerr << "Failed to listen on socket" << std::endl;
		return 1;
	}
	std::cout << "Server is running..." << std::endl;
	for(int i = 0; i < 2; ++i){
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
		if(client_socket == -1){
			std::cerr << "Failed to accept client" << std::endl;
			--i;
			continue;
		}
		struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        #if defined(__unix__) || defined(__APPLE__)
        auto t = &timeout;
        #else
        auto t = reinterpret_cast<const char*>(&timeout);
        #endif
        if(setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, t, sizeof(timeout)) < 0){
            std::cout << "Error setting socket options" << '\n';
            exit(1);
        }
		std::cout << "Connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
		client[i] = client_socket;
	}
	while(true){
		get_msg();
		give_msg();
	}
	close(server_socket);
	#if !defined(__unix__) && !defined(__APPLE__)
    WSACleanup();
    #endif
	return 0;
}
