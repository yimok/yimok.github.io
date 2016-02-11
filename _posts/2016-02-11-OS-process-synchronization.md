---
layout: post
title: "[OS]Process Synchronization"
description: "[OS]프로세스 동기화" 
modified: 2016-02-12
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

Process의 동기화가 무엇인지를 알아보고 Process Synchronization 에 따른 문제점이 무엇인지 또 그러한 문제점을 해결하는 방안이 무엇인지 알아보자.  

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## 프로세스 동기화

- 프로세스 동기화는 프로세스들이 한 시스템에 여러 개 있는 다중 프로그래밍 시스템에서 필요한 기술이다. 다중 프로그래밍은 프로세스 여러 개가 동시에 수행되는 것을 말한다.
- 여러 프로세스들이 같은 프로세서 혹은 입출력 장치를 공유하여 사용하기도 하는데 이때 이 프로세스들이 동시에 한 자원을 공유하여 사용하면 여러 문제가 발생된다.
- 이러한 문제를 해결하기 위해 프로세스 끼리 동기화를 시켜서 자원이 순서대로 사용될 수 있게 하는 것 을 프로세스 동기화(Process Synchronization)라 한다.
- 쉽게 말해서 Process Synchronization은 여러 프로세스들이 서로 interaction 할 때 발생한다.  

### Process interacting의 특징

- Process interacting 을 하면 자원과 컴퓨터 시스템의 상태(메인 메모리, 레지스터 들에 저장된 상태)를 서로 공유한다.
- 프로세스의 수행이 Non-deterministic해 진다. -> 같은 입력을 넣어도 경우에 따라 다른 결과가 나온다. 다시 말해서  프로세스의 수행의 결과가 같을 수 없다.

### 왜 프로세스는 서로 interaction을 하는가?

1. 어떤 소프트웨어 시스템을 설계하게 되면 여러 조각(Decomposition)으로 만들고 각각의 조각을 독립적으로 개발한다. 그 결과로 여러 프로세스가 나오게 된다. 즉 시스템이 복잡해지면 모듈러 디자인을 해서 구성된 프로세스들 끼리 서로 상호 작용을 하여 하나의 소프트웨어를 구성하게 된다.
2. Concurrency(병렬성)를 높이기 위해서이다. -> 웹 브라우를 싱글 Thread로 만들면 그 Thread가 시간이 오래 걸릴 경우 다른 일들을 처리하지 못한다. 하지만 Thread를 여러 개 두면, 다시 말해서 Concurrency를 높이면 다른 Thread들이 또 다른 일을 처리해 줄 수 있다.
3. 자원 공유를 통해 오버헤드를 줄일 수 있다. 

### interaction의 문제점 1

```
static int iValue[2];

void interrupt ReadVemp(void){
	iValue[0]  =  센서로 부터 값을 읽어옴;
	ivalue[1]  =  센서로 부터 값을 읽어옴;
}

void main(void)
{
	int iV0, iV1;

	while(TRUE)
	{
		iV0 = iValue[0];
		iV1 = iValue[1];
		if(iV0 != iV1)
			고장이 날수 있다고 경고를 울림;
	}
}
 

```

- 위 코드는 interaction의 문제점을 설명하기위에 제시된 코드이다.
- 센서로 부터 값을 읽어 업데이트하는 인터럽트 서비스 루틴 과 읽어들인 값을 이용하여 특정 조건에 따라 경고를 울리는 유저 프로세스 부분으로 구성된 코드이다.
- 하지만 위 코드와 같이 인터럽트 서비스 루틴과 프로세스가 함께 Interaction 하면서 작동하게 되면 올바른 계산 결과를 내지 못하는데 이런 상황을 Non-Reentrant Code 라고 한다.
- 위 코드에서 ISR 부분과 main으로 작성된 유저 프로세스가 서로 경합을 하면서 자원을 공유하려 한다.(iValue[] 배열자원)

```
//Solution

static int iValue[2];

void interrupt ReadVemp(void){
	iValue[0]  =  센서로 부터 값을 읽어옴;
	ivalue[1]  =  센서로 부터 값을 읽어옴;
}

void main(void)
{
	int iV0, iV1;

	while(TRUE)
	{
		disalbe();   // Disable interrupts using array
		iV0 = iValue[0];
		iV1 = iValue[1];
		enable();
		if(iV0 != iV1)
			고장이 날수 있다고 경고를 울림;
	}
}
 

```

인터럽트를 disable 시키면 유저프로세스가 수행될 때 인터럽트에 의해 쪼개지지 않아 Reentrant Code가 되어 올바르게 작동한다.

>Reentrant Code(재진입 가능 코드):
>여러 Process 들에 의해 동시에 호출되거나, 이전 호출이 완료되기 전에 반복 호출되어도 올바르게 수행되 코드

### interaction의 문제점 2

```
// Buffer

if(BufferFlag)
{
	BufferFlag = FALSE;
	UseBuffer();
	BufferFlag = TURE;
}


```

- BuffeFlag을 FALSE로 만들고 버퍼를 사용하고 TRUE로 만든다.
- 여러 프로세스들이 버퍼를 두고 if 문을 두어 사용한다.
- 하지만 프로세스가 공유하는 자원은 버퍼 말고도 BufferFlag 라는 변수도 공유 하기 때문에  아래와 같은 문제가 발생한다.

<figure>
	<img src="/images/post2-1.PNG" alt="">
</figure>

- proc 1 이 아직 FALSE로 바뀌기 전에 proc 2가 진입을 해버려서 두 프로세스가 버퍼를 사용하는 문제가 발생한다.
- 위와 같은 코드를 Race Condition 이라고 볼 수 있다.

>Race Condition(경합 조건) : 여러 프로세스들이 동기화 절차를 거치지 않고 동시에 자원을 사용하기 위해 경쟁함으로써 그 수행 결과를 예측할 수 없게 되는 상황

### 정리

Process Synchronization 이란 interaction 하는 프로세스들이 한 자원을 공유하는 것 이라고 하며 OS 가 아무런 조작을 하지 않으면 문제가 발생하는 것을 Synchronization 문제라고 한다. 

## Synchronization 문제 해결방법

- 자원을 공유하는 코드 구간을 Atomic 하게 만들어야한다. -> ex) 인터럽트를 disable 한다.
- 인터럽트를 disable 함으로써 Atomic 하게 만들었다. 하지만 이건 프로세스와 인터럽트와 의 문제이고 프로세스와 프로세스 사이의 문제는 어떻게 해결해야할지 생각해보자.
-  과거에 배운 내용 중 Context Switching을 생각해 보자 이 Context Switching 이 발생되려면 인터럽트가 발생되어야한다. 즉 인터럽트를 disable 하면 Context Switching 이 발생되지 않는다.
- 프로세스들이 서로 경합 할 때도 인터럽트를 disable 하면 Context Switching 이 발생되지 않는다. (싱글 프로세서에서만)
- Critical Section 안에서는 하나의 프로세스만 실행할 수 있게 된다. 
- 그리고 Critical Section 안에서는 Mutual exclusion 이라는 현상이 나타나야 한다.  
- Critical Section한 프로세스가 들어가게 되면 다른 프로세스를 다 배제 시키는 능력이 필요하다 이를 Mutual exclusion 이라 하고 OS 는 이 Mutual exclusion 매커니즘을 제공해야한다.

>Atomic operation : 일련의 모든 연산이 끝날 때까지 다른 프로세스는 그 연산에 대한 어떠한 변화도 할 수 없다.

>Critical Section : 어떤 한 코드 한 조각을 atomic 하게 즉 Non-Interruptable 하게 만들었을 때 코드 섹션을 Critical Section이라 한다.  

## Mutual exclusion 매커니즘

### 요구사항

- 주어진 시간에 하나의 프로세스만 크리티컬 섹션에 허용이 되어야 한다.
- Mutual exclusion을 필요로 하는 크리티컬 섹션에 여러 개의 프로세스가 진입을 원하면 그 중에 하나만 진입 할 수 있도록 허용 해야 한다.
- 크리티컬 섹션 안에 들어간 프로세스는 최대한 빨리 나와야 한다.

### 세마포어	

- 1970년대 다익스트라가 고안해낸 Mutual exclusion 알고리즘이다.
<figure>
	<img src="/images/post2-2.PNG" alt="">
</figure>

- 위 그림에서 세마포어는 열쇠, 그리고 열쇠를 관리하는 자는 OS, 벤치는 Waiting 큐, 작업공간은 Run 큐이다.
- 위와 같은 메커니즘이 세마포어 메커니즘이라 한다.
- 세마포어는 Synchronization을 제공해주는 정수형 변수로 있다[1] , 없다[0] 으로 표현한다.


#### 세마포어 API


1. 열쇠 줘 : lock(Semaphore)       , wait(Semaphore)      , P(Semaphore)
2. 열쇠 받아 : unlock(Semaphore)   , signal(Semaphore)     , V(Semaphore)


>lock , unlock 은 Synchronization 관점 에서의 API
>
>wait , signal 은 process state transition을 야기하는 API ( 스케줄링 관점 )



```
// 위 그림을 코드로 구현

semaphore S1 = 1 ;

Task1()
{
	P(S1)

		use pr;

	V(S1)

}

Taske2()
{
	P(S1)

		use pr;

	V(S1)

}


```

- 세마포어는 무슨 값으로 초기화 시켜야 할까? ->  1로 초기화 (바이너리 세마포어)
- 만약 작업공간이 하나 더 증가 한다면 세마포어 변수(카운팅 세마포어)는 2,1,0를 가진다.
- 카운팅 세마포어는 초기값을 2로 초기화 시킨다.

#### 스케줄링 관점의 세마포어

<figure>
	<img src="/images/post2-3.PNG" alt="">
</figure>

- 인터럽트 서비스 루틴은 깨어나야 하므로 signal(s) = V(s)
- Task 는 자고 있어야하므로 wait(s) = P(s)
- 초기값은 0으로 주어야 Task가 먼저 수행한다고 할지라도 대기 상태로 들어간다.

#### Producer/Consumer

<figure>
	<img src="/images/post2-4.PNG" alt="">
</figure>

- Producer 프로세스는 데이터를 생성만하는 것이고 Consumer 프로세스는 데이터를 읽어간다.
- 생성된 데이터를 Consumer 에게 전달하기위에 중간에 Buffer를 사용한다.
- Producer가 너무빨리 생성하면 Buffer 가 가득차기 때문에 이 Buffer가 빌때까지 Producer는 대기한다. 꺼꾸로 Consumer가 너무 빨리 읽으면 Buffer가 비기 때문에 Consumer가 대기한다.
- 이를 세마포어를 이용하여 구현하면 간편하게 구현할 수 있다.

<figure>
	<img src="/images/post2-5.PNG" alt="">
</figure>

- 초기에 데이터는 없기때문에 0 이고 버퍼는 비어있기때문에 1로 초기화 한다.
- Producer/Consumer는 스케줄링과 Mutual exclusion이 절묘하게 결합되어 있다. 이런 기능을 세마포어로 심플하게 구현 가능하다.

#### 정리

- 세마포어는 Mutual exclusion 도 제공해주고 스케줄링도 제공해 준다.