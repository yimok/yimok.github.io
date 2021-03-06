#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector를 쓰기위한 라이브러리
#include <math.h> //log,floor 사용
#include <time.h> //clock()
#include <iterator> // back_inserter
using std::vector;
int count1 = 0;
int count2 = 0;
#pragma warning(disable:4996)
#define SIZE 502//행렬 사이즈 0인덱스를 제외할거라 +1

//최소 곱셈 알고리즘
//param : 2차 벡터 배열 M,d,P
//return : 없음
void minmult(vector< vector<int> > &M, vector<int> &d, vector< vector<int> > &P)
{
	int i, j, k, diagonal;
	int temp = 0;
	int min,minidx;


	//벡터 생성시 M배열을 0으로 이미 초기화를했음
	//배열인덱스는 1부터 시작한다고 가정한다
	//diagonal변수는 대각선의 위치를 파악하기 위한 변수이다.
	//만약 diagonal이 1이라면 정중앙에 있는 대각선 한단계 위 대각선을 말한다.
	//즉 diagonal 값을 행렬의 사이즈에서 뺼셈하여 i의 범위를 정하고, j값을 현재 i의 값에 diagonal을 더하여 
	//대각선위치의 배열을 건드릴 수 있게 만든다.
	//다시말해서 상삼각행렬만 필요하므로 중앙 대각선 아래의 값을 필요없다.
	for (diagonal = 1; diagonal <= d.size() - 1; diagonal++)
	{
		for (i = 1; i < d.size() - diagonal; i++)
		{
			j = i + diagonal;
			// 맨처음 min값에 무조건 넣기위해 큰값으로 초기화
			min = 100000000;  



			//M[i][j] = minimum(M[i][k] + M[k+1][j] + di-1 * dk * dj) 구현  범위 i <= k <= j-1 
			//i와 j를 를 기준으로 k값을 구한다.
			//만약 M[1][4] 의 곱셈의 횟수를 구하여 저장하려면
			//temp = M[1][1]+M[2][4] + d[0]*d[1]*d[4]
			//temp = M[1][2]+M[3][4] + d[0]*d[2]*d[4]
			//temp = M[1][3]+M[4][4] + d[0]*d[3]*d[4]
		    //즉 k값을 변경하면서 얻은 곱셈 횟수를 temp 에 저장하여 
			//min 변수와 비교를하면서 작을경우 min에 저장하고
			//최종적으로 for문을 다돌면 최소곱셈횟수와, 최소값을 주는 k의 위치를 저장한다.
			for (k = i; k <= j - 1; k++)
			{
				//각 인수를 구하는 곱셈 횟수 ,+ 두 인수를 곱하는데 필요한 곱셈의 횟수
				temp  = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];


				
				if (min > temp)
				{
					min = temp;     //곱셈 횟수 저장
					minidx = k; 	//최소값을 주는 k의 위치를 저장한다
				
				}
			}
			
		
			M[i][j] = min;
			P[i][j] = minidx;
		}
	}
}
	


// 바이너리 파일을 읽어와 벡터 1차원 배열에 저장시키는 함수.
// parameter : 읽은 값을 저장시킬 vector 주소 , 파일명, 사이즈
// return : 없음
void MatrixInit(vector<int> &matrix, char * fname, int num)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	int idx = 0;
	int temp = 0;

	if (fin == NULL)
	{
		printf("파일명이 없습니다.\n");
		return ;
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
	
	idx = 0;
	//총 501개의 데이터를 읽음
	for (int i = 0; i <= num-1; i++)
	{

		//arr에 읽어온 데이터들을 벡터 배열로 저장
		matrix[i] = arr[idx];
		idx++;
	}


	fclose(fin);

}



// 최적의 순서를 출력해주는 함수 
// parameter : 파일 포인터 fout, 벡터 P주소, 행 p, 열 r 
// return : 없음
void Order(FILE *fout, vector< vector<int> > &P, int q, int r)
{
	int k;

	if (q == r)
		fprintf(fout, "A%d", q);
	else
	{	
		k = P[q][r];
		fprintf(fout, "(");
		Order(fout, P, q, k);
		Order(fout, P, k+1, r);
		fprintf(fout, ")");
	}

	

}

int main()
{
	int Row = SIZE;
	int Col = SIZE;
	char fname1[50], fname2[50];
	int start, end; //시간측정


	// ex) vector<vector<int> >  arr(6, vector<int>(5, 0));
	// 설명: vector< vector<int> > 형 벡터 6개(가로 6줄)를 할당 한다는 뜻
	//       vector<int>(5,0) 은 모든 가로줄은 5개짜리 0으로 초기화 된 익명의 int 형 벡터 배열을 생성해 초기값을 넣는다.
	vector < vector<int> > M(Row, vector<int>(Col, 0)); 
	vector < vector<int> > P(Row, vector<int>(Col, 0)); 
	vector<int>  d(SIZE - 1, 0); 

	
	printf("연쇄행렬 최소곱셈을 구하는 알고리즘입니다.\n");
	printf("계산중 .... \n");
	MatrixInit(d, "arr.txt", 501);
    minmult(M, d, P);
	FILE *fout;
	fout = fopen("result.txt", "wt");

	Order(fout, P, 1, 500);
	printf("계산이 완료되었습니다. 결과는 result.txt에 저장되었습니다.\n\n");
	
	return 0 ;
}