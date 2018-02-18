#include "bst.h"
#include <iostream>
#include <vector>
#include <fstream>

int main() {
    BST<int> tree;
    for (int i = 0; i < 100; ++i) {
        int r = rand() % 30;
        tree.insert(r);
    }

    std::ofstream fout("graph.dot");
    tree.gen_dotfile(fout);
    fout.close();

    system("dot graph.dot -Tsvg -o graph.svg");

#ifdef __unix__
    system("xdg-open ./graph.svg");
#else
    system("start graph.svg");
#endif
    return 0;
}
