// C

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main() {
    int numero = 0;
    
    int dir_de_numero = &numero;
    
    Node* n1 = (Node*)malloc(sizeof(Node));
    Node* n2 = (Node*)malloc(sizeof(Node));
    Node* n3 = (Node*)malloc(sizeof(Node));
    
    n1->data = 1;
    n2->data = 2;
    n3->data = 3;
    
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;
    
    Node* current = n1;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
    
    free(n1);
    free(n2);
    free(n3);
    
    return 0;
}

// JAVA

public class LinkedListExample {
    public static void main(String[] args) {
        Node n1 = new Node(1);
        Node n2 = new Node(2);
        Node n3 = new Node(3);
        
        n1.next = n2;
        n2.next = n3;
        
        Node current = n1;
        while (current != null) {
            System.out.println(current.data);
            current = current.next;
        }
    }
    
    static class Node {
        int data;
        Node next;
        
        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }
}

// GOLANG

package main

import "fmt"

type Node struct {
    data int
        next *Node
}

func main() {
    n1 := &Node{data: 1}
    n2 := &Node{data: 2}
    n3 := &Node{data: 3}
    
    n1.next = n2
        n2.next = n3
        
        current := n1
        for current != nil {
        fmt.Println(current.data)
            current = current.next
    }
}