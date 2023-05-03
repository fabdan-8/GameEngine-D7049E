#include "Server.h"
#include <thread>
#include <iostream>
#include <fstream>

extern Server server;

void Print(std::string msg) {
    //lock
    std::cout << msg;
    //unlock
}

void Client::Send(std::string msg) {
    SDLNet_TCP_Send(sock, msg.c_str(), msg.size());
}

void Client::DropConnection() {
    timeout += maxtime;
    std::terminate();
}

void Client::Command() {
    mut.lock();
    std::string command = std::string(data);
    std::cout << "> ";
    std::cout << receiving;
    //for (int a = 0; a < datasize; a++) {
    //    if ((data[a] >= 'a' && data[a] <= 'w') || (data[a] >= 'A' && data[a] <= 'W') || (data[a] >= '0' && data[a] <= '9')) {
    //        std::cout << data[a];
    //    }
    //    else {
    //        std::cout << "?";
    //    }
    //}
    std::cout << "\n";

    if (auth > UNKNOWN_FRIEND) {
        //ok
        if (receiving > 0) {
            if (receiving >= datasize) {
                data_buf.write(data, datasize);
                receiving -= datasize;
            }
            else {
                data_buf.write(data, receiving);
                receiving = 0;
                command = std::string(data + receiving);
            }
            if (receiving == 0) {
                //finished
                if (task.size() >= 9) {
                    if (task.find("img ") == 0) {
                        int pos = task.find(".jpg", 4);
                        if (pos == task.size() - 4) {
                            std::string imgname = task.substr(4, pos - 4);

                            //check if name is ok
                            bool name_ok = true;
                            for (int a = 0; a < imgname.size(); a++) {
                                if ((imgname[a] >= 'a' && imgname[a] <= 'z') || (imgname[a] >= 'A' && imgname[a] <= 'Z') || (imgname[a] >= '0' && imgname[a] <= '9')) {
                                    //ok
                                }
                                else {
                                    name_ok = false;
                                }
                            }
                            if (name_ok) {
                                imgname = "dump/" + imgname + ".jpg";
                                std::ofstream file;
                                file.open(imgname.c_str());
                                if (file.is_open()) {
                                    file << data_buf.rdbuf();
                                    file.close();
                                }
                                Print("made jpg - '" + imgname + "'\n");

                                Send("image received " + imgname + "\n");
                            }
                            else {
                                Print("name is weird - '" + imgname + "'\n");
                            }
                        }
                    }
                }
            }
        }
        if (receiving == 0) {
            data_buf.clear();
            task = "";
        }
        int pos = command.find_first_of('\n');
        if (pos < command.size() - 1 && datasize != command.size()) {
            command = command.substr(0, pos);
            data_buf.write(data + command.size(), datasize);
        }
        //std::cout << "{" << datasize - command.size() << "}";
    }
    else if (auth == UNAUTH_FRIEND) {
        std::string comp = "no help";
        if (command.find(comp) == 0) {//auth ok
            auth = UNKNOWN_FRIEND;
            Send("wtf\n");
            Print("auth ok\n");
        }
        else {
            DropConnection();
        }
    }

    std::string comp;

    comp = "meas";
    if (command.find(comp) == 0) {
        if (auth == SENSOR_FRIEND) {
            
        }

        goto END_COMP;
    }

    comp = "sensor friend";
    if (command.find(comp) == 0) {

        auth = SENSOR_FRIEND;

        Print("client is a sensor\n");

        goto END_COMP;
    }

    comp = "phone friend";
    if (command.find(comp) == 0) {

        auth = PHONE_FRIEND;

        Print("client is a phone\n");

        goto END_COMP;
    }

    comp = "img ";
    if (command.find(comp) == 0) {
        if (auth == PHONE_FRIEND) {
            int pos = command.find_first_of(';');
            if (pos > 0) {
                int pos2 = command.size();
                if (pos2 - pos > 1) {
                    int bytes = atoi(command.substr(pos + 1, pos2 - (pos + 1)).c_str());
                    if (bytes > 0 && bytes < 25000000) {//25 megabytes max
                        receiving = bytes;
                        task = command.substr(0, pos);
                        Print("image being received\n");
                    }
                }
            }
        }
    }

END_COMP:
    mut.unlock();
    return;
}

void Server::StartServer() {
    if (SDLNet_ResolveHost(&ip, NULL, port) < 0) {
        return;
    }
    std::cout << SDLNet_ResolveIP(&ip) << "\n";
    //system("pause>nul");
    listening_socket = SDLNet_TCP_Open(&ip);
    if (!listening_socket) {
        return;
    }
    std::thread listen_thread(&Server::Listen, this);//Listen on separate thread
    listen_thread.detach();
    Print("Server started\n");
}

void Server::StopServer() {
    listen = false;
    client_mut.lock();
    for (int a = 0; a < client.size(); a++) {
        if (client[a]) {
            SDLNet_TCP_Close(client[a]->sock);
            SDLNet_FreeSocketSet(client[a]->set);
            delete client[a];
            client[a] = nullptr;
        }
    }
    client.clear();
    client_mut.unlock();

    Print("Server stopped\n");
}

void Server::Receive() {
    if (client_mut.try_lock()) {// so it doesnt block everything
        for (int a = 0; a < client.size(); a++) {
            
            int socket_ready = SDLNet_CheckSockets(client[a]->set, 0);
            if (!client[a]->has_data) {
                client[a]->has_data = socket_ready > 0;
            }
            if (socket_ready < 0) {
                DropConnection(client[a]);//error - kill
                a = client.size() + 1;//break the loop
            }
            else if (client[a]->has_data && client[a]->mut.try_lock()) {
                client[a]->has_data = false;
                for (int b = 0; b < maxdata; b++) {
                    client[a]->data[b] = 0;
                }
                int recv = SDLNet_TCP_Recv(client[a]->sock, (void*)client[a]->data, maxdata);
                if (recv > 0) {
                    //Command(client[a]->data, client[a]);//FEL
                    //std::cout << client[a]->data << "\n";
                    //std::cout << "AAA" << "\n";
                    client[a]->datasize = recv;
                    client[a]->command_thread = std::thread(&Client::Command, client[a]);
                    client[a]->command_thread.detach();
                    client[a]->timeout = 0;
                    client[a]->mut.unlock();
                }
                else {
                    DropConnection(client[a]);
                    a = client.size() + 1;//break the loop
                }
            }
            else {
                client[a]->timeout++;
                if (client[a]->timeout == maxtime / 2) {
                    client[a]->Send("hello\n");
                }
                else if (client[a]->timeout >= maxtime) {
                    Print("timed out... ");
                    DropConnection(client[a]);
                    a = client.size() + 1;//break the loop
                }
            }
        }
        client_mut.unlock();
    }
}

void Server::Listen() {
    listen = true;
    while (listen) {
        TCPsocket new_socket = SDLNet_TCP_Accept(listening_socket);
        if (new_socket) {
            client_mut.lock();
            if (listen) {
                Client* new_client = new Client;
                new_client->set = SDLNet_AllocSocketSet(1);
                SDLNet_TCP_AddSocket(new_client->set, new_socket);
                new_client->sock = new_socket;

                Print("new connection! (" + std::to_string(client.size() + 1) + " total)\n");

                new_client->auth = UNAUTH_FRIEND;
                new_client->Send("send help\n");

                client.push_back(new_client);
            }
            else {
                SDLNet_TCP_Close(new_socket);
            }
            client_mut.unlock();
        }
    }
    SDLNet_TCP_Close(listening_socket);
    listening_socket = nullptr;
}

bool Server::FindClient(Client* which_client) {
    bool found = false;
    if (which_client) {
        for (int a = 0; a < client.size(); a++) {
            if (client[a] == which_client) {
                found = true;
                a = client.size();
            }
        }
    }
    return found;
}

void Server::DropConnection(Client* which_client) {
    if (which_client) {
        for (int a = 0; a < client.size(); a++) {
            if (client[a] == which_client) {
                client[a] = nullptr;
                client.erase(client.begin() + a);

                if (which_client->mut.try_lock()) {
                    //command not running
                }
                else {
                    which_client->command_thread.~thread();
                }

                SDLNet_TCP_Close(which_client->sock);
                SDLNet_FreeSocketSet(which_client->set);

                delete which_client;

                Print("connection " + std::to_string(a + 1) + " dropped! (" + std::to_string(client.size()) + " remaining)\n");

                return;
            }
        }
    }
}
