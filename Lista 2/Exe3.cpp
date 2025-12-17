#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

class VeiculoAutonomo
{
    protected:
        int id;
        double bateria;
        string posicao;

    public:
        VeiculoAutonomo(int id, double bateria, string posicao) : id(id), bateria(bateria), posicao(posicao) {}

        virtual ~VeiculoAutonomo() {}

        virtual double consumoPorKm() = 0;
        virtual void estrategiaRecarga() = 0;

        virtual void planejarRota(string destino)
        {
            cout << "[Veiculo " << id << "] Calculando rota padrao para: " << destino << endl;
        }

        virtual void mover()
        {
            if(bateria > 10)
            {
                cout << "[Veiculo " << id << "] Movendo-se para destino... (Bateria: " << bateria << "%)" << endl;
                bateria -= 5;
            }
            else
            {
                cout << "[Veiculo " << id << "] Bateria critica! Solicitando recarga." << endl;
            }
        }

        virtual void relatorioStatus()
        {
            cout << "ID: " << id << " | Pos: " << posicao << " | Bat: " << bateria << "% | Consumo: " << consumoPorKm() << " kW/km" << endl;
        }

        virtual void detectarObstaculos()
        {
            cout << "[Veiculo " << id << "] Sensores padrao ativos." << endl;
        }
};

class CarroAutonomo : public VeiculoAutonomo
{
    private:
        int numPassageiros;
        bool modoSport;

    public:
        CarroAutonomo(int id, double bateria, string posicao, int numPassageiros) : VeiculoAutonomo(id, bateria, posicao), numPassageiros(numPassageiros), modoSport(false) {}

        double consumoPorKm() override
        {
            return 0.15;
        }

        void estrategiaRecarga() override
        {
            cout << "[Carro] Buscando estacao de recarga rapida (Supercharger)." << endl;
        }

        void detectarObstaculos() override
        {
            cout << "[Carro] Lidars e cameras 360 detectando pedestres e outros carros." << endl;
        }
};

class CaminhaoAutonomo : public VeiculoAutonomo
{
    private:
        double capacidadeCarga;
        int eixos;

    public:
        CaminhaoAutonomo(int id, double bateria, string posicao, double capacidadeCarga, int eixos) : VeiculoAutonomo(id, bateria, posicao), capacidadeCarga(capacidadeCarga), eixos(eixos) {}

        double consumoPorKm() override
        {
            return 1.2 + (capacidadeCarga * 0.05);
        }

        void estrategiaRecarga() override
        {
            cout << "[Caminhao] Buscando doca de recarga industrial de alta voltagem." << endl;
        }

        void planejarRota(string destino) override
        {
            cout << "[Caminhao " << id << "] Calculando rota para " << destino << " evitando pontes com restricao de peso e vias estreitas." << endl;
        }

        void detectarObstaculos() override
        {
            cout << "[Caminhao] Radar de longo alcance verificando transito na rodovia." << endl;
        }
};

class OnibusAutonomo : public VeiculoAutonomo
{
    private:
        int lotacaoMaxima;
        bool rampaAcessibilidade;

    public:
        OnibusAutonomo(int id, double bateria, string posicao, int lotacaoMaxima) : VeiculoAutonomo(id, bateria, posicao), lotacaoMaxima(lotacaoMaxima), rampaAcessibilidade(true) {}

        double consumoPorKm() override
        {
            return 0.8;
        }

        void estrategiaRecarga() override
        {
            cout << "[Onibus] Recarga por inducao no terminal central." << endl;
        }

        void planejarRota(string destino) override
        {
            cout << "[Onibus " << id << "] Calculando rota para " << destino << " priorizando faixas exclusivas e paradas obrigatorias." << endl;
        }
};

class Despachante
{
    private:
        vector<unique_ptr<VeiculoAutonomo>> frota;

    public:
        void adicionarVeiculo(VeiculoAutonomo* veiculo)
        {
            frota.push_back(unique_ptr<VeiculoAutonomo>(veiculo));
        }

        void gerenciarFrota()
        {
            cout << "--- INICIANDO OPERACAO DA FROTA ---" << endl;
            for(const auto& v : frota)
            {
                v->relatorioStatus();
                v->detectarObstaculos();
                v->estrategiaRecarga();
                v->planejarRota("Centro da Cidade");
                v->mover();
                cout << "-----------------------------------" << endl;
            }
        }
};

int main()
{
    Despachante central;

    central.adicionarVeiculo(new CarroAutonomo(101, 85.0, "Garagem A", 4));
    central.adicionarVeiculo(new CaminhaoAutonomo(201, 60.0, "Deposito Norte", 15.0, 6));
    central.adicionarVeiculo(new OnibusAutonomo(301, 90.0, "Terminal Sul", 45));
    central.adicionarVeiculo(new CarroAutonomo(102, 10.0, "Rua B", 2));

    central.gerenciarFrota();

    return 0;
}