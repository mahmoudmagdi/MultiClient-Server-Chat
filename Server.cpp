#include <iostream>
#include "unp.h"

int main(){

    
    int client, server;
    int portNum = 2430;
    int bufferSize = 1024;
    char buffer[bufferSize];
    struct sockaddr_in server_addr;
    socklen_t size;
    int pid;
    
    client = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);
    
    if ((bind(client, (struct sockaddr *) &server_addr, sizeof(server_addr))) < 0) {
        std::cout << "=> Error binding connection, the socket has already been established..." << std::endl;
        return -1;
    }
    
    listen(client, 1);
    size = sizeof(server_addr);
    pid = fork();
    
    while (1) {
        
        if(pid > 0 || pid == 0){
            
            server = accept(client, (struct sockaddr *) &server_addr, &size);
            strcpy(buffer, "=> Server connected...\n");
            write(server, buffer, (size_t) bufferSize);
            
            do {
                std::cout << "Client: ";
                do {
                    read(server, buffer, (size_t) bufferSize);
                    std::cout << buffer << " ";
                    if (*buffer == '#') {
                        *buffer = '*';
                        goto terminate;
                    }
                } while (*buffer != '*');
                
                
                std::cout << "\nServer: ";
                do {
                    std::cin >> buffer;
                    write(server, buffer, (size_t) bufferSize);
                    if (*buffer == '#') {
                        write(server, buffer, (size_t) bufferSize);
                        *buffer = '*';
                        return 0;
                    }
                } while (*buffer != '*');
            } while (true);

        }
        
    terminate:
        close(server);
        exit(1);
    }
}
