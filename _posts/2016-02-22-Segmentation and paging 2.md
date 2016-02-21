---
layout: post
title: "[OS]세그멘테이션과 페이징(2)"
description: "[OS]세그멘테이션과 페이징(2)" 
modified: 2016-02-22
tags: [blog]
comments: true
image:
  feature: back1.jpg
---
Paged Segmentation 에 대해 알아봅시다. 

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## Paged Segmentation

- 페이징만 한다는 것은 프로세스에 한개의 세그먼트만 제공하는것이다. 즉 페이징은 Fragmentation 은 해결했지만 프로세스에 다중 세그먼트를 할당 할 수 있는 방법은 달성하지 못하였기 때문에 페이지와 세그먼트를 같이 사용 한다. 