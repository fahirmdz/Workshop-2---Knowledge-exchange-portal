#include"pch.h"
#include "Korisnik.h"

Korisnik::Korisnik() :_ime(nullptr), _prezime(nullptr), _email(nullptr), _datumRegistracije(nullptr) {}
Korisnik::Korisnik(const char *ime, const char *prezime, const char *email, const char *datum, Login &l) : _login(l) {
	_ime = AlocirajNizKaraktera(ime);
	_prezime = AlocirajNizKaraktera(prezime);
	_email = AlocirajNizKaraktera(email);
	_datumRegistracije = AlocirajNizKaraktera(datum);
}
Korisnik::Korisnik(const Korisnik& k) :_login(k._login) {
	_ime = AlocirajNizKaraktera(k._ime);
	_prezime = AlocirajNizKaraktera(k._prezime);
	_email = AlocirajNizKaraktera(k._email);
	_datumRegistracije = AlocirajNizKaraktera(k._datumRegistracije);
}
Korisnik::~Korisnik() {
	delete[] _ime, _prezime, _email, _datumRegistracije;
	_ime = _prezime = _email = _datumRegistracije = nullptr;
}

Korisnik& Korisnik::operator=(const Korisnik& k) {
	if (&k != this) {
		delete[] _ime, _prezime, _email, _datumRegistracije;
		_login = k._login;
		_ime = AlocirajNizKaraktera(k._ime);
		_prezime = AlocirajNizKaraktera(k._prezime);
		_email = AlocirajNizKaraktera(k._email);
		_datumRegistracije = AlocirajNizKaraktera(k._datumRegistracije);
	}
	return *this;
}

char *Korisnik::getIme()const { return AlocirajNizKaraktera(_ime); }
char *Korisnik::getPrezime()const { return AlocirajNizKaraktera(_prezime); }
char *Korisnik::getEmail()const { return AlocirajNizKaraktera(_email); }
char *Korisnik::getDatumRegistracije()const { return AlocirajNizKaraktera(_datumRegistracije); }
Login Korisnik::getLogin()const { return _login; }
void Korisnik::changeUsername(const char *user) { _login.changeUsername(user); }
void Korisnik::changePassword(const char *pw) { _login.changePassword(pw); }
bool Korisnik::valid()const { return !(_ime == nullptr || _prezime == nullptr || _email == nullptr || _datumRegistracije == nullptr); }


bool operator==(const Korisnik& k1, const Korisnik& k2) {
	return strcmp(k1._ime, k2._ime) == 0 && strcmp(k1._prezime, k2._prezime) == 0;
}

ostream& operator<<(ostream & COUT, const Korisnik& k) {
	if (!k.valid() || !k._login.valid()) {
		cout << "Greska! Ne mogu se ispisati informacije o korisniku..\n";
		return COUT;
	}
	cout << "Ime: " << k._ime << "\nPrezime: " << k._prezime << "\nE-mail: " << k._email << "\nDatum registracije: " << k._datumRegistracije << endl;
	cout << "--Log in podaci--\n" << k._login << endl;
	return COUT;
}