#ifndef __BANK_H__
#define __BANK_H__

#include <vector>
#include "client.h"

using namespace std;

class Bank{

private:
	vector<Client*> clients;

public:
	Bank(){};
	Client* find_client_by_id(int id);
	void add_client(Client* client);
	vector<Client*> get_clients();
};


#endif