#pragma once
#include <SDL.h>
#include <SDL_net.h>
#include <vector>
#include <mutex>
#include <sstream>

//static const int maxdata = 1024;
static const int maxdata = 65536;
static const int maxtime = 4096;

//auth:
#define NO_FRIEND 0
#define UNAUTH_FRIEND 1
#define AUTH_FRIEND 2
#define UNKNOWN_FRIEND 3
#define SENSOR_FRIEND 4
#define PHONE_FRIEND 5

class Client {
public:
	SDLNet_SocketSet set = nullptr;
	TCPsocket sock = nullptr;
	char data[maxdata] = { 0 };
	int datasize = 0;
	std::stringstream data_buf;
	std::string task;
	int receiving = 0;
	unsigned char auth = NO_FRIEND;
	int timeout = 0;
	bool has_data = false;
	std::mutex mut;
	std::thread command_thread;
	void Send(std::string msg);
	void DropConnection();
	void Command();
};

class Server {
public:
	void StartServer();
	void StopServer();
	void Receive();
	bool listen = true;
private:
	void Listen();
	bool FindClient(Client* which_client);
	void DropConnection(Client* which_client);//only run when client_mut is locked!!!
	std::vector<Client*> client;
	TCPsocket listening_socket = nullptr;
	IPaddress ip = { 0 };
	unsigned short int port = 20276;
	int maxsockets = 4;
	std::mutex client_mut;
	//std::mutex command_mut;
};

