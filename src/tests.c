#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif
#include <stdlib.h>

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  initNode    (Node *nodePtr, int value);
Node* createNode  (int value);
void  destroyNode (Node **nodePtrPtr);
void  destroyList (Node **headPtrPtr);
int   addFirst    (Node **headPtrPtr, Node *newNodePtr);
int   addLast     (Node **headPtrPtr, Node *newNodePtr);
Node* detachFirst (Node **headPtrPtr);
Node* detachLast  (Node **headPtrPtr);
Node* detachValue (Node **headPtrPtr, int value);
int   deleteFirst (Node **headPtrPtr);
int   deleteLast  (Node **headPtrPtr);
int   deleteValue (Node **headPtrPtr, int value);
void  destroyList (Node **headPtrPtr);
int   printList   (Node *headPtr);
int   listLength  (Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Use TEST_ASSERT_TRUE_MESSAGE for every assertion.
//  - Do NOT use TEST_ASSERT_EQUAL — it reveals expected values.
//  - Heap tests: use createNode / destroyList.
//  - Stack tests: declare Node variables on the stack.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_initNode_sets_value
//
// Declare a Node on the stack.
// Call initNode with a known value.
// Verify that the value field contains that value.
// ============================================================

void test_initNode_sets_value(void) {
    Node a;

    initNode(&a, 42);
    TEST_ASSERT_TRUE_MESSAGE(a.value == 42, "Error: initNode must set the value field.");
}


// ============================================================
// test_initNode_sets_next_null
//
// Declare a Node on the stack.
// Call initNode.
// Verify that nextPtr is NULL after the call.
// ============================================================

void test_initNode_sets_next_null(void) {
    Node a;

    a.nextPtr = &a;          // start non-NULL so the test proves initNode clears it
    initNode(&a, 7);
    TEST_ASSERT_TRUE_MESSAGE(a.nextPtr == NULL, "Error: initNode must set nextPtr to NULL.");
}


// ============================================================
// test_initNode_null_guard
//
// Call initNode with NULL as the nodePtr.
// Verify the program does not crash.
// ============================================================

void test_initNode_null_guard(void) {
    initNode(NULL, 42);
    TEST_ASSERT_TRUE_MESSAGE(1 == 1,
        "Error: initNode must handle NULL without crashing.");
}


// ============================================================
// test_createNode_not_null
//
// Call createNode with a known value.
// Verify the returned pointer is NOT NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_not_null(void) {
    Node *nodePtr = createNode(5);

    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL, "Error: createNode must return a non-NULL pointer.");

    destroyNode(&nodePtr);
}


// ============================================================
// test_createNode_value
//
// Call createNode with a known value.
// Verify that the value field of the returned node
// contains the correct value.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_value(void) {
    Node *nodePtr = createNode(5);

    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL && nodePtr->value == 5, "Error: createNode must set the value field.");

    destroyNode(&nodePtr);
}


// ============================================================
// test_createNode_next_null
//
// Call createNode.
// Verify that nextPtr of the returned node is NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_next_null(void) {
    Node *nodePtr = createNode(5);

    TEST_ASSERT_TRUE_MESSAGE(nodePtr != NULL && nodePtr->nextPtr == NULL, "Error: createNode must set nextPtr to NULL.");

    destroyNode(&nodePtr);
}


// ============================================================
// test_destroyNode_sets_null
//
// Call createNode to allocate a node.
// Call destroyNode.
// Verify that the pointer is NULL after the call.
// ============================================================

void test_destroyNode_sets_null(void) {
    Node *nodePtr = createNode(5);

    destroyNode(&nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(nodePtr == NULL, "Error: destroyNode must set the pointer to NULL.");
}


// ============================================================
// test_addFirst_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addFirst.
// Verify that headPtr now points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addFirst_empty_list(void) {
    Node *headPtr = NULL;
    Node *nodePtr = createNode(10);

    addFirst(&headPtr, nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == nodePtr, "Error: addFirst on an empty list must make the node the head.");

    destroyList(&headPtr);
}


// ============================================================
// test_addFirst_non_empty
//
// Add two nodes using addFirst.
// Verify that headPtr points to the SECOND node added
// (the most recently added node is at the front).
// Verify the first node is reachable via nextPtr.
// Clean up with destroyList.
// ============================================================

void test_addFirst_non_empty(void) {
    Node *headPtr   = NULL;
    Node *firstPtr  = createNode(10);
    Node *secondPtr = createNode(20);

    addFirst(&headPtr, firstPtr);
    addFirst(&headPtr, secondPtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == secondPtr, "Error: addFirst must put the newest node at the front.");
    TEST_ASSERT_TRUE_MESSAGE(headPtr->nextPtr == firstPtr, "Error: the earlier node must follow the new head.");

    destroyList(&headPtr);
}


// ============================================================
// test_addFirst_null_headptr
//
// Call addFirst with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addFirst_null_headptr(void) {
    Node node;

    initNode(&node, 10);
    TEST_ASSERT_TRUE_MESSAGE(addFirst(NULL, &node) == -1, "Error: addFirst must return -1 when headPtrPtr is NULL.");
}


// ============================================================
// test_addLast_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addLast.
// Verify that headPtr points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addLast_empty_list(void) {
    Node *headPtr = NULL;
    Node *nodePtr = createNode(10);

    addLast(&headPtr, nodePtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == nodePtr, "Error: addLast on an empty list must make the node the head.");

    destroyList(&headPtr);
}


// ============================================================
// test_addLast_non_empty
//
// Add two nodes using addLast.
// Verify that headPtr points to the FIRST node added.
// Verify the second node is reachable via nextPtr.
// Verify the second node's nextPtr is NULL.
// Clean up with destroyList.
// ============================================================

void test_addLast_non_empty(void) {
    Node *headPtr   = NULL;
    Node *firstPtr  = createNode(10);
    Node *secondPtr = createNode(20);

    addLast(&headPtr, firstPtr);
    addLast(&headPtr, secondPtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == firstPtr, "Error: addLast must keep the first node at the head.");
    TEST_ASSERT_TRUE_MESSAGE(headPtr->nextPtr == secondPtr, "Error: addLast must attach the new node after the last one.");
    TEST_ASSERT_TRUE_MESSAGE(secondPtr->nextPtr == NULL, "Error: the new last node's nextPtr must be NULL.");

    destroyList(&headPtr);
}


// ============================================================
// test_addLast_null_guard
//
// Call addLast with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addLast_null_guard(void) {
    Node node;

    initNode(&node, 10);
    TEST_ASSERT_TRUE_MESSAGE(addLast(NULL, &node) == -1, "Error: addLast must return -1 when headPtrPtr is NULL.");
}


// ============================================================
// test_detachFirst_returns_node
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify the returned pointer equals &a.
// ============================================================

void test_detachFirst_returns_node(void) {
    Node a, b;

    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;

    Node *gotPtr = detachFirst(&headPtr);

    TEST_ASSERT_TRUE_MESSAGE(gotPtr == &a, "Error: detachFirst must return the old head node.");
}


// ============================================================
// test_detachFirst_updates_head
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify that headPtr now points to b.
// ============================================================

void test_detachFirst_updates_head(void) {
    Node a, b;

    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;

    detachFirst(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == &b, "Error: detachFirst must move headPtr to the second node.");
}


// ============================================================
// test_detachFirst_empty_list
//
// Call detachFirst on an empty list (headPtr == NULL).
// Verify the function returns NULL without crashing.
// ============================================================

void test_detachFirst_empty_list(void) {
    Node *headPtr = NULL;

    TEST_ASSERT_TRUE_MESSAGE(detachFirst(&headPtr) == NULL, "Error: detachFirst must return NULL for an empty list.");
}


// ============================================================
// test_detachValue_found
//
// Build a stack chain: a(1) -> b(2) -> c(3) -> NULL
// Call detachValue for value 2 (middle node).
// Verify the returned pointer equals &b.
// Verify a->nextPtr now points to c.
// Verify b->nextPtr is NULL after detach.
// ============================================================

void test_detachValue_found(void) {
    Node a, b, c;

    initNode(&a, 1);
    initNode(&b, 2);
    initNode(&c, 3);
    a.nextPtr = &b;
    b.nextPtr = &c;

    Node *headPtr = &a;

    Node *gotPtr = detachValue(&headPtr, 2);

    TEST_ASSERT_TRUE_MESSAGE(gotPtr == &b, "Error: detachValue must return the matching node.");
    TEST_ASSERT_TRUE_MESSAGE(a.nextPtr == &c, "Error: detachValue must reconnect the chain around the node.");
    TEST_ASSERT_TRUE_MESSAGE(b.nextPtr == NULL, "Error: the detached node's nextPtr must be NULL.");
}


// ============================================================
// test_detachValue_head
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for value 1 (head node).
// Verify the returned pointer equals &a.
// Verify headPtr now points to b.
// ============================================================

void test_detachValue_head(void) {
    Node a, b;

    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;

    Node *gotPtr = detachValue(&headPtr, 1);

    TEST_ASSERT_TRUE_MESSAGE(gotPtr == &a, "Error: detachValue must return the head node when it matches.");
    TEST_ASSERT_TRUE_MESSAGE(headPtr == &b, "Error: detaching the head must move headPtr to the next node.");
}


// ============================================================
// test_detachValue_not_found
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for a value that does not exist (e.g. 99).
// Verify the function returns NULL.
// ============================================================

void test_detachValue_not_found(void) {
    Node a, b;

    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;

    Node *headPtr = &a;

    TEST_ASSERT_TRUE_MESSAGE(detachValue(&headPtr, 99) == NULL, "Error: detachValue must return NULL when the value is missing.");
}


// ============================================================
// test_deleteFirst_removes_node
//
// Create two heap nodes and build a list.
// Call deleteFirst.
// Verify the function returns 0.
// Verify headPtr now points to the second node.
// Clean up with destroyList.
// ============================================================

void test_deleteFirst_removes_node(void) {
    Node *headPtr   = NULL;
    Node *secondPtr = createNode(20);

    addLast(&headPtr, createNode(10));
    addLast(&headPtr, secondPtr);

    TEST_ASSERT_TRUE_MESSAGE(deleteFirst(&headPtr) == 0, "Error: deleteFirst must return 0 on success.");
    TEST_ASSERT_TRUE_MESSAGE(headPtr == secondPtr, "Error: deleteFirst must move headPtr to the second node.");

    destroyList(&headPtr);
}


// ============================================================
// test_deleteFirst_empty_list
//
// Call deleteFirst on an empty list.
// Verify the function returns -1 without crashing.
// ============================================================

void test_deleteFirst_empty_list(void) {
    Node *headPtr = NULL;

    TEST_ASSERT_TRUE_MESSAGE(deleteFirst(&headPtr) == -1, "Error: deleteFirst must return -1 for an empty list.");
}


// ============================================================
// test_deleteValue_found
//
// Create three heap nodes: 10 -> 20 -> 30
// Call deleteValue for 20.
// Verify the function returns 0.
// Verify listLength is now 2.
// Verify 20 is no longer in the list.
// Clean up with destroyList.
// ============================================================

void test_deleteValue_found(void) {
    Node *headPtr = NULL;

    addLast(&headPtr, createNode(10));
    addLast(&headPtr, createNode(20));
    addLast(&headPtr, createNode(30));

    TEST_ASSERT_TRUE_MESSAGE(deleteValue(&headPtr, 20) == 0, "Error: deleteValue must return 0 when the value is found.");
    TEST_ASSERT_TRUE_MESSAGE(listLength(headPtr) == 2, "Error: deleteValue must shorten the list by one.");

    int stillThere = 0;

    for (Node *currentPtr = headPtr; currentPtr != NULL; currentPtr = currentPtr->nextPtr)
        if (currentPtr->value == 20)
            stillThere = 1;

    TEST_ASSERT_TRUE_MESSAGE(!stillThere, "Error: the deleted value must no longer be in the list.");

    destroyList(&headPtr);
}


// ============================================================
// test_deleteValue_not_found
//
// Create two heap nodes: 10 -> 20
// Call deleteValue for 99.
// Verify the function returns -1.
// Verify the list is unchanged (length still 2).
// Clean up with destroyList.
// ============================================================

void test_deleteValue_not_found(void) {
    Node *headPtr = NULL;

    addLast(&headPtr, createNode(10));
    addLast(&headPtr, createNode(20));

    TEST_ASSERT_TRUE_MESSAGE(deleteValue(&headPtr, 99) == -1, "Error: deleteValue must return -1 when the value is missing.");
    TEST_ASSERT_TRUE_MESSAGE(listLength(headPtr) == 2, "Error: a failed deleteValue must leave the list unchanged.");

    destroyList(&headPtr);
}


// ============================================================
// test_destroyList_empties_list
//
// Create three heap nodes and build a list.
// Call destroyList.
// Verify headPtr is NULL after the call.
// ============================================================

void test_destroyList_empties_list(void) {
    Node *headPtr = NULL;

    addLast(&headPtr, createNode(10));
    addLast(&headPtr, createNode(20));
    addLast(&headPtr, createNode(30));

    destroyList(&headPtr);
    TEST_ASSERT_TRUE_MESSAGE(headPtr == NULL, "Error: destroyList must leave headPtr NULL.");
}


// ============================================================
// test_listLength_empty
//
// Call listLength with NULL.
// Verify the function returns 0.
// ============================================================

void test_listLength_empty(void) {
    TEST_ASSERT_TRUE_MESSAGE(listLength(NULL) == 0, "Error: listLength must return 0 for an empty list.");
}


// ============================================================
// test_listLength_three
//
// Create three heap nodes and build a list.
// Call listLength.
// Verify the function returns 3.
// Clean up with destroyList.
// ============================================================

void test_listLength_three(void) {
    Node *headPtr = NULL;

    addLast(&headPtr, createNode(10));
    addLast(&headPtr, createNode(20));
    addLast(&headPtr, createNode(30));

    TEST_ASSERT_TRUE_MESSAGE(listLength(headPtr) == 3, "Error: listLength must count every node.");

    destroyList(&headPtr);
}


// ============================================================
// test_printList_empty
//
// Call printList with NULL.
// Verify the function returns -1 without crashing.
// ============================================================

void test_printList_empty(void) {
    TEST_ASSERT_TRUE_MESSAGE(printList(NULL) == -1, "Error: printList must return -1 for an empty list.");
}