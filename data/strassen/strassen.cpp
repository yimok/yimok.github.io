#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector를 쓰기위한 라이브러리
#include <math.h> //log,floor 사용
#include <time.h> //clock()
using std::vector;

#pragma warning(disable:4996)
#define SIZE 1024 //행렬 사이즈

// 바이너리 파일을 읽어와 벡터 2차원 배열에 저장시키는 함수.
// parameter : 읽은 값을 저장시킬 vector 주소 , 파일명, , 행사이즈, 열사이즈 
// return : 없음
void MatrixInit(vector< vector<int> > &matrix, char * fname, int Row, int Col)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	char * arr = new char[Row*Col];
	int idx = 0;

	if (fin == NULL)
	{
		printf("파일명이 없습니다.\n");
		return;
	}

	if (fread(arr, Row*Col, 1, fin) != 1)
	{
		printf("에러");
		exit(1);
	}


	for (int i = 0; i <= Row - 1; i++)
	{
		for (int j = 0; j <= Col - 1; j++)
		{
			matrix[i][j] =  arr[idx];
			idx++;
		}

	}
	fclose(fin);

}


// 행렬 A와 B를 더하여 C에 저장시키는 함수(A행렬 B행렬 C행렬은 같은 크기)
// parameter :행렬 A,B,C 
// return : 없음
void MatrixSum(vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{

	for (int i = 0; i < (int)matrixA.size(); i++) // matrixA.size() = 행 길이
	{
		for (int j = 0; j< (int)matrixA[i].size(); j++) // matrixA.size() = 열 길이
		{
			matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}

}

// 행렬 A와 B를 빼서 C에 저장시키는 함수(A행렬 B행렬 C행렬은 같은 크기)
// parameter : 행렬 A,B,C 
// return : 없음
void MatrixSub(vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{
	for (int i = 0; i < (int)matrixA.size(); i++) // matrixA.size() = 행 길이
	{
		for (int j = 0; j< (int)matrixA[i].size(); j++) // matrixA.size() = 열 길이
		{
			matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
		}
	}


}

// 행렬 A와 B를 곱하여 C에 저장시키는 함수(A행렬 B행렬 C행렬은 같은 크기)
// parameter : 행렬 A, B, C 
// return : 없음
void MatrixMul(vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{
	for (int i = 0; i < (int)matrixA.size(); i++) // matrixA.size() = 행 길이
	{
		for (int j = 0; j< (int)matrixA[i].size(); j++) // matrixA.size() = 열 길이
		{
			for (int k = 0; k < (int)matrixA[i].size(); k++)
			{
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}


}





// 임계값 구하는 함수
// parameter : 행렬의 가로 및 세로 길이 (ex:1024)
// return : 임계값 반환
int getThreshold(int n)
{
	int th;
	double k = floor(log(n) / log(2) - 6);
	th = (int)floor(n / pow(2.0, k)) + 1;
	return th;
}


// 4개의 부분행렬로 나누는 함수
// parameter : 나눌 행렬, 저장할 행렬 공간 4개
// return : 없음
void Submatrix(vector< vector<int> > &matrixOrigin, vector< vector<int> > &matrix11, vector< vector<int> > &matrix12,
	vector< vector<int> > &matrix21, vector< vector<int> > &matrix22)
{
	int newNum = matrix11.size();  //부분행렬의 사이즈 

	for (int i = 0; i < newNum; i++)
	{
		for (int j = 0; j < newNum; j++)
		{
			matrix11[i][j] = matrixOrigin[i][j];						//좌 상단행렬
			matrix12[i][j] = matrixOrigin[i][j + newNum];				//우 상단행렬
			matrix21[i][j] = matrixOrigin[i + newNum][j];				//좌 하단행렬
			matrix22[i][j] = matrixOrigin[i + newNum][j + newNum];		//우 하단행렬
		}
	}

}


// 4개의 부분행렬들을 재결합 해주는 함수
// parameter : 합친 결과를 저장할 행렬 , 부분행렬 11, 12, 21, 22
// return : 없음
void Mergematrix(vector< vector<int> > &matrixOrigin, vector< vector<int> > &matrix11, vector< vector<int> > &matrix12,
	vector< vector<int> > &matrix21, vector< vector<int> > &matrix22)
{
	int newNum = matrix11.size();  //부분행렬의 사이즈

	for (int i = 0; i < newNum; i++)
	{
		for (int j = 0; j < newNum; j++)
		{
			matrixOrigin[i][j] = matrix11[i][j];						//좌 상단행렬
			matrixOrigin[i][j + newNum] = matrix12[i][j];				//우 상단행렬
			matrixOrigin[i + newNum][j] = matrix21[i][j];         	    //좌 하단행렬
			matrixOrigin[i + newNum][j + newNum] = matrix22[i][j];	    //우 하단행렬
		}
	}


}





// 쉬트라센 알고리즘 함수
// parameter : 행렬의 사이즈(ex: 1024x1024 -> 1024입력) , 행렬 A, B, C
// return : 없음
void Strassen(int n, vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{


	if (n <= getThreshold(n))
	{
		MatrixMul(matrixA, matrixB, matrixC);
		return;
	}
	else
	{
		int newRow = n / 2;					//4등분을 하기 위해
		vector<int> newCol(newRow, 0);

		//a11~a22 부분행렬, b11~b22 부분행렬 
		vector < vector<int> > a11(newRow, newCol), a12(newRow, newCol), a21(newRow, newCol), a22(newRow, newCol);
		vector < vector<int> > b11(newRow, newCol), b12(newRow, newCol), b21(newRow, newCol), b22(newRow, newCol);

		//부분행렬들의 연산결과를 m1~m7 에저장
		vector < vector<int> > m1(newRow, newCol), m2(newRow, newCol), m3(newRow, newCol), m4(newRow, newCol)
			, m5(newRow, newCol), m6(newRow, newCol), m7(newRow, newCol);

		//a11~b22 의 연산결과들을 임시로 저장할 그릇
		vector < vector<int> > tempA(newRow, newCol), tempB(newRow, newCol);

		// m1~m7 연산 결과로 C를 구하기 위해 저장 할 행렬
		vector < vector<int> > c11(newRow, newCol), c12(newRow, newCol), c21(newRow, newCol), c22(newRow, newCol);


		//A의 부분행렬 4개, B의 부분행렬 4개 생성
		Submatrix(matrixA, a11, a12, a21, a22);
		Submatrix(matrixB, b11, b12, b21, b22);


		MatrixSum(a11, a22, tempA);		       // a11+a22
		MatrixSum(b11, b22, tempB);		       // b11+b22
		Strassen(newRow, tempA, tempB, m1);    // m1=(a11+a11)(b11+b22)
		
		MatrixSum(a21, a22, tempA);            // a21+a22
		Strassen(newRow, tempA, b11, m2);      // m2=(a21+a22)b11

		MatrixSub(b12, b22, tempB);            // b12-b22
		Strassen(newRow, a11, tempB, m3);      // m3=a11(b12-b22)

		MatrixSub(b21, b11, tempB);            // b21-b11
		Strassen(newRow, a22, tempB, m4);      // m4=a22(b21-11)

		MatrixSum(a11, a12, tempA);            //  a11+a12
		Strassen(newRow, tempA, b22, m5); 	   // m5=(a11+a12)b22

		MatrixSub(a21, a11, tempA);            // a21-a11
		MatrixSum(b11, b12, tempB);            // b11+b12
		Strassen(newRow, tempA, tempB, m6);    // m6=(a21-a11)(b11+b12)

		MatrixSub(a12, a22, tempA);            // a12-a22
		MatrixSum(b21, b22, tempB);            // b21+b22
		Strassen(newRow, tempA, tempB, m7);    // m7 = (a12 - a22)(a12 - a22)




		// 위에서 계산된 m1~m7 결과로  c11 ~ c22 를 만든다.
		MatrixSum(m1, m4, tempA); //m1 + m4
		MatrixSum(tempA, m7, tempB); //m1 + m4 + m7
		MatrixSub(tempB, m5, c11); //c11 = m1 + m4 - m5 + m7

		MatrixSum(m3, m5, c12); //c12 = m3 + m5

		MatrixSum(m2, m4, c21); //c21 = m2 + m4

		MatrixSum(m1, m3, tempA); //m1 + m3
		MatrixSum(tempA, m6, tempB); //m1 + m3 + m6
		MatrixSub(tempB, m2, c22); //c22 = m1 + m3 - m2 + m6



		//재 병합
		Mergematrix(matrixC, c11, c12, c21, c22);


	}
}


void FileOutput(char *fname, vector< vector<int> > &matrix)
{
	FILE *fout;
	fout = fopen(fname, "wt");   

	for (int i = 0; i < (int)matrix.size(); i++)
	{
		for (int j = 0; j < (int)matrix.size(); j++)
		{
			fprintf(fout, "%d  ", matrix[i][j]);
		}
		fprintf(fout, "\n");
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

	vector < vector<int> > A(Row, vector<int>(Col, 0)); // A[Row][Col] 인 동적 배열
	vector < vector<int> > B(Row, vector<int>(Col, 0)); // B[Row][Col] 인 동적 배열
	vector < vector<int> > C(Row, vector<int>(Col, 0)); // C[Row][Col] 인 동적 배열
	vector < vector<int> > D(Row, vector<int>(Col, 0)); // D[Row][Col] 인 동적 배열

	printf("A행렬에 입력할 파일명을 입력하세요 \n( 입력 예 : xxx.txt )");
	scanf("%s", &fname1);
	printf("B행렬에 입력할 파일명을 입력하세요 \n( 입력 예 : xxx.txt )");
	scanf("%s", &fname2);


	MatrixInit(A, fname1, Row, Col);
	MatrixInit(B, fname2, Row, Col);

	start = clock();
	MatrixMul(A, B, D);
	end = clock();
	printf("Navie matrix multiplication time : %f ms \n", (double)(end - start));

	start = clock();
	Strassen(A.size(), A, B, C);
	end = clock();
	printf("Strassen matrix multiplication time : %f ms \n", (double)(end - start));

	FileOutput("Navie result.txt", D);
	FileOutput("Strassen result.txt", C);
	printf("무식한 방법 결과가 Navie result.txt에 저장되었습니다. \nStrassen 방법이 Strassen result.txt에 저장되었습니다.\n\n");
	

	return 0;
}