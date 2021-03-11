#include "BinarySearchTree.hpp"

int main() {
  BinarySearchTree<int> tree; // создаем пустое дерево
  tree.insert(15); // добавляем узлы
  tree.insert(3);
  tree.insert(20);

  int keyFound = tree.iterativeSearch(15); // поиск должен быть успешным
  std::cout << "Key:" << 15 <<
            (keyFound ? " found successfully" : " not found") <<
            " in the tree" << '\n';
  std::cout << "count = " << tree.getCount() << '\n';

  tree.deleteKey(3);
  tree.print(std::cout);

  std::cout << "Count is\t" << tree.getCount() << '\n';

  std::cout << "Height is\t" << tree.getHeight() << '\n';

  tree.inorderWalk();

}
