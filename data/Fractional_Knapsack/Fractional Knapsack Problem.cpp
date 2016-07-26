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