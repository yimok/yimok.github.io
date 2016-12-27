---
layout: page
title: ""
modified: 2016-12-25
tags: [blog]
comments: true
image:
  feature: back8.jpg
---


<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


# Line Tracer - Using Remote Controller
--------
- Cortex-m4 마이크로프로세서를 사용하여 만든 라인트레이서
- github : [https://github.com/yimok/Line-Tracer](https://github.com/yimok/Line-Tracer)

# 개발 환경
- IAR Embedded Workbench
- C 언어사용
- ComportMaster(디버깅용 Usart 툴)


# 사용한 부품 및 센서

<figure>
<p style="text-align: center;">	
	<img src="/images/sensor1.png">
</p>
</figure>
<figure>
<p style="text-align: center;">	
	<img src="/images/sensor2.png">
</p>
</figure>

# 회로 스케치

<figure>
<p style="text-align: center;">	
	<img src="/images/sketch.jpg">
</p>
</figure>

# 구현 기능 - Remote Controller

- 가속도 센서를 기판 중앙에 장착하고 , stm32 보드 1개와 블루투스를 장착 후 연결 , 3.7v 배터리를 5v 승압기에 연결하여 마이크로프로세서에 전압 인가
- 리모트 컨트롤 기울기에따라 총 10가지 동작가능 0~9 의 숫자를 블루투스 통신을 사용해 라인트레이서 마이크로프로세서쪽으로 전송
- 앞으로 3단계 뒤로 3단계 좌우 각각 2단계 제자리 1단계

# 구현 기능 - Line Tracer

- 기판위에 적외선센서 4개와 초음파센서, stm32보드, 블루투스 를 장착하고 연결 7805 로 12v 배터리의 전압을 변환하여 5v 를 각각 모터드라이브, 마이크로프로세서에 인가 하여 작동
- 모서리 부분의 적외선센서 4개로 벽의 거리를 센싱 하여 벽면이 가까워지는 쪽의 반대 바퀴의 rpm 을 늦춤, 초음파 센서는 정면에 벽을 인식하고 가까워지면 모터동작을 멈춤
- 리모트 컨트롤로부터 얻은 0~9의 값에따라 모터의 좌,우 바퀴를 각각 개별적으로 타이머 돌리면서 구동시킴



# 결과 사진 

<figure>
<p style="text-align: center;">	
	<img src="/images/linetracer1.png">
</p>
</figure>

<figure>
<p style="text-align: center;">	
	<img src="/images/linetracer2.png">
</p>
</figure>

# 결과 영상

[가속도 센서로 모터제어](https://youtu.be/CWzntotpnHU)                                                                           
[초음파 센서로 모터제어](https://youtu.be/7dy97rkTpmQ)                                                                                                             
[최종 시연 영상](https://youtu.be/vs4gfxyZsqw)              
