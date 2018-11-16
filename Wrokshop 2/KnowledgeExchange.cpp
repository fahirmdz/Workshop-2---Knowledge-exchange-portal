#pragma once
#include"pch.h"
#include "Korisnik.h"
#include "Vrijeme.h"
#include "Komentar.h"
#include "Clanak.h"
#include<conio.h>
#include<cstdlib>
using namespace std;

const char* _oblasti1[] = { "IT","Hardware","Software","IoT","AI" };
KnowledgeExchange::KnowledgeExchange() :_appName(nullptr), _korisnici(nullptr), _clanci(nullptr), brKorisnika(0), brClanaka(0) {}
KnowledgeExchange::KnowledgeExchange(const char *appName, Administrator a) : _appName(AlocirajNizKaraktera(appName)),
admin(a), _korisnici(nullptr), _clanci(nullptr), brKorisnika(0), brClanaka(0) {}
KnowledgeExchange::KnowledgeExchange(const KnowledgeExchange& k) : _appName(AlocirajNizKaraktera(k._appName)), admin(k.admin), brKorisnika(k.brKorisnika), brClanaka(k.brClanaka) {
	if (brKorisnika > 0) {
		_korisnici = new Korisnik[brKorisnika];
		for (int i = 0; i < brKorisnika; i++)
			_korisnici[i] = k._korisnici[i];
	}
	else
		_korisnici = nullptr;
	if (brClanaka > 0) {
		_clanci = new Clanak[brClanaka];
		for (int i = 0; i < brClanaka; i++)
			_clanci[i] = k._clanci[i];
	}
	else
		_clanci = nullptr;
}
KnowledgeExchange::~KnowledgeExchange() {
	delete[] _appName; _appName = nullptr;
	delete[] _korisnici; _korisnici = nullptr;
	delete[] _clanci; _clanci = nullptr;
}

KnowledgeExchange& KnowledgeExchange::operator+=(const Korisnik& k) {
	if (!k.valid())
		return *this;
	if (brKorisnika > 0)
		for (int i = 0; i < brKorisnika; i++)
			if (_korisnici[i] == k) {
				cout << "Korisnik vec postoji..\n";
				return *this;
			}
	Korisnik *temp = new Korisnik[brKorisnika + 1];
	if (brKorisnika > 0)
		for (int i = 0; i < brKorisnika; i++)
			temp[i] = _korisnici[i];
	delete[] _korisnici;
	_korisnici = temp;
	_korisnici[brKorisnika++] = k;
	cout << "Uspjesna registracija..\n";
	return *this;
}
KnowledgeExchange& KnowledgeExchange::operator+=(const Clanak& c) {
	if (!c.valid())
		return *this;
	Clanak *temp = new Clanak[brClanaka + 1];
	if (brClanaka > 0)
		for (int i = 0; i < brClanaka; i++)
			temp[i] = _clanci[i];
	delete[] _clanci;
	_clanci = temp;
	_clanci[brClanaka++] = c;
	cout << "Uspjesno dodan clanak..\n";
	return *this;
}
KnowledgeExchange& KnowledgeExchange::operator-=(const Korisnik& k) {
	if (!k.valid() || brKorisnika <= 0 || _korisnici == nullptr)
		return *this;
	int temp;
		for (int i = 0; i < brKorisnika; i++)
			if (k == _korisnici[i])
				temp = i;
	if (brClanaka > 0 && _clanci != nullptr)
		for (int i = 0; i < brClanaka; i++)
			if (_clanci[i].getAutor() == k)
				*this -= _clanci[i];
	for (int i = temp; i < brKorisnika - 1; i++)
		_korisnici[i] = _korisnici[i + 1];
	brKorisnika--;
	return *this;
}
KnowledgeExchange& KnowledgeExchange::operator-=(const Clanak& c) {
	if (!c.valid() || brClanaka <= 0 || _clanci == nullptr)
		return *this;
	int temp;
	for (int i = 0; i < brClanaka; i++)
		if (c == _clanci[i])
			temp = i;
	for (int i = temp; i < brClanaka - 1; i++)
		_clanci[i] = _clanci[i + 1];
	brClanaka--;
	return *this;
}
bool KnowledgeExchange::prikaziClanke(const Korisnik& k,int p) {
	if (brClanaka <= 0) {
		cout << "Trenutno nema clanaka na portalu..\n";
		return false;
	}
	for (int i = 0; i < brClanaka; i++)
		cout <<i+1<< _clanci[i].getNaslov()<<" - Autor: "<<_clanci[i].getAutor().getIme()<<" "<< _clanci[i].getAutor().getPrezime()<< endl;
	int x;
	do {
		cout << "Unesite redni broj clanka koji zelite da otvorite (0-EXIT): ";
		cin >> x;
		if(x<0 || x>brClanaka)
			cout<<"Unijeli ste pogresan redni broj.. Ponovite unos!\n";
	}while((x<0 || x>brClanaka) && x!=0);
	_clanci[x - 1].uvecajPreglede(1);
	cout << _clanci[x - 1] << endl;
	int z;
	do {
		cout << "Da li zelite dodati komentar na ovaj clanak (1-DA,2-NE): ";
		cin >> z;
		if (z < 1 || z>2)
			cout << "Greska! Nista unijeli ispravnu vrijednost!\n";
	} while (z < 1 || z>2);
	cin.ignore();
	if (z == 1) {
		char *komentar = new char[100];
		cout << "\nUnesite sadrzaj komentara: ";
		cin.getline(komentar, 100);
		char *datum = new char[12];
		cout << "Datum: ";
		cin.getline(datum, 12);
		int s, m;
		cout << "Vrijeme (ss:mm): ";
		cin >> s >> m;
		Komentar comment(k, komentar, datum, Medium, Vrijeme(s, m));
		cin.ignore();
		_clanci[x - 1] +=comment;
		cout << "\nKomentar uspjesno dodan..\n";
		delete[] komentar; 
		delete[] datum;
		komentar = datum = nullptr;
	}
	return true;
}
bool KnowledgeExchange::prikaziClanke(const Korisnik& k) {
	if (brKorisnika <= 0) {
		cout << "Trenutno nema korisnika na portalu..\n";
		return false;
	}
	if (brClanaka <= 0)
	{
		cout << "Trenutno nema clanaka na portalu..\n";
		return false;
	}
	for (int i = 0; i < brClanaka; i++)
		cout << i + 1 << ". -> Naslov: " << _clanci[i].getNaslov() << " - Autor: " << _clanci[i].getAutor().getIme() << " " << _clanci[i].getAutor().getPrezime() << endl;
	return true;
}
char* KnowledgeExchange::inputPassword(){
	int x = 0;
	char k;
	char *pw = new char[12];
	while (x < 11) {
		k = _getch();
		if (k != 13) {
			pw[x++] = k;
			cout << "*";
		}
		else
			break;
	}
	pw[11] = '\0';
	return pw;
}


Clanak* KnowledgeExchange::createClanak(const Korisnik& k) {
	char *naziv, *sadrzaj, *datum;
	naziv = new char[40];
	sadrzaj = new char[255];
	datum = new char[12];
	Oblasti _oblast;
	int brt;
	cout << "--Kreiranje novog clanka--\n";
	cout << "Unesite naziv clanka: ";
	cin.getline(naziv, 40);
	cout << "Odaberite neku od oblasti o kojoj zelite pisati: \n ";
	for (int i = 0; i < 5; i++)
		cout <<i+1<<". ->"<< *_oblasti1[i] << endl;
	int z;
	do {
		cout << "Vas izbor (1-5): ";
		cin >> z;
		if (z < 1 || z>5)
			cout << "Greska! Unijeli ste pogresan redni broj..\n";
	} while (z < 1 || z>5);
	cin.ignore();
	_oblast = Oblasti(z - 1);
	cout << "Unesite sadrzaj vaseg clanka: ";
	cin.getline(sadrzaj, 255);
	cin.ignore();

	cout << "Datum kreiranja: ";
	cin.getline(datum, 12);
	int s, m;
	cout << "Vrijeme kreiranja (sati:minuti): ";
	cin >> s >> m;
	Vrijeme v(s, m);
	cin.ignore();

	Clanak *_clanak=new Clanak(k, v, _oblast, naziv, sadrzaj, datum, 0);
	do {
		cout << "Koliko tagova zelite postaviti (0-10): ";
		cin >> brt;
		if (brt < 0 || brt>10)
			cout << "Greska! Ponovite unos..\n";
	} while (brt < 0 || brt>10);
	cin.ignore();

	if (brt > 0)
		for (int i = 0; i < brt; i++) {
			char *tag = new char[20];
			cout << "Sadrzaj tag-a: ";
			cin.getline(tag, 20);
			*_clanak += tag;
			delete[] tag;
		}
	if (_clanak->valid())
		return _clanak;
	else
		return nullptr;
}
char *KnowledgeExchange::getName()const { return AlocirajNizKaraktera(_appName); }

void KnowledgeExchange::adminSector() {
	int x;
	bool prijavljen = false;
	cout << "--Admin login--\n";
	char *username;
	char *pass;
	do {
		username = new char[20];
		cout << "Username: ";
		cin.getline(username, 20);
		cout << "Password: ";
		pass = inputPassword();
		Login l1(username, pass);
		if (l1 == admin.getLogin())
			prijavljen = true;
		if (!prijavljen) {
			cout << "Greska! Unijeli ste pogresan username ili password!\n";
			int z;
			do {
				cout << "1 - pokusaj opet\n2 - EXIT\nVas izbor: ";
				cin >> z;
				if (z < 1 || z>2)
					cout << "Greska! Pogresan redni broj..\n";
			} while (z < 1 || z>2);
			cin.ignore();
			if (z == 2)
				break;
			delete[] username; username = nullptr;
			delete[] pass; pass = nullptr;
			l1.~Login();
		}
	} while (!prijavljen);
	system("PAUSE");
	system("cls");
	if (prijavljen) {
		cout << "-> Uspjesno ste se prijavili!\n\n";
		do {
			cout << "---Dobrodosli u administratorski meni----\n\n";
			cout << "1 - Ban/Ukloni odrijedjenog korisnika\n";
			cout << "2 - Ukloni odrijedjeni clanak\n";
			cout << "3 - Ukloni komentar sa odrijedjenog clanka\n";
			cout << "0 - EXIT\n";
			do {
				cout << "--------------------\nVas izbor: ";
				cin >> x;
				if (x < 0 || x>3)
					cout << "Greska! Opcija ne postoji..\n";
				if (x == 0)
					cout << "Hvala na posjeti!\n";
			} while ((x < 0 || x>3) && x != 0);
			cin.ignore();

			if (x == 1) {
				int z = -1;
				if (brKorisnika <= 0)
					cout << "Trenutno nema registrovanih korisnika..\n";
				else {
					for (int i = 0; i < brKorisnika; i++)
						cout << i + 1 << ". " << _korisnici[i].getIme() << " " << _korisnici[i].getPrezime() << " - Username: " << _korisnici[i].getLogin().getUsername() << endl;
					do {
						cout << "Unesite redni broj korisnika kojeg zelite ukloniti sa portala (0 - EXIT): ";
						cin >> z;
						if (z<1 || z>brKorisnika)
							cout << "Greska! Unijeli ste pogresan redni broj..Ponovite unos!\n";
					} while ((z<1 || z>brKorisnika) && z != 0);
					cin.ignore();

					if (z > 0) {
						(*this) -= _korisnici[z - 1];
						cout << "Korisnik uspjesno uklonjen..\n";
					}
				}
			}
			else if (x == 3 || x == 2) {
				if (brClanaka <= 0)
					cout << "Trenutno nema clanaka..\n";
				else {
					for (int i = 0; i < brClanaka; i++)
						cout << i + 1 << ". " << _clanci[i].getNaslov() << " - Autor: " << _clanci[i].getAutor().getIme() << " " << _clanci[i].getAutor().getPrezime() << endl;
					int z;
					do {
						cout << "Unesite redni broj clanka: ";
						cin >> z;
						if (z<1 || z>brClanaka)
							cout << "Greska! Unijeli ste neispravan redni broj..\n";

					} while ((z<1 || z>brClanaka) && z != 0);
					cin.ignore();

					if (x == 2)
						(*this) -= _clanci[z - 1];
					else {
						if (_clanci[z - 1].getBrojKomentara() <= 0)
							cout << "Trenutno nema komentara na ovom clanku..\n";
						else {
							_clanci[z - 1].printKomentare();
							int t;
							do {
								cout << "Unesite redni broj komentara koji zelite ukloniti (0-EXIT): ";
								cin >> t;
								if (t<0 || t>_clanci[z - 1].getBrojKomentara())
									cout << "Greska! Unijeli ste pogresan redni broj.. Ponovite unos!\n";
							} while ((t<0 || t>_clanci[z - 1].getBrojKomentara()) && t != 0);
							cin.ignore();
							_clanci[z - 1] -= (t - 1);
						}
					}
				}
			}
			system("PAUSE");
			system("cls");
		} while (x != 0);
	}
	else
		cout << "\nPrijava nije uspjela!\n";
}
void KnowledgeExchange::userSector() {
	int x = -1;
	Korisnik *_user = portalLogin();
	if (_user != nullptr) {
		do {
			system("PAUSE");
			system("cls");
			cout << "---Dobrodosli u korisnicki meni---\n\n";
			cout << "1 - Dodaj clanak\n";
			cout << "2 - Izbrisi clanak\n";
			cout << "3 - Dodaj tag na svoj clanak\n";
			cout << "4 - prikazi sve clanke\n";
			cout << "5 - prikaze moje clanke\n";
			cout << "6 - promijeni korisnicko ime\n";
			cout << "7 - promijeni lozinku\n";
			cout << "0 - EXIT\n";
			do {
				cout << "Vas izbor: ";
				cin >> x;
				if (x < 0 || x>7)
					cout << "Trazena opcija ne postoji.. Ponovite unos!\n";
				if (x == 0)
					cout << "Hvala na koristenju naseg portala!\n\n";
			} while ((x < 0 || x>7) && x != 0);
			cin.ignore();
			if (x == 1) {
				cout << "--Dodavanje novog clanka--\n\n";
				Clanak *_clanak = createClanak(*_user);
				if (_clanak != nullptr) {
					(*this) += *_clanak;
					cout << "Uspjesno ste dodali clanak..\n";
				}
				else
					cout << "Zao nam je, dodavanje clanka nije uspjelo..\n";
			}
			else if (x == 2) {
				if (prikaziClanke(*_user)) {
					int z;
					do {
						cout << "Unesite redni broj clanka koji zelite ukloniti (0-EXIT): ";
						cin >> z;
						if (z<0 || z>brClanaka)
							cout << "Greska! Clanak sa rednim brojem koji ste unijeli ne postoji!\n";
					} while ((z<0 || z>brClanaka) && z != 0);
					cin.ignore();
					if (z != 0) {
						(*this) -= _clanci[z - 1];
						cout << "Clanak uspjesno uklonjen..\n";
					}
				}
			}
			else if (x == 3) {
				if (prikaziClanke(*_user)) {
					int z;
					do {
						cout << "Unesite redni broj clanka na koji zelite dodati tag (0-EXIT): ";
						cin >> z;
						if (z<0 || z>brClanaka)
							cout << "Greska! Clanak sa rednim brojem koji ste unijeli ne postoji!\n";
					} while ((z<0 || z>brClanaka) && z != 0);
					cin.ignore();
					if (z != 0) {
						char *tag = new char[20];
						cout << "Sadrzaj tag-a: ";
						cin.getline(tag, 20);
						_clanci[z - 1] += tag;
						delete[] tag;
						cout << "Tag uspjesno dodan..\n";
					}
				}
				else
					cout << "Neuspjesno dodavanje taga..\n";
			}
			else if (x == 4)
				prikaziClanke(*_user,1);
			else if (x == 5)
				prikaziClanke(*_user);

			else if (x == 6) {
				char *user;
				int flag = 0;
				do {
					user= new char[20];
					cout << "Unesite zeljeni username: ";
					cin.getline(user, 20);
					if (!checkUsername(user)) {
						cout << "Username koji ste unijeli vec postoji.. Ponovite unos!\n";
						flag = 1;
						delete[] user;
					}
				} while (flag == 1);
				cin.ignore();
				_user->changeUsername(user);
				cout << "Username uspjesno promijenjen..\n";
			}
			else if (x == 7) {
				cout << "Unesite zeljeni password: ";
				char *pw = inputPassword();
				_user->changePassword(pw);
				cout << _user->getLogin() << endl;
				cout << "Password uspjesno promijenjen..\n";
			}
			else {
				cout << "Neuspjesna prijava.. Zao nam je.\n";
				return;
			}
			system("PAUSE");
			system("cls");
		} while (x != 0);
	}
}
Korisnik* KnowledgeExchange::logovanje() {
	if (brKorisnika <= 0) {
		cout << "Trenutno nema registrovanih korisnika..\n\n";
		int l;
		do {
			cout << "Ako se zelite registrovati unesite broj 1 (0-EXIT): ";
			cin >> l;
			if (l != 0 && l != 1)
				cout << "Greska! Trazena opcijane postoji.. Ponovite unos!\n";
		} while (l != 0 && l != 1);
		if (l == 0)
			return nullptr;
		else
			return registracija();

	}
	char *user , *pw=nullptr;
	int trazeni = -1, brPokusaja = 0;
	cout << "---Odjel prijavljivanja--\n\n";
	do {
		if (brPokusaja >= 3)
			cout << "Zao nam je, prekoracili ste broj pokusaja prijavljivanja! Pokusajte kasnije..\n";
		else {
			user = new char[15];
			cout << "Username: ";
			cin.getline(user, 15);
			cout << "Lozinka: ";
			pw = inputPassword();
			brPokusaja++;
			Login temp(user, pw);
			for (int i = 0; i < brKorisnika; i++)
				if (_korisnici[i].getLogin() == temp)
					trazeni = i;
			if (trazeni == -1) {
				delete[] user; user = nullptr;
				delete[] pw; pw = nullptr;
				cout << "Pogresan username ili password! Ponovite unos.\n";
			}

		}
	} while (trazeni == -1 && brPokusaja < 3);
	if (trazeni >= 0)
		if (pw != nullptr && strcmp(_korisnici[trazeni].getLogin().getPassword(), pw) == 0) {
			cout << "\nUspjesno ste se prijavili!\n";
			return &_korisnici[trazeni];
		}
	return nullptr;
}
bool KnowledgeExchange::checkUsername(const char *user) {
	if (brKorisnika>0)
		for(int i=0;i<brKorisnika;i++)
			if(strcmp(_korisnici[i].getLogin().getUsername(),user)==0)
				return false;
	return true;
}
Korisnik* KnowledgeExchange::registracija() {
	char *_ime, *_prezime, *_email, *_datumRegistracije;
	char *user, *pw;
	_ime = new char[15], _prezime = new char[15], _email = new char[50], _datumRegistracije = new char[12], user = new char[10], pw = new char[12];
	cout << "--Odjel registracije--\n";
	cin.ignore();
	cout << "Ime: ";
	cin.getline(_ime, 15);
	cout << "Prezime: ";
	cin.getline(_prezime, 15);
	cin.ignore();

	int flag = 0;
	do {
		cout << "E-mail: ";
		cin.getline(_email, 50);
		if (brKorisnika > 0)
			for (int i = 0; i < brKorisnika; i++)
				if (strcmp(_korisnici[i].getEmail(), _email) == 0) {
					flag = 1;
					cout << "E-mail koji ste unijeli je vec u upotrebi!\n";
					delete[] _email;
					_email = nullptr;
				}
	} while (flag == 1);
	cout << "Datum registracije: ";
	cin.getline(_datumRegistracije, 12);
	flag = 0;
	do {
		cout << "\nZeljeni username: ";
		cin.getline(user, 10);
		if (brKorisnika > 0)
			if (!checkUsername(user)) {
				cout << "Zeljeni username je vec u upoterbi! Zao nam je. Ponovite unos.\n";
				delete[] user;
				user = nullptr;
				flag = 1;
			}
	} while (flag == 1);
	cin.ignore();
	//----PASSWORD--------

	cout << "Unesite lozinku (11 karaktera max): ";
	pw = inputPassword();
	//---------------------
	Login log(user, pw);
	Korisnik novi(_ime, _prezime, _email, _datumRegistracije, log);
	if (novi.valid()) {
		(*this) += novi;
		cin.ignore();
		return &_korisnici[brKorisnika - 1];
	}
	else {
		cout << "Registracija neuspjesna!\n";
		cin.ignore();
		return nullptr;
	}
}
Korisnik* KnowledgeExchange::portalLogin() {
	cout << "---Dobrodosli na portal za razmjenu znanja---\n\n";
	int x;
	do {
		cout << "1 - Log In\n";
		cout << "2 - Registracija\n";
		cout << "0 - EXIT\n\n";

		cout << "Vas izbor: ";
		cin >> x;
		if (x != 1 && x != 2 && x != 0)
			cout << "Greska! Odaberite neku od ponudjenih opcija!\n";
	} while (x != 0 && x != 2 && x != 1);
	cin.ignore();
	if (x == 2)
		return registracija();
	else if (x == 1)
		return logovanje();

	return 0;
}