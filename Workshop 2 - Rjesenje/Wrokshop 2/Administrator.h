#pragma once
#include "Login.h"
#include "KnowledgeExchange.h"

class Administrator {
private:
	Login _login;
	char *_ime, *_prezime;
public:
	Administrator();
	Administrator(const char*, const char*, Login);
	Administrator(const Administrator&);
	~Administrator();
	Administrator& operator=(const Administrator&);
	char *getIme()const;
	char *getPrezime()const;
	Login getLogin()const;
	void changeUsername(const char *);
	void changePassword(const char *);
	void changeIme(const char *);
	void changePrezime(const char *);
};