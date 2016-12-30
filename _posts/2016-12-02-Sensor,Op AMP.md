---
layout: post
title: "센서와 증폭기"
description: "센서와 증폭기" 
modified: 2016-12-03
tags: [blog]
comments: true
image:
  feature: back1.jpg
---

우리가 사용하는 센서와, 전압을 증폭해주는 OP앰프에대해 알아보자.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->



## Sensor

### 센서들의 특징

<figure>
<p style="text-align: center;">	
	<img src="/images/ssensor1.png">
</p>
</figure>


- 센서의 Input은 기타 에너지
- 센서의 Output은 99.9% 가 전기 에너지
- 기타가 소리면 소리센서, 초음파면 초음파 센서



### 적외선 센서

<figure>
<p style="text-align: center;">	
	<img src="/images/ssensor2.PNG">
</p>
</figure>


- 발광부와 수광부가 존재
- 수광부는 일종의 트랜지스터라고 볼 수 있다. 받은 빛의 양에 따라 수광부 내부의 수도꼭지를 조절하여 전압의 양이 변한다. 이 전압값으로 센싱 데이터 측정


### 증폭기

- 만약 0~3.3v 까지 표현이 가능한 적외선 센서가 있다고 하자. 그러나 거리에 따라 빛의 세기가 달라 최대 수용값이 차이가 날 때가 있다.
- 즉 적외선 센서는 최대 데이터를 표현하고 있는데 거리때문에 2v로 밖에 표현이 불가할 때, 전압증폭기를 적용하여 최대 3.3v로 사용하도록 한다.
- 전류증폭 : 트랜지스터
- 전압증폭 : OP앰프 -> 낮은 전압을 높은 전압으로 올리는 소자(에너지를 생성하는 소자이기때문에 전압을 인가해야함) 
 
<figure>
<p style="text-align: center;">	
	<img src="/images/sensor3.png">
</p>
</figure>

- 증폭기는 전압을 분배해주는 것 뿐이다. 무에서 유를 창조하는 것은 불가능. 외부 전압을 인가해줘야함
- 그렇다면 전압을 크게 걸어주면 안되는가? -> OP AMP가 버티지못하고 터져버린다.
- 우리가 원하는 값을 + 이므로 보통 OP AMP를 한개더 장착하여 +값으로 만든다. 가능하면 앞쪽에서 증폭을 많이해준다.

### 수광부센서에 OP Amp 달기

<figure>
<p style="text-align: center;">	
	<img src="/images/sensor4.png">
</p>
</figure>

Reference: Sang Youn Kim - Micro processor , Korea university of technology & education
