/*Uma empresa de transporte possui uma frota de ˆonibus, cada um
com sua rota. As rotas possuem v´arias paradas. A empresa tamb´em
mant´em motoristas associados `a frota. Elabore as classes e implemente.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Motorista
{
	private:
		string nome;

	public:
		Motorista(string n)
		{
			nome = n;
		}

		string getNome()
		{
			return nome;
		}

		~Motorista()
		{}
};

class Rota
{
	private:
		string nomeRota;
		vector<string> paradas;

	public:
		Rota(string n)
		{
			nomeRota = n;
		}

		void adicionarParada(const string& parada)
		{
			paradas.push_back(parada);
		}

		void mostrarRota()
		{
			cout << "Rota: " << nomeRota << endl;
			cout << "Paradas:" << endl;
			for (int i = 0; i < paradas.size(); i++)
			{
				cout << " - " << paradas[i] << endl;
			}
		}

		~Rota()
		{}
};

class Onibus
{
	private:
		string placa;
		Rota rota;
		Motorista motorista;

	public:
		Onibus(string p, Rota r, Motorista m) : placa(p), rota(r), motorista(m) {}

		void mostrarOnibus()
		{
			cout << "Onibus: " << placa << endl;
			cout << "Motorista: " << motorista.getNome() << endl;
			rota.mostrarRota();
		}

		~Onibus()
		{}
};

class EmpresaTransporte
{
	private:
		string nome;
		vector<Onibus> frota;

	public:
		EmpresaTransporte(string n)
		{
			nome = n;
		}

		void adicionarOnibus(Onibus o)
		{
			frota.push_back(o);
		}

		void mostrarFrota()
		{
			cout << "Empresa: " << nome << endl;
			for (int i = 0; i < frota.size(); i++)
			{
				frota[i].mostrarOnibus();
				cout << "-----------------" << endl;
			}
		}

		~EmpresaTransporte()
		{}
};

int main()
{
	Motorista motorista1("Carlos");
	Motorista motorista2("Ana");

	Rota rota1("Rota Centro");
	rota1.adicionarParada("Parada 1");
	rota1.adicionarParada("Parada 2");
	rota1.adicionarParada("Parada 3");

	Rota rota2("Rota Bairro");
	rota2.adicionarParada("Parada A");
	rota2.adicionarParada("Parada B");

	Onibus onibus1("ABC-1234", rota1, motorista1);
	Onibus onibus2("XYZ-5678", rota2, motorista2);

	EmpresaTransporte empresa("Transporte XPTO");
	empresa.adicionarOnibus(onibus1);
	empresa.adicionarOnibus(onibus2);

	empresa.mostrarFrota();

	return 0;
}