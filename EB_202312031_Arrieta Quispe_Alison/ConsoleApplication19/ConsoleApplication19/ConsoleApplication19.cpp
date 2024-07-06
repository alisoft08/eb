#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include "List.h"
#include "Arbol.h"
#include "ArbolBusquedaBinaria.h"
#include "HashTable.h"
#include "Grafo.h"

using namespace std;
using namespace dby;

vector<string> especies = { "Sauce", "Encino","Cocotero","Magnolia","Olivo","Nogal","Laurel","Almendro"
};

List<Arbol*>* listaArboles = new List<Arbol*>();
List<Arbol*>* listaArbolesOrdenada = new List<Arbol*>();
BST<int> arbolBusquedaBinaria;
CGrafo<int>* graph = new CGrafo<int>();

//INICIALIZANDO UN HASH TABLE, la funcion esta dentro de la clase usando metodo de division de horner para evitar colisiones
HashTable<string, int> hashTable(100, false);


//CREANDO GRAFO
void crearGrafo() {
    graph->adicionarVertice('A'); //indice 0
    graph->adicionarVertice('B'); //indice 1
    graph->adicionarVertice('C'); //indice 2
    graph->adicionarVertice('D'); //indice 3
    graph->adicionarVertice('E'); //indice 4
    graph->adicionarVertice('F'); //indice 5

    graph->adicionarArco(0, 1);
    graph->modificarArco(0, 0, 10);
    graph->adicionarArco(1, 2);
    graph->modificarArco(1, 0, 15);
    graph->adicionarArco(2, 3);
    graph->modificarArco(2, 0, 12);
    graph->adicionarArco(1, 3);
    graph->modificarArco(1, 1, 20);
    graph->adicionarArco(4, 0);
    graph->modificarArco(4, 0, 18);
    graph->adicionarArco(5, 0);
    graph->modificarArco(5, 0, 13);
    graph->adicionarArco(3, 4);
    graph->modificarArco(3, 0, 6);
}

//FUNCION PARA IMPRIMIR GRAFO CON TEMPLATES
template<typename T>
void imprimirGrafo(CGrafo<T>* G) {


    for (int i = 0; i < G->cantidadVertices(); ++i) {
        char verInicio = G->obtenerVertice(i);
        cout << "De la esquina " << verInicio << " a la(s) esquina(s):\n";

        for (int j = 0; j < G->cantidadArcos(i); j++)
        {
            char verLlegada = G->obtenerVertice(G->obtenerVerticeLlegada(i, j));
            cout << verLlegada;
            cout << " existen " << G->obtenerArco(i, j) << " km";
            cout << endl;
        }
        cout << endl;
    }

}

//FUNCION PARA VERIFICAR SI EL NODO A ELIMINAR DEL ARBOL BINARIO DE BUSQUEDA ES IMPAR
bool esImpar(int num) {
    if (num % 2 == 0) {
        return false;
    }
    else {
        return true;
    }
}

//BUSQUEDA BINARIA - PREVIAMENTE DEBE ESTAR ORDENADO
int busquedaBinaria(List<Arbol*>* lista, double altura) {
    int izquierda = 0;
    int derecha = lista->size() - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        
        if (lista->at(medio)->getAltura()<altura) {
            izquierda = medio + 1;
           
        }
       
        else if (lista->at(medio)->getAltura()>altura) {
            derecha = medio - 1;
        }
        // Si encuentra el peso buscado, devuelve el índice
        else {
            return medio;
        }
    }
    // Si no se encuentra el peso, devuelve -1
    return -1;
}


//ORDENANDO SEGUN ALTURAS CON MERGE SORT
void Merge(List<Arbol*>* vector1, List<Arbol*>* vector2, List<Arbol*>* vector, int n)
{
    int i = 0, j = 0, k = 0;
    int mitad = n / 2;
    while (i < mitad && j < n - mitad)
    {
        if (vector1->at(i)->getAltura() < vector2->at(j)->getAltura())
        {
            vector->insert(k, vector1->at(i));
            k++; i++;
        }
        else
        {
            vector->insert(k, vector2->at(j));
            k++; j++;
        }
    }

    while (i < mitad)
    {
        vector->insert(k, vector1->at(i));
        k++; i++;
    }

    while (j < n - mitad)
    {
        vector->insert(k, vector2->at(j));
        k++; j++;
    }
}

void MergeSort(List<Arbol*>* vector, int n)
{
    if (n > 1)
    {
        int mitad = n / 2;
        List<Arbol*>* vector1 = new List<Arbol*>();
        List<Arbol*>* vector2 = new List<Arbol*>();

        for (int i = 0; i < mitad; i++)
        {
            vector1->insert(i, vector->at(i));
        }
        for (int i = mitad; i < n; i++)
        {
            vector2->insert(i - mitad, vector->at(i));
        }

        MergeSort(vector1, mitad);
        MergeSort(vector2, n - mitad);
        Merge(vector1, vector2, vector, n);

        
    }
}

//LLENANDO DATOS A LISTAS DE FORMA ALEATORIA

void llenarDatos(int& it, long long& cantTotalArboles) {

    

    int cantArbol;
    string especie;
    double altura;
    double diametro;
    int edad;
    int salud;
    int posRegistro;

    cout << "Ingrese la cantidad de Vacas a registrar: "; cin >> cantArbol;
    for (int i = 0; i < cantArbol; i++) {
        

        
        
        especie = especies[rand() % especies.size()];
        

        altura = rand() % (600 - 200) + 200;
        altura = (double)altura / 100;
        
        diametro = rand() % (200 - 100) + 100;
        diametro = (double)diametro / 100;

        edad = rand() % (900 - 20) + 20;
        salud = rand() % (10 - 1) + 1;
        

        Arbol* arbol = new Arbol(especie, altura, diametro, edad, salud, it + 1);
        arbolBusquedaBinaria.insert(edad);
        //EN ESTE CASO LA 'KEY' ES UN STRING ENTONCES SE APLICA EL METODO DE POLINOMIO DE HORNER PARA QUE HACERLO HASH
        hashTable.insert(especie, edad);
        listaArboles->push_back(arbol);

        it++;
    }

    cantTotalArboles += cantArbol;
}

//IMPLEMENTANDO METODOS RECURSIVOS

Arbol* encontrarArbolMayorAltura(List<Arbol*>* lista, int n) {
    // Caso base: si la lista tiene un solo elemento
    if (n == 1) {
        return lista->at(0);
    }

    // Llamada recursiva: encontrar el árbol con la mayor altura en el resto de la lista
    Arbol* maxResto = encontrarArbolMayorAltura(lista, n - 1);

    // Comparar el último árbol con el árbol con la mayor altura del resto
    return (lista->at(n - 1)->getAltura() > maxResto->getAltura()) ? lista->at(n - 1) : maxResto;
}


Arbol* encontrarArbolMenorEdad(List<Arbol*>* lista, int n) {
    // Caso base: si la lista tiene un solo elemento
    if (n == 1) {
        return lista->at(0);
    }

    // Llamada recursiva: encontrar el árbol con la menor edad en el resto de la lista
    Arbol* minResto = encontrarArbolMenorEdad(lista, n - 1);

    // Comparar el último árbol con el árbol con la menor edad del resto
    return (lista->at(n - 1)->getEdad() < minResto->getEdad()) ? lista->at(n - 1) : minResto;
}


double sumaAlturasArboles(List<Arbol*>* lista, int n) {
    // Caso base: si la lista está vacía
    if (n == 0) {
        return 0.0;
    }

    // Llamada recursiva: sumar la altura del último árbol con la suma de las alturas del resto
    return lista->at(n - 1)->getAltura() + sumaAlturasArboles(lista, n - 1);
}


//IMPRIEMIENTO ELEMENTOS DE UN ARBOL BINARIO DE BUSQUEDA, EN ORDEN, PRE ORDEN Y POST ORDEN
template <typename T>
void printValue(T value) {
    cout << value << " ";
}

template<typename T>
void printTree(BST<T>& arbol) {
    cout << "\nPre Orden : ";
    arbol.traverse(bst_traverse::pre_order, printValue<T>);

    cout << "\nEn Orden: ";
    arbol.traverse(bst_traverse::in_order, printValue<T>);

    cout << "\nPost Orden: ";
    arbol.traverse(bst_traverse::post_order, printValue<T>);

}
int menu() {
    cout << "\n";
    cout << "-------------------------------------" << endl;
    cout << "======================MENU===============" << endl;
    cout << "<1>    Ingresar Arboles" << endl;
    cout << "<2>    Busqueda Binaria (con Altura)" << endl;
    cout << "<3>    Listar datos de Arbol" << endl;
    cout << "<4>    Listar datos de Arbol ordenados (MergeSort - segun altura)" << endl;
    cout << "<5>    Implementar Hash Table (especie, edad)" << endl;
    cout << "<6>    Mostrar elementos del arbol de busqueda binaria (edades)" << endl;
    cout << "<7>    Eliminar nodo del arbol" << endl;
    cout << "<8>    Ver grafo de distancias de las sedes" << endl;
    cout << "<9>    Usar funciones recursivas" << endl;
    cout << "<10>   Salir." << endl;
    cout << "-------------------------------------" << endl;
    cout << "Ingrese una opcion: ";
    int opcion;
    do
    {
        cin >> opcion;
        if (opcion < 0 || opcion>10)
            cout << "Ingrese una opcion valida... ";
    } while (opcion < 0 || opcion>10);

    return opcion;
}

int main()
{
    int* mayor;
    int it = 0;
    long long cantTotalArboles = 0;
    bool estaOrdenado = false;
    srand(time(NULL));

    int opcion = 0;

    while (opcion != 10) {
        system("cls");
        opcion = menu();
        int opcionRecursiva = 0;
        switch (opcion)
        {
        case 1:
            system("cls");
            llenarDatos(it, cantTotalArboles);
            estaOrdenado = false;
            cout << "Presiona cualquier tecla para continuar...";
            _getch();
            break;

        case 2:
            //IMPLEMENTA EL METODO DE BUSQUEDA BINARIA
            system("cls");
            if (!estaOrdenado) {
                cout << "Ordene la lista primero en la opcion 4...\n";
            }
            else {
                double alturaBuscar;
                cout << "Ingrese la altura que desea buscar: ";
                cin >> alturaBuscar;
                int indice = busquedaBinaria(listaArbolesOrdenada, alturaBuscar);
                if (indice == -1) {
                    cout << "No se encuentra el elemento...\n";
                }
                else {

                    cout << "El elemento buscado '" << alturaBuscar << "' se encuentra en la posicion: \n" << indice;
                    cout << endl;
                }
            }
            cout << "Presiona cualquier tecla para continuar...";
            _getch();
            break;
            
        case 3:
            system("cls");
            if (cantTotalArboles < 1) {
                cout << "Registre arboles primero...\n";
            }
            else {
                for (int i = 0; i < cantTotalArboles; i++) {
                    listaArboles->at(i)->printDatos();
                }
            }
            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;

        case 4:
            system("cls");
            if (cantTotalArboles < 1) {
                cout << "Registre arboles primero...\n";
            }
            else {
                // Limpiar la lista ordenada antes de llenarla de nuevo
                estaOrdenado = true;
                listaArbolesOrdenada->clear();

                for (int i = 0; i < cantTotalArboles; i++) {
                    listaArbolesOrdenada->push_back(listaArboles->at(i));
                }
                int n = cantTotalArboles;
                MergeSort(listaArbolesOrdenada, n);

                for (int i = 0; i < cantTotalArboles; i++) {
                    listaArbolesOrdenada->at(i)->printDatos();
                }
            }
            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;
        case 5:
            system("cls");
            //IMPLEMENTANDO HASH TABLE AL CUAL YA LE HEMOS AGREGADO ELEMENTOS EN LA FUNCION: LLENARDATOS() 


           
            hashTable.for_each([](std::pair<std::string, int> item) {
                cout << "Clave: " << item.first << ", Valor: " << item.second << endl;
                });
            
            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;



        case 6:
            system("cls");
            //IMPLEMENTANDO UN ARBOL DE BUSQUEDA BINARIA AL CUAL YA LE HEMOS AGREGADO ELEMENTOS EN LA FUNCION LLENARDATOS()
            printTree(arbolBusquedaBinaria);
            
            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;

        case 7:
            system("cls");
            //ELIMINANDO NODO DESEADO POR EL USUARIO Y MOSTRANDO EL ARREGLO DEL ARBOL BINARIO DE BUSQUEDA SIN EL EL NODO
            int nodo;
            do {
                cout << "Ingrese nodo que desea eliminar: \n";
                cin >> nodo;
                if (!arbolBusquedaBinaria.search(nodo)) {
                    cout << "El nodo ingresado no existe actualmente en el arbol...\n";
                }
            } while (!arbolBusquedaBinaria.search(nodo));
            
            cout << "Arbol de busqueda binaria sin '" << nodo << "':\n";
            arbolBusquedaBinaria.remove(nodo);
            printTree(arbolBusquedaBinaria);
            
            if (esImpar(nodo)) {
                cout << "\nEl numero eliminado era impar.\n";
            }
            

            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;
        
        case 8:
            system("cls");
            crearGrafo();
            imprimirGrafo(graph);
            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;

        case 9:

            system("cls");
            if (cantTotalArboles < 1) {
                cout << "Registre arboles primero...\n";
            }
            else {

                cout << "<1> Encontrar arbol de mayor altura\n";
                cout << "<2> Encontrar arbol de menor edad\n";
                cout << "<3> Hayar la suma total de alturas de los arboles\n\n";
                cout << "Ingres opcion: ";
                do
                {
                    cin >> opcionRecursiva;
                    if (opcionRecursiva < 0 || opcionRecursiva>10)
                        cout << "Ingrese una opcion valida... ";
                } while (opcionRecursiva < 0 || opcionRecursiva>10);

                if (opcionRecursiva == 1) {
                    cout << "\nEl arbol de mayor altura es: \n";
                    encontrarArbolMayorAltura(listaArboles, listaArboles->size())->printDatos();
                }
                else if (opcionRecursiva == 2) {
                    cout << "<<\El arbol de menor edad es: \n";
                    encontrarArbolMenorEdad(listaArboles, listaArboles->size())->printDatos();
                }
                else {
                    cout << "\nLa suma total de alturas de los arboles es: " << sumaAlturasArboles(listaArboles, listaArboles->size());
                }
            }
            cout << "\nPresiona cualquier tecla para continuar...";
            _getch();
            break;


            
        default:
            break;

        }
    }

    delete listaArboles; 
    delete listaArbolesOrdenada; 

    return 0;
}

