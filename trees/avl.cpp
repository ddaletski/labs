#include "avl.h"
#include <iostream>
#include <vector>
#include <fstream>

int main() {
    Avl<int> avl;
    for (int i = 0; i < 100; ++i) {
        int r = rand() % 30;
        avl.insert(r);
    }

    std::ofstream fout("graph.dot");
    avl.gen_dotfile(fout);
    fout.close();

    system("dot graph.dot -Tsvg -o ./graph.svg");
    system("xdg-open ./graph.svg");
    return 0;
}
