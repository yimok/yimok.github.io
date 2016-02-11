---
layout: post
title: "[OS]Computer System Architecture"
description: "[OS]Computer System Architecture" 
modified: 2016-02-12
tags: [blog]
comments: true
image:
  feature: back1.jpg
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


## Computer System Architecture

<figure>
	<img src="/images/post3-1.PNG" alt="">
</figure>

- 컴퓨터의 기본적인 구성 요소 : CPU , 메모리 , I/O디바이스 가 있다.
- 이러한 하드웨어 기본요소들을 연결하는 기법을 System bus 라 한다. 
- I/O 디바이스들은 자기와 버스 간에 Controller 라는 것을 가지고 있다. 이 컨트롤러가 CPU를 대신해 I/O 디바이스를 권장하고 운영 하는 역할을 한다.

### System bus

- 시스템 버스는 CPU와 메모리 , CPU와 I/O 디바이스 , I/O디바이스와 메모리 간의 데이터 전송을 담당하는 부분이다.
- 시스템 버스는 다시 데이터 버스와 어드레스 버스로 나뉘어져있다. 
- 버스로 데이터를 전송하려면 데이터의 소스, 목적지가 지정이 되어야 한다. 이러한 것이 지정되는 것이 어드레스고 이 어드레스는 어드레스 버스라는 것에 의해 전송이 된다.
- 실제 데이터는 데이터 버스에 의해 전송이 된다.
- 기본적인 버스 transaction(처리) 과정은 Read/Write 이다.
- Bus Transaction을 하려면 누군가가 시작하는 과정이 있어야 한다. -> Bus Transaction을 시작할 수 있는 요소를 Bus master 라고 한다.
- Bus master는 Read/write를 할 수 있는데 Read/write를 시작하기 전에 Bus를 우선적으로 장악해야 한다. 왜냐하면 컴퓨터 시스템 안에는 Bus transaction을 시작할 수 있는 Bus master가 여러 개 존재하기 때문이다.
- 여러 Bus master 가 Bus를 장악하려고 할 때 어떤 특정 Bus master에게 Bus를 제공해주는 조정자가 있는데 이를 Bus arbiter 라고 한다.
- Bus arbiter는 Bus master들 에게 request 시그널을 받는다. 이 여러 개의 request signal을 받으면 그중 우선순위가 높은 것 또는 정책에 따라 Bus master를 선정하게 된다.
- 그리고 Bus master에게 Grant signal을 제공해 주어 Bus를 제공해 준다.
-이러한 Bus Transaction을 할 수 있는 Bus master 들은 어떤 것이 있을까? -> 대표적으로 CPU , I/O Controller, DMA(Direct Memory Access) Controller 등이 있다.


### Bus slave

- 대표적인 Bus slave는 메인 메모리가 있으며  I/O 컨트롤러들도 단독적으로 버스 마스터를 할 수 있지만 CPU 아래서 Bus Slave 역할도 할 수 있다.
- 버스 슬레이브라는 장치는 데이터를 담고 있는 장치이다. 그럼 I/O 컨트롤러는 데이터를 담고 있을까? -> 정확히 말하자면 I/O 컨트롤러 안에 있는 버퍼 메모리나 레지스터 들이 버스 슬레이브 역할이라고 볼 수 있다.
- 버스 슬레이브는 데이터를 담고 있어야 하고, 어드레스를 가지고 있어야 한다.

### I/O 컨트롤러의 역할 
- 자기 레지스터 또는 버퍼 안에 데이터가 있으면 이것을 실제 I/O 디바이스로 출력하는 역할을 한다. or 자기 Input 레지스터가 비어있으면 I/O 디바이스에서 데이터를 읽어오는 역할을 한다. 이것이 I/O 컨트롤러의 기능이다.
- I/O 컨트롤러 안에 여러 개의 레지스터들이 존재하기 때문에 이 I/O 레지스터들에 대한 주소가 필요하다. 이런 어드레스를 I/O 어드레스라 한다.


>Interrupt-Driven I/O : CPU가 I/O 동작에 직접적으로 관여하지 않기 때문에 I/O동작이 완료되면 I/O 컨트롤러가 CPU 에게 비동기적으로 완료되었음을 알려주는 방식
>
>Polling I/O : Interrupt-Driven I/O 와는 반대로 CPU가 출력될 데이터를 I/O 컨트롤러에 있는 Output 레지스터에 보내어 I/O 동작이 완료될 때 까지 CPU가 반복해서 I/O 컨트롤러의 레지스터 상태를 확인하는 방식(인터럽트 관여 안함)

### Port-maped I/O

- 인텔 프로세서 에서 사용 하는 기법중 하나이다
- port-maped I/O 는 디바이스 레지스터들을 위해 별도의 주소 공간을 할애 한다. 메모리 어드레스 공간과는 별도의 포트 어드레스 공간을 가지게 된다.
- 메모리 어드레스와 port 어드레스를 구별하는 방식.

### Memory-mapped I/O

- 메인메모리의 주소공간의 일부를 할애해서 거기에 I/O 레지스터들을 매핑 하는 방법
- 포트맵과는 다르게 I/O 오퍼레이션하기 위한 별도의 명령이 필요 없다.

### Character Device Driver(문자 디바이스 드라이버)

- 처리 단위가 Character( 1Byte / 8Bit )임을 의미한다. H/W와 OS간에 발생하는 지연 시간( Delay 등 )이 거의 없거나 없어야 하는 경우에 사용된다. 따라서 입/출력에 Buffer Memory / Cache( 버퍼 메모리 / 캐시 )가 필요가 없다는 점이 중요한 특징이다.
- 가장 대표적인 Character Device Driver는 바로 Keyboard이다. Keyboard는 사용자가 입력을 함과 동시에 바로 OS로 전달되어야 하므로 Character Device Driver를 사용한다.

### Block Device Driver(블록 디바이스 드라이버)

- 입/출력에 Buffer Memory / Cache( 버퍼 메모리 / 캐시 )가 필요한 디바이스 드라이버이다. H/W의 처리 속도가 느려 OS와의 통신에 지연이 많이 생기는 경우나 한 번에 큰 단위로 처리를 해야하는 경우에 Buffer Memory / Cache를 통해 Block Unit( 블록 단위 )로 H/W와 OS간의 통신이 이루어지도록 구성된다.
- 가장 대표적인 Block Device Driver로는 Disk Driver( External Memory Driver )가 있다. Disk는 처리 속도가 느리며, 한 번에 큰 단위의 접근을 필요로 하기 때문에 Block Device Driver를 사용한다.


### DMA Operation
- Interrupt-Driven I/O, Polling I/O 는 캐릭터 I/O Operation 이다.  캐릭터는 1byte, 단위의 작은 단위이다. 하지만 블록 단위로 전송할 필요가 생길 수 있다. 이럴 때 캐릭터 단위로 전송하면 매우 느릴 것이다. 왜냐하면 한 바이트 씩 전송하는 캐릭터 전송을 하면 한 바이트 전송이 끝날 때 마다 인터럽트가 전송될 것이기 때문이다. 그러한 단점을 고안 한 것 이 DMA Operation 이다.
- cpu가 DMA 스스로 처리할 수 있도록 몇 가지 정보를 전달한다.
>1. cpu는 전송되어야할 블록의 메모리 시작 주소를 DMA 컨트롤러에게 전달한다.
>2. 얼마나 많은 데이터를 한 블록에 포함하고 있는지 즉 블록의 사이즈를 DMA 컨트롤러에게 전달한다.
>3. 그리고 Read/Write 커맨드를 보낸다.

- 즉 DMA는 CPU의 개입 없이 I/O 컨트롤러가 메모리에 직접 접근하여 Data를 읽거나 쓸 수 있도록 하는 기능이다.
- Block Data를 옮길 때 CPU 간섭을 최소한으로 줄이기 위해 사용 한다.(하지만 블록 단위 전송이 끝나면 마찬가지로 인터럽트가 전송된다)

### DMA의 2가지 방식

- 사이클 스틸링 : cpu가 버스를 사용하고 있지 않을 때만 DMA 컨트롤러가 버스를 사용하는 방식 이 방식을 사용하면 CPU의 성능에는 영향을 미치지 않지만 DMA 하는데 시간이 많이 걸림

- Block Transfer : CPU와 DMA 컨트롤러가 대등하게 경쟁하여 Bus를 사용하는 방식

### 정리 

- Block device driver -> DMA operation
- Char device driver-> interrupt driven I/O , Polling I/O

## Interrupt Mechanism

- 인터럽트 방법은 OS가 존재하기 위해서 컴퓨터 하드웨어가 제공해야하는 가장 중요한 방법이다. OS를 Interrupt driven(주도의) system 이라 부르기도 한다.

### 소프트웨어 인터럽트(동기적) 

- 소프트웨어 인터럽트는 현재 수행하는 프로그램에 문제가 발생 했을 때 그러한 문제를 해결하기 위해 수행된다.(예외처리) ->Trap 이라 부른다.(동기적)
.


### 하드웨어 인터럽트(비동기적)

- 인터럽트는 CPU 외부에서 CPU가 관심을 가져야할 만큼 중요한 사건이 발생할 경우 그것을 알려주는 하드웨어적 Mechanism이다. -> 인터럽트는 비동기적 이다.
- 인터럽트가 발생하면 CPU의 컨트롤이 인터럽트 서비스 루틴(ISR)이라는 곳에 넘어가게 된다.
- OS 는 이런 소프트웨어 인터럽트와 , 하드웨어 인터럽트를 가지고 있기 때문에 OS를 인터럽트 주도적이다 라고 말한다

<figure>
	<img src="/images/post3-3.PNG" alt="">
</figure>

- 하드웨어 인터럽트는 마이크로프로세서에 인터럽트 시그널을 받아들일 수 있는 특정 핀이 있어야한다.
- 그리고 시그널을 전송하는 특정 인터럽트 Interrupt Source가 있어야한다.
- Interrupt Source가 될 수 있는 것으로는 I/O Controller, DMA Contorller 등이 있다.(CPU에게 인터럽트를 날려야하는 Unit 들)

### 하드웨어 인터럽트 처리 과정

1. 현재 Instruction(명령)을 마저 완료하고. 마이크로 프로세서의 프로그램 카운터(PC:현재 수행중인 주소, 돌아올 주소) 값을 안전한 곳에 저장.
2. 현재 수행중인 프로그램을 중단.
3. 여러 인터럽트 소스중 Interrupt Request Number(IRQ 번호)를 통해 받아야할 인터럽트 소스를 확인 
4. 컴퓨터시스템의 어떤 특정 메모리에는 지금 처리해야할 인터럽트 핸들러들의 주소가 저장되어 있는데 이것이 저장된 것이 Interrupt Vector Table이다.
인터럽트 리퀘스트 넘버가 Interrupt Vector Table의 인덱스로 작용해서 필요한 인터럽트를 검색해서 Interrupt Service Routine(ISR)의 주소를 확인하고 수행

### Programable Interrupt Controller
<figure>
	<img src="/images/post3-2.PNG" alt="">
</figure>

- 만약 인터럽스 소스의 수에따라 프로세서에 핀을 만들면 프로세서가 확장성을 감당하기 어려울것이다 이러한 문제점을 개선하기 위해 PIC를 개발하였다.
- PIC를 소스와 CPU 사이에 두어 CPU인터럽트 한라인에 	여러개의 인터럽트를 처리 할 수 있도록 함.

>- 왜 PIC 는 Programmable 이라는 단어를 붙였을까?
>- Programmable 하다는 것은 소프트웨어적으로 동작에 영향을 줄 수 있다는 뜻이다. 동기화나 스케줄링의 특징 때문에 특정인터럽트를 사용 못하도록 disable 시켜야 하는 경우가 필요하다. 
>- 이러한 작업을 수행하기 위해 PIC 안에 각 인터럽트 소스 라인에는 한 bit 짜리 flag를 가지고 있는데 이 flag를 0으로 하면 그 인터럽트 라인은 disable 이 된다. 그리고 1로 켜면 다시enable 된다. 이 flag 비트를 끄고 켜는 것을 소프트웨어적으로 처리할 수 있기 때문에 Programmable 하다고 말한다.
>- 즉 다시 말하면 인터럽트 소스가 16개 있다면 PIC 안에는 16비트짜리 flag 레지스터가 있고  이 레지스터들은 전부 I/O 어드레스 범위 안에 매핑이 되어있고 다 포트 어드레스를 부여 받고 있다. 이를 소프트웨어적으로 끄거나 켤 수 있다.
이러한 작업을 전문적 용어로 Interrupt Mask 라고 한다.
 
 
## Hardware Protection Mechanism

### Privileged instruction

- Operation System만 수행할 수 있는 Instruction(명령)
ex)MMU의 레지스터들 (베이스 레지스터, 바운드 레지스터)은 OS만 세팅할 수 있다.

### Dual Mode Operation

- 사람은 뇌 속의 신경에 따라 상쾌한 기분, 우울한 기분을 결정하는데
컴퓨터는 모드를 어떻게 선택할까? 프로세서 안에 존재하는 레지스터가 그 모드를 결정한다.
- 마이크로프로세서의 특정 상태를 나타내는 레지스터가 있는데 이를 Processor status register 라고 한다. 또는 control status register 라고도 한다. 이 마이크로프로세서 레지스터는 최근에 마이크로프로세서가 수행했던 여러 가지 일들을 기억하고 있다. 예를 들면 방금 전 명령의 수행 결과 0 이었는데 –1이었는지 positive 였는지 기억한다. 또는 그전 명령이 오버플로가 발생했는지 기억한다. 왜냐하면 다음 명령에 영향을 미치기 때문이다.
- 여러 가지 상황 정보를 flag 형태로 기억하는데 그중 한 비트가 있고 그중 하나를 모드 비트라 한다. 모드비트가 0이면 OS을 수행하는 모드고 , 1로 되어있으면 User program을 수행하는 모드다.  
- 0이 된 모드를 Kernel Mode 또는 Privileged Mode , Monitor Mode 라고 한다.

> Kernel Mode (Privileged Mode or Monitor Mode) : 
> 커널이 Privileged Instruction 들을 수행 시킬 수 있는 모드
> 
>
> User Mode :
> Privileged Instruction 들을 수행 시킬 수 없는 모드
> 
> 
> ex)인스트럭션이 Privileged Instruction 인데 모드가 1로 되어있으면 누군가가 Protection을 침범 하려한다. -> 소프트웨어 인터럽트를 발생(Trap)
> 
> 
> 컴퓨터시스템은 기본적으로 유저 프로그램(버그가 많으므로)을 통제된 환경에서만 수행 시킨다.
> 
> 

### Operating System이 Kernel Mode에서 수행될 때 부여받는 주요권한

- Privileged Instruction을 수행시킬 수 있는 권한
- 모든 Memory 영역에 접근할 수 있는 권한

### 어떻게 모드 변환을 할 수 있을까?

<figure>
	<img src="/images/post3-4.PNG" alt="">
</figure>

- 모드 체인지는 kernel mode 안에서 수행하는 OS이 권장하도록 만들면 된다.(OS는 신뢰가 높기 때문에)
- 그런데 위 단계를 지키면서 유저 모드에서 커널모드로 변경하려면 이 시스템이 커널 모드에 있어야 한다는 모순된 상황이 있다(나는 유저모드에 있는데..)
- 예를 들어 I/O 명령을 수행해야한다(Privileged Instruction) 커널 모드가 필요하다. 이럴 경우 하드웨어 적인 인터럽트 메커니즘이 필요 한다. 
- 인터럽트가 필요하면 하드웨어적으로 모드를 0으로 변경해준다. -> 모드 체인지는 하드웨어적인 매커니즘으로 일어나고 이것이 인터럽트이다. -> 즉 인터럽트가 발생하면 무조건 커널 모드로 들어가고 커널모드로 바뀌는 순간 그 모드 체인지를 관할 할 수 있는 인터럽트 서비스 루틴이 시스템을 장악한다.
- 위의 방법들로 I/O , Memory, CPU를 Protection 한다. 즉 쉽게 말해서 Memory를 Protection 한다는 것은 MMU 레지스터들을 통제한다는 것이다. 메모리가 다른 작업에 의해 Call 되지 않게 하는 것이다.
- 왜 I/O나 Memory , CPU를 Protection 해야 하는가? -> 이러한 메모리나 I/O 들을 자원이라고 말하는데 컴퓨터시스템에서 자원을 독점한다면 큰문제가 된다.

>어떻게 하면 I/O를 Protection 할 수 있을까? → I/O 레지스터들 (포트 레지스터들을) privileged instruction 으로 만들어 보호한다. → I/O 에 관련된 모든 함수들은 커널로 들어가야 한다.
> 
>
>CPU Protection? CPU도 I/O나 Memory처럼 자원이다. 어떤 프로그램이 수행되려면 CPU가 반드시 필요한데 어떤 한 작업이 CPU를 monopolize(독점)하는 현상이 발생될 수 있다. 이러한 문제를 해결하기 위해 그 작업에게 일정 시간만을 허용하도록 세팅한다.(Timer Interrupt)
	

