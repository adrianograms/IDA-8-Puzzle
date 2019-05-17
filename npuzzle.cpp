

#include <iostream> 
#include <bits/stdc++.h>
#include <string.h>
#include <stack> 
#include <vector>
#include <map>
#include <xmmintrin.h>

using namespace std; 

struct Node;

vector<Node*> limitesValidos_global;
vector<Node*> limitesInvalidos_global;

map<string,bool> matrizes_existentes;

struct Node {
    Node *pai;
    int valorfx;
    int gx;
    int hx;
    int n,m;
    char **matriz;
    Node(){}
    /*
    Função que calcula o hx para a matriz.
    Pega cada elemento da matriz que não for o 0 e calcula a diferença
    entre a posição atual dele e a posição objetivo
    */
    static int calculahx(char matriz[3][3]) {
        int hx = 0;
        for(int x =0; x< 3; x++) {
            for(int y = 0; y< 3; y++) {
                if(matriz[x][y] != 0) {
                    hx += abs(x - ((int)matriz[x][y]/3)) 
                    + abs(y - ((int)matriz[x][y]%3));
                }
            }
        }
        return hx;
    }
	void constroi_matriz(){
		matriz = new char*[n];
		for (int i = 0; i < n; ++i){
			matriz[i] = new char[m];
		}
		
	}

    /*
    Construtor para o primeiro Node
    */
    Node(char matriz[3][3], int gx, int hx) {
        this->gx = gx;
        this->hx = hx;
        this->valorfx = gx + hx;
        memcpy(this->matriz,matriz,sizeof(char)*9);
        pai = NULL;
    }

    /*
    Construtor para os outros Nodes
    */
    Node(Node *pai, char matriz[3][3], int gx, int hx) {
        this->gx = gx;
        this->hx = hx;
        this->valorfx = gx + hx;
        memcpy(this->matriz,matriz,sizeof(char)*9);
        this->pai = pai;
    }

    /*
    O processamento dos filhos, consiste em criar os filhos de um No
    e setar seus valores de hx e gx, alem do vetor ao qual eles fazem parte
    */
    void processamentofilhos(int x_src,int y_scr,int x_dest,int y_dest) {
		
		if(pai!= NULL && pai->matriz[x_src][y_scr] == 0)
			return;

        int valorAtual = abs(x_src - (int)(matriz[x_src][y_scr]/3)) 
        + abs(y_scr - (int)(matriz[x_src][y_scr]%3));

        int proximoValor = abs(x_dest - (int)(matriz[x_src][y_scr]/3)) 
        + abs(y_dest - (int)(matriz[x_src][y_scr]%3));

        char matriz_aux[3][3];
        memcpy(matriz_aux, this->matriz, sizeof(char)*9);
        matriz_aux[x_dest][y_dest] = matriz[x_src][y_scr];
        matriz_aux[x_src][y_scr] = 0;
        //cout << hashcode(matriz_aux) << endl;
        if(matrizes_existentes.count(hashcode(matriz_aux)))
			return;
        Node *n;
        if(valorAtual > proximoValor) {
            n = new Node(this,matriz_aux,gx+1,hx-1);
            //filhos.push(n);
        }
        else {
            n = new Node(this,matriz_aux,gx+1,hx+1);
            //filhos.push(n);
        }

        if(n->valorfx == this->valorfx)
            limitesValidos_global.push_back(n);
        else
            limitesInvalidos_global.push_back(n);
            
        matrizes_existentes[hashcode(n->matriz)] = true;
        




}

    /*
    Função que cria todos os filhos do Nó, validos ou invalidos
    */
    void createfilhos() {
        for(int x=0;x<3;x++)
        {
            for(int y=0;y<3;y++)
            {
                if(matriz[x][y] == 0) {

                    if(x+1 != 3) {
                        processamentofilhos(x+1,y,x,y);
                        /*
                        int aux = x+1;

                        int valorAtual = abs(aux - ((int)matriz[x+1][y]/3)) 
                        + abs(y - ((int)matriz[x+1][y]%3));

                        int proximoValor = abs(x - ((int)matriz[x+1][y]/3)) 
                        + abs(y - ((int)matriz[x+1][y]%3));

                        char matriz_aux[3][3];
                        memcpy(matriz_aux, this->matriz, sizeof(char)*9);
                        matriz_aux[x][y] = matriz[x+1][y];
                        matriz_aux[x+1][y] = 0;

                        if(valorAtual > proximoValor) {
                            Node n = Node(this,matriz_aux,gx+1,hx-1);
                            filhos.push(n);
                        }
                        else {
                            Node n = Node(this,matriz_aux,gx+1,hx+1);
                            filhos.push(n);
                        }
                        */
                        
                    }
                    if(x-1 != -1) {
                        processamentofilhos(x-1,y,x,y);
                    }
                    if(y+1 != 3) {
                        processamentofilhos(x,y+1,x,y);
                    }
                    if(y-1 != -1) {
                        processamentofilhos(x,y-1,x,y);
                    }
                    
                }
            }
        }
    }
    string static hashcode(char matriz[3][3]) {
		string hash;
		for(int i =0; i< 3;i++) {
			for(int j =0; j< 3; j++) {
				hash += matriz[i][j];
			}
		}
		
		return hash;
	} 
};

/*
Função de execução
*/
void run() {
    char matriz_primordial[3][3] = {{8,7,6},{5,4,3},{2,1,0}};
    limitesInvalidos_global.clear();
    limitesValidos_global.clear();
    Node *no = new Node(matriz_primordial,0,Node::calculahx(matriz_primordial));
    while(no->hx != 0) {
        no->createfilhos();
        if(limitesValidos_global.empty() == true) {
            limitesValidos_global = limitesInvalidos_global;
            limitesInvalidos_global.clear();
        }
        no = limitesValidos_global.back();
        limitesValidos_global.pop_back();
    }
    for(int i = 0; i< 3; i++) {
        for(int j = 0; j< 3; j++) {
            cout << (int)no->matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout <<matrizes_existentes.size() << endl;

}
  
int main() 
{ 
    char matriz[3][3];
    for(int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            matriz[x][y]='a';
        }
    }
    Node n = Node(matriz, 0,0);
    cout << n.matriz[2][1] << endl;
    vector<Node*> teste;
    Node a = Node();
    teste.push_back(&a);
    a.gx = 2;
    run();
} 
