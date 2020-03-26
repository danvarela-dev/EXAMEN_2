#include "examen2_21651030_offline.h"
#include <string>
#include <iostream>
#include <fstream>

#pragma warning (disable : 4996)

RecData::RecData() {

	buffer[0] = 0;
	Codigo[0] = 0;
	Nombres[0] = 0;
	Apellidos[0] = 0;
	Departamento[0] = 0;
	Edad[0] = 0;
	Sueldo[0] = 0;
}

void RecData::Pack() {


	int a = strlen(Codigo) + 1;
	char auxCodigo[11];

	int j = 0;
	for (size_t i = 0; i <= 10; i++)
	{
		if (i < a)
			auxCodigo[i] = '0';
		else
			auxCodigo[i] = Codigo[j++];
	}
	auxCodigo[10] = '\0';

	strcat(buffer, auxCodigo);
	strcat(buffer, ",");
	strcat(buffer, Nombres);
	strcat(buffer, ",");
	strcat(buffer, Apellidos);
	strcat(buffer, ",");
	strcat(buffer, Departamento);
	strcat(buffer, ",");
	strcat(buffer, Edad);
	strcat(buffer, ",");

	char enteros[6];
	char decimal[3];


	bool dot = 0;
	int x = 0;


	while (x < strlen(Sueldo))
	{
		if (Sueldo[x++] == '.')
			dot = true;
	}

	if (!dot)
		strcat(Sueldo, ".");


	x = 0;

	while (Sueldo[x] != '.')
	{
		enteros[x] = Sueldo[x];
		x++;

	}
	enteros[x] = '\0';
	x++;
	char enteroAux[7];
	int y = 0;
	int sz = 6 - strlen(enteros);
	size_t i = 0;
	for (i = 0; i < 6; i++)
	{
		if (i < sz)
			enteroAux[i] = '0';
		else
			enteroAux[i] = enteros[y++];

	}
	enteroAux[6] = '\0';

	if (dot) {
		y = 0;
		while (x < 9)
		{
			decimal[y++] = Sueldo[x++];
		}

		char decimalAux[3];

		int sizeDec = strlen(decimal);
		y = 0;
		while (y < 3)
		{
			if (sizeDec < y)
				decimalAux[y] = '0';
			else
				decimalAux[y] = decimal[y];
			y++;
		}
		if (strlen(decimalAux) == 1)
			decimalAux[1] = '0';

		decimalAux[2] = '\0';

		strcpy(Sueldo, enteroAux);
		strcat(Sueldo, ".");
		strcat(Sueldo, decimalAux);

		strcat(buffer, Sueldo);
	}
	else {
		strcat(buffer, enteroAux);
		strcat(buffer, ".00");
	}


	strcat(buffer, ",");

	for (int i = strlen(buffer); i < 125; i++)
		buffer[i] = '*';


}

void RecData::unPack() {

	char* c = buffer;
	char temp[50];
	int i = 0, j = 0;
	while (c[i] != ',')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;

	strcpy(Codigo, temp);

	while (c[i] != ',')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Nombres, temp);

	while (c[i] != ',')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Apellidos, temp);
	while (c[i] != ',')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Departamento, temp);

	while (c[i] != ',')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Edad, temp);

	while (c[i] != ',')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;


	strcpy(Sueldo, temp);


}
void RecData::getOne()
{
	cout << "REGISTRO" << endl;
	cout << "Ingrese Codigo: ";
	cin.getline(Codigo, 10);
	cout << "Ingrese nombres: ";
	cin.getline(Nombres, 50);
	cout << "Ingrese Apellidos: ";
	cin.getline(Apellidos, 50);
	cout << "Ingrese Departamento: ";
	cin.getline(Departamento, 4);
	cout << "Ingrese Edad: ";
	cin.getline(Edad, 3);
	cout << "Ingrese Sueldo: ";
	cin.getline(Sueldo, 10);

	Pack();
}

DataFile::DataFile() {}

void DataFile::Add() {
	ofstream file;

	file.open("Registros.txt", ofstream::out | ofstream::app);

	if (!file) {
		cout << "Error abriendo archivo: " << endl;
		return;
	}



	file.seekp(0, ios::end);
	int pos = file.tellp();
	file.seekp(pos, ios::beg);

	if (pos == 0)
		for (size_t i = 0; i < 4; i++)
			head[0] = '-1';
	file.write(head, 4);

	reg.getOne();


	int len = strlen(reg.buffer);

	for (size_t i = len; i < 101; i++)
	{
		reg.buffer[i] = '*';
	}


	file.write(reg.buffer, 100);
	file << '\n';



	file.close();

}

int DataFile::Find(char* codigo) {

	ifstream file;
	ofstream oFile;

	file.open("Registros.text", ifstream::in);


	string line;


	file.read(head, 4);
	int offset = 0;


	while (getline(file, line))
	{
		offset = file.tellg();
		strcpy(reg.buffer, line.c_str());
		reg.unPack();

		if (strcmp(codigo, reg.Codigo) == 0) {
			cout << "Codigo: " << reg.Codigo << endl;
			cout << "Nombres: " << reg.Nombres << endl;
			cout << "Apellidos: " << reg.Apellidos << endl;
			cout << "Departamento: " << reg.Departamento << endl;
			cout << "Edad: " << reg.Edad << endl;
			cout << "Sueldo: " << reg.Sueldo << endl;


			return offset;

		}


	}


	file.close();

	return -1;
}

void DataFile::Remove(char* ID) {

	int offsetToMark = Find(ID);
	ofstream file;

	file.open("Registros.txt", ofstream::cur);
	file.seekp(offsetToMark, ios::cur);

	file << "*";

	if (offsetToMark == -1)
		cout << "Registro no encontrado..." << endl;
	else
		cout << "Registro Eliminado..." << endl;

	file.close();

}

void DataFile::Compact() {
	ifstream i_file;
	ofstream indexFile;
	ofstream o_file;
	int curPointer = 0;


	i_file.open("Registros.txt", ifstream::in);
	o_file.open("Registros-Compacted.txt", ifstream::out | ifstream::trunc);

	string line;
	int offset = 0;
	while (getline(i_file, line))
	{
		offset = i_file.tellg();
		if (line[0] != 'D') {
			o_file << line << '\n';
		}
	}

	i_file.close();
	o_file.close();
	indexFile.close();

}

void DataFile::PrintAll() {

	ifstream f;
	f.open("Registros.txt", ifstream::in);
	string line;
	char codAux[11];

	while (getline(f, line))
	{
		strcpy(reg.buffer, line.c_str());

		reg.unPack();


		cout << "************************* REGISTRO ******************************" << endl;
		cout << "Codigo: " << reg.Codigo << endl;
		cout << "Nombres: " << reg.Nombres << endl;
		cout << "Apellidos: " << reg.Apellidos << endl;
		cout << "Departamento: " << reg.Departamento << endl;
		cout << "Edad: " << reg.Edad << endl;
		cout << "Sueldo: " << reg.Sueldo << endl;

	}

	f.close();


}