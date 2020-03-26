#include <limits>
#include <fstream>
#include <inttypes.h>
#include <unordered_map> 
#include <iostream>
#include "examen2_21651030_datafile.h"

#pragma warning (disable : 4996)
 
using namespace std;

void help() {
	cout << "Utilizar los siguientes comandos disponibles" << endl;
	cout << "print:        Imprimir todos los registros del archivo " << endl;
	cout << "add:          Agregar un registro al archivo" << endl;
	cout << "find <key>:   Encuentra el <key> en el archivo" << endl;
	cout << "remove <key>: Remueve el <key> en el archivo" << endl;
	cout << "compact:      Para compactar el archivo" << endl;
	cout << "help:         Para ver la ayuda" << endl;
	cout << "exit:         Salir del programa" << endl;
}

int main(int argc, char** argv) {

	DataFile t;
	char cmd[200];
	char m_command[200];
	char m_param1[200];
	char* ptr;
	help();

	while (1)
	{
		cmd[0] = 0;
		m_command[0] = 0;
		m_param1[0] = 0;

		printf("\r\nCommand>");
		fgets(cmd, 200, stdin);

		ptr = strtok(cmd, " \n");
		if (ptr != NULL) strcpy(m_command, ptr);

		ptr = strtok(NULL, " \n");
		if (ptr != NULL) strcpy(m_param1, ptr);


		if (!strcmp("print", m_command)) 	t.PrintAll();
		if (!strcmp("add", m_command)) 	t.Add();
		if (!strcmp("find", m_command))		t.Find(m_param1);
		if (!strcmp("remove", m_command))	t.Remove(m_param1);
		if (!strcmp("compact", m_command))	t.Compact();
		if (!strcmp("help", m_command))	help();
		if (!strcmp("exit", m_command))		break;

	}

	return 0;
}





