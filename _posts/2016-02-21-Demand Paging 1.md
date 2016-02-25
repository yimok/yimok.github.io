---
layout: post
title: "[OS]Demand Paging(1)"
description: "[OS]Demand Paging(1)" 
modified: 2016-02-20
tags: [blog]
comments: true
image:
  feature: back6.jpg
---
Demand Paging이 무엇이고 왜 필요한지 알아보자. 

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## Demand Paging 

- 프로그램이 필요로하는 모든 메모리(Code,Data,Stack Segment)가 물리 메모리에 있어야 하는것은 아니다. 프로그램은 Locality를 가지고 있기때문에 필요한 것만 물리메모리에 올려서 사용한다.
- 여기서 Locality란 프로그램이 가장 최근에 접근했던 데이터를 다시 접근하거나 최근에 참조했던 데이터 근처의 주소를 참조하는 경향이 있는 것이다.
- 이와 같이 프로그램의 Locality 때문에 Demand Paging이 가능하다.
- Demand Paging 은 집중적으로 액세스되는 페이지들만 필요할때 읽어들이는 것이다.


### Virtual address

- 존재하지 않는 물리메모리를 표현하는 주소공간 
- 논리 메모리라고도 한다.
- 기존에는 Physical Address 를 RAM으로 보았지만 I/O 장치들도 Physical Address 이다.

### Swap Device


<figure>
	<img src="/images/dp1.PNG" alt="">
</figure>

- 프로그램에서 물리메모리에 저장되지 못한 페이지들을 저장하는 디스크 공간으로 File에 비해 운영체제가 직접 빠르게 접근 할 수 있다.

### 이상적인 Demand Paging의 동작


- 앞으로 사용될 페이지와 사용되지 않을 페이지를 미리 예측해서 Physical Memory로 불러들이거나, Swap Device로 내보내는 것
- Residence Bit 를 사용 -> 대상 페이지가 Physical Memory에 있는지 Swap Device에 있는지를 표시하는 Page Table의 플래그


## Page Fault 

- Page Fault란 Virtual Address가 가리키는 Page가 Physical Memory에 없어서 프로세스가 더 이상 진행할 수 없는 상태를 운영체제에게 알려주는 인터럽트이다.
- Page Fault가 발생했을때 현재 수행중이던 프로세스는 차단이 되고 Page Fault handler가 나타난다.

### Page Fault Handler

1. Page Fault Handler는 DMA Controller에게 해당 Page의 주소를 전달한다.
2. 해당 Page를 Phyisical Memory로 로드시킨다.
3. DMA Controller의 작업이 끝나면 인터럽트 발생
4. 운영체제는 Page Fault를 일으킨 프로세스의 수행을 재개

하지만 Page Fault의 처리가 다른 인터럽트에 비해 어렵다. 그 이유는 기존 인터럽트는 현재 수행중인 명령이 끝나고 진행 했지만 Page Fault는 수행중인 명령에 의해 변화된 상태를 되돌렸다가 Page Fault 처리가 끝난 후 해당 명령을 재개해야 하기 때문이다.

### Page Fault를 어떻게 최소화 하는가.	


- Page selection policy : 어떤 페이지를 언제 메모리로 불러들일 것인가.
- Page replacement Policy : 어떤 페이지를 골라 swap device로 보낼 것인가.
- Page replacement style : 교체할 페이지를 전체 프로세스에서 고르냐 vs 특정 프로세스에서 고르냐
- Page Placement style(페이지 할당 스타일) : 페이지를 할당 할때 어떻게 할당 할 것이냐.(Static or Dynamic)   

### Page selection policy

- Prepaging : 앞으로 사용될 Page를 예측해서 미리 Main Memory로 로드하는 기법 -> Locality에 기반하여 Page Fault가 발생한 근처에 있는 Page들을 Main Memory로 로드	
- Request Paging(=Overlay) : 논리적으로 연관성이 있는 Page들을 미리 Main Memory로 로드하는 기법(과거 MMU가 없을때 사용함)
- Working set : Prepaing 과 Request Paging 을 결합하여 OS가 자동적으로 예측한 페이지를 올

### Page replacement Policy 

- 메인메모리에 새로운 페이지를 읽어들이려고 하는데 사용가능한 페이지 frame 공간이 없을때 강제로 만들어야한다. 그때 사용하는것이 Page replacement Policy  이다.
- Random : 임의로 페이지를 골라 swap device로 보낸다.(하드웨어적으로 구현)
- FIFO : 메모리에 가장 오래있던 페이지를 골라 swap device로 보낸다. (많이 사용되지만 페이지 교체 정책으로 적절하지 않을수 있다. -> 부팅시 만들어진 중요한 페이지들을 보내버릴수도 있기때문에)
- OPT(Optimal) : 가장 먼 미래동안 사용되지않을 페이지를 골라서 내보내는것 -> 페이지의 로그를 미리 다 알고 있어야 구현가능(현실적으로 불가능)
- LRU(Least Recently Use): 최근에 최소 사용된 페이지를 swap device 로 보낸다. -> LRU 알고리즘은 프로그램의 Locality에 기하기 때문에 잘 동작한다.
- 실제적으로 FIFO와 LRU 알고리즘을 많이 사용한다.
- FIFO는 연결리스트 큐로 만들어 구현
- LRU는 어떻게 구현할까? 페이지 프레임마다 Counter 레지스터를 두어 사용될때마다 Counter를 변경하여 빈도수를 측정하자 -> 현실적으로 오버헤드가 너무큼 -> 카운터 레지스터 대신에 한 비트를 두어서 어떤 페이지가 액세스되면 1로 set하고 액세스되지않으면 0으로 set 하는 Reference Bit(Use bit)을 둔다. 
 
<figure>
	<img src="/images/replace.PNG" alt="">
</figure>

- 페이지 A B C D를 페이지 프레임 3개인 공간에 LRU, FIFO, OPT를 사용하여 집어넣는 그림이다.

### 교체정책 - LRU 구현(Clock Algorithm)

- FIFO 로 Page replacement를 할경우 메모리를 늘렸음에도 불구하고 페이지 폴트가 더 많이 발생하는 Belay's Anomaly 현상이 나타난다.
- 사람들은 그래서 LRU에 더 관심을 가지게 된다.
- LRU 를 초창기에 구현할때는 카운트할 수 있는 레지스터를 넣으려고 했지만 오버헤드가 굉장히 커지고 비효율적이었다
- 그래서 한 비트를 Reference bit으로 잡고 시간 간격을 나누어 돌리는 방법 Clock 알고리즘을 사용했다. 이 알고리즘은 일정 시간간격에 Reference bit가 1인지 0인지 판단(최근에 사용 했는지 안헀는지)하여 교체하고, 그 시간간격이 지나가면 비트를 모두 리셋하는 방법이다.

<figure>
	<img src="/images/clock.PNG" alt="">
</figure>

[그림 출처](http://pages.cs.wisc.edu/~bart/537/lecturenotes/s20.html)

- 페이지가 교체할 시기가 오면 클락 알고리즘을 돌린다. 즉 클락 핸드를 돌리는데
- 중앙에서 도는 선이 Clock Hand 이고 이 Clock Hand가 가리키는 Page의 Reference Bit이 1인 경우 최근에 사용 되었다는 표시 이므로 0으로 바꾸고 Clock Hand가 다음 Page를 가리키도록 한다. 
- 이 과정을 반복하다가 Reference Bit이 0인 Page를 만나면 해당 페이지는 최근에 사용하지 않은 페이지이므로 교체한다.
- 즉 Reference Bit 이 0인것을 찾아 교체한다.
- 만약 모든 Reference Bit이 1이라면 그 1인 Reference Bit 페이지들을 FIFO 알고리즘으로 다시 추려낸다.

### 교체정책 - FIFO + Frame Buffering 구현

- **하드웨어적으로 Reference bit이 지원이 안된다면 FIFO를 사용해야한다.**
- VAX/VMS 시스템에서 Frame Buffering을 개발하여 FIFO의 단점을 개선함
- 기본적인 FIFO 알고리즘은 연결리스트 큐의 형태로 물리메모리에 먼저들어온 페이지(Used Page Frame) 순서대로 저장되며 마찬가지로 교체가 일어나면 가장 앞에 Page Frame이 버려진다.
- Frame Buffer 알고리즘은 free page Frame 들이 저장되는 연결리스트 큐를 하나더 만들어 교체되어 버려진 프레임들을 저장해놓았다가 만약 다시 사용해야 할 경우 다시 Used Page Frame 큐에 붙여서 사용한다.
- 즉 한번더 기회를 주는 방식이다.

### Page replacement style

- 메모리 할당 스타일을 말한다.
- 메모리를 요구하는 주체를 프로세스로 볼 수도 있고, 유저 단위로도 볼 수 있다. 또는 시스템 단위로 볼 수도 있다.
- **Per-Process replacement(프로세스 단위) : 동적으로 현재 메모리가 부족한지 아닌지 판단하여 페이지를 프로세스들에게 효과적으로 배분한다. -> 단위 시간동안 발생한 Page Fault 횟수로 확인(Page Fault가 많을수록 메모리가 부족한것) **
- Per-job replacement(유저단위) : 다른 Job을 보호해 줄 수 있지만 미리 할당을 했기때문에 job 마다 메모리 불공평이 있을 수 있다.
- Global Replacement(시스템 단위) : 같은 시스템 내에서 한 놈이 메모리를 지나치게 쓴다면 나머지에게 악영향을 줌 하지만 잘 사용한다면 효과적임


## 정리

- 과거에는 프로그램과 관련된 모든 메모리가 물리메모리 위에 올라가 있었다. 하지만 이런식으로 작동시키면 메모리 가격도 비싸고 프로그램의 locality 특성 때문에 비효율적이다.
- 그래서 프로그램에서 램에 올리는 용량은 적게 만들고 그대신 싼 디스크를 swap device로 사용하는 기법인 virtual memory management 를 사용했다. 
- 그리고 virtual memory management 는 논리주소를 물리주소로 바꾸는 MMU의 지원이 꼭 필요하다.
- 하지만 Demanding Paging 을 하게되면 페이지 폴트가 발생하게 되고 이런 페이티 폴트를 최소화하는 정책들이 만들어지게 된다.
- 페이지 선택정책, 교체 정책 등등..
- 페이지 교체 정책에서는 FIFO와 LRU가 사용되며 LRU 는 Clock 알고리즘을 사용하여 구현한다. FIFO의 단점을 개선하기 위해 FIFO + Frame Buffer 를 같이 사용한다.

