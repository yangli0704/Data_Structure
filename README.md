# Data_Structure
This page summarises basic data structure and their implementation in C, Python and Go\
The main data structure that I am going to focus on here are as follow:\
1.Singly Linked List\
2.Doubly Linked List\
3.Binary Search Tree\
4.** AVL Tree\

I quote the definition of the definition of AVL tree from Wikipedia:

In computer science, an AVL tree (named after inventors Adelson-Velsky and Landis) is a self-balancing binary search tree. It was the first such data structure to be invented. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Lookup, insertion, and deletion all take O(log n) time in both the average and worst cases, where n is the number of nodes in the tree prior to the operation. Insertions and deletions may require the tree to be rebalanced by one or more tree rotations.

The AVL tree is named after its two Soviet inventors, Georgy Adelson-Velsky and Evgenii Landis, who published it in their 1962 paper "An algorithm for the organization of information".

There serveal main operation for AVL tree: 1) Insert, 2) Delete, 3) Search, 4) Traversal. From the example in this file, one could find the example I have done in C. Please be aware that AVL tree property may be spoiled after each insert or delete operation so a rebalancing operation needs to be introduced to keep AVL tree property. This is also available in my example. 
