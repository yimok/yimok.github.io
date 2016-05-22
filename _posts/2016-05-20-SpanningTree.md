---
layout: post
title: "[알고리즘]kruskal / prim 알고리즘 "
description: "[알고리즘]kruskal / prim 알고리즘" 
modified: 2016-05-20
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

최소비용 신장트리를 구하는 알고리즘 kruskal 알고리즘과 prim 알고리즘을 구현해 보자
 


<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->



## 탐욕적인 방법

### 설명

- Prim 알고리즘과 Kruskal 알고리즘은 탐욕적인 방법을 이용하는데,  탐욕적인 방법이란 과거나 미래를 생각하지 않고 현재에 가장 최적이라고 생각되는 결과만을 받아서 최종적으로 최적의 결과를 얻는다. 종합된 결과가 최적의 결과라는 것은 증명으로 판단한다.

## Prim algorithm

### 분석/풀이


- Prim 알고리즘 이란? 가중치가 있는 무방향 그래프의 모든 노드를 포함하면서 각 가중치의 합이 최소가 되는 부분 그래프인 트리, 즉 최소비용 신장트리를 구하는 알고리즘 이다. 
- 아래 그림은 prim 알고리즘을 사용하여 정점 0에서 시작하여 최소비용 신장트리를 구하는 과정이다.

<figure>
	<img src="/images/prim.png" alt="">
</figure>
- [사진 출처](http://cbb1225.tistory.com/entry/%EC%B5%9C%EC%86%8C-%EC%8B%A0%EC%9E%A5-%ED%8A%B8%EB%A6%ACMinimum-Cost-Spanning-Trees)

- 시작정점부터 출발하여 신장트리를 조금씩 확장해 나가는 방법으로 맨 처음 시작정점만이 신장 트리 집합에 포함되고 이렇게 만들어진 신장트리에 가장 인접한 정점들 중 최소 비용의 이음선을 찾아 연결된 정점을 다시 넣어 신장트리를 확장한다.
- 즉 시작정점을 집합 Y에 넣고 나머지 정점들이 있는 집합 V와 가중치를 각각 비교하여 즉 V-Y 사이의 가중치중 최소가 되는 이음선을 찾고 F에 저장한다. 다시 다음 정점을 Y에 넣고 비교하는 식으로 V==Y가 될 때까지 비교하여 최소비용 신장트리를 구현한다.
- 그래프의 배열 W는 아래와 같이 표현 한다.


<figure>
	<img src="/images/prim2.png" alt="">
</figure>

- 아래 2개의 배열로 각 정점의 가중치를 비교하여 인덱스와 가중치를 저장한다.
- nearest[i] = vi에서 가장 가까운 Y에 속한 정점의 인덱스
- distance[i] = vi와 nearest[i]가 인덱스인 두 정점을 연결하는 이음선의 가중치


## Kruskal algorithm

### 분석/풀이
- Kruskal 알고리즘 이란? 가중치가 있는 무방향 그래프의 모든 노드를 포함하면서 각 가중치의 합이 최소가 되는 부분 그래프인 트리, 즉 최소비용 신장트리를 구하는 알고리즘 으로 Prim 알고리즘과 비슷하지만 구현하는 방식이 다르다.
- 우선 무방향 그래프의 모든 이음선을 가중치에 따라 오름차순으로 정렬시킨다. 
- 그리고 가중치가 가장 작은 이음선들을 삽입하는데, 삽입하고 나서 순환 사이클을 형성 한다면 이 이음선은 삽입하지 않고 패스하고 그 다음 가중치가 작은 이음선을 삽입한다.
- 무방향 그래프 정점의 수가 n일 때 n-1개의 이음선을 삽입할때까지 위 과정을 반복하여 최소비용신장트리를 완성시킨다.
<figure>
	<img src="/images/kruskal1.png" alt="">
</figure>

- [그림 출처](http://cbb1225.tistory.com/entry/%EC%B5%9C%EC%86%8C-%EC%8B%A0%EC%9E%A5-%ED%8A%B8%EB%A6%ACMinimum-Cost-Spanning-Trees))



### Kruskal, Prim 알고리즘 구현 소스코드

- [코드 다운로드](https://github.com/yimok/yimok.github.io/tree/master/data/spanningtree)


```cpp

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

```

### 코드 해설

1. minmult 함수 : 인자로 2차원 vector 배열 M, d, P를 입력받는다. 이 함수는 연쇄행렬의 최소곱셈을 구하는 알고리즘이며 2개의 for (diagonal = 1; diagonal <= d.size() - 1; diagonal++) 과 for (i = 1; i < d.size() - diagonal; i++)을 사용하여 상 삼각행렬의 값을 다루도록 구성한다. 즉 행렬상의 정중앙 대각선의 위쪽의 값들을 다룬다. 그리고 for문을 한 개 더 두어 I에서 j까지의 곱의 횟수를 측정하여 최소의 값을 저장한다. temp  = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];  은 k값을 변경해 가면서 곱셈의 횟수를 temp에 저장해놓고 이 temp와 min값을 비교하여서 작을 경우 min에 다시 저장한다. 동시에 이 값이 나온 k도 저장한다. 그리고 for문이 다 돌면 최종적으로 저장된 min 값을 M배열에 적재시키고, 최소 값을 주는 k의 위치를 P배열에 저장시킨다. 
 
2. edge, Distance 구조체 : edge 구조체는 3개의 int형 변수로 구성되어있으며 각각 시작점 I, 끝점 J 그리고 그 이음선의 가중치를 저장한다. / Distance 구조체는 가중치를 저장하는 구조체로 어디서부터 시작하는지와, 길이를 저장한다.

3. Prim 함수 : 인자로 2차원 vector 배열 W, edge 구조체 변수 F를 받는다. 1차원 vector  배열 nearest와 1차원 동적배열 distance를 만들고 그리고 우선 첫 시작정점기준으로  nearest와 distance를 초기화 시켜준다. 그래프 인덱스의 0번은 사용하지 않으므로 반복문을 i=2부터 돌리고 , v1 부터 시작하므로 nearst 배열에 1로 초기화를 한다. 그 후에  distance 배열 구조체의 length를 v1 - vi 을 연결하는 이음선의 가중치로 초기화 한다. start 변수는 v1부터 시작하므로 1로 초기화한다. 

4. 이렇게 초기화가 된 상태에서 다시 for문을 구성하여 만약 가중치가 0이상이고, min 보다 작다면 그 가중치가 최소이므로 min변수에 다시 저장한다. 반복문을 통해 가장 가ᄁᆞ이 있는 정점 즉 비용이 적은 정점을 찾는다. 그렇게 찾은 정점을 인자로 받아온 변수 F에 각각 시작점, 끝점, 비용 순으로  F[i - 2].i = distance[vnear].start;  ,  F[i - 2].j = vnear;  , F[i - 2].cost = min;  저장한다. 그리고 distance[vnear].length = -1;  F에 넣은 정점은 더 이상 볼 필요 없으므로 -1로 초기화한다. 그리고 for문을 한개 더 구성하여 if (W[j][vnear] < distance[j].length) 위에서 저장했던 집합 Y에 속하지 않은 정점들에서 vnear까지의 가중치와 저장된 최소 가중치와 비교한다. 즉 F에 넣은 정점 다음 이음선을 구하는 과정이다. 만약 그 가중치가 더 작을 경우 distance 값들을 갱신하고, nearest 역시 갱신한다. 이 과정을 반복하여 최소비용 신장트리를 구현한다.

5. Compare 함수 : qsort 라이브러리 함수의 4번째 인자로 들어갈 함수이다. edge.cost 의 크기를 비교하여 오름차순으로 정렬한다.

6. EdgeInit 함수 : 인자로 2차원 vector 배열 W, edge 구조체 변수 F를 받는다. 그래프 W에서 정점들 간의 가중치만을 뽑아오는 함수로 대각선을 중심으로 위의 원소들 즉 상삼각행렬들의 값만을 가져와 E 배열에 저장한다. 무방향 그래프 이기때문에 대각선을 중심으로 한쪽만 받으면 된다.  

7. initial 함수 : 인자로 1차원 vector 배열을 받는다. 서로소 집합에 초기값을 저장한다.

8. find 함수 : 인자로 정수형 변수 i, 1차원 vector 배열을 받는다. 작은 가중치 순으로 입력받은 시작정점 i 를 서로소집합 Prime에서 찾아 그 값을 리턴한다. 즉 리턴값은 i가 속한 서로소 집합의 위치이다.

9. merge 함수 : 인자로 정수형 변수 2개와, 1차원 vector 배열을 받는다. kruskal 함수 내부에서 find함수를 사용해 값을 비교하여 서로소라면 이 함수가 실행되며 인자로 받은 Prime 배열에 p, q를 사용해 두 집합을 합친다.

10. kruskal 함수 : 인자로 2차원 vector 배열, edge 구조체 배열 E, F, 정수형 변수 Esize를 받는다. 서로소 집합을 저장하기 위한 vector 배열 Prime을 만들고 initial() 함수를 호출해 초기화한다. 그리고 qsort() 라이브러리 함수를 사용해 받아온 edge 구조체 배열 E를 오름차순으로 정렬 시킨다. 즉 각 정점들간의 가중치 값을 오름차순으로 정렬한다. 그리고 정점의 수가 n일때 n-1개가 될 때 까지 작은 가중치들을 넣으면서 최소비용 신장트리를 만들어야 하므로 반복문을 구성한다. 하지만 배열인덱스를 1부터 시작하였으므로 while (count < W.size() - 2) , 즉 -2를 하였다. edge 구조체 변수 e에 가장 작은 최소 가중치를 넣고 변수 i와 j에 각 시작점, 끝점을 넣고 이 변수들과 서로소 집합 배열을 find() 함수에 넣어서 서로소집합의 위치를 리턴 받고 기 값을 사용하여 서로소인지 판단한 후 합병을 실시하고 최소비용신장트리를 저장하는 F 배열에 값을 저장한다. 최소비용 신장트리가 완성될떄까지  이 과정을 반복한다. 

11. MatrixInit 함수 : 2차원 vector 배열 , 파일명, 행 사이즈, 열사이즈를 받는다 . 바이너리 파일로 읽어온 데이터가 배열의 행, 열, 가중치 순으로 총 3만개의 데이터 즉 100x100 배열로 표현할 수 있는 데이터가 존재하고 이를 arr 동적 1차원 배열에 뽑아 놓고 다시 vector 2차원 배열 marix에 집어넣는다. 이때 0번째 인덱스는 사용하지 않으므로 +1을 하여 값을 넣는다.

12. MatrixOut 함수 : edge 구조체 배열 F, 파일명, 사이즈를 받는다 . F에 저장된 값들을 순서대로 파일로 저장한다.

13. Main 함수 : 그래프를 저장한 vector 2차원 배열과, 이음선, 신장트리 결과를 저장한 구조체 edge 배열 변수를 생성하고 위에서 정의한 함수들을 사용하여 알고리즘을 실행한다. QueryPerformanceFrequency(); ,QueryPerformanceCounter(); 함수를 사용하여 ns 단위로 시간을 측정한다. 결과를 출력하고 각 알고리즘의 소요된 시간을 출력한다. 그리고 파일로 저장한다. 

### 코드 실행 결과

<figure>
	<img src="/images/result1.png" alt="">
</figure>
<figure>
	<img src="/images/result2.png" alt="">
</figure>