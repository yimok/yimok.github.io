---
layout: post
title: Github 블로그 repository를 clone해서 글쓰기
description: 블로그 repository가 설치되어 있지 않은 PC에서 블로그를 작성하는 방법
modified: 2015-07-05
tags: [blog]
comments: true
image:
  feature: abstract-4.png
  credit: dargadgetz
---

블로그 repository가 설치되어 있지 않은 PC에서 블로그를 작성하는 방법을 알아보자. 
여러가지 방법이 있겠지만, 이번에는 github의 remote repository를 clone해서 글을 작성하고 commit하는 방법을 살펴보기로 한다. 

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## 준비

[이전 글](http://hochulshin.com/how-to-use-jekyll-on-github-2/)을 참조하여 [SourceTree 프로그램](https://www.sourcetreeapp.com/)과 [markdownpad](http://markdownpad.com/download.html)를 설치하고, 블로그를 위한 임의의 빈 폴더를 만든다.  

## clone하기

1. SourceTree를 실행
2. 메뉴에서 **복제/생성** 아이콘을 선택->
3. 저장소 복제 탭에서 소스 경로/URL에 github의 블로그 repository 주소 `https://github.com/자기아이디/자기아이디.github.io.git`를 입력 
4. 소스 경로/URL 입력의 오른쪽 지구본 아이콘을 선택하여 호스팅 서비스, 사용자 명, 비밀번호를 입력하고 선호 프로토콜은 https로 선택 
5. github의 remote repository 목록 중 블로그를 위한 사용자명.github.io를 선택
6. 블로그를 위한 임의의 빈 폴더 경로를 **목적지 경로**에 입력하고 **이 저장소 책갈피에 넣기**를 선택
7. **클론**을 실행    

## 글 작성해서 commit하기

### 작성하기

**_post** 폴더에 다른 md 파일을 markdownpad로 열고 새로 commit할 이름으로 저장한 뒤 작성한다. 

### 테스트

Command Prompt에서 `bundle exec jekyll build  ` 명령을 통해 여러 설정파일을 통해 블로그 컨텐츠를 build한다. 성공적으로 완료되면 서버를 구동하기 위해 `bundle exec jekyll serve`명령을 실행한다. 웹브라우저에서 주소로 **localhost:4000**을 입력하여 작성한 내용을 꼼꼼히 확인한다. 

### commit

SourceTree에서 변경사항을 확인하고 commit을 한다. 
