#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include<vector>
#include<string>
using namespace std;

typedef enum{E=200, W1 , W2, W3, W4, W5, W6, P, C, T, E1, O1, A1, N1, L1, R1, Q1}generadores;
//typedef enum { a=97, e=101, n=110, o=111, q=113, r=114, x=120} terminales;
typedef std::set<int> conj;
typedef std::map<int,conj> fila;
typedef std::map<int, fila> tabla;


typedef struct {
int generador;
int primero;
int segundo;
} regla;

typedef std::vector<regla> gramatica;

regla CrearG( int a , int b, int c){
      
      regla r;
      r.generador=a;
      r.primero=b;
      r.segundo=c;
      
      return r;
   }


gramatica L;
tabla N;
//conj c;



void push_backk(){ 
     
  L.push_back(CrearG(E,W2,W3)); 
  L.push_back(CrearG(W1,P,Q1));
  L.push_back(CrearG(W2,W1,E));  
  L.push_back(CrearG(W3,E1,E));
  L.push_back(CrearG(W4,P,O1));
  L.push_back(CrearG(E,W4,C));
  L.push_back(CrearG(W5,C,A1));
  L.push_back(CrearG(E,W5,T));   
  L.push_back(CrearG(E,N1,P));
  L.push_back(CrearG(W6,L1,E));
  L.push_back(CrearG(E,W6,R1));
  L.push_back(CrearG(E,'x',0));
  L.push_back(CrearG(P,W4,C));
  L.push_back(CrearG(P,W5,T));   
  L.push_back(CrearG(P,N1,P));
  L.push_back(CrearG(P,W6,R1));
  L.push_back(CrearG(P,'x',0));
  L.push_back(CrearG(C,W5,T));
  L.push_back(CrearG(C,N1,P));
  L.push_back(CrearG(C,W6,R1));
  L.push_back(CrearG(C,'x',0));
  L.push_back(CrearG(T,N1,P));
  L.push_back(CrearG(T,'x',0));
  L.push_back(CrearG(T,W6,R1));
  L.push_back(CrearG(E1,'e',0));
  L.push_back(CrearG(O1,'o',0));
  L.push_back(CrearG(A1,'a',0));
  L.push_back(CrearG(N1,'n',0));
  L.push_back(CrearG(L1,'l',0));
  L.push_back(CrearG(R1,'r',0));
  L.push_back(CrearG(Q1,'q',0)); 
                         
     }


bool isMember(conj &s, int a){
     
    return s.find(a) != s.end();
   
    }

void buildSet(conj &s, int b, int c){
  
  for(int i=0;i<L.size();i++){                     
     if((L[i].primero==b) && (L[i].segundo==c)){                               
          s.insert(L[i].generador);
    }
  }
}
     
     
void addSymbols(conj &dest, conj &src1, conj &src2){
       
  conj::iterator ir;
  conj::iterator ir2; 
     for(ir=src1.begin(); ir != src1.end(); ir++){                 
        for(ir2=src2.begin(); ir2 != src2.end(); ir2++){
                                            
                 buildSet(dest,*ir,*ir2); 
         }
    }                       
}

          
void buildSet(conj &s, int t){
     for(int i=0; i<L.size(); i++){
          if((L[i].primero == t) || (L[i].segundo == t)){
                 s.insert(L[i].generador);
          }       
     }
}


bool analize(gramatica &g, string &w){
   int n= w.length();
   
   for(int i=1; i<=n; i++)
      buildSet(N[i][1], w[i-1]);
   for(int j=2; j<=n; j++){
      for(int i=1; i<=n-j+1; i++){
          for(int k=1; k<=j-1; k++){
                addSymbols(N[i][j],N[i][k], N[i+k][j-k]); 
               
           }
       }
   }  
   if(isMember(N[1][n],E)){
      cout<<" la cadena esta en el lenguaje L(Quest)"<<endl;
      cout<<endl;
      }
   else {
     cout<<"la cadena no esta en el lenguaje L(Quest)"<<endl;
     cout<<endl;
     }
    
}


int main(){
    
    string cadena; 
    push_backk(); 
   // mostrargramatica();
    
    cout<<"ingrese una cadena: ";
    cin>>cadena;
    cout<<endl;
    
    analize(L,cadena);
    
     

    system("PAUSE");
    return 0;
}
