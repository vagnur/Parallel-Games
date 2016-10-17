#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int tot=0;
vector<vector<bool> > minimales;
vector<vector<bool> > resultado;

bool comparar(vector<bool> game1, vector<bool> game2);
void redundantes(vector<bool> game,vector<bool> redundante,bool value,int i);

int main(int argc,char *argv[]){
	int jugadores,lineas;
	ifstream entrada(argv[1]);
	ofstream salida("resultado.txt");
	entrada >> lineas;
	entrada >> jugadores;
	vector<bool> x;
	vector<bool> y;
	while(lineas!=0){
		for(int i=0;i<jugadores;i++){
			bool value;
			entrada >> value;
			x.push_back(value);
		}
		redundantes(x,y,x[0],0);
		minimales.push_back(x);
		x.clear();
		lineas --;
	}
	salida << resultado.size() << '\n';
	salida << jugadores << '\n';
	for(int i=0;i<resultado.size();i++){
		for(int j=0;j<resultado[i].size();j++){
			salida << resultado[i][j] << " ";
		}
		salida << '\n';
	}
	entrada.close();
}

bool comparar(vector<bool> game1, vector<bool> game2){
	for (int i=0;i<game1.size();i++){
		if(game1[i] > game2[i]) return 1;
	}
	return 0;
}

void redundantes(vector<bool> game,vector<bool> redundate,bool value,int i){
	if(i!=0)
		redundate.push_back(value);
	if(game.size()==redundate.size()){
		int flag = 1;
		for(int j=0;j<minimales.size();j++){
			if(comparar(minimales[j],redundate)==0) {flag=0;break;}
		}
		if(flag==1){
			resultado.push_back(redundate);
		}
	}
	else{
		if(game[i]==1)
			redundantes(game,redundate,1,i+1);
		else{
			redundantes(game,redundate,0,i+1);
			redundantes(game,redundate,1,i+1);
		}
	}
	
}