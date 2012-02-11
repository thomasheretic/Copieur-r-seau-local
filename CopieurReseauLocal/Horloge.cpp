#include "Horloge.h"

Horloge* Horloge::singleton=0;



Horloge::Horloge()
{
    raffraichissement();
}



Horloge* Horloge::getInstance()
{
    if(singleton==0)
        singleton=new Horloge();

    return singleton;
}

Horloge* Horloge::destruction()
{
    if(singleton!=0)
        delete singleton;
    return singleton;
}

void Horloge::raffraichissement()
{
    secondes=time(NULL);
}

bool Horloge::timerInferieurHorloge(time_t& timer)
{
	if(timer<secondes)
		return true;
	return false;
}

void Horloge::horlogePlusDelai(time_t& timer, const int& delai)
{
	timer=secondes+delai;
}