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


# IoT Termproject
--------
- 동물에 장착할 End Device로 부터 온도, 3축 데이터를 수집하여 Gateway에서 정제후 Server로 데이터 전송하여 소의 수태,질병을 판별하는 작은 시스템
- github : [https://github.com/yimok/Smart-IoT](https://github.com/yimok/Smart-IoT)

# 개발 환경
- Spring Framework - Web App
- Node.js/Python - Gateway(Mobius YT/Thyme 적용)
- MySql DB

# 사용 디바이스 및 센서
- End Device : Arduino Uno , 적외선 센서 , 3축 가속도 센서, ZigBee
- Gateway : Raspberry Pi 2, ZigBee 
- Server : PC(windows 10)

# 구현 기능
- End 디바이스로 부터 센싱 데이터를 수집하여 ZigBee 통신으로 일정 시간마다 Gateway에 전송
- Gateway는 End 디바이스로부터 수집한 데이터를 무작정 서버로 전송하는것이 아니라 , 변화폭이 클경우 유효한 데이터만 전송한다.
- 서버는 수집한 데이터를 MySql DB에 저장하고 이 데이터를 그래프로 표현하는 Web App 구성 하였다.

# 시스템 구성도

<figure>
<p style="text-align: center;">	
	<img src="/images/iotstructure2.png">
</p>
</figure>

# Mobius 적용 구성도 

<figure>
<p style="text-align: center;">	
	<img src="/images/iotstructure3.png">
</p>
</figure>

# 소프트웨어 구성도

<figure>
<p style="text-align: center;">	
	<img src="/images/iotstructure.png">
</p>
</figure>


# 결과 사진 

<figure>
<p style="text-align: center;">	
	<img src="/images/iot1.png">
</p>
</figure>

<figure>
<p style="text-align: center;">	
	<img src="/images/graph1.png">
</p>
</figure>

<figure>
<p style="text-align: center;">	
	<img src="/images/graph2.png">
</p>
</figure>