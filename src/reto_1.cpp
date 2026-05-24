#include "reto_1.h"
#include <queue>

using namespace std;


// BFS
int AlcancePersonalizado(int id_origen) 
{
    if (!aeropuertos.count(id_origen)) return 0;

    queue<pair<int, int>> cola; 
    unordered_map<int, bool> visitado;

    visitado[id_origen] = true;
    cola.push({id_origen, 0});
    int alcanzados = 0;

    while (!cola.empty()) {
        int id     = cola.front().first;
        int saltos = cola.front().second;
        cola.pop();

        if (saltos >= 3) continue;

        if (!adyacencia.count(id)) continue;
        for (int i = 0; i < (int)adyacencia[id].size(); i++) 
        {
            int dest = adyacencia[id][i].id_Destino;
            if (!visitado.count(dest)) 
            {
                visitado[dest] = true;
                alcanzados++;
                cola.push({dest, saltos + 1});
            }
        }
    }
    return alcanzados;
}

void resolverReto1() {
    cout << "\n=== RETO 1: Alcance Personalizado ===" << endl;
    cout << "Ingresa el codigo IATA o nombre del aeropuerto: ";
    string input;
    cin.ignore();
    getline(cin, input);

    int id = -1;
    if (iata_a_id.count(input)) 
    {
        id = iata_a_id[input];
    }
    else 
    {
        for (auto it = aeropuertos.begin(); it != aeropuertos.end(); ++it) 
        {
            if (it->second.nombre == input) 
            {
                id = it->first;
                break;
            }
        }
    }

    if (id == -1) 
    {
        cout << "Aeropuerto no encontrado." << endl;
        return;
    }

    Aeropuerto& a = aeropuertos[id];
    cout << "Aeropuerto: " << a.nombre << " (" << a.IATA << ") - " << a.ciudad << ", " << a.pais << endl;
    int alcance = AlcancePersonalizado(id);
    cout << "Aeropuertos alcanzables con maximo 3 escalas: " << alcance << endl;
}
