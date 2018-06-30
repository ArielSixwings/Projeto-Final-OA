// Driver program to test above functions
#include "ArvoreB.hpp"
#include "In_OutPuts.hpp"

int main(int argc, char*argv[]){
    int ordem = atoi(argv[1]);
    if(ordem %2 == 0){
        ArvoreB teste((ordem / 2));
        int size = HowManyLines("lista1.txt");
        char** Chaves = BuildPrimaryKey("lista1", size);
        for(int i = 0; i < size; i++){
            teste.Insere_ArvoreB(Chaves[i]);
            cout<<Chaves[i]<<endl;
        }
    }else{
        ArvoreB teste((ordem / 2) + 1);
        int size = HowManyLines("lista1.txt");
        char** Chaves = BuildPrimaryKey("lista1", size);
        for(int i = 0; i < size; i++){
            teste.Insere_ArvoreB(Chaves[i]);
            cout<<Chaves[i]<<endl;
        }
    }
    

    // cout<<"Inicialmente\n\n\n"<<endl; //é o print do C++
    // teste.Percorre_ArvoreB();

    // teste.Remove("CAR62364");
    // cout<<"\n\n";
    // teste.Percorre_ArvoreB();
    return 0;
}