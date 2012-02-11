#include "Debug.h"


Debug* Debug::_singleton = 0;


Debug* Debug::getInstance() 
{
	if(_singleton==0)
		_singleton = new Debug();
	return _singleton;
}


Debug* Debug::destruction() 
{
	if(_singleton) {
		delete _singleton;
		_singleton = 0;
	}
	return _singleton;
}


Debug::Debug()
{
#ifdef DEBUG
	ofstream fichier (fichierLogs.c_str());
	fichier.close();
	AllocConsole();
#endif
	print("Debug contructeur");
}


Debug::~Debug()
{
	print("Debug destructeur");
#ifdef DEBUG
	FreeConsole();
#endif
}

bool Debug::print(const string& Msg) {
	string msgToPrint = Msg;

#ifdef DEBUG


	ofstream fichier (fichierLogs.c_str(),ios::app);
	if(fichier.fail()==false) {
		fichier << msgToPrint << endl;
	}
	fichier.close();

	string::size_type i = 0;
	while ((i = msgToPrint.find('7', i)) != string::npos)
		msgToPrint.replace(i++, 1, "$");

	HWND hWnd = GetConsoleWindow();
	HANDLE hdlout = GetStdHandle(STD_OUTPUT_HANDLE);
	if ((hdlout == INVALID_HANDLE_VALUE) || (hdlout == NULL) || (hWnd == NULL))
		return false; // can't write at all
	
	BOOL ret = WriteFile(hdlout, (msgToPrint+"\n").c_str(), (DWORD)(msgToPrint+"\n").length(),\
								NULL, NULL);
	return (ret != 0? true:false);
#else
	return true;
#endif
}
