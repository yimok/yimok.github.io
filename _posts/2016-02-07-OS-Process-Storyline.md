---
layout: post
title: "[OS]Dispatcher 동작 흐름"
description: "[OS]Dispatcher 동작 흐름" 
modified: 2016-02-13
tags: [blog]
comments: true
image:
  feature: back1.jpg
---
Process의 Dispatcher 흐름을 보도록 하자

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Dispatcher 동작 흐름

- 디스패처가 진행되려면 인터럽트가 꼭 필요하다.
- 인터럽트가 걸리면 스택에 현재명령위치와 PSW를 저장해야한다

### 1단계
<figure>
	<img src="/images/post5-1.PNG" alt="">
</figure>

- 마이크로프로세서에는 스택의 Top을 가리키는 스택 포인터(SP 레지스터)를 제공 한다.
- 현재 어떤 프로세스가 수행하고 있으면 이 SP 레지스터가 스택의 TOP주소를 가리키고 있다.
- OS에는 전역 변수가 하나 있다. 그것이 OS PCB Current(OS Process Control Bolock Current : 현재 수행중인 프로세스 컨트롤 블록 이라는 뜻이다.)이다. 
- 현재 수행중인 PCB에 대한 포인터를 OS가 변수에 둬서 가리키고 있다.
- 복습(참고) : PCB안에는 현재 수행중인 프로세스의 ID 값, 스케줄링의 여러 정보 값, Context Switching 하는데 필요한 정보 값(스택 포인터 필드 Stack Pointer) 이 들어가 있다.

### 2단계

<figure>
	<img src="/images/post5-2.PNG" alt="">
</figure>

- 인터럽트가 딱 걸리면 스택의 탑에 PSW가 저장된다. 
- 2개의 WORD의 주소가  저장되는데(인텔 특징상 2개로 저장됨) -> 2개가 리턴 주소다.


### 3단계

<figure>
	<img src="/images/post5-3.PNG" alt="">
</figure>

- 위 과정을 겪고 난후 해당 인터럽트 서비스 루틴으로 점프(jmp)를 해야 한다.
- CPU 레지스터들의 모든 값들을 스택에 대피 시켜야한다. 인텔 프로세서는  이것을 도와주기 위해서 PUSHA(push all) 이라는 함수를 가지고 있는데 이 PUSHA 하면 이 모든 레지스터가 스택에 쫙 들어가게 된다. 위 사진이 그 모습이다.
- 저장되지 않는 몇 개의 레지스터가 있긴 한데 별도의 push 명령으로 집어 넣는다.
- SP 레지스터가 가리키고 있는 값이 맨 아래로 이동했다는 것을 기억하자.
 
>스택에 저장되어있는 SP레지스터는?? 값이 계속 바뀌는데 왜있을까..? -> 그냥 엉터리 값이다. 진짜 값은 스택에 저장 못시키고 PCB에 저장 시킨다. 결과적으로 PCB의 스택포인터 값과 CPU의 스택포인터 값이 같은 곳을 가리키게 된다.

### 4단계

<figure>
	<img src="/images/post5-4.PNG" alt="">
</figure>

- 사실상 cpu context 레지스터 대피는 모두 완료되었다.

- 그러면 이제 인터럽트에 맞게 진행이 되어야 하는데. 만약 Time out 인터럽트라고 하면  스케줄러를 호출하고 이 스케줄러가 다음에 돌아야 될 프로세스를 알려준다.
- 어떻게 알려 주냐면? -> 다음에 돌아야 될 프로세스의 PCB 포인터값을 인터럽트 서비스 루틴 한테 전달해 준다. -> 즉 OS PCB Current 에 돌아야할 PCB 포인터 값을 전달해준다.
- 그럼 OS PCB Current는 새로운 프로세스(PCB)를 가리키게 된다.
- 새로운 PCB도 역시나 스택이 있다. 그런데 이 스택도 이전 프로세스가 가리킨 스택과 똑같은 모습을 하고 있다? -> 이놈도 Context switching을 한번이라도 당했으면 인터럽트 서비스 루틴에서 스택을 만들어주니깐 당연히 똑같은 모습을 가지게 된다.
- CPU의 스택포인터 값을 새로 받아온 PCB의 스택포인터 값으로 집어넣어주어 POP할 스택을 다시 잡아준다.

### 5단계 
<figure>
	<img src="/images/post5-5.PNG" alt="">
</figure>

- 이제 Pop을 한다. -> 즉 이제 새로 수행될 프로세스의 메모리 레지스터(Context) 값들이 CPU 레지스터로 들어오게 된다.
- Return 함수를 사용하면 복귀하면 된다.

### Fake Stack

- 위와 같은 진행 흐름은 거의 모든 동작에 잘 작동된다.  
- 단 한 가지 예외가 있다. 
- 바로 처음 프로세스가 만들어 졌을 경우이다.
- 이런 경우엔 Fake Stack을 OS가 만들어 주어야한다.

<figure>
	<img src="/images/post5-6.PNG" alt="">
</figure>

- OS가 어떤 프로세스를 처음 생성하게 되면 그 프로세스의 스택을 마치 Context Switching을 한번이라도 당한 것처럼 만들어 줘야한다.
- 마치 인터럽트를 당한 것 처럼 PSW(모드비트 1, 인터럽트 enable)와 리턴 주소를 넣어 준다.
- 리턴 주소로는 그 프로세스의 시작주소(entry point)를 넣어준다. 왜냐면 아직 시작하지도 않았으므로..
- 나머지 레지스터의 값들은 어차피 오버 라이드 되므로 아무 값을 넣어도 상관없지만 기본적으로 0으로 채워 넣어준다.
- 그리고 마지막을 PCB의 스택 포인터 값을 스택의 Top 주소로 가리키게 하도록 하면 끝이다.

## 정리

- 이러한 스택은 메인메모리에 있다!! 다시말해서 메인메모리 아무 곳 에나 있다. -> 각 프로세스별로 전부 별도로 한 개씩 스택을 따로 가지고 있다. 
- 즉 메인메모리에 스택이 여러 개가 있고 단지 활성화된 스택은 한 개가 있는 것이다.
