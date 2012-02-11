#include "Copieur.h"

GestionnaireTelechargement* GestionnaireTelechargement::_singleton=0;


GestionnaireTelechargement::GestionnaireTelechargement() 
{
	buffer= new char[tailleBuffer];

	debug=Debug::getInstance();
	debug->print("GestionnaireTelechargement constructor");

	horloge=Horloge::getInstance();
	timestampRaffraichissementFichier=0;

	ifstream fichier (fichierTelechargements);
	if(fichier.fail()) {
		debug->print("Le fichier de Telechargements n'a pas ete trouve. Creation du fichier.");
		fichier.close();
		ofstream out(fichierTelechargements);
		out.close();
		return;
	}

	string ligne, lien, outFileName, taille, vitessekoParSeconde, progressionPourcent, positionCourante;
	while (getline(fichier,ligne)) {
		stringstream ss(ligne);
		getline(ss,lien,';');
		getline(ss,taille,';');
		getline(ss,vitessekoParSeconde,';');
		getline(ss,progressionPourcent,';');
		getline(ss,outFileName,';');
		getline(ss,positionCourante,';');

		Transfert f(lien,stringToLong(taille),stringToFloat(vitessekoParSeconde),stringToInt(progressionPourcent),outFileName,stringToLong(positionCourante));		

		string server = getServerName(lien);
		map<string,list<Transfert>>::iterator it = telechargements.find(server);
		if(it==telechargements.end()) {
			debug->print("Telechargement nouveau serveur.");
			list<Transfert> nouveauVecteur;
			nouveauVecteur.push_back(f);
			telechargements.insert(pair<string,list<Transfert>>(server, nouveauVecteur));
		}
		else {
			bool found=false;
			for(list<Transfert>::iterator itTransferts=it->second.begin();itTransferts!=it->second.end();itTransferts++) {
				if(itTransferts->lien.compare(lien)==0) {
					found=true;
					debug->print("Le lien "+itTransferts->lien+" existe deja.");
				}
			}
			if(found==false) {
				it->second.push_back(f);
				debug->print("Creation d'un nouveau Telechergement sur un serveur existant.");
			}
		}
	}

	fichier.close();
}

bool GestionnaireTelechargement::sauvegardeFichier()
{
	ofstream fichier(fichierTelechargements);
	if(fichier.fail()) {
		debug->print("Impossible de sauvegarder les telechargements.");
		return false;
	}

	for (map<string,list<Transfert>>::iterator itServeurs=telechargements.begin();itServeurs!=telechargements.end();itServeurs++) {
		for(list<Transfert>::iterator itTransfert=itServeurs->second.begin();itTransfert!=itServeurs->second.end();itTransfert++) {
			fichier << itTransfert->lien << ";" << itTransfert->taille << ";" << ((int)(itTransfert->vitessekoParSeconde)) << ";"
				<< itTransfert->progressionPourcent << ";" << itTransfert->outFileName << ";"
				<< itTransfert->positionCourante << endl;
		}
	}
	fichier.close();
	return true;
}



GestionnaireTelechargement::~GestionnaireTelechargement() 
{
	delete [] buffer;
	debug->print("Liberation du buffer d'entree-sortie.");
	sauvegardeFichier();
	debug->print("GestionnaireTelechargement destructor");
	debug=Debug::destruction();
}



GestionnaireTelechargement* GestionnaireTelechargement::getInstance()
{	
	if(_singleton==0) {
		_singleton=new GestionnaireTelechargement();
	}
	return _singleton;
}

GestionnaireTelechargement* GestionnaireTelechargement::destruction()
{
	if(_singleton) {
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}


void GestionnaireTelechargement::nouveauTelechargement(string& lien) 
{
	Transfert f(lien);

	string server = getServerName(lien);
	debug->print("Serveur=["+server+"] trouve pour le lien "+lien);
	map<string,list<Transfert>>::iterator it = telechargements.find(server);
	if(it==telechargements.end()) {
		list<Transfert> nouveauVecteur;
		nouveauVecteur.push_back(f);
		telechargements.insert(pair<string,list<Transfert>>(server, nouveauVecteur));
		debug->print("Insertion d'une pair Serveur-lien.");
	}
	else {
		bool found=false;
		for(list<Transfert>::iterator itTransferts=it->second.begin();itTransferts!=it->second.end();itTransferts++) {
			if(itTransferts->lien.compare(lien)==0) {
				found=true;
				debug->print("Le lien ["+itTransferts->lien+"] existe deja.");
			}
		}
		if(found==false) {
			it->second.push_back(f);
			debug->print("Nouveau lien ["+lien+"] sur serveur existant "+server);
		}
	}
	sauvegardeFichier();
}

bool GestionnaireTelechargement::update()
{
	if(horloge->timerInferieurHorloge(timestampRaffraichissementFichier)) {
		debug->print("Sauvegarde des telechargements dans un fichier");
		horloge->horlogePlusDelai(timestampRaffraichissementFichier, periodeRaffraichissementFichierSeconde);
		sauvegardeFichier();

		map<string,list<Transfert>>::iterator itServeurs=telechargements.begin();
		if(itServeurs==telechargements.end()) {
			sauvegardeFichier();	
			return false;
		}
		while(itServeurs!=telechargements.end()) {
			if(itServeurs->second.empty())
				itServeurs=telechargements.erase(itServeurs);
			else itServeurs++;
		}
	}

	unsigned short cptTelechargementParServeur;
	for (map<string,list<Transfert>>::iterator itServeurs=telechargements.begin();itServeurs!=telechargements.end();itServeurs++) {
		cptTelechargementParServeur=0;
		list<Transfert>::iterator it=itServeurs->second.begin();
		while(it!=itServeurs->second.end()) {
			if((it->isReady())&&(cptTelechargementParServeur<nombreFichierParServer)) {

				streamsize tailleCopie=0;
				long tailleLecture;
				if(it->positionCourante+tailleBuffer > it->taille) {
					tailleLecture=it->taille-it->positionCourante;
				}
				else {
					tailleLecture = tailleBuffer;
				}

				//buffer=new char[tailleLecture];				

				bool transfertTermine=false;
				long newPos=-1;
				ifstream in;
				in.exceptions(ifstream::failbit | ifstream::badbit);
				try {
					in.open (it->lien.c_str(),ios::binary);
					if(it->positionCourante!=0)
						in.seekg(it->positionCourante);
					in.read(buffer,tailleLecture);
					tailleCopie = in.gcount();	
#ifdef DEBUG
					debug->print("Lecture de "+toString(tailleCopie)+" octets.");
#endif
					newPos = in.tellg();
					in.close();
				}
				catch (ifstream::failure e) {
#ifdef DEBUG
					debug->print("In: Exception levee: "+toString(e.what()));	
#endif
					it->erreurCpt++;
					//Sleep(1000);
				}
				
				ofstream out;
				if(tailleCopie!=0) {

					out.exceptions(ifstream::failbit | ifstream::badbit);
					try {
						
						if(newPos!=-1) {
							out.open(it->outFileName.c_str(),ios::binary|ios::app);
							out.write(buffer,tailleCopie);
							out.flush();
#ifdef DEBUG
							debug->print("Ecriture de "+toString(tailleCopie)+" octets.");
#endif
							it->positionCourante=newPos;
							if(it->positionCourante>=it->taille)
								transfertTermine=true;
							it->erreurCpt=0;
#ifdef DEBUG
							debug->print("In: Nouvelle position="+toString(newPos));
#endif
						}
						else {
#ifdef DEBUG
							debug->print("Erreur: tellg a retourne -1.");	
#endif
						}				
						out.close();						
					}
					catch (ofstream::failure e) {
#ifdef DEBUG
						debug->print("out: Exception levee: "+toString(e.what()));					
#endif
						it->erreurCpt++;
						//Sleep(1000);
					}
				}
				else {
#ifdef DEBUG
					debug->print("Aucun octet n'a ete lu cette fois");
#endif
					//Sleep(1000);
				}


				if(it->erreurCpt>10) {
					it->setDelai();
				}

				if(transfertTermine) {
#ifdef DEBUG
					debug->print("In: Fin de fichier atteinte.");
#endif
					it=itServeurs->second.erase(it);
					sauvegardeFichier();
				}
				else {
					it++;
				}

				cptTelechargementParServeur++;
			}
			else {
				it++;
			}
		}
	}


	if(horloge->timerInferieurHorloge(timestampVitesse)) {
		horloge->horlogePlusDelai(timestampVitesse, 1);

		for (map<string,list<Transfert>>::iterator itServeurs=telechargements.begin();itServeurs!=telechargements.end();itServeurs++) {
			for(list<Transfert>::iterator itTransfert=itServeurs->second.begin();itTransfert!=itServeurs->second.end();itTransfert++) {
				if(itTransfert->isReady()==false) {
					itTransfert->vitesses.push_back(0);
					if(itTransfert->vitesses.size()>nombreFiltre)
						itTransfert->vitesses.erase(itTransfert->vitesses.begin());
					itTransfert->vitessekoParSeconde=0;
				}

				float progressionRatio = ((float)itTransfert->positionCourante)/((float)itTransfert->taille);
				itTransfert->progressionPourcent=(int)(progressionRatio*100);

				float nouvelleVitesse = (float)(itTransfert->positionCourante - itTransfert->dernierePosition)/1024;
				itTransfert->vitesses.push_back(nouvelleVitesse);
				if(itTransfert->vitesses.size()>nombreFiltre)
					itTransfert->vitesses.erase(itTransfert->vitesses.begin());

				float nouvelleVitessekoParSeconde=0;
				for(list<float>::iterator itVitesse=itTransfert->vitesses.begin();itVitesse!=itTransfert->vitesses.end();itVitesse++)
					nouvelleVitessekoParSeconde+=*itVitesse;

				if(itTransfert->vitesses.size()!=0)
					nouvelleVitessekoParSeconde/=itTransfert->vitesses.size();
				
				itTransfert->vitessekoParSeconde = nouvelleVitessekoParSeconde;
				itTransfert->dernierePosition=itTransfert->positionCourante;
				/*if(itTransfert->isReady()==false)
					itTransfert->vitessekoParSeconde=0;*/
			}
		}
	}

	return true;
}