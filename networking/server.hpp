#pragma once

#include <SDL2/SDL_net.h>
#include <vector>

namespace engine::networking {

class handler {
public:
    virtual ~handler() = default;

    virtual std::vector<uint8_t> receive(int id, const std::vector<uint8_t> &data) = 0;
    virtual bool idle() = 0;
};

class server {
public:
    server(uint16_t port, int max_connections);
    ~server();

    server(const server &) = delete;
    server &operator=(const server &) = delete;

    void run(unsigned int timeout, handler &h);
    void shutdown();

private:
    SDLNet_SocketSet socket_set;
    std::vector<TCPsocket> clients;
    unsigned int num_clients;
    bool running;
    TCPsocket server_socket;

    int check_server_socket();
    int check_client_socket(int i, handler &h);
    void add_client(TCPsocket client);
    void remove_client(int i);
};

} // namespace engine::networking
