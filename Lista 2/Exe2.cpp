#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Midia
{
    protected:
        string titulo;
        int ano;
        int duracao;

    public:
        Midia(string titulo, int ano, int duracao) : titulo(titulo), ano(ano), duracao(duracao) {}

        virtual ~Midia() {}

        virtual void reproduzir() = 0;
        virtual string infoDetalhada() = 0;
        virtual bool combina(string filtro) = 0;
};

class Musica : public Midia
{
    private:
        string artista;
        int bitrate;

    public:
        Musica(string titulo, int ano, int duracao, string artista, int bitrate) : Midia(titulo, ano, duracao), artista(artista), bitrate(bitrate) {}

        void reproduzir() override
        {
            cout << "Tocando Musica: " << titulo << " - " << artista << " (" << duracao << "s)" << endl;
        }

        string infoDetalhada() override
        {
            return "[Musica] " + titulo + " | Artista: " + artista + " | Ano: " + to_string(ano) + " | " + to_string(bitrate) + "kbps";
        }

        bool combina(string filtro) override
        {
            return (titulo.find(filtro) != string::npos) || (artista.find(filtro) != string::npos);
        }
};

class Video : public Midia
{
    private:
        string resolucao;
        string codec;

    public:
        Video(string titulo, int ano, int duracao, string resolucao, string codec) : Midia(titulo, ano, duracao), resolucao(resolucao), codec(codec) {}

        void reproduzir() override
        {
            cout << "Reproduzindo Video: " << titulo << " [" << resolucao << "] codec: " << codec << endl;
        }

        string infoDetalhada() override
        {
            return "[Video] " + titulo + " | Res: " + resolucao + " | Codec: " + codec + " | Ano: " + to_string(ano);
        }

        bool combina(string filtro) override
        {
            return (titulo.find(filtro) != string::npos) || (resolucao.find(filtro) != string::npos);
        }
};

class Podcast : public Midia
{
    private:
        string host;
        string convidados;

    public:
        Podcast(string titulo, int ano, int duracao, string host, string convidados) : Midia(titulo, ano, duracao), host(host), convidados(convidados) {}

        void reproduzir() override
        {
            cout << "Transmitindo Podcast: " << titulo << " com " << host << " e convidados: " << convidados << endl;
        }

        string infoDetalhada() override
        {
            return "[Podcast] " + titulo + " | Host: " + host + " | Feat: " + convidados + " | D: " + to_string(duracao) + "s";
        }

        bool combina(string filtro) override
        {
            return (titulo.find(filtro) != string::npos) || (host.find(filtro) != string::npos) || (convidados.find(filtro) != string::npos);
        }
};

int main()
{
    vector<unique_ptr<Midia>> catalogo;

    catalogo.push_back(unique_ptr<Musica>(new Musica("Bohemian Rhapsody", 1975, 354, "Queen", 320)));
    catalogo.push_back(unique_ptr<Video>(new Video("Interestelar", 2014, 10140, "4K", "H.264")));
    catalogo.push_back(unique_ptr<Podcast>(new Podcast("NerdCast RPG", 2023, 7200, "Jovem Nerd", "Azaghal, Tucano")));
    catalogo.push_back(unique_ptr<Musica>(new Musica("Hotel California", 1976, 390, "Eagles", 320)));

    cout << "--- LISTAGEM COMPLETA ---" << endl;
    for(const auto& item : catalogo)
    {
        cout << item->infoDetalhada() << endl;
    }

    cout << endl << "--- REPRODUZINDO TUDO ---" << endl;
    for(const auto& item : catalogo)
    {
        item->reproduzir();
    }

    string termoBusca = "Queen";
    cout << endl << "--- FILTRANDO POR: " << termoBusca << " ---" << endl;
    for(const auto& item : catalogo)
    {
        if(item->combina(termoBusca))
        {
            cout << "Encontrado: " << item->infoDetalhada() << endl;
        }
    }

    return 0;
}