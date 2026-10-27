#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

 using namespace std;

int main() {
int  fd = socket(AF_INET, SOCK_STREAM, 0);


struct sockaddr_in addr = {};
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // Replace with the server's IP address
addr.sin_port = ntohs(1234); // Replace with the server's port
 connect(fd, (struct sockaddr*)&addr, sizeof(addr));

char message[] = "hello";
write(fd, message, sizeof(message) - 1);
 char buffer[1024];
ssize_t n = recv(fd, buffer, sizeof(buffer) - 1, 0);
if (n >0) {
buffer[n] = '\0';
cout << "server says: " << buffer << endl;
}
close(fd);
return 0;
}