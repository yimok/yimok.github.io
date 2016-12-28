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


# Web Service Computing Term-Project
--------
- REST, AWS를 활용한 공원 정보 제공
- github : [https://github.com/yimok/wsc](https://github.com/yimok/wsc)

# 개발 환경
- Spring Framework
- Apache Tomcat 8
- Java JDK 8
- Intellij IDEA


# 사용한 Open API


 - [서울시 공원 API](http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-394)                                                                         
 - [서울시 공중화장실 API](http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-162)                                                                                                     
 - [서울시 자전거 대여소 정보 API](http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-12969)         
 - [서울시 자전거 대여소 정보 API](http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-12969)      
 - [다음 로컬 주소 -> 좌표변환 API](https://developers.daum.net/services/apis/local/geo/addr2coord)       
 - [다음 키워드로 장소검색 API](https://developers.daum.net/services/apis/local/v1/search/keyword.format)        



# 정보 가공
1. 공원 주변 공공화장실, 자전거 대여소 파악
2. 지하철역의 경도,위도 정보를 수집하여 검색한 공원과의 거리를 계산하여 가장 가까운역을 파악


# 사용 명세서

## 1.Park Info

- 요청주소(로컬) : [http://localhost:8080/seoul/park/info](http://localhost:8080/seoul/park/info)
- 요청주소(아마존) : [http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/info?](http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/info?)

<figure>
<p style="text-align: center;">	
	<img src="/images/sheet1.png">
</p>
</figure>

## 2.Nearest Station

- 요청주소(로컬) : [http://localhost:8080/seoul/park/neareststation](http://localhost:8080/seoul/park/neareststation)
- 요청주소(아마존) : [http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/neareststation?](http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/neareststation?)


<figure>
<p style="text-align: center;">	
	<img src="/images/sheet2.png">
</p>
</figure>


## 3.주소에 따른 공원 검색

- 요청주소(로컬) : [http://localhost:8080/seoul/park/nearest?address=주소&parkc=5](http://localhost:8080/seoul/park/nearest?address=노원구&parkc=5)
- 요청주소(아마존) : [http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/nearest?address=주소&parkc=5](http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/nearest?address=노원구&parkc=5)


<figure>
<p style="text-align: center;">	
	<img src="/images/sheet4.png">
</p>
</figure>


<figure>
<p style="text-align: center;">	
	<img src="/images/sheet5.png">
</p>
</figure>


# 결과 사진 

<figure>
<p style="text-align: center;">	
	<img src="/images/web1.PNG">
</p>
</figure>

<figure>
<p style="text-align: center;">	
	<img src="/images/web2.PNG">
</p>
</figure>
