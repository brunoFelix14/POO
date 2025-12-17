#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <iomanip>

using namespace std;

struct Ponto
{
    double x, y;
};

class Forma
{
    protected:
        double x, y;

    public:
        Forma(double x, double y) : x(x), y(y) {}

        virtual ~Forma() {}

        virtual void desenhar() const = 0;
        virtual void mover(double dx, double dy) = 0;
        virtual double area() const = 0;
        virtual double perimetro() const = 0;
        virtual unique_ptr<Forma> clonar() const = 0;
        virtual void escalar(double fator) = 0;
};

class Circulo : public Forma
{
    private:
        double raio;

    public:
        Circulo(double x, double y, double raio) : Forma(x, y), raio(raio)
        {
            if(raio <= 0)
            {
                throw invalid_argument("Raio deve ser maior que zero.");
            } 
        }

        virtual ~Circulo() {}

        void desenhar() const override
        {
            cout << "[Circulo] Centro: (" << x << ", " << y << ") | Raio: " << raio << endl;
        }

        void mover(double dx, double dy) override
        {
            x += dx;
            y += dy;
        }

        double area() const override
        {
            return 3.14159 * raio * raio;
        }

        double perimetro() const override
        {
            return 2 * 3.14159 * raio;
        }

        unique_ptr<Forma> clonar() const override
        {
            return unique_ptr<Forma>(new Circulo(*this));
        }

        void escalar(double fator) override
        {
            if(fator <= 0)
            {
                throw invalid_argument("Fator de escala invalido.");
            } 
            raio *= fator;
        }
};

class Retangulo : public Forma
{
    private:
        double largura, altura;

    public:
        Retangulo(double x, double y, double largura, double altura) : Forma(x, y), largura(largura), altura(altura)
        {
            if(largura <= 0 || altura <= 0) 
            {
                throw invalid_argument("Dimensoes devem ser positivas.");
            }
        }   

        virtual ~Retangulo() {}

        void desenhar() const override
        {
            cout << "[Retangulo] Pos: (" << x << ", " << y << ") | Lar: " << largura << " | Alt: " << altura << endl;
        }

        void mover(double dx, double dy) override
        {
            x += dx;
            y += dy;
        }

        double area() const override
        {
            return largura * altura;
        }

        double perimetro() const override
        {
            return 2 * (largura + altura);
        }

        unique_ptr<Forma> clonar() const override
        {
            return unique_ptr<Forma>(new Retangulo(*this));
        }

        void escalar(double fator) override
        {
            if(fator <= 0)
            {
                throw invalid_argument("Fator de escala invalido.");
            } 
            largura *= fator;
            altura *= fator;
        }
};

class Poligono : public Forma
{
    private:
        vector<Ponto> vertices;

    public:
        Poligono(double x, double y, const vector<Ponto>& verts) : Forma(x, y), vertices(verts)
        {
            if(vertices.size() < 3)
            { 
                throw invalid_argument("Poligono precisa de pelo menos 3 vertices.");
            }
        }

        virtual ~Poligono() {}

        void desenhar() const override
        {
            cout << "[Poligono] Origem: (" << x << ", " << y << ") | Vertices: " << vertices.size() << endl;
        }

        void mover(double dx, double dy) override
        {
            x += dx;
            y += dy;
            for(auto& v : vertices)
            {
                v.x += dx;
                v.y += dy;
            }
        }

        double area() const override
        {
            double soma1 = 0, soma2 = 0;
            for(size_t i = 0; i < vertices.size(); i++)
            {
                size_t j = (i + 1) % vertices.size();
                soma1 += vertices[i].x * vertices[j].y;
                soma2 += vertices[i].y * vertices[j].x;
            }
            return abs(soma1 - soma2) / 2.0;
        }

        double perimetro() const override
        {
            double p = 0;
            for(size_t i = 0; i < vertices.size(); i++)
            {
                size_t j = (i + 1) % vertices.size();
                double dx = vertices[j].x - vertices[i].x;
                double dy = vertices[j].y - vertices[i].y;
                p += sqrt(dx * dx + dy * dy);
            }
            return p;
        }

        unique_ptr<Forma> clonar() const override
        {
            return unique_ptr<Forma>(new Poligono(*this));
        }

        void escalar(double fator) override
        {
            if(fator <= 0) 
            {
                throw invalid_argument("Fator de escala invalido.");
            }    

            for(auto& v : vertices)
            {
                v.x = x + (v.x - x) * fator;
                v.y = y + (v.y - y) * fator;
            }
        }
};

class Ferramenta
{
    public:
        virtual ~Ferramenta() {}
        virtual void aplicar(Forma& f) = 0;
};

class FerramentaRedimensionar : public Ferramenta
{
    private:
        double fator;

    public:
        FerramentaRedimensionar(double fator) : fator(fator) {}

        virtual ~FerramentaRedimensionar() {}

        void aplicar(Forma& f) override
        {
            cout << "--- Ferramenta: Redimensionando x" << fator << " ---" << endl;
            f.escalar(fator);
        }
};

class FerramentaMover : public Ferramenta
{
    private:
        double dx, dy;

    public:
        FerramentaMover(double dx, double dy) : dx(dx), dy(dy) {}

        virtual ~FerramentaMover() {}

        void aplicar(Forma& f) override
        {
            cout << "--- Ferramenta: Movendo (" << dx << ", " << dy << ") ---" << endl;
            f.mover(dx, dy);
        }
};

class Renderer
{
    private:
        vector<unique_ptr<Forma>> canvas;

    public:
        void adicionarForma(unique_ptr<Forma> f)
        {
            canvas.push_back(move(f));
        }

        void renderizar()
        {
            cout << "=== RENDERIZANDO CANVAS ===" << endl;
            for(const auto& f : canvas)
            {
                f->desenhar();
                cout << "    Area: " << f->area() << " | Perimetro: " << f->perimetro() << endl;
            }
            cout << "===========================" << endl;
        }

        void aplicarFerramentaEmTodos(Ferramenta& t)
        {
            for(auto& f : canvas)
            {
                try
                {
                    t.aplicar(*f);
                }

                catch(const exception& e)
                {
                    cerr << "Erro ao aplicar ferramenta: " << e.what() << endl;
                }
            }
        }

        void duplicarUltimo()
        {
            if(!canvas.empty())
            {
                cout << "--- Clonando ultimo elemento ---" << endl;
                canvas.push_back(canvas.back()->clonar());
            }
        }
};

int main()
{
    try
    {
        Renderer renderer;

        renderer.adicionarForma(unique_ptr<Circulo>(new Circulo(0, 0, 10)));
        renderer.adicionarForma(unique_ptr<Retangulo>(new Retangulo(5, 5, 20, 10)));
        
        vector<Ponto> triangulo = {{0, 0}, {10, 0}, {5, 10}};
        renderer.adicionarForma(unique_ptr<Poligono>(new Poligono(0, 0, triangulo)));

        renderer.renderizar();

        FerramentaRedimensionar zoom(2.0);
        renderer.aplicarFerramentaEmTodos(zoom);

        renderer.duplicarUltimo();
        
        FerramentaMover move(10, 10);
        renderer.aplicarFerramentaEmTodos(move);

        renderer.renderizar();

        cout << "\nTeste de Validacao:" << endl;
        unique_ptr<Circulo> cErro(new Circulo(0, 0, -5));
    }

    catch(const exception& e)
    {
        cerr << "EXCECAO CAPTURADA NA MAIN: " << e.what() << endl;
    }

    return 0;
}