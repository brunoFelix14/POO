#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

class Funcionario
{
    protected:
        string nome;
        int id;

    public:
        Funcionario(string nome, int id) : nome(nome), id(id) {}

        virtual ~Funcionario() {}

        virtual double calcularPagamento() = 0;
        virtual string gerarDemonstrativo() = 0;
};

class Assalariado : public Funcionario
{
    private:
        double salarioMensal;

    public:
        Assalariado(string nome, int id, double salarioMensal) : Funcionario(nome, id), salarioMensal(salarioMensal) {}
 
        double calcularPagamento() override
        {
            return salarioMensal;
        }

        string gerarDemonstrativo() override
        {
            return "ID: " + to_string(id) + " | Assalariado: " + nome + " | R$ " + to_string(calcularPagamento());
        }
};

class Horista : public Funcionario
{
    private:
        double valorHora;
        double horasTrabalhadas;

    public:
        Horista(string nome, int id, double valorHora, double horasTrabalhadas) : Funcionario(nome, id), valorHora(valorHora), horasTrabalhadas(horasTrabalhadas) {}

        double calcularPagamento() override
        {
            if(horasTrabalhadas > 44)
            {
                double horasExtras = horasTrabalhadas - 44;
                return (44 * valorHora) + (horasExtras * valorHora * 1.5);
            }
            return horasTrabalhadas * valorHora;
        }

        string gerarDemonstrativo() override
        {
            return "ID: " + to_string(id) + " | Horista: " + nome + " | R$ " + to_string(calcularPagamento());
        }
};

class Comissionado : public Funcionario
{
    private:
        double salarioBase;
        double vendas;
        double percentual;

    public:
        Comissionado(string nome, int id, double salarioBase, double vendas, double percentual) : Funcionario(nome, id), salarioBase(salarioBase), vendas(vendas), percentual(percentual) {}

        double calcularPagamento() override
        {
            return salarioBase + (vendas * percentual);
        }

        string gerarDemonstrativo() override
        {
            return "ID: " + to_string(id) + " | Comissionado: " + nome + " | R$ " + to_string(calcularPagamento());
        }
};

int main()
{
    vector<unique_ptr<Funcionario>> funcionarios;

    funcionarios.push_back(unique_ptr<Assalariado>(new Assalariado("Joao Silva", 101, 3500.00)));
    funcionarios.push_back(unique_ptr<Horista>(new Horista("Maria Oliveira", 102, 60.0, 50.0)));
    funcionarios.push_back(unique_ptr<Comissionado>(new Comissionado("Carlos Santos", 103, 1500.0, 20000.0, 0.05)));

    cout << fixed << setprecision(2);
    cout << "--- FOLHA DE PAGAMENTO ---" << endl;

    for(const auto& func : funcionarios)
    {
        cout << func->gerarDemonstrativo() << endl;
    }

    return 0;
}