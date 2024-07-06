#pragma once
#include <iostream>
using namespace std;

class Arbol
{
private:
	string especie;
	double altura;
	double diametro;
	int edad;
	int salud;
	int posRegistro;

public:
	Arbol() {

		this->especie = "";
		this->altura = 0.0;
		this->diametro = 0.0;
		this->edad = 0;
		this->salud = 0;
		this->posRegistro = 0;
	}

	Arbol(string especie, double altura, double diametro, int edad, int salud, int posRegistro) : especie(especie), altura(altura), diametro(diametro), edad(edad),
		salud(salud), posRegistro(posRegistro) {}


	void printDatos() {
		cout << "\nArbol " << this->posRegistro << ":";
		cout << "\nEspecie " << this->especie;
		cout << "\nAltura: " << this->altura << " cm";
		cout << "\nDiametro: " << this->diametro << " cm";
		cout << "\nSalud (en escala del 1 - 10): " << this->salud;
		cout << "\nEdad: " << this->edad << " anios\n";
		
		
	}

	int getEdad() {
		return edad;
	}
	double getAltura() {
		return altura;
	}

    
    

	~Arbol();

};
