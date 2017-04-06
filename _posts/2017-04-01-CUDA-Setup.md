---
layout: post
title: "[CUDA]CUDA 설치 및 적용하기 / OpenCV 설치 및 적용하기"
description: "[CUDA]CUDA 설치 및 적용하기"
modified: 2017-04-01
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

CUDA 를 사용하여 병렬 프로그래밍을 하기위한 CUDA 설치 및 적용하기 

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## CUDA(Compute Unified Device Architecture)

### CUDA 설치 및 적용하기

- PC에 NVIDIA 그래픽카드가 장착되어야 CUDA를 사용할 수 있으며 그래픽카드 사양에따라 CUDA 아키텍처가 다르고, 그래픽 카드가 고사양 일수록 당연히 CUDA의 연산능력도 향상 됩니다.
- 본인은 GEFORCE 840M 그래픽 카드를 사용하며 여기에 CUDA 맥스웰 아키텍처가 적용되어 있습니다.
- Visual Studio 2012 사용
- [CUDA 8.0 설치파일 다운로드](https://developer.nvidia.com/cuda-downloads)

1. 위 링크에서 자신의 운영체제에 맞는 CUDA 8.0 을 다운로드받아 설치를 진행합니다. -> nvidia experience는 설치 안하셔도 됩니다.
2. Visual Studio를 실행하고 -> 파일 -> 새로만들기 -> 프로젝트

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup.png">
</p>
</figure>

3. 위 그림과 같이 NVIDIA 항목에 CUDA 8.0 Runtime 을 눌러 프로젝트를 생성해줍니다.

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup2.png">
</p>
</figure>
4. 프로젝트와 함께 kernel.cu라는 이름의 파일이 생성되고 kernel.cu 안의 내용을 지우고 자신이 원하는 CUDA 프로그래밍 코드를 작성하고 평소에 Visual Studio 사용했던 그대로 컴파일 및 빌드를 진행하면 됩니다.

## OpenCV

### OpenCV 설치 및 적용하기

- [CUDA 8.0 설치파일 다운로드](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.13/opencv-2.4.13.exe/download
)

1. 위 링크로 들어가면 OpenCV 다운로드가 진행되며, 다운로드 완료후 설치를 진행합니다 이때 설치를 C:\opencv 에 해줍시다.

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup9.png">
</p>
</figure>

2. 명령 프롬프트를 관리자 권한으로 실행 후 setx -m OPENCV_DIR C:\opencv\build\x86\vc11 입력

3. 내PC -> 속성 -> 고급시스템 설정 -> 고급 탭의 환경변수 클릭

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup3.png">
</p>
</figure>

4. 위 그림처럼 상단의 PATH를 열고 

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup4.png">
</p>
</figure>

5. %OPENCV_DIR%\bin 추가

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup5.png">
</p>
</figure>

6. Visual Studio 실행 후 프로젝트를 생성하고 위 그림처럼 왼쪽 창에서 속성 관리자 탭 -> Debug/Win32 -> Microsoft.Cpp.Win32.user 오른쪽 클릭 속성 클릭

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup6.png">
</p>
</figure>

7. C/C++ -> 일반 -> 추가 포함 디렉토리 편집을 눌러 -> 그림과 같이 3번 을 추가


<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup8.png">
</p>
</figure>

8. 링커 -> 일반 -> 추가 라이브러리 디렉터리에 위 그림처럼 $(OPENCV_DIR)\lib 추가

<figure>
<p style="text-align: center;">	
	<img src="/images/cudasetup7.png">
</p>
</figure>

9. 이어서 위 그림처럼 링커 -> 입력 -> 추가 종속성 편집을 눌러 아래 파일을 다운로드 받고 내용을 추가
10. [OpenCV_lib.txt](https://github.com/yimok/yimok.github.io/tree/master/data/OpenCV)
11. OpenCV 적용완료