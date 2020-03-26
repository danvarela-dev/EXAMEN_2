#include "examen2_21651030_offline.h"

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

	char enteros[6];
	char decimal[2];

	int x = 0, y = 0;

	while (1)
	{
		if (x < strlen(Sueldo))
			enteros[x++] = '0';
		else
			enteros[x++] = Sueldo[y++];

		if (strlen(Sueldo) > x || Sueldo[x] == '.') break;

	}
	enteros[y] = '\0';
	

	strcat(Sueldo, enteros);

	strcat(buffer, Sueldo);


	strcat(buffer, ",");

	for (int i = strlen(buffer); i < 125; i++)
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

DataFile::DataFile() {}

void DataFile::agregarRegistro() {
	ofstream file;

	file.open("Registros.txt", ofstream::out | ofstream::app);

	if (!file) {
		cout << "Error abriendo archivo: " << endl;
		return;
	}
	
	file.seekp(0, ios::end);
	int pos = file.tellp();
	file.seekp(pos, ios::beg);

	reg.getOne();

	int len = strlen(reg.buffer);

	for (size_t i = len; i < 101; i++)
	{
		reg.buffer[i] = ' ';
	}


	file.write(reg.buffer, 100);

	

	file.close();

}

int DataFile::buscar(string ID) {

	ifstream file;

	file.open("Registros.text", ifstream::in);

	return -1;

	file.close();

}

void DataFile::eliminar(string ID) {

	int offsetToMark = buscar(ID);
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

void DataFile::compactar() {
	ifstream i_file;
	ofstream indexFile;
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
		i_file.read(buffer_aux, 100);
		buffer_aux[99] = '\0';
		strcpy(reg.buffer, buffer_aux);
		reg.unPack();

		if (reg.Codigo[0] != '*' && curPointer < filesize) {
			o_file << buffer_aux;
		}

		curPointer += 100;
	}

	i_file.close();
	o_file.close();
	indexFile.close();

}
