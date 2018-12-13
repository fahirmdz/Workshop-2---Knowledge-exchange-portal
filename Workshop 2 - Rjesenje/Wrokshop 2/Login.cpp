#include"pch.h"
#include "Login.h"

char *AlocirajNizKaraktera(const char *a) {
	if (a == nullptr)
		return nullptr;
	char *temp = new char[strlen(a) + 1];
	strcpy_s(temp, strlen(a) + 1, a);
	return temp;
}
Login::Login() :_username(nullptr), _password(nullptr) {}
Login::Login(const char *user, const char *pass) {
	_username = AlocirajNizKaraktera(user);
	_password = AlocirajNizKaraktera(pass);
}
Login::Login(const Login& l) {
	_username = AlocirajNizKaraktera(l._username);
	_password = AlocirajNizKaraktera(l._password);
}
Login::~Login() {
	delete[] _username; _username = nullptr;
	delete[] _password; _password = nullptr;
}
Login& Login::operator=(const Login& l) {
	if (&l != this) {
		delete[] _username;
		delete[] _password;
		_username = AlocirajNizKaraktera(l._username);
		_password = AlocirajNizKaraktera(l._password);
	}
	return *this;
}
bool Login::valid()const { return !(_username == nullptr || _password == nullptr); }
void Login::changeUsername(const char *novi) {
	delete[] _username;
	_username = AlocirajNizKaraktera(novi);
}
void Login::changePassword(const char *noviPw) {
	delete[] _password;
	_password = AlocirajNizKaraktera(noviPw);
}
char* Login::getPassword()const { return AlocirajNizKaraktera(_password); }
char* Login::getUsername()const { return AlocirajNizKaraktera(_username); }

bool operator==(const Login& l1, const Login& l2) {
	return strcmp(l1._username, l2._username) == 0 && strcmp(l1._password,l2._password)==0;
}
ostream& operator<<(ostream& COUT, const Login& l) {
	if (l._password == nullptr || l._username == nullptr) {
		cout << "No available credentials..\n";
		return COUT;
	}
	cout << "Username: " << l._username << "\nPassword: " << l._password << endl;
	return COUT;
}