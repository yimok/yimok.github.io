
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