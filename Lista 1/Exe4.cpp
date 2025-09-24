/*Em uma clínica médica, cada paciente tem um prontuário contendo
diversas anotações médicas feitas por um médico responsável.
O prontuário deve estar vinculado a um paciente e a um médico.
Identifique e implemente as classes envolvidas.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Prontuario
{
    private:
        string pacienteNome;
        string medicoNome;
        vector<string> anotacoes;

    public:
        Prontuario(const string& p, const string& m)
        {
            pacienteNome = p;
            medicoNome = m;
        }

        ~Prontuario()
        {
            cout << "Prontuario apagado" << endl;
        };

        void adicionarAnotacao(const string& anotacao)
        {
            anotacoes.push_back(anotacao);
        }

        void exibir() const
        {
            cout << "Prontuario do paciente: " << pacienteNome << endl;
            cout << "Medico responsavel: " << medicoNome << endl;
            cout << "Anotacoes:" << endl;

            for (int i = 0; i < anotacoes.size(); i++)
            {
                cout << "- " << anotacoes[i] << endl;
            }
            cout << "-----------------" << endl;
        }
};

class Medico
{
    private:
        string nome;

    public:
        Medico(const string& n)
        {
            nome = n;
        }

        ~Medico()
        {
            cout << "Médico apagado" << endl;
        };

        string getNome() const
        {
            return nome;
        }
};

class Paciente
{
    private:
        string nome;
        Prontuario prontuario;

    public:
        Paciente(const string& n, const Medico& m)
            : prontuario(n, m.getNome())
        {
            nome = n;
        }

        void adicionarAnotacao(const string& texto)
        {
            prontuario.adicionarAnotacao(texto);
        }

        void exibirProntuario() const
        {
            prontuario.exibir();
        }
};

class Clinica
{
    private:
        vector<Medico> medicos;
        vector<Paciente> pacientes;

    public:
        void adicionarMedico(const Medico& m)
        {
            medicos.push_back(m);
        }

        void adicionarPaciente(const Paciente& p)
        {
            pacientes.push_back(p);
        }

        void exibirPacientes() const
        {
            for (int i = 0; i < pacientes.size(); i++)
            {
                pacientes[i].exibirProntuario();
            }
        }
};

int main()
{
    Clinica clinica;

    Medico medico1("Dr. Silva");

    Paciente paciente1("Joao", medico1);

    paciente1.adicionarAnotacao("Paciente apresenta dor de cabeça.");
    paciente1.adicionarAnotacao("Prescrito analgésico.");

    clinica.adicionarMedico(medico1);
    clinica.adicionarPaciente(paciente1);

    clinica.exibirPacientes();

    return 0;
}