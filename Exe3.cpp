/*Uma loja virtual registra pedidos de clientes. Cada pedido possui itens
(com produto, quantidade e pre¸co unit´ario) e est´a vinculado a um cli-
ente. O sistema deve calcular o valor total do pedido. Descubra as
classes e implemente.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pedido
{
    private:
        string produto;
        int quantidade;
        float preco;

    public:
        Pedido(const string& prod, int q, float p)
        {
            produto = prod;
            quantidade = q;
            preco = p;
        }

        ~Pedido()
        {
            cout << "Pedido Apagado" << endl;
        }

        float calcularTotal() const
        {
            return quantidade * preco;
        }

        void exibir() const
        {
            cout << produto << " x" << quantidade << " = R$ " << calcularTotal() << endl;
        }
};

class Cliente
{
    private:
        string nome;
        vector<Pedido> pedidos;

    public:
        Cliente(const string& n)
        {
            nome = n;
        }

        ~Cliente()
        {
            cout << "Cliente Apagado" << endl;
        }

        void adicionarPedido(const Pedido& pedido)
        {
            pedidos.push_back(pedido);
        }

        void exibirPedidos() const
        {
            cout << "Cliente: " << nome << endl;
            for(int i = 0; i < pedidos.size(); i++)
            {
                pedidos[i].exibir();
            }
        }
};

class Loja
{
    private:
        vector<Cliente> clientes;

    public:
        void adicionarCliente(const Cliente& cliente)
        {
            clientes.push_back(cliente);
        }

        void exibirClientes() const
        {
            for(int i = 0; i < clientes.size(); i++)
            {
                clientes[i].exibirPedidos();
                cout << "-----------------" << endl;
            }
        }
};

int main()
{
    Loja loja;

    Cliente cliente1("Bruno");

    Pedido pedido1("Mouse", 2, 50.0);
    Pedido pedido2("Teclado", 1, 120.0);

    cliente1.adicionarPedido(pedido1);
    cliente1.adicionarPedido(pedido2);

    loja.adicionarCliente(cliente1);

    loja.exibirClientes();

    return 0;
}