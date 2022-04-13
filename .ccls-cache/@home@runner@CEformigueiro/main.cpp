#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <pthread.h>
#include <thread>


using namespace std;


vector<int> look(int x, int y, int mapa_fero[100][100], int mapa_food[100][100], int look_distance){
  // define as variáveis
  int x_min = x - look_distance;
  int x_max = x + look_distance;
  int y_min = y - look_distance;
  int y_max = y + look_distance;
  
  int look_x, look_y;
  int mov_x, mov_y;
  int retorno = 0;

  //cout << "Coordenadas calculadas: " ;
  
  for(int x_i = x_min; x_i < x_max; x_i++){
    look_x = x_i - x;
    
    for(int y_i = y_min; y_i < y_max; y_i++){
      look_y = y_i - y;

      
      if(mapa_food[(x_i)][(y_i)] != 0){
        if(look_x == 0){mov_x = 0;}
        else{mov_x = look_x/abs(look_x);}
        if(look_y == 0){mov_y = 0;}
        else{mov_y = look_y/abs(look_y);}

        retorno = 1;
        vector<int> vetor = {retorno,mov_x, mov_y, look_x, look_y};
        return vetor;
      }
      if(mapa_fero[(x_i)][(y_i)] != 0){

        mov_x = look_x/abs(look_x);
        mov_y = look_y/abs(look_y);
        vector<int> vetor = {1,mov_x, mov_y, look_x, look_y};

        return vetor;
      }   
    } 
  }
  cout << "\n";
  vector<int> vetor = {retorno};
  return vetor;
}

class Formigueiro{
public:
  int id;
  int x, y;
};

class Formiga{
public:  
  int id;
  int x, y; //posição dela no mapa
  int borda_h, borda_v; // limite de movimento no mapa
  int state = 0; // procurando comida, indo pro formigueiro...
  int passo[2] = {-1, 1};
  int home[2] = {0, 0};
  int caminhos[8][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {-1,1}, {1,-1}, {-1,-1} }; 

  void andar(int mapa_fero[100][100], int mapa_food[100][100], int look_distance, vector<Formigueiro> n_homes){
      
      vector<int> andar;
      if(state == 0){ //Formiga em idle procurando comida
        andar = look(x,y,mapa_fero, mapa_food, 8);
        if(andar[0] == 1){
          //cout << andar[1] << "\n";
          //cout << andar[2] << "\n";
          passo[0] = andar[1];
          passo[1] = andar[2];
          if(andar[3] == 0 && andar[4] == 0){state = 1;}
              }
          }

      if(state == 1){//Formiga em retorno ao Formigueiro
        for(int i = 0; i < n_homes.size(); i++){
          if(n_homes[i].id == id){
            home[0] = n_homes[i].x;
            home[1] = n_homes[i].y;
          }
          if((home[0] - x) == 0 ){passo[0] = 0;}//Calculo de X
          else{passo[0] = (home[0] - x)/abs(home[0] - x);}
          if((home[1] - y) == 0 ){passo[1] = 0;}//Calculo de Y
          else{passo[1] = (home[1] - y)/abs(home[1] - y);}

          if((home[0] - x) == 0 && (home[1] - y) == 0){
            state = 0; //Checa se chegou ao formigueiro
          }         
        }        
      }
      
      //srand (time(nullptr));
      while( x + passo[0] == 0 || x + passo[0] == borda_h-1 || y + passo[1] == 0 || y + passo[1] == borda_v-1 || (passo[0] == 0 && passo[1] == 0)){
      int k = rand() % 8;
      passo[0] = caminhos[k][0];
      passo[1] = caminhos[k][1];
      }
      
      x = x + passo[0];
      y = y + passo[1];
  }
  
};

class Mapa{
public:
  int x, y; // Implementa um limite para o mapa

  int mapa_f[100][100] {0}; // Formigas - Mapa limitado para 100x100

  int mapa_fero[100][100] {0}; // Feromônio - Mapa limitado para 100x100

  int mapa_food[100][100] {0}; // Comida - Mapa limitado para 100x100

  int mapa_home[100][100] {0}; // Formigueiro - Mapa limitado para 100x100
  
  vector <Formiga> n_ants; // Vetor das formigas presentes no mapa

  vector <Formigueiro> n_homes;

  void inserir_ant(Formiga ant){ // Método que insere formiga no vetor de formigas
    n_ants.push_back(ant);
  }

  void popular(){ // Método que apresenta à matriz de formigas onde está cada formigas
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
          mapa_f[i][j] = 0;
        }
      }
    
    for(int i = 0; i < n_ants.size(); i++){

      mapa_f[n_ants[i].x][n_ants[i].y] = mapa_f[n_ants[i].x][n_ants[i].y] + 1;
    }
  }

  void inserir_formigueiro(Formigueiro a_home){
      n_homes.push_back(a_home);
      mapa_home[a_home.x][a_home.y] = mapa_home[a_home.x][a_home.y] + 1;
  }

  void inserir_comida(){
    //srand ((unsigned)time(NULL));
    int x_k = rand() % x;
    while( abs(x_k - x)  ){ //PRECISA SABER COMO É IMPLEMENTADO
      x_k = rand() % x;  } //O FORMIGUEIRO
//PARA ESCOLHER O LUGAR DA COMIDA TEM QUE ESTAR MINIMAMENTE 
//LONGE DO FORMIGUEIRO
    int y_k = rand() % y;
    
  }

  void plot(){ // Gera a parte gráfica
    
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
        //COMEÇA A PLOTAR AS BORDAS------------------
        if(i == 0 && j == y - 1){ 
          cout << "#" << "\n";}
          
        else if(i == 0 || i == x - 1){
          cout << "#";}
          
        else if(j == 0 ){
          cout << "#";}
          
        else if(j == y - 1){
          cout << "#" << "\n";}
        //TERMINA DE PLOTAR AS BORDAS---------------

        else if(mapa_f[i][j] != 0){ //Formiga
                  cout<<"f";}

        else if(mapa_food[i][j] != 0){ //Comida
                  cout << "C";}

        else if(mapa_home[i][j] != 0){ //Formigueiro
                  cout << "T";}

        else if(mapa_fero[i][j] != 0){ //Feromônio
                  cout << ".";}
          
        else{
          cout << " ";       

          
        }

        }
    }
  }
};


int main() {
  srand (time(nullptr));
  cout << "programa começou" << "\n";
  int x = 25; //altura
  int y = 60; //largura
  Mapa map{x,y};
  Formigueiro home1{1, 3, 4};
  Formiga ant1{1,5,6, x, y};
  Formiga ant2{1,5,5, x, y};
  Formiga ant3{1,5,4, x, y};
  map.inserir_ant(ant1);
  map.inserir_ant(ant2);
  map.inserir_ant(ant3);
  map.inserir_formigueiro(home1);

  //cout << map.mapa_home[3][4] << "\n";
  
  map.popular();
  map.mapa_food[13][30] = 1;
  map.plot();
  
  //map.plot();
  cout << "\n";
  int a;
  for(int k = 0; k < 1000; k++){
    system("clear");
    for(int l = 0; l < map.n_ants.size(); l++){
      //chamar thread:::
      map.n_ants[l].andar(map.mapa_fero, map.mapa_food, 8, map.n_homes);
      }


    
    map.popular();
    map.plot();
    cout << "\n" << "Localizacao de x: " << map.n_ants[0].x << "\n";
    cout << "\n" << "Localizacao de y: " << map.n_ants[0].y << "\n";
    usleep(50000);
}
  
  cout << "\n" << "programa terminou" << "\n";
}