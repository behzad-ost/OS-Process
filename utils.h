#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>
#include <stdio.h>
#include "client.h"
#include "bank.h"
#include "utils.h"

using namespace std;

vector<string> get_directory_files(string dir_name);

vector<string> split_string(string str, char c);

int cheat_checker(string file_path, Bank* bank);

void log(string l);

string int2str(int n);

#endif