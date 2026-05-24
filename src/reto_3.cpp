#include "reto_3.h"
#include <queue>
#include <algorithm>

using namespace std;

const double INF = 1e18;


//Dijkstra
unordered_map<int, double> dijkstra(int origen) 
{
    unordered_map<int, double> dist;
    dist[origen] = 0.0;

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
    pq.push({0.0, origen});

    while (!pq.empty()) 
    {
        double d = pq.top().first;
        int    u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue; 

        if (!adyacencia.count(u)) continue;
        for (int i = 0; i < (int)adyacencia[u].size(); i++) 
        {
            int    v    = adyacencia[u][i].id_Destino;
            double nd   = d + adyacencia[u][i].Distancia;
            if (!dist.count(v) || nd < dist[v]) 
            {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dist;
}

void resolverReto3() 
{
    cout << "\n=== RETO 3: La Maxima Eficiencia (Diametro) ===" << endl;
    cout << "Calculando diametro del grafo (puede tomar unos minutos)..." << endl;

    double max_dist    = 0.0;
    int mejor_origen   = -1;
    int mejor_destino  = -1;

    for (auto it = adyacencia.begin(); it != adyacencia.end(); ++it) 
    {
        int id_origen = it->first;
        unordered_map<int, double> dist = dijkstra(id_origen);

        for (auto jt = dist.begin(); jt != dist.end(); ++jt) 
        {
            int    id_dest = jt->first;
            double d       = jt->second;
            if (id_dest != id_origen && d > max_dist) 
            {
                max_dist       = d;
                mejor_origen   = id_origen;
                mejor_destino  = id_dest;
            }
        }
    }

    if (mejor_origen == -1) 
    {
        cout << "No se encontro ninguna ruta valida." << endl;
        return;
    }

    Aeropuerto& orig = aeropuertos[mejor_origen];
    Aeropuerto& dest = aeropuertos[mejor_destino];

    cout << "Par de aeropuertos con mayor camino minimo:" << endl;
    cout << "  Origen  : " << orig.nombre << " (" << orig.IATA << ") - " << orig.ciudad << ", " << orig.pais << endl;
    cout << "  Destino : " << dest.nombre << " (" << dest.IATA << ") - " << dest.ciudad << ", " << dest.pais << endl;
    cout << "  Distancia: " << (int)max_dist << " km" << endl;
}
