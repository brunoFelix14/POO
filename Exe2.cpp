/*Um usu´ario de m´usica online pode criar playlists, onde cada playlist
cont´em v´arias m´usicas. Um mesmo usu´ario pode ter diversas playlists
associadas ao seu perfil. Modele as classes necess´arias e implemente.*/

#include <iostream>
#include <string>

using namespace std;

class Musica
{   
    private:
        string nome;

    public:
        Musica(string n) : nome(move(n)) {}

        ~Musica()
        {
            cout << "Musica apagada da playlist" << endl;
        }

        string getNome()
        {
            return nome;
        }
};

class Playlist
{
    private:
        string nome;
        Musica* musicas[10];
        int quantia;

    public:
        Playlist(string n) : nome(move(n)), quantia(0) {}

        ~Playlist()
        {
            cout << "Playlist deletada" << endl;
        }

        void adicionarMusica(Musica &m)
        {
            if(quantia < 10)
            {
                musicas[quantia] = &m;
                quantia ++; 
            }
        }

        void mostrarMusicas()
        {
            cout << "Playlist: " << nome << endl;

            for(int i = 0; i < quantia; i++)
            {
                cout << i + 1 << ". " << musicas[i] -> getNome() << endl;
            }
        }
};

class Usuario_Musica
{
    private:
        string nome;
        Playlist* playlist[5];
        int quantiaPlaylist;

    public:
        Usuario_Musica(string n) : nome(move(n)), quantiaPlaylist(0) {}

        void novaPlaylist(Playlist &p)
        {
            if(quantiaPlaylist < 5)
            {
                playlist[quantiaPlaylist] = &p;
                quantiaPlaylist ++;
            }
        }
        
        void verPlaylist()
        {
            cout << "Usuário: " << nome << endl;
            
            for(int i = 0; i < quantiaPlaylist; i++)
            {
                playlist[i] -> mostrarMusicas();
            }
        }
};

int main()
{
    Musica m1("November Rain");
    Musica m2("Numb");
    Musica m3("Faint");

    Playlist p1("Rock");

    p1.adicionarMusica(m1);
    p1.adicionarMusica(m2);
    p1.adicionarMusica(m3);

    Usuario_Musica user("Bruno Felix");

    user.novaPlaylist(p1);

    user.verPlaylist();

    return 0;
}