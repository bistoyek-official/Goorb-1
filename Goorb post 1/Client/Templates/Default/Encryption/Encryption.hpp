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
#include "selected.hpp"

int constexpr BY = 256, _K_ = 8;

vector<string> bank_y[BY];

string contact_name;

int is_online = 0;

class Client{
	public:
    bool open = false;

    void start(const string& server_ip, int server_port){
        #if !defined(__unix__) && !defined(__APLLE__)
        WSADATA wsaData;
        if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
            cout << "WSAStartup failed" << '\n';
            return;
        }
        #endif
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);
        inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock == -1){
            cout << "Failed to create socket" << '\n';
            return;
        }
        if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
            cout << "Failed to connect to server" << '\n';
            return;
        }
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        #if defined(__unix__) || defined(__APPLE__)
        auto t = &timeout;
        #else
        auto t = reinterpret_cast<const char*>(&timeout);
        #endif
        if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, t, sizeof(timeout)) < 0){
            cout << "Error setting socket options" << '\n';
            exit(1);
        }
        open = true;
        return;
    }

    void send_it(){
        string dir = "../Draft/encoded.txt";
        std::ifstream f(dir);
        bool b = false;
        char byte;
        int64_t cnt = 0;
        while(f.get(byte))
            ++cnt;
        f.close();
        string data = to_string(cnt);
        send(sock, data.c_str(), data.size(), 0);
        send(sock, " ", 1, 0);
        f.open(dir);
        char c[1];
        while(f.get(byte)){
            c[0] = byte;
            send(sock, c, 1, 0);
        }
        f.close();
        time_t t = time(nullptr);
        dir = "../Chats/You/" + to_string(t) + "/";
        create_dir(dir);
        move_file("../Draft/message.zip", dir);
        move_file("../Draft/encoded.txt", dir);
        ofstream f1("../Draft/message.zip", ios::binary);
        write_zip_header(f1);
        f1.close();
        return;
    }

    bool my_recv(){
        char ch = '0';
        char* c = &ch;
        int64_t sz = 0;
        while((*c) != ' '){
            sz = 10 * sz + (*c) - '0';
            int len = recv(sock, c, 1, 0);
            if(len < 0)
                return false;
        }
        if(!sz){
            ++is_online;
            return false;
        }
        time_t t = time(nullptr);
        string dir = "../Chats/" + contact_name + "/" + to_string(t)+ "/encoded.txt";
        create_dir("../Chats/" + contact_name + "/" + to_string(t)+ "/");
        ofstream f(dir);
        cout << "receiving the message ..." << '\n';
        for(int i = 0; i < sz; ++i){
            if(i % 2048 == 0)
                cout << "*";
            else if(i % 1024 == 0)
                cout << "\b \b";
            recv(sock, c, 1, 0);
            f << (*c);
        }
        f.close();
        cout << "\nthe message received completely!" << '\n';
        return true;
    }

    bool recv_it(){
        return my_recv();
    }

    void end_it(){
        send(sock, "~", 1, 0);
        close(sock);
        #if !defined(__unix__) && !defined(__APPLE__)
        WSACleanup();
        #endif
        open = false;
        return;
    }

private:
    int sock;
    struct sockaddr_in server_addr;
} client;

void encode_to_send(){
    string dir = "../Draft/";
	for(int i = 0; i < BY; ++i){
		ifstream bank("../Bank/" + to_string(i) + ".txt");
		if(!bank.is_open())
            exit(2);
		bank_y[i].clear();
		bank_y[i].push_back("");
		while(getline(bank, bank_y[i][bank_y[i].size() - 1])){
            if(bank_y[i][bank_y[i].size() - 1].empty()){
                bank_y[i].pop_back();
                break;
            }
            bank_y[i].push_back("");
        }
        if(bank_y[i][bank_y[i].size() - 1].empty())
            bank_y[i].pop_back();
		bank.close();
	}
	ifstream plain_text(dir + "message.zip", ios::binary);
	ofstream cipher_text(dir + "encoded.txt");
	cipher_text.close();
	if(!plain_text.is_open()){
        cout << "can't find the file try again, press any key to continue";
        getch();
        return;
	}
	len = 0;
	srand(time(nullptr));
	while(true){
		int c = rnb(plain_text) + 128;
		if(c == -1)
            break;
        for(int i = 0; i < 8; ++i)
            mapped[len + i] = ((c & (1 << (7 - i))) != 0);
		len += 8;
		if(len % _K_ == 0 && CAPACITY - len < _K_){
            cipher_text.open(dir + "encoded.txt", ios::app);
            for(int i = 0; i < len / _K_; ++i){
                int num = 0;
                for(int j = i * _K_; j < (i + 1) * _K_; ++j)
                    num = (num << 1) | mapped[j];
                cipher_text << bank_y[num][rand() % bank_y[num].size()] << '\n';
            }
            cipher_text.close();
            len = 0;
		}
	}
	if(len){
        cipher_text.open(dir + "encoded.txt", ios::app);
        for(int i = 0; i < (len + _K_ - 1) / _K_; ++i){
            int num = 0;
            for(int j = i * _K_; j < (i + 1) * _K_; ++j)
                num = (num << 1) | mapped[j];
            cipher_text << bank_y[num][rand() % bank_y[num].size()] << '\n';
        }
        cipher_text.close();
        len = 0;
    }
	return;
}

void decode_to_read(const string &dir){
	ifstream cipher_text(dir + "encoded.txt");
	int cnt = 0;
	string s;
	while(getline(cipher_text, s))
		++cnt;
	len = 0;
	b_len = false;
	sha256.decrypt(dir, cnt, ".zip");
	return;
}

#if defined(__unix__) || defined(__APPLE__)
void handleSignal(int signal){
    if(signal == SIGINT || signal == SIGTERM)
    	client.end_it();
}

#else
BOOL WINAPI ConsoleHandler(DWORD signal){
    if(signal == CTRL_CLOSE_EVENT)
        client.end_it();
    return TRUE;
}
#endif
