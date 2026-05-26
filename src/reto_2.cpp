#include "reto_2.h"
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int inicio, unordered_map<int, bool>& visitado, stack<int>& pila) 
{
    stack<pair<int, int>> stk;
    stk.push({inicio, 0});
    visitado[inicio] = true;

    while (!stk.empty()) 
    {
        int v   = stk.top().first;
        int& idx = stk.top().second;
        bool avanzado = false;

        if (adyacencia.count(v)) 
        {
            while (idx < (int)adyacencia[v].size()) 
            {
                int sig = adyacencia[v][idx].id_Destino;
                idx++;
                if (!visitado.count(sig)) 
                {
                    visitado[sig] = true;
                    stk.push({sig, 0});
                    avanzado = true;
                    break;
                }
            }
        }
        if (!avanzado) 
        {
            pila.push(v);
            stk.pop();
        }
    }
}

int dfs2(int inicio, unordered_map<int, vector<int>>& trans, unordered_map<int, bool>& visitado) 
{
    stack<int> stk;
    stk.push(inicio);
    visitado[inicio] = true;
    int tam = 0;

    while (!stk.empty()) 
    {
        int v = stk.top(); 
        stk.pop();
        tam++;
        if (!trans.count(v)) continue;
        for (int i = 0; i < (int)trans[v].size(); i++) 
        {
            int vecino = trans[v][i];
            if (!visitado.count(vecino)) 
            {
                visitado[vecino] = true;
                stk.push(vecino);
            }
        }
    }
    return tam;
}

void resolverReto2() {
    cout << "\n=== RETO 2: Grupos y Aislamiento Aereo ===" << endl;

    stack<int> pila;
    unordered_map<int, bool> vis1;
    for (auto it = aeropuertos.begin(); it != aeropuertos.end(); ++it) 
    {
        if (!vis1.count(it->first)) 
        {
            dfs1(it->first, vis1, pila);
        }
    }

    unordered_map<int, vector<int>> trans;
    for (auto it = adyacencia.begin(); it != adyacencia.end(); ++it) 
    {
        int origen = it->first;
        for (int i = 0; i < (int)it->second.size(); i++) 
        {
            int dest = it->second[i].id_Destino;
            trans[dest].push_back(origen);
        }
    }

    unordered_map<int, bool> vis2;
    int total_grupos  = 0;
    int mayor_grupo   = 0;
    int grupos_grandes = 0; 

    while (!pila.empty()) 
    {
        int v = pila.top(); pila.pop();
        if (!vis2.count(v)) 
        {
            int tam = dfs2(v, trans, vis2);
            total_grupos++;
            mayor_grupo = max(mayor_grupo, tam);
            if (tam > 1) grupos_grandes++;
        }
    }

    cout << "Total de SCCs encontrados       : " << total_grupos   << endl;
    cout << "Grupos con mas de 1 aeropuerto  : " << grupos_grandes << endl;
    cout << "Tamano del grupo mas grande     : " << mayor_grupo    << endl;
}
