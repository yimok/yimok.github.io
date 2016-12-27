
---
layout: post
title: "Web Service Computing"
description: "Web Service Computing" 
modified: 2016-12-253
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



#Web Service Computing Term-Project
- REST, AWS를 활용한 공원 정보 제공
- hi

#개발 환경
- Spring Framework
- Apache Tomcat 8
- Java JDK 8
- Intellij IDEA


#사용한 Open API

|             사용 API       | 주소               |
| ---------------------- | ------------------------ |
| 서울시 공원 API               |http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-394     |                                                                          
| 서울시 공중화장실 API                |http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-162 |                                                                                                     
| 서울시 자전거 대여소 정보 API               |http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-12969 |         
| 서울시 자전거 대여소 정보 API               |http://data.seoul.go.kr/openinf/openapiview.jsp?infId=OA-12969  |       
| 다음 로컬 주소 -> 좌표변환 API               |https://developers.daum.net/services/apis/local/geo/addr2coord |         
| 다음 키워드로 장소검색 API               |https://developers.daum.net/services/apis/local/v1/search/keyword.format |         



#정보 가공
1. 공원 주변 공공화장실, 자전거 대여소 파악
2. 지하철역의 경도,위도 정보를 수집하여 검색한 공원과의 거리를 계산하여 가장 가까운역을 파악


#사용 명세서

##Park Info

- 요청 주소(로컬)  : http://localhost:8080/seoul/park/info
- 요철 주소(아마존) : http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/info?

|             출력변수      | 타입           |       설명               |
| ---------------------- | ------------------------ | ------------------------ |
| xWGS84              |           Double        |      공원의 x좌표                    |                                                                     
| yWGS84           |             Double      |         공원의 y좌표            |                                                                                                      
| pname        |    String        |              공원의 이름        |        
| rcount           |    Int            |    공원 내의 자전거 대여소 수                 |    
| Bcount         |         Int      |      공원 내의 공공 화장실 수              |       


##Nearest Station

- 요청 주소(로컬)  : http://localhost:8080/seoul/park/neareststation
- 요철 주소(아마존) : http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/neareststation?


|             출력변수      | 타입           |       설명               |
| ---------------------- | ------------------------ | ------------------------ |
| station              |        HashMap<String, Double>       |  공원 인근의 지하철 역 3곳의 이름과 거리     |                                                                     
| pname         |             Double      |         공원의 이름          |                                                                                                      


##주소에 따른 공원 검색

- 요청 주소(로컬)  : http://localhost:8080/seoul/park/nearest?address=주소&parkc=5
- 요철 주소(아마존) : http://ec2-52-199-192-231.ap-northeast-1.compute.amazonaws.com/seoul/park/nearest?address=주소&parkc=5


|             요청변수      | 타입           |       설명               |  값의 범위            |
| ---------------------- | ------------------------ | ------------------------ |------------------------ |
| address             |        string       |  검색할 주소     |        |                                                                 
| parkc         |             string      |         출력할 공원 수          |   최소1, 최대 97   |                                                                                                       


|             출력변수      | 타입           |       설명               | 
| ---------------------- | ------------------------ | ------------------------ | 
| curx          |        Double      |  입력한 주소의 x 좌표     |                                                                       
| cury         |         Double      |         입력한 주소의 y좌표          |                                                                                                        
| curlocation         |         String      |         주소         | 
| park       |         HashMap<String,Double>      |         주소와 가장 가까운 공원 3곳의 이름과 거리        | 


#결과 사진 


![image 1](http://postfiles8.naver.net/MjAxNjEyMjdfMTY1/MDAxNDgyODE4OTc2NTcz.itJCLPVIPS-A3T_1hsXcbYBpnhk8xVw8QibB3ZJLMp4g.U7P4j-trZmHnyc-PHwqw6VRcFvpniAShM8ZBUEXwvLgg.PNG.dlagyrbs/web1.PNG?type=w2) 


![image 2](http://postfiles4.naver.net/MjAxNjEyMjdfOTQg/MDAxNDgyODE4OTc2OTc5.i0NxaAfVXwdz91rZEwkwvewwyoAnk-zqXaPQ3umT1i4g.78M7iK4WNlwuI1dVaZR2pgP0iDbs5He2h2S0S3KgERsg.PNG.dlagyrbs/web2.PNG?type=w2) 

