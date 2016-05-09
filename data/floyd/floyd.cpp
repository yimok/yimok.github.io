#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector를 쓰기위한 라이브러리
#include <math.h> //log,floor 사용
#include <time.h> //clock()
#include <iterator> // back_inserter
using std::vector;

#pragma warning(disable:4996)
#define SIZE 100 //행렬 사이즈

// 그래프의 인접행렬 W, 최단경로를 저장할 D, 한 정점과 끝정점 사이에 지나가는 정점중 가장 큰 인덱스가 저장된 P  
// parameter : W,D,P 2차원 벡터 주소
// return : 없음
void floyd(vector< vector<int> > &matrixW, vector< vector<int> > &matrixD, vector< vector<int> > &matrixP)
{
	int i, j, k;
	
	std::copy(matrixW.begin(), matrixW.end(), matrixD.begin());  //배열 카피 D = W
	
	for (i = 0; i < (int)matrixW.size(); i++)     //배열의 사이즈만큼 반복문을 돌린다.
	{
		for (j = 0; j < (int)matrixW.size(); j++)
		{
			matrixP[i][j] = 0;    //0으로 초기화를 시켜줌 
		}
	}


	for (k = 0; k < (int)matrixW.size(); k++)   // 경로사이의 거쳐가는 정점
	{
		for (i = 0; i < (int)matrixW.size(); i++)  // 출반 정점
		{
			for (j = 0; j < (int)matrixW.size(); j++)  // 도착 정점
			{
				if (matrixD[i][k] + matrixD[k][j] < matrixD[i][j]) // 만약 원래 가중치 값보다 작을 경우
				{
					matrixP[i][j] = k;  //P에 가장 마지막에 지나간 정점 즉 k를 저장(가장 큰 인덱스)
					matrixD[i][j] = matrixD[i][k] + matrixD[k][j]; //k를 거쳐가는 가중치가 더 작을경우 새로운경로 가중치로 입력
				}
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
	char * arr = new char[Row*Col*3];
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
	for (int i = 0; i <= Row*Col*3 - 1; i=i+3)
	{

		//fread로 arr에 읽어온 데이터들중 첫번째를 행, 두번째를 열, 그리고 3번째는 가중치이므로 
		//matrix[arr[i]][arr[j]] = arr[idx]; 와 같이 배열에 저장시킨다.
		matrix[arr[i]][arr[j]] = arr[idx];
		j = j + 3;
		idx=idx + 3;
	}
	fclose(fin);

}


// 시작 정점과 끝 정점 사이의 지나간 정점을 표현해주기위한 재귀함수 
// parameter : 파일 포인터 fout, 벡터 P주소, 시작정점 q, 끝정점 r 
// return : 없음
void OutFilePath(FILE *fout, vector< vector<int> > &P, int q, int r)
{
	if (P[q][r] != 0)
	{	
		OutFilePath(fout, P, q, P[q][r]);
		fprintf(fout, "%d->", P[q][r]);
		OutFilePath(fout, P, P[q][r], r);
	}

}


// OutFilePath 함수를 호출하여 두 정점 사이의 지나간 정점들을 저장시키는 함수
// parameter : 파일명 , 벡터 P 주소
// return : 없음
void PathOutput(char *fname, vector< vector<int> > &P)
{
	FILE *fout;
	fout = fopen(fname, "wt");

	for (int i = 0; i < (int)P.size(); i++)
	{
		for (int j = 0; j < (int)P.size(); j++)
		{
			fprintf(fout, "[시작:%d]->", i);
			OutFilePath(fout, P, i, j);
			fprintf(fout, "[도착:%d]  ", j);
			fprintf(fout, "\n"	);
		}

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
	vector < vector<int> > W1(Row, vector<int>(Col, 0)); // W1[Row][Col] 인 동적 배열
	vector < vector<int> > D1(Row, vector<int>(Col, 0)); // D1[Row][Col] 인 동적 배열
	vector < vector<int> > P1(Row, vector<int>(Col, 0)); // P1[Row][Col] 인 동적 배열
	
	vector < vector<int> > W2(Row, vector<int>(Col, 0)); 
	vector < vector<int> > D2(Row, vector<int>(Col, 0)); 
	vector < vector<int> > P2(Row, vector<int>(Col, 0)); 


	printf("Floyd 알고리즘을 사용하여 최단경로를 탐색합니다.  \n");

	MatrixInit(W1, "denseG.txt", Row, Col);
	MatrixInit(W2, "sparseG.txt", Row, Col);
	printf("deseG 와 sparseG 최단경로 탐색중 ....\n");
	floyd(W1, D1, P1);
	floyd(W2, D2, P2);

	PathOutput("result denseG.txt", P1);
	PathOutput("result sparseG.txt", P2);

	printf("최단경로 탐색이 완료되었습니다.\n결과는 result denseG.txt , result sparseG.txt 로 저장되었습니다. \n\n");

	return 0;
}