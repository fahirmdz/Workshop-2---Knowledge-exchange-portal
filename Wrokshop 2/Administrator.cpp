#pragma once
#include"pch.h"
#include "Administrator.h"

Administrator::Administrator() :_ime(nullptr), _prezime(nullptr) {}
Administrator::Administrator(const char *ime, const char *prezime, Login l) : _login(l) {
	_ime = AlocirajNizKaraktera(ime);
	_prezime = AlocirajNizKaraktera(prezime);
}
Administrator::Administrator(const Administrator& a) : _login(a._login) {
	_ime = AlocirajNizKaraktera(a._ime);
	_prezime = AlocirajNizKaraktera(a._prezime);
}

Administrator::~Administrator() {
	delete[] _ime; _ime = nullptr;
	delete[] _prezime; _prezime = nullptr;
}

Administrator& Administrator::operator=(const Administrator& a) {
	if (&a != this) {
		delete[] _ime;
		delete[] _prezime;
		_ime = AlocirajNizKaraktera(a._ime);
		_prezime = AlocirajNizKaraktera(a._prezime);
		_login = a._login;
	}
	return *this;
}
char *Administrator::getIme()const { return AlocirajNizKaraktera(_ime); }

char *Administrator::getPrezime()const { return AlocirajNizKaraktera(_prezime); }

Login Administrator::getLogin()const { return _login; }

void Administrator::changeUsername(const char *user) { _login.changeUsername(user); }

void Administrator::changePassword(const char *pw) { _login.changePassword(pw); }

void Administrator::changeIme(const char *ime) {
	delete[] _ime;
	_ime = AlocirajNizKaraktera(ime);
}

void Administrator::changePrezime(const char *prezime) {
	delete[] _prezime;
	_prezime = AlocirajNizKaraktera(prezime);
}