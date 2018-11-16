#pragma once
#include "Vrijeme.h"
#include "Korisnik.h"

enum popularity { Low, Medium, High };


class Komentar {
private:
	Korisnik k;
	char *_tekst, *_datum;
	Vrijeme _vrijeme;
	popularity _popularnost;

public:
	Komentar();
	Komentar(Korisnik, const char *, const char *, popularity, Vrijeme);
	Komentar(const Komentar&);
	~Komentar();

	Komentar& operator=(const Komentar&);

	Komentar& operator+=(const char *);

	bool valid()const;
	friend class Administrator;
	friend ostream& operator<<(ostream&, const Komentar&);
	friend bool operator==(const Komentar&, const Komentar&);
};
