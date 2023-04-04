#pragma once
#include <iostream>
#include<fstream>
#include<conio.h>
#include<Windows.h>
#include<vector>
#include<filesystem>
#include <bitset>
#include <sstream>
const short KEY_0 = 48,
KEY_1 = 49, KEY_2 = 50, KEY_3 = 51,
KEY_4 = 52, KEY_5 = 53, KEY_6 = 54,
KEY_7 = 55, KEY_8 = 56, KEY_9 = 57;
#define CTRL(x) (#x[0] - 'a' + 1)
#define myfor(i, start, stop) for(int i=start; i<stop; i++)
using std:: cin;
using std:: cout;
using std:: ifstream;
using std:: ofstream;
using std:: string;
using std:: vector;
using std:: to_string;
using std:: remove;
using std:: to_string;
using std:: filesystem:: create_directory;
using namespace std::filesystem;
struct user
{
	string name;
	string surname;
	string id;
	string rank;
	string login;
	string password;
};

enum intype {NO_PRINT, PROTECT, NO_PROTECT};

void menu();

short mygetch(const string& message, const vector<short>& keys, const string& defaultmessage);

void sign_up(vector <user>& users, const vector<string>& ranks, const string& user_range);

void sign_in(const vector <user>& users, bool& successful_sign_in, short& index);

void read_data(vector <user>& users, vector<string>& ranks, const string& user_range, const string& data_range);

void profile(vector <user>& users, const short& index, bool& successful_sign_in, const string& user_range);

void admin_profile(vector <user>& users, vector<string>& ranks, const short& index, bool successful_sign_in, const string& user_range, const string& data_range);

void write_data(const user& user_data, const string& user_range);

void read_ranks(vector<string>& ranks, const string& user_range);

void my_exit(bool& program, const int& KEY_3);

void deleting(vector<user>& users, const string& user_range);

void read_user_data(vector<user>& users, const string& user_range);

void edit_data(vector<user>& users, const short& edit_index, const string& user_range, bool admin = false, const vector<string>& ranks = {});

string keyboard(const enum intype& type);

vector<string> get_files(const string& path);

string md5(const string& str);

void start();