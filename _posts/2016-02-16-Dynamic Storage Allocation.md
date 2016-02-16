---
layout: post
title: "[OS]동적 할당"
description: "[OS]동적 할당" 
modified: 2016-02-15
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

Dynamic Allocation에 대해 알아보겠습니다.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## Dynamic Allocation


### 복습 - Static  
--- 
- static allocation, static scheduling, static analysis(컴파일러) 등.. 이 있다.
- execution 전 이다. 즉 runtime 전
- static allocaion : 프로그램이 수행되기 전에 미리 메모리를 할당 하는 것 - code segment , data segment
- static allocation 의 특징 : 어떤 변수의 생명 주기가 프로그램의 시작과 종료와 일치


### 왜 Dynamic이 필요 한가?
---
- Dynamic은 execution 이후 이다. runtime 이후
- 함수의 호출 순서를 예측할 수 없기 때문에 Dynamic이 필요 하다.
- 자료구조를 동적으로 구현한다. 예를 들면 PCB를 Linked list로 구현한다.(메모리 한계 까지  얼마든지 PCB를 생성 할 수 있다) -> 과거에는 PCB를 배열로 만들었었는데 프로세스를 어느 한계까지 생성하면 더이상 생성하지 못하였다.
- 요구에 맞추어 자료구조를 생성 하면 어떠한 장점이 있을까? -> 메모리가 가득 찰 때까지 자료구조를 충분히 생성할 수 있다.
- Dynamic Allocation 하는 대표적인 예 : 프로그램안에서 함수를 호출 하였을 때 함수가 필요로하는 지역변수들을 담아두는 공간 으로 Stack을 사용한다.
- Activation Records(Stack Frames) : Procedure(함수)가 수행되기 위해 필요한 정보들을 저장하고 관리하기 위해 Stack에 저장되는 데이터 구조
- 이 Activation Records 는 그 함수가 호출이 되어서 종료될 때까지 생명주기를 갖는다.


<figure>
	<img src="/images/dynamic1.PNG" alt="">
</figure>

- Activation Records 가 생성 되는 것은 Push(), Activation Records 가 사라지는 것은 Pop() 과 일치한다.
- 즉 함수 호출과 리턴이 Push() , Pop() 과 대응된다.

### 동적 할당 구현하는 2가지 방법
---
- Stack
- Heap

### 동적 할당 명령어

- 프로그래밍 언어에 따라 다르다
- Allocate(new) : 할당 
- free(deallocate) : 해제

## Heap

- 힙은 프로세스가 필요한 양 만큼 메모리를 할당 할 수 있다.

``` 

if(c) then use 100 data items // 99%

else use 1,000,000 data items // 1%

```

- 위 코드를 static 으로 구현 한다면 1% 밖에 발생되지 않는 조건 때문에 무조건 데이터 100만 개를 생성 해야한다.
- 하지만 dynamic 으로 구현한다면 상황에 맞게 데이터 수를 생성하면 된다.

### Heap 사용

- C++,Java : new, delete
- C : malloc(), free()
 
<figure>
	<img src="/images/dynamic2.PNG" alt="">
</figure>

- 처음에는 순차적으로 할당을 하고
- 누군가가 free 를 하게 되면 Heap에 빈 공간(hole)들이 생긴다.
- 이 빈 공간들을 효율적으로 사용하기 위해 빈 공간의 일부를 포인터로 사용하여 다음 빈공간들을 연결한다(Linked list)
- 그리고 제일 첫 공간을 가리키는 포인터를 Free List 라고 부른다.
- 다시 말해서 Free list 는 맨처음에 큰 Heap 을 가리키고 있다가 malloc() 과 free() 를 반복하면서 생긴 빈 공간들 중 첫 공간을 가리키게 된다.

<figure>
	<img src="/images/dynamic3.PNG" alt="">
</figure>

- 두 공간이 이어질 수 있다면 free 함수가 합병을 시킨다.
- 즉 free 함수는  Free List로 반환되는 공간이 기존 가용한 공간과 병합이 가능한 경우 하나의 큰 공간으로 병합하고 아닐 경우 새로운 포인터 를 추가한다. 
- 하지만 위 방법에도 단점이 존재한다.
- malloc 과 free를 계속해서 하다보면 궁극적으로 공간(hole)들이 점점 작아질 수 밖에 없다. 이렇게 작은 공간들이 많아지는 현상을 Fragmentation 이라 한다.

### Fragmentation 단점

- 맨 처음 Heap 에 있는 큰 공간 하나가 굉장히 작은 공간으로 쪼개 져서 흩어져 있다.
- 특정 프로그램을 올리려고 하는데 용량은 맞지만 이 공간들이 너무 작아서 올리지 못하는 문제가 발생한다.

### Fragmentation 해결방법

1. 다른 프로세스가 큰 공간을 반환 할 때까지 그 프로세스를 sleep 시킨다.  -> 하지만 .. 다른 프로세스가 큰 공간을 반환하지 않아 지금 실행해야할 프로세스는 게속 sleep 상태에 있고 또 추가적으로 들어온 프로세스 역시 공간이 부족하여 sleep 으로 가는 상태가 발생한다. 이러한 현상이 지속되면 Deadlock 이 발생 한다.
2. Fragmentation 을 최소화 할 수 있는 기법들을 사용한다. (slab allocator, paging기법 등 ..)

### Fragmentation 최소화 기법 - Buddy Allocator

<figure>
	<img src="/images/buddy allocator1.PNG" alt="">
</figure>

- 기본적으로 Heap 을 사용한다.
- Heap의 크기를 2^k 로 잡는다.
- 위 그림처럼 2^(k-1) 을 해 가면서 힙의 공간을 반씩 잘라 준비해 놓고 
- malloc() 을 하면 크기에 맞는 공간을 제공해준다.
- 
<figure>
	<img src="/images/buddy allocator2.PNG" alt="">
</figure>

- free 를 하면 그 공간을 다시 반환 받고 다시 큰 공간으로 병합할 수 있는 확률이 증가한다.
- Linux 에서 Buddy allocator 와 slab allocator 를 사용한다.

### Free List

1. Linked list로 구현하여 관리 한다.
2. bitmap 을 사용한다.(Disk allocation 할때 많이 사용)

### Linked list로 구현한 free list

- Best-fit : free list를 따라 가면서 여분이 가장 적게 남는 공간을 찾아 할당한다.(Linked list 필요) -> Best fit을 계속하다보면 hole 의 사이즈가 굉장히 작아진다. 즉 작은 공간이 많아져 Fragmentation 문제가 더 심각해질 수 있다.
- first-fit : 첫번째 공간을 할당한다. -> Best-fit 보다는 hole의 사이즈가 좀 크다, 평균적인 사이즈의 공간이 많아진다.
- 결과적으로 Best-fit 으로 할당하는 것이 항상 좋은 결과를 가져오는 것은 아니다.
- Worst-fit : 제일 큰 공간들을 만드는 것
- 결과적으로 이런 fit 방법으로 해결하기는 어렵다.

### Fragmentation 최소화 기법 - Memory pool

<figure>
	<img src="/images/memory pool.PNG" alt="">
</figure>

- 기존 동적할당 방법은 다양한 공간 사이즈 때문에 Fragmentation을 유발하였다.
- 좀더 효율 적인 방법인 Memory pool 은 동일한 사이즈의 메모리 블록들을 미리 할당해 놓는 것이다.

## 정리 

- 동적 할당의 Heap 에대해 알아 보았다.
- Heap 은 Fragmentation 을 유발하고
- Fragmentation 은 시스템에 안좋은 영향을 준다.
- Fragmentation 을 최소화 하기 위해 Buddy Allocator , Memory pool 등을 사용한다. 

