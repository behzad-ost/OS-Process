#include <string>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "bank.h"
#include "utils.h"
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
using namespace std;


int main(){
	string dir;
	int num_of_proc;
	Bank* bank = new Bank();
	vector<string> files;
	cout<<"Directory : ";
	cin >> dir;
	cout<<"Number_of_Processes : ";
	cin >> num_of_proc;
	files = get_directory_files(dir);
	int checking[10000] ;
	pid_t pid;
	int num_of_files_per_proc =  files.size() / num_of_proc + 1;
	int fd_write;
	int fd_read;
	char myfifo[20] = "/tmp/fifo";
	strcat(myfifo,dir.c_str());
    mkfifo(myfifo, 0666);
	pid = fork();

	if(pid==-1){
		cout<<"Error Forking!"<<endl;
		return 1;
	}
	vector<int> child_pids;
	if(pid==0){
		char buf[100];
		int count = 0;
		int fd2 ;
		string boogy_files="";
		while((fd2 = open(myfifo, O_RDONLY)) > 0){
				int n = read(fd2, buf, 100);
				close(fd2);
	        	buf[n] = '\0';
	        	if(strcmp(buf,"")!=0){
					count++;
					string boogy_file(buf);
					vector<string> named_tokens  = split_string(boogy_file, '#');
					for(int t = named_tokens.size()-1 ; t >=0  ; t--){
						if(named_tokens[t]!=""){
							cout<<"			Cheat in : "<<named_tokens[t]<<endl;
							boogy_files += named_tokens[t];
							boogy_files += "\n";
							named_tokens.pop_back();
						}
					}
					if(count % 10 == 0){
						boogy_files += "\t\t\t";
						boogy_files += "\n";
						boogy_files += int2str(count);
						log(boogy_files);
						boogy_files="";
					}
	        	}
		}
	    printf("Done with the named Pipe\n");
		exit(0);
	}else{
		child_pids.push_back(pid);
		int index = 0;
		for(int i = 0 ; i < num_of_proc ; i++){
    		int fd[2];
    		pipe(fd);
    		pid = fork();
    		if(pid==0){
    			close(fd[1]);
    			char pm[20];
		    	int bytes;
		    	if((bytes = read(fd[0], pm, 1000)) > 0){
		    		pm[bytes]='\0';
		    		close(fd[0]);
		    		string s(pm);
		   	 		vector<string> tokens = split_string(s,'*');
		   	 		for(int k = 0 ; k < tokens.size() ; k++){
		   	 			if(tokens[k]!=""){
							cout<<"Proccing: ./" + dir + "/" +tokens[k] <<endl;
			   	 			if(cheat_checker("./"+dir+"/"+tokens[k], bank)==1){
			   	 				fd_write = open(myfifo, O_WRONLY);
						    	char send[100];
						    	strcpy(send, tokens[k].c_str());
						    	strcat(send, "#");
						    	write(fd_write, send, strlen(send));
			   	 				
			   	 			}
		   	 			}
		   	 		}
		   	 		exit(0);
		    	}
    		}else{
    			child_pids.push_back(pid);
		    	close(fd[0]);
				string files_concat = "";
				for(int j = 0 ; j < num_of_files_per_proc ; j++){
					if(index < files.size()){						
						files_concat+=files[index];
						files_concat+="*";
						index++;
					}
				}    	
					int status;
					pid_t result = waitpid(pid, &status, WNOHANG);
					// cout<<"child "<<i<<" : "<<pid<<" : "<<status<<endl;
		    		write(fd[1], files_concat.c_str(), files_concat.length());
		    		close(fd[1]);
	    			// wait(NULL); //for big num_proc
    		}
		}
		
		string quit;
		while(cin>>quit){
			if(quit=="quit"){
				for(int i = 0 ; i < child_pids.size() ; i++){
					int status;
					// pid_t result = waitpid(child_pids[i], &status, WNOHANG);
					// cout<<"child "<<i<<" : "<<child_pids[i]<<" : "<<status<<endl;
					kill(child_pids[i], SIGKILL);
				}
				break;
			}
		}
		cout<<"Killed All "<<endl;
		exit(0);
	}
}