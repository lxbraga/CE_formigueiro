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
#include <mutex>

using namespace std;
mutex mtx; 
class Feromonio;
class Formigueiro;
class Formiga;
class Mapa;

class Feromonio {        
public:          
    int x, y;  // Posicao x e y
    int dir_x,dir_y;
    int intensidade;      
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

 /* if(mapa_food[x][y] != 0){
    vector<int> vetor = {retorno};
    return vetor;
  }*/
  
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

 	void assimilar(vector<int> fromAndar){
   		x = fromAndar[0];
   		y = fromAndar[1];
   		state = fromAndar[2];
   		passo[0] = fromAndar[3];
   		passo[1] = fromAndar[4];}

  	void andar( int mapa_fero[100][100],
            int mapa_food[100][100],
            int look_distance, 
            vector<Formigueiro> n_homes,
            vector<Feromonio> n_feros){
      
    vector<int> andar;// { X , Y , STATE ,  PASSO[0], PASSO[1]  };
    vector<int> toFormiga(5);
    	if(state == 0){ //Formiga em idle procurando comida
        	andar = look(x,y,mapa_fero, n_feros, mapa_food, look_distance);
        	if(andar[0] == 1){
          		//cout << andar[1] << "\n";
          		//cout << andar[2] << "\n";
          		//toFormiga[3] = andar[1];
          		//toFormiga[4] = andar[2];
          		passo[0] = andar[1];
          		passo[1] = andar[2];
          		//if(andar[3] == 0 && andar[4] == 0){
            if(mapa_food[x][y] != 0){
            	mtx.lock();
			  	mapa_food[x][y] = mapa_food[x][y] - 1;
              	state = 1;
				mtx.unlock();
			} // MUTEX VAI NA LINHA DE CIMA ^^^
        }
    }

    if(state == 1){//Formiga em retorno ao Formigueiro
        for(int i = 0; i < n_homes.size(); i++){
          /*if((formiga.home[0] - formiga.x) == 0 && (formiga.home[1] - formiga.y) == 0){
            formiga.state = 0; //Checa se chegou ao formigueiro
            break;
          } */
	        if(n_homes[i].id == id){
	            home[0] = n_homes[i].x;
	            home[1] = n_homes[i].y;    
	            if((home[0] - x) == 0 ){passo[0] = 0;}//Calculo de X
	            else{passo[0] = (home[0] - x)/abs(home[0] - x);}
	            if((home[1] - y) == 0 ){passo[1] = 0;}//Calculo de Y
	            else{passo[1] = (home[1] - y)/abs(home[1] - y);}
	            if(passo[0] == 0 && passo[1] == 0) {state = 0;}
          	}
        }        
    }
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
    int intensidade_fero;
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


    void popular(){ // Método que apresenta à matriz de formigas onde está cada formigas
        for(int i = 0; i < x; i++){
          	for(int j = 0; j < y; j++){
              	mapa_f[i][j] = 0;// Zera as matrizes
              	mapa_fero[i][j] = 0;
            }
        }
        for(int i = 0; i < n_ants.size(); i++){
          //Adiciona a formiga à matriz
          	mapa_f[n_ants[i].x][n_ants[i].y] = mapa_f[n_ants[i].x][n_ants[i].y] + 1;
        }
        for(int i = 0; i < n_feros.size(); i++){
          	mapa_fero[n_feros[i].x][n_feros[i].y] = mapa_fero[n_feros[i].x][n_feros[i].y] + n_feros[i].intensidade;
        }
      }

    void adicionar_feromonio(){
      	for(int i = 0; i < n_ants.size(); i++){
        	if(n_ants[i].state == 1 && mapa_fero[n_ants[i].x][n_ants[i].y] == 0){
          		Feromonio fero{n_ants[i].x, n_ants[i].y, -1 * n_ants[i].passo[0], -1 * n_ants[i].passo[1], intensidade_fero};
              	n_feros.push_back(fero);
        	}
        	else if(n_ants[i].state == 1 && mapa_fero[n_ants[i].x][n_ants[i].y] != 0){
          		for(int k = 0; k <n_feros.size(); k++){
            		if(n_feros[k].x == n_ants[i].x && n_feros[k].y == n_ants[i].y && n_feros[k].intensidade < 50){
              			n_feros[k].intensidade = n_feros[k].intensidade + 20;
          			} 
        		}
      		}
    	}
  	}

    void remover_feromonio(){
      	for(int i = 0; i < n_feros.size(); i++){
        	if(n_feros[i].intensidade == 0 || n_feros[i].intensidade < 0){
          		n_feros.erase(n_feros.begin() + i);
        	}
      	}
    }
    
    void inserir_formigueiro(Formigueiro a_home){ // Método que apresenta à matriz de formigueiros onde está cada formigueiro
        n_homes.push_back(a_home);
        mapa_home[a_home.x][a_home.y] = mapa_home[a_home.x][a_home.y] + 1;
    }

    void inserir_comida(int ref_x, int ref_y){
      mapa_food[ref_x][ref_y] = mapa_food[ref_x][ref_y] + intensidade_fero;  
    }

    void plot(){ // Gera a parte gráfica
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
            //COMEÇA A PLOTAR AS BORDAS------------------
	            if(i == 0 && j == y - 1){ 
	              cout << "#" << "\n";
					}
	            else if(i == 0 || i == x - 1){
	              cout << "#";
					}
	            else if(j == 0 ){
	              cout << "#";
					}
	            else if(j == y - 1){
	              cout << "#" << "\n";
					}
	            //TERMINA DE PLOTAR AS BORDAS---------------
	            else if(mapa_f[i][j] != 0){ //Formiga
	                      cout<<"f";
					}
	            else if(mapa_food[i][j] != 0){ //Comida
	                      cout << "C";
					}
	            else if(mapa_home[i][j] != 0){ //Formigueiro
	                      cout << "T";
					}
	            else if(mapa_fero[i][j] != 0){ //Feromônio
	                      cout << ".";
					}
	            else{
	              cout << " ";         
	            }	    
            }
        }
    }
};

void formiga_andar(Mapa& mapa, int iterador, int look_distance){
  mapa.n_ants[iterador].andar(mapa.mapa_fero,mapa.mapa_food,look_distance,mapa.n_homes,mapa.n_feros);
}



int main() {
	srand (time(nullptr));
	cout << "programa começou" << "\n";
	int x = 25; //altura
	int y = 60; //largura
	int look_distance = 8;
	int intensidade_feromonio = 20;
	Mapa mapa{x, y, intensidade_feromonio};
	mapa.inserir_comida(13,30);
	Formigueiro home1{1, 3, 4};
	//Formigueiro home2{2, 20, 55};
	Formiga ant1{1,5,6, x, y};
	Formiga ant2{1,5,5, x, y};
	Formiga ant3{1,5,4, x, y};
	// Formiga ant4{2,22,55, x, y};
	// Formiga ant5{2,22,54, x, y};
	// Formiga ant6{2,22,53, x, y};
	mapa.inserir_ant(ant1);
	mapa.inserir_ant(ant2);
	mapa.inserir_ant(ant3);
	mapa.inserir_formigueiro(home1);
	// mapa.inserir_ant(ant4);
	// mapa.inserir_ant(ant5);
	// mapa.inserir_ant(ant6);
	// mapa.inserir_formigueiro(home2);
	//cout << mapa.mapa_home[3][4] << "\n";  
	mapa.popular();
	//mapa.mapa_food[13][30] = 10;
	mapa.plot();  
	//mapa.plot();
	cout << "\n";
	int a;
	vector<int> movimento(5);
	for(int k = 0; k < 2000; k++){
	    system("clear");
    mapa.adicionar_feromonio();
    mapa.remover_feromonio();
    mapa.popular();
    //mapa.popular_feromonio();
	vector<thread> arr;
    for(int l = 0; l < mapa.n_ants.size(); l++){
      	//chamar thread:::
      	mapa::n_ants;
      	//arr.emplace_back(mapa.n_ants[l].andar(mapa.mapa_fero, mapa.mapa_food, look_distance, mapa.n_homes, mapa.n_feros));
	  	arr.push_back(&mapa::n_ants[l].andar, mapa.mapa_fero, mapa.mapa_food, look_distance, mapa.n_homes, mapa.n_feros);
		// mapa.n_ants[l].andar(mapa.mapa_fero, mapa.mapa_food, look_distance, mapa.n_homes, mapa.n_feros);
		//arr.emplace_back(&mapa::n_ants);
      	//movimento = andar(mapa.n_ants[l],mapa.mapa_fero, mapa.mapa_food, look_distance, mapa.n_homes, mapa.n_feros);
      	//arr.emplace_back(formiga_andar,mapa,l,look_distance);
      	//mapa.n_ants[l].assimilar(movimento);
      	cout << "Tamanho do vetor feromônio: " << mapa.n_feros.size() << "\n";
		for(auto &thread : arr){
			thread.join();
		}
    }// THREAD VAI AQUI

    for(int n = 0; n < mapa.n_feros.size(); n++)
      	mapa.n_feros[n].decrementaIntensidade();
      	//A cada tick ele diminui um da intensidade de cada feromônio
    	cout << "\n" << "Quantidade de comida: "<< mapa.mapa_food[13][30] << "\n";
    	mapa.plot();
    	cout << "\n" << "Localizacao de x: " << mapa.n_ants[0].x << "\n";
    	cout << "\n" << "Localizacao de y: " << mapa.n_ants[0].y << "\n";
    	usleep(50000);
	}
  
  	cout << "\n" << "programa terminou" << "\n";
}
