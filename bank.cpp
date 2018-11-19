#include "bank.h"
#include "client.h"
#include <stddef.h>


using namespace std;

Client* Bank::find_client_by_id(int id){
	for(int i = 0  ; i < clients.size(); i++){
		if(clients[i]->get_id()== id)
			return clients[i];
	}
	return NULL;
}

void Bank::add_client(Client* client){
	clients.push_back(client);
}

vector<Client*> Bank::get_clients(){
	return clients;
}