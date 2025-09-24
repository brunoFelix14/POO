/*Uma pequena biblioteca deseja informatizar seu acervo. Ela guarda
v´arios livros, cada um com informa¸c˜oes b´asicas como t´ıtulo, autor e
ano de publica¸c˜ao. O sistema deve permitir registrar os livros e list´a-
los. Identifique as classes e implemente.*/

#include <iostream>
#include <string> 

using namespace std;

class Livro
{
    private:
        string titulo;
        string autor;
        int ano_pub;

    public:
        Livro(string t, string a, int p) : autor(std::move(a)), titulo(std::move(t)), ano_pub(p) {}

        ~Livro()
        {
            cout << "Livro Excluido" << endl;
        }

        string getTitulo()
        {
            return titulo;
        }

        string getAutor()
        {
            return autor;
        }

        int getAno()
        {
            return ano_pub;
        }

        void dados()
        {
            cout << "Dados do Livro: " << getTitulo() << ", " << getAutor() << ", " << getAno();
        }

};

class Biblioteca
{
    private:
        Livro* livros[10];
        int quantia;
        
    public:
        Biblioteca()
        {
            quantia = 0;
        }

        void adicionarLivro(Livro* liv)
        {
            if(quantia < 10)
            {
                livros[quantia] = liv;
                quantia ++;
            }
            else
            {
                cout << "Biblioteca Cheia";
            }
        }

        void mostrarLivros()
        {
            cout << " |-----Biblioteca-----|" << endl;
            for(int i = 0; i < quantia; i++)
            {
                livros[i] -> dados();
                cout << endl;
            }
        }

};

int main()
{   
    Livro l1("Os Dois Morrem No Final", "Adam Silveira", 2021);
    Livro l2("O Primeiro a Morrer No Final", "Adam Silveira", 2022);

    Biblioteca lib;

    lib.adicionarLivro(&l1);
    lib.adicionarLivro(&l2);

    lib.mostrarLivros();

    return 0;
}