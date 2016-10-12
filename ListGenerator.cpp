#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

struct Node{
	list<list<bool> > x;
	int cnodes;
	//Incluir información útil
};

list<Node> headers;
list<Node>::iterator it;
list<bool>::iterator itbool;
list<bool>::iterator itbool2;
list<list<bool> >::iterator itlist;

void createList(char argv[]);
void createAndInsert(int jugadores, vector<bool> game,list<bool> part);
void insert(list<Node>::iterator it,vector<bool> game,int jugadores);

/*
Entrada del tipo
<Cantidad de juegos>
<Cantidad de jugadores>
<juego 1>
...
<juego n>
Ejemplo de juego:
0 1 0 1
*/

int main(int arcgc, char *argv[]){
	createList(argv[1]);
	for(it=headers.begin();it!=headers.end();++it){
		cout << (*it).cnodes << endl;
		for(itlist=(*it).x.begin();itlist!=(*it).x.end();++itlist){
			for(itbool=(*itlist).begin();itbool!=(*itlist).end();++itbool)
				cout << (*itbool);
		}
		cout << endl;			
	}
	return 0;
}

void createList(char nombre[]){
	bool flag = 0;
	int jugadores,juegos;
	ifstream entrada(nombre);
	entrada >> juegos;
	entrada >> jugadores;
	while(juegos!=0){
		vector<bool> game;
		list<bool> part;
		flag = 0;
		//Lee juego y guarda la potencial cabecera
		for (int j=0;j<jugadores;j++){
			bool value;
			entrada >> value;
			game.push_back(value);
			if(j<jugadores/2)
				part.push_back(game[j]);
		}
		//Compara si la cabecera existe
		for(it=headers.begin();it!=headers.end();++it){
			int count = 0;
			for(itbool=(*it).x.front().begin(),itbool2=part.begin();
                itbool!=(*it).x.front().end(), itbool2!=part.end();
				++itbool,++itbool2){
				if((*itbool)==(*itbool2))
					count++;
			}
			if(count==jugadores/2){
				flag = 1;
				break;
			}
		}
		//Si existe se inserta la cola
		if(flag)
			insert(it,game,jugadores);
		//Si no existe, se crea la cabecera y se inserta la cola
		else{
			createAndInsert(jugadores,game,part);
		}
		juegos--;
	}
	entrada.close();
}

//Función para insertar cuando la cabecera ya existe
void insert(list<Node>::iterator it,vector<bool> game,int jugadores){
	list<bool> part2;
	for(int i=jugadores/2;i<jugadores;i++)
		part2.push_back(game[i]);
	(*it).x.push_back(part2);	
	(*it).cnodes++;
}

//Función para insertar cuando la cabecera no existe
void createAndInsert(int jugadores, vector<bool> game,list<bool> part){
	Node node;
	node.x.push_back(part);
	node.cnodes=0;
	list<bool> part2;
	for(int j=jugadores/2;j<jugadores;j++){
		part2.push_back(game[j]);
	}
	node.x.push_back(part2);
	node.cnodes++;
	headers.push_back(node);
}