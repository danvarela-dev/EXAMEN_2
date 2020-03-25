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
	IndexFile index;
	list<IndexFile> listLoaded = index.getList();//carga indice a memoria
	file.seekp(0, ios::end);
	int pos = file.tellp();
	file.seekp(pos, ios::beg);

	reg.getOne();

	int len = strlen(reg.buffer);

	for (size_t i = len; i < 101; i++)
	{
		reg.buffer[i] = ' ';
	}

	strcpy(index.ID, reg.Cedula);
	index.Offset = pos;
	listLoaded.push_back(index);//modifica lista de indice

	file.write(reg.buffer, 100);

	index.setList(listLoaded);//escribe a archivo lista actualizada

	file.close();

}

int DataFile::buscar(string ID) {

	ifstream file;

	file.open("Index.dat", ifstream::in);
	IndexFile index;

	list<IndexFile> list = index.getList();


	if (list.size() == 0)
		return -1;



	for (auto it = list.begin(); it != list.end(); it++)
	{
		if (it->ID == ID) {
			return it->Offset;
		}
	}

	return -1;

	file.close();

}

void DataFile::eliminar(string ID) {

	int offsetToMark = buscar(ID);
	ofstream file;
	IndexFile index;


	file.open("Registros.txt", ofstream::cur);
	file.seekp(offsetToMark, ios::cur);

	file << "*";

	if (offsetToMark == -1)
		cout << "Registro no encontrado..." << endl;
	else
		cout << "Registro Eliminado..." << endl;

	file.close();

	list<IndexFile> list = index.getList();
	index.setList(list);

}

void DataFile::compactar() {
	ifstream i_file;
	ofstream indexFile;
	ofstream o_file;
	int curPointer = 0;
	IndexFile index;
	list<IndexFile> list = index.getList();

	i_file.open("Registros.txt", ifstream::in);
	indexFile.open("Index.dat", ifstream::out);
	o_file.open("Registros-Compacted.txt", ofstream::out | ios::trunc);


	for (auto it = list.begin(); it != list.end(); it++)
	{
		strcpy(index.ID, it->ID);
		index.Offset = it->Offset;
		index.indexPack();
		if (index.indexBuff[0] != '*')
			indexFile.write(index.indexBuff, 50);
	}



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

		if (reg.Cedula[0] != '*' && curPointer < filesize) {
			o_file << buffer_aux;
		}

		curPointer += 100;
	}

	i_file.close();
	o_file.close();
	indexFile.close();

}

void IndexFile::createIndexFile()
{
	ifstream iFile;
	ofstream oFile;



	iFile.open("Registros.txt", ifstream::in);
	oFile.open("Index.dat", ifstream::trunc);

	char buff[50];
	iFile.seekg(0, ios::end);
	int sz = iFile.tellg();
	iFile.seekg(0, ios::beg);

	int offset = 0;
	int curPointer = 0;
	while (sz > curPointer)
	{
		offset = iFile.tellg();
		iFile.read(reg.buffer, 100);
		reg.unPack();

		strcpy(ID, reg.Cedula);
		Offset = offset;
		indexPack();


		oFile.write(indexBuff, 50);

		curPointer += 100;
	}

	iFile.close();
	oFile.close();

}


void IndexFile::indexPack()
{
	char offsetStr[10];
	offsetStr[0] = 0;
	ID[strlen(ID)] = '\0';
	indexBuff[0] = 0;
	strcat(indexBuff, ID);
	strcat(indexBuff, "|");
	sprintf(offsetStr, "%d", Offset);
	offsetStr[strlen(offsetStr)] = '\0';
	strcat(indexBuff, offsetStr);
	strcat(indexBuff, "|");

	for (size_t i = strlen(indexBuff); i < 50; i++)
		indexBuff[i] = ' ';

	indexBuff[strlen(indexBuff)] = '\0';

}

void IndexFile::indexUnPack() {
	char* c = indexBuff;
	char temp[15];
	char offsetStr[15];

	int i = 0, j = 0;

	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	i++;
	strcpy(ID, temp);


	while (c[i] != '|')
	{
		temp[j++] = c[i++];
	}
	temp[j] = '\0';
	j = 0;
	strcpy(offsetStr, temp);
	Offset = atoi(offsetStr);


}

list<IndexFile> IndexFile::getList() {


	ifstream file;
	IndexFile index;
	list<IndexFile> lista;
	createIndexFile();
	file.open("Index.dat", ios::in);
	int curPointer = 0;
	file.seekg(0, ios::end);
	int sz = file.tellg();
	file.seekg(0, ios::beg);

	while (sz > curPointer)
	{
		file.read(indexBuff, 50);
		indexUnPack();
		strcpy(index.ID, ID);
		index.Offset = Offset;

		lista.push_back(index);

		curPointer += 50;
	}

	file.close();

	return lista;
}

void IndexFile::setList(list<IndexFile> l) {
	ofstream file;

	createIndexFile();

	file.open("Index.dat", ios::out | ios::trunc);

	for (auto it = l.begin(); it != l.end(); it++)
	{
		strcpy(ID, it->ID);
		Offset = it->Offset;
		indexPack();

		file.write(indexBuff, 50);
	}

	file.close();

}