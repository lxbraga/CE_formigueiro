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

class Feromonio {        
public:          
        int x, y;  // Posicao x e y
        int dir_x,dir_y;
        int intensidade = 50;      
    
        void decrementaIntensidade(){
          intensidade -= 1;
        }
};


vector<int> look(int x, int y,
                 int mapa_fero[100][100],
                 vector<Feromonio> n_feros,
                 int mapa_food[100][100],
                 int look_distance){
  
  // define as variáveis
  int x_min = x - look_distance;
  int x_max = x + look_distance;
  int y_min = y - look_distance;
  int y_max = y + look_distance;
  
  int look_x, look_y;
  int mov_x, mov_y;  
  int retorno = 0;
 // int maior_fero;

  //if(x = )
  
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

      for(int i = 0; i < n_feros.size(); i++){
          if(n_feros[i].x == x && n_feros[i].y == y){
            retorno = 1;
            vector<int> vetor = {retorno, n_feros[i].dir_x, n_feros[i].dir_y,look_x, look_y};
            return vetor;
            }
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
  //int k; // aleatorizador de vetor
  int borda_h, borda_v; // limite de movimento no mapa
  int state = 0; // procurando comida, indo pro formigueiro...
  //int rand_step = 0;
  int passo[2] = {-1, 1};
  int home[2] = {0, 0};
  int caminhos[8][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {-1,1}, {1,-1}, {-1,-1} }; 

  void andar(int mapa_fero[100][100],
            int mapa_food[100][100],
            int look_distance, 
            vector<Formigueiro> n_homes,
            vector<Feromonio> n_feros){
      
      vector<int> andar;
      if(state == 0){ //Formiga em idle procurando comida
        andar = look(x,y,mapa_fero, n_feros, mapa_food, look_distance);
        if(andar[0] == 1){
          //cout << andar[1] << "\n";
          //cout << andar[2] << "\n";
          passo[0] = andar[1];
          passo[1] = andar[2];
          if(andar[3] == 0 && andar[4] == 0){
            mapa_food[x][y] = mapa_food[x][y] - 1;
            state = 1;} // MUTEX VAI NA LINHA DE CIMA ^^^
              }
          }

      if(state == 1){//Formiga em retorno ao Formigueiro
        for(int i = 0; i < n_homes.size(); i++){
          if((home[0] - x) == 0 && (home[1] - y) == 0){
            state = 0; //Checa se chegou ao formigueiro
            break;
          } 
          if(n_homes[i].id == id){
            home[0] = n_homes[i].x;
            home[1] = n_homes[i].y;
          }
          if((home[0] - x) == 0 ){passo[0] = 0;}//Calculo de X
          else{passo[0] = (home[0] - x)/abs(home[0] - x);}
          if((home[1] - y) == 0 ){passo[1] = 0;}//Calculo de Y
          else{passo[1] = (home[1] - y)/abs(home[1] - y);}

          Feromonio fero{x,y, -1 * passo[0], -1 * passo[1]};
          //n_feros.push_back(fero);//adiciona no lugar
          
        }        
      }
      
      //srand (time(nullptr));
      while( x + passo[0] == 0 || x + passo[0] == borda_h-1 || //x se movendo para uma das bordas
        y + passo[1] == 0 || y + passo[1] == borda_v-1 || // //y se movendo para uma das bordas
        (passo[0] == 0 && passo[1] == 0)){ //formiga sem vetor de movimento
        
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
    
      vector <Formigueiro> n_homes; // Vetor das Formigueiros presentes no mapa
    
      vector <Feromonio> n_feros; // Vetor das formigas presentes no mapa
    
      void inserir_ant(Formiga ant){ // Método que insere formiga no vetor de formigas
        n_ants.push_back(ant);
      }
    
      void popular(){ // Método que apresenta à matriz de formigas onde está cada formiga
        for(int i = 0; i < x; i++){
          for(int j = 0; j < y; j++){
              mapa_f[i][j] = 0; // Zera as matrizes
              mapa_fero[i][j] = 0;
            }
          }
        
        for(int i = 0; i < n_ants.size(); i++){
          //Adiciona a formiga à matriz
          mapa_f[n_ants[i].x][n_ants[i].y] = mapa_f[n_ants[i].x][n_ants[i].y] + 1;
          if(n_ants[i].state == 1){
            Feromonio fero{n_ants[i].x, n_ants[i].y, -1 * n_ants[i].passo[0], -1 * n_ants[i].passo[1]};
            n_feros.push_back(fero);
            //TALVEZ ADICIONAR DIREÇÃO NO FEROMONIO???
            }
        }
        for(int i = 0; i< n_feros.size(); i++){
          if(n_feros[i].intensidade == 0){
            n_feros.erase(n_feros.begin() + i);
          }
          else{ mapa_fero[n_feros[i].x][n_feros[i].y] = mapa_fero[n_feros[i].x][n_feros[i].y] + n_feros[i].intensidade;}
        }
        
      }
    
      void inserir_formigueiro(Formigueiro a_home){ // Método que apresenta à matriz de formigueiros onde está cada formigueiro
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
  int look_distance = 8;
  Mapa map{x,y};
  Formigueiro home1{1, 3, 4};
  //Formigueiro home2{2, 20, 55};
  Formiga ant1{1,5,6, x, y};
  Formiga ant2{1,5,5, x, y};
  Formiga ant3{1,5,4, x, y};
  // Formiga ant4{2,22,55, x, y};
  // Formiga ant5{2,22,54, x, y};
  // Formiga ant6{2,22,53, x, y};
  map.inserir_ant(ant1);
  map.inserir_ant(ant2);
  map.inserir_ant(ant3);
  map.inserir_formigueiro(home1);
  // map.inserir_ant(ant4);
  // map.inserir_ant(ant5);
  // map.inserir_ant(ant6);
  // map.inserir_formigueiro(home2);

  //cout << map.mapa_home[3][4] << "\n";
  
  map.popular();
  map.mapa_food[13][30] = 10;
  map.plot();
  
  //map.plot();
  cout << "\n";
  int a;
  for(int k = 0; k < 2000; k++){
    system("clear");
    map.popular();
    for(int l = 0; l < map.n_ants.size(); l++){
      //chamar thread:::
      cout << "Quantidade de comida: "<< map.mapa_food[13][30] << "\n";
      map.n_ants[l].andar(map.mapa_fero, map.mapa_food, look_distance, map.n_homes, map.n_feros);
      }// THREAD VAI AQUI

    for(int n = 0; n < map.n_feros.size(); n++)
      map.n_feros[n].decrementaIntensidade();
      //A cada tick ele diminui um da intensidade de cada feromônio
    
    map.plot();
    cout << "\n" << "Localizacao de x: " << map.n_ants[0].x << "\n";
    cout << "\n" << "Localizacao de y: " << map.n_ants[0].y << "\n";
    usleep(50000);
}
  
  cout << "\n" << "programa terminou" << "\n";
}
