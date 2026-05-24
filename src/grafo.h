#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Aeropuerto {
    int id;
    string nombre, ciudad, pais;
    string IATA, ICAO;
    double lat, lon;
};

struct Arista {
    int id_Destino;
    int id_Origen;
    double Distancia;
    string aerolinea;
    int id_aerolinea;
};

extern unordered_map<int, Aeropuerto>     aeropuertos;
extern unordered_map<int, vector<Arista>> adyacencia;
extern unordered_map<string, int>         iata_a_id;

void   cargarAeropuertos(const string& archivo);
void   cargarRutas(const string& archivo);
double calcularDistancia(double lat1, double lon1, double lat2, double lon2);

#endif
