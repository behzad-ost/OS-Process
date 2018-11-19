#ifndef __CLIENT_H__
#define __CLIENT_H__


class Client{
private:
	int id;
	int balance;

public:
	Client(int _id, int _balance): id(_id), balance(_balance) {}
	void decrease_balance(int amount);
	void increase_balance(int amount);
	int get_id();
	int get_balance();

};

#endif