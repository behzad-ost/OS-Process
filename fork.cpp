#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

using namespace std;

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(void){
	int pid;
	pid= fork();

	if(pid==0){
		while(1)
			cout<<"Child"<<endl;
	}else{
		string s;
		while(cin>>s)
			if(s=="quit"){
				kill(pid,SIGKILL);
				break;
			}

	}

   return 0;
}