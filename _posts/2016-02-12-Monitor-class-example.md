---
layout: post
title: "C#의 Monitor class 를 이용한 예제"
description: "C#의 Monitor class 를 이용한 예제" 
modified: 2016-02-13
tags: [blog]
comments: true
image:
  feature: back1.jpg
---
스레드의 동기화 이해를 위해 C#의 Monitor class 를 이용하여 코드를 작성해 보겠다.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Monitor class

- .NET Framwork 에서 제공하는 Monitor 클래스를 활용하여 스레드의 동기화에대해 좀 더 자세히 이해해 보겠다.
- Monitor class 의 네임스페이스는 System.Threading 에 있다
- 자세한 사용법은 [MSDN 참고](https://technet.microsoft.com/ko-kr/library/system.threading.monitor(v=vs.110))
- 기본적인 함수로 Monitor.Enter() , Monitor.Exit() 이다.
- Monitor.Enter()는 지정된 스레드를 잠궈서 Critical Section 에 다른 쓰레드가 침입하지 못하도록 한다 
- Monitor.Exit()는 지정된 스레드를 해제하여 다음 쓰레드가 Critical Section 을 수행할 수 있게 한다.

### Monitor class 예제  1

```cs

using System;
using System.IO;
using System.Threading;

namespace monitorclass
{
class Program
    {

        static object locker = new object();
        static void ThreadMain()
        {
            for (int i = 0; i < 50000; i++)
                for (int j = 0; j < 50000; j++) ;        

             WriteToFile();                              // 공유 리소스에 접근 - critical section
        }
        static void WriteToFile()
        {
            String ThreadName = Thread.CurrentThread.Name;
            Console.WriteLine("{0} using Resource", ThreadName);
            Monitor.Enter(locker);                       // 모니터에 들어감
            try
            {
                using (StreamWriter sw = new StreamWriter(@"C:\Users\hyokyun\Documents/hoho.txt", true))
               {   
                   sw.WriteLine(ThreadName);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                Monitor.Exit(locker);                  // 모니터에서 나옴
                Console.WriteLine("{0} releasing Resource", ThreadName);
            }
        }
        static void Main(string[] args)
        {
            for (int i = 0; i < 3; i++)
            {
                Thread thread = new Thread(new ThreadStart(ThreadMain));
                thread.Name = String.Concat("Thread - ", i);
                thread.Start();
                
            }
            Console.Read();
        }
    }
}
```

<figure>
	<img src="/images/post7-2.PNG" alt="">
</figure>

- 생성된 3개의 쓰레드가 하나의 파일(공유 자원)에 접근하기 위한 소스코드 이다.
- 한 쓰레드가 작업을 진행하기 전에 Monitor.Enter() 호출하여 Monitor 에들어가 작업을 하는동안에는 다른 쓰레드가 접근할 수 없다.
- Monitor.Exit() 를 호출하여 Monitor 에서 나오면 공유자원을 해제하고 다음 쓰레드에게 자원을 넘긴다.
 

### montior class 예제 2


```cs

using System;
using System.Threading;

namespace waitndpulesmethod
{
    class TickTock
    {
        public void tick(bool running)
        {
            lock (this)
            {
                if (!running)
                {  //  틱이 다 끝났다면 정지함    
                    Monitor.Pulse(this);  //  나머지 스레드에게 알리고   
                    return;               //  리턴으로 빠져 나온다.
                }
                Console.Write("Tick  ");
                Monitor.Pulse(this);  // tock 스레드에게 다음에 너가 수행하라고 알린다.  
                Monitor.Wait(this);  //  tick 자기는 wait상태로 간다.
            }
        }
        public void tock(bool running)
        {
            lock (this)
            {
                if (!running)
                {  //  톡이 다 끝났다면 정지함    
                    Monitor.Pulse(this);  //  나머지 스레드에게 알리고
                    return;               //  리턴으로 빠져 나온다.
                }
                Console.WriteLine("Tock");
                Monitor.Pulse(this);  //  tick 스레드에게 다음에 너가 수행하라고 알린다.    
                Monitor.Wait(this);  //   tock 자기는 wait 상태로 간다.
            }
        }
    }
    class MyThread
    {
        public Thread thrd;
        TickTock ttOb;
        //  Construct  a  new  thread.    
        public MyThread(string name, TickTock tt)
        {
            thrd = new Thread(this.run);
            ttOb = tt;
            thrd.Name = name;
            thrd.Start();
        }
        //  Begin  execution  of  new  thread.    
        void run()
        {
            if (thrd.Name == "Tick")
            {
                for (int i = 0; i < 5; i++) ttOb.tick(true);
                ttOb.tick(false);
            }
            else
            {
                for (int i = 0; i < 5; i++) ttOb.tock(true);
                ttOb.tock(false);
            }
        }
    }
    class TickingClock
    {
        public static void Main()
        {
            TickTock tt = new TickTock();
            MyThread mt1 = new MyThread("Tick", tt);
            MyThread mt2 = new MyThread("Tock", tt);

            mt1.thrd.Join();
            mt2.thrd.Join();
            Console.WriteLine("Clock  Stopped");
            Console.Read();
        }
    }
}
```

<figure>
	<img src="/images/post7-1.PNG" alt="">
</figure>

- Monitor.Pulse() 와 Monitor.Wait() 를 사용한 예제이다
- Monitor.Pulse()는 대기 중인 큐에 포함된 스레드에 잠겨 있는 개체의 상태 변경을 알린다.
- Monitor.Wait()는 개체의 잠금을 해제한 다음 잠금을 다시 가져올 때까지 현재 스레드를 차단한다.