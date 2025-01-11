/* При необходимости запуска, закомментировать все, кроме нужного задания!*/

/* 1. Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
 Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
 
 Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const size_t DEFAULT_SIZE = 8;

class StringHasher {
public:
   StringHasher(size_t prime1 = 71, size_t prime2 = 7);
   size_t operator()(const string &str);
   size_t operator[](const string &str);

private:
   size_t prime1;
   size_t prime2;
};

StringHasher::StringHasher(size_t prime1, size_t prime2) {
   this->prime1 = prime1;
   this->prime2 = prime2;
}

size_t StringHasher::operator()(const string &str) {
   size_t hash = 0;
   for (int i = 0; i < str.size(); ++i) {
       hash = hash * prime1 + str[i];
   }
   return hash;
}

size_t StringHasher::operator[](const string &str) {
   size_t hash = 0;
   for (int i = 0; i < str.size(); ++i) {
       hash = hash * prime2 + str[i];
   }
   return hash;
}

template <typename T, typename Hasher>
class HashTable {
public:
   HashTable(size_t initial_size = DEFAULT_SIZE);

   bool Add(const T &key);
   bool Has(const T &key);
   bool Delete(const T &key);

   //деструктор не нужен, тк вектор автоматически очистит память, выделенную под него
private:
   void grow();

   vector<T> table;
   size_t size;
   Hasher hasher;
};

template <typename T, typename Hasher>
HashTable<T, Hasher>::HashTable(size_t initial_size) {
   size = 0;
   table = vector<T>(initial_size, T());
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T &key) {

   if (4 * size >= 3 * table.size()) grow();

   size_t hash1 = hasher(key);
   size_t hash_now = hash1;
   size_t hash2 = hasher[key];
   T element = table[hash_now % table.size()];
   int idx_del = -1;

   for (size_t idx = 0; idx < table.size(); ++idx) {
       if (element == "del" and idx_del == -1) idx_del = hash_now % table.size();
       else if (element == key) return false;
       else if (element == T()) {
           if (idx_del >= 0) table[idx_del] = key;
           else table[hash_now % table.size()] = key;
           size++;
           return true;
       }
       hash_now = (hash1 + idx * (2 * hash2 + 1));
       element = table[hash_now % table.size()];
   }
   table[idx_del] = key;
   size++;

   return true;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Has(const T &key) {
   size_t hash1 = hasher(key);
   size_t hash_now = hash1;
   size_t hash2 = hasher[key];
   T element = table[hash_now % table.size()];

   for (size_t idx = 0; idx < table.size(); ++idx) {
       if (element == key) return true;
       else if (element == T()) return false;
       hash_now = (hash1 + idx * (2 * hash2 + 1));
       element = table[hash_now % table.size()];
   }

   return false;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Delete(const T &key) {
   size_t hash1 = hasher(key);
   size_t hash_now = hash1;
   size_t hash2 = hasher[key];
   T element = table[hash_now % table.size()];

   for (size_t idx = 0; idx < table.size(); ++idx) {
       if (element == key) {
           table[hash_now % table.size()] = "del";
           size--;
           return true;
       }
       else if (element == T()) return false;
       hash_now = (hash1 + idx * (2 * hash2 + 1));
       element = table[hash_now % table.size()];
   }

   return false;
}

template <typename T, typename Hasher>
void HashTable<T, Hasher>::grow() {
   vector<T> TableNew(table.size() * 2, T());
   swap(table, TableNew);
   size = 0;

   for (size_t idx = 0; idx < TableNew.size(); ++idx) {
       if (TableNew[idx] != "del" and TableNew[idx] != T()) {
           Add(TableNew[idx]);
       }
   }
}


int main(int argc, const char * argv[]) {
   HashTable<string, StringHasher> table;

   char act;
   string key;

   while (cin >> act >> key)
   {
       switch (act)
       {
           case '?':
           {
               cout << (table.Has(key) ? "OK" : "FAIL") << endl;
               break;
           }
           case '+':
           {
               cout << (table.Add(key) ? "OK" : "FAIL") << endl;
               break;
           }
           case '-':
           {
               cout << (table.Delete(key) ? "OK" : "FAIL") << endl;
               break;
           }
           case '!':
           {
               return 0;
           }

       }
   }
   return 0;
}


/*
2. Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. Выведите элементы в порядке post-order (снизу вверх).
 Рекурсия запрещена.
 */

#include <iostream>
#include <stack>
using namespace std;

template <typename T>
struct DefaultComparator{
   bool operator()(const T& l, const T& r) const{
       return l < r;
   }
};

template <typename T>
struct Node {
   T data;
   Node *left = nullptr;
   Node *right = nullptr;
   Node(T val) : data(val){}
};

template <typename T, typename Comparator = DefaultComparator<T>>
class BinSearchTree {
private:
   Node<T>* root = nullptr;
   Comparator comp;
public:
   BinSearchTree() : root(nullptr) {}
   
   //Запрет копирования и присваивания
   BinSearchTree(const BinSearchTree&) = delete;
   BinSearchTree& operator=(const BinSearchTree&) = delete;

   ~BinSearchTree();
   
   void insert(T val);
   Node<T>*& findForDel(T val);
   Node<T>* find(T val);
   bool Delete(T val);
   void DeleteNode(Node<T>*& node);
//    void del(T val);
   void preOrd();

};

template <typename T, typename Comparator>
BinSearchTree<T, Comparator>::~BinSearchTree() {
   if (this->root == nullptr) return;
   
   stack<Node<T>*> stack1, stack2;
   stack1.push(this->root);
   
   while (not stack1.empty()) {
       Node<T>* node = stack1.top();
       stack1.pop();
       
       stack2.push(node);
       
       if (node->left != nullptr) {
           stack1.push(node->left);
       }
       
       if (node->right != nullptr) {
           stack1.push(node->right);
       }
   }
   
   while (not stack2.empty()) {
       Node<T>* node = stack2.top();
       stack2.pop();
       
       delete node;
   }
}

template <typename T, typename Comparator>
void BinSearchTree<T, Comparator>::insert(T val) {
   Node<T>* newNode = new Node<T>(val);
   Node<T>* node = this->root;
   if (node == nullptr) {
       this->root = newNode;
       return;
   }
   Node<T>* parent = nullptr;
   while (node != nullptr) {
       parent = node;
       if (comp(val, node->data)) {
           node = node->left;
       }
       else if (comp(node->data, val)) {
           node = node->right;
       }
   }
   if (comp(val, parent->data)) {
       parent->left = newNode;
   }
   else {
       parent->right = newNode;
   }
}

//получаем ссылку на указатель на узел, чтобы при удалении можно было изменять сам узел
template <typename T, typename Comparator>
Node<T>*& BinSearchTree<T, Comparator>::findForDel(T val) {
   Node<T>** node = &this->root;
   while (*node != nullptr) {
       if (comp(val, (*node)->data)) {
           node = &(*node)->left;
       }
       else if (comp((*node)->data, val)) {
           node = &(*node)->right;
       }
       else {
           return *node;
       }
   }
   return *node;
}

template <typename T, typename Comparator>
Node<T>* BinSearchTree<T, Comparator>::find(T val) {
   Node<T>*& node = findForDel(val);
   return node;
}



//template <typename T, typename Comparator>
//void BinSearchTree<T, Comparator>::del(T val) {
//    Node<T>* node = this->root;
//    Node<T>* parent = nullptr;
//    while (node != nullptr) {
//        parent = node;
//        if (comp(val, node->data)) {
//            node = node->left;
//        }
//        else if (comp(node->data, val)) {
//            node = node->right;
//        }
//    }
//    if (node == nullptr) return;
//
//    //Нет детей
//    if (node->left == nullptr and node->right == nullptr) {
//        if (parent == nullptr) {
//            this->root = nullptr; //удаляем корень
//        }
//        else if (comp(val, parent->data)) {
//            parent->left = nullptr;
//        }
//        else {
//            parent->right = nullptr;
//        }
//        delete node;
//    }
//
//    //1 ребенок
//    else if (node->left != nullptr or node->right != nullptr) {
//        Node<T>* child = node->left == nullptr ? node->right : node->left;
//        if (parent == nullptr) {
//            this->root = nullptr; //удаляем корень
//        }
//        else if (comp(val, parent->data)) {
//            parent->left = child;
//        }
//        else {
//            parent->right = child;
//        }
//        delete node;
//    }
//
//    //2 ребенка
//    else {
//        Node<T>* child = node->right;
//        if (parent == nullptr) {
//            this->root = nullptr; //удаляем корень
//        }
//        else if (child->left == nullptr) {
//            node = child;
//        }
//    }
//}

template <typename T, typename Comparator>
bool BinSearchTree<T, Comparator>::Delete(T val) {
   Node<T>*& node = findForDel(val);
   if (node == nullptr) return false;
   DeleteNode(node);
   return true;
}

template <typename T, typename Comparator>
void BinSearchTree<T, Comparator>::DeleteNode(Node<T>*& node ) {
   if (node->left == nullptr) { // Нет левого поддерева.
       Node<T>* right = node->right;
       delete node;
       node = right;
   }
   else if (node->right == nullptr) { // Если нет правого поддерева.
       Node<T>* left = node->left; // Подставляем левое.
       delete node;
       node = left;
   }
   else { // Есть оба поддерева.
   // Ищем минимальный элемент в правом поддереве и его родителя.
       Node<T>* minParent = node;
       Node<T>* min = node->right;
       while (min->left != nullptr) {
           minParent = min;
           min = min->left;
       }
   node->data = min->data;
   // Удаляем min, подставляя на его место min->right.
   (minParent->left == min ? minParent->left : minParent->right) = min->right;
   delete min;
   }
}


template <typename T, typename Comparator>
void BinSearchTree<T, Comparator>::preOrd() {
   if (this->root == nullptr) return;
   
   stack<Node<T>*> stack1, stack2;
   stack1.push(this->root);
   while (not stack1.empty()) {
       Node<T>* node = stack1.top();
       stack1.pop();
       
       stack2.push(node);
       
       if (node->left != nullptr) {
           stack1.push(node->left);
       }
       
       if (node->right != nullptr) {
           stack1.push(node->right);
       }
   }
   
   while (not stack2.empty()) {
       Node<T>* node = stack2.top();
       stack2.pop();
       
       cout << node->data << " ";
   }
}

int main() {
   int n;
   BinSearchTree<int, DefaultComparator<int>> tree;
   cin >> n;
   for (int i = 0; i < n; ++i) {
       int el;
       cin >> el;
       tree.insert(el);
   }
   tree.preOrd();
   cout << endl;
   return 0;
}

/*3. Постройте B-дерево минимального порядка t и выведите его по слоям.
 В качестве ключа используются числа, лежащие в диапазоне [0..232-1]

 Требования:

 B-дерево должно быть реализовано в виде шаблонного класса.
 Решение должно поддерживать передачу функции сравнения снаружи.*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class BTree
{
public:
   struct Node
   {
       Node(bool leaf)
       : leaf(leaf)
       {
       }
       
       ~Node()
       {
           for (Node* child: children)
           {
               delete child;
           }
       }
       
       bool leaf;
       std::vector<T> keys;
       std::vector<Node*> children;
   };
   
   BTree(size_t min_degree)
   : t(min_degree), root(nullptr)
   {
   }
   
   ~BTree()
   {
       if (root)
           delete root;
   }
   
   void Insert(const T &key)
   {
       if (!root)
           root = new Node(true);
       
       // здесь и дальше: если при спуске по дереву находим
       // переполненный узел -- сначала разбиваем его, потом спускаемся
       if (isNodeFull(root))
       {
           Node *newRoot = new Node(false);
           newRoot->children.push_back(root);
           root = newRoot;
           splitChild(root, 0);
       }
       
       // теперь корень точно не переполнен, можем вызвать insertNonFull
       insertNonFull(root, key);
   }
   
   void bfs() {
       if (!root) return;
       
       queue<const typename BTree<T>::Node*> q;
       q.push(root);
       q.push(nullptr);
       while (!q.empty()) {
           const auto* node = q.front();
           q.pop();
           if (node == nullptr) {
               cout << endl;
               if (!q.empty()) {
                   q.push(nullptr);
               }
               continue;
           }
           for (int i = 0; i < node->keys.size(); ++i) {
               cout << node->keys[i] << " ";
           }
           for (int i = 0; i < node->children.size(); ++i) {
               if (node->children[i]) {
                   q.push(node->children[i]);
               }
           }
       }
   }
   
   void debugPrint()
   {
       debugPrintInternal(root, 0);
   }
   
private:
   
   void debugPrintInternal(Node *node, int indent)
   {
       std::cout << std::string(indent, ' ');
       std::cout << "keys: [";
       for (auto it = node->keys.begin(); it != node->keys.end(); it++)
       {
           std::cout << (*it);
           if (it + 1 != node->keys.end())
               std::cout << ", ";
       }
       std::cout << "]" << std::endl;
       
       for (auto child: node->children)
       {
           debugPrintInternal(child, indent + 4);
       }
   }
   
   bool isNodeFull(Node *node)
   {
       return node->keys.size() == 2*t - 1;
   }
   
   void splitChild(Node *node, size_t index) {
       Node *nowChild = node->children[index];
       
       Node *newNode = new Node(nowChild->leaf);
       
       for (int i = 0; i < t - 1; ++i) {
           newNode->keys.push_back(nowChild->keys[i + t]);
       }
       if (!nowChild->leaf) {
           for (int i = 0; i < t; ++i) {
               newNode->children.push_back(nowChild->children[i + t]);
           }
       }
       nowChild->keys.resize(t - 1);
       if (!nowChild->leaf) {
               nowChild->children.resize(t);
       }
       
//        node->children.insert(node->children.begin() + index + 1, newNode);
//        
//        
//        node->keys.insert(node->keys.begin() + index, nowChild->keys[t - 1]);
       node->children.resize(node->children.size() + 1);
       for (int i = node->children.size() - 1; i > index + 1; --i) {
           node->children[i] = node->children[i - 1];
       }
       node->children[index + 1] = newNode;
       
       node->keys.resize(node->keys.size() + 1);
       for (int i = node->keys.size() - 1; i > index; --i) {
           node->keys[i] = node->keys[i - 1];
       }
       node->keys[index] = nowChild->keys[t - 1];
   }
   
//    void splitChild(Node *node, size_t index) {
//            Node *child = node->children[index];
//            Node *newNode = new Node(child->leaf);
//            newNode->keys.resize(t - 1);
//
//            for (int j = 0; j < t - 1; j++) {
//                newNode->keys[j] = child->keys[j + t];
//            }
//
//            if (!child->leaf) {
//                newNode->children.resize(t);
//                for (int j = 0; j < t; j++) {
//                    newNode->children[j] = child->children[j + t];
//                }
//            }
//
//            child->keys.resize(t - 1);
//            if (!child->leaf) {
//                newNode->children.resize(t);
//                for (int j = 0; j < t; j++) {
//                    newNode->children[j] = child->children[j + t];
//                }
//            }
//
//            child->keys.resize(t - 1);
//            if (!child->leaf) {
//                child->children.resize(t);
//            }
//
//            node->children.insert(node->children.begin() + index + 1, newNode);
//            node->keys.insert(node->keys.begin() + index, child->keys[t - 1]);
//        }

   
   // вставить ключ key в гарантированно не переполненную ноду node
   void insertNonFull(Node *node, const T &key)
   {
       int pos = node->keys.size() - 1;
       
       // гарантированно не перепеполненный лист -- запишем новый ключ в него
       if (node->leaf)
       {
           // расширили вектор ключей для вставки нового
           node->keys.resize(node->keys.size() + 1);
           while (pos >= 0 && key < node->keys[pos])
           {
               // обходим ключи справа налево, сдвигая вправо на 1
               node->keys[pos + 1] = node->keys[pos];
               pos--;
           }
           // вставляем новый ключ на освобожденное в цикле место
           node->keys[pos + 1] = key;
       }
       // не лист, значит есть потомки, пишем в один из них
       else
       {
           // ищем позицию потомка, в которого добавим ключ
           while (pos >= 0 && key < node->keys[pos])
           {
               pos--;
           }
           
           // если потомок и так полон, надо его сначала разбить
           if (isNodeFull(node->children[pos + 1]))
           {
               splitChild(node, pos + 1);
               // после разбиения потомка в текущий узел из него поднялся ключ
               // надо сравниться и с ним
               if (key > node->keys[pos + 1])
                   pos++;
           }
           insertNonFull(node->children[pos + 1], key);
       }
   }
   
   size_t t;
   Node *root;
   
   friend void test1();
};

// случаи вставки с иллюстраций в лекции
void test1()
{
   BTree<char> tree(3);
   
   tree.root = new BTree<char>::Node(false);
   tree.root->keys = {'G', 'M', 'P', 'X'};
   
   {
       auto child = new BTree<char>::Node(true);
       child->keys = {'A', 'C', 'D', 'E'};
       tree.root->children.push_back(child);
   }
   
   {
       auto child = new BTree<char>::Node(true);
       child->keys = {'J', 'K'};
       tree.root->children.push_back(child);
   }
   {
       auto child = new BTree<char>::Node(true);
       child->keys = {'N', 'O'};
       tree.root->children.push_back(child);
   }
   {
       auto child = new BTree<char>::Node(true);
       child->keys = {'R', 'S', 'T', 'U', 'V'};
       tree.root->children.push_back(child);
   }
   {
       auto child = new BTree<char>::Node(true);
       child->keys = {'Y', 'Z'};
       tree.root->children.push_back(child);
   }
   
   std::cout << "Initial tree:" << std::endl;
   tree.debugPrint();
   std::cout << std::endl;
   
   std::string insertKeys = "BQLF";
   // посимвольно добавляем в дерево ключи
   for (auto c: insertKeys)
   {
       tree.Insert(c);
       std::cout << "After inserting " << c << ":" << std::endl;
       tree.debugPrint();
       std::cout << std::endl;
   }
}

int main(int argc, const char * argv[]) {
   int t;
   cin >> t;
   cin.ignore();
   BTree<int> tree(t);
   string stroka;
   getline(cin, stroka);
   stringstream stream(stroka);
   int key;
   while (stream >> key) {
       tree.Insert(key);
   }
   tree.bfs();
   cout << endl;
   return 0;
}


/*4. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n).
*/

#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
struct DefaultComparator{
   bool operator()(const T& l, const T& r) const{
       return l >= r; //поменять при другой задаче, слева большие элементы, справа меньше или равно
   }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class AvlTree
{
 struct Node
 {
     Node(const T &data)
     : data(data), left(nullptr), right(nullptr), height(1), count(1)
     {
     }
     
     T data;
     Node *left;
     Node *right;
     size_t height;
     size_t count;
 };
   
public:
   AvlTree()
   : root(nullptr)
   {
   }
   
   //Запрет копирования и присваивания
       AvlTree(const AvlTree&) = delete;
       AvlTree& operator=(const AvlTree&) = delete;
   
   ~AvlTree()
   {
       destroyTree(root);
   }
   
   void Add(const T &data)
   {
       root = addInternal(root, data);
   }
   
   int AddStatics(const T &data) {
       int statics = 0;
       root = addInternalStatics(root, data, statics); //addInternal, если не нужна порядковая стат
       return statics;
   }
   
   bool Has(const T &data)
   {
       Node *tmp = root;
       while (tmp)
       {
           if (comp(tmp->data, data)) {
               tmp = tmp->right;
           }
           else if (comp(data, tmp->data)) {
               tmp = tmp->left;
           }
           else {
               return true;
           }
       }
       return false;
   }
   void Delete(const T &data)
   {
       root = deleteInternal(root, data);
   }
   
   void DeleteStatics(int idx)
   {
       root = deleteInternalStatics(root, idx);
   }
   
   void PrintTree() const {
           printTree(root, 0);
       }
   
private:
   
   void destroyTree(Node *node)
   {
       if (node)
       {
           destroyTree(node->left);
           destroyTree(node->right);
           delete node;
       }
   }
   
   Node* deleteInternal(Node *node, const T &data)
   {
       if (!node)
           return nullptr;
       if (comp(node->data, data))
           node->right = deleteInternal(node->right, data);
       else if (comp(data, node->data))
           node->left = deleteInternal(node->left, data);
       else
       {
           Node *left = node->left;
           Node *right = node->right;
           
           delete node;
           
           if (!right)
               return left;
           else if (!left)
               return right;
           
           // поддерево, из которого берем элемент взамен удаляемого, выбираем на основе сравнения глубин.
           // (берем из более глубокого)
           
           Node *min;
           if (right->height <= left->height) {
               min->left = findAndRemoveMax(left, min); //если дерево классическое, в данной реализации c отзеркаленным деревом надо искать Min
               min->right = right;
           }
           else 
           {
               min->right = findAndRemoveMin(right, min); //тут вроде тоже поменять
               min->left = left;
           }
           
           return doBalance(min);
       }
       return doBalance(node);
   }
   
   
   Node* deleteInternalStatics(Node *node, int idx) {
       if (!node) 
           return nullptr;

       int leftCount = (node->left) ? node->left->count : 0; // возможно не нужен +1

       if (idx < leftCount) {
           node->left = deleteInternalStatics(node->left, idx);
       }
       else if (idx > leftCount) {
           node->right = deleteInternalStatics(node->right, idx - leftCount - 1);
       }
       else {
           Node *left = node->left;
           Node *right = node->right;
           delete node;

           if (!right) 
               return left;
           if (!left) 
               return right;
           
           // поддерево, из которого берем элемент взамен удаляемого, выбираем на основе сравнения глубин.
           // (берем из более глубокого)
           
           Node *newNode = new Node(0);
           T newData;
           if (right->height > left->height) {
               newNode->right = findAndRemoveMax(right, newData);
               newNode->left = left;
           }
           else {
               newNode->left = findAndRemoveMin(left, newData);
               newNode->right = right;
           }
           newNode->data = newData;
           return doBalance(newNode);
       }

       return doBalance(node);
   }


   
   Node* findMin(Node *node)
   {
       while (node->left)
           node = node->left;
       return node;
   }
   
   Node* removeMin(Node *node)
   {
       if (!node->left)
           return node->right;
       node->left = removeMin(node->left);
       return doBalance(node);
   }
   
   Node* findAndRemoveMin(Node *node, T &min)
   {
       if (!node->right) {
           min = node->data;
           return node->left;
       }
       node->right = findAndRemoveMin(node->right, min);
       return doBalance(node);
   }
   
   Node* findAndRemoveMax(Node *node, T &max)
   {
       if (!node->left) {
           max = node->data;
           return node->right;
       }
       node->left = findAndRemoveMax(node->left, max);
       return doBalance(node);
   }
   
   Node* addInternal(Node *node, const T &data)
   {
       if (!node)
           return new Node(data);
       if (comp(data, node->data)) {
           node->left = addInternal(node->left, data);
       }
       else {
           node->right = addInternal(node->right, data);
       }
       
       return doBalance(node);
   }
   

   Node* addInternalStatics(Node *node, const T &data, int &statics) {
       if (!node) {
           return new Node(data);
       }
       if (data == 50) cout << "leftCountStart: " << data << " " << node->left->count << endl;
       int leftCount = (node->left) ? node->left->count : 0; //возможно +1 не нужен
       cout << "data: " << data << " " << statics << endl;

       if (comp(data, node->data)) {
           node->left = addInternalStatics(node->left, data, statics);
       }
       else {
           cout << "leftCount: " << data << " " << leftCount << endl;
           statics += leftCount + 1;
           cout << "data: " << data << " " << statics << endl;
           node->right = addInternalStatics(node->right, data, statics);
       }
       return doBalance(node);
   }


   
   size_t getHeight(Node *node)
   {
       return node ? node->height : 0;
   }
   
   void fixHeight(Node *node)
   {
       node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
   }
   
   void fixCount(Node *node)
   {
       if (!node) return;
       
       size_t leftCount = (node->left) ? node->left->count : 0;
       size_t rightCount = (node->right) ? node->right->count : 0;
       
       node->count = leftCount + rightCount + 1;
   }
   
   int getBalance(Node *node)
   {
       return getHeight(node->right) - getHeight(node->left);
   }
   
   Node* rotateLeft(Node *node)
   {
       Node *tmp = node->right;
       node->right = tmp->left;
       tmp->left = node;
       fixHeight(node);
       fixCount(node);
       fixHeight(tmp);
       fixCount(tmp);
       return tmp;
   }
   
   Node* rotateRight(Node *node)
   {
       Node *tmp = node->left;
       node->left = tmp->right;
       tmp->right = node;
       fixHeight(node);
       fixCount(node);
       fixHeight(tmp);
       fixCount(tmp);
       return tmp;
   }
   
   Node* doBalance(Node *node)
   {
       fixHeight(node);
       fixCount(node);
       switch (getBalance(node))
       {
           case 2:
           {
               if (getBalance(node->right) < 0)
                   node->right = rotateRight(node->right);
               return rotateLeft(node);
           }
           case -2:
           {
               if (getBalance(node->left) > 0)
                   node->left = rotateLeft(node->left);
               return rotateRight(node);
           }
           default:
               return node;
       }
   }
   
   void printTree(Node *node, int indent) const {
           if (node == nullptr) {
               return;
           }

           // Печатаем правое поддерево с увеличенным отступом
           if (node->right) {
               printTree(node->right, indent + 4);
           }

           // Печатаем текущий узел
           if (indent > 0) {
               std::cout << std::setw(indent) << ' ';
           }
           std::cout << node->data << std::endl;

           // Печатаем левое поддерево с увеличенным отступом
           if (node->left) {
               printTree(node->left, indent + 4);
           }
       }
   
   Node *root;
   Comparator comp;
};

int main(int argc, const char * argv[]) {
   AvlTree<int> tree;
   size_t N, command;
   int node;
   cin >> N;
   for (int i = 0; i < N; ++i) {
       cin >> command >> node;
       switch (command) {
           case 1:
               cout << tree.AddStatics(node) << endl;
               tree.PrintTree();
               break;
           case 2:
               tree.DeleteStatics(node);
               tree.PrintTree();
               break;
           default:
               cout << "Wrong command" << endl;
               break;
       }
   }
   return 0;
}


/*5. Напишите две функции для создания архива из одного файла и извлечения файла из архива.
 
 Метод архивирует данные из потока original
 void Encode(IInputStream& original, IOutputStream& compressed);

 Метод восстанавливает оригинальные данные
 void Decode(IInputStream& compressed, IOutputStream& original);

 где:
 typedef char byte;

 interface IInputStream {
 // Возвращает false, если поток закончился
 virtual bool Read(byte& value) = 0;
 };

 interface IOutputStream {
 virtual void Write(byte value) = 0;
 };

 В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных. Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.

 В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит размер сжатого файла в процентах от исходного.

 Пример минимального решения:
 #include "Huffman.h"

 static void copyStream(IInputStream&input, IOutputStream& output) {
 byte value;
 while(input.Read(value)) { output.Write(value); }
 }

 void Encode(IInputStream& original, IOutputStream& compressed) {
 copyStream(original, compressed);
 }

 void Decode(IInputStream& compressed, IOutputStream& original) {
 copyStream(compressed, original);
 }

*/

//#include "Huffman.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <bitset>
#include <queue>
#include <random>
#include <ctime>


typedef unsigned char byte;
#define interface struct

interface IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
    virtual void Write(byte value) = 0;
};

// Реализация IInputStream на основе std::vector<byte>
class MemoryInputStream : public IInputStream {
private:
    const std::vector<byte>& buffer; // Ссылка на буфер с данными
    size_t position;                // Текущая позиция чтения

public:
    explicit MemoryInputStream(const std::vector<byte>& buf) : buffer(buf), position(0) {}

    bool Read(byte& value) override {
        if (position >= buffer.size()) {
            return false; // Достигнут конец потока
        }
        value = buffer[position++];
        return true;
    }
};

// Реализация IOutputStream на основе std::vector<byte>
class MemoryOutputStream : public IOutputStream {
private:
    std::vector<byte>& buffer; // Ссылка на буфер для записи данных

public:
    explicit MemoryOutputStream(std::vector<byte>& buf) : buffer(buf) {}

    void Write(byte value) override {
        buffer.push_back(value); // Добавляем байт в буфер
    }
};




struct Node {
    byte symbol; //символ
    int freq; //частота
    Node* left; //левый потомок
    Node* right;//правый потомок
    bool isLeaf = false;
    
    //конструктор при добавлении нового листа
    Node(byte sym, int freq) : symbol(sym), freq(freq), left(nullptr), right(nullptr), isLeaf(true) {
        if (this->symbol == 0 and this->freq == 0) isLeaf = false;
    }
    
    //конструктор при добавлении двух листов в один узел
    Node(Node *left, Node *right) : symbol(0), freq(left->freq + right->freq), left(left), right(right), isLeaf(false) {}
    

    
    struct NodesComparator{
        bool operator()(const Node *node1, const Node *node2) const{
            return node1->freq > node2->freq;
        }
    };
};


class BitWriter
{
public:
    BitWriter()
    : bitCount(0)
    {
    }
    
    void WriteBit(unsigned char bit)
    {
        if (bitCount % 8 == 0)
        {
            buffer.push_back(0);
        }
        if (bit)
        {
            buffer[bitCount/8] |= 1 << (7 - bitCount % 8);
        }
        bitCount++;
    }
    
    void WriteByte(unsigned char byte)
    {
        if (bitCount % 8 == 0)
        {
            buffer.push_back(byte);
        }
        else
        {
            int offset = bitCount % 8;
            buffer[bitCount/8] |= byte >> offset;
            buffer.push_back(byte << (8 - offset));
        }
        bitCount += 8;
    }
    
    const std::vector<unsigned char> &GetBuffer() const
    {
        return buffer;
    }
    
    size_t GetBitCount() const
    {
        return bitCount;
    }
    
private:
    std::vector<unsigned char> buffer;
    size_t bitCount;
};

class BitReader
{
public:
    BitReader(IInputStream& compressed)
        : stream(compressed),
          currentByte(0),
          nextByte(0),
          isLastByte(false),
          bitsLeft(8) {
              if (!stream.Read(currentByte)) {
                  std::cout << "Error" << std::endl;
              };
              if (!stream.Read(nextByte)) {
                  std::cout << "Error" << std::endl;
              };
    }


    
    bool ReadBit(unsigned char& bit)
    {
        if (bitsLeft == 0 and !isLastByte) {
            currentByte = nextByte;
            if (!stream.Read(nextByte)) {
                isLastByte = true;
            }
            bitsLeft = 8;
        }
        
        else if(bitsLeft == 0 and isLastByte) {
            return false;
        }
        
        bit = (currentByte >> 7) & 1; //старший(самый левый) бит
        currentByte <<= 1;
        bitsLeft--;
        
        return true;
    }
    
    bool ReadByte(unsigned char& value)
    {
        if (bitsLeft == 0 and !isLastByte) {
            currentByte = nextByte;
            if (!stream.Read(nextByte)) {
                isLastByte = true;
            }
            value = currentByte;
            return true;
        }
        
        if (isLastByte and bitsLeft != 8) {
            return false;
        }

        value = (currentByte & 0xFF) | (nextByte >> bitsLeft); //склеиваем текущий и следующий байт
        currentByte = nextByte << (8 - bitsLeft); //обновляем текущий байт
        bitsLeft = (bitsLeft + 8) % 8;
        if (bitsLeft == 0) bitsLeft = 8;
        
        if (!stream.Read(nextByte)) {
            isLastByte = true;
        }

        return true;
    }
    bool isLastByte;
    int bitsLeft; //осталось битов в текущем байте
    byte currentByte; // Текущий байт
    byte nextByte; //следующий байт
private:
    IInputStream& stream;
};


void visualizeBuffer(const std::vector<unsigned char> &buffer)
{
    for (auto &b: buffer)
    {
        std::cout << std::bitset<8>(b) << "|";
    }
    std::cout << std::endl;
}

Node* BuildHuffmanTree(const std::unordered_map<byte, int>& frequencу) {
    std::priority_queue<Node*, std::vector<Node*>, Node::NodesComparator> q;
    for (const auto& [symb, freq] : frequencу) {
        if (freq != 0) {
            Node *node = new Node(symb, freq);
            q.push(node);
        }
    }
    
    if (q.size() == 1) {
        Node* node = q.top();
        q.pop();
        Node* newNode = new Node(0, 0);
        Node* root = new Node(newNode, node);
        return root;
    }
    
    
    while (q.size() > 1) {
        Node *left = q.top();
        q.pop();
        Node *right = q.top();
        q.pop();
        Node *newNode = new Node(left, right);
        q.push(newNode);
    }
    return q.top();
}

void BuildTableCodes(Node *root, std::string code, std::unordered_map<byte, std::string>& codes) {
    if (root == nullptr) {
        return;
    }
    if (root->isLeaf == true) {
        codes[root->symbol] = code;
    }
    
    BuildTableCodes(root->left, code + "0", codes);
    BuildTableCodes(root->right, code + "1", codes);
}

void serialize(Node *node, BitWriter &message, size_t len) {
    if (len == 1) {
        message.WriteBit(1);
        message.WriteByte(node->right->symbol);
        return;
    }
    if (node->isLeaf) {
        message.WriteBit(1);
        message.WriteByte(node->symbol);
    }
    else {
        serialize(node->left, message, len);
        serialize(node->right, message, len);
        message.WriteBit(0);
    }
}

Node* deserialize(BitReader& reader, byte countAlph) {
    int countRead = 0;
    std::stack<Node*> stack;
    
    if (countAlph == 1) {
        byte bit;
        reader.ReadBit(bit);
        byte symb;
        reader.ReadByte(symb);
        Node *node = new Node(symb, 0);
        Node* root = new Node(new Node(0, 0), node);
        return root;
    }
    
    while (true) {
        if (stack.size() <= 1 and countRead >= countAlph) {
            break;
        }
        byte bit;
        reader.ReadBit(bit);
        
        if (bit == 1) {
            byte symb;
            reader.ReadByte(symb);
            Node *node = new Node(symb, 0);
            stack.push(node);
            countRead++;
        }
        
        else {
            Node *right = stack.top();
            stack.pop();
            Node *left = stack.top();
            stack.pop();
            
            Node *newNode = new Node(left, right);
            stack.push(newNode);
        }
    }
    return stack.top();
}

void PrintTree(const Node* node, int depth = 0) {
    if (!node) {
        return; // Если узел пустой, ничего не делаем
    }

    // Отступы для текущей глубины
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }

    if (!node->left and !node->right) {
        std::cout << "'" << static_cast<char>(node->symbol) << "' (leaf)" << std::endl;
    } else {
        // Если узел внутренний, выводим информацию о нем
        std::cout << "[internal]" << std::endl;
    }

    // Рекурсивно выводим левое и правое поддеревья
    PrintTree(node->left, depth + 1);
    PrintTree(node->right, depth + 1);
}

void DeleteTree(Node* node) {
    if (node == nullptr) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

//Кодирование
void Encode(IInputStream& original, IOutputStream& compressed) {
    std::vector<byte> inputData;
    std::unordered_map<byte, int> freq;
    byte symb;
    bool check = false;
    int count_b = 0;
    bool find_compr = false;
    int num = -1; //запоминание типа файла
    
    
    
    while (original.Read(symb)) {
        check = true;
        freq[symb]++;
        inputData.push_back(symb);
        ++count_b;
        //Проверяем не является ли JPEG или MP3 файлом, они закордированы по умолчанию, поэтому при дополнительном кодировании мы наоборот ухудшим ситуацию
        //Проверка на MP3
        if (count_b == 2 and inputData[0] == 0xFF and inputData[1] == 0xFB) {
            find_compr = true;
            num = 1;
            break;
        }
        else if (count_b == 2 and inputData[0] == 0xFF and inputData[1] == 0xF3) {
            find_compr = true;
            num = 1;
            break;
        }
        else if (count_b == 2 and inputData[0] == 0xFF and inputData[1] == 0xF2) {
            find_compr = true;
            num = 1;
            break;
        }
        //Проверка на JPEG
        if (count_b == 3 and inputData[0] == 0xFF and inputData[1] == 0xD8 and inputData[2] == 0xFF) {
            find_compr = true;
            num = 2;
            break;
        }
    }
    
    if (find_compr) {
        compressed.Write(inputData[0]);
        compressed.Write(inputData[1]);
        compressed.Write(inputData[2]);
        while(original.Read(symb)) {
            compressed.Write(symb);
        }
        return;
    }
    
    if (!check) {
        return;
    }
    
    Node *root = BuildHuffmanTree(freq); //построение дерева Хаффмана и запись его вершины
    
    std::unordered_map<byte, std::string> codes; //хранение таблицы кодов
    
    BuildTableCodes(root, "", codes); //создание таблицы кодов
    
    BitWriter message; //выходное сообщение
    message.WriteByte(freq.size()); //первай байт - количество символов в дереве Хаффмана(алфавит меньше 255!!!)
    serialize(root, message, freq.size()); //сериализуем дерево
    
    //считаем длину кода Хаффмана
    int lastByteLen = 0;
    for (const auto& [symb, code] : codes) {
        lastByteLen += code.length() * freq[symb];
    }
    lastByteLen += 2 * freq.size() - 1 + 3; //3 это размер самого lastbytelen
    lastByteLen %= 8;
    message.WriteBit((lastByteLen >> 2) & 1); // Старший бит
    message.WriteBit((lastByteLen >> 1) & 1); // Средний бит
    message.WriteBit(lastByteLen & 1);        // Младший бит
    
    //запись кода Хаффмана
    for (byte symb : inputData) {
        for (byte i : codes[symb]) {
            message.WriteBit(i - '0'); //преобразовываем char в unsigned char
        }
    }
    
    //запись данных в поток
    const std::vector<unsigned char>& buffer = message.GetBuffer();
    for (unsigned char byte : buffer) {
        compressed.Write(byte);
    }
    DeleteTree(root);
}


//Декодирование
void Decode(IInputStream& compressed, IOutputStream& original) {
    //считываем длину алфавита
    byte countAlph;
    if (!compressed.Read(countAlph)) return;
    
    //получаем дерево Хаффмана
    BitReader reader(compressed);
    
    //Проверяем не является ли JPEG или MP3 файлом, они закордированы по умолчанию, поэтому при дополнительном кодировании мы наоборот ухудшим ситуацию
    if (countAlph == 0xFF and reader.currentByte == 0xD8 and reader.nextByte == 0xFF) {
        original.Write(0xFF);
        original.Write(0xD8);
        original.Write(0xFF);
        byte symb;
        while (compressed.Read(symb)) {
            original.Write(symb);
        }
        return;
    }
    
    else if (countAlph == 0xFF and (reader.currentByte == 0xFB or reader.currentByte == 0xF2 or reader.currentByte == 0xF3)) {
        original.Write(0xFF);
        original.Write(reader.currentByte);
        byte symb;
        while (compressed.Read(symb)) {
            original.Write(symb);
        }
        return;
    }
    
    Node* root = deserialize(reader, countAlph);
    
    //получаем длину последнего бита сообщения
    byte lastByte = 0;
    byte bit;
    reader.ReadBit(bit);
    lastByte |= (bit << 2);
    reader.ReadBit(bit);
    lastByte |= (bit << 1);
    reader.ReadBit(bit);
    lastByte |= bit;
    
    int lastByteLen = static_cast<int>(lastByte);
    
    if (lastByteLen == 0) {
        lastByteLen = 8;
    }
    
    if (reader.isLastByte) {
        lastByteLen += reader.bitsLeft - 8; //если уже зашли в последний байт и взяли оттуда часть данных
    }
    
    Node* currentNode = root;
    int counter = 0;
    
    //вывод в поток
    while (reader.ReadBit(bit)) {
        if (lastByteLen == 0) lastByteLen = 8;
        if (reader.isLastByte and lastByteLen != 0 and counter < lastByteLen) {
            currentNode = (bit == 1) ? currentNode->right : currentNode->left;
            counter++;
            
            if (currentNode->right == nullptr and currentNode->left == nullptr) {
                original.Write(currentNode->symbol);
                currentNode = root;
            }
        }
        else if(reader.isLastByte and (lastByteLen == 0 or counter >= lastByteLen)) {
            break;
        }
        else {
            currentNode = (bit == 1) ? currentNode->right : currentNode->left;
            
            if (currentNode->right == nullptr and currentNode->left == nullptr) {
                original.Write(currentNode->symbol);
                currentNode = root;
            }
        }
    }
    DeleteTree(root);
}

void PrintCompressedData(const std::vector<byte>& data) {
    std::cout << "Compressed data in bits:\n";
    for (size_t i = 0; i < data.size(); ++i) {
        std::bitset<8> bits(data[i]); // Представляем байт как 8 бит
        std::cout << bits;
        if (i < data.size() - 1) {
            std::cout << " "; // Разделяем байты пробелами
        }
    }
    std::cout << "\n";
}

std::vector<byte> GenerateRandomData(size_t length) {
    std::vector<byte> data;
    data.reserve(length);
    
    std::mt19937 rng(static_cast<unsigned int>(std::time(0))); // генератор случайных чисел
    std::uniform_int_distribution<int> dist(32, 126); // диапазон от пробела до тильды (~)
    
    for (size_t i = 0; i < length; ++i) {
        byte randomChar = static_cast<byte>(dist(rng));
        data.push_back(randomChar);
    }
    
    return data;
}

void TestHuffman() {
    // Генерация случайных данных
    for (size_t i = 1; i < 1000; ++i) {
//        std::vector<byte> inputData = GenerateRandomData(i);
//        std::vector<byte> inputData = {
//            0x42, 0x4D, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00,
//            0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
//            0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00,
//            0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
//            0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x13, 0x0B,
//            0x00, 0x00, 0x13, 0x0B, 0x00, 0x00, 0x00, 0x00,
//            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
//            0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
//            0xFF, 0xFF, 0xFF
//        };
        
        std::vector<byte> inputData = {
            0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
            0x49, 0x46, 0x00, 0x01, 0x01, 0x01, 0x00, 0x48,
            0x00, 0x48, 0x00, 0x00, 0xFF, 0xDB, 0x00, 0x43,
            0x00, 0x03, 0x02, 0x02, 0x03, 0x03, 0x02, 0x04,
            0x03, 0x03, 0x04, 0x04, 0x04, 0x05, 0x04, 0x05,
            0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06,
            0x06, 0x06, 0x06, 0xFF, 0xC0, 0x00, 0x11, 0x08,
            0x00, 0x48, 0x00, 0x48, 0x03, 0x01, 0x21, 0x00,
            0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 0xFF, 0xD9
        };


        
        // Выводим сгенерированные данные (для наглядности)
        std::cout << "Generated input data: ";
        for (byte b : inputData) {
            std::cout << static_cast<char>(b);
        }
        std::cout << "\n";
        
        // Создаем входной и выходной потоки
        MemoryInputStream inputStream(inputData);
        std::vector<byte> compressedData;
        MemoryOutputStream compressedStream(compressedData);
        
        // Сжимаем данные
        Encode(inputStream, compressedStream);
        
        // Проверяем сжатые данные
        std::cout << "Compressed data size: " << compressedData.size() << " bytes\n";
        PrintCompressedData(compressedData); // Печатаем данные в битовом формате
        
        // Декодируем обратно
        MemoryInputStream decompressedInputStream(compressedData);
        std::vector<byte> outputData;
        MemoryOutputStream outputStream(outputData);
        
        Decode(decompressedInputStream, outputStream);
        
        // Проверяем восстановленные данные
        std::cout << "Decompressed data: ";
        for (byte b : outputData) {
            std::cout << static_cast<char>(b);
        }
        std::cout << "\n";
        
        // Проверяем корректность восстановления
        if (outputData == inputData) {
            std::cout << "Decompression successful! Data matches original.\n";
        } else {
            std::cout << "Decompression failed! Data does not match original.\n";
            break;
        }
    }
}

int main() {
    TestHuffman();
    return 0;
}
