#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

enum Color { RED, BLACK };

struct RBNode
{
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree
{
private:
    RBNode* root;

    void rotateLeft(RBNode*& root, RBNode*& pt)
    {
        RBNode* pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (!pt->parent)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(RBNode*& root, RBNode*& pt)
    {
        RBNode* pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (!pt->parent)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(RBNode*& root, RBNode*& pt)
    {
        RBNode* parent_pt = nullptr;
        RBNode* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
        {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left)
            {
                RBNode* uncle_pt = grand_parent_pt->right;

                if (uncle_pt && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    if (pt == parent_pt->right)
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            else
            {
                RBNode* uncle_pt = grand_parent_pt->left;

                if (uncle_pt && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    if (pt == parent_pt->left)
                    {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    RBNode* BSTInsert(RBNode* root, RBNode* pt)
    {
        if (!root)
            return pt;

        if (pt->data < root->data)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void inorder(RBNode* node)
    {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

public:
    RBTree() : root(nullptr) {}

    void insert(int data)
    {
        RBNode* pt = new RBNode(data);
        root = BSTInsert(root, pt);
        fixViolation(root, pt);
    }

    void print()
    {
        inorder(root);
        std::cout << std::endl;
    }

    RBNode* getRoot() { return root; }
};

void drawRBTree(sf::RenderWindow& window, RBNode* node, float x, float y,
    float offsetX, sf::Font& font)
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
        drawRBTree(window, node->left, childX, childY, offsetX / 2, font);
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
        drawRBTree(window, node->right, childX, childY, offsetX / 2, font);
    }

    sf::CircleShape circle(25);
    circle.setPosition(x - 25, y - 25);

    if (node->color == RED)
        circle.setFillColor(sf::Color(255, 50, 50));
    else
        circle.setFillColor(sf::Color(50, 50, 50));

    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::White);
    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    std::stringstream ss;
    ss << node->data;
    text.setString(ss.str());
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(x - textBounds.width / 2, y - textBounds.height / 2 - 5);
    window.draw(text);
}
/*

RBNode* minValueNode(RBNode* node) {
    RBNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

void fixDelete(RBNode*& root, RBNode* x) {
    while (x != root && (!x || x->color == BLACK)) {
        RBNode* parent = x->parent;
        RBNode* sibling;

        if (x == parent->left) {
            sibling = parent->right;

            if (sibling && sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rotateLeft(root, parent);
                sibling = parent->right;
            }

            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK)) {
                sibling->color = RED;
                x = parent;
            } else {
                if (!sibling->right || sibling->right->color == BLACK) {
                    if (sibling->left)
                        sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(root, sibling);
                    sibling = parent->right;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->right)
                    sibling->right->color = BLACK;
                rotateLeft(root, parent);
                x = root;
            }
        } else {
            sibling = parent->left;

            if (sibling && sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rotateRight(root, parent);
                sibling = parent->left;
            }

            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK)) {
                sibling->color = RED;
                x = parent;
            } else {
                if (!sibling->left || sibling->left->color == BLACK) {
                    if (sibling->right)
                        sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(root, sibling);
                    sibling = parent->left;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->left)
                    sibling->left->color = BLACK;
                rotateRight(root, parent);
                x = root;
            }
        }
    }

    if (x)
        x->color = BLACK;
}

void deleteNodeRB(RBTree& tree, int key) {
    RBNode* root = tree.getRoot();
    RBNode* node = root;

    while (node) {
        if (key < node->data)
            node = node->left;
        else if (key > node->data)
            node = node->right;
        else
            break;
    }

    if (!node) return; 

    RBNode* y = node;
    RBNode* x;
    Color yOriginalColor = y->color;

    if (!node->left) {
        x = node->right;
        if (node->parent) {
            if (node == node->parent->left)
                node->parent->left = node->right;
            else
                node->parent->right = node->right;
        } else {
            tree.root = node->right;
        }
        if (x) x->parent = node->parent;
    } else if (!node->right) {
        x = node->left;
        if (node->parent) {
            if (node == node->parent->left)
                node->parent->left = node->left;
            else
                node->parent->right = node->left;
        } else {
            tree.root = node->left;
        }
        if (x) x->parent = node->parent;
    } else {
        y = minValueNode(node->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == node) {
            if (x) x->parent = y;
        } else {
            if (y->parent) {
                if (y == y->parent->left)
                    y->parent->left = x;
                else
                    y->parent->right = x;
            }
            if (x) x->parent = y->parent;
            y->right = node->right;
            if (y->right) y->right->parent = y;
        }

        if (node->parent) {
            if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
        } else {
            tree.root = y;
        }

        y->parent = node->parent;
        y->left = node->left;
        if (y->left) y->left->parent = y;
        y->color = node->color;
    }

    delete node;

    if (yOriginalColor == BLACK) {
        fixDelete(tree.getRoot(), x);
    }
}

*/
int main()
{
    RBTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);

    std::cout << "Recorrido Inorden: ";
    tree.print();

    /*
    deleteNodeRB(tree, 30);
    std::cout << "Después de eliminar 30: ";
    tree.print();
    */
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Arbol Rojo-Negro");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

    sf::Text titulo;
    titulo.setFont(font);
    titulo.setString("Arbol Rojo-Negro - Rojo: Nodos Rojos | Negro: Nodos Negros");
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

        RBNode* raiz = tree.getRoot();
        if (raiz)
        {
            drawRBTree(window, raiz, 600, 100, 200, font);
        }

        window.draw(titulo);
        window.draw(instrucciones);
        window.display();
    }

    return 0;
}
