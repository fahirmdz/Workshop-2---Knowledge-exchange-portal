#pragma once
#include "Korisnik.h"
#include "Komentar.h"
#include "Vrijeme.h"

enum Oblasti :int;

class Clanak {
private:
	//Naslov, Sadrzaj, Datum, Satnica, BrojPregleda
	Korisnik _korisnik;
	char *_naslov, *_sadrzaj, *_datum;
	char *_tagovi[10]{ nullptr };
	Vrijeme _satnica;
	Komentar *_komentari;
	Oblasti _oblast;
	int brojPregleda, brojKomentara, _brojTagova;
public:
	Clanak();
	Clanak(Korisnik, Vrijeme, Oblasti, const char*, const char*, const char*, int);
	Clanak(const Clanak&);
	~Clanak();
	Clanak& operator=(const Clanak&);
	Clanak& operator+=(const Komentar&);
	bool valid()const;
	Clanak& operator+=(const char*);
	Clanak& operator-=(int);
	char* getNaslov()const;
	void uvecajPreglede(int);
	char *getDatum()const;
	Vrijeme getVrijeme()const;
	int getBrojKomentara()const;
	int getBrojTagova()const;
	int getBrojPregleda()const;
	Korisnik getAutor()const;
	bool valid();
	bool tagCompare(const char *);
	void printKomentare()const;
	friend ostream& operator<<(ostream&, const Clanak&);
	friend bool operator==(const Clanak&, const Clanak&);
	friend class Administrator;
};
