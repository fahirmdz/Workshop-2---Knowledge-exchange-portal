#pragma once
#include "Login.h"
#include "Vrijeme.h"
class Korisnik {
private:
	char *_ime, *_prezime, *_email, *_datumRegistracije;
	Login _login;

public:
	Korisnik();
	Korisnik(const char*, const char*, const char*, const char*, Login&);
	Korisnik(const Korisnik&);
	~Korisnik();
	Korisnik& operator=(const Korisnik&);
	char *getIme()const;
	char *getPrezime()const;

	char *getEmail()const;
	char *getDatumRegistracije()const;
	Login getLogin()const;
	void changeUsername(const char *);
	void changePassword(const char *);
	bool valid()const;
	friend ostream& operator<<(ostream&, const Korisnik&);
	friend class Administrator;
	friend bool operator==(const Korisnik&, const Korisnik&);
};