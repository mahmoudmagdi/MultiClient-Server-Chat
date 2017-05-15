#include <iostream>
#include "unp.h"

int main(){

    int client;
    int portnum = 2430;
    int bufferSize = 1024;
    char buffer[bufferSize];
    char* ip = (char *) "127.0.0.1";
    struct sockaddr_in server_addr;
    
    
    client = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnum);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    
    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        std::cout << "=> Connection to the server port number: " << portnum << std::endl;
    
    read(client, buffer, (size_t) bufferSize);
    
    do {
        std::cout << "Client: ";
        do {
            std::cin >> buffer;
            write(client, buffer, (size_t) bufferSize);
            if (*buffer == '#') {
                return 0;
            }
        } while (*buffer != '*');
        
        std::cout << "Server: ";
        do {
            read(client, buffer, (size_t) bufferSize);
            std::cout << buffer << " ";
            if (*buffer == '#') {
                return 0;
            }
        } while (*buffer != '*');
        std::cout << std::endl;
        
    } while (true);
    
    }
