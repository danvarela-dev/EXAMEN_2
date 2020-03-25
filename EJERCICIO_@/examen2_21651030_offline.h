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


	char Codigo[10];
	char Nombres[50];
	char Apellidos[50];
	char Departamento[3];
	char Edad[3];
	char Sueldo[9];
};

class DataFile {
public:
	DataFile();

	//agrega registro a archivo
	void agregarRegistro();
	int buscar(string);
	void eliminar(string);
	void compactar();//compacta el archivo de registros y tambien el de indices
	char buffer_aux[125];

private:
	RecData reg;

};




#endif // !PROGRAM_H
