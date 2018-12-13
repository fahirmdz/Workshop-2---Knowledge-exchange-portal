#include"pch.h"
#include "Komentar.h"
const char *_popularity[] = { "Low","Medium","High" };
Komentar::Komentar() :_tekst(nullptr), _datum(nullptr) {}
Komentar::Komentar(Korisnik user, const char *tekst, const char *datum, popularity p, Vrijeme v) : k(user), _popularnost(p), _vrijeme(v) {
	_tekst = AlocirajNizKaraktera(tekst);
	_datum = AlocirajNizKaraktera(datum);
}
Komentar::Komentar(const Komentar& comment) : k(comment.k), _popularnost(comment._popularnost), _vrijeme(comment._vrijeme) {
	_tekst = AlocirajNizKaraktera(comment._tekst);
	_datum = AlocirajNizKaraktera(comment._datum);
}
Komentar::~Komentar() {
	delete[] _tekst, _datum;
	_tekst = _datum = nullptr;
}

Komentar& Komentar::operator=(const Komentar& comment) {
	if (&comment != this) {
		delete[] _tekst, _datum;
		_tekst = AlocirajNizKaraktera(comment._tekst);
		_datum = AlocirajNizKaraktera(comment._datum);
		_popularnost = comment._popularnost;
		_vrijeme = comment._vrijeme;
		k = comment.k;
	}
	return *this;
}

Komentar& Komentar::operator+=(const char *tekst) {
	if (tekst == nullptr)
		return *this;
	int v = strlen(_tekst) + strlen(tekst) + 3;
	char *temp = new char[v];
	strcpy_s(temp, v, _tekst);
	strcat_s(temp, v, " ");
	strcat_s(temp, v, tekst);
	delete[] _tekst;
	_tekst = temp;
	return *this;
}

bool Komentar::valid()const { return !(_tekst == nullptr || !k.valid() || !_vrijeme.valid()); }

bool operator==(const Komentar& k1, const Komentar& k2) {
	return (k1.k == k2.k &&  strcmp(k1._tekst, k2._tekst) == 0);
}

ostream& operator<<(ostream& COUT, const Komentar& c) {
	if (!c.valid()) {
		cout << "Greska! Komentar ne moze biti ispisan..\n";
		return COUT;
	}
	cout << "Komentar od " << c.k.getIme() << " " << c.k.getPrezime() << ": " << c._tekst << endl;
	cout << "Datum i vrijeme: " << c._datum << ", ";
	c._vrijeme.Info(true);
	return COUT;
}