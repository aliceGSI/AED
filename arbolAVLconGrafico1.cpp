#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>

struct AVLNode
{
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    AVLNode* root;

    int getHeight(AVLNode* node)
    {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(AVLNode* node)
    {
        if (node)
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    AVLNode* rotateRight(AVLNode* y)
    {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x)
    {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* insert(AVLNode* node, int key)
    {
        if (!node)
            return new AVLNode(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->data)
            return rotateRight(node);

        if (balance < -1 && key > node->right->data)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->data)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node)
    {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, int key)
    {
        if (!root)
            return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else
        {
            if (!root->left || !root->right)
            {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {
                AVLNode* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (!root)
            return root;

        updateHeight(root);

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorder(AVLNode* node)
    {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void add(int key)
    {
        root = insert(root, key);
    }

    void remove(int key)
    {
        root = deleteNode(root, key);
    }

    void print()
    {
        inorder(root);
        std::cout << std::endl;
    }

    AVLNode* getRoot() { return root; }

    int getBalanceFactor(AVLNode* node)
    {
        return getBalance(node);
    }
};

void drawAVLTree(sf::RenderWindow& window, AVLNode* node, float x, float y,
    float offsetX, sf::Font& font, AVLTree& tree)
{
    if (!node) return;

    if (node->left)
    {
        float childX = x - offsetX;
        float childY = y + 80;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(childX, childY), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawAVLTree(window, node->left, childX, childY, offsetX / 2, font, tree);
    }

    if (node->right)
    {
        float childX = x + offsetX;
        float childY = y + 80;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(childX, childY), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawAVLTree(window, node->right, childX, childY, offsetX / 2, font, tree);
    }

    sf::CircleShape circle(25);
    circle.setPosition(x - 25, y - 25);
    circle.setFillColor(sf::Color(100, 255, 100));
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::White);
    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    std::stringstream ss;
    ss << node->data;
    text.setString(ss.str());
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(x - textBounds.width / 2, y - textBounds.height / 2 - 5);
    window.draw(text);

    int balance = tree.getBalanceFactor(node);
    sf::Text balanceText;
    balanceText.setFont(font);
    std::stringstream bss;
    bss << balance;
    balanceText.setString(bss.str());
    balanceText.setCharacterSize(14);

    if (balance > 1 || balance < -1)
        balanceText.setFillColor(sf::Color::Red);
    else
        balanceText.setFillColor(sf::Color::Yellow);

    sf::FloatRect balanceBounds = balanceText.getLocalBounds();
    balanceText.setPosition(x - balanceBounds.width / 2, y - 45);
    window.draw(balanceText);
}
///*
int main()
{
    AVLTree tree;

    tree.add(50);
    tree.add(30);
    tree.add(70);
    tree.add(20);
    tree.add(40);
    tree.add(60);
    tree.add(80);
    tree.add(10);
    tree.add(25);

    std::cout << "Recorrido Inorden: ";
    tree.print();
   
    
   // tree.remove(20);
    //tree.print();

    //std::cout << "Eliminando 30...\n";
    //tree.remove(30);
    //tree.print();

    //std::cout << "Eliminando 50...\n";
    //tree.remove(50);
    //tree.print();
    
    
    
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Arbol AVL");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

    sf::Text titulo;
    titulo.setFont(font);
    titulo.setString("Arbol AVL - Factor de Balance (izq - der)");
    titulo.setCharacterSize(20);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(20, 20);

    sf::Text instrucciones;
    instrucciones.setFont(font);
    instrucciones.setString("Amarillo: Balanceado | Rojo: Desbalanceado");
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

        AVLNode* raiz = tree.getRoot();
        if (raiz)
        {
            drawAVLTree(window, raiz, 600, 100, 200, font, tree);
        }

        window.draw(titulo);
        window.draw(instrucciones);
        window.display();
    }

    return 0;
}
//*/

/*
int main()
{
    AVLTree tree;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "AVL Desbalanceado");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

    sf::Text titulo;
    titulo.setFont(font);
    titulo.setString("AVL - Amarillo: Balanceado | Rojo: Desbalanceado");
    titulo.setCharacterSize(20);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(20, 20);

    sf::Text instrucciones;
    instrucciones.setFont(font);
    instrucciones.setString("Presiona ESPACIO para insertar siguiente nodo");
    instrucciones.setCharacterSize(16);
    instrucciones.setFillColor(sf::Color(200, 200, 200));
    instrucciones.setPosition(20, 650);

    int nodos[] = { 10, 20, 30, 40, 50, 25 };
    int index = 0;

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
                if (event.key.code == sf::Keyboard::Space && index < 6)
                {
                    tree.add(nodos[index]);
                    index++;
                }
            }
        }

        window.clear(sf::Color(30, 30, 40));

        AVLNode* raiz = tree.getRoot();
        if (raiz)
        {
            drawAVLTree(window, raiz, 600, 100, 200, font, tree);
        }

        window.draw(titulo);
        window.draw(instrucciones);
        window.display();
    }

    return 0;
}
*/
