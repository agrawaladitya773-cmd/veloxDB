#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

 using namespace std;



int main() {
int fd = socket(AF_INET, SOCK_STREAM, 0);
int val = 1;
setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
// The above code creates a TCP socket and sets the SO_REUSEADDR option to allow the socket to bind to an address that is in a TIME_WAIT state. This is useful for quickly restarting a server without waiting for the socket to be released by the operating system.
struct sockaddr_in addr = {};
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = ntohl(0); // Bind to all available interfaces
addr.sin_port = ntohs(1234);
 bind(fd, (struct sockaddr*)&addr, sizeof(addr));
listen(fd, 5); // Start listening for incoming connections with a backlog of 5
// The above code binds the socket to port 1234 on all available network interfaces and starts liistening for incoming connections.
while (true) {
    //accept incoming connections
    int conn_fd = accept(fd, nullptr, nullptr);
    // The above code accepts an incoming connection and returns a new socket file descriptor for the connection
    char buffer[1024];
    ssize_t n = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        cout << "client says: " << buffer << endl;
        const char* response = "world";
        send(conn_fd, response, strlen(response), 0);
    }
    close(conn_fd); // Close the connection after handling it
}


return 0;
}
