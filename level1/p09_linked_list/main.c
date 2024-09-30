#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node {
    int value;
    struct Node* nextNode;
} Node;
typedef struct MyList {
    Node emptyNode;
} MyList;

MyList* CreateList() {
    MyList* newList = NULL;
    do {
        newList = (MyList*)malloc(sizeof(MyList));
    } while (newList == NULL);
    newList->emptyNode.value = -1;
    newList->emptyNode.nextNode = NULL;
    return newList;
}
void PushMyList(MyList* target, int input) {
    Node* p = NULL;
    do {
        p = (Node*)malloc(sizeof(Node));
    } while (p == NULL);
    p->nextNode = target->emptyNode.nextNode;
    target->emptyNode.nextNode = p;
    p->value = input;
}
void PopMyList(MyList* target) {
    Node* p = target->emptyNode.nextNode;
    target->emptyNode.nextNode = p->nextNode;
    free(p);
}
Node* GetP(MyList* target) {
    return &(target->emptyNode);
}
void CopyList(MyList* source, MyList* target) {
    Node* ps = GetP(source);
    Node* pt = GetP(target);
    while (target->emptyNode.nextNode != NULL) PopMyList(target);
    while (ps->nextNode != NULL) {
        ps = ps->nextNode;
        pt->nextNode = (Node*)malloc(sizeof(Node));
        pt = pt->nextNode;
        pt->value = ps->value;
        pt->nextNode = NULL;
    }
}
void InsertMyList(MyList* target, int input, Node* index) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->nextNode = index->nextNode;
    index->nextNode = p;
    p->value = input;
}

int main() {
    MyList aList = *CreateList();
    MyList bList = *CreateList();
    //随便加入点元素
    for (int i = 0; i < 10; i++)
    {
        PushMyList(&aList, i);
    }
    //for (int i = 0; i < 10; i++)
    //{
    //    PushMyList(&aList, i);
    //}
    //遍历
    Node* p2 = GetP(&bList);
    Node* p1 = GetP(&aList);
    while (p1->nextNode != NULL) {
        p1 = p1->nextNode;
        printf("%d\n", p1->value);
    }
    p1 = GetP(&aList);
    //反序
    p1 = GetP(&aList);
    while (p1->nextNode != NULL) {
        p1 = p1->nextNode;
        PushMyList(&bList, p1->value);
        p1 = GetP(&aList);
        PopMyList(&aList);
    }
    CopyList(&bList, &aList);
    p1 = GetP(&aList);
    while (p1->nextNode != NULL) {
        p1 = p1->nextNode;
        printf("%d\n", p1->value);
    }
    //查找
    p1 = GetP(&aList);
    int index = 0;
    bool isFiveEixst;
    while (p1->nextNode != NULL) {
        p1 = p1->nextNode;
        index++;
        if (p1->value == 5) {
            printf("Index = %d\n", index);
            isFiveEixst = true;
        }
    }
    if (!isFiveEixst) printf("-1");
    p1 = GetP(&aList);

    return 0;
}