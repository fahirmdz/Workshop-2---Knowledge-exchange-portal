#pragma once
#include "Administrator.h"
#include "Korisnik.h"
#include "Clanak.h"

class KnowledgeExchange {

private:
	char *_appName;
	Administrator admin;
	Korisnik* _korisnici;
	Clanak* _clanci;
	int brKorisnika, brClanaka;

public:
	KnowledgeExchange();
	KnowledgeExchange(const char *, Administrator);
	KnowledgeExchange(const KnowledgeExchange&);
	~KnowledgeExchange();

	KnowledgeExchange& operator+=(const Korisnik&);
	KnowledgeExchange& operator+=(const Clanak&);
	KnowledgeExchange& operator-=(const Korisnik&);
	KnowledgeExchange& operator-=(const Clanak&);

	bool checkUsername(const char*);
	bool prikaziClanke(const Korisnik&,int);
	bool prikaziClanke(const Korisnik&);
	Clanak* createClanak(const Korisnik&);
	char *getName()const;
	char* inputPassword();
	void adminSector();
	void userSector();
	Korisnik* portalLogin();
	Korisnik* logovanje();
	Korisnik* registracija();
	friend class Administrator;
};
