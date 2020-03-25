#include "examen2_21651030_datafile.h"
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
	char auxCodigo[10]{};

	int j = 0;
	for (size_t i = 0; i <= 10; i++)
	{
		if (i < a)
			auxCodigo[i] = '0';
		else
			auxCodigo[i] = Codigo[j++];
	}

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

	/*char enteros[6];
	char decimal[2];
	
	int x = 0, y = 0;

	while (Sueldo[x] != '.' || x < strlen(Sueldo))
	{
		if (x < strlen(Sueldo))
			enteros[x] = '0';
		else {
			enteros[y++] = Sueldo[x];
		}
	}
	enteros[y] = '\0';
	strcat(Sueldo, enteros);*/

	strcat(buffer, Sueldo);


	strcat(buffer, ",");

	for(int i = strlen(buffer); i < 125 ; i++)
		buffer[i] = '*';

	buffer[strlen(buffer)] = '\n';

	

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
	int a = 10 - strlen(temp);
	for (int i = a; i >= 0; i--)
		temp[i] = '0';

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



void DataFile::Add() {
	ofstream file;

	file.open("Registros.txt", ofstream::out | ofstream::app);

	if (!file) {
		cout << "Error abriendo archivo: " << endl;
		return;
	}

	

	reg.getOne();

	int len = strlen(reg.buffer);
	for (size_t i = len; i < 125; i++)
	{
		reg.buffer[i] = ' ';
	}

	file.write(reg.buffer, 125);

	file.close();

}

int DataFile::Find(string codigo) {

	ifstream file;

	file.open("Registros.txt", ifstream::in);

	if (!file) {
		cout << "Error abriendo archivo: " << endl;
		return 0;
	}
	int curPointer = 0;

	while (!file.eof())
	{
		curPointer = file.tellg();
		file.read(reg.buffer, 125);

		reg.unPack();
		if (codigo == reg.Codigo) {
			cout << "Codigo: " << reg.Codigo << endl;
			cout << "Nombres: " << reg.Nombres << endl;
			cout << "Apellidos: " << reg.Apellidos << endl;
			cout << "Departamento: " << reg.Departamento << endl;
			cout << "Edad: " << reg.Edad << endl;
			cout << "Sueldo: " << reg.Sueldo << endl;

			return curPointer;
		}

	}
	file.close();
	return 0;
}

void DataFile::Remove(string nombre) {
	int offsetToMark = Find(nombre);

	ofstream file;
	file.open("Registros.txt", ofstream::cur);
	file.seekp(offsetToMark, ios::cur);

	file << "D";

	file.close();

}

void DataFile::Compact() {
	ifstream i_file;
	ofstream o_file;
	int curPointer = 0;


	i_file.open("Registros.txt", ifstream::in);
	o_file.open("Registros-Compacted.txt", ofstream::out | ios::trunc);


	i_file.seekg(0, ios::end);
	int filesize = i_file.tellg();
	i_file.seekg(0, ios::beg);


	while (!i_file.eof())
	{


		i_file.seekg(curPointer, ios::beg);
		i_file.read(buffer_aux, 125);

		if (buffer_aux[0] != 'D' && curPointer < filesize) {
			o_file << buffer_aux;
		}

		curPointer += 125;
	}

	i_file.close();
	o_file.close();

}


void DataFile::PrintAll() {

	
	ifstream f;
	f.open("Registros.txt", ifstream::in);

	while (1)
	{
		f.read(buffer_aux, 125);
		buffer_aux[strlen(buffer_aux)] = '\0';
		strcpy(reg.buffer, buffer_aux);
		reg.unPack();
		

		cout << "Codigo: " << reg.Codigo << endl;
		cout << "Nombres: " << reg.Nombres << endl;
		cout << "Apellidos: " << reg.Apellidos << endl;
		cout << "Departamento: " << reg.Departamento << endl;
		cout << "Edad: " << reg.Edad << endl;
		cout << "Sueldo: " << reg.Sueldo << endl;


	}




}