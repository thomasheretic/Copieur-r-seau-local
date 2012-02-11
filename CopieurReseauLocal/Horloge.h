#pragma once

#include <string>
#include <ctime>
#include <iostream>
using namespace std;



//enum listeHorloge
//{
//    TIMER_AFFICHE=0,
//    TIMER_UPDATE,
//    TIMER_END
//};



/**
* \brief
*/
class Horloge
{
    static Horloge* singleton;

//    int temps[TIMER_END];

    //Le temps quand le timer est lancé
    time_t secondes;
    Horloge();

    public:

    static Horloge* getInstance();
    static Horloge* destruction();

    void raffraichissement();
	bool timerInferieurHorloge(time_t& timer);
	void horlogePlusDelai(time_t& timer, const int& delai);

};




