#include <iostream>

using namespace std;

class Mapa{
public:
  string mapa[30][30];
  void popular(){
    for(int i = 0; i < 30; i++){
      for(int j = 0; j < 30; j++){
        if(i == 0 && j == 30 - 1){ mapa[i][j] = "#";}//cout << "#" << "\n";}
          
        else if(i == 0 || i == 30 - 1){mapa[i][j] = "#";}//cout << "#";}
          
        else if(j == 0 ){mapa[i][j] = "#";}//cout << "#";}
          
        else if(j == 30 - 1){mapa[i][j] = "#";}//cout << "#" << "\n";}
          
        else{
          mapa[i][j] = " ";//cout << ".";
        }
        //if(i == 30 - 1){cout << "#" << "\n";} 
        }
      }   
    }
  void gerar(){
    for(int i = 0; i < 30; i++){
      for(int j = 0; j < 30; j++){
        cout << mapa[i][j];
      }
      cout << "\n";
    }
  }

};

/*class Mapa{
public:
  string mapa[30][30];
  void popular(){
    for(int i = 0; i < 30; i++){
      for(int j = 0; j < 30; j++){
        if(i == 0 && j == 30 - 1){ mapa[i][j] = "#";}//cout << "#" << "\n";}
          
        else if(i == 0 || i == 30 - 1){mapa[i][j] = "#";}//cout << "#";}
          
        else if(j == 0 ){mapa[i][j] = "#";}//cout << "#";}
          
        else if(j == 30 - 1){mapa[i][j] = "#";}//cout << "#" << "\n";}
          
        else{
          mapa[i][j] = " ";//cout << ".";
        }
        //if(i == 30 - 1){cout << "#" << "\n";} 
        }
      }   
    }
  void gerar(){
    for(int i = 0; i < 30; i++){
      for(int j = 0; j < 30; j++){
        cout << mapa[i][j];
      }
      cout << "\n";
    }
  }

};*/