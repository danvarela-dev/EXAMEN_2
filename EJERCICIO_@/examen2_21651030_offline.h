#ifndef PROGRAM_H
#define PROGRAM_H
#include <iostream>
#include <string.h>
#include <list>


using namespace std;


class RecData {

public:
	RecData();
	void Pack();
	void unPack();
	void getOne();

	char buffer[101];


	char Cedula[14];
	char Nombres[20];
	char Apellidos[20];
	char Direccion[20];
	char Ciudad[14];
	char Estado[7];
	char ZipCode[5];
};

class DataFile {
public:
	DataFile();

	void PrintAll();
	void Add();
	int Find(char *);
	void Remove(char *);
	void Compact();
	char buffer_aux[100];

	char head[4];
	
	list<int> freeSpaces;

	list<int> getFreeSpaces();

private:
	RecData reg;

};






#endif // !PROGRAM_H
