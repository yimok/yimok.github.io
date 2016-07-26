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





