---
layout: post
title: "[OS]세그멘테이션과 페이징(1)"
description: "[OS]세그멘테이션과 페이징(1)" 
modified: 2016-02-18
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

Segmentation과 Paging 에 대해 알아 봅시다.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## Segmentation

- 과거 멀티프로그램 배치 모니터 시스템은 동시에 Active 한 Job 들이 메인메모리에 존재 할 수 있었다. 또 메모리의 한쪽 끝에는 컨트롤 시스템 소프트웨어가 있었고 나머지 공간에 유저 프로세스들의 메모리가 할당 되어 사용 되었다. 이것이 배치모니터 였다.
- 이런 배치 모니터 시스템에서 유저 프로세스들은 하나의 메모리 세그먼트를 할당 받았다. 지난 시간에 배운것처럼 유저 프로세스는 Data section, Text Section, stack , heap 의 공간이 있는데 이것을 하나의 메모리 세그먼트에 매핑 시켰다.
- 이런 방법을 사용하면 어떠한 문제가 있을까? -> 링커가 각 섹션을 나눈 이유가 있었다. Text 섹션은 Read만 가능하면 되고 , Data 섹션, stack , heap은 Read/Write 가 가능 한것 처럼 각각의 특징들이 있는데 하나의 메모리 세그먼트를 할당 받는다면 이런 특징을 살릴 수 없게된다.
- 다시 말해서 **하나의 메모리 세그먼트를 할당 받는다면 두 유저 프로세스가 동일한 Text Section을 공유하기 힘들다.**
- 또 **각 메모리 섹션들에게 다른 Read/Write 권한을 설정하기가 힘들다.**

### Multiple Segmentation

- 하나의 메모리 세그먼트를 할당 받는다면 각 섹션들의 특징을 살릴 수 없는 문제점이 나왔다. 이를 해결 하기위해 각 섹션들을 각 세그먼트로 나누어 할당 시켜주는 방법이 나왔다.
- 하지만 이 방법도 새로운 문제점이 생겼다. 과거에 하나의 세그먼트에 할당 시켰을때는 Address 매핑이 굉장히 쉬웠다. Base 레지스터와, Bound 레지스터 2개를 이용해 매핑을 하였다. 하지만 세그먼트의 수가 증가하면 각 세그먼트마다 별도의 Base 레지스터와 Bound 레지스터를 만들어야 했다.

### Multiple Segmentation 해결책 

- 각 세그먼트마다 별도의 Base, Bound 레지스터를 할당하려면 하드웨어적으로 어떻게 구현해야 할까? 
- 첫째는 세그먼트 어드레스 레지스터들을 별도로 가지고 있어 각 세그먼트 구간을 사용할 때 그 주소로 매핑시킨다.	
- 둘째는 별도의 레지스터를 할당하지 않고 메인메모리에 세그먼트의 Base, Bound 레지스터를 테이블 방식저장하여 사용했다.

### Sementation - Address translation

<figure>
	<img src="/images/segmant.PNG" alt="">
</figure>

- MMU(Memory Management Unit) : CPU가 물리 메모리에 접근하는 것을 관리하는 하드웨어 장치
- CPU를 통해서 나오는 논리 주소는 컴파일러, 링커가 보는 어드레스이다. 과거에 프로그래머가 어셈블리어를 많이 사용할때는 프로그래머들도 볼 수 있는 어드레스이다.
- 과거에는 실리콘 집적도가 낮아서 CPU칩 MMU칩이 따로 존재 하였다. 하지만 현재는 CPU, MMU가 하나의 칩안에 존재한다.


<figure>
	<img src="/images/segmant1.PNG" alt="">
</figure>

1. 32bit 에서 모든 프로세스는 위와 같은 크기의 논리주소를 갖는다. 
2. 물리 주소는 한개밖에 없지만 논리주소는 무수히 많이(수행중인 프로세스 개수 만큼)만들어도 상관없다. 
3. MMU는 먼저 CPU 에서 나온 논리 주소가 어느 세그먼트인지 알아야 한다.
4. 논리주소의 각 섹션 상위 2bit는 그 섹션이 무엇인지 판단하는 ID로 사용되고, 나머지 
6. 30bit 는 세그먼트의 offset으로 사용 된다. 
5. 상위 2bit ID 는 세그먼트 테이블의 Index로 사용된다.

<figure>
	<img src="/images/segmant2.PNG" alt="">
</figure>

- 세그먼트 테이블에는 그 세그먼트가 어디서 부터 시작하는지(Base Address), 세그먼트 크기는 얼마인지(Bounds) , Read인지 write인지 파악하는 정보가 필요하다.
- Base Address 는 물리주소이다. -> 물리 메모리의 어디에있는지 알려주는 주소이다.
- 그리고 추가적으로 **MMU 안에는 세그먼트 테이블의 시작주소를 알 수 있도록 STBR(Segment Table Base Register)가 존재한다.**
- 정리하자면 프로세스가 바뀔때(Context Switching)마다 MMU안에 STBR에 그 프로세스에 맞는 세그먼트 테이블로 재배치 해주어야 한다.

### Segmentation - Address translation 실제 구현 방법


<figure>
	<img src="/images/segmant3.PNG" alt="">
</figure>

- 논리주소의 아래 12bit는 그대로 내리고 앞의 2bit는 테이블의 인덱스 값이므로
- 0x1600 -> 01 , 600 으로 세그먼트테이블의 1번 인덱스 베이스 주소 0x0000 을 600에 더한다.
- 0x600 이 나오게 된다.
- 그러나 이 값은 세그먼트 테이블의 Bound 범위를 초과하므로 오류가 나고 프로텍션이 일어난다.
- 또 다른 예로 세그먼트 테이블의 0번 세그먼트를 쓰기로 사용한다면 이 또한 오류가 나서 OS 시스템이 메모리 프로텍션을 한다. 

### Sementation - Address translation 문제점

- 메모리를 접근하기 위해서 실제적으로 2번의 접근이 필요하다. -> (MMU 에서 세그먼트 테이블에 접근하고, 물리 메모리에 접근한다.)
- 이러한 이유로 프로그램의 수행이 2배이상 느려진다.
- 또 세그먼트가 메인메모리에 많이 존재하므로 Fragmentaion 이 발생한다.
- 또 스택 세그먼트를 할당했는데.. 주어진 스택 세그먼트보다 스택이 더 증가해서 오버플로우가 일어나는 경우도 발생한다. -> 스택 세그먼트 위쪽이 비어있는 공간이면 늘려도 상관없지만, 만약 다른 공간이 차지하고있다면.. 그 공간이 현재 사용하지 않을경우 다시 디스크로 보낸다. 또 다른 해결법은 반대로 스택세그먼트를 디스크로 보내 나중에 충분한 공간이 생겼을때 불러들인다.(Swapping 방법 사용)

### Segmentation 의 장단점

- 장점: 내부 단편화가 없고, 코드나 데이터, 스택등 각 특징을 종류별로 분류하여 저장하므로, 공유, 보호가 쉽다.
- 단점: 외부 단편화 발생

### [복습]Fragmentation 발생 이유

- 요청된 Memory allocation size가 다르다. -> 유니사이즈로 할당하여 해결

## Paging

- Multiple Sementation 을 위해 Address Translation 을 하였는데 이로인해 발생한 여러 문제점(Fragmentation 등)들을 해결하기 위해 Paging 기법이 개발되었다.
- 유니사이즈 메모리 공간을 swapping 한다.
- 현대 OS 시스템의 가장 중요한 기법

<figure>
	<img src="/images/segmant4.PNG" alt="">
</figure> 

- Page : **Logical Address space를 일정한 크기로 나눈 Memory Block**
- Frame(or Pageframe) : **Physical Address space를 일정한 크기로 나눈 Memory Block, Page와 크기가 동일 함**
- 위 처럼 전부 동일한 크기로 메모리 할당이 일어나므로 fragmentation 을 해결할 수 있다.
- 과거에는 페이지 size를  0.5kb , 1kb 로 했다. 왜 0.5kb, 1kb 로 했을까? -> Swapping 을 염두하여 size를 결정하였는데 Swapping 할때 한 블록(과거에는 0.5kb, 1kb)의 크기를 기준으로 한번에 페이지를 전송하기 위해서 였다.
-  요즘은 버스의 bandwidth 가 커지고 메모리 크기도 커져서 페이지 크기가 증가 하였다.(1MB, 2MB)

### Paging - Address translation

- MMU가 세그먼테이션 테이블을 이용해 Address translation 을 하였듯이 Paging도 MMU가 페이징 테이블을 이용해 Address translation 한다.
- 세그먼트 테이블에서 Address translation를 할때 우선적으로 세그먼트 넘버를 가져왔듯이 페이징 테이블도 페이지 넘버를 가져와야한다.  

<figure>
	<img src="/images/segmant5.PNG" alt="">
</figure> 

- 상위 bits 를 페이지 넘버로 사용하고 하위 bits를 페이지 오프셋으로 사용한다.
- 위 그림은 SPARC 마이크로프로세서 의 페이지 주소이다 20bits를 page 넘버에 사용하고 12bit를 페이지 크기로 사용한다. 
- 페이지 테이블의 크기 = 2^20(인덱스) x (물리 메모리 페이지 번호) 가 된다.
- 즉 이러한 이유로 프로세스가 많아질수록 페이지 테이블의 수가 많아져 메모리 낭비가 심해진다. 

<figure>
	<img src="/images/segmant7.PNG" alt="">
</figure> 

<figure>
	<img src="/images/segmant6.PNG" alt="">
</figure> 

- MMU 안에 페이지 테이블의 시작 주소를 가리키는 레지스터인 PTBR(Page Table Base Register)이 존재해야한다
- 세그먼트일때와 마찬가지로 Context Switching 이 일어날때마다 OS 는 이 page 테이블의 시작주소를 새로운 프로세스의 시작주소로 재배치 한다.

### Paging 과 segmentation 의 차이점?

- Segmentation에서는 실제 세그먼트의 크기가 가변적인 반면 Paing 에서는 페이지 크기가 다 일정하다. 이로인해 Fragmentation을 해결한다.

### Paging 을 사용했을때의 장점

- Fragmentation을 해결할 수 있다.
- Swapping 이 용이해진다.(페이지 크기를 디스크 블록 사이즈에 맞춤)

### Paging 을 사용했을때의 단점

- Internal Fragmentation 이 발생하나 효과는 미미함.
- Segmentation일 때와 마찬가지로 메모리를 접근하기 위해서 실제적으로 2번의 접근이 필요하다
- Segmentation과 반대로 페이지 테이블의 크기가 방대해지는 문제가 생긴다.

### Paging 테이블의 내부


<figure>
	<img src="/images/segmant8.PNG" alt="">
</figure>

- 페이지 테이블의 레코드는 1word(32bits 머신 = 32bits) 의 크기에 맞춘다.
- MMU의 PTBR는 페이지 테이블의 시작주소를 가리킨다.
- 위에서 페이지 넘버의 크기가 2^20 이라고 하였으므로 2^20 개 만큼의 페이지 테이블 레코드들이 존재한다.
- 이 페이지 레코드 상위 20bits 에는 Frame number가 들어가 있다. , 어차피 offset은 동일 하므로 넣지 않는다.
- offset을 넣지 않는 대신 하위 12bits에는 그 페이지를 표현하는 여러가지 속성들이 들어가 있다.
- 이러한 특징 때문에 페이지테이블의 크기가 상당히 크다.
- 만약 페이지 넘버가 22bit 라면 2^22 이고 한페이지마다 1word(4바이트) 이므로 2^22 X 4바이트 = 16MB 의 크기가 페이지테이블을 위해 사용된다. -> Swapping 으로 해결


### 정리

- 요즘 OS 는 페이징을 지원하며 이것을 지원해주기 위한 하드웨어 MMU가 칩 속에 다 구현되어있다.