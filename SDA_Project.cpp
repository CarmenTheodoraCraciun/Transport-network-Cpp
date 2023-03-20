#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include<set>
#include<vector>
#include <string>
#include<algorithm>

#include "LinkedListElem.h";
#include "Edge.h";
#include "Graph.h";

using namespace std;

void getDate(string path);
void Kruscal();

set<string> cities;
vector<Edge*> edges;

/*afisaza datele cerute*/
void showDate() {
    system("cls");
    cout << "The optimal way for the gas network:" << endl;
    double s = 0;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        cout <<"\t"<< **it << endl;
        s += (*it)->getD();
    }
    cout << "The total distance covered is " << s << " km\nExample of browsing:\n";
    Graph* g=new Graph(cities.size());
    for (auto it = edges.begin(); it != edges.end(); ++it)
        g->addEdge(cities, (*it)->getC1(), (*it)->getC2());
    g->getPath(cities);
}

//Proiectare unei retele de gaz
int main(){
    cout << "\tGas network\n\nGive a path of a CSV file the like:\nCity 1,City 2, Distance\nEnter the path\n";
    string path;
    cin >> path; 
    //path = "./Cities_OT.csv";
    getDate(path);
    Kruscal();
    showDate();
    return 0;
}

bool compare(Edge* x, Edge* y) {
    return (x->getD() < y->getD());
}

/*citeste datele din fisier
cities va fi multimea de noduri a grafurlui
edges va fi multumea de muchii a grafului*/
void getDate(string path) {
    ifstream fin(path);
    if(fin.is_open()) {
        string line;
        getline(fin, line);
        while (getline(fin, line)) {
            stringstream s(line);
            string x; string v[3]; int i = -1;
            while (getline(s, x, ','))
                //g.addEdge(v[0], v[2], v[3]);
                v[++i] = x;
            cities.insert(v[0]);
            cities.insert(v[1]);
            edges.push_back(new Edge(v[0], v[1], v[2]));
        }
        //sortam dupa distanta
        sort(edges.begin(), edges.end(), compare);
        fin.close();
    }
    else{
        system("cls");
        cout << path << " could not open\n";
        main();
    }
}

/*sterge muchii din edges
edges devine MST*/
void Kruscal() {
    //dijointSet
    for (auto it = cities.begin(); it != cities.end(); ++it)
        //cream cate o multime pentru fiecare oras
        LLelem[*it] = LinkedListElem::MakeSet(*it);
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        bool unionDone = false;
        LinkedListElem::Union(LLelem[(*it)->getC1()], LLelem[(*it)->getC2()],unionDone);
        if (!unionDone) {
            //daca deja fac parte din aceeasi multime atunci muchia *it creaza un ciclu
            //deci o stergem
            auto it2 = it-1;
            edges.erase(it);
            it = it2;
        }
    }
}

