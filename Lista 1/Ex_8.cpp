/* Em um sistema de e-commerce, o cliente adiciona produtos em um
carrinho de compras. Esse carrinho ´e usado para gerar um pedido,
que inclui informa¸c˜oes de pagamento. Monte as classes necess´arias e
implemente.*/

#include <iostream>
#include <string>

using namespace std;

class Produto
{
    private:
        string nome;
        double preco;

    public:
        Produto(string n, double p) : nome(n), preco(p) {}

        string getNome() 
        { 
            return nome; 
        }
        
        double getPreco() 
        { 
            return preco; 
        }
};

class Carrinho
{
    private:
        Produto *produto1;
        Produto *produto2;

    public:
        Carrinho(Produto *p1, Produto *p2) : produto1(p1), produto2(p2) {}

        double calcularTotal()
        {
            double total = 0;
            if(produto1)
            {
                total += produto1->getPreco();
            }
             
            if(produto2)
            {
                total += produto2->getPreco();
            }    
            return total;
        }

        void mostrarProdutos()
        {
            if(produto1)
            {
                cout << "Produto: " << produto1->getNome() << " - R$ " << produto1->getPreco() << "\n";
            }
            if(produto2)
            {
                cout << "Produto: " << produto2->getNome() << " - R$ " << produto2->getPreco() << "\n";
            }
        }
};

class Pagamento
{
    private:
        string metodo;
        double valor;

    public:
        Pagamento(string m, double v) : metodo(m), valor(v) {}

        void mostrar()
        {
            cout << "Pagamento via " << metodo << " no valor de R$ " << valor << "\n";
        }
};

class Pedido
{
    private:
        Carrinho *carrinho;
        Pagamento pagamento;

    public:
        Pedido(Carrinho *c, Pagamento p) : carrinho(c), pagamento(p) {}

        void confirmar()
        {
            cout << "Resumo do pedido:\n";
            if(carrinho)
            {
                carrinho->mostrarProdutos();
                cout << "Total: R$ " << carrinho->calcularTotal() << "\n";
            }
            pagamento.mostrar();
        }
};

class Cliente
{
    private:
        string nome;
        Carrinho *carrinho;

    public:
        Cliente(string n, Carrinho *c) : nome(n), carrinho(c) {}

        void finalizarCompra(string metodo)
        {
            if(carrinho)
            {
                double total = carrinho->calcularTotal();

                Pagamento p(metodo, total);
                Pedido pedido(carrinho, p);

                cout << "Cliente: " << nome << "\n";

                pedido.confirmar();
            }
        }
};

int main()
{
    Produto p1("Notebook", 3500.00);
    Produto p2("Mouse", 150.00);

    Carrinho carrinho(&p1, &p2);

    Cliente c1("Bruno", &carrinho);

    c1.finalizarCompra("Cartao de Credito");

    return 0;
}
