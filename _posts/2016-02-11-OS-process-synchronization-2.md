---
layout: post
title: "[OS]Process Synchronization(2)"
description: "[OS]프로세스 동기화(2)" 
modified: 2016-02-13
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

Semaphore 기법에 대해 좀더 자세히 알아보고  Mutual exclusion 의 다른 기법인  Monitor에 대해 알아 보자 

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Semaphore

- 이전 글에서 세마포어의 기본 개념에 대해 알아 보았다.
- 세마 포어란 쉽게 말해 프로세스 Synchronization을 위한 int형 변수이다

### Semaphore 단점

- 하지만 이 세마포어도 큰 단점이 존재 하는데 바로 Unstructured Programming Construct 이기 때문에 컴파일러 등의 도구를 사용한 디버깅이 어렵다는 단점이 있다.

>structured Programming Construct : if 문을 사용할때 {} 와 같은 괄호를 써줘서 컴파일러가 디버깅 할 수 있는 것을 말한다.

<figure>
	<img src="/images/post6-1.PNG" alt="">
</figure>

- 위 소스코드가 세마포어 단점의 한 예 이다.
- Producer 와 Consumer 라는 프로세스 두개가 존재 할때, P와 V로 만든 Crtical Section 을 구현한 코드라면 Argument가 같아야하는데 Consumenr 의 Argument가 다르기 이 S2 를 S1으로 고쳐야 하는지 .. 아니면 다른 의도로 만들었다면 Producer의 V(S1)을 V(S2)로 고쳐야 할지 안 방법이 없다.
- 다시 말해서 이 소스코드를 만든 제작자의 의도가 Critical Section 을 의도 한건지, 아니면 그냥 스케줄링 관점을 의도한 건지 세마포어는 Unstructured Programming Construct 이기 때문에 컴파일러 도구를 사용하여 디버깅을 할 수 없기 때문에 버그가 나기 쉽다.

### Semaphore 단점 해결법

<figure>
	<img src="/images/post6-2.PNG" alt="">
</figure>

- P(), V() 라는 API 이름 대신에  mutex_ 를 붙인 API 함수를 사용한다.

<figure>
	<img src="/images/post6-3.PNG" alt="">
</figure>

- 기존 Semaphore API는 위 표와 같은 기능을 했다.
- 기존 lock() , unlock()을 이용하요 Mutual exclusion 을 구현 하려고 할때  mutex_ 를 붙여서 사용한다.
- mutex_lock() , mutex_unlock() 을 사용하면 이 함수는 반드시 같은 세마포어를 argument로 받아 Critical section 을 구현해야 한다.
- 즉 위 소스에서  mutex_ 를 사용 했으므로 Task2의 S2를 S1으로 바꾸면 된다 .

### Mutext 가 가진 추가 기능

- Mutual Exclusion을 구현하기 위해 사용하는 sleeping Lock
- 동일한 Mutex를 사용할 때 mutex_lock()을 호출한 프로세스와 mutex_unlock()을 호출한 프로세스가 일치하여야 한다.
- 동일한 프로세스인지 mutex_ 는 체크하는 기능을 가지고 있다.
- 즉 문을 닫고 들어간 사람이 문을 열고 나갈 수 있기 때문이다.

### Semaphore 구현 방법

<figure>
	<img src="/images/post6-4.PNG" alt="">
</figure>

- 세마포어는 int형 정수(0,1 또는 열쇠의 수에 따라 0,1,2 등..)로 표현된다고 말했다.
- 하지만 열쇠가 없어서 들어가지 못한 프로세스들이 대기하는 waiting queue 가 존재 해야한다.
- 세마포어는 위 코드처럼 int 형 변수와 큐를 가진 구조체이다.

### P() , V() 구현 방법(싱글 프로세서)

<figure>
	<img src="/images/post6-5.PNG" alt="">
</figure>

- 세마포어 자체도 글로벌 변수이기 떄문에 이런 세마포어도 가드를 하기 위해 인터럽트를 걸어 준다. 즉 disableInterrupts() , enableInterrupts() 를 사용한다.
- disableInterrupts() , enableInterrupts()는 굉장히 강력하지만 짧은 시간동안만 사용하기때문에 큰 상관이 없다.
- S.cnt 를 검사하여 열쇠가 몇개인지 판단하고 그 결과에 따라 큐를 대기시킬지, 깨울지 조건에 따라 결정 하고  열쇠의 수를 감소시키거나 증가 시킨다.
- 여기서 추가적으로 알아야 할 것이 있다. 바로 세마포어의 카운트 값이 음수일 경우 이 음수의 절대값이 큐에서 대기하고 있는 프로세스의 개수이고 또 양수일 경우 남아 있는 열쇠(자원)의 개수 이다.

### 멀티 프로세서에서 세마 포어 구현

- 위 메커니즘은 싱글 프로세서 에서 작동하는 메커니즘이다.
- 기존 싱글 프로세서에서 세마 포어는는 disable 이라는 메커니즘을 기반으로 구현을 하혔다.
- 어떻게 하면 멀티 프로세서 에서도 작동하는 메커니즘을 만들까? -> Atomic Operation이 필요 하다. 다시 말해서 글로벌 변수(자원) 을 읽고, 수정 하고,쓰고 , 다시 되돌리는 과정중 에 다른 프로세서가 그 글로벌 변수에 침입하지 못하도록 막는 것이 필요하다.

<figure>
	<img src="/images/post6-6.PNG" alt="">
</figure>

- 위 그림을 보면 이해가 쉬울 것이다.
- 맨처음 버스 아비터에게 버스를 쓰겠다고 요청하고 허가를 받은후 글로벌 변수를 읽는다. 여기까지가 Read 이고 읽어온 글로벌 변수를 수정한다(modify), 그리고 수정된 변수를 다시 메모리에 올리고 아비터에게 사용이 끝남을 알린다.(write) 
- 1,2,3 번이 한 사이클로 동작 되는 것을 Atomic Operation 이라 하고 이 동작이 되는 동안 다른 프로세서는 버스를 사용할 수 없다.

### TAS(Test-and-Set)

- 멀티프로세서 에서 위와 같은  Atomic Operation 을 구현하는 대표적 방식중 하나인 TAS(Test-and-Set)은 하드웨어가 제공해주는 Instruction 으로 TAS 의 파라미터로 메모리 location(lock_var 변수)이 들어간다. 
- 그럼 TAS 는 이 lock_var 변수를 읽어(read) 들여서 이 변수를 1인지 0인지 Test 한다. 
- 그리고 이 값을 1이던 0이던 무조건 1로 만들어 버린후 사용 한다. 즉 하나의 TAS 명령에서 읽고, 수정하고, 쓰기를 한다. 추가적으로 버스를 완전히 장학한다.
- 정확히 정리하자면 메모리의 Boolean 변수를 읽어서 확인한 후 값을 1로 쓰는 작업을 Atomic하게 수행하는 명령어 이다.

### TAS 사용의 예


```
 while(TAS(lock_var)!=0)
{
		.
		.
		.
}



// Critical Section    
// 공유 자원을 다 사용하면 lock_var = 0

if(use shared resource == FALSE)
	lock_var = 0;



```
- TAS()는 lock_var 을 읽어서 그 값을 체크하고, 리턴 하는데 0 이 아니면 무한 루프를 돌고 0이면 루프를 빠져 나온다.
- 어떤 한 프로세서가 공유자원을 사용 하고 있다면 글로벌 변수 lock_var 은 1이기 때문에 다른 프로세서는 While 문을 계속 돌고 있을 것이다.
- 공유 자원을 다 사용하면 lock_var = 0 으로 만들어주고 다른 프로세서가 루프문을 빠져나와 공유자원을 사용할 수 있다.



### TAS 정리

- 멀티프로세서 Synchronization 을 하기위해서는 하드웨어적 서포트가 필요하다. 
- 그 하드웨어적 서포트는 바로 글로벌 변수(lock_var)를 읽고, 수정하고, 다시 되돌리는 과정중 다른 프로세서가 진입하지 못하도록하는 Atomic operation을 만드는 것이다.
- 그 중 멀티프로세서에서 사용되는 가장 일반적인 방법이 TAS 이다.
- TAS 는 글로벌 변수의 값을 읽어와 이놈이 0이면 0을 리턴하고 1이면 1을 리턴 하는데, 1이든 0이든 무조건 1을 쓰게 하여 루프문을 돌게 한다. 그렇게 하여 다른 프로세서가 자원을 사용중일 때 자신은 루프문을 돌아 침범하지 않도록 한다. 

### TAS 의 문제점

- 기존 싱글프로세서 세마포어는 웨이팅 큐에 들어가기 때문에 CPU에 큰 영향을 끼치지 않지만
- 멀티 프로세서의 TAS 는 한 프로세서가 루프에 들어가서 계속 돌고 있다. 
- 이것을 Busy Waiting (또는 Spin lock) 이라 한다. 
- 이 Spin lock 은 여러가지 나쁜 문제들을 초래한다.

### 스마트폰의 Lockup 문제

- 스마트폰의 Lockup 문제가 대표적인 Spin lock 문제이다.
- ex) 유저 프로세스가 자원을 사용하고 싶은데 그 자원이 Spin Lock 에의해 가드가 되어있다.
- 즉 다른 프로세서에 의해서 자원(lock_var)이 잡혀 있을때 자신은 자원이 풀릴 때까지 계속 Spinning 을 하게 된다.
- 근데 어떠한 예기치않은 상황(인터럽트 등..) 때문에 자원(lock_var)을 가지고 있던 프로세서가 쫒겨나고 이상한놈이 그 자원을 쓰고 있다면... 자신은 아무이유도 모르고 Spinning 을 하고 있을 것이다.
- 이런 문제를 Lock Holder Preemption 이라 한다

### Lock Holder Preemption Problem

- 내가 lock_var(자원) 을 잡기위해서 루프를 돌고 있는데 그 lock_var 을 풀어 줄수 있는 놈이 쫒겨난 경우.. 
- 요즘 같이 멀티프로세서 를 사용하는 경우 이 문제가 많이 발생 된다.

### 세마포어 총정리

-프로세스의 Synchronization 을 제공하기위해서 OS 의 차원의 메커니즘이 세마포어인데 세마포어를 구현하려면 하드웨어적인 지원이 필요하다 싱글 프로세서일 경우에는 disableinterrupt ,enableinterrupt 를 사용하면 되고 멀티 프로세서일 경우는 TAS 같은 atomic operation 을 사용 하면 된다.

### 멀티프로세서도 가능한 세마포어 구현 방법

<figure>
	<img src="/images/post6-5.PNG" alt="">
</figure>

위와 같은 기존 싱글 프로세서에서 돌아가는 세마포어 코드에서 아래와 같이 수정해 준다.

```

disableInterrupt();
->  disableInterrupt();
    while (TAS(lockMem) ! = 0) continue;

enableInterrupt();
->  lockMem = 0;
	enableInterrupt();
 
```

## 또 다른 Synchronization 메커니즘 Monitor

- 기본적으로 세마포어를 사용한다.
- 세마포어의 Unstructured Programming Construct 의 단점을 개선하기 위해 만들어진 메커니즘이 Monitor 이다
- Monitor 는 Abstract Data Type(클래스)의 구조를 기반으로 출발한다. 즉 멤버 변수와, 멤버 함수를 가지고 있다.

### Monitor의 개념

- 기존 세마포어는 어셈블리어 수준이었다면, Monitor는 C++ 이나 JAVA 와 같은 하이레벨 언어로 제작되었다.

```
// C 스타일의 모니터

monitor QueueHandler
{
	struct{...} queue;  // shared date
	
	addToQueue(val)
	{
	 " code to add shared queue "
	}	

	int removeFromQueue()
	{
	 " code to remove from queue "
	}

}
 
```

- monitor 인 큐핸들러 이다.
- 공유 데이터가 큐인 인 멤버변수 공유데이터가 있고 공유 데이터에 값을 넣는 add 함수와 공유데이터에서 값을 가져오는 remove 함수가 있다.
- 공유 데이터가 있기 때문에 Synchronization 이 필요하다.


<figure>
	<img src="/images/post6-7.PNG" alt="">
</figure>

- 공유자원에 추가하고 제거하는 수행을 하다가 어떤 조건(Condition variables)이 발생하는 경우가 있다. 
- 그럼 그 조건에 맞게 wait() 또는 signal() 을 해야한다.

```

// resource_manager 라는 모니터 

var busy: bollean ;     // 공유 자원
x : condition;          // condition 변수

procedure entry acquire()   
{
	if(busy) x.wait;
	busy = true;
}

procedure entry release()
{
	busy = false;
	x.signal;
}
 
initialization()
{
	busy = false;
}

```

- acquire() 메소드는 busy의 값을 읽어서 True 이면 자신이 wait를 하고 누군가가 자신을 꺠워주면 busy를 True로 만들고 자신의 일을 한다.
- release() 메소드는 busy 를 false로 만들고 자기 때문에 기다리고 있는 프로세스가 있으면 깨워준다.
- 모니터의 동기화를 좀더 완벽하게 하기 위해서 조건 변수라는(Condition 변수)것을 추가하였다.
- Monitor의 Condition 변수(조건 변수)는 어떤 조건이 충족되기를 기다리고 있는 Process들의 Waiting Queue 이다. 즉 이 큐는 wait 와 signal 이라는 명령어를 가지고 있고 x.signal은 waiting 큐에서 대기중인 프로세스가 깨어나는것, x.wait 는 프로세스가 큐에 대기 한다는 동작 이다.
- **Monitor 는 한번에 하나의 Process만 내부의 함수를 수행 할 수 있도록 허용하기 때문에 Monitor 내부의 공유 자원(공유 변수)를 따로 보호할 필요가 없다.**

### Hoare Sytle Monitor

Wait 큐에서 깨어난 Process 가 바로 Monitor 내부로 진입하는 방식

### Brinch-hansen Style Monitor

Wait 큐에서 Sinal을 보낸 Process가 수행을 계속하는 방식의 Monitor

### Monitor 구현

- Monitor는 OS의 메커니즘이라기 보다 프로그래밍 언어의 메커니즘이다.
- 즉 컴파일러가 Monitor 를 세마포어로 변환 시켜줘야 동작을 한다.
- 

```
/*Hoare Sytle Monitor*/


P(monitor_lock);
	Body of the Function;
if(sig_lock_count > 0) 
{
	V(sig_lock);
}
else
{
	V(monitor_lock);
}

// x.wait
x_count++;

if(sig_lock_count > 0)
{
	V(sig_lock);
}
else
{
	V(monitor_lock);
}
 P(x_lock);
x_count--;



// x.signal
if(x_count > 0)
{
	sig_lock_count++;
	V(x_lock);
	P(sig_lock);
	sig_lock_count--;
}


//monitor_lock  : 모니터를 위한 큐를 가지고 있는 세마포어
//sig_lock      : 시그널을 위한 큐를 가지고 있는 세마포어
//x_lock        : condition 변수를 위한 큐를 가지고 있는 세마포어

```
<figure>
	<img src="/images/post6-8.PNG" alt="">
</figure>

우선적으로 공유자원이 몇개인지 파악 or 큐의 수를 파악 하여 총 세마포어 수를 파악한다.

1. condition 변수 수에 맞게 큐가 필요하다. -> x_lock
2. Hoare Sytle Monitor에서 Sinal을 보낸 Process 가 Monitor 밖에서 대기하기 위한 큐가 필요하다. -> sig_lock
3. monitor_lock 큐

이제 동작 을 보자

1. 제일 먼저 모니터에 들어가려면 모니터 함수를 호출하기 전에 P(monitor_lock)으로 문을 따고 들어가야 한다.
2. 모니터안의 함수를 수행하고 다 끝나면 V()를 해서 꺠워줘야 하는데 우선적으로 signaler 에잇는 큐를 깨워준다 -> V(sig_lock)
3. 시그널 큐의 카운트를 판단하여 없다면 monitor_lock 에 있는 놈을 꺠워준다.

wait 를 보자

1. wait 가 불려 진 시점에서 아직 진행되던 프로세스는 모니터 안에 있으므로 x_count(wait 카운트)를 하나 증가시키고
2. 모니터를 빠져나오니깐 나대신 다른 프로세스를 넣어주어야 하기때문에 우선적으로 signaler 를 확인하고 없으면 monitor_lock 에 있는 프로세스를 모니터에 넣어 준다.
3. 자신은 x_lock(condition 큐)로 빠져나온다. -> P(x_lock)
4. 만약 깨어나면 다시 x_count-- 을하고 모니터 안에서 진행한다.

signal을 보자

1. x_count 의 값을 확인하여 0보다 클경우 waiting 큐에 기다리는 프로세스가 있으므로 자신은 signaler로 들어가야 하기때문에  sig_lock_count 를 1증가 시키고
2. V(x_lock)으로 condtion 변수에 wait 프로세스를 깨워주고
3. P(sig_lock)으로 자신은 sinaler 큐에 wait 한다.

### 정리

- Process Synchronization 은 굉장히 어려운 부분이 많은것 같다..
- 여러 책하고 사이트를 보면서 부족한 부분을 정리하고 고쳐나가야 할 것 같다.

 