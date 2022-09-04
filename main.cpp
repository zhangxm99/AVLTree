//
// Created by 张晰铭 on 2022/9/3.
//
#include "avl_tree.h"

int main() {
    avl_tree<int> dataset;
    for (int i = 0; i < 30; i++) {
        dataset.add(i);
    }

    dataset.traverse();


    return 0;
}
