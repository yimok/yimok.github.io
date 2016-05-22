#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector를 쓰기위한 라이브러리
#include <math.h> //log,floor 사용
#include <time.h> //clock()
#include <Windows.h>
using std::vector;

#pragma warning(disable:4996)
#define SIZE 100 //행렬 사이즈

//vi - vj 값과 가중치 저장 구조체
typedef struct edge
{
	int i;    // vi
	int j;    // vj
	int cost;
}edge;

// 가중치를 임시로 저장할 구조체
typedef struct distance
{
	int start;
	int length;

}Distance;


//qsort 비교를 위한 함수
int compare(const void * x, const void * y)
{
	return (*(edge *)x).cost - (*(edge *)y).cost;
}

//그래프 W에서 정점들간의 가중치만을 뽑아오기 위한 함수
void EdgeInit(edge E[], vector< vector<int> > &W)
{
	int count=0;
	for (int i = 1; i < W.size(); i++)
	{
		for (int j = i; j < W.size(); j++)
		{
			if (i != j)
			{
				E[count].cost = W[i][j];
				E[count].i = i;
				E[count].j = j;
				count++;
			}
		}


	}

}

//서로소 집합들을 저장하기위한 배열공간을 초기화
void initial(vector<int>  &Prime)
{
	int i = 0;
	for (i = 0; i < (int)Prime.size(); i++)
	{
		Prime[i] = i;
	}

}

//가중치에 따른 시작정점i를 서로소 집합에서 찾는다.
int find(int i, vector<int>  &Prime)    
{
	int j;
	j = i;
	while (Prime[j] != j)
		j = Prime[j];
	return j;
}


//find 함수로 얻은 p,q 값을 사용하여 비교를 하고 이 함수를 실행하여
//Prime 배열에 합친다.
void merge(int p, int q, vector<int>  &Prime)   
{
	if (p < q)     
		Prime[q] = p;  
	else
		Prime[p] = q;
}

// kruskal 알고리즘
// parameter : 2차원 배열 vector, edge 구조체 변수 E, edge 구조체 변수 F, E 
// return : 없음
void kruskal(vector< vector<int> > &W, edge E[], edge F[] ,int Esize)
{
	int i, j, count = 0, num = 0;
	int p, q; // 서로소 체크
	double start, end; // 시간측정
	edge e;
	vector<int>  Prime((int)W.size(),0);

	//qsort 인자, 정렬할 배열 시작주소, 배열 요소의 갯수, 배열 요소 하나의 크기, 비교함수
	//edge의 cost에 따라 오름차순으로 정렬한다
	qsort(E, Esize, sizeof(edge), compare);
	initial(Prime);  //서로소 집합 초기화
	
	//정점 n일떄 n-1 개가 될 때 까지 반복문을 돌리지만
	//배열인덱스 1부터시작하므로 -2를 함
	while (count < W.size() - 2)  
	{
		

		e = E[num];
		i = E[num].i;
		j = E[num].j;

		p = find(i, Prime);
		q = find(j, Prime);
		
		if (p != q)
		{
			merge(p, q, Prime);
			F[count] = e;
			count++;

		}

		num++;
	}

}


// Prim 알고리즘
// parameter : 2차원 배열 vector, edge 구조체 변수 F 
// return : 없음
void prim(vector< vector<int> > &W, edge F[])
{
	int i, vnear;
	int min;
	edge e;
	//int* nearest = new int[(int)W.size()];  
	vector<int>  nearest((int)W.size(), 0);
	Distance* distance = new Distance[(int)W.size()];
	for (i = 2; i < (int)W.size(); i++)
	{
		nearest[i] = 1;                 // 첫 정점 v1으로 우선 초기화
		distance[i].length = W[1][i];   // v1에서 vi 을 연결하는 이음선의 가중치로 초기화
		distance[i].start = 1;          // 초기 v1부터 시작하므로 1로 초기화 즉 집합Y = {v1}
	}


	//정점의 수만큼 for문을 돌린다.
	for (int i = 2; i < (int)W.size(); i++)
	{
		
		min = 1000;             

		for (int j = 2; j < (int)W.size(); j++)
		{
			//만약 가중치가 0이상이고, min 보다 작다면
			//그 가중치가 최소이므로 min에 다시 저장한다.
			//반복문을 통해 가장 가까이있는 정점을 찾는다.
			if (distance[j].length >= 0 && distance[j].length < min)
			{ 
				min = distance[j].length;  // 가중치를 min에 저장한다.
				vnear = j;                 // 정점을 저장
			}
		}

		F[i - 2].i = distance[vnear].start;    // 시작 정점 저장
		F[i - 2].j = vnear;                    // 가장 가까운 정점 저장
		F[i - 2].cost = min;                   // 가중치 저장	

		distance[vnear].length = -1;

		for (int j = 2; j < (int)W.size(); j++)
		{

			// 위에서 저장했던 집합 Y에 
			// 속하지 않은 정점들에서 vnear 까지의 가중치와 
			// 저장된 최소 가중치와 비교한다.
			if (W[j][vnear] < distance[j].length)
			{  
				//만약 그 가중치가 더 작을경우 
				// Y로 부터의 거리(distance[i])를 다시 갱신한다.
				distance[j].length = W[j][vnear];  
				distance[j].start = vnear;          
				nearest[j] = vnear;
			}
		}

	}
}




// 바이너리 파일을 읽어와 벡터 2차원 배열에 저장시키는 함수.
// parameter : 읽은 값을 저장시킬 vector 주소 , 파일명, , 행사이즈, 열사이즈 
// return : 없음
void MatrixInit(vector< vector<int> > &matrix, char * fname, int Row, int Col)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	char * arr = new char[Row*Col * 3];
	int idx = 2;
	int j = 1;

	if (fin == NULL)
	{
		printf("파일명이 없습니다.\n");
		return;
	}

	if (fread(arr, Row*Col * 3, 1, fin) != 1)
	{
		printf("에러");
		exit(1);
	}

	int count = 0;


	//바이너리 파일을 읽어온 데이터가 배열의 행, 열, 가중치 순으로 총 3만개의 데이터 
	//즉 100x100 배열로 표현할 수 있는 데이터가 존재
	for (int i = 0; i <= Row*Col * 3 - 1; i = i + 3)
	{

		//fread로 arr에 읽어온 데이터들중 첫번째를 행, 두번째를 열, 그리고 3번째는 가중치이므로 
		//matrix[arr[i]][arr[j]] = arr[idx]; 와 같이 배열에 저장시킨다.
		//배열의 0번째 인덱스는 사용하지 않으므로 +1을 했음
		matrix[arr[i]+1][arr[j]+1] = arr[idx];
		j = j + 3;
		idx = idx + 3;
	}
	fclose(fin);

}

// 최소비용 신장트리 값을 파일로 출력해주는 함수
// parameter : 구조체 배열변수 F, 파일명, 크기 
// return : 없음
void MatrixOut(edge F[], char * fname, int size)
{
	FILE *fout;

	fout = fopen(fname, "wt");
	
	for (int i = 0; i < size-1; i++)  //정점의 수에서 -1 을 해야함
	{
			fprintf(fout, "%2d (%3d - %3d  : %3d )",i+1, F[i].i , F[i].j , F[i].cost);
			fprintf(fout, "\n");
	
	}

}
int main()
{

	char fname1[50], fname2[50];

	//시간측정을 위한 변수
	LARGE_INTEGER timecheck1, timecheck2, timecheck3, timecheck4;
	LARGE_INTEGER start, end;
	double time1, time2, time3, time4;
	

	// ex) vector<vector<int> >  arr(6, vector<int>(5, 0));
	// 설명: vector< vector<int> > 형 벡터 6개(가로 6줄)를 할당 한다는 뜻
	//       vector<int>(5,0) 은 모든 가로줄은 5개짜리 0으로 초기화 된 익명의 int 형 벡터 배열을 생성해 초기값을 넣는다.
	
	
	vector < vector<int> > W1(SIZE + 1, vector<int>(SIZE + 1, 0)); // W1[SIZE][SIZE] 인 동적 배열
	vector < vector<int> > W2(SIZE + 1, vector<int>(SIZE + 1, 0));

	// E 배열 사이즈 구하기 => 상삼각행렬 
	int Esize = ( (W1.size()-1 ) * (W1.size()-1 )) / 2 - (W1.size()-1)/2;   
	edge *F1 = new edge[W1.size() -1];       //prim 알고리즘 
	edge *F2 = new edge[W2.size() - 1];      //prim 알고리즘  
	edge *F3 = new edge[W1.size() - 1];      //kruskal 알고리즘
	edge *F4 = new edge[W2.size() - 1];      //kruskal 알고리즘
	edge *E1 = new edge[Esize]; // kruskal 알고리즘 모든 이음선 저장
	edge *E2 = new edge[Esize]; // kruskal 알고리즘 모든 이음선 저장                                                                    
	

	printf("Prim 알고리즘과 , Kruskal 알고리즘을 사용하여  최소비용 신장트리를 구합니다.)\n");
	printf("인접리스트로 표현된 그래프를 입력하세요(입력순서: denseUdiT.txt -> 엔터 -> sparseUdiT.txt -> 엔터) \n");
	scanf("%s %s", fname1,fname2);
	MatrixInit(W1, fname1 , SIZE, SIZE);
	MatrixInit(W2, fname2, SIZE, SIZE);

	printf("알고리즘 계산중 ...\n\n\n");
	

	//시간측정함수, Prim 알고리즘 수행
	QueryPerformanceFrequency(&timecheck1);
	QueryPerformanceCounter(&start);
	prim(W1, F1);
	QueryPerformanceCounter(&end);
	time1 = (double(end.QuadPart - start.QuadPart) / timecheck1.QuadPart);
	
	//시간측정함수, Prim 알고리즘 수행
	QueryPerformanceFrequency(&timecheck2);
	QueryPerformanceCounter(&start);
	prim(W2, F2);
	QueryPerformanceCounter(&end);
	time2 = (double(end.QuadPart - start.QuadPart) / timecheck2.QuadPart);

	//시간측정함수, Kruskal 알고리즘 수행
	
	EdgeInit(E1, W1);
	QueryPerformanceFrequency(&timecheck3);
	QueryPerformanceCounter(&start);
	kruskal(W1, E1, F3, Esize);
	QueryPerformanceCounter(&end);
	time3 = (double(end.QuadPart - start.QuadPart) / timecheck3.QuadPart);


	//시간측정함수, Kruskal 알고리즘 수행

	EdgeInit(E2, W2);
	QueryPerformanceFrequency(&timecheck4);
	QueryPerformanceCounter(&start);
	kruskal(W2, E2, F4, Esize);
	QueryPerformanceCounter(&end);
	time4 = (double(end.QuadPart - start.QuadPart) / timecheck4.QuadPart);


	//결과출력, 시간출력
	printf(" prim %s \t    prim %s\t     kruskal %s \t  kruskal %s  \n",fname1,fname2,fname1,fname2);
	for (int i = 0; i < (int)W1.size() - 2 ; i++)
	{
		printf("%2d (%3d - %3d  : %3d )\t ", i + 1, F1[i].i, F1[i].j, F1[i].cost);
		printf("%2d (%3d - %3d  : %3d )\t    ", i + 1, F2[i].i, F2[i].j, F2[i].cost);
		printf("%2d (%3d - %3d  : %3d )\t  ", i + 1, F3[i].i, F3[i].j, F3[i].cost);
		printf("%2d (%3d - %3d  : %3d )\t ", i + 1, F4[i].i, F4[i].j, F4[i].cost);
		printf("\n");
	}
	printf("Time : %f ns \t Time : %f ns  \t    Time : %f ns  \t   Time : %f ns  \n\n",time1,time2,time3,time4);
	



	//파일로 저장
	MatrixOut(F1, "prim result(dense).txt", W1.size() - 1);
	MatrixOut(F2, "prim result(sparse).txt", W2.size() - 1);
	MatrixOut(F3, "kruskal result(dense).txt", W1.size() - 1);
	MatrixOut(F4, "kruskal result(sprase).txt", W2.size() - 1);
	
	



	// 책에있는 신장트리 구하기 ////
	vector<vector<int> > W3({
		vector<int>({ 0, 0, 0, 0, 0, 0 }),
		vector<int>({ 0, 0, 1, 3, 101, 101 }),
		vector<int>({ 0, 1, 0, 3, 6, 101 }),
		vector<int>({ 0, 3, 3, 0, 4, 2 }),
		vector<int>({ 0, 101, 6, 4, 0, 5 }),
		vector<int>({ 0, 101, 101, 2, 5, 0 })
	});

	// E 배열 사이즈 구하기 => 상삼각행렬
	int Esize2 = ((W3.size() - 1) * (W3.size() - 1)) / 2 - (W3.size() - 1) / 2;    
	edge *E3 = new edge[Esize];             // kruskal 알고리즘 모든 이음선 저장  
	edge *F5 = new edge[W1.size() - 1];     //prim 알고리즘
	edge *F6 = new edge[W2.size() - 1];     //kruskal 알고리즘

	prim(W3, F5);
	EdgeInit(E3, W3);
	kruskal(W3, E3, F6, Esize2);

	MatrixOut(F5, "prime result(book).txt", W3.size() - 1);
	MatrixOut(F6, "kruskal result(book).txt", W3.size() - 1);
	
	return 0;
	

}