# Text representation with Higher-Order Paths
## Scope
Advantages of using higher-order paths [1] between documents are illustrated in Fig. 1. In
this figure, there are three documents, d1, d2 and d3 which include a set of terms {t1, t2, t3}, {t3,
t4, t5} and {t4, t5} respectively. Using a traditional similarity measure which is based on the
shared terms (e.g. dot product), similarity value between documents d1 and d3 will be zero
since they do not share any terms. But in fact these two documents have some similarities in
the context of the dataset through d2 as it can be seen in Fig. 1. This supports the idea that using higher-order paths between documents, it is possible to obtain a non-zero similarity value between d1 and d3 which was not possible in traditional Bag of Words (BOW) [2]
representation. This value becomes larger if there are many interconnecting documents like d2
between d1 and d3. This may stem from the reason that the two documents are written on the
same topic using two different but semantically closer sets of terms. This project aims to represent these higher-order paths by using Linked-Lists. Consequently, this project is a programming assignment in C, which aims to build an algorithm based on linked-lists that will build an efficient representation of documents.

