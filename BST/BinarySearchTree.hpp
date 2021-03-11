#include <iostream>
#include <functional>

//
// Определение шаблона класса BinarySearchTree
//

template<class T>
class BinarySearchTree {
private:
  // Описание структуры узла со ссылками на детей
  struct Node {
    // Конструктор узла
    Node(const T &key, Node *left = nullptr, Node *right = nullptr,
         Node *p = nullptr) :
      key_(key), left_(left), right_(right), p_(p) {}

    T key_; // значение ключа, содержащееся в узле
    Node *left_; // указатель на левое поддерево
    Node *right_; // указатель на правое поддерево
    Node *p_; // указатель на родителя !!! не используется
  };

  // Дерево реализовано в виде указателя на корневой узел.
  Node *root_;
public:

  // Конструктор "по умолчанию" создает пустое дерево
  BinarySearchTree() : root_(nullptr) {}

  // Деструктор освобождает память, занятую узлами дерева
  virtual ~BinarySearchTree() {
    deleteSubtree(root_);
  }

  // Печать строкового изображения дерева в выходной поток out
  void print(std::ostream &out) const {
    printNode(out, root_);
    out << std::endl;
  }

  // Функция поиска по ключу в бинарном дереве поиска
  bool iterativeSearch(const T &key) const {
    auto curr = root_;
    bool is = false;
    while (curr != nullptr) {
      if (key == curr->key_) {
        is = true;
        return is;
      } else {
        if (key < curr->key_) {
          curr = curr->left_;
        } else if (key > curr->key_) {
          curr = curr->right_;
        }

      }
    }
    return is;
  }

  // Вставка нового элемента в дерево, не нарушающая порядка
  // элементов. Вставка производится в лист дерева
  bool insert(const T &key) {

    Node *newNode = new Node(key);

    if(root_ == nullptr) {
      root_ = newNode;
      return true;
    }

    Node* curr = root_;
    while (curr != nullptr) {
      if (curr->key_ == newNode->key_) {
        return false;
      }
      if (curr->key_ > newNode->key_) {
        if (curr->left_ == nullptr) {
          curr->left_ = newNode;
          newNode->p_ = curr;
          return true;
        } else {
          curr = curr->left_;
        }
      } else if (curr->key_ < newNode->key_) {
        if (curr->right_ == nullptr) {
          curr->right_ = newNode;
          newNode->p_ = curr;
          return true;
        } else {
          curr = curr->right_;
        }
      }
    }
  }



  // Удаление элемента из дерева, не нарушающее порядка элементов
  void deleteKey(const T &key) {
    remove(root_,key);
  }

  // Определение количества узлов дерева
  int getCount() const {
    return getCountSubTree(this->root_);
  }

  // Определение высоты дерева
  int getHeight() const {
    return getHeightSubTree(this->root_);
  }

  void inorderWalk() const{
    this->inorderWalk(root_);
  }
private:

  // Функция поиска адреса узла по ключу в бинарном дереве поиска
  Node *iterativeSearchNode(const T &key) const {
    Node *current = root_;
    while (current != nullptr) {
      while (key != current->key_) {
        current = (current->key_ < key ? current->right_ : current->left_);
      }

    }
    return current;
  }

  //
  // Рекурсивные функции, представляющие
  // рекурсивные тела основных интерфейсных методов
  //
  // Рекурсивная функция для освобождения памяти
  void deleteSubtree(Node *node) {
    if (node != nullptr) {
      deleteSubtree(node->left_);
      deleteSubtree(node->right_);
      delete node;
    }
  }

  // Рекурсивная функция определения количества узлов дерева
  int getCountSubTree(Node *node) const {
    if (node == nullptr)
      return 0;
    return (1 + getCountSubTree(node->left_) +
            getCountSubTree(node->right_));
  }

  // Рекурсивная функция определения высоты дерева
  int getHeightSubTree(Node *node) const {
    if (node == nullptr) {
      return 0;
    }
    int left = getHeightSubTree(node->left_);
    int right = getHeightSubTree(node->right_);
    return 1 + (left < right ? right : left);
  }

  // Рекурсивная функция для вывода изображения дерева в выходной поток
  void printNode(std::ostream &out, Node *root) const {
    // Изображение дерева заключается в круглые скобки.
    if (root) {
      // Для узлов дерева должна быть определена (или переопределена)
      // операция вывода в выходной поток <<
      printNode(out, root->left_);
      out << root->key_<<'\t';
      printNode(out, root->right_);
    }
  }

  // Рекурсивная функция для организации обхода узлов дерева.
  void inorderWalk(Node *node) const {
    if (node == NULL)
      return;

    inorderWalk(node->left_);

    std::cout << node->key_ << "\t";

    inorderWalk(node->right_);
  }


  //Добавление нового элемента в дерево (рекурсивно)
  void recursiveInsert(Node *&node, const T &key) {
    if (node == nullptr) {
      node = new Node(key);
    } else {
      recursiveInsert((key < node->key_ ? node->left_ : node->right_), key);
    }
  }

  //Поиск элемента следующего за указанным
  const Node *searchNext(Node *node, const T &key) {
    if (node == nullptr) {
      return nullptr;
    }
    if (key >= node->key_) {
      return searchNext(node->right_);
    } else {
      const Node *temp = searchNext(node->left_);
      return (temp == nullptr ? node : temp);
    }
  }

  //Вспомогательная функция
  Node *cutMin(Node *node) {
    if (node == nullptr) {
      return node;
    }
    if (node->left_ == nullptr) {
      return node->right_;
    }
    node->left_ = cutMin(node->left_);
    return node;
  }

  //Вспомогательная функция 2
  Node *getMin(Node *node) {
    while (node->left_ != nullptr) {
      node = node->left_;
    }
    return node;
  }

  //Удаление элемента из дерева, не нарушающее порядка элементов
  Node *remove(Node *node, const T &key) {
    if (node == nullptr) {
      return node;
    }
    if (key < node->key_) {
      node->left_ = remove(node->left_, key);
    } else if (key > node->key_) {
      node->right_ = remove(node->right_, key);
    } else {
      Node *left = node->left_;
      Node *right = node->right_;
      delete node;
      if (left == nullptr) {
        return remove(right, key);
      } else if (right == nullptr) {
        return left;
      }
      Node *temp = getMin(right);
      right = cutMin(right);
      temp->left_ = left;
      temp->right_ = remove(right, key);
      return temp;
    }
    return node;
  }

};
// конец шаблона класса TreeBinarySearchTree

