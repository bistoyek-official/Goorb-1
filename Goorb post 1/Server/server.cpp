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

int constexpr PORT = 10000;

int client[2], server_socket_, cnt;

void broadcast(){
    bool run[2] = {true, true};
    char c[1];
	for(int i = 0; run[0] && run[1]; i = 1 - i){
        if(!run[i])
            continue;
        if(recv(client[i], c, 1, 0) < 0){
            run[i] = false;
            continue;
        }
        if((*c) == '~'){
            run[i] = false;
            --cnt;
            send(client[1 - i], "0 ", 2, 0);
            return;
        }
        send(client[1 - i], c, 1, 0);
    }
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
	server_socket_ = server_socket;
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
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;
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
	cnt = 2;
	for(int i = 0; i < 2; ++i)
        send(client[i], "0 ", 2, 0);
	while(cnt == 2)
		broadcast();
    #if defined(__unix__) || defined(__APPLE__)
    int signal;
    if(signal == SIGINT || signal == SIGTERM){
    	close(client[0]);
        close(client[1]);
        close(server_socket_);
    }
    #else
    DWORD signal;
    if(signal == CTRL_CLOSE_EVENT){
        close(client[0]);
        close(client[1]);
        close(server_socket_);
        WSACleanup();
    }
    #endif
	return 0;
}

#if defined(__unix__) || defined(__APPLE__)
void handleSignal(int signal){
    if(signal == SIGINT || signal == SIGTERM){
    	close(client[0]);
        close(client[1]);
        close(server_socket_);
    }
}

#else
BOOL WINAPI ConsoleHandler(DWORD signal){
    if(signal == CTRL_CLOSE_EVENT){
        close(client[0]);
        close(client[1]);
        close(server_socket_);
        WSACleanup();
    }
    return TRUE;
}
#endif
