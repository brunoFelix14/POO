/*Em um jogo, cada jogador possui um invent´ario que guarda itens e
armas. Al´em disso, h´a inimigos que podem estar equipados com armas.
Estruture as classes necess´arias e implemente.*/

#include <iostream>
#include <string>

using namespace std;

class Item
{
    private:
        string nome;

    public:
        Item(string n) : nome(n) {}

        string getNome() 
        { 
            return nome; 
        }
};

class Arma
{
    private:
        string nome;
        int dano;

    public:
        Arma(string n, int d) : nome(n), dano(d) {}
        
        string getNome() 
        { 
            return nome; 
        }
        
        int getDano() 
        { 
            return dano; 
        }
};

class Inventario
{
    private:
        Item *item;
        Arma *arma;

    public:
        Inventario(Item *i, Arma *a) : item(i), arma(a) {}

        void mostrar()
        {
            if(item)
            {
                cout << "Item guardado: " << item->getNome() << "\n";
            }
            if(arma)
            {
                cout << "Arma guardada: " << arma->getNome() << " (Dano " << arma->getDano() << ")\n";
            }
        }
};

class Jogador
{
    private:
        string nome;
        Inventario inventario;

    public:
        Jogador(string n, Item *i, Arma *a) : nome(n), inventario(i, a) {}

        void mostrarStatus()
        {
            cout << "Jogador: " << nome << "\n";
            inventario.mostrar();
        }
};

class Inimigo
{
    private:
        string tipo;
        Arma *arma;

    public:
        Inimigo(string t, Arma *a) : tipo(t), arma(a) {}

        void mostrarStatus()
        {
            cout << "Inimigo: " << tipo << "\n";
            if(arma)
            {
                cout << "Arma equipada: " << arma->getNome() << " (Dano " << arma->getDano() << ")\n";
            }
            else
            {
                cout << "Sem arma equipada.\n";
            }
        }
};

int main()
{
    Item pocao("Pocao de Vida");
    Arma espada("Espada Longa", 50);
    Arma garra("Garra Afiada", 20);

    Jogador j1("Arthur", &pocao, &espada);
    Inimigo i1("Lobo", &garra);

    j1.mostrarStatus();
    cout << "-----------------\n";
    i1.mostrarStatus();

    return 0;
}
