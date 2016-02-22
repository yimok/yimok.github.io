---
layout: post
title: "[OS]세그멘테이션과 페이징(2)"
description: "[OS]세그멘테이션과 페이징(2)" 
modified: 2016-02-19
tags: [blog]
comments: true
image:
  feature: back1.jpg
---
Paged Segmentation 에 대해 알아봅시다. 

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## 복습

- 초창기에는 한 job이 하나의 세그먼트만 받아서 멀티프로그래밍을 했다. 이로 인해 어떠한 문제가 발생하였을까? 
- 프로세스의 코드,데이터,스택 등 여러 섹션이 있는데 이런 섹션들을 각각 다른 특징들을 가지고 있다. 예를 들면 코드섹션은 읽기만 가능, 스택 섹션은 읽기 쓰기 전부 가능, 또 코드 섹션과 같이 Read only 인 경우 여러 프로세스들이 공유를 할 수 있다.
- 이러한 특징들을 살릴 수 없기 때문에 한 프로세스에 여러개의 세그먼트를 부여하는 방법을 적용하였다. 이러한 기술을 Segmentation 이라 하였다.
- 이 Segmentation 을 구현하기 위해 세그먼트 테이블이 등장하게 되었고 MMU 안에는 이 테이블을 가리키는 레지스터가 들어가게 되었다.
- 하지만 아직 Fragmentation 문제는 해결되지 못하였는데 이를 해결하기 위해 메모리 할당 단위를 고정 시키는 Paging 이라는 방법을 구현하였다. 

## Paged Segmentation

- 페이징만 한다는 것은 프로세스에 한개의 세그먼트만 제공하는것이다. 즉 페이징은 Fragmentation 은 해결했지만 프로세스에 다중 세그먼트를 할당 할 수 있는 방법은 달성하지 못하였기 때문에 페이지와 세그먼트를 같이 사용 한다. 
- 먼저 Segmentation으 수행하고 각 Segment 별로 Paging을 수행

### Paged Segmentation 특징

1. 기존에 물리주소를 저장하던 Base Address 대신 해당 Segment의 Page Table의 위치를 저장
2. 기존 Bound 값 대신 해당 Segment의 Page 개수를 저장


<figure>
	<img src="/images/segmentpaged1.PNG" alt="">
</figure>

- 위 그림은 IBM 370 시스템에서의 가상 메모리 공간이다.
- 상위 4비트를 세그먼트 인덱스로 사용하고 두번째 8비트를 페이지 넘버로 사용한다. 그리고 하위 12비트를 페이지 오프셋으로 사용한다. 
- 위 주소로 예측할 수 있는 페이지 하나의 사이즈는 2^12 = 4KB 이다. 또 세그먼트 당 최대 페이지의 수는 2^8 개 이다. 그리고 프로세스 하나에게 부여할 수 있는 세그먼트의 개수는 2^4 = 16개 이다.
- 우리가 배운 세그먼트는 코드,데이터,스택,힙 등.. 몇개 없는데 왜 16개까지 부여하도록 하였을까? -> 어떤 2개의 프로세스가 메모리 지을 공유할때 따로 세그먼트를 만들어서 사용할 수 있도록 OS에게 선택의 기회를 좀 더 제공한다.


### Paged Segmentation 구현
 
<figure>
	<img src="/images/segmentpaged2.PNG" alt="">
</figure>

- 세그먼트 테이블에는 16개의 레코드가 있고, 각 레코드에는 페이지 테이블의 시작 주소가 들어가게 된다.
- 위 그림은 세그먼트 테이블중 3개만을 표시 했다. 0x2000 이 읽기만 가능한것으로 보아 Code 세그먼트인것을 알 수 있고, 0x1000 이 읽기쓰기 모두 가능한것으로 보아 Data 세그먼트인것을 추측할 수 있다. 0x0000 은 사용하지 않는 세그먼트이다.

<figure>
	<img src="/images/segmentpaged3.PNG" alt="">
</figure>

1. 상위 4비트가 세그먼트 넘버이므로 0인 것을 알 수 있고 세그먼트 테이블의 0번째 인덱스의 레코드를 찾아간다.
2. 0번째 레코드의 Base 어드레스 값이 0x2000 인것을 확인 하였고 메모리의 0x2000위치 즉 페이지 테이블 레코드위치로 가서 가상 주소의 8비트 값 02 를 사용하여 3번째 위치의 Physical Frame number 0x0003과 매핑한다.
3. 그리고 마지막으로 070 을 더해준다.

### 정리	

- 위처럼 Segmetn Table과 Page Table을 사용한 주소 변환은 MMU에 의해 하드웨어 적으로 수행된다.
- 그러나 프로세스의 Context switching 이나 새로운 프로세스 들이 일어날 때, 운영체제가 Base/Bound Register 및 Segment/Page Table들을 관리해야 하므로 운영체제에게 Transparant 하지는 않음

### 참고

- 리눅스는 Paging 만 사용한다. 
- MMU가 지원했던 세그멘테이션의 많은 기능을 OS가 해결하고 MMU의 순수 Paging 만을 사용한다. 
- Paging 만 사용하면 액세스 컨트롤을 어떻게 해결? -> 과거에 세그먼트 단위로 하던 액세스 컨트롤을 전부 페이지 테이블로 내려서 사용한다.
- 공유 문제는 어떻게 해결? -> 공유도 페이지 단위로 한다.
 
 
## Machine independent Code 와 Machine dependent Code

- OS를 만들때 머신에 독립적인 코드와, 머신에 의존하는 코드로 나눌 수 있다.
- 여기서 머신이란 CPU 구조, 시스템 구조(버스, 메모리 맵), I/O 장치 이며 이 3가지 하드웨어의 차이에 맞추어 제작되는 운영체제 코드를 Machine dependent Code 라고 하며
- 이 머신과 상관없는 운영체제 코드를 Machine independent Code 라고 한다.
- 개발자들은 Machine independent Code 한 코드의 비중을 높이려고하는데 그 이유는 운영체제의 Portability를 높여 다른 하드웨어에서도 동일한 운영체제를 사용하기 위해서이다.
- 대표적인 Machine Dependent Code : Context switching, 프로세스 생성, I/O장치 드라이버, 메모리 관리(MMU) 등이 있다.
- 그래서 리눅스가 Paging 만을 지원하는 이유가 여기있다. 인텔 프로세서는 세그먼트와 페이징을 다 지원하지만, ARM 프로세서의 경우 세그먼트를 지원하지 않기때문에 리눅스는 여러 프로세서에서 사용할 수 있도록 Paging만을 사용하고 세그먼트의 기능들을 OS에서 구현하도록 하였다.


## 여러 속성을 가진 page 

- 이전에 공부했던것 처럼 물리 메모리를 일정한 조각으로 나눈 것을 page frame 이라고 불렀다
- 이 frame 들은 속성들을 가지고 있는데 대표적으로 mapped page, unmapped page, cached page, uncached page 와 같은 속성을 가지고 있다.
- cached page : 일반적인 페이지는 cached page 이다. 한번 액세스 하면 이 페이지를 캐시의 빈공간에 적재시켜 나중에 다시 사용한다.
- uncached page : 절대 캐싱을 하지 않는 것이다. 만약 페이지를 공유 하고 있다면 캐싱을 하면안된다. -> 내가 frame 하나를 수정 하고 있는데 CPU가 예전에 캐싱한 frame 을 가지고 연산을 한다면 문제가 발생하기 때문이다.-> DMA operation을 위해 사용되는 Page의 경우 여러 프로세스에 의해 동시에 읽고 쓰기가 일어 날 수 있기 때문에 uncached page를 사용한다.
- mapped page : 전통적인 Address translation 방법으로 주소를 액세스하여 얻는 페이지를 말한다.
- unmapped page : Address translation 없이 물리 메모리를 바로 날려서 액세스 하는것을 말한다.(메모리 일부는 이처럼 다이렉트 액세스를 사용한다.) -> 페이지 테이블은 unmapped page 에 들어가 있다.

## Large page table 의 문제

- 페이지 테이블은 unmapped page 영역(물리 메모리) 에서 continuous 하게 저장되있다.
- 그러나 시스템에서 unmapped page영역을 조금만 유지하는데.. 이곳에 거대한 페이지 테이블이 저장된다면 시스템에 좋지않은 영향을 끼칠 것이다.
- 이런 Large Page Table 의 문제를 해결하기 위해서 Page Table의 크기를 줄이거나, 연속적인 메모리 공간 요구량을 줄여서 해결한다.


### VAX(Virtual Adrress extension) - VMS

- Large Page Table 문제를 해결하기 위해 VAX 컴퓨터의 VMS 시스템이 개발되었다.
- 가상 주소공간을 4개의 공간으로 나누었다. -> System 세그먼트, P0 세그먼트, P1 세그먼트, unused 세그먼트


<figure>
	<img src="/images/segmentpaged5.PNG" alt="">
</figure>

1. VAX 는 위 그림과 같이 가상주소의 일부를 OS에게 할당하고 유저는 가상주소의 나머지 부분을 사용하는 방법을 쓴다.
2. 그리고 OS영역안에 유저 페이지 테이블이 존재한다.
3. 유저 페이지 테이블이 저장된 OS영역은 mapped page이다(가상주소 공간)
4. 또 유저 페이지 테이블의 엔트리 주소 역시 가상 주소이다.
5. 다시 시스템 페이지 테이블의 엔트리 주소를 얻어와서 물리 주소를 찾는다.	




### TLB(Translation Lookaside Buffers)

<figure>
	<img src="/images/segmentpaged4.PNG" alt="">
</figure>
그림 출처 : https://www.cs.uic.edu

- 속도 문제를 해결하기 위한 방법
- logical address 를 발사하면 MMU 안에 있는 TLB를 먼저 뒤져서 TLB hit가 나게 되면 그 frame 넘버를가져와서 물리주소를 찾고 실패하면 페이지 테이블로가서 frame넘버를 가져와 물리주소를 찾는다.
- TLB의 사이즈를 늘리던가, 페이지의 사이즈를 늘리면 Hit확률이 증가한다.
- TLB는 하드웨어 구현방식이다.
