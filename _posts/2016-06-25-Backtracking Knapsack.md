---
layout: post
title: "[알고리즘]0/1 Knapsack - Bactracking"
description: "[알고리즘]0/1 Knapsack - Bactracking" 
modified: 2016-06-20
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

백트래킹 – 0/1 배낭채우기에 대해 알아보자
 


<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->



## 백트래킹 – 0/1 배낭채우기

### 분석/풀이


- 되추적 방법을 사용한 0/1 배낭채우기 알고리즘 은 무게 당 가치가 높은 물건부터 우선적으로 채워나가며, 물건의 총 무게가 배낭의 용량을 초과하지 않으면서 물건의 값어치가 최대가 되도록 물건을 적재 시키는 방법이다. 탐욕적 방법으로 물건의 일부분을 잘라서 담았던 빈틈없이 배낭을 채웠던 방법과는 차이가 있다.
- 상태 공간 트리를 구축하여 백트래킹 기법으로 깊이 우선 탐색을 실시한다. 즉 값어치가 높은 물건을 순서대로 넣는다. 만약 상태 공간 트리의 루트에서 왼쪽으로 가면 첫 번째 물건을 배낭에 넣는 경우이고, 오른쪽으로 간다면 첫 번째 물건을 넣지 않는 경우이다.

<figure>
	<img src="/images/01knapsack1.png" alt="">
</figure>

- 위 그림은 아이템의 수가 4개이고, 가방의 무게 W가 16일 때 아이템을 배낭에 채워나가는 상태 공간 트리이다.  트리에서 왼쪽으로 쭉 계속 먹다가 적절하지 않은 물건이면 트리 왼쪽 끝 에서 한 단계 백트래킹 해서 먹지 않고 다른 걸 먹고, 또 적절한 물건이 아니면 위로 올라가면서 바꿔가면서 계속 먹는다. 이러한 과정을 거쳐 최적의 해답을 구한다.
- 그리고 유망성 검사를 해야 하는데 상태 공간 트리의 어떠한 마디까지의 물건의 무게 합이 weight라고 할 때 가방의 무게 W보다 크거나 같으면 그 마디는 유망하지 않다고 판단한다. 
- 그리고 아래 식으로 bound 값을 구하여 maxprofit 과 비교하여 유망하지 않은지를 판단한다. 

<figure>
	<img src="/images/01knapsack2.png" alt="">
</figure>

### Fractional Knapsack 구현 소스

- [코드 다운로드](https://github.com/yimok/yimok.github.io/tree/master/data/01_knapsack)


```cpp


#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector를 쓰기위한 라이브러리
using std::vector;

//1. 트리에서 왼쪽으로 쭉 계속먹는다
//2. 트리 왼쪽끝에서 한단계 백트래킹해서 먹지않고 다른걸 먹는다.
//3. 위로 올라가면서 바꿔가면서 넣는다.

#pragma warning(disable:4996)
#define SIZE 500 //아이템 사이즈

int maxprice, itemnum=SIZE, W, totprice;
int numbest=0; // 살펴본 물건들(먹지 않은 물건 개수 포함)
vector<char> bestset(SIZE+1, 0); // 최대 이익일때 선택한 물건들
vector<char> include(SIZE+1, 0); // 현재 선택한 물건 (먹은걸 y, 안먹은걸 n )



struct item
{
	int id;
	float w;
	float p;

};



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

	Item[0].p = 0;
	Item[0].w = 0;
	
	for (int i = 1; i <=SIZE; i++)
	{
		//arr에 읽어온 데이터들을  저장
		//id와, arr배열에 저장한 price,weight를
		//인덱스에 맞게 구조체 변수에 저장함
		Item[i].id = i;
		Item[i].p = arr[i-1];
		Item[i].w = arr2[i-1];
	}



}

//qsort 비교함수
//무게당 가치로 비교함
int compare(const void *x, const void *y)
{
	if ((*(item *)y).p / (*(item *)y).w > (*(item *)x).p / (*(item *)x).w)
		return 1;
	else if ((*(item *)y).p / (*(item *)y).w < (*(item *)x).p / (*(item *)x).w)
		return -1;
	else
		return 0;
}



// 해당 아이템이 유망한가를 판단하는 함수
// parameter : 아이템의 수, weight , ITEM 구조체 배열 변수 시작주소
// return : true / false
bool promising(int i, int weight, item ITEM[])
{
	int j, k;
	int totweight;
	float bound;
	static int o = 1;

	//더이상 못먹으면 즉 weight가 가방을 넘치면 재귀탈출
	if (weight >= W)
		return false;

	else
	{
		//다음 아이템을 먹는다고 가정했을때
		//다음 아이템을 의미하는 j와
		//bound 에 지금까지의 price들을 저장한다
		//totweight도 우선 현재까지의 무게로 초기화 한다.
		j = i + 1;     
		bound = totprice;  
		totweight = weight;   

		// 무게가 허락하는데 까지 다음 아이템을 포함시킨다
		while (j <= itemnum && totweight + ITEM[j].w <= W)
		{       
			totweight = totweight + ITEM[j].w;
			bound = bound + ITEM[j].p;
			j++;
		}

		k = j;  

		// bound값 산출	
		if (k <= itemnum)         
			bound = bound + (W - totweight) * ITEM[k].p / ITEM[k].w;

		return bound > maxprice;
	}
}

// 01 배낭채우기 되추적 알고리즘 구현 함수
// parameter : 아이템의 수, price, weight , ITEM 구조체 배열 변수 시작주소
// return : 없음
void knapsack(int i, int price, int weight, item ITEM[])
{
	// W는 가방의 한계 무게
	// 무게가 충분하고 price가 maxprice보다 크면
	// maxprice 최대 이익을 현재 이익으로 저장
	if (weight <= W && price > maxprice)
	{
		maxprice = price;    
		numbest = i;
		
		// y, n 으로 저장된 include 들을 bestset에 저장함
		// 즉 사용을 했다 안했다를 표시하기 위함 
		bestset = include;

	}
	
	// 현재 아이템이 유망 하다면
	if (promising(i, weight, ITEM))  
	{

		// 다음 아이템을 포함시킨다
		// 트리로 비유하면 자식노드중 왼쪽놈으로
		include[i + 1] = 'y';     
		
		totprice = price + ITEM[i+1].p;
		knapsack(i + 1, price + ITEM[i + 1].p, weight + ITEM[i + 1].w, ITEM);
		
		// 만약 위 재귀함수에서 유망성 검사를 통해 유망하지 않음이 판단되면
		// 다음 아이템을 포함시키지 않는다
		// 트리로 치면 자식노드중 오른쪽놈으로 
		include[i + 1] = 'n';                 
		totprice = price;
		knapsack(i + 1, price, weight, ITEM);
	}
}





int main()
{

	char fname1[50], fname2[50];
	int c;
	item ITEM[SIZE+1];

	
	ArrayInit(ITEM, "price.txt", "weight.txt");
	printf("백트래킹 0/1 배낭채우기 알고리즘 입니다.\n");
	printf("가방의 최대무게를 입력하세요\n");
	scanf("%d", &W);

	//0번째 인덱스는 사용안하므로
	//1번째 인덱스부터 정렬함
	qsort(&ITEM[1], SIZE, sizeof(item), compare);

	knapsack(0, 0, 0, ITEM);
	
	for (int i = 1; i <= SIZE; i++)
	{
		if (bestset[i] == 'y')
			printf("[ID:%3d   price:%3.0f weight:%3.0f]\n", ITEM[i].id,  ITEM[i].p, ITEM[i].w);
	}
	printf("maxprice : %d    \n", maxprice );


	return 0;


}


// 백트래킹: 깊이우선 탐색
// branch and bound 와의 차이점은 유망성 검사는 같지만 -> 넓이 우선 탐색(자식노드 2개부터 보고 또 자식노드의 자식노드2개를 보고 ..)->힙,디큐로 구현가능

```

### 코드 해설

1. Struct item : 물건의 id, weigt, price를 저장하는 구조체

2. ArrayInit 함수 : 인자로 1차원 vector 배열, 파일명 2개를 받는다. 함수 내부에 FILE 포인터 변수 fin1, fin2 을 선언하고 바이너리 파일을 읽을 수 있도록 rb로 파일을 오픈한다. 우선 저장된 데이터 수를 확인하기 위하여 반복문을 돌려 데이터의 수를 idx변수에 저장하고 이 변수를 이용하여 동적 배열을 생성한 후 다시 데이터를 읽어서 arr 동적배열에 저장시킨다. 즉 500개의 데이터(price,weight)를 arr, arr2 배열에 저장 시킨다. arr, arr2 배열에 저장한 데이터들을  Item 구조체 변수들에 적재 시킨다 이때 id값도 같이 저장한다.

3. compare 함수 : qsort()함수의 인자로 넘겨 줄 비교함수로 item 구조체 변수의 가격과 무게로 값어치를 환산해 비교하여 정렬시키도록 도와준다.

4. Promising 함수 : 인자로 물건의 수 , 무게, item 구조체 배열 변수 ITEM, 을 받는다. 해당 아이템이 유망한가를 판단하는 함수로 현재까지 저장한 물건의 weight가 가방의 용량 W와 같거나 넘으면 재귀를 탈출하고 , 아니라면 다음 아이템을 먹는다고 판단하고 ,다음 아이템을 의미하는 j를 만들고, bound에 지금까지 price들을 저장시킨다. totweight 도 지금까지 저장된 무게로 바꾼다. totweight와 bound를 반복문을 사용하여 무게가 허락하는 한도까지 아이템을 포함시켜서 값을 저장시키고 , 반복문을 통해 저장된 bound와 totweiht 값을 사용하여  bound = bound + (W - totweight) * ITEM[k].p / ITEM[k].w; 식을 그 경로의 boud 값을 만들고 maxprice 값과 비교해 유망한지 아닌지 판단한다.

5. knapsack 함수 : 인자로 물건의 수 ,가격, 무게, item 구조체 배열 변수 ITEM, 을 받는다. 0/1 배낭채우기 되추적 방법 구현 함수로 전역 변수로 선언된 가방 한계무게 W, maxprice를 입력받은 weight 와 price를 비교하면서 조건에 만족할 경우 maxprice의 최대 이익을 받아온 price로 저장한다. 그리고 전역변수로 선언된 bestset, include 배열 즉 아이템이 사용이 되었다 안되었다를 판단하기 위해 ‘y’ , ‘n’을 저장한 배열 include를 bestset에 으로 지정한다. 그리고 if문 안에 promising() 함수를 호출해 현재 아이템이 유망한지 안한지를 판단하여 유망하다면 include[i+1] = ‘y’ 로 지정하고 깊이탐색이므로 다시 다음 아이템을 재귀호출을 통해 유망한지 판단한다. 이 과정을 반복하여 최적의 해를 구한다. 재귀를 탈출했다면 유망하지 않으므로 함수의 끝부분에 include[i+1] = ‘n’을 표기해 배낭에 넣지 않음을 알리고 다시 재귀 호출을 한다.

### 코드 실행 결과

<figure>
	<img src="/images/01knapsack3.png" alt="">
</figure>
