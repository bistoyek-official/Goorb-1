#include "selected.hpp"

int constexpr BY = 256, _K_ = 8;

vector<string> bank_y[BY];

string contact_name = "Unkown";

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
        string data = "", s;
        bool b = false;
        while(getline(f, s)){
            if(b)
                data += '\n';
            data += s;
            b = true;
        }
        data += '\n';
        f.close();
        data = to_string(data.size()) + ' ' + data;
        send(sock, data.c_str(), data.size(), 0);
        time_t t = time(nullptr);
        dir = "../Chats/You/" + to_string(t) + "/";
        creat_dir(dir);
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
        time_t t = time(nullptr);
        string dir = "../Chats/" + contact_name + "/" + to_string(t)+ "/encoded.txt";
        creat_dir("../Chats/" + contact_name + "/" + to_string(t)+ "/");
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

#if defined(__unix__) || defined(__APPLE__)
void handleSignal(int signal){
    if(signal == SIGINT || signal == SIGTERM){
    	if(client.open)
            client.end_it();
}

#else
BOOL WINAPI ConsoleHandler(DWORD signal){
    if(signal == CTRL_CLOSE_EVENT)
        if(client.open)
            client.end_it();
    return TRUE;
}
#endif

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
	ifstream plain_text(dir + "message.zip");
	if(!plain_text.is_open()){
        cout << "can't find the file try again, press any key to continue";
        getch();
        return;
	}
	int64_t cnt = 0;
	while(true){
		int c = rnb(plain_text) + 128;
		if(c == -1)
            break;
        for(int i = 0; i < 8; ++i)
            mapped[cnt * 8 + i] = ((c & (1 << (7 - i))) != 0);
		++cnt;
	}
    cnt = (cnt * 8) / _K_;
	srand(time(nullptr));
	ofstream cipher_text(dir + "encoded.txt");
	for(int i = 0; i < cnt; ++i){
		int num = 0;
		for(int j = i * _K_; j < (i + 1) * _K_; ++j)
			num = (num << 1) | mapped[j];
		cipher_text << bank_y[num][rand() % bank_y[num].size()] << '\n';
	}
	cipher_text.close();
	return;
}

void decode_to_read(const string &dir){
	ifstream cipher_text(dir + "encoded.txt");
	int cnt = 0;
	string s;
	while(getline(cipher_text, s))
		++cnt;
	len = 0;
	sha256.decrypt(dir, cnt, ".zip");
	return;
}
