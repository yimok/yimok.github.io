---
layout: post
title: "[알고리즘]Merge Sort"
description: "[알고리즘]Merge Sort" 
modified: 2016-04-09
tags: [blog]
comments: true
image:
  feature: back6.jpg
---
Divide & Conquer 방법 중 하나인 합병정렬에 대해 알아보자.
 


<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Divide & Conquer

- 분할정복방법이란 어떠한 문제를 2개이상의 더 작은 문제로 나눈 후 두 작은 문제를 처리하는 방식이다.
- 분할정복법은 Top-down 접근 방법이다. 즉, 어떠한 문제의 맨 상위 사례의 해답은 아래로 내려가면서 작은 사례에 대한 해답을 구함으로써 구한다.
- 대표적으로 이분검색법, 합병정렬, 쉬트라센의 행렬곱셈 알고리즘 등이 있다.

## 합병 정렬(Merge sort)

<figure>
	<img src="/images/merge1.png" alt="">
</figure>

- 합병 정렬이란 임의의 순서로 저장된 배열에서 값을 탐색하는 알고리즘으로 정렬할 배열을 중심으로 왼쪽 오른쪽으로 재귀하면서 나누어 인덱스가1 즉 1개의 값만 가지게 되었을 경우 나누는 것을 멈추고 나누어진 배열들의 크기를 비교(좌, 우 나눠진 2개씩)해 가면서 다시 합병하여 최종적으로 정렬된 값을 배열에 저장시킨다. 
- S[4] 배열에 10,5,20,9 값이 저장되어 있다고 하자 mergesort(배열의 크기, S 배열) 함수를 만들어 배열의 반을 중심(mid)으로 좌측 L배열과 우측 R배열을 만든다. 그리고 S배열을 반반 나누어 저장한다. 재귀적으로 mergesort를 구현하여 배열의 크기 size > 1 즉 사이즈가 1이 되었을때는 배열이 한 개만 있으므로 더 이상 나눌 필요가 없다. 
- 이제 이렇게 나눠진 값을 merge(좌측 배열 크기, 우측 배열 크기, L배열, R배열, S배열) 함수를 사용하여 합치는데 나눠진 두 배열 L 배열과 R배열의 값을 비교하여 오름차순 정렬일 경우 작은 값을 S배열에 저장시키고 값을 뽑아온 배열의 인덱스를 1증가시킨다. 이런 과정을 반복하면 L과 R배열 중 하나의 값만 빼고 모두 들어가게 된다. 나머지 값은 반복문을 더 추가 구성하여 L배열과 R배열의 인덱스가 지정된 배열 크기를 넘어 갔는지 비교하여 넘지 않았을 경우 그 배열에 값이 남아있는 것이므로 값을 뽑아 S배열에 마저 저장한다.


### 합병 정렬 구현 코드


```cpp


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#pragma warning(disable:4996)        //visual 2013 에서 scanf 및 fprintf, fscanf 사용시 오류 제거
void merge(int Lsize, int Rsize, int L[], int R[], int S[])
{
	int i =0, j =0, k =0;
	while (i <= Lsize -1 && j <= Rsize -1)    //L배열의 크기와 R배열의 크기와 비교하여 
	{				                 //인덱스가 초과할 경우 반복문을 빠져나온다.	
		if (L[i] < R[j])		    //L배열의 값과 R배열의 값을 비교
		{
			S[k] = L[i];            //L배열이 작을경우 S배열에 L을 적재		
			i++;
		}
		else
		{
			S[k] = R[j];	   //R배열이 작을경우 S배열에 L을 적재		
			j++;
		}
		k++;
	}
	
	for (;;)           //위 반복문을 빠져 나왔을 경우 L배열과 R배열중 하나의 값만 남아있을것이다. 
	{	               //이 나머지 값을 넣기 위한 반복문 							 
		if (i > Lsize - 1) break;
		S[k] = L[i];
		i++;
		k++;
	}
	for (;;)
	{
		if (j > Rsize - 1) break;
		S[k] = R[j];
		j++;
		k++;
	}
}
void mergesort(int size, int S[])
{
	if (size>1)
	{
		const int mid = size/2;	//size가 만약 4라면  mid=2
								   
		int* L = new int[mid];         //입력된 size가 4라면 L배열의 크기는 2
		int* R = new int[size- mid];  //입력된 size가 4라면 R배열의 크기는 2 
                                                //(size - mid = 4 -2 = 2)
		for (int i =0; i < mid; i++)	//S배열을 나누어 L배열 R배열에 적재시킨다.
		{
			L[i] = S[i];
		}
		for (int i = mid; i <size; i++)
		{
			R[i - mid] = S[i];
		}
		mergesort(mid, L);	             //mergesort 함수를 재귀로 구현하여 
                                                     // 값이 한개가 저장될 때까지 분할 한다. 
		mergesort(size - mid, R);
		merge(mid, size - mid, L, R, S); //1개로 분할된 이후 merge 함수를 동작시킨다.
	}
}
int main()
{
	FILE *fin, *fout;				
	int idx = 0;
	int temp = 0;
	char fname[50];				
	printf("파일명을 입력하세요! 합병정렬 결과는 result.txt 로 저장됩니다. \n( 입력 예 : xxx.txt )");
	scanf("%s", &fname);
	//데이터의 개수를 읽어오기 위해 fopen, idx 변수에 데이터 수를 카운트함
	fin = fopen(fname, "rb");     //파일이름은 입력으로 받기
	if (fin == NULL)
	{
		printf("파일명이 없습니다.\n");
		return - 1;
	}
	//파일속에 저장된 데이터의 수를 확인하기위한 반복문  idx에 값 축적
	while (1)
	{
		if (feof(fin) !=0)
			break;
		fscanf(fin, "%d\n", &temp);
		idx++;
	}
	fseek(fin, 0L, SEEK_SET);		//파일 포인터 위치를 처음으로 리셋
	int* arr = new int[idx -1];		//동적 배열 할당 축적된 idx값으로 배열크기 결정
	idx = 0;
	
	while (1)			    //데이터 뽑아서 arr 동적배열에 저장 시키기	
	{
		if (feof(fin) !=0)
			break;
		fscanf(fin, "%d\n", &temp);
		arr[idx] = temp;
		idx++;
	}
	fclose(fin);
	idx = _msize(arr) /4;    //배열의 길이 49999
	mergesort(idx, arr);	     //합병정렬 실시
	fout = fopen("result.txt", "wb");   //정렬된 데이터 result.txt 파일에 저장하기
	for (int i =0; i < idx; i++)
		fprintf(fout, "%d\n", arr[i]);
	printf("정렬이 완료되었습니다 프로젝트 폴더내 result.txt 를 확인하세요 \n");

	return 0;
}


```

### 코드 해설

1. 파일 데이터 불러오기 저장하기 : FILE 형 포인터 변수 fin, fout을 선언한다. 그리고 파일 데이터의 수, 동적 배열크기를 결정 지을 int idx 변수, 값을 저장할 int temp 변수, scanf 로 파일 이름을 입력받아 저장할 char fname[50] 변수를 선언하여 scanf 로 파일명을 입력받아 입력받은 파일명이 abc.txt 라면 abc.txt 파일의 데이터를 라인단위(\n)로 읽어 우선 idx 변수에 카운트를 한다. 이 동작을 수행 하여 동적배열의 크기를 결정 짖고 동적 배열을 만든 후 동적 배열 arr에 abc.txt를 다시 읽어와 라인단위(\n)로 값들을 저장시킨다. 그렇게 5만개의 데이터가 저장된 배열읃 얻게 되며 합병정렬을 수행 후 결과를 다시 파일로 저장시키기 위해 fopen("result.txt", "wb");  함수를 사용하여 result.txt 파일명으로 정렬된 값 들을 저장 시킨다.
2. void mergesort(int size, int S[]) 함수 : 정렬할 배열의 크기와 배열의 시작 주소를 매개변수로 입력 받아서 동작되는 함수로 if(size > 1) 비교 문으로 각 배열의 크기가 1개가 될 때까지 분할 하도록 한다. 입력받은 배열의 중간 값인 mid를 사용하여 좌측 배열 L[mid] , 우측배열 R[size – mid] 2개의 동적배열을 만들고 S배열을 나누어 L배열과 R배열에 적재 시킨다. 이러한 과정을 재귀적 방법을 통하여 구현한다. 그리고 배열의 크기가 1이 되어 다 분할된다면 merge 함수를 호출하도록 한다.
3. void merge(int Lsize, int Rsize, int L[], int R[], int S[]) 함수 : 쪼개진 L배열과 R배열을 정렬하면서 합병하는 함수로 L배열의 인덱스 i 변수, R배열의 인덱스 j , S배열의 인덱스 k를 선언하고 while (i <= Lsize -1 && j <= Rsize –1) 반복문 안에서 두 배열 L배열과 R배열의 값을 비교하여 작은 값을 S배열에 저장시키고 값을 뽑아온 배열의 인덱스를 1증가 시키며 반복문을 돌린다 만약 L배열과 R배열 중 인덱스가 최대 인덱스 크기를 초과할 경우 반복문을 종료 시킨다. 나머지 값은 for(;;)반복문을 더 추가 구성하여 L배열과 R배열의 인덱스가 지정된 배열 크기를 넘어 갔는지 비교하여 넘지 않았을 경우 그 배열에 값이 남아있는 것이므로 값을 뽑아 S배열에 마저 저장한다.


### 코드 실행 결과

<figure>
	<img src="/images/merge2.png" alt="">
</figure>
<figure>
	<img src="/images/merge3.png" alt="">
</figure>