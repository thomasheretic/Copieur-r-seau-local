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
using namespace std;

static const int delaiSecondes = 60;
static const int periodeRaffraichissementFichierSeconde = 1;
static int tailleBuffer=20000; // en octet
static const unsigned int nombreFichierParServer = 1;

static unsigned int nombreFiltre = 10;


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


long GetFileSize( std::ifstream &  fichier );
//
//
//enum EtatTelechargement 
//{
//	TELECHARGEMENT_EN_ATTENTE,
//	TELECHARGEMENT_EN_COURS
//};




class Transfert 
{
public:
	unsigned char erreurCpt;

	string lien;
	string outFileName;
	long taille;
	float vitessekoParSeconde;
	list<float> vitesses;

	int progressionPourcent;
	long positionCourante;
	long dernierePosition;

	time_t delaiAttenteReprise;

	//EtatTelechargement etatTelechargement ;

	Transfert(string& lien)
	{
		positionCourante = 0;
		dernierePosition = 0;
		this->lien=lien;
		ifstream fichier(lien.c_str(),ios::binary);
		this->taille=GetFileSize(fichier);
		Debug::getInstance()->print("Taille du fichier="+toString(taille));
		fichier.close();

		this->vitessekoParSeconde=0;
		this->progressionPourcent=0;

		int posFound = 0; // Récupération du niom du fichier
		int posRemembered;
		while ((posFound = lien.find("\\",posFound+1))!=string::npos) 
			posRemembered=posFound;
		outFileName=lien.substr(posRemembered+1);

		//ofstream out(outFileName.c_str());
		//out.close();
		delaiAttenteReprise=0;
		erreurCpt=0;
		//etatTelechargement=TELECHARGEMENT_EN_ATTENTE;
	}

	Transfert(string& lien, long taille, float vitesse, int progression, string& outName, long position) 
	{
		this->lien=lien;
		this->taille=taille;
		this->vitessekoParSeconde=vitesse;
		this->progressionPourcent=progression;
		this->outFileName=outName;
		this->positionCourante=position;
		this->dernierePosition=position;
		this->delaiAttenteReprise=0;
		//etatTelechargement=TELECHARGEMENT_EN_ATTENTE;
		erreurCpt=0;
	}
	
	void setDelai() {
		Horloge::getInstance()->horlogePlusDelai(delaiAttenteReprise, delaiSecondes);
	}

	bool isReady() {
		if(delaiAttenteReprise==0)
			return true;
		return Horloge::getInstance()->timerInferieurHorloge(delaiAttenteReprise);
	}
};

