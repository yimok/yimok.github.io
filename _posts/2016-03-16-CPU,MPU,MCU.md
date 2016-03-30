---
layout: post
title: "CPU,MCU,MPU의 차이"
description: "CPU,MCU,MPU의 차이" 
modified: 2016-03-16
tags: [blog]
comments: true
image:
  feature: back6.jpg
---
CPU,MCU,MPU의 차이에 대해 알아보자

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## CPU

### CPU(Central Processing Unit)

<figure>
	<img src="/images/cpu.PNG" alt="">
</figure>

[그림 출처](http://http://donghwada.tistory.com/entry/CPU-%EA%B5%AC%EC%A1%B0)
- 컴퓨터 중앙 처리 장치 CPU는 프로그램 명령어를 실행하는 일을 담당하며 제어장치(Control Unit), 연산장치(ALU), 레지스터 세부분으로 구성된다 그리고 주기억장치를 비롯한 다른 장치들과 시스템 버스로 연결되어 있다.



## MPU

### MPU(Micro Processing Unit)

- CPU를 하나의 단일 IC(Intergrated Circuit) 칩에 집적시켜 만든 반도체 소자를 마이크로 프로세서 유닛 MPU 라고 한다.
- CPU의 여러 형태 중 소자가 하나인 종류가 MPU이며, 모든 MPU는 CPU지만 모든 CPU가 MPU인 것은 아니다.
- MPU 는 MCU 와 달리 주변장치가 필요하다.

## MCU

### MCU(Micro Controller Unit)
<figure>
	<img src="/images/mcu.png" alt="">
</figure>

[그림 출처](http://www.ddaily.co.kr/news/article.html?no=117571)

- MCU 은 CPU 기능은 물론이고 일정한 용량의 메모리, 입출력 제어 인터페이스, 주변장치 컨트롤러 회로까지 칩 하나에 내장한 반도체이다.
- 즉 MCU는 PC의 메인보드 전체를 칩 하나에 집적시켜 놓은 것이라고 볼 수 있다. 그래서 기능이 많은 MCU의 경우, 칩에 전원을 연결하고 입출력 장치를 연결하기만 하면 그것 자체로 일종의 작은 컴퓨터가 되기도 한다.


