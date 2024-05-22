#include <iostream>
#include <fstream>
#include <string>

#define ARCHIVO "MensajeEncriptado.txt"
#define CHECKSUM_DESENCRIPTADO 27851
#define NUM_ENCRIPTACION 30

using namespace std;


//Funcion para verificar un el check sum de un cojunto de strings.
int checksum(string encriptado) {

	//Creamos una variable on un valor 0
	int checksum = 0;

	//Por cada character que nos pase, haremos una suma del valor int que tiene ese caracter a una variable llamada checksum.
	for (int i = 0; i < encriptado.length(); i++)
	{
		checksum += int(encriptado[i]);
	}
	cout << "The check sum is: " << checksum << endl;

	//Devolveremos el valor numerico que nos ha dado.
	return checksum;

}



string fuerza_bruta(string mensajes) {

	//Creo un bool para el bucle while no pare hasta desencriptarlo.
	bool desencriptado = false;
	//El mensaje a desencriptar es el recibido por la función.
	string mensajes_a_desencriptar = mensajes;

	//Variable que se incrementara por cada vez que el bucle ejecuta el codigo.
	int i = 1;

	//Hasta que no este desecriptado.
	while (!desencriptado)
	{
		//Creamos una variable donde se alamacenara el intento de descodificacion
		string mensajes_desencriptado;

		//Bucle por cada character que tenga la variable.
		for (int y = 0; y < mensajes_a_desencriptar.length(); y++)
		{
			//Restara el valor i de cada caracter.
			mensajes_desencriptado += char(mensajes_a_desencriptar[y] - i);
		}

		//Si pasando la variable de intento de descodificacion al calculo de checksum concuerda con el valor del chechsum desencriptado parara el bucle.
		if (checksum(mensajes_desencriptado) == CHECKSUM_DESENCRIPTADO)
		{
			//retornaremos el mensaje y pararemos el bucle.
			cout << "Desencriptado" << endl;
			desencriptado = true;
			return mensajes_desencriptado;
		}
		else
		{
			//Si no es el mismo checksum, sumara uno.
			i += 1;
			cout << "Intento num:" << i << endl;
		}
	}
}



string desencriptacion(string mensajes) {

	//Variables para recibir el mensaje a desencripar y el resultado.
	string mensajes_a_desencriptar = mensajes;
	string mensajes_desencriptado;


	//Por lo largo que sea el mensaje descifraremos cada caracter restando en la tabla ascii lo que se ha sumado.
	for (int i = 0; i < mensajes_a_desencriptar.length(); i++)
	{
		mensajes_desencriptado += char(mensajes_a_desencriptar[i] - NUM_ENCRIPTACION);
	}

	//Devolveremos el string del mensaje desencriptado.
	return mensajes_desencriptado;
}

string encriptacion(string mensajes) {

	//Creamos variables de mensaje a encriptar y encriptado.
	string mensajes_a_encriptar = mensajes;
	string mensajes_encriptado;

	cout << "mensaje a encriptar " << mensajes_a_encriptar << endl;


	//Por lo largo que sea se modificara cada caracter a una suma de 5
	for (int i = 0; i < mensajes_a_encriptar.length(); i++)
	{
		//Por cada character que tenga le sumamos el numero de encriptacion.
		mensajes_encriptado += char(mensajes_a_encriptar[i] + NUM_ENCRIPTACION);
	}

	//Devolvemos la string encriptada que ha hecho la funcion.
	return mensajes_encriptado;
}


void menu_1() {

	ifstream archivo;
	archivo.open(ARCHIVO);
	

	if (!archivo.is_open())
	{
		cout << "Archivo no abierto correctamente" << endl;
	}
	else
	{
		cout << "abierto" << endl;
	}

	string linea;
	string mensajes_guardados;

	//Hasta que el archivo no pueda coger mas lineas del archivo:
	while (getline(archivo, linea)) {

		//Guardaremos todas las lineas en una variable.
		mensajes_guardados += linea;
	}

	//Pasamos a hacerle fuerza bruta al texto extraido.
	mensajes_guardados = fuerza_bruta(mensajes_guardados);
	//Cuando acaba lo sacamos por terminal.
	cout << "Mensajes en el Archivo:" << endl << mensajes_guardados << endl;

	archivo.close();

}

void menu_2() {

	string archivo_desencriptar;
	//Preguntamos el nombre del archivo que quiere desencripar y lo almazenamos en una variable.
	cout << "Que archivo quieres desencriptar? EJ: hola.txt" << endl;
	cin >> archivo_desencriptar;

	//Abrimos el archivo como lectura.
	ifstream archivo;
	//Lo abrimos en no create porque en el caso que no exista cuando verifiquemos si esta abierto nos dara false.
	archivo.open(archivo_desencriptar, ios::_Nocreate);

	//En caso que no existe nos dara que archivo.is_open == FALSE
	if (!archivo.is_open())
	{
		cout << "Archivo no existe o no se ha podido abrir correctamente." << endl;
	}
	//Si esta abierto:
	else
	{
		cout << "abierto" << endl;

		string linea;
		string contenido;
		//Sacamos todas las lineas que contenga ese archivo
		while (getline(archivo, linea))
		{
			contenido += linea;
		}
		//Sacamos por terminal lo que tenia el archivo.
		cout << "Contenido del archivo sin desencriptar: " << endl << contenido << endl << endl;

		//Lo desencriptamos.
		contenido = desencriptacion(contenido);
		//Lo sacamos por la salida estandar.
		cout << "Contenido del archivo Desencriptado: " << endl << contenido << endl;

		archivo.close();
	}

}

void menu_3() {

	string archivo_desencriptar;
	bool abierto = false;
	//Preguntamos el nombre
	cout << "Que archivo quieres encriptar? EJ: hola.txt" << endl;
	cin >> archivo_desencriptar;

	//Abrimos en modo append y lectura y escritura. Con el modo append nos creara el archivo si no existe y si no nos añadira al final de todo la información a añadir.
	fstream archivo;
	archivo.open(archivo_desencriptar, ios::app);

	//Verificaión
	if (!archivo.is_open())
	{
		cout << "Archivo no existe o no se ha podido abrir correctamente." << endl;
	}
	else
	{
		cout << "abierto" << endl;
		abierto = true;
	}

	bool fin_mensajes = false;
	string mensaje;
	string mensajes;
	cin.ignore();

	//Si esta abierto o creado el usuario podra insertar.
	while (fin_mensajes == false && abierto == true)
	{
		cout << "Mensaje a enviar" << endl;
		getline(cin, mensaje);


		//Si el mensaje es exit parara.
		if (mensaje == "exit")
		{
			//En caso que ponga exit saldra del bucle.
			fin_mensajes = true;
		}
		else
		{
			//Guardaremos cada mensaje con un salto del linea.
			mensajes += (mensaje + '\n');
		}


	}


	//Añadimos los mensajes nuevos encriptados
	archivo << encriptacion(mensajes);

	//Cerramos el archivo.
	archivo.close();

}





void main() {

	bool programa_activo = true;

	//Mientras el programa este activo:
	while (programa_activo)
	{
		bool menu_correcto = false;
		char user_insert_menu;

		//Verificacion de que pone el numero correcto
		while (!menu_correcto)
		{
			cout << "Que quieres hacer? \n \n 1- Fuerza bruta \n 2- Desencriptar \n 3- Encriptar \n 4- Salir" << endl;
			cin >> user_insert_menu;

			//Verificacion de que pone un char entre el 1 y el 4.
			if (user_insert_menu > '4' || user_insert_menu < '1')
			{
				cout << "numero incorrecto" << endl;
			}
			else
			{
				cout << "mensaje correcto " << endl;
				menu_correcto = true;
			}
		}
		//Con switch ejecutamos la funcion del menu dependiendo del numero. HAGO DOBLE VERIFICACION DEL INPUT. NUNCA TE FIES.
		switch (user_insert_menu)
		{

		case '1':
			menu_1();
			break;

		case '2':
			menu_2();
			break;

		case '3':
			menu_3();
			break;

		case '4':
			programa_activo = false;
			break;


		default:
			break;
		}

	}
}