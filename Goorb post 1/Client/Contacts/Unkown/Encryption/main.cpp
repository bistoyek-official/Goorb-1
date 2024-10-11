#include "Encryption.hpp"

int main(){
    init();
    while(!client.open){
        cls();
        cout << "Goorb post\n";
        cout << "Raz protocol\n";
        cout << "Created by: 21\n";
        cout << "_________________________________________\n";
        string server_ip, server_port_s;
        int server_port = 0;
        cout << "Enter the server IP: ";
        getline(cin, server_ip);
        cout << "Enter the server port: ";
        getline(cin, server_port_s);
        for(auto e: server_port_s)
            server_port = 10 * server_port + (e - '0');
        server_port = max(min(server_port, (1 << 16) - 1), 0);
        client.start(server_ip, server_port);
        if(!client.open){
            cout << "cannot connect to the server press space button to retry\n";
            while(getch() != ' ');
        }
    }
    while(true){
        while(client.my_recv());
        cls();
        cout << "Goorb post\n";
        cout << "Raz protocol\n";
        cout << "Created by: 21\n";
        cout << "_________________________________________\n";
        cout << "Private Message to: " << contact_name << "\n_________________________________________\n";
        cout << "You can choose any of these options by entering their number:\n";
        cout << "  1. Encrypt the draft\n";
        cout << "  2. Send the draft\n";
        cout << "  3. Decode message\n";
        cout << "  4. Make stronger the Bank_y\n";
        cout << "  5. Exit\n";
        if(kbhit()){
            char c = getch();
            if(c == '1')
                encode_to_send();
            if(c == '2')
                client.send_it();
            if(c == '3'){
                cout << "~ the directory of message: ";
                string dir;
                getline(cin, dir);
                decode_to_read(dir);
            }
            if(c == '4'){
                cout << "put the update folder in the ./Encryption directory and then press space\n";
                while(getch() != ' ');
                for(int i = 0; i < BY; ++i){
                    ifstream f1("update/" + to_string(i) + ".txt");
                    ofstream f2("../Bank/" + to_string(i) + ".txt", ios::app);
                    string ln;
                    while(getline(f1, ln))
                        f2 << ln << '\n';
                }
                cout << "ok now delete the update folder and then press space\n";
                while(getch() != ' ');
            }
            if(c == '5')
                exit(0);
        }
        usleep(1000000);
    }
    return 0;
}
