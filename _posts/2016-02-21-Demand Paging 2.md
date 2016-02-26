---
layout: post
title: "[OS]Demand Paging(2)"
description: "[OS]Demand Paging(2)" 
modified: 2016-02-21
tags: [blog]
comments: true
image:
  feature: back6.jpg
---
Thrashing 과 Working Set 에 대해 알아봅시다.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## Thrashing

### Thrashing이 발생하는 과정

1. 시스템에 충분히 많은 Process가 동작중 일때
2. 동작 중인 Process가 요구하는 Memory가 가용한 Physical Memory 보다 많아서 Page Fault가 발생 하게 되고
3. Page Fault를 처리하는 동안 Process는 블록당하게 되므로 CPU Utilization이 낮아짐
4. CPU Scheduler는 시스템이 한가한 것으로 판단하고 더 많은 Process들을 동작시킴
5. Memory가 더욱 부족해짐으로써 악순환이 반복됨
6. 즉 CPU가 프로세스 실행보다 페이지 교체에 더 많은 시간을 소비하게 된다.


### Thrashing 해결법

- PC의 경우 유저 또는 OS가 불필요한 프로세스를 제거 시킨다.
- 스마트폰 처럼 Swap Devie가 없는 경우 많은 Process로 인해 Memory가 부족하면 어떻게 처리할까? -> 안드로이드의 Low Memory killer와 같이 동작중인 Process를 강제로 종료시켜서 완전히 Memory에서 제거할 수 밖에 없다.

## Working Set

- 어느 시점에 특정 Process가 Access 하는 Page들의 집합을 워킹 셋이라고 한다.
- Prepaging : 실제 Page 요청이 있기 전에 향후 Access될 것으로 예상되는 Page를 미리 Memory에 로드하는 것
- 이 워킹셋을 정확히 안다면 어떤 프로세스가 Swap 당할때 그 프로세스의 워킹셋을 전부 Prepaging 할 수 있다. 이러한 개념에 의해 Page Fault를 줄일수 있다. 기존에는 한 페이지+전,후 페이지만을 넣었다면 워킹셋은 한 집합을 넣는것이다.
- 하지만 이 작업을하려면 넣어야할 워킹셋을 정확하게 알아야한다.

### Working Set을 어떻게 예측할까?

- Working set parameter 방법 : 현재부터 과거 일정 시간동안 액세스된 페이지들을 워킹셋으로 정의하는 방법이다. 하지만 시간 간격이 너무 짧으면 충분한 워킹셋을 보유하지 못하고, 또 시간 간격이 너무 길면 불필요한 페이지를 포함한 워킹셋을 보유하게 된다. 이러한 단점이 있다. -> 하지만 실질적으로 구현은 어렵다.
- 운영체제는 현재 프로세스가 Page Fault가 얼마나 발생하였는지를 확인하여 Process가 잘 돌고 있는지 아닌지를 판단한다. 그리고 그 페이지들을 워킹셋으로 묶는다.

## Page Fault 발생 횟수에 따른 OS의 Memory 할당 정책

- 상한점 보다 Page Fault가 많이 발생하는 경우 : 해당 Process에게 더 많은 Memory(Page Frame)를 할당
- 하한점 보다 Page Fault가 적게 발생하는 경우 : 해당 process에게 할당된 Memory(Page Frame)를 회수
- 이와 같이 적절한 선을 정하여 그 선을 넘거나 안넘을 경우 적절하게 Page Frame 을 할당한다.
- 이를 Resident Set 이라 한다.

## 메모리 관리 기법 동향

- 물리 메모리의 크기가 커졌다. 
- 물리메모리가 커졌다는 말은 페이지 프레임 커졌다는 말과 같기때문에 Page replacement 정책이 덜 중요해졌다.
- 물리 메모리의 크기가 커지면서 페이지의 크기도 커졌다.
- 가상 주소 공간이 커졌다. -> 64bits 공간


### Large Page Table 관리 문제

- 페이지 테이블을 유지하기 위해 필요한 공간이 너무큼
- 즉 가상 메모리 공간이 너무 커짐 64bit -> 2^64
- 페이지 테이블이 Phyisical Memory의 연속적인 공간에 존재해야함.
- Hierarchical page table ,Hased page Table, Inverted page table 방법을 통해 해결


### Hierarchical page table 

- 테이블 공간을 줄이지는 못하지만 페이지 테이블들을 물리 메모리상에 작은 조각으로 나누어 만듬
- 32bit 컴퓨터에서 페이지를 나눌때 상위 22bit를 페이지 넘버 하위 10bit를 페이지 오프셋으로 보았다.
- 여기서 페이지 넘버를 한번더 나누어 상위 14bit를 first-level index , 하위 8bit를 second-level index 로 정한다.

<figure>
	<img src="/images/twolevel.PNG" alt="">
</figure>

- 2단계를 거쳐서 마지막 페이지 엔트리에 10bit 오프셋을 더해서 최종적으로 물리메모리의 위치를 구한다.
- 단계가 추가 되면서 추가적인 액세스를 해야한다는 단점이 존재한다.

### Hased page Table 

<figure>
	<img src="/images/hashtable.PNG" alt="">
</figure>
[그림출처](https://www.cs.uic.edu)

- 논리주소의 P(page number)를 해쉬 테이블을 통해서 해당하는 엔트리들을 얻어오는 기법이다.


### Inverted page table 

<figure>
	<img src="/images/inverted.PNG" alt="">
</figure>
[그림출처](https://www.cs.uic.edu)

- 페이지 사이즈를 획기적으로 줄이는 방법
- 시스템 전체에 Page table은 한개만 존재한다
- 페이지 테이블의 사이즈는 가상메모리 사이즈가 아니라, 실제 시스템에 존재하는 물리 메모리(페이지 프레임 갯수)사이즈 이다. 
- Page number와 Process id를 가지고 페이지테이블에서 Physical Frame number를 찾는다.
- 거대한 TLB 라고 보면 된다.