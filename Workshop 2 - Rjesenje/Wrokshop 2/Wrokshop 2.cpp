#pragma once
#include "pch.h"
/* Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene članaka među korisnicima.

Izdvojene su sljedeće funkcionalnosti: - Administrator sistema je zadužen za upravljanje korisničkim nalozima
(Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) može sadržavati više tagova, ali pripada samo jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar (Tekst, Datum, Popularnost) na određeni članak.

 Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima i/ili funkcijama. */
using namespace std;

void main() {
	Administrator admin("Fahir", "Mumdzic", Login("fahirmdz", "admin123"));
	KnowledgeExchange portalZnanja("-------Knowledge exchange BiH-------", admin);
	cout << "Portal znanja '" << portalZnanja.getName() << "'\n--------DOBRO DOSLI---------\n\n";
	int x;
	do {
		do {
			cout << "1 - Administratorski odjel\n";
			cout << "2 - Korisnicki odjel\n";
			cout << "0 - EXIT\n";
			cout << "Vas izbor: ";
			cin >> x;
			if (x < 0 || x>2)
				cout << "Greska! Odabrana opcija ne postoji! Ponovite unos..\n";
		} while ((x < 0 || x>2) && x != 0);
		cin.ignore();
		if (x == 1)
			portalZnanja.adminSector();
		else if (x == 2)
			portalZnanja.userSector();
		else {
			cout << "\nHVALA NA KORISTENJU NASEG PORTALA!\n";
			break;
		}
	} while (x != 0);
}
