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
	char buffer[125];


	char Codigo[11];
	char Nombres[49];
	char Apellidos[49];
	char Departamento[4];
	char Edad[3];
	char Sueldo[9];
};

class DataFile {
public:
	DataFile();

	//agrega registro a archivo
	void Add();
	int Find(char * );
	void Remove(char *);
	void Compact();//compacta el archivo de registros y tambien el de indices
	void PrintAll();
	char buffer_aux[125];

	char head[4];
	list<DataFile> disponibles;

private:
	RecData reg;

};




#endif // !PROGRAM_H
