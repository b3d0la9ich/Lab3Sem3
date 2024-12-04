#pragma once
#include <string>
#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int value, Node* nextNode = nullptr)
        : data(value), next(nextNode) {}
};