#include "grafo.h"
#include "reto_1.h"
#include "reto_2.h"
#include "reto_3.h"
#include "reto_4.h"
#include "reto_5.h"
using namespace std;

void Menu_Principal() {
    cargarAeropuertos("../data/airports_final.csv");
    cargarRutas("../data/routes_final.csv");

    int opcion;
    do {
        cout << "\n========= MENU PRINCIPAL =========" << endl;
        cout << "1. Reto 1 - Alcance Personalizado (BFS)"      << endl;
        cout << "2. Reto 2 - Grupos y Aislamiento Aereo (Kosaraju)" << endl;
        cout << "3. Reto 3 - La Maxima Eficiencia / Diametro (Dijkstra)" << endl;
        cout << "0. Salir"                                       << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: resolverReto1(); break;
            case 2: resolverReto2(); break;
            case 3: resolverReto3(); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}

int main() {
    Menu_Principal();
    return 0;
}
