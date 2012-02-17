#pragma once


#include <string>
#include <fstream>
using namespace std;



inline string getServerName (string& lien) 
{
	string serveur;
	string::size_type positionPremierCaractere=0;
	for(unsigned int i=0;i<lien.length();i++) {
		if(lien[i]!='\\') {
			positionPremierCaractere=i;
			break;
		}
	}

	if(positionPremierCaractere != string::npos)
		serveur = lien.substr(positionPremierCaractere);

	string::size_type positionFinServeur=serveur.find('\\');
	if(positionFinServeur != string::npos)
		serveur=serveur.substr(0,positionFinServeur);
	
	return serveur;
}






inline long GetFileSize( std::ifstream & fichier )
{
    // sauvegarder la position courante
    long pos = fichier.tellg();
    // se placer en fin de fichier
    fichier.seekg( 0 , std::ios_base::end );
    // récupérer la nouvelle position = la taille du fichier
    long size = fichier.tellg() ;
    // restaurer la position initiale du fichier
    fichier.seekg( pos,  std::ios_base::beg ) ;
    return size ;
}



