#include "grafo.h"
#include <fstream>
#include <sstream>
#include <cmath>

unordered_map<int, Aeropuerto>     aeropuertos;
unordered_map<int, vector<Arista>> adyacencia;
unordered_map<string, int>         iata_a_id;

double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    const double R  = 6371.0;
    const double PI = acos(-1.0);
    double dLat = (lat2 - lat1) * PI / 180.0;
    double dLon = (lon2 - lon1) * PI / 180.0;
    lat1 = lat1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;
    double a = sin(dLat/2)*sin(dLat/2) + cos(lat1)*cos(lat2)*sin(dLon/2)*sin(dLon/2);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    return R * c;
}

vector<string> parsearLinea(const string& linea) {
    vector<string> campos;
    string campo;
    bool enComillas = false;
    for (char c : linea) {
        if (c == '"') {
            enComillas = !enComillas;
        } else if (c == ',' && !enComillas) {
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c;
        }
    }
    campos.push_back(campo);
    return campos;
}

void cargarAeropuertos(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << archivo << endl;
        return;
    }
    string linea;
    getline(file, linea);
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        vector<string> c = parsearLinea(linea);
        if (c.size() < 8) continue;     
        try {
            Aeropuerto a;
            a.id     = stoi(c[0]);
            a.nombre = c[1];
            a.ciudad = c[2];
            a.pais   = c[3];
            a.IATA   = c[4];
            a.ICAO   = c[5];
            a.lat    = stod(c[6]);
            a.lon    = stod(c[7]);
            aeropuertos[a.id] = a;
            iata_a_id[a.IATA] = a.id;  
        } catch (...) { continue; }         
    }
    cout << "Aeropuertos cargados: " << aeropuertos.size() << endl;
}

void cargarRutas(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << archivo << endl;
        return;
    }
    string linea;
    getline(file, linea);
    int count = 0;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        vector<string> c = parsearLinea(linea);
        if (c.size() < 4) continue; 
        try {
            int id_destino   = (int)stod(c[0]);
            int id_origen    = (int)stod(c[1]);
            string aerolinea = c[2];
            int id_aerolinea = (int)stod(c[3]);

            Aeropuerto& orig = aeropuertos[id_origen];
            Aeropuerto& dest = aeropuertos[id_destino];

            Arista a;
            a.id_Origen    = id_origen;
            a.id_Destino   = id_destino;
            a.Distancia    = calcularDistancia(orig.lat, orig.lon, dest.lat, dest.lon);
            a.aerolinea    = aerolinea;
            a.id_aerolinea = id_aerolinea;

            adyacencia[id_origen].push_back(a);
            count++;
        } catch (...) { continue; }   
    }
    cout << "Rutas cargadas: " << count << endl;
}
