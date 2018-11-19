#include <iostream>
#include "client.h"

using namespace std;

void Client::decrease_balance(int amount){
	balance-=amount;
}

void Client::increase_balance(int amount){
	balance+=amount;
}

int Client::get_id(){
	return id;
}

int Client::get_balance(){
	return balance;
}