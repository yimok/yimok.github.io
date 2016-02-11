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

### interaction의 문제점

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

- 인터럽트를 disable 시키면 유저프로세스가 수행될 때 인터럽트에 의해 쪼개지지 않아 Reentrant Cod가 되어 올바르게 작동한다.

>Reentrant Code(재진입 가능 코드):
>여러 Process 들에 의해 동시에 호출되거나, 이전 호출이 완료되기 전에 반복 호출되어도 올바르게 수행되 코드

