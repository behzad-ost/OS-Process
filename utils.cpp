#include <vector>
#include "client.h"
#include "bank.h"
#include "utils.h"


using namespace std;


vector<string> get_directory_files(string dir_name){
	DIR *d;
  	struct dirent *dir;
  	vector<string> files;
  	d = opendir(dir_name.c_str());
  	if (d){
    	while ((dir = readdir(d)) != NULL){
    		if(dir->d_type == DT_REG)
      			// printf("%s\n", dir->d_name);
      			files.push_back(dir->d_name);
    	}
    	closedir(d);
    	return files;
  }
}

vector<string> split_string(string str , char c){
	vector<string> result;
	int space_pos=0;
	while(space_pos!=-1){
		space_pos=str.find(c);
		if(space_pos != 0)
			result.push_back(str.substr(0,space_pos));
		str=str.substr(space_pos+1);
	}
	return result;
}


int cheat_checker(string file_path, Bank* bank){
	string line;
  	ifstream myfile (file_path.c_str());
  	if (myfile.is_open()){
    	while ( getline(myfile,line)){
      		// cout << line << '\n';
      		vector<string> tokens;
      		tokens = split_string(line, ' ');
      		if(tokens[1]!= "->"){
      			int id = atoi(tokens[0].c_str());
      			int balance = atoi(tokens[2].c_str());
      			Client* client = new Client(id, balance);
      			bank->add_client(client);
      			// vector<Client*> people;
      			// people = bank->get_clients();
      			// int b = people[0]->get_balance();
      			// cout<<b<<endl;
      		}else{
      			Client* sender = bank->find_client_by_id(atoi(tokens[0].c_str()));
      			Client* receiver = bank->find_client_by_id(atoi(tokens[2].c_str()));
      			int amount = atoi(tokens[4].c_str());
      			sender->increase_balance(amount);
      			receiver->decrease_balance(amount);
      			if(sender->get_balance()<0){
              cout<<"Client "<<sender->get_id()<<" is cheater"<<endl;
              return 1;
            }
      		}
    	}
    	myfile.close();
      return 0;
  	}
  	else{
  		cout << "Unable to open file"; return -1;
  	}
}

void log(string l){
  ofstream log_file("log.txt",fstream::app);
  log_file<<(l+"\n");
  log_file.close();
}

string int2str(int n) {
  if(n <= 0)
    return "0";
  string s;
  while(n != 0) {
    s = (char)(n % 10 + '0') + s;
    n /= 10;
  }
  return s;
}
