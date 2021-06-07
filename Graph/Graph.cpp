
//�ο�://ԭ�����ӣ�https ://blog.csdn.net/Africa_South/article/details/88553068
#include "DataDefine.h"

#include <iostream>
#include <queue>
//#include <limits.h>
//#include <cmath>
#define MAX 1024

void showMatrix(MGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++) 
			std::cout << G.arcs[i][j].adj << " ";

		std::cout << std::endl;
	}
}

status LocateVex(MGraph G, VertexType u)
{
	int pos;
	for (pos = 0; pos < G.vexnum && G.vexs[pos] != u; pos++);

	return pos;
}

status CreateDG(MGraph& G)
{
	return OK;
}

status CreateDN(MGraph& G)
{
	return OK;
}

status CreateUDG(MGraph& G)
{
	//����ͼ
	int IncInfo; //IncInfoΪ0��ʾ�����߲��洢��Ϣ
	std::cin >> G.vexnum >> G.arcnum >> IncInfo;
	int i, j;
	for (i = 0; i < G.vexnum; i++) 
		std::cin >> G.vexs[i]; //����������������
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) 
			G.arcs[i][j] = { MAX,NULL };
		//��ʼ���ڽӾ���һ���ǳ�ʼ��Ϊ0��
		//������������ǰ��UDNһ����Ϊ��ͨ��һЩ���Һ���
	}
	// �����ڽӵĵ��������ڽӱ�
	for (i = 0; i < G.arcnum; i++) {
		VertexType v1, v2;
		std::cin >> v1 >> v2;
		int index1 = LocateVex(G, v1);
		int index2 = LocateVex(G, v2);
		G.arcs[index1][index2].adj = 1; // 1��ʾ�ڽ�
		if (IncInfo) std::cin >> *G.arcs[index1][index2].info;
		G.arcs[index2][index1] = G.arcs[index1][index2];  // ����ͼ�Գƹ���
	}
	return OK;
}

status CreateUDN(MGraph& G)
{
	//�������������Ȩͼ��
	int IncInfo;//IncInfo=0,�򻡲�������Ϣ
	std::cout << ("please input graph vertexNum ArcNum IncInfo=0 \n");
	std::cin >> G.vexnum >> G.arcnum >> IncInfo;
	//printf("please input graph vertexNum ArcNum IncInfo=0 \n");
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >> G.vexs[i];//���춥������
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; ++j) {
			//init graph
			G.arcs[i][j] = { MAX,NULL };
		}
	}

	for (int k = 0; k < G.arcnum; k++) {
		VertexType v1, v2; VRType w;

		std::cin >> v1 >> v2 >> w;

		int i = LocateVex(G, v1); int j = LocateVex(G, v2);
		std::cout << "index i=" << i << "," << "j=" << j << std::endl;
		G.arcs[i][j].adj = w;
		if (IncInfo) {
			std::cin >> *G.arcs[i][j].info;
		}
		G.arcs[j][i] = G.arcs[i][j];
		std::cout << "G.arcs[" << i << "][" << j << "]" << "," << G.arcs[i][j].adj << std::endl;
	}
	return OK;
}

status CreateGraph(MGraph& G)
{
	//��������(�ڽӾ���)��ʾ��
	G.kind = UDN;
	switch (G.kind)
	{
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);//����ͼ
	case UDN:return CreateUDN(G);//�������������Ȩͼ��
	default:return ERROR;

	}
}

//����ͼG��U�ĵ�һ���ٽӽڵ�
status FirstAdjVex(MGraph G, VertexType v)
{
	int index = LocateVex(G, v);
	int i = 0;
	while (i < G.vexnum)
	{
		if (G.arcs[index][i].adj != MAX)
			break;
		i++;
	}
	if (i == G.vexnum) return -1;

	return i;
}

// ����G�ж���v�����u����һ�ڽӵ�
int NextAdjVex(MGraph G, VertexType v, VertexType u) {
	int indexV = LocateVex(G, v);
	int indexU = LocateVex(G, u);
	int index;
	for (index = indexU + 1; index < G.vexnum && G.arcs[indexV][index].adj == MAX; index++);
	if (index == G.vexnum) return -1;
	else return index;
}

VertexType GetVex(MGraph G, VertexType V)
{
	return 0;
}

void PutVex(MGraph& G, VertexType V)
{
}

void InsertVex(MGraph& G, VertexType v) 
{
}

void DeleteVex(MGraph& G, VertexType V)
{
}

void InsertArc(MGraph& G, VertexType v, VRType w)
{
}

void DeleteArc(MGraph& G, VertexType v, VRType w)
{
}

// ��ͼ�е�v�����㿪ʼ����������ȱ���
void DFS(MGraph G, int v, int* visited) {
	visited[v] = 1; //�ȷ��ʶ���v
	std::cout << G.vexs[v] << " ";
	for (int w = FirstAdjVex(G, G.vexs[v]); w >= 0; w = NextAdjVex(G, G.vexs[v], G.vexs[w])) {
		if (!visited[w])
			DFS(G, w, visited); // ��v����δ���ʵ��ڽӶ���w�ݹ����DFS
	}
}

// ͼ��������ȱ���
void DFSTraverse(MGraph G) {
	int* visited = new int[G.vexnum]; // ���ʱ�־����
	for (int i = 0; i < G.vexnum; i++) visited[i] = 0; // ��ʼ��δ������
	for (int i = 0; i < G.vexnum; i++) {
		if (!visited[i])
			DFS(G, i, visited); // ����δ���ʵĶ���i����DFS��
											 // ��ΪͼG���ܲ�����ͨͼ
	}
}


void BFSTraverse(MGraph G) {
	// ���չ�����ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited��
	int* visited = new int[G.vexnum];
	std::queue<int> Q;
	int i;
	for (i = 0; i < G.vexnum; i++) visited[i] = 0;

	for (i = 0; i < G.vexnum; i++) {
		if (!visited[i]) { //���ʶ���i
			visited[i] = 1;
			std::cout << G.vexs[i] << " ";
			Q.push(i);
			while (!Q.empty()) {
				int u = Q.front();
				Q.pop(); //ȡ����ͷ����
				for (int w = FirstAdjVex(G, G.vexs[u]); w >= 0; w = NextAdjVex(G, G.vexs[u], G.vexs[w])) {
					if (!visited[w]) {  // wΪu����δ���ʵ��ڽӶ���
						visited[w] = 1;
						std::cout << G.vexs[w] << " ";
						Q.push(w);
					}
				}
			}
		}
	}
}

//����ķ�㷨
struct {
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

int minmum(MGraph G) 
{

	int min = MAX;
	int index = -1;
	for (int i = 0; i < G.vexnum; ++i) {
		//��Сֵ���� �ñߵ�Ȩֵ �� �ñߵ�Ȩֵ��Ϊ 0
		if (min > closedge[i].lowcost && closedge[i].lowcost != 0) {
			min = closedge[i].lowcost;
			index = i;
		}
	}
	return index;
}


//˼�룺��̰���㷨�� ʱ�临�Ӷȣ�O(n*n)
//ʹ�ø�������closedge{���㣬Ȩֵ}
//�ӵ�ǰ�ڵ�д�뵽�����������Ϣ���Ѿ����ʹ���lowcost = 0;
//���ϵ���õ�ǰ������һ���ڵ����С��

void MiniSpanTree_PRIM(MGraph G, VertexType u) 
{
	//�鱾P174���
	int k = LocateVex(G, u);//�ö���λ��      k=0

	for (int j = 0; j < G.vexnum; ++j)//���������ʼ��
		if (j != k)//�൱��u���� �ߵ���Ϣ
			closedge[j] = { u,G.arcs[k][j].adj };//{adjvex,lowcost}

	closedge[k].lowcost = 0;//��ʼ��U={u}����u���뼯��

	for (int i = 1; i < G.vexnum; ++i) 
	{//ѡ������G.vexnum-1������
		k = minmum(G);    //���T����һ����㣬��k����
		printf("%c-->%c\n", closedge[k].adjvex, G.vexs[k]);//��� ��������
		closedge[k].lowcost = 0;//��k���㲢��U��

		for (int j = 0; j < G.vexnum; ++j)
			if (G.arcs[k][j].adj < closedge[j].lowcost)
				//�¶��㲢��U������ѡ����С��
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj };
	}
}


//���·�����Ͻ�˹�����㷨
typedef int Patharc[MAX_VERTEX_NUM];//���ڴ洢���·���±������
typedef int ShortPathTable[MAX_VERTEX_NUM];//���ڴ洢���������·����Ȩֵ��

void ShortestPath_DIJ(MGraph G, int V0, Patharc& P, ShortPathTable& D) {
	int v, w, min, k = NULL;
	int final[MAX_VERTEX_NUM];  //final[w]=1 ��ʾ�Ѿ���ö���V0��Vw�����·��

	//��ʼ������
	for (v = 0; v < G.vexnum; v++) {
		final[v] = 0;             //ȫ�������ʼ��Ϊδ�ҵ����·��
		D[v] = G.arcs[V0][v].adj; //����V0�������ߵĶ������Ȩֵ
		P[v] = 0;                 //��ʼ��·������PΪ0
	}

	D[V0] = 0;    //V0��V0·��Ϊ0
	final[V0] = 1;//V0��V0����Ҫ��·��

	//��ʼ��ѭ����ÿ�����V0��ĳ��v��������·��
	for (v = 1; v < G.vexnum; v++) {
		min = MAX;
		//ѭ����õ�һ����֪���·���Ķ��㣬��Ϊ��ɢ�����Ķ���
		for (w = 0; w < G.vexnum; w++)
			if (!final[w] && D[w] < min) {
				k = w;
				min = D[w];
			}
		final[k] = 1; //��Ŀǰ�ҵ�������Ķ�����1
		//������ǰ���·�� ������
		//�Ӹö��㷢ɢ��ȥ�ĸ��������������
		for (w = 0; w < G.vexnum; w++)
			//�������v�����·������������·���ĳ��ȶ̵Ļ�������
			if (!final[w] && (min + G.arcs[k][w].adj < D[w])) {
				D[w] = min + G.arcs[k][w].adj;//�޸ĵ�ǰ·������
				P[w] = k;     //���ǰ������
			}

	}
}


//���·�������������㷨
//���ʾ��Ƕ�̬�滮
//ʱ�临�Ӷ� n*n*n
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void ShortestPath_FLOYD(MGraph G, PathMatrix& P, DistancMatrix& D) 
{
	int v, w, k;
	//��ʼ��D��P
	for (v = 0; v < G.vexnum; v++)
		for (w = 0; w < G.vexnum; w++)
		{
			D[v][w] = G.arcs[v][w].adj;
			P[v][w] = -1;
		}

	//�㷨����
	for (k = 0; k < G.vexnum; k++)
		for (v = 0; v < G.vexnum; v++)
			for (w = 0; w < G.vexnum; w++)
				if (D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k];
				}
}



int main()
{
	/*������
		6 10 0
		A B C D E F
		A B 5
		A C 8
		A D 7
		A F 3
		B C 4
		C D 5
		C F 9
		D E 5
		D F 6
		E F 1

		����ͼ
		8 9 0
		V1 V2 V3 V4 V5 V6 V7 V8
		V1 V2
		V1 V3
		V2 V4
		V2 V5
		V3 V6
		V3 V7
		V4 V8
		V5 V8
		V6 V7

		8 9 0
		A B C D E F G H
		A B
		A C
		A D
		B D
		B E
		C F
		C G
		D H
		E H
		F G
		
		*/


	MGraph graph;
	CreateGraph(graph);
	showMatrix(graph);
	std::cout << "\nBFS��\n";
	BFSTraverse(graph);
	std::cout << "\nDFS��"<<std::endl;
	DFSTraverse(graph);
	std::cout << std::endl;
	std::cout << "prim��" << std::endl;
	MiniSpanTree_PRIM(graph, 'A');

	Patharc p; ShortPathTable dis;
	std::cout << "ShortestPath_DIJ��" << std::endl;
	ShortestPath_DIJ(graph, 0, p, dis);

	for (int i = 0; i < graph.vexnum; i++)
	{
		std::cout << dis[i] <<" "<<std::endl;
	}

	return OK;
}

