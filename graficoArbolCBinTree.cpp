#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <queue>

struct CNode
{
    CNode(int _v)
    {
        v = _v; nodes[0] = nodes[1] = 0;
    }
    int v;
    CNode* nodes[2];
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool find(int x, CNode**& p);
    bool ins(int x);
    bool rem(int x);
    CNode** rep(CNode** p);
    void inorder(CNode* n);
    void print();
    int height1(CNode* n);
    void h1(CNode* n, int h, int& maxh);
    int height2(CNode* n);
    void print_levels();
    void levels(CNode* n);
    CNode* getRoot() { return root; }

private:
    CNode* root;
    bool brep;
};

CBinTree::CBinTree()
{
    root = 0;   brep = 0;
}

CBinTree::~CBinTree()
{}

bool CBinTree::find(int x, CNode**& p)
{
    for (p = &root; *p && (*p)->v != x;
        p = &((*p)->nodes[(*p)->v < x]));
    return *p != 0;
}

bool CBinTree::ins(int x)
{
    CNode** p;
    if (find(x, p)) return 0;
    *p = new CNode(x);
    return 1;
}

bool CBinTree::rem(int x)
{
    CNode** p;
    if (!find(x, p)) return 0;

    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CNode** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    CNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

CNode** CBinTree::rep(CNode** p)
{
    CNode** q = p;
    for (q = &((*q)->nodes[!brep]); (*q)->nodes[brep];
        q = &((*q)->nodes[brep]));
    brep = !brep;
    return q;
}

void CBinTree::print()
{
    inorder(root);
    std::cout << " h = " << height2(root);
    std::cout << "\n";
}

void CBinTree::inorder(CNode* n)
{
    if (!n) return;
    inorder(n->nodes[0]);
    std::cout << n->v << " ";
    inorder(n->nodes[1]);
}

int CBinTree::height1(CNode* n)
{
    int maxh = 0;
    h1(root, 1, maxh);
    return maxh;
}

void CBinTree::h1(CNode* n, int h, int& maxh)
{
    if (!n) return;
    if (h > maxh) maxh = h;
    h1(n->nodes[0], h + 1, maxh);
    h1(n->nodes[1], h + 1, maxh);
}

int CBinTree::height2(CNode* n)
{
    if (!n) return 0;
    int l = height2(n->nodes[0]),
        r = height2(n->nodes[1]);
    return std::max(l, r) + 1;
}

void CBinTree::print_levels()
{
    std::cout << "\n";
    levels(root);
    std::cout << "\n";
}

void CBinTree::levels(CNode* n)
{
    if (!n) return;
    std::queue<CNode*> q;
    q.push(n);
    while (!q.empty())
    {
        CNode* x = q.front();
        std::cout << x->v << " ";
        if (x->nodes[0]) q.push(x->nodes[0]);
        if (x->nodes[1]) q.push(x->nodes[1]);
        q.pop();
    }
}

void drawTree(sf::RenderWindow& window, CNode* root, float x, float y,
    float offsetX, sf::Font& font, int level = 0)
{
    if (!root) return;

    if (root->nodes[0])
    {
        float childX = x - offsetX;
        float childY = y + 80;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(childX, childY), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, root->nodes[0], childX, childY, offsetX / 2, font, level + 1);
    }

    if (root->nodes[1])
    {
        float childX = x + offsetX;
        float childY = y + 80;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(childX, childY), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, root->nodes[1], childX, childY, offsetX / 2, font, level + 1);
    }

    sf::CircleShape circle(25);
    circle.setPosition(x - 25, y - 25);

    if (!root->nodes[0] && !root->nodes[1])
        circle.setFillColor(sf::Color(100, 150, 255));
    else
        circle.setFillColor(sf::Color(255, 100, 100));

    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::White);
    window.draw(circle);

    sf::Text text;
    text.setFont(font);

    std::stringstream ss;
    ss << root->v;
    text.setString(ss.str());
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(x - textBounds.width / 2, y - textBounds.height / 2 - 5);
    window.draw(text);
}

int main()
{
    CBinTree t;

    t.ins(60); t.print();
    t.ins(30); t.print();
    t.ins(70); t.print();
    t.ins(20); t.print();
    t.ins(40); t.print();
    t.ins(65); t.print();
    t.ins(80); t.print();
    t.ins(75); t.print();

    t.print_levels();

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Arbol Binario");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

    sf::Text titulo;
    titulo.setFont(font);
    titulo.setString("Arbol Binario");
    titulo.setCharacterSize(20);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(20, 20);

    sf::Text instrucciones;
    instrucciones.setFont(font);
    instrucciones.setString("Presiona ESC para cerrar");
    instrucciones.setCharacterSize(16);
    instrucciones.setFillColor(sf::Color(200, 200, 200));
    instrucciones.setPosition(20, 650);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color(30, 30, 40));

        CNode* raiz = t.getRoot();
        if (raiz)
        {
            drawTree(window, raiz, 600, 100, 200, font);
        }

        window.draw(titulo);
        window.draw(instrucciones);
        window.display();
    }

    return 0;
}