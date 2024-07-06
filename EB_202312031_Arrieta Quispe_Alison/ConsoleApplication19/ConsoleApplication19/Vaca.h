#pragma once
#include <iostream>
using namespace std;

class Vaca
{
private:
	int id;
	string nombre;
	double kilos;
	string color;
	int edad;
	int posRegistro;

public:
	Vaca() {
		this->id = 0;
		this->nombre = "";
		this->kilos = 0.0;
		this->color = "";
		this->edad = 0;		
		this->posRegistro = 0;
	}

	Vaca(int id, string nombre, double kilos, string color, int edad, int pos) : id(id), nombre(nombre),
		kilos(kilos), color(color), edad(edad), posRegistro(pos){}


	void printDatos() {
		cout << "\nVaca " << this->posRegistro << ":";
		cout << "\nNombre: " << this->nombre;
		cout << "\nID: " << this->id;
		cout << "\nKilos: " << this->kilos << " kg";
		cout << "\nColor: " << this->color;
		cout << "\nEdad: " << this->edad << " anios\n";
	}

	int getEdad() {
		return edad;
	}
	double getKilos() {
		return kilos;
	}

    
    

	~Vaca();

};
