---
layout: post
title: "[알고리즘]0/1 Knapsack - Dynamic/Branch and bound"
description: "[알고리즘]0/1 Knapsack - Dynamic/Branch and bound" 
modified: 2016-06-30
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

동적계획식 방법과 분기한정 가지치기 방법으로 0/1 배낭채우기 문제를 해결해보자.
 


<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->



## 동적계획식 – 0/1 배낭채우기

### 분석/풀이


- 0/1 배낭 채우기는 물건을 통째로 넣거나(1) 안 넣거나(0) 둘중 하나를 선택해야한다 물건을 자를 수 없다. 이 방법을 사용하여 최적해를 구한다. 즉 배낭에 담을 물건을 선택해서 선택된 물건의 가치가 최대가 되도록 한다.
- n개의 물건이 있을 때 각 물건을 넣을 것 인지 안 넣을 것인지 선택하기 때문에 배낭에 넣을 물건을 선택할 수 있는 경우의 수는  가지를 가진다. 이 가지수로 총 가치를 계산한다. 계산된 값을 비교하여 총가치가 최대인 최적해를 구한다. 
- 물건 <1, ... , n>으로 W kg인 배낭을 채우는 최적해가 K(n,W) 라고 할 때, 이 최적해는 물건 n이 최적해 안에 포함되는 경우와, 안되는 경우 2가지로 구분해야한다.

<figure>
	<img src="/images/01knapsack4.PNG" alt="">
</figure>

- 점화식
<figure>
	<img src="/images/01knapsack5.png" alt="">
</figure>
- 물건 n의 무게가 가방 W의 여유 무게보다 클 경우 아예 넣지를 못하므로 K(n-1,W) 이다.
- 하지만 점화식의 3번째처럼 넣을 수 있는 경우 다 계산해서 최대 값을 선택해야한다. 


## branch and bound – 0/1 배낭채우기 (best – first search)

### 분석/풀이


- 백트래킹 0/1배낭채우기와 매우 비슷하지만 차이점은 트리 횡단 방법이 정해진 것이 아니라는 것과, 최적화 문제를 푸는데만 쓰인다는 것이다. 즉 분기한정 알고리즘은 어떤 마디가 유망한지를 결정하기 위해서 그 마디에서 한계값을 계산하고 이 한계값은 그 마디 아래로 확장하여 구할 수 있는 해답값의 한계를 나타낸다. 그 한계값이 그때까지 찾은 최고 해답값보다 더 좋지 않으면 그 마디는 유망하지 않다고 판단하고, 더 좋다면 유망하다라고 판단한다.
- 이를 구현하는 방법은 분기한정 가지치기 최고우선검색(best-first search with branch-and-bound pruning) 이라 하고 또 분기한정 가지치기 너비우선검색(breadth-first search with branch-and-bound pruning) 이라고 하는 방법으로 구할 수 있지만 너비우선검색은 깊이우선검색에 비해 이점이 없다.
- 분기한정 가지치기 너비우선검색 0-1배낭채우기는 추가적으로 한계값을 사용하여 검색을 향상시키는 방법이다. 주어진 어떤 마디의 모든 자식마디를 방문 후, 유망하면서 확장하지 않은 마디들을 모두 살펴보고, 그 중에서 한계값이 가장 좋은 마디를 우선적으로 확장한다. 이를 구현할 때 우선순위 큐를 사용한다.
아이템수 4개 , 가방의무게 16

<figure>
	<img src="/images/01knapsack6.png" alt="">
</figure>

1. 마디 (0,0)을 방문한다. -> 이익과 무게를 $0과 0으로 놓는다. -> 한계값을 계산하면, $115가 된다. -> maxprofit을 0으로 놓는다.
2. 마디(1,1)을 방문한다 -> 이익과 무게를 계산하면, $40과 2가 된다. -> 무게 2는 W의 값 16보다 작거나 같고, 이익 $40은 $0보다 크므로, maxprofit의 값을 $40으로 놓는다.

3. 마디(1,2)를 방문한다. -> 이익과 무계를 계산하면 $0, 0이 된다. -> 한계값을 계산하면 $82가 된다.
4. 아직 확장하지 않은 마디 중에서 가장 큰 한계값을 가진 유망한 마디를 구한다. -> 마디 (1.1)은 한계값이 $115이고 , 마디(1,2)는 한계값이 $82 이므로, 마디 (1,1)이 한계값이 가장 크면서, 유망하고, 확장하지 않은 마디이다. 그 마디의 자식마디를 다음에 방문한다.
5. 이 과정을 반복하면서 유망성검사를 하여 최적해를 구한다.

- 유망성 검사를 할때는 아래 식으로 bound 값을 구하는 함수를 만들고 이 값을 노드내에 넣어서  maxprofit 과 비교하고, 또 무게를 넘지 않았는지 판단하여 유망하지 않은지를 체크한다 

<figure>
	<img src="/images/01knapsack7.png" alt="">
</figure>

### 동적계획식/분기한정 가지치기 – 01 배낭채우기 구현 소스

- [코드 다운로드](https://github.com/yimok/yimok.github.io/tree/master/data/01_knapsack_dynamic,branch_and_bound)


```cpp


#include <stdio.h>
#include <stdlib.h>
#include <vector> 
#include <queue>
#include <iostream>

#pragma warning(disable:4996)
#define SIZE 500 //아이템 사이즈
using namespace std;
int maxprofit;

//노드 정보 구조체
struct node
{
	int level;
	int w;
	int p;
	float bound;
};

//아이템 구조체
struct item
{
	int id;
	float w;
	float p;
};

//우선순위 큐의 3번째 인자 비교 오퍼레이터
struct cmp{
	bool operator()(node x, node y) 
	{
		return y.bound > x.bound;
		
	}
};


//큐소트의 비교함수
int compare(const void *x, const void *y)
{
	if ((*(item *)y).p / (*(item *)y).w > (*(item *)x).p / (*(item *)x).w)
		return 1;
	else if ((*(item *)y).p / (*(item *)y).w < (*(item *)x).p / (*(item *)x).w)
		return -1;
	else
		return 0;
}

// 가중치,무게 파일을 읽어와 벡터 1차원 배열에 저장시키는 함수.
// parameter : 읽은 값을 저장시킬 vector 1차 배열 , 파일명1, 파일명2
// return : 없음
void ArrayInit(item  Item[], char * fname1, char *fname2)
{
	FILE *fin1, *fin2;
	fin1 = fopen(fname1, "rb");
	fin2 = fopen(fname2, "rb");
	int idx = 0, temp = 0;

	if (fin1 == NULL || fin2 == NULL)
	{
		printf("파일명이 없습니다.\n");
		return;
	}

	//파일속에 저장된 데이터의 수를 확인하기위한 반복문  idx에 값 축적
	while (1)
	{
		if (feof(fin1) != 0 || feof(fin2) != 0)
			break;
		fscanf(fin1, "%d\n", &temp);
		idx++;
	}
	fseek(fin1, 0L, SEEK_SET);			//파일 포인터 위치를 처음으로 리셋

	//동적 배열 할당 축적된 idx값으로 배열크기 결정
	int * arr = new int[idx - 1];
	int * arr2 = new int[idx - 1];
	idx = 0;

	//데이터 뽑아서 arr 동적배열에 저장 시키기
	while (1)
	{
		if (feof(fin1) != 0 || feof(fin2) != 0)
			break;
		fscanf(fin1, "%d\n", &temp);
		arr[idx] = temp;
		fscanf(fin2, "%d\n", &temp);
		arr2[idx] = temp;
		idx++;
	}
	fclose(fin1);
	fclose(fin2);

	
	for (int i = 0; i < SIZE; i++)
	{
		//arr에 읽어온 데이터들을  저장
		//id와, arr배열에 저장한 price,weight를
		//인덱스에 맞게 구조체 변수에 저장함
		Item[i].id = i+1;
		Item[i].p = arr[i];
		Item[i].w = arr2[i];
	}


}


// 한계값을 구하는 함수
// parameter : 가방의무게, 아이템 수, 노드, 아이템
// return : 계산된 한계값
float bound(int Weight, int n, node u, item ITEM[])
{
	int j, k;
	int totweight;
	float result;

	if (u.w >= Weight)
		return 0;
	else
	{
		result = u.p;
		j = u.level + 1;
		totweight = u.w;
		while (j <= n && totweight + ITEM[j-1].w <= Weight)
		{
			totweight = totweight + ITEM[j-1].w;
			result = result + ITEM[j-1].p;
			j++;
		}
		k = j;
		if (k <= n)
			result = result + (Weight - totweight) * ITEM[k-1].p / ITEM[k-1].w;

		return result;
	}


}

//우선순위 큐 초기화 함수
void clear(std::priority_queue<node, vector<node>, cmp > &q)
{
	std::priority_queue<node, vector<node>, cmp > empty;
	std::swap(q, empty);
}


// 분기한정 가지치기 최고우선검색 알고리즘
// parameter : 무게, 아이템, 아이템 수
// return : 없음
void Branch_and_bound_Knapsack_0_1(int Weight, item ITEM[], int n)
{
	priority_queue <node, vector<node> , cmp > Q;
	node u, v;
	
	//큐 초기화
	clear(Q);

	//루트 노드 설정
	v.level = 0;
	v.p = 0;
	v.w = 0;
	v.bound = bound(Weight, n, v, ITEM);
	
	maxprofit = 0;
	Q.push(v);

	while (!Q.empty())
	{

		v = Q.top();
		
		
		//최고의 한계값을 가진 마디 제거
		Q.pop();

		//마디가 아직 유망한지를 검사한다.
		if (v.bound > maxprofit)
		{
			//노드 u를 다음 아이템을 포함하는 자식마디로 놓는다.
			u.level = v.level + 1;
			u.w = v.w + ITEM[u.level-1].w;
			u.p = v.p + ITEM[u.level-1].p;
			
		

			if (u.w <= Weight && u.p > maxprofit)
			{
				maxprofit = u.p;
				//최적해를 얻는 노드 순서 출력
				printf("[level:%3d   price:%d  weight:%d ]\n", u.level, u.p, u.w);
			}
			u.bound = bound(Weight, n, u, ITEM);
			if (u.bound >maxprofit)
				Q.push(u);

			//노드 u를 다음 아이템을 포함하지않는 자식 마디로 놓는다.
			u.w = v.w;
			u.p = v.p;

			u.bound = bound(Weight, n, u, ITEM);
			if (u.bound > maxprofit)
				Q.push(u);

		}

	}

}

// 동적계획식 방법으로 구현한 0-1배낭채우기
// parameter : 가방의무게, 아이템들이 저장된 구조체 배열, 아이템 수, 최적해를 저장할 K, 출력할때 필요한 Check배열
// return : 없음
void Dynamic_Knapsack_0_1(int Weight, item ITEM[], int n, vector < vector<int> > &K)
{
	int i, u;
	vector < vector<int> > Check(SIZE + 1, vector<int>(Weight + 1, 0));
	vector<item> Print;
	vector<item>::iterator it;
	//아이템의 수 i를 점진적으로 증가시킴
	for (i = 0; i <= n; i++)
	{
		//가방의 무게 u를 증가시켜감
		for (u = 0; u <= Weight; u++)
		{
			//Check[i][u] : 어떤 아이템이 입력되었는지 출력을 하기위해 체크하는 배열
			//K[i][u] : 물건 <1,...,i>를 용량 u kg의 배낭에 넣을 수 있는 최적해의 총 가치.
			//최종적으로 i가 n까지 가고, u가 weight까지 가면 우리가 원하는 최적해의 총 가치를 구할 수 있다.
			//상향식으로 계산해가면서 최적해의 값을 구한다.
			//점화식 3가지 식을 아래처럼 표현한다.
			//만약 아이템이 없거나, 가방의남은 무게가 0이면
			if (i == 0 || u == 0)
			{
				K[i][u] = 0;

			}
			//아이템의 무게가 가망의 남은무게보다 커서 집어넣지 못할경우
			//아이템n이 최적해 안에 포함되지 않으므로 아래식과 같다.
			else if (ITEM[i - 1].w > u)
			{
				K[i][u] = K[i - 1][u];
				Check[i][u] = 0;
			}

			//다 넣을수 있는경우 다 계산해서 최대값을 선택해야한다.
			//i와 ,u 값을 증가시켜가면서 이전에 저장된값과, 현재의 값과 비교해보면서 
			//가치가 높은 값을 K에 저장시켜서 최적해를 구한다.
			else if (K[i - 1][u] > ITEM[i - 1].p + K[i - 1][u - ITEM[i - 1].w])
			{
				K[i][u] = K[i - 1][u];
				Check[i][u] = 0;
			}

			//최종적으로 저장시켰을떄 값의 위치를 파악하기위해
			//해당 인덱스위치의 Check 배열의 값을 1로바꿈
			else
			{
				K[i][u] = ITEM[i - 1].p + K[i - 1][u - ITEM[i - 1].w];
				Check[i][u] = 1;
			}
		}
	}
	
	
	//가방에 어떤 아이템을 넣었는지 출력하는 구문
	u = Weight;
	it = Print.begin();
	
		for (i = n; i >= 1; i--)
		{
			if (Check[i][u] == 1)
			{
				//Check 배열을 참조하면서 역순으로 값을 가져와
				//다시 Print vector에 넣는데 Print.begin() 은 배열의 가장 앞에부터 넣는다.
				//결국 역오름차순값이 오름차순으로 정렬된상태로 Print vector에 저장됨
				it = Print.insert(it, ITEM[i-1]); 
				u = u - ITEM[i-1].w;
			}
		}

		for (int i = 0; i < Print.size(); i++)
			printf("[ID:%3d   price:%3.0f  weight:%3.0f]\n", Print[i].id, Print[i].p, Print[i].w);


}

int main()
{

	char fname1[50], fname2[50];
	int c;
	int itemnum = SIZE, W;
	item ITEM[SIZE];
	
	ArrayInit(ITEM, "price.txt", "weight.txt");
	printf("동적계획법과 분기한정 가지치기 최고우선검색 방법으로 0/1 배낭채우기를 하는  알고리즘 입니다.\n");
	printf("가방의 최대무게를 입력하세요\n");
	scanf("%d", &W);
	
	vector < vector<int> > K(itemnum + 1, vector<int>(W + 1, 0));
	vector<item> Print;
	
	//가치순으로 정렬
	qsort(ITEM, SIZE, sizeof(item), compare);
	
	printf("동적계획법을 사용한 0-1배낭채우기 문제해결 알고리즘\n");
	Dynamic_Knapsack_0_1(W, ITEM, itemnum, K);
	printf("maxprice : %d \n\n", K[itemnum][W]);

	printf("분기한정 가지치기 최고우선검색 방법을 사용한 0-1배낭채우기 문제해결 알고리즘\n");
	Branch_and_bound_Knapsack_0_1(W,ITEM,itemnum);
	printf("maxprice : %d \n", maxprofit);

	return 0;

}




```

### 코드 해설

1. Struct item : 물건의 id, weight, price를 저장하는 구조체

2. Struct node : 노드의 level, weight, price, 한계값을 저장하는 구조체

3. ArrayInit 함수 : 인자로 1차원 vector 배열, 파일명 2개를 받는다. 함수 내부에 FILE 포인터 변수 fin1, fin2 을 선언하고 바이너리 파일을 읽을 수 있도록 rb로 파일을 오픈한다. 우선 저장된 데이터 수를 확인하기 위하여 반복문을 돌려 데이터의 수를 idx변수에 저장하고 이 변수를 이용하여 동적 배열을 생성한 후 다시 데이터를 읽어서 arr 동적배열에 저장시킨다. 즉 500개의 데이터(price,weight)를 arr, arr2 배열에 저장 시킨다. arr, arr2 배열에 저장한 데이터들을  Item 구조체 변수들에 적재 시킨다 이때 id값도 같이 저장한다.

4. cmp 함수 : 우선순위 큐 STL의 3번쨰 인자로 들어가는 비교 오퍼레이터

5. clear 함수 : 우선순위 큐 초기화 함수

6. compare 함수 : qsort()함수의 인자로 넘겨 줄 비교함수로 item 구조체 변수의 가격과 무게로 값어치를 환산해 비교하여 정렬시키도록 도와준다.

7. Bound 함수 :  무게, 물건의 수, node 구조체 변수, item 구조체 배열 변수 ITEM, 을 받는다. 해당 아이템의 한계값을 구하는 함수로 받아온 노드 u의 weight가 가방의 용량 W와 같거나 넘으면 재귀를 탈출하고 , 아니라면 다음 아이템을 먹는다고 판단하고 ,다음 아이템 즉 다음 노드를 의미하는 j에 u.level + 1을 하여 만들고, result에 지금까지 price들을 저장시킨다. totweight 도 지금까지 저장된 무게를 저장한다. totweight와 result를 반복문을 사용하여 무게가 허락하는 한도까지 아이템을 포함시켜서 값을 저장시키고 , result = result + (Weight - totweight) * ITEM[k-1].p / ITEM[k-1].w; 식을 사용해 노드의 한계값을 구해 리턴한다.

8. Branch_and_bound_Knapsack_0_1 함수 : 인자로 가방의 무게, item 구조체 배열 변수 ITEM , 물건의 수 를 받는다. 0/1 배낭채우기 branch_and_bound(최고우선검색) 방법을 구현한 함수로 우선순위 큐를 사용한다. 노드 v,u를 만들고 루트노드 v를 설정한 뒤 루트 노드를 큐에 넣고 그 후에 큐가 빌때까지 반복문을 돌리면서 마디가 유망한지를 검사하여 자식노드 u를 다음아이템을 포함하는 자식마디로 놓을지 아니면 포함하지 않는 자식마디로 놓을지 판단하여 배낭채우기를 한다.

9. Dynamic_Knapsack_0_1 함수 : 인자로 가방의 무게, item 구조체 배열 변수 ITEM , 아이템 수, 최적해를 저장할 vector 1차원 배열 K을 받는다. 이 함수는 동적계획식 방법으로 구현한 0/1 배낭채우기 함수이며, 아이템 의수 I를 점짐적으로 증가시키고, 가방의 무게 u도 증가시켜가면서 상향식으로 계산해 가면서 최적해의 값을 구한다. Check 배열은 어떤 아이템이 입력되었는지 출력을 하기위해 체크하기 위한 배열이고, K배열은 물건 <1,...,i>를 용량 u kg의 배낭에 넣을 수 있는 최적해의 총 가치가 저장된다. 최종적으로 i가 n까지 가고, u가 weight까지 가면 우리가 원하는 최적해의 총 가치를 구할 수 있다.그리고 동적계획식으로 배낭채우기를 실행하는 점화식을 구현했다. 만약 아이템이 없거나, 가방의 무게가 0이면 if (i == 0 ll u == 0) 구문을 실행, 아이템의 무게가 가망의 남은무게보다 커서 집어넣지 못할 경우 아이템n이 최적해 안에 포함되지 않으므로 else if (ITEM[i - 1].w > u) 구문을 실행 ,  다 넣을수 있는경우 다 계산해서 최대값을 선택해야한다. i와 ,u 값을 증가시켜가면서 이전에 저장된값과, 현재의 값과 비교해보면서 가치가 높은 값을 K에 저장시켜서 최적해를 구한다. else if (K[i - 1][u] > ITEM[i - 1].p + K[i - 1][u - ITEM[i – 1].w]) 구문과  나머지 else 구문을 실행 , 그리고 최종적으로 값이 저장되었을떄 해당 인덱스의 값으로 check배열의 값을 1로 바꿔 기억한다. 이 배열을 사용하여 그 인덱스의 item 값들을 Print vector에 저장하는데 이때 insert 함수를 사용하여서 벡터의 앞에서 삽입한다. 그러면 역오름차순으로 되었던 값이 오름차순으로 되어 알맞게 출력된다.

### 코드 실행 결과

<figure>
	<img src="/images/01knapsack8.png" alt="">
</figure>

<figure>
	<img src="/images/01knapsack9.png" alt="">
</figure>