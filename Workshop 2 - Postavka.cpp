#include<iostream> 

using namespace std;

class Vrijeme {
int _sati;  int _minute;  int _sekunde; public:

	//Konstruktor bez parametara  //Konstruktor sa 3 parametra (sati, minute i sekunde) 
	//Konstruktor sa 2 parametra (sati i minute) 

	//Funkciju Info sa neobaveznim parametrom tipa bool koji odreduje da li ce vrijeme biti ispisano u punom formatu
	//(hh:mm:ss) ili u skracenom formatu (hh:mm). Default-no funkcija vrši ispis u punom formatu. 


	//Funkciju Add koja kao rezultat vraca novi objekat tipa vrijeme koji predstavlja  
	//sumu vremena poslijedenog kao parametar i instance this. 


	//Funkciju Add koja kao rezultat vraca novi objekat tipa vrijeme koji predstavlja  
	//sumu parametra izraženog u minutama i vremena instance this. 


	//Funkciju CompareTo koja vraca vrijednost tipa int u zavisnosti od toga da li je vrijeme instance this prije, jednako ili poslije
	//vremena proslijedenog kao parametar.  //Moguce povratne vrijednosti:  //-1 - vrijeme instance this nastupa prije vremena v2 
	// 0 - vrijeme instance this je jednako vremenu v2  // 1 - vrijeme instance this nastupa nakon vremena v2 

};


/* Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene clanaka medu korisnicima.

Izdvojene su sljedece funkcionalnosti: - Administrator sistema je zadužen za upravljanje korisnickim nalozima 
(Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka). - Svaki clanak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) 
može sadržavati više tagova, ali pripada samo jednoj oblasti. - Clanke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije takoder mogu ostaviti komentar (Tekst, Datum, Popularnost) na odredeni clanak. */

/* Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima i/ili funkcijama. */

class Datum {
int _dan;  
int _mjesec; 
int _godina;

public:  
	
	//Potrebne konstruktor i destruktor funkcije 

//Funkciju Info
}; 

class Korisnik {
	char _ime[30];
	char _korisnickoIme[20];  char* _lozinka;

public:
	//Potrebne konstruktor i destruktor funkcije 

//Funkciju za promjenu korisnicke lozinke 

//Funkciju Info 
};

class Komentar {
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	//Potrebne konstruktor i destruktor funkcije 

//Funkciju za izmjenu popularnosti komentara 

//Funkciju Info 

};

class Clanak {
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
	int _brojKomentara;

public:

	//Funkciju za dodavanje tagova za clanak 
	/*Funkciju za promjenu sadržaja i vremena promjene clanka. Kao verifikaciju dozvole potrebno je
	proslijediti korisnicko ime autora clanka.  Samo kreator clanka ima permisije da mijenja njegov sadržaj.  */

	//Funkciju za dodavanje komentara 

	//Funkciju Info 

};

int main() {

	//Kreirati testni program koji demonstrira implementirane funckionalnosti 


	return 0;
}