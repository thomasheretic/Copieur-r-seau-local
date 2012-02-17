#pragma once


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <ctime>
#include "Convertisseur.h"
#include "Horloge.h"
#include "Debug.h"
#include "Transfert.h"
using namespace std;


static const char fichierTelechargements[]="Telechargements.txt";


//bool Device::lock()
//{
//	DWORD dwWaitResult = WaitForSingleObject(mutex, INFINITE);
//   switch (dwWaitResult)  {
//		// The thread got ownership of the mutex
//      case WAIT_OBJECT_0:
//			return true;
//      case WAIT_ABANDONED: 
//          return FALSE; 
//    }
//	 return false;
//}
//bool Device::unlock()
//{
//	ReleaseMutex(mutex);
//	return true;
//}




class GestionnaireTelechargement
{
	static GestionnaireTelechargement* _singleton;

	Debug* debug;

	Horloge* horloge;
	char* buffer;

	map<string,list<Transfert>> telechargements;

	time_t timestampRaffraichissementFichier;
	time_t timestampVitesse;


	GestionnaireTelechargement();
	~GestionnaireTelechargement();

public:
	
	static GestionnaireTelechargement* getInstance();
	static GestionnaireTelechargement* destruction();

	bool sauvegardeFichier();
	void nouveauTelechargement(string& lien);
	bool update();
};

