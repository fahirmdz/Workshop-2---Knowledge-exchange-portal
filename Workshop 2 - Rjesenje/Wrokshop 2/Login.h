#pragma once
#include "pch.h"
#include<iostream>
#include<cstring>

using namespace std;

char *AlocirajNizKaraktera(const char *);
class Login {
private:
	char *_username, *_password;

public:
	Login();
	Login(const char*, const char *);
	Login(const Login&);
	~Login();
	Login& operator=(const Login&);
	bool valid()const;
	void changeUsername(const char *);
	void changePassword(const char *);
	char *getPassword()const;
	char *getUsername()const;

	friend ostream& operator<<(ostream&, const Login&);
	friend class Administrator;
	friend bool operator==(const Login&, const Login&);
};
