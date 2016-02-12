---
layout: post
title: "[OS]Atomic Operation"
description: "[OS]Atomic Operation" 
modified: 2016-02-13
tags: [blog]
comments: true
image:
  feature: back1.jpg
---
Atomic Operation 에 대해 알아보자

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Automic Operation 이란?


- 글로벌 자원을 읽고, 수정하고, 다시 되돌리는 이 과정을 가장 작은 단위로 만드는 것이다.
- 즉 한 프로세스의 일련의 모든 연산이 끝날 때까지 다른 프로세스는 그 연산에 대한 어떠한 변화도 할 수 없다.
- 전체 연산 중 어느 하나라도 실패할 경우, 모든 연산은 실패하여, 시스템은 전체 연산이 시작하기 전의 상태로 복구된다.

### Automic Operation의 필요성

- 멀티스레드 프로그램에서 여러 쓰레드간 공유되는 자원들은, 여러 쓰레드가 동시에 액세스 하기 때문에 Race condition 이라는 경쟁이 돌입한다. 이를 막기위해 보통 lock() 을 사용한다.(윈도우의 경우 Critical Section)
- 이러한 각 자원들 간의 동기화(synchronization) 문제를 해결하기 위해 하드웨어에서 지원되는 Atomic operation 의 개발로 많은 문제가 해결되고 있으며 lock-free 알고리즘이나 자료구조를 위한 툴로 많이 사용되고 있다.

### Atomic Operation 예제
```
// 1. atomic operation 사용
AtomicExchange(&i, 0);


// 2. Critical Section 사용
EnterCriticalSection(&cr);
i = 0;
LeaveCriticalSection(&cr);

```
- 단순히 변수 i에 0으로 초기화하는 작업을 하는 코드의 2가지 예이다
- Atomic operation을 사용할경우 변수 i를 0으롤 초기화 할경우 다른 스레드는 초기화가 진행되는 동안 변수 i 를 읽거나 쓸 수 없다.
- 반면 Critical Section을 사용할 경우 결과는 같지만 원하는 lock 을 얻지 못할 경우, 스레드는 대기상태로 전환되고 다른 스레드로 Context switiching 하는 작업이 일어나며 이것은 CPU 입장에서 상당한 CPU 사이클을 사용하는 매우 비싼 작업이다.
- Automic operation은 Context switching을 발생시키지 않는다.

```
 g_count++;    

// 1. read  g_count -> register0  
// 2. add   1, register0  
// 3. write register0 

```

- 위 코드와 같이 스레드 간의 공유변수 g_count를 1만큼 증가시키는 작업을 할때 이 코드는 Atomic 할까?
- 간단해 보이는 이 문장 하나가 실제 CPU 입장에서는 Read, modify, Write 라는 3단계를 거치게 된다.
- 스레드 A가 1단계를 거쳐서 g_count의 값을 읽어온 다음 스레드 B가 다시 같은 g_count 의 값을 읽어 1증가 시키고 메모리에 쓸 수 있다.
- 그럼 2만 큼 증가되어야할 g_count는 1밖에 증가되지 못하는 현상이 발생한다.
- 이러한 단순한 연산도 lock 으로 보호되어야만 안전하다.
- 하지만 atomic 으로 연산할 경우 이러한 동기화 문제를 하드웨어적으로 해결해 준다.



## [참고]IA-32에서의 Atomic Operation

- 32비트 인텔 CPU (IA-32)에서 지원되는 Atomic Operation에 관해 알아보자. 다음과 같은 인텔의 CPU 연산들 앞에 LOCK을 붙여 해당 연산을 Atomic하게 만들 수 있다. 즉, 스레드간의 동기화를 신경쓰지 않아도 된다. 
- ADD, ADC, AND, BTC, BTR, BTS, CMPXCHG, CMPXCH8B, DEC, INC, NEG, NOT, OR, SBB, SUB, XOR,


>[참고 사이트](http://choiwonwoo.egloos.com/1176220)