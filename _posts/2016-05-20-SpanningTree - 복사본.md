---
layout: post
title: "[알고리즘]Fractional Knapsack Problem"
description: "[알고리즘]Fractional Knapsack Problem" 
modified: 2016-06-20
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

빈틈없이 배낭채우기 알고리즘에대해 알아보자.
 


<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->



## 빈틈없이 배낭채우기

### 분석/풀이


- 빈틈없이 배낭채우기 알고리즘은 무게 당 가치가 높은 물건부터 우선적으로 채워나가다가 물건이 가방의 무게 수용량을 넘어 갈 경우 물건의 일부분을 잘라서 담는다. 이 빈틈없이 배낭 채우기 방법은 탐욕적인 접근방법으로 최적해를 구할 수 있다.
- 우선 무게당 가치가 높은 물건 순으로 미리 정렬을 해서 가방에 채우는 방법도 있고, 반복문으로 계속 가치가 높은 물건을 비교해 가면서 최대값을 뽑아내어 가방에 채우는 방법이 있다. 
- 500개 의 아이템을 채웠는지 안 채웠는지를 판단을 하기위해 used[] 배열을 만들어 각 인덱스를 0,1 값으로 사용했는지 안 사용했는지를 판단해 가면서 가치가 높은 max 값을 찾아 가방에 적재 시킨다.  그리고 가방무게를 초과할 경우 마지막 아이템을 가방무게에 맞게 잘라서 적재 시킨다. 


### Fractional Knapsack 구현 소스

- [코드 다운로드](https://github.com/yimok/yimok.github.io/tree/master/data/Fractional_Knapsack)


```cpp

#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector를 쓰기위한 라이브러리
#include <time.h>
using std::vector;
#pragma warning(disable:4996)
#define SIZE 500 //가방 사이즈


// 가중치,무게 파일을 읽어와 벡터 1차원 배열에 저장시키는 함수.
// parameter : 읽은 값을 저장시킬 vector 1차 배열 , 파일명
// return : 없음
void ArrayInit(vector<int>  &array, char * fname)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	int idx=0, temp = 0;

	if (fin == NULL)
	{
		printf("파일명이 없습니다.\n");
		return;
	}

	//파일속에 저장된 데이터의 수를 확인하기위한 반복문  idx에 값 축적
	while (1)
	{
		if (feof(fin) != 0)
			break;
		fscanf(fin, "%d\n", &temp);
		idx++;
	}
	fseek(fin, 0L, SEEK_SET);			//파일 포인터 위치를 처음으로 리셋


	int * arr = new int[idx - 1];		//동적 배열 할당 축적된 idx값으로 배열크기 결정
	idx = 0;

	//데이터 뽑아서 arr 동적배열에 저장 시키기
	while (1)
	{
		if (feof(fin) != 0)
			break;
		fscanf(fin, "%d\n", &temp);
		arr[idx] = temp;
		idx++;
	}
	fclose(fin);

	
	
	for (int i = 0; i < SIZE ; i++)
	{

		//arr에 읽어온 데이터들을 벡터 배열로 저장
		array[i] = arr[i];

	}


	fclose(fin);

}



// 빈틈없이 가방채우기 알고리즘 함수
// parameter : price가 저장된 배열, weight가 저장된 배열 , 가방의 용량
// return : 없음
void Fractional_Knapsack(vector<int> &price, vector<int> &weight, int capacity)
{
	int i, max;
	int *used = new int[price.size()];     //지정된 인덱스위치의 아이템이 사용했는지 안했는지 판단
	int current_weight;
	double total_value=0;


	//사용 가능한 용량
	current_weight = capacity;
	
	//아직 사용전이기 떄문에 0으로 모두 초기화 
	for (i = 0; i < (int)price.size(); i++)
	{
		used[i] = 0; 
	}
	
	
	//Item을 넣으면서 current_weight를 깍아가며
	//최대 수용량까지 반복문을 돌림
	while (current_weight > 0) 
	{ 
		
		max = -1;
		
		//무게당 비용 비율이 가장 높은 아이템 을찾는다.
		for (i = 0; i < (int)price.size(); ++i)
		{
			//아직 넣지않은 아이템 즉 used[i]가 0이고 
			//max가 -1(맨처음 넣을때) 이거나
			//가격을 무게로 나는 비율을 비교했을때 max 인덱스의 비율보다 큰경우 
			//max를 i로 고침
			if ((used[i] == 0) && ((max == -1) || ((double)price[i] / weight[i] >(double)price[max] / weight[max])))
			{
				max = i;
			}
		}

		//위 반복문에서 가장 고효율의 아이템이 뭔지 알았으므로
		//그 인덱스를 1로 하여 사용여부를 표시함
		used[max] = 1; 

		//max 아이템의 인덱스를 사용하여 무게와 가격을 불러와
		//current_weight 값과 total_value 값을 수정함
		current_weight -= weight[max]; 
		total_value += price[max];

		//추가한 아이템을 출력함
		if (current_weight >= 0)
			printf("%3d 번째 Item (가치:%3d, 무게:%3d) 추가 성공 , 남은 무게 공간 %d.\n", 
				max , price[max], weight[max], current_weight);
		
		
		//만약 마지막에 추가한 아이템이 수용용량을 초과하는 무게를 가지고 있다면
		//용량에 맞게 나누어 나눈 값을 저장한다.
		else 
		{
			printf("%3d 번째 Item (가치:%3d, 무게:%3d)  %2d%% 나누어 추가 성공 \n", 
				max, price[max], weight[max],(int)(( 1+(double)current_weight / weight[max]) * 100));
			
			total_value -= price[max];
			total_value += (1+(double)current_weight / weight[max]) * price[max];
		}
	}

	printf("아이템의 총 가치는 %.0f 입니다.\n", total_value);

}


int main()
{

	char fname1[50], fname2[50];
	int c;

	vector<int>  Price(SIZE , 0); // Price[SIZE] 인 동적 배열
	vector<int>  Weight(SIZE, 0); // Weight[SIZE] 인 동적 배열
	ArrayInit(Price, "price.txt");
	ArrayInit(Weight, "weight.txt");
	
	printf("빈틈없이 배낭채우기 알고리즘 입니다.\n");
	printf("가방의 최대무게를 입력하세요\n");
	scanf("%d", &c);
	
	Fractional_Knapsack(Price, Weight, (int)c);

	return 0;


}

```

### 코드 해설

1. ArrayInit 함수 : 인자로 1차원 vector 배열, 파일명을 받는다. 함수 내부에 FILE 포인터 변수 fin을 선언하고 바이너리 파일을 읽을 수 있도록 rb로 파일을 오픈한다. 우선 저장된 데이터 수를 확인하기 위하여 반복문을 돌려 데이터의 수를 idx변수에 저장하고 이 변수를 이용하여 동적 배열을 생성한 후 다시 데이터를 읽어서 arr 동적배열에 저장시킨다. 즉 500개의 데이터를 arr 배열에 저장 시킨다. arr 배열에 저장한 데이터들을  vector 배열로 다시 저장한다. array[i] = arr[idx]; 

2. Fractional_Knapsack 함수 : 인자로 1차원 vector 배열 2개 , 가방의 용량을 받는다. current_weight 변수에 가방의 용량을 저장하여 아이템을 적재시킬떄 마다 그 무게만큼 감소 시켜 사용가능한 공간을 표기한다. 그리고 use[] 동적 배열을 만들어 500개의 아이템들이 가방에 적재를 했는지 안했는지 판단하는 역할을 하도록 한다. 즉 0 또는 1이 저장되며 0이면 사용안됨 1이면 사용됨이다. 그리고 반복문을 current_weight가 0 보다 클 때 까지 돌리며 맨처음 max를 –1로 초기화하고 무게 당 가치가 가장 높은 아이템을 찾아 max에 그 아이템의 인덱스를 저장시켜서 used[max] = 1로 변환(사용 함)하고 , current_weight -= weight[max] 저장 시킨 아이템의 무게만큼 빼서 남은 무게를 알림, total_value += price[max] 총 가치 저장함 그리고 추가한 아이템이 정상적으로 됬다고 출력해준다. 만약 마지막에 추가한 아이템이 수용용량을 초과하는 무게를 가지고 있다면 용량에 맞게 나누어, 나눈 값을 가방에 저장한다. 그리고 역시 출력한다.

3. main 함수 : price, weight를 저장할 2개의 1차원 배열을 만들고 위에서 생성한 함수를을 호출한다.

### 코드 실행 결과

<figure>
	<img src="/images/fractional1.png" alt="">
</figure>
