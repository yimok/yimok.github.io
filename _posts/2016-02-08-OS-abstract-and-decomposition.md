---
layout: post
title: "[OS]Abstraction and Decomposition"
description: "[OS]Abstraction and Decomposition" 
modified: 2016-02-13
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

Abstraction 과 Decomposition에 대해 알아보자.  

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Abstraction 

- OS는 Complexity(복잡한) 소프트웨어다. 이러한 복잡함을 해결하려면 Abstraction 과 Decomposition을 사용해야한다.
- 추상화(Abstraction)를 시스템 디자인에 적용하면 Layered Architecture 가 나오게 된다.


### Layered Architecture

<figure>
	<img src="/images/postab1.PNG" alt="">
</figure>

- 위 그림은 Layered Architecture 이다.
- 여기서 OS 레이어의 역할은 아래 복잡한 하드웨어를 보이지 않게 해서 꼭 필요한 인터페이스만 위로 제공해 주는 것이 OS 레이어의 역할이다.
- 그리고 각 레이어가 만나는 곳 즉 계층과 계층 사이에는 통신을 위해 정의된 호출 규약 API(Application Programming Interface) 가 존재한다.
- 위와 같이 계층구조를 나타내게 해주는 것이 Abstraction 의 기능이다.
- 아래 계층은 위 계층에게 인터페이스(추상화)를 제공해준다. 그리고 위 계층은 아래계층에서 제공한 인터페이스를 사용한다. 즉 위 계층은 아래 계층이 제공하는 기능만을 사용 할 수 있으며 반대의 경우는 발생하지 않아야 한다.
- 이렇게 추상화 된 레이어 아키텍처를 위에서부터 구체화하는 작업을 Decomposition 이라고 한다.
- 
### API(Application Programming Interface)

- 계층과 계층 사이의 통신을 위해 정의된 호출 규약
- ex) OS의 API는 바로 System Call(함수) 들이다.

### Layering Principle

위의 계층은 아래 계층이 제공하는 기능만을 사용할 수 있으며 반대의 경우는 발생하지 않아야 한다.

## Decomposition

<figure>
	<img src="/images/postab2.PNG" alt="">
</figure>

- OS를 5가지 부분으로 나눈다(Decomposition) 프로세서 스케줄러 부분 ,파일 시스템 부분, 메모리 관리 부분, I/O 관리 부분, 네트워크 관리 부분 이렇게 또 쪼개서 점점 구체화 하는 작업을 한다.
