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

class IndexFile {
public:
	IndexFile() {}

	RecData reg;
	char indexBuff[50];

	char ID[14];
	int Offset;

	//empaqueta variables de clase
	void indexPack();
	//desempaqueta variables de buffer leido de archivo
	void indexUnPack();
	//crea un archivo usando como llave primaria cedula
	// y el offset, este se crea secuecialmente, no necesita ser ordenado
	void createIndexFile();

	//carga archivo de indices a lista
	list<IndexFile> getList();
	//escribe a archivo lista recibida de parametro
	void setList(list<IndexFile>);

};






#endif // !PROGRAM_H
