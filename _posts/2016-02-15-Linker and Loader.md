---
layout: post
title: "[OS]컴파일 & 링킹 & 로더 과정" 
description: "[OS]컴파일 & 링킹 & 로더 과정" 
modified: 2016-02-15
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

소스코드가 어떻게 컴파일 되고 링킹 되는지 그 과정을 알아 보겠습니다.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## 프로그램이 빌드되는 과정

<figure>
	<img src="/images/build.PNG" alt="">
</figure>


- 각각 의 소스파일들이 .O (오브젝트 파일로) 변환이 되고 
- 여러개의 오브젝트 파일이 하나의 오브젝트 파일로 묶이는데 이것을 Linker라고 한다.
- 이렇게 하나의 오브젝트파일로 묶인 파일을 Executable File 이라고 한다.
- 이렇게 생긴 exe 파일을 실행시키면 OS의 로더에 의해서 메모리에 깔리게 되고
- 그 프로세스들에게 필요한 Context들이 생겨나면서 프로그램이 수행 가능하게 된다.

### 소스 파일 

- 사람이 읽을 수 있는 문법들 (C , JAVA)

### 오브젝트 파일

- 수행 코드, 데이터 들이 저장되어 있다.
- 또 이런 수행코드, 데이터들이 메모리 어디에 저장되어야 하는지 알려주는 주소 정보들이 있다. 
- 그리고 여러 변수들의 정보 등등..이 저장되어있는 Symbol Table이 있다.
- Linker가 프로그램을 Linking 하기 위해 사용하는 정보가 있는데 그 정보들이 저장된 테이블을 Relocation Table 이라 한다.

### 컴파일러

- 각 소스파일을 오브젝트파일로 변환 시켜주는 역할을 한다.

### 링커

- 모든 오브젝트 파일들을 하나의 오브젝트 파일로 합친다(Executable file로 합친다)

### 로더

- Executable file 을 읽는다.
- 메인 메모리에 오브젝트 파일에있는 내용들을 올리고
- context들을 만들고 프로그램을 수행시킬 수 있도록 만든다.
- OS의 한 부분이다.

## Section

- 컴파일러를 거쳐 만들어진 오브젝트 파일 안에는 여러개의 Section이 존재한다.
- 오브젝트 파일을 구성하는 Unit 들 또는 어떠한 데이터를 묶어놓은 단위들을 Section 이라 한다.
- 각 섹션들은 추후 메모리에 적재될 독자적인 영역을 가지게 된다. -> 이 영역을 
- 라고 부른다.
- 각 섹션안에는 함수이름이나, 변수이름등 , 여러 심볼들이 존재하고 그 섹셕안에서 자신만의 위치인 offset을 주소로 가진다.

### 오브젝트 파일을 구성하는 Section 들

- Text section(Code section) : 명령어들이 들어가 있다.(ex: printf("hello); )
- Data section : 초기화 된 전역 변수들이 저장되어 있다.(ex: int a = 0;)
- BSS section : 초기화 되지 않은 전역 변수들이 저장되어 있다.(ex: int b;) -> BSS:Block Started by Symbol
- Ohter section : Relocation table , Sybol table 등이 저장됨

### 왜 BSS 와 Data 섹션을 구분 하였을까?

- 변수 선언을 하고 값을 넣어 초기화를 하면 메모리에 그만큼의 공간을 잡아 먹는다(ex:int a = 4; 는 4바이트 공간을잡음)
- 그런데 만약 int a[100000] 과 같은 배열을 선언만하고 초기화 하지 않았다고 하자  400000 바이트의 공간을 쓸데 없이 잡아먹을 필요가 없기 때문에 그냥 저 변수의 이름과 얼마만큼 크기를 잡았다는 정보만 올려주기 위해 BSS 와 Data 섹션을 구분지어서 사용한다.


### .c 파일이 컴파일 되는 과정

<figure>
	<img src="/images/Section.PNG" alt="">
</figure>

- .c 파일이 컴파일러를 통해 .o 파일로 변환되는 과정
- 소스코드들이 각 섹션으로 배치된다.

### .o 파일들을 링킹 하는 과정

<figure>
	<img src="/images/Linker.PNG" alt="">
</figure>

- 여러 오브젝트 파일에있는 동일한 섹션들을 하나의 덩어리로 합친다.
- 이때 각 섹션들을 몇 번지에 저장하라고 하는 별도의 파일이 있는데 이것을 **링커 스크립트** 파일이라고 한다.
- 예를 들어 특정 하드웨어(임베디드 시스템)의 메모리 앞부분 1mb 가 ROM이라고 하면 이 부분 다음부터 섹션을 적재 시켜야 하므로 링커 스크립트 파일을 이용하여 설정해줄 수 있다.
- 링킹이 끝나면 Executable File이 생성된다.

### Loader 가 Exe파일을 읽어들이는 과정

- OS Loader가 exe파일을 읽는다.
- 이미 exe 파일에는 Data section은 몇번지에 저장하고, Code section은 몇번지에 저장하라는 정보들이 다 들어있기 때문에 그대로 읽어 오면 된다.
- 그리고 마지막으로 PC(Program Counter)를 그 exe파일의 엔트리 포인트로 설정하면 로딩이 끝난다.

## 링킹 과정의 문제점

- 우리가 소스코드로 코딩할때는 우리가 읽을 수 있는 문자,부호 들을 사용하지만 실제 컴퓨터가 읽을때는 010101 로 읽는다.
- 결국 실제로 마이크로프로세서는 문자들을 읽는것이 아니라 이것의 OP코드와 , 오퍼랜드의 주소, 등을 본다.
- 즉 다시말해서 우리가 입력한 Symbol(문자,부호)들을  주소로 변환 하여야 한다.
- 그런데 Symbol 이 주소로 변환되려면 이 Symbol이 실제 어느 위치에 있는지 알아야 하는데 이 위치를 안다는 것은 쉬운 일이 아니다.
- C는 소스 파일이 여러개로 쪼개져 있고 링킹 하기 전에 오브젝트 파일도 여러개로 쪼개져 있기 때문에 컴파일러가 한 오브젝트 파일을 만지고 있는 동안 다른 오브젝트 파일의 Symbol 주소를 알 수가 없다. 이것을 **Cross-reference**라고 한다.
- 이 Cross-refernce를 해결하는 것이 링커의 몫이다.

### Cross-refernce 해결 방법

- Cross-refernce 에 대한 정보가 여러 오브젝트 파일에 흩어져 있으므로 각 오브젝트 파일을 다니면서 주소들을 수집해야 한다.
- 그리고 나서 수집된 주소들을 이용해서 실제 주소들로 대체한다.
- 링커가 이 문제를 해결하려면 path를 2개 이상 사용해야 링킹을 할 수 있다.

### Symbol Table

<figure>
	<img src="/images/Linker2.PNG" alt="">
</figure>

- Symbol들의 주소와 정보들을 쉽게 찾을 수 있도록 한곳에 모아 둔 테이블이다.
- 위 그림과 같이 코드를 변환 하는 작업이 필요한데 이때 Symbol Table을 사용한다.

<figure>
	<img src="/images/symbol table.PNG" alt="">
</figure>

- Symbol Table의 정보를 검색할때는 Symbol의 이름으로 검색 한다.
- 테이블에는 각 심볼이 포함된  Section의 시작 주소와 그 심볼의 Section내 offset이 기입되어 있다.
- 정리하자면 컴파일러가 어떤 심볼을 읽게 되면 그 심볼에 해당하는 진입점을 테이블에 넣고 그 심볼의 주소를 알 수 있으면 Section 주소와 offset으로 채워 넣는다. 이러한 주소를 Internal Reference 라고 한다.
- 이때 주소를 알 수 있다는 것은 자신과 같은 오브젝트 파일을 생성 할때 알 수 있다는 말이다.

### Relocation Table(1)

- Section 시작주소 + offset 주소로 파악된 symbol 주소(Internal Reference)를 PC Relative 한 주소로 변환한다. 즉 PC 상대주소로 변환한다.
- 이런 변환을 하는 이유는 전체 section의 위치가 변경 되어도 PC로부터의 상대적인 주소(거리)는 바뀌지 않기 때문이다.
- 그래서 PC Relative 한 주소로 변환하여 사용한다.
- ex) call local_func   ->  call PC+0x1B	

### Relocation Table(2)

- 그럼 Cross reference 들은 어떻게 처리 할까?
- 링커가 Cross reference 들의 주소를 모르기 때문에 모른다고 체크(0으로 채운다)해놓고 Internal Reference 를 우선적으로 처리한다.
- ex) call printf -> call 0x0
- 추가적으로 Relocation Table에 이 Cross reference의 위치를 기입한다.

### Relocation Table Example(1)

<figure>
	<img src="/images/Relocation Table1.PNG" alt="">
</figure>

※ c언어의 extern 키워드는 해당 변수가 외부의 다른 파일에서 정의 되었다는것을 알려주는 것이다.

- 컴파일을 하면 맞는 섹션에 소스코드가 적재가 되고 오브젝트 파일들이 만들어진다. 
- my_var, func() 둘다 Cross Reference 이므로 정확한 주소를 몰라 일단 0x0 으로 초기화한다.
- 그런 후 Text 섹션의 시작위치와 mov, call의 명령어의 섹션내 offset을 Relocation Table에 적재 시킨다. 
- 링커의 첫번째 path 에서 이러한 과정으로 Relocation Table을 생성한다.

<figure>
	<img src="/images/Relocation Table2.PNG" alt="">
</figure>

- 링커 스크립트에 의해 섹션들이 합병되면 각 작은 섹션들의 위치를 알 수 있고
- 마찬가지로 그 작은 섹션 안에 있는 Symbol 들의 주소 정보들역시 파악할 수 있어 Symbol Table 에 적재 시켜 놓는다.
- 이전에 Relocation Table에 적재 시켰던 Symbol Name 을 가지고 Symbol Table 에 가서 그 Symbol의 메모리 주소를 찾아 가져와서 고친다.

### Relocation Table Example(2)

<figure>
	<img src="/images/Relocation Table3.PNG" alt="">
</figure>

- 소스코드가 2개의 .c 파일로 되어있다.
- 우선 main.c 를 컴파일 하면 아래와 같은 결과가 나온다.

<figure>
	<img src="/images/Relocation Table4.PNG" alt="">
</figure>

- lib.c를 컴파일 하면 아래와 같은 결과가 나온다.

<figure>
	<img src="/images/Relocation Table5.PNG" alt="">
</figure>

- extern 변수가 없으므로 Relocation Table은 존재하지 않는다.

<figure>
	<img src="/images/Relocation Table6.PNG" alt="">
</figure>

<figure>
	<img src="/images/Relocation Table7.PNG" alt="">
</figure>

- 링커가 링킹을 하게되면 각 작은 섹션들의 위치를 정해준다.
- 이렇게 각 심볼들의 주소들을 계산할 수 있게 된다.

<figure>
	<img src="/images/Relocation Table8.PNG" alt="">
</figure>

- 마지막으로 흩어져있는 오브젝트 파일들을 읽어서 동일한 섹션들을 묶어서 하나의 exe 파일로 만든다.

##정리

- Code Segment 와 Data Segment 는 무엇일까?
- 위에서 설명한것처럼 링킹을 통해 exe 파일을 만들면 각 섹션들이 존재한다(Code Section, data section) 이 섹션들이 같은 이름의 세그먼트 영역에 로드되어 프로그램이 실행된다.
- 즉 Code section -> Code Segment , Data section -> Data segment
- BSS Section 은 Data Segment에 합병이 된다.
- Stack Segment, Heap Segment는 로더가 프로그램을 로딩 하는 시점에 빈 스택과 힙을 만들어준다.
- Code Segment 와 Data Segment 는 프로그램이 로딩될때 한번 할당된다. 그리고 프로그램이 종료될때 반환된다. -> Static Storage Allocation
- Stack Segment, Heap Segment 은 다이나믹하게 할당 받는다 -> Dynamic Storage Allocation