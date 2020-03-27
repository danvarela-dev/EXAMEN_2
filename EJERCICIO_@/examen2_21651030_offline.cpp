#include "examen2_21651030_offline.h"
#include <fstream>

#pragma warning (disable : 4996)

RecData::RecData() {

	buffer[0] = 0;

	Cedula[0] = 0;
	Nombres[0] = 0;
	Apellidos[0] = 0;
	Direccion[0] = 0;
	Ciudad[0] = 0;
	Estado[0] = 0;
	ZipCode[0] = 0;
}

void RecData::Pack() {

	if (buffer[0] != 0)
		buffer[0] = 0;

	strcat(buffer, Cedula);
	strcat(buffer, "|");
	strcat(buffer, Nombres);
	strcat(buffer, "|");
	strcat(buffer, Apellidos);
	strcat(buffer, "|");
	strcat(buffer, Direccion);
	strcat(buffer, "|");
	strcat(buffer, Ciudad);
	strcat(buffer, "|");
	strcat(buffer, Estado);
	strcat(buffer, "|");
	strcat(buffer, ZipCode);
	strcat(buffer, "|");

}

void RecData::unPack() {

	char* c = buffer;
	char temp[30];
	int i = 0, j = 0;

	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Cedula, temp);


	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Nombres, temp);

	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Apellidos, temp);

	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Direccion, temp);
	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Ciudad, temp);

	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(Estado, temp);

	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(ZipCode, temp);

}
void RecData::getOne() {
	cout << "REGISTRO" << endl;
	cout << "Ingrese Cedula:";
	cin.getline(Cedula, 14);
	cout << "Ingrese nombres: ";
	cin.getline(Nombres, 20);
	cout << "Ingrese Apellidos: ";
	cin.getline(Apellidos, 20);
	cout << "Ingrese Direccion: ";
	cin.getline(Direccion, 20);
	cout << "Ingrese Ciudad: ";
	cin.getline(Ciudad, 15);
	cout << "Ingrese Estado: ";
	cin.getline(Estado, 7);
	cout << "Ingrese Zip Code: ";
	cin.getline(ZipCode, 6);
	cout << endl;
	Pack();

}



DataFile::DataFile() {}

void DataFile::Add() {
	ofstream file;
	freeSpaces = getFreeSpaces();


	file.open("Registros.txt", ofstream::out | ofstream::cur);

	if (!file) {
		cout << "Error abriendo archivo: " << endl;
		return;
	}

	file.seekp(0, ios::end);
	int pos = file.tellp();
	file.seekp(pos, ios::beg);

	int firstAvailable = freeSpaces.front();


	
	if (pos == 0) {
		head[0] = '0';
		head[1] = '0';
		head[2] = '0';
		head[3] = '-1';

		file.write(head, 4);
	}
	
	reg.getOne();

	int len = strlen(reg.buffer);

	for (size_t i = len; i < 101; i++)
	{
		reg.buffer[i] = ' ';
	}

	/*char headAux[4];
	int  k = 0;
	k = 4 - strlen(head);
	sprintf(headAux, "%d", firstAvailable);
	for (size_t i = 0; i < 4; i++)
	{
		if (i < k)
			head[i] = '0';
		else
			head[i] = headAux[k++];
	}*/

	//if (firstAvailable == -1) {
	//	head[0] = '0';
	//	head[1] = '0';
	//	head[2] = '0';
	//	head[3] = '-1';
	//}*/

	file.seekp(0, ios::beg);
	file.write(head, 4);


	if (firstAvailable == -1) {
		file.seekp(0, ios::end);
	}
	else {
		file.seekp(firstAvailable);
		freeSpaces.pop_front();
	}

	


	


	file.write(reg.buffer, 100);



	file.close();
}

int DataFile::Find(char * ID) {

	ifstream file;

	file.open("Registros.txt", ifstream::in);

	file.read(head, 4);

	int offset =file.tellg();


	while (!file.eof())
	{
		file.read(reg.buffer, 100);

		reg.unPack();


		if (strcmp(reg.Cedula, ID) == 0) {

			cout << "************************* REGISTRO ******************************" << endl;
			cout << "Cedula: " << reg.Cedula << endl;
			cout << "Nombres: " << reg.Nombres << endl;
			cout << "Apellidos: " << reg.Apellidos << endl;
			cout << "Direccion: " << reg.Direccion << endl;
			cout << "Ciudad: " << reg.Ciudad << endl;
			cout << "Estado: " << reg.Estado << endl;
			cout << "ZipCode: " << reg.ZipCode << endl;

			return offset;
		}

		offset = file.tellg();

	}


	return -1;

	file.close();

}

void DataFile::Remove(char* ID) {

	int offsetToMark = Find(ID);
	
	freeSpaces.push_back(offsetToMark);

	ofstream file;

	char offsetStr[4];
	sprintf(offsetStr, "%d", offsetToMark);

	int sizeOffset = 4 - strlen(offsetStr);
	int j = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (i < sizeOffset)
			head[i] = '0';
		else
			head[i] = offsetStr[j++];
	}

	file.open("Registros.txt",ofstream::cur | ofstream::out);
	file.write(head, 4);
	file.seekp(offsetToMark - 4, ios::cur);

	file << '*';

	file.close();

	if (offsetToMark == -1) {
		cout << "Registro no encontrado..." << endl;
		return;
	}
	else
		cout << "Registro Eliminado..." << endl;


}


list<int> DataFile::getFreeSpaces() {
	ifstream file;
	file.open("Registros.txt", ifstream::in);

	file.read(head, 4);

	int num = atoi(head);

	int offset = file.tellg();

	list<int> freeOffsets;


	while (!file.eof())
	{
		file.read(buffer_aux, 100);

		if (buffer_aux[0] == '*')
			freeOffsets.push_back(offset);


		offset = file.tellg();
	}
	
	if (freeOffsets.empty())
		freeOffsets.push_back(-1);


	return freeOffsets;

}

void DataFile::PrintAll() {


	ifstream file;
	file.open("Registros.txt", ifstream::in);

	file.seekg(0, ios::end);
	int sz = file.tellg();
	file.seekg(0, ios::beg);

	int pos = 0;

	while (!file.eof())
	{
		if(pos == 0) file.read(head, 4);
			
		file.read(reg.buffer, 100);
		reg.unPack();

		if (pos == sz) break;

		cout << "***********REGISTRO***********" << endl;
		cout << "Cedula:";
		cout << reg.Cedula << endl;
		cout << "nombres: ";
		cout << reg.Nombres << endl;
		cout << "Apellidos: ";
		cout << reg.Apellidos << endl,
		cout << "Direccion: ";
		cout << reg.Direccion << endl;
		cout << "Ciudad: ";
		cout << reg.Ciudad << endl;
		cout << "Estado: ";
		cout << reg.Estado << endl;
		cout << "Zip Code: ";
		cout << reg.ZipCode << endl;


		pos = file.tellg();

	}

	file.close();	

}


void DataFile::Compact() {
	ifstream i_file;
	ofstream indexFile;
	ofstream o_file;
	int curPointer = 0;

	i_file.open("Registros.txt", ifstream::in);
	o_file.open("Registros-Compacted.txt", ofstream::out);


	i_file.seekg(0, ios::end);
	int filesize = i_file.tellg();
	i_file.seekg(0, ios::beg);

	head[0] = '0';
	head[1] = '0';
	head[2] = '0';
	head[3] = '-1';


	o_file.write(head, 4);

	while (!i_file.eof())
	{

		
		if (curPointer == 0) i_file.read(head, 4);
		i_file.read(reg.buffer, 100);

		reg.unPack();

		if (reg.Cedula[0] != '*' && curPointer < filesize) {
			o_file << reg.buffer;
		}

		curPointer += 100;
	}

	i_file.close();
	o_file.close();

	cout << "Se genero copia del archivo compactado" << endl;

}