## Ternary Search Tree

This project is written in C which aims to write an algorithm that will build a ternary search tree (TST) and makes necessary operations in this tree.

Consider a TST where the only difference with a binary search tree is that
a key that is greater than the current node’s key but less than or equal to the square
of it is located at the middle child of the node. More formally expressed,

Key(LCA) < Key(A) < Key(MCA) ≤ (Key(A))2 < Key(RCA)

where A represents the current node, LCA, MCA and RCA denote the left child, the middle
child and the right child of A, in respective order.

In this project we can find the node with find function and we can remove specific node.

We also need to find a formula that makes the tree has a minimum depth level.
In that situation I developed an artificial intelligence that creates its own formula to keep tree in minimum depth level.
