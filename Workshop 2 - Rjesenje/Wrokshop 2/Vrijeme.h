#pragma once
#include<iostream>
#include "Administrator.h"

using namespace std;

class Vrijeme {
private:
	int _sati;
	int _minute;
	int _sekunde;
public:

	Vrijeme();
	Vrijeme(int, int, int);
	Vrijeme(int, int);
	Vrijeme(const Vrijeme&);
	Vrijeme& operator=(const Vrijeme&);
	bool valid()const;

	void Info(bool)const;

	int convertToSec(const Vrijeme&)const;
	Vrijeme& correctFormat(Vrijeme&);
	Vrijeme Add(const Vrijeme&);
	Vrijeme Add(int);
	int CompareTo(const Vrijeme&);

	friend class Administrator;
};