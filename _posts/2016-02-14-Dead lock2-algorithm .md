---
layout: post
title: "[알고리즘]Banker 알고리즘 구현" 
description: "[알고리즘]Banker 알고리즘 구현" 
modified: 2016-02-13
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

C로 Banker 알고리즘 구현해 보았습니다.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Banker 알고리즘

### 코드

아래 표를보고 Banker 알고리즘을 구현하겠습니다.

<figure>
	<img src="/images/ba1.PNG" alt="">
</figure>


```cpp

#include <iostream>  
using namespace::std;

void main() {

	//instance
	int A, B, C;

	// process state check
	bool finish[5] = { false, false, false, false, false };


	//allocation
	int Pall[5][3] = { { 0, 1, 0 }, { 2, 0, 0 }, { 3, 0, 2 }, { 2, 1, 1 }, { 0, 0, 2 } };

	//Max 
	int Pmax[5][3] = { { 7, 5, 3 }, { 3, 2, 2 }, { 9, 0, 2 }, { 2, 2, 2 }, { 4, 3, 3 } };

	//Need = Max - allocation
	int Pneed[5][3];

	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			Pneed[a][b] = Pmax[a][b] - Pall[a][b];
		}

	}


	int available[3] = { 3, 3, 2 }; // available resource

	cout << "Banker's Algorithm \n" << endl;
	cout << "available Resource" << endl;
	cout << "A" << '\t' << "B" << '\t' << "C" << endl;
	cout << available[0] << '\t' << available[1] << '\t' << available[2] << "\n" << endl;
	cout << "Safe Sequence \n ";
	cout << "[" << "   ";


	for (int j = 0; j < 5; j++)
	{
		if (finish[0] == false){
			if (available[0] >= Pneed[0][0] && available[1] >= Pneed[0][1] && available[2] >= Pneed[0][2])
			{
				cout << "process0" << "   ";

				// 사용 가능 자원 - need 
				available[0] = available[0] - Pneed[0][0];
				available[1] = available[1] - Pneed[0][1];
				available[2] = available[2] - Pneed[0][2];

				// 사용 가능 자원 + 제거한 프로세스의 max 자원
				available[0] = available[0] + Pmax[0][0];
				available[1] = available[1] + Pmax[0][1];
				available[2] = available[2] + Pmax[0][2];
				finish[0] = true;
			}
		}
		if (finish[1] == false){
			if (available[0] >= Pneed[1][0] && available[1] >= Pneed[1][1] && available[2] >= Pneed[1][2])
			{
				cout << "process1" << "   ";
				available[0] = available[0] - Pneed[1][0];
				available[1] = available[1] - Pneed[1][1];
				available[2] = available[2] - Pneed[1][2];

				available[0] = available[0] + Pmax[1][0];
				available[1] = available[1] + Pmax[1][1];
				available[2] = available[2] + Pmax[1][2];
				finish[1] = true;
			}
		}
		if (finish[2] == false){
			if (available[0] >= Pneed[2][0] && available[1] >= Pneed[2][1] && available[2] >= Pneed[2][2])
			{
				cout << "process2" << "   ";
				available[0] = available[0] - Pneed[2][0];
				available[1] = available[1] - Pneed[2][1];
				available[2] = available[2] - Pneed[2][2];

				available[0] = available[0] + Pmax[2][0];
				available[1] = available[1] + Pmax[2][1];
				available[2] = available[2] + Pmax[2][2];
				finish[2] = true;
			}
		}
		if (finish[3] == false){
			if (available[0] >= Pneed[3][0] && available[1] >= Pneed[3][1] && available[2] >= Pneed[3][2])
			{
				cout << "process3" << "   ";
				available[0] = available[0] - Pneed[3][0];
				available[1] = available[1] - Pneed[3][1];
				available[2] = available[2] - Pneed[3][2];

				available[0] = available[0] + Pmax[3][0];
				available[1] = available[1] + Pmax[3][1];
				available[2] = available[2] + Pmax[3][2];
				finish[3] = true;
			}
		}
		if (finish[4] == false){
			if (available[0] >= Pneed[4][0] && available[1] >= Pneed[4][1] && available[2] >= Pneed[4][2])
			{
				cout << "process4" << "   ";
				available[0] = available[0] - Pneed[4][0];
				available[1] = available[1] - Pneed[4][1];
				available[2] = available[2] - Pneed[4][2];

				available[0] = available[0] + Pmax[4][0];
				available[1] = available[1] + Pmax[4][1];
				available[2] = available[2] + Pmax[4][2];
				finish[4] = true;
			}
		}
	}
	A = available[0];
	B = available[1];
	C = available[2];

	cout << "]" << endl;
	cout << "\n" << endl;
	cout << "Instance Value" << endl;
	cout << "A" << '\t' << "B" << '\t' << "C" << endl;
	cout << A << '\t' << B << '\t' << C << endl;
}


```

### 결과

<figure>
	<img src="/images/ba2.PNG" alt="">
</figure>


- 위 코드에서는 Safe Sequence 결과가 p1 -> p3-> p4 -> p0 -> p2 로 나옵니다.
- Safe Sequence 결과가 여러개가 나올 수 있으나 제가 구현한 코드 알고리즘에서는 저 순서대로 나오네요
- 어떤 프로세스를 먼저 해제하느냐에 따라 결과가 다르게 나올 수 있겠죠?