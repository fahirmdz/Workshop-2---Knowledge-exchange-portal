#include"pch.h"
#include "Vrijeme.h"

//Konstruktor bez parametara 
	//Konstruktor sa 3 parametra (sati, minute i sekunde) 
	//Konstruktor sa 2 parametra (sati i minute) 
Vrijeme::Vrijeme() :_sati(0), _minute(0), _sekunde(0) {}
Vrijeme::Vrijeme(int sa, int m, int s) : _sati(sa), _minute(m), _sekunde(s) {}
Vrijeme::Vrijeme(int sa, int m) : _sati(sa), _minute(m), _sekunde(0) {}
Vrijeme::Vrijeme(const Vrijeme& v) : _sati(v._sati), _minute(v._minute), _sekunde(v._sekunde) {}

Vrijeme& Vrijeme::operator=(const Vrijeme &v) {
	_sati = v._sati;
	_minute = v._minute;
	_sekunde = v._sekunde;
	return *this;
}
bool Vrijeme::valid()const {
	return !(_sati > 23 || _sati < 0 || _minute < 0 || _minute>59 || _sekunde < 0 || _sekunde>59);
}
//Funkciju Info sa neobaveznim parametrom tipa bool koji određuje da li će vrijeme biti ispisano u punom formatu 
//(hh:mm:ss) ili u skraćenom formatu (hh:mm). Default-no funkcija vrši ispis u punom formatu. 
void Vrijeme::Info(bool fullFormat = true)const {
	if (_sati / 10 == 0)
		cout << 0;
	cout << _sati << ":";
	if (_minute / 10 == 0)
		cout << 0;
	cout << _minute;
	if (!fullFormat)
		cout << endl;
	else {
		if (_sekunde / 10 == 0)
			cout << 0;
		cout << _sekunde << endl;
	}
}
//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja  
//sumu vremena poslijeđenog kao parametar i instance this. 
int Vrijeme::convertToSec(const Vrijeme& v1)const {
	return v1._sekunde + (v1._minute * 60) + (v1._sati * 60 * 60);
}
Vrijeme& Vrijeme::correctFormat(Vrijeme& v) {
	if (v._sekunde > 59) {
		v._minute += v._sekunde / 60;
		v._sekunde = v._sekunde % 60;
	}
	if (v._minute > 59) {
		v._sati += v._minute / 60;
		v._minute = v._minute % 60;
	}
	if (v._sati > 23)
		v._sati = 0;
	return *this;
}
Vrijeme Vrijeme::Add(const Vrijeme& v) {
	int sati, min, sek;
	int x1 = convertToSec(v), x2 = convertToSec(*this);
	sati = (int)(x1 / 60 / 60) + (int)(x2 / 60 / 60);
	min = (int)((x1 - (sati * 60 * 60)) / 60) + (int)((x2 - (sati * 60 * 60)) / 60);
	sek = (int)(x1 - (x1 - (sati * 60 * 60))) + (int)(x2 - (x2 - (sati * 60 * 60)));
	Vrijeme vTemp(sati, min, sek);
	correctFormat(vTemp);
	return vTemp;
}

//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja  
//sumu parametra izraženog u minutama i vremena instance this. 
Vrijeme Vrijeme::Add(int minute) {
	int sati, min, sek;
	int  x2 = convertToSec(*this);
	sati = (int)(x2 / 60 / 60);
	min = minute + (int)((x2 - (sati * 60 * 60)) / 60);
	sek = (int)(x2 - (x2 - (sati * 60 * 60)));
	Vrijeme vTemp(sati, min, sek);
	correctFormat(vTemp);
	return vTemp;
}

//Funkciju CompareTo koja vraća vrijednost tipa int u zavisnosti od toga da li je vrijeme instance this prije, jednako ili poslije 
//vremena proslijeđenog kao parametar.  //Moguće povratne vrijednosti:  //-1 - vrijeme instance this nastupa prije vremena v2  
// 0 - vrijeme instance this je jednako vremenu v2  // 1 - vrijeme instance this nastupa nakon vremena v2 
int Vrijeme::CompareTo(const Vrijeme& v) {
	if (this->_sati > v._sati)
		return 1;
	else if (this->_sati < v._sati)
		return -1;
	else if (this->_minute > v._minute)
		return 1;
	else if (this->_minute < v._minute)
		return -1;
	else if (this->_sekunde > v._sekunde)
		return 1;
	else if (this->_sekunde < v._sekunde)
		return -1;
	else
		return 0;
}