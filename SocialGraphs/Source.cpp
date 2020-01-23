#include <stdio.h>
#include <stdlib.h>

/*
*	ABDULLAH GULCUR - 150116014 -
*	THIS PROGRAM FINDS INFLUENCER PEOPLE ON SOCIAL GRAPH
*	THERE ARE DIFFERENT KIND OF METHODS TO FIND THAT PERSON
*	DEGREE, CLOSENESS, BETWEENNESS CENTRALITY
*
*	THIS PROGRAM ALSO PRINTS THE ALL SHORTEST PATHS IN GRAPH
*	IN ORDER TO FIND ALL OF PATHS YOU NEED TO MODIFY ------
*
*	/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
*	// WRITTEN AND COMPILED IN VISUAL STUDIO 2015 COMMUNITY VERSION //
*	/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
*/

/*
*I used person struct to hold all information
*/
struct Person
{
	char name[30];
	int id;
	int degree;
	float degreeCentrality;
	float closeness;
	float closenessCentrality;
	float betweenness;
	float betweennessCentrality;
};
typedef struct Person Person;

/*
* Que is gonna be used for BFS algorithm
*/
struct queue {
	int items[100];
	int front;
	int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

/*
* node represents node in adjacency list 
*/
struct node
{
	int vertex;
	struct node* next;
};
typedef struct node node;

struct node* createNode(int);

struct Graph
{
	int * path;
	int numVertices;
	struct node** adjLists;
	int * visited;
};
typedef struct Graph Graph;

struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void bfs(struct Graph* graph, int startVertex, int dest, int countsForIntermediate[], int countsIfExist[], Person p[]);
void printPath(struct Graph* graph, int index, int countsForIntermediate[], int countsIfExist[], Person p[]);
void printGraph(struct Graph* graph);
void setDegreeCentrality(Graph* graph, Person p[]);
void printDegreeCentrality(Graph* graph, Person p[]);
void setClosenessCentrality(int dist[], int n, int src, Person p[]);
void printClosenessCentrality(Graph * graph, Person p[]);
void bfs1(Graph* graph, int startVertex, Person p[]);
void fn(struct Graph* graph, int currentNode, int index, int dest, int dist[], int countsForIntermediate[], int countsIfExist[], Person p[]);
void setPath(Graph* graph, Person p[]);
void printAdjacencyMatrix(Graph* graph, Person p[]);
int isFriend(node * pCrawl, int x);
void setBetweennessCentrality(Graph* graph, Person p[], int countsForIntermediate[], int countsIfExist[]);
void printBetweennessCentrality(Graph* graph, Person p[]);

int main()
{

	/*
	*Sets person structs
	*/
	Person p[10];

	p[0].id = 0;
	strcpy(p[0].name, "Cem"); 
	p[1].id = 1;
	strcpy(p[1].name, "Ayse");
	p[2].id = 2;
	strcpy(p[2].name, "Belma");
	p[3].id = 3;
	strcpy(p[3].name, "Edip");
	p[4].id = 4;
	strcpy(p[4].name, "Dundar");
	p[5].id = 5;
	strcpy(p[5].name, "Gamze");
	p[6].id = 6;
	strcpy(p[6].name, "Ferit");
	p[7].id = 7;
	strcpy(p[7].name, "Halit");
	p[8].id = 8;
	strcpy(p[8].name, "Ilke");
	p[9].id = 9;
	strcpy(p[9].name, "Jale");

	Graph* graph = createGraph(10);
	int V = graph->numVertices;
	
	/*
	* add edges
	*/
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 6);
	addEdge(graph, 0, 4);
	addEdge(graph, 1, 6);
	addEdge(graph, 1, 4);
	addEdge(graph, 1, 2);
	addEdge(graph, 2, 4);
	addEdge(graph, 3, 4);
	addEdge(graph, 3, 2);
	addEdge(graph, 3, 5);
	addEdge(graph, 4, 6);
	addEdge(graph, 4, 5);
	addEdge(graph, 5, 6);
	addEdge(graph, 5, 7);
	addEdge(graph, 6, 7);
	addEdge(graph, 7, 8);
	addEdge(graph, 8, 9);

	printAdjacencyMatrix(graph, p); // prints adjacency matrix

	printf("\n------\n");
	
	setPath(graph, p);  // prints all possible shortest paths
	printf("\n------\n");
	printBetweennessCentrality(graph, p);

	printf("\n------\n");

	for (int i = 0; i < V; i++) { // here is for closeness centrality
		bfs1(graph, i, p);
	}
	printClosenessCentrality(graph, p);
	printf("\n------\n");

	setDegreeCentrality(graph, p);
	printDegreeCentrality(graph, p);
	printf("\n------\n");

	return 0;
}

void setPath(Graph* graph, Person p[]) { // Sets possible shortest pairs

	int V = graph->numVertices;

	printf("Source\t\tTarget\t\tIntermediate Nodes\tPath\n");

	int * countsForIntermediate = (int)malloc(sizeof(int)*V);
	int * countsIfExist = (int)malloc(sizeof(int)*V);

	for (int i = 0; i < V; i++) {
		countsForIntermediate[i] = 0;
		countsIfExist[i] = 0;
	}
		
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++) {
			bfs(graph, i, j, countsForIntermediate, countsIfExist, p);
		}
		printf("\n");
	}
	setBetweennessCentrality(graph, p, countsForIntermediate, countsIfExist);
}

void setBetweennessCentrality(Graph* graph, Person p[], int countsForIntermediate[], int countsIfExist[]) {

	int V = graph->numVertices;
	int n = (V - 1) * (V - 2) / 2;

	for (int i = 0; i < V; i++) {
		p[i].betweenness = (float)countsForIntermediate[i] / countsIfExist[i];
		p[i].betweennessCentrality = p[i].betweenness / n;
	}
}

void printBetweennessCentrality(Graph* graph, Person p[]) {

	int count = 0;
	int V = graph->numVertices;

	printf("Betweenness Centrality\n");
	printf("Node\tScore\tStandardized Score\n");

	for (int i = 0; i < V; i++)
	{
		node * pCrawl = graph->adjLists[i];
		printf("%s\t", p[i].name);
		printf("%.4f\t%.4f", p[i].betweenness, p[i].betweennessCentrality);
		printf("\n");
	}
}

void setDegreeCentrality(Graph* graph, Person p[])
{
	int count = 0;
	int v;
	for (v = 0; v < graph->numVertices; ++v)
	{
		node * pCrawl = graph->adjLists[v];
		while (pCrawl)
		{
			count++;
			pCrawl = pCrawl->next;
		}
		p[v].degree = count;
		p[v].degreeCentrality = (float)count / (graph->numVertices - 1);
		count = 0;
	}
}

void printDegreeCentrality(Graph* graph, Person p[])
{
	int count = 0;
	int v;

	printf("Degree Centrality\n");
	printf("Node\tScore\tStandardized Score\n");

	for (v = 0; v < graph->numVertices; ++v)
	{
		node * pCrawl = graph->adjLists[v];
		printf("%s\t", p[v].name);
		printf("%d\t%.4f", p[v].degree, p[v].degreeCentrality);
		printf("\n");
	}
}

void setClosenessCentrality(int dist[], int n, int src, Person p[])
{
	int sum = 0;

	for (int i = 0; i < n; ++i)
		sum += dist[i];

	p[src].closenessCentrality = (float)1 / sum * (n-1);
	p[src].closeness = (float)1 / sum;
}

void printClosenessCentrality(Graph * graph, Person p[]) {

	int v;

	printf("Closeness Centrality\n");
	printf("Node\tScore\tStandardized Score\n");

	for (v = 0; v < graph->numVertices; ++v)
	{
		node * pCrawl = graph->adjLists[v];
		printf("%s\t", p[v].name);
		printf("%.4f\t%.4f", p[v].closeness, p[v].closenessCentrality);
		printf("\n");
	}
}

void printPath(Graph* graph, int index, int countsForIntermediate[], int countsIfExist[], Person p[]) {  // prints all shortest paths

	int count = 0;

	for (int i = 0; i <= index; i++) {
		if (i == 0) 
			printf("%s\t\t", p[graph->path[0]].name); // sorce
		else if (i == index) 
			printf("%s\t\t", p[graph->path[i]].name); // target

	}
	for (int i = 0; i <= index; i++) { // intermediate nodes
		if (i != 0 && i != index) {
			printf("%s-", p[graph->path[i]].name);
			countsForIntermediate[graph->path[i]]++;
		}
	}
	printf("\t\t\t");
	for (int i = 0; i <= index; i++) {
			printf("%s-", p[graph->path[i]].name);  // prints all shortest paths
			countsIfExist[graph->path[i]]++;
	}
	printf("\n");
}


/*
*This function has specific algorithm to find all possible paths. But in line 308, i modified if statement to find shortest ones.
*/
void fn(Graph* graph, int currentNode, int index, int dest, int dist[], int countsForIntermediate[], int countsIfExist[], Person p[]) {
	
	node * adjListNode = graph->adjLists[currentNode];

	graph->path[index] = currentNode;
	graph->visited[currentNode] = 1;//the most IMP step in graph traversing, otherwise cycle will be formed
	if (currentNode == dest && index <= dist[currentNode]) { 
		printPath(graph, index, countsForIntermediate, countsIfExist, p);
	}
	else {
		while (adjListNode != NULL) {
			int adjNode = adjListNode->vertex;
			if (graph->visited[adjNode] == 0) {
				fn(graph, adjNode, index + 1, dest, dist, countsForIntermediate, countsIfExist, p);
			}
			adjListNode = adjListNode->next;
		}
	}
	graph->visited[currentNode] = 0;
}

void bfs(Graph* graph, int startVertex, int dest, int countsForIntermediate[], int countsIfExist[], Person p[]) { // bfs algorithm to set nodes distances

	int v = graph->numVertices;

	int * dist = (int)malloc(sizeof(int)* v);
	int * parent = (int)malloc(sizeof(int)* v);

	for (int i = 0; i < v; i++) {
		dist[i] = 0;
		parent[startVertex] = -1;
	}
	struct queue* q = createQueue();

	graph->visited[startVertex] = 1;
	enqueue(q, startVertex);

	while (!isEmpty(q)) {
		int currentVertex = dequeue(q);

		node* temp = graph->adjLists[currentVertex];

		while (temp != NULL) {
			int adjVertex = temp->vertex;

			if (graph->visited[adjVertex] == 0) {
				dist[adjVertex] = dist[currentVertex] + 1;
				parent[adjVertex] = currentVertex;
				graph->visited[adjVertex] = 1;
				enqueue(q, adjVertex);
			}
			temp = temp->next;
		}
	}

	for (int i = 0; i < graph->numVertices; i++) {
		graph->visited[i] = 0;
	}

	fn(graph, startVertex, 0, dest, dist, countsForIntermediate, countsIfExist, p);
}

void bfs1(Graph* graph, int startVertex, Person p[]) { // to set closeness centrality distances

	int v = graph->numVertices;

	int * dist = (int)malloc(sizeof(int)* v);

	for (int i = 0; i < v; i++) {
		graph->visited[i] = 0;
	}
	dist[startVertex] = 0;

	struct queue* q = createQueue();

	graph->visited[startVertex] = 1;
	enqueue(q, startVertex);

	while (!isEmpty(q)) {
		int currentVertex = dequeue(q);

		node* temp = graph->adjLists[currentVertex];

		while (temp != NULL) {
			int adjVertex = temp->vertex;

			if (graph->visited[adjVertex] == 0) {
				dist[adjVertex] = dist[currentVertex] + 1;
				graph->visited[adjVertex] = 1;
				enqueue(q, adjVertex);
			}
			temp = temp->next;
		}
	}
	setClosenessCentrality(dist, v, startVertex, p);
}

node* createNode(int v)
{
	node* newNode = malloc(sizeof(node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

Graph* createGraph(int vertices)
{
	Graph* graph = malloc(sizeof(Graph));
	graph->numVertices = vertices;
	graph->path = malloc(vertices * sizeof(node*));
	graph->adjLists = malloc(vertices * sizeof(node*));
	graph->visited = malloc(vertices * sizeof(int));

	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
		graph->path[i] = 0;
	}
	return graph;
}

void printAdjacencyMatrix(Graph* graph, Person p[]) {

	int V = graph->numVertices;

	printf("\t");

	for (int i = 0; i < V; i++) {
		printf("%s\t", p[i].name);
	}

	printf("\n\n");

	for (int i = 0; i < V; i++) {
		printf("%s\t", p[i].name);
		node * pCrawl = graph->adjLists[i];
		for (int j = 0; j < V; j++) {
			if (isFriend(pCrawl, j)) {
				printf("1\t");
			}
			else {
				printf("0\t");
			}
		}
		printf("\n\n", i);
	}
}

int isFriend(node * pCrawl, int x) { // it is used in printAdjacencyMatrix(Graph* graph, Person p[]) method. Checks whether node is friend of specific node

	while (pCrawl != NULL) {

		if (pCrawl->vertex == x) {
			return 1;
		}
		pCrawl = pCrawl->next;
	}
	return 0;
}

void printGraph(Graph* graph)
{
	int v;

	for (v = 0; v < graph->numVertices; ++v)
	{
		node * pCrawl = graph->adjLists[v];
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl)
		{
			printf("-> %d", pCrawl->vertex);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

void addEdge(Graph* graph, int src, int dest)
{
	// Add edge from src to dest
	node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;

	 //Add edge from dest to src
	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
}

struct queue* createQueue() {
	struct queue* q = malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}


int isEmpty(struct queue* q) {
	if (q->rear == -1)
		return 1;
	else
		return 0;
}

void enqueue(struct queue* q, int value) {
	
	if (q->front == -1)
		q->front = 0;
	q->rear++;
	q->items[q->rear] = value;
}

int dequeue(struct queue* q) {
	int item;
	if (isEmpty(q)) {
		item = -1;
	}
	else {
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear) {
			q->front = q->rear = -1;
		}
	}
	return item;
}