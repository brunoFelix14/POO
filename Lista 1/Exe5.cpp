/*Uma institui¸c˜ao de ensino organiza cursos, que possuem v´arias tur-
mas. Cada turma ´e conduzida por um professor e cont´em v´arios alunos
matriculados. Represente esse cen´ario com classes em C++*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Professor
{
	private:
		string nome;

	public:
		Professor(string n)
		{
			nome = n;
		}

		string getNome()
		{
			return nome;
		}

		~Professor()
		{}
};

class Aluno
{
	private:
		string nome;

	public:
		Aluno(string n)
		{
			nome = n;
		}

		string getNome()
		{
			return nome;
		}

		~Aluno()
		{}
};

class Turma
{
	private:
		Professor professor;
		vector<Aluno> alunos;

	public:
		Turma(Professor p) : professor(p) {}

		void adicionarAluno(Aluno a)
		{
			alunos.push_back(a);
		}

		void mostrarTurma()
		{
			cout << "Professor: " << professor.getNome() << endl;
			cout << "Alunos:" << endl;
			for (Aluno &a : alunos)
			{
				cout << " - " << a.getNome() << endl;
			}
		}

		~Turma()
		{}
};

class Curso
{
	private:
		string nome;
		vector<Turma> turmas;

	public:
		Curso(string n)
		{
			nome = n;
		}

		void adicionarTurma(Turma t)
		{
			turmas.push_back(t);
		}

		void mostrarCurso()
		{
			cout << "Curso: " << nome << endl;
			for (Turma &t : turmas)
			{
				t.mostrarTurma();
			}
		}

		~Curso()
		{}
};

class Instituicao
{
	private:
		string nome;
		vector<Curso> cursos;

	public:
		Instituicao(string n)
		{
			nome = n;
		}

		void adicionarCurso(Curso c)
		{
			cursos.push_back(c);
		}

		void mostrarInstituicao()
		{
			cout << "Instituicao: " << nome << endl;
			for (Curso &c : cursos)
			{
				c.mostrarCurso();
			}
		}

		~Instituicao()
		{}
};

int main()
{
	Instituicao inst("IFMS");

	Curso curso1("Engenharia de Computacao");

	Professor prof1("Beto");
	Turma turma1(prof1);
	turma1.adicionarAluno(Aluno("Maria"));
	turma1.adicionarAluno(Aluno("Joao"));

	curso1.adicionarTurma(turma1);

	inst.adicionarCurso(curso1);

	inst.mostrarInstituicao();

	return 0;
}