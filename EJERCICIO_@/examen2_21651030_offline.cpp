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