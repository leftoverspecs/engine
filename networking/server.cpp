#include "server.hpp"

#include "transmit.hpp"

#include <algorithm>
#include <iostream>
#include <map>

namespace engine::networking {

namespace {

TCPsocket open_server_socket(uint16_t port) {
    IPaddress addr;
    if (SDLNet_ResolveHost(&addr, nullptr, port) < 0) {
        SDL_Log("Error resolving host: %s", SDLNet_GetError());
        throw std::runtime_error("Error resolving host");
    }
    TCPsocket socket = SDLNet_TCP_Open(&addr);
    if (socket == nullptr) {
        SDL_Log("Error opening socket: %s", SDLNet_GetError());
        throw std::runtime_error("Error opening socket");
    }
    return socket;
}

} // namespace

server::server(uint16_t port, int max_connections)
    : socket_set(SDLNet_AllocSocketSet(max_connections)),
      server_socket(open_server_socket(port)),
      clients(max_connections, nullptr),
      num_clients(0),
      running(true)
{
    if (socket_set == nullptr) {
        SDL_Log("Error allocating socket set: %s", SDLNet_GetError());
        throw std::runtime_error("Error allocating socket set");
    }
    if (SDLNet_TCP_AddSocket(socket_set, server_socket) != 1) {
        SDL_Log("Error adding server socket to socket set: %s", SDLNet_GetError());
        throw std::runtime_error("Error adding server socket to socket set");
    }
}

server::~server() {
    for (int i = 0; i < clients.size(); ++i) {
        remove_client(i);
    }
    SDLNet_TCP_DelSocket(socket_set, server_socket);
    SDLNet_TCP_Close(server_socket);
    SDLNet_FreeSocketSet(socket_set);
}

void server::run(unsigned int timeout, handler &h) {
    SDL_Log("Server: Let's serve!");
    while (running || num_clients > 0) {
        int ready = SDLNet_CheckSockets(socket_set, timeout);
        if (ready < 0) {
            SDL_Log("Error checking sockets: %s", SDLNet_GetError());
            throw std::runtime_error("Error checking sockets");
        } else if (ready == 0) {
            if (!h.idle()) {
                running = false;
            }
        } else {
            ready -= check_server_socket();
            int i = 0;
            while (i < clients.size() && ready > 0) {
                TCPsocket &client = clients[i];
                if (client != nullptr) {
                    ready -= check_client_socket(i, h);
                }
                ++i;
            }
        }
    }
    SDL_Log("Server: Goodbye!");
}

int server::check_client_socket(int i, handler &h) {
    TCPsocket &client = clients[i];
    if (SDLNet_SocketReady(client)) {
        const auto received = receive(client);
        const auto answer = h.receive(i, received);
        if (running) {
            send(client, answer);
            if (received.empty()) {
                remove_client(i);
            }
        } else {
            send(client, {});
            remove_client(i);
        }
        return 1;
    }
    return 0;
}

int server::check_server_socket() {
    if (SDLNet_SocketReady(server_socket)) {
        if (num_clients < clients.size()) {
            TCPsocket client = SDLNet_TCP_Accept(server_socket);
            if (client != nullptr) {
                if (running) {
                    add_client(client);
                } else {
                    SDLNet_TCP_Close(client);
                    SDL_Log("Can't accept more clients since server shuts down");
                }
            } else {
                SDL_Log("Error accepting Client: %s", SDLNet_GetError());
            }
        } else {
            SDL_Log("Can't accept more clients, already accepted %ld", clients.size());
        }
        return 1;
    } else {
        return 0;
    }
}

void server::add_client(TCPsocket client) {
    const auto it = std::find(clients.begin(), clients.end(), nullptr);
    if (it != clients.end()) {
        if (SDLNet_TCP_AddSocket(socket_set, client) > 0) {
            SDL_Log("Accepting Client %d", num_clients);
            *it = client;
            ++num_clients;
        } else {
            SDL_Log("Error adding Client socket to socket set: %s", SDLNet_GetError());
            SDLNet_TCP_Close(client);
        }
    } else {
        SDL_Log("Can't find any free Client slots");
        SDLNet_TCP_Close(client);
    }
}

void server::remove_client(int i) {
    TCPsocket &client = clients[i];
    if (client != nullptr) {
        SDL_Log("Client %d quit", i);
        SDLNet_TCP_DelSocket(socket_set, client);
        SDLNet_TCP_Close(client);
        client = nullptr;
        --num_clients;
    }
}

void server::shutdown() {
    running = false;
}

} // namespace common
