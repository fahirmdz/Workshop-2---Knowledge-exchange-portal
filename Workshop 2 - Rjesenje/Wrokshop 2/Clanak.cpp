#include"pch.h"
#include "Clanak.h"

enum Oblasti { IT, Hardware, Software, IoT, AI };
const char*_oblasti2[] = { "IT","Hardware","Software","IoT","AI" };
Clanak::Clanak() :_naslov(nullptr), _sadrzaj(nullptr), _datum(nullptr), _komentari(nullptr),
brojKomentara(0), brojPregleda(0), _brojTagova(0) {}
Clanak::Clanak(Korisnik _user, Vrijeme v, Oblasti o, const char* naslov, const char *sadrzaj, const char *datum, int brTagova) :
	_korisnik(_user), _satnica(v), _oblast(o), _naslov(AlocirajNizKaraktera(naslov)), _sadrzaj(AlocirajNizKaraktera(sadrzaj)), _datum(AlocirajNizKaraktera(datum)),
	_brojTagova(brTagova), _komentari(nullptr), brojPregleda(0), brojKomentara(0) {}
Clanak::Clanak(const Clanak& c) :_korisnik(c._korisnik), _naslov(AlocirajNizKaraktera(c._naslov)), _sadrzaj(AlocirajNizKaraktera(c._sadrzaj)),
_datum(AlocirajNizKaraktera(c._datum)), _satnica(c._satnica), _oblast(c._oblast), brojPregleda(c.brojPregleda), brojKomentara(c.brojKomentara),
_brojTagova(c._brojTagova)
{
	if (_brojTagova > 0)
		for (int i = 0; i < _brojTagova; i++)
			_tagovi[i] = AlocirajNizKaraktera(c._tagovi[i]);
	if (brojKomentara > 0) {
		_komentari = new Komentar[brojKomentara];
		for (int i = 0; i < brojKomentara; i++)
			_komentari[i] = c._komentari[i];
	}
}
Clanak::~Clanak() {
	delete[] _naslov, _sadrzaj, _datum;
	_naslov = _sadrzaj = _datum = nullptr;
	if (_brojTagova > 0)
		for (int i = 0; i < _brojTagova; i++) {
			delete[] _tagovi[i];
			_tagovi[i] = nullptr;
		}
	delete[] _komentari;
	_komentari = nullptr;
}
bool Clanak::valid()const { return _satnica.valid() && _naslov != nullptr && _datum != nullptr && _sadrzaj != nullptr;  }
Clanak& Clanak::operator=(const Clanak& c) {
	if (&c != this) {
		delete[] _naslov, _sadrzaj, _datum;
		delete[] _komentari;
		_korisnik = c._korisnik;
		_naslov = AlocirajNizKaraktera(c._naslov);
		_sadrzaj = AlocirajNizKaraktera(c._sadrzaj);
		_datum = AlocirajNizKaraktera(c._datum);
		_brojTagova = c._brojTagova;
		brojKomentara = c.brojKomentara;
		brojPregleda = c.brojPregleda;
		_oblast = c._oblast;
		if (_brojTagova > 0)
			for (int i = 0; i < _brojTagova; i++)
				_tagovi[i] = AlocirajNizKaraktera(c._tagovi[i]);
		if (brojKomentara > 0)
		{
			_komentari = new Komentar[brojKomentara];
			for (int i = 0; i < brojKomentara; i++)
				_komentari[i] = c._komentari[i];
		}
	}
	return *this;
}

Clanak& Clanak::operator+=(const Komentar& c) {
	if (c.valid()) {
		Komentar *temp = new Komentar[brojKomentara + 1];
		for (int i = 0; i < brojKomentara; i++)
			temp[i] = _komentari[i];
		delete[] _komentari;
		temp[brojKomentara++] = c;
		_komentari = temp;
	}
	return *this;
}

Clanak& Clanak::operator+=(const char* c) {
	if (_brojTagova == 10)
		return *this;
	_tagovi[_brojTagova++] = AlocirajNizKaraktera(c);
	return *this;
}

Clanak& Clanak::operator-=(int x) {
	if (x<0 || x>brojKomentara - 1 || brojKomentara <= 0)
		return *this;
	int trazeni = -1;
	for (int i = 0; i < brojKomentara; i++)
		if (_komentari[i] == _komentari[x])
			trazeni = i;
	if (trazeni == -1)
		return *this;
	for (int i = trazeni; i < brojKomentara - 1; i++)
		_komentari[i] = _komentari[i + 1];
	brojKomentara--;
	return *this;

}
void  Clanak::uvecajPreglede(int p) { brojPregleda++; }
char* Clanak::getNaslov()const { return AlocirajNizKaraktera(_naslov); }

char *Clanak::getDatum()const { return AlocirajNizKaraktera(_datum); }

Vrijeme Clanak::getVrijeme()const { return _satnica; }

int Clanak::getBrojKomentara()const { return brojKomentara; }

int Clanak::getBrojTagova()const { return _brojTagova; }

int Clanak::getBrojPregleda()const { return brojPregleda; }

Korisnik Clanak::getAutor()const { return _korisnik; }

bool Clanak::valid() { return !(!_korisnik.valid() || _sadrzaj == nullptr || _datum == nullptr || _naslov == nullptr); }
bool Clanak::tagCompare(const char *tag) {
	if (_brojTagova <= 0)
		return false;
	for (int i = 0; i < _brojTagova; i++)
		if (strcmp(_tagovi[i], tag) == 0)
			return true;
	return false;
}

void Clanak::printKomentare()const {
	if (brojKomentara <= 0 || _komentari == nullptr)
		return;
	cout << "--KOMENTARI--\n";
	for (int i = 0; i < brojKomentara; i++)
		cout << i + 1 << ". " << _komentari[i] << endl;
}


bool operator==(const Clanak& c1, const Clanak& c2) {
	return (strcmp(c1._sadrzaj, c2._sadrzaj) == 0) && (strcmp(c1._naslov, c2._naslov) == 0) && c1._korisnik == c2._korisnik;
}

ostream& operator<<(ostream& COUT, const Clanak& c) {
	if (!c.valid())
		return COUT;
	cout << "\n---Naslov: " << c._naslov << "----\n";
	cout << "Autor --> " << c._korisnik.getIme() << " " << c._korisnik.getPrezime() << "\nDatum i vrijeme objave: " << c._datum << ", ";
	c._satnica.Info(true);
	cout << "\nOblast: " << _oblasti2[c._oblast] << "\nTagovi: ";
	if (c._brojTagova <= 0)
		cout << "NEMA\n";
	else
		for (int i = 0; i < c._brojTagova; i++)
			cout << "#" << c._tagovi[i] << ",  ";
	cout << "Sadrzaj: " << c._sadrzaj << endl;
	cout << "----------------------------------------------------\n---------Komentari----------\n";
	if (c.brojKomentara <= 0)
		cout << "--NEMA--\n";
	else
		for (int i = 0; i < c.brojKomentara; i++)
			cout << c._komentari[i] << endl;
	cout << "Broj pregleda: " << c.brojPregleda << endl;
	return COUT;
}