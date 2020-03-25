#ifndef EXAMEN_2_21651030_DATAFILE_H
#define EXAMEN_2_21651030_DATAFILE_H
#include <iostream>
#include <string.h>



using namespace std;


class RecData {

public:
	RecData();
	void Pack();
	void unPack();
	void getOne();

	char buffer[125];

	char Codigo[10];
	char Nombres[50];
	char Apellidos[50];
	char Departamento[3];
	char Edad[3];
	char Sueldo[9];
};


class DataFile {
public:
	DataFile() = default;

	void Add();
	int Find(string);
	void Remove(string);
	void Compact();
	void PrintAll();

	char buffer_aux[125];

private:
	RecData reg;

};

#endif // !EXAMEN_2_21651030_DATAFILE_H
