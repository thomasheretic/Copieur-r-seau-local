/*
 * (C) Copyright 2010 Kuantic S.A.S. - Tous droits réservés.
 *
 * Document confidentiel, diffusion uniquement selon les accords de NDA
 * entre Kuantic S.A.S. et le destinataire de ce document.
 *
 * This is a confidential document, that can be disclosed only to
 * recipients having a NDA up to date with Kuantic S.A.S. (France)
 *
 */

#pragma once

#include <string>
#include <sstream>
#ifndef WINVER
#define WINVER 0x0502
#endif
#include <windows.h>
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

/**
* \brief		convert a char* to System::String.
* \param		s	 A pointer to char we need to convert.
* \return	A System::String^ containing all characters.
*/
inline String^ cppStr2NetStr( const char* s )  { 
	return gcnew String( s ); 
}
/**
* \brief		convert a wchar_t* to System::String.
* \param		s	 A pointer to wchar_t we need to convert.
* \return	A System::String^ containing all characters.
*/
inline String^ cppWStr2NetStr( const wchar_t* s) {
	return gcnew String( s );
}
/**
* \brief		Convert a System::String^ object to std::wstring.
* \param		ns	 The System::String^ to convert.
* \return	The std::wstring containing values in System::String.
*/
inline std::wstring netStr2CppWStr(String^ ns) {
	try {
		wchar_t* str = (wchar_t*) Marshal::StringToHGlobalUni(ns).ToPointer();
		wstring ret(str);
		Marshal::FreeHGlobal(IntPtr(str));
		return ret;
	}
	catch (Exception^ Ex) {
		Console::WriteLine(Ex->Message);
		delete Ex;
		return L"";
	}
}
/**
* \brief		Convert a System::String^ object to std::string.
* \param		ns	 The System::String^ to convert.
* \return	The std::string containing values in System::String.
*/
inline std::string netStr2CppStr(String ^ ns) {
	try {
		char* str = (char*) Marshal::StringToHGlobalAnsi(ns).ToPointer(); //StringToHGlobalAnsi // StringToHGlobalUni
		string ret(str);
		Marshal::FreeHGlobal(IntPtr(str));
		return ret;
	}
	catch (Exception^ Ex) {
		Console::WriteLine(Ex->Message);
		delete Ex;
		return "";
	}
}
/**
* \brief		Get a std::wstring from a System::String^ object.
* \param		ns	 The System::String^ to convert.
* \return	The std::wstring containing values in System::String.
*/
inline std::wstring netStr2WCppStr(String ^ ns) {
	try {
		wchar_t* str = (wchar_t*) Marshal::StringToHGlobalUni(ns).ToPointer();
		wstring ret(str);
		Marshal::FreeHGlobal(IntPtr(str));
		return ret;
	}
	catch (Exception^ Ex) {
		Console::WriteLine(Ex->Message);
		delete Ex;
		return L"";
	}

}
/**
* \brief		Get an integer from a System::String^.
* \param		ns	 The System::String^ to convert.
* \return	An integer containing the String equivalent value.
*/
inline int netStr2Int (String ^ ns) {
	stringstream ss;
	int ret;
	ss << netStr2CppStr(ns);
	ss >> ret;
	return ret;
}

//inline string wchar2string (wchar_t* widechar) {
//	char buf[256];
//	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)widechar,-1,buf,sizeof(buf),NULL,NULL);
//	string out(buf);
//	return out;
//}

//
//inline LPWSTR string2LPWSTR (string chaine) {
//	int Size_name = MultiByteToWideChar (CP_ACP, 0, chaine.c_str(), -1, NULL, 0);
//	LPWSTR TC_name = new WCHAR[Size_name];
//	MultiByteToWideChar (CP_ACP, 0, chaine.c_str(), -1, TC_name, Size_name);
//	return TC_name;
//}

/**
* \brief		Get an integer equivalent contained in a string.
* \param		str	  The string containing the value.
* \return	An integer containing the value.
*/
inline int string2Int (const string& str) {
	stringstream ss;
	ss << str;
	int ret;
	ss >> ret;
	return ret;
}


/*
 * (C) Copyright 2011 Kuantic S.A.S. - Tous droits réservés.
 *
 * Document confidentiel, diffusion uniquement selon les accords de NDA
 * entre Kuantic S.A.S. et le destinataire de ce document.
 *
 * This is a confidential document, that can be disclosed only to
 * recipients having a NDA up to date with Kuantic S.A.S. (France)
 *
 */
 

/**
* \file		MiscConv.h
* \author	Kuantic
* \version	1.0
* \brief		Provide few methods for standard conversions.
*
* \details	This file contains all standard convertion function needed. 
*				For exemple, to get the dynatik device phone number, or to convert
*				an UTF8 multibyte to a wide string usable for many methods like
*				for the MFC methods
*/

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <windows.h>
using namespace std;


/**
* \brief		Convert a basic object (int, char, short) to a std::string 
*				with a specific user-defined number of chars.
* \details	The string is made by loading a standard T object into a stringstream.
* \param Value	 the basic object to convert.
* \param nbChar the number of chars that the output string should contain.
* \param cfill	 a char that fill the string if the convertion is smaller that
*					 nbChar.
* \return		 The converted/formated string.
*/
template<typename T>
inline std::string toString(const T& Value, const unsigned char& nbChar, \
									 const char& cfill = '0') 
{
	std::ostringstream oss;
	oss.width(nbChar);
	oss.fill(cfill);
	oss << Value;
	return oss.str();
}
/**
* \brief		Convert an object to a std::string using template.
* \param		Value	 a standard T object to convert.
* \return	A std::string object converted from object parameter.
*/
template<typename T>
inline std::string toString( const T& Value ) 
{
    std::ostringstream oss;
    oss << Value;
    return oss.str();
}
/**
* \brief Convert a basic object to a std::wstring.
* \param		Value	  a standard T object to convert.
* \return	A std::wstring object converted from object parameter.
*/
template <typename T>
inline wstring toWString (const T& Value) 
{
	wstringstream ss;
	ss << Value;
	return ss.str();
}


/**
* \brief		Fast convertion from a std::wstring to a std::string used for ASCII
*				characters only.
* \param		wstr	  Thr wide string to convert.
* \return	A std::string with all caracters that were in the wstring input
*				parameter.
*/
inline string wstringToString(const wstring& wstr) 
{
	string str(wstr.begin(),wstr.end());
	return str;
}
/**
* \brief		Fast convertion from a std::string to a std::wstring used for ASCII
*				characters only.
* \param		str	  Thr string to convert.
* \return	A std::wstring with all caracters that were in the string input
*				parameter.
*/
inline wstring stringToWstring(const string& str) 
{
	wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}
/**
* \brief		Converts a wide string into an unsigned int object.
* \param		wstr	  The wide string to convert.
* \return	The unsigned int object got from the wide string parameter.
*/
inline unsigned int wstringToUInt(const wstring& wstr) 
{
	unsigned int value;
	wstringstream wss;
	wss << wstr;
	wss >> value;
	return value;
}
/**
* \brief		Converts a wide string into an int object.
* \param		wstr	  The wide string to convert.
* \return	The int object got from the wide string parameter.
*/
inline int wstringToInt (const wstring& wstr) 
{
	int value;
	wstringstream wss;
	wss << wstr;
	wss >> value;
	return value;
}
/**
* \brief		Converts a wide string into an unsigned short object.
* \param		wstr	  The wide string to convert.
* \return	The unsigned short object got from the wide string parameter.
*/
inline unsigned short wstringToUShort (const wstring& wstr) 
{
	unsigned short value;
	wstringstream wss;
	wss << wstr;
	wss >> value;
	return value;
}
/**
* \brief		Converts a std::string into a long object.
* \param		str	  The std::string to convert.
* \return	The long object.
*/
inline long stringToLong (const string& str) {
	long lint;
	stringstream ss;
	ss << str;
	ss >> lint;
	return lint;
}

inline unsigned short stringToUShort (const string& str) {
	unsigned short usht;
	stringstream ss;
	ss << str;
	ss >> usht;
	return usht;
}	

inline short stringToShort (const string& str) {
	short sht;
	stringstream ss;
	ss << str;
	ss >> sht;
	return sht;
}


/**
* \brief		Converts a std::string into a int object.
* \param		str	  The std::string to convert.
* \return	The int converted object.
*/
inline int stringToInt (const string& str) {
	int integer;
	stringstream ss;
	ss << str;
	ss >> integer;
	return integer;
}

inline fstream::pos_type stringToPosType (const string& str) {
	unsigned long pt;
	stringstream ss;
	ss << str;
	ss >> pt;
	return pt;
}


/**
* \brief		Converts a std::string into a float object.
* \param		str	  The std::string to convert.
* \return	The float converted object.
*/
inline float stringToFloat (const string& str) {
	float flotant;
	stringstream ss;
	ss << str;
	ss >> flotant;
	return flotant;
}
/**
* \brief		Convert an Int parameter to its hexadecimal value and return it 
*				in a string.
* \param		nb	 An integer number to convert.
* \return	The std::string containing the hexadecimal value of the input 'nb'.
*/
inline string intToHexString(const int& nb) 
{
	stringstream ss;
	ss.width(2);
	ss.fill('0');
	ss << right << std::uppercase << std::hex << nb;
	return ss.str();
}
/**
* \brief		Convert a char parameter to its hexadecimal and return it in a string.
* \param		c	 The char to convert.
* \return	The std::string containing the char parameter under its hexadecimal
*				form.
*/
inline string charToHexString(const char& c) 
{
	stringstream ss;
	ss.width(2);
	ss.fill('0');
	ss << std::uppercase << std::hex << (((int)c) & 0xFF);
	return ss.str();
}
/**
* \brief		Get an understandable hexadecimal string from an input char string.
* \param		data	  A std::string containing characters.
* \return	The string containing the hexadecimal form of the string parameters,
*				with twice more bytes than in 'data'.
*/
inline string stringToHexString (const string& data)
{
	string out;
	out.reserve(data.length()*2);
	string::const_iterator it;
	for (it = data.begin(); it != data.end(); it++) {
		out += charToHexString(*it);
	}
	return out;
}
