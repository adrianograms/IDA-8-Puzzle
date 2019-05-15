

#include <iostream> 
#include <string.h>
#include <stack> 
#include <vector>

using namespace std; 

struct Node {
    Node *pai;
    stack<Node> filhos;
    int valorfx;
    int gx;
    int hx;
    char matriz[3][3];
    static std::vector<Node> limitesValidos;
    static std::vector<Node> limitesInvalidos;
    Node(){}

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

    Node(char matriz[3][3], int gx, int hx) {
        this->gx = gx;
        this->hx = hx;
        this->valorfx = gx + hx;
        memcpy(this->matriz,matriz,sizeof(char)*9);
        pai = NULL;
    }

    Node(Node *pai, char matriz[3][3], int gx, int hx) {
        this->gx = gx;
        this->hx = hx;
        this->valorfx = gx + hx;
        memcpy(this->matriz,matriz,sizeof(char)*9);
        this->pai = pai;
    }

    void processamentofilhos(char matriz[3][3],int x_src,int y_scr,int x_dest,int y_dest) {

        int valorAtual = abs(x_src - ((int)matriz[x_src][y_scr]/3)) 
        + abs(y_scr - ((int)matriz[x_src][y_scr]%3));

        int proximoValor = abs(x_dest - ((int)matriz[x_src][y_scr]/3)) 
        + abs(y_dest - ((int)matriz[x_src][y_scr]%3));

        char matriz_aux[3][3];
        memcpy(matriz_aux, this->matriz, sizeof(char)*9);
        matriz_aux[x_dest][y_dest] = matriz[x_src][y_scr];
        matriz_aux[x_src][y_scr] = 0;

        if(valorAtual > proximoValor) {
            Node n = Node(this,matriz_aux,gx+1,hx-1);
            filhos.push(n);
            limitesValidos.push_back(n);
        }
        else {
            Node n = Node(this,matriz_aux,gx+1,hx+1);
            filhos.push(n);
            limitesInvalidos.push_back(n);
        }

}

    void createfilhos() {
        for(int x=0;x<3;x++)
        {
            for(int y=0;y<3;y++)
            {
                if(matriz[x][y] == 0) {

                    if(x+1 != 3) {
                        processamentofilhos(this->matriz,x+1,y,x,y);
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
                        processamentofilhos(this->matriz,x-1,y,x,y);
                    }
                    if(y+1 != 3) {
                        processamentofilhos(this->matriz,x,y+1,x,y);
                    }
                    if(y-1 != -1) {
                        processamentofilhos(this->matriz,x,y-1,x,y);
                    }
                    
                }
            }
        }
    }
};

void run() {
    char matriz_primordial[3][3] = {{8,7,6},{5,0,4},{3,2,1}};
    Node no = Node(matriz_primordial,0,Node::calculahx(matriz_primordial));
    while(no.valorfx != no.gx) {
        no.createfilhos();
        if(no.limitesValidos.empty() == true) {
            Node::limitesValidos = Node::limitesInvalidos;
            no.limitesInvalidos.clear();
        }
    }

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
    vector<int> teste;
    teste.push_back(1);
} 
