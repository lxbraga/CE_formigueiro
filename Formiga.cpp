#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

vector<int> lista_formigas;

vector<int> look(int position[2], int mapa_ent[100][100], int look_distance){
  int x = position[0];
  int y = position[1];
  int look_x, look_y;
  int mov_x, mov_y;

  for(int i = 0; i < look_distance; i++){
    look_x = x + look_distance/2 - i;
    if( look_x < 0){ look_x = 0;}
    
    for(int j = 0; j < look_distance; j++){
      look_y = y + look_distance/2 - j;
      if( look_y < 0){ look_y = 0;}
      
      if(mapa_ent[(look_x)][(look_y)] != 0){
        mov_x = look_x/abs(look_x);
        mov_y = look_y/abs(look_y);
        vector<int> vetor = {mov_x, mov_y};
        return vetor;
      }
        
    }
  }
  vector<int> vetor = {0, 0};
  return vetor;
}

class Formiga{
public:  
  int id;
  int x, y; //posição dela no mapa
  int borda_h, borda_v; // limite de movimento no mapa
  int state; // procurando comida, indo pro formigueiro...
  int passo[2] = {-1, 1};
  int paths[8][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {-1,1}, {1,-1}, {-1,-1} };
  //vector<vector<int> > caminhos(8);

  void andar(){
    
    vector<vector<int> > caminhos(8);
    for ( int i = 0 ; i < 8 ; i++ )
        caminhos[i].resize(2);
    
    for ( int i = 0 ; i < 8 ; i++ ){
      for(int j = 0; j < 2; j++){
        caminhos[i][j] = paths[i][j];        
      }
    }
    cout << "formiga ajeitou caminho" << "\n";
    srand (time(NULL));
    while( x + passo[0] == 0 || x + passo[0] == borda_h-1 || y + passo[1] == 0 || y + passo[1] == borda_v-1){
    cout << "formiga escolhendo caminho" << "\n";
    int k = rand() % 9;
    passo[0] = caminhos[k][0];
    passo[1] = caminhos[k][1];
      
    }
    x = x + passo[0];
    y = y + passo[1];

  //cout << "\n";
  cout << "formiga deu passo " << "\n";  
  //cout << "x"
  }
  
};

class Mapa{
public:
  int x, y; //Implementa um limite para o mapa
  int mapa_f[100][100] {0}; //Mapa limitado para 100x100 - este para formigas
  int mapa_ent[100][100] {0};
    vector <Formiga> n_ants;

  void add_ant(Formiga ant){
    n_ants.push_back(ant);
  }

  void popular(){
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
          mapa_f[i][j] = 0;
        }
      }
    
    for(int i = 0; i < n_ants.size(); i++){

      mapa_f[n_ants[i].x][n_ants[i].y] = mapa_f[n_ants[i].x][n_ants[i].y] + 1;
    }
  }

  void plot(){
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
        //COMEÇA A PLOTAR AS BORDAS
        if(i == 0 && j == y - 1){ 
          cout << "#" << "\n";}
          
        else if(i == 0 || i == x - 1){
          cout << "#";}
          
        else if(j == 0 ){
          cout << "#";}
          
        else if(j == y - 1){
          cout << "#" << "\n";}
        //TERMINA DE PLOTAR AS BORDAS

        else if(mapa_f[i][j] != 0){
                  cout<<"f";}
        
          
        else{
          cout << " ";       

          
        }
        //if(i == 30 - 1){cout << "#" << "\n";} 
        }
    }
  }
};
