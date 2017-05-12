---
layout: post
title: "[Design Pattern]Observer Pattern"
description: "[Design Pattern]Observer Pattern"
modified: 2017-04-11
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

Observer Pattern 에 대한 이해와 실습

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## 옵저버 패턴(Observer Pattern)

### 옵저버 패턴(Observer Pattern)

<figure>
<p style="text-align: center;">	
	<img src="/images/observer1.png">
</p>
</figure>

- 신문사(Subject)는 신문을 발행함
- 고객(Observer 객체들)은 새롭게 신문이 발핼될 때마다 받아보기 위해서 구독을 해야하며, 또는 구독을 중단할 수 있음
- Observer Pattern 은 1대다 관계를 가진다. 즉 하나의 Subject객체의 상태가 변하면 다수의 Observer객체 에게 자동 통보 하는 구조를 가짐

<figure>
<p style="text-align: center;">	
	<img src="/images/observer uml.png">
</p>
</figure>

- 위 UML은 Push 방식으로 구현한 Observer 패턴
- Subject interface를 구현한 WeatherStation이 구독하는 Observer 타입의 객체들을 저장하기위해 ArrayList로 observers 멤버변수를 가짐
- WeatherStation에서 상태변화가 일어나면 구독하는 Observer 들에게 정보(온도, 습도 등..)를 제공함(Push 방식)
- 만약 Pull 방식으로 구현할 경우 Subject 객체를 직접 넘겨서 Observer 상에서 직접 getter 메소드를 이용해 정보를 가져옴
- 단 Pull 방식의 경우 tight-coupling이 됨(Subject 객체 자체를 넘기므로)

### 옵저버 패턴(Observer Pattern) 코드 - Push 방식

```java
import java.util.ArrayList;


public interface Subject {
	void registerObserver(Observer o);
	void removeObserver(Observer o);
	void notifyObservers();
}

public class WeatherStation implements Subject {
	
	//Observer들을 저장
	private ArrayList<Observer> observers = new ArrayList<>();
	private double temperature;
	
	@Override
	public void registerObserver(Observer o) {
		observers.add(o);
	}
	@Override
	public void removeObserver(Observer o) {
		observers.remove(o);
	}
	@Override
	public void notifyObservers() {
		//push 방식
		for(Observer o: observers) o.update(temperature);
		
	}
	public void setMeasurement(double temperature){
		this.temperature = temperature;
		notifyObservers();
	}
}

```

```java
	
public interface Observer {
	//push 방식
	void update(double temperature);
}

public class NewsClient implements Observer {
	@Override
	public void update(double temperature) {
		System.out.printf("현재온도: %.2f\n", temperature);
	}
}


```


```java
public class Test {

	public static void main(String[] args) {
		WeatherStation ws = new WeatherStation();
		Observer o = new NewsClient();
		ws.registerObserver(o);
		ws.setMeasurement(20.3);
		ws.removeObserver(o);
		ws.setMeasurement(30.3);
	}

}
```


### 옵저버 패턴(Observer Pattern) 코드 - Pull 방식


```java
import java.util.ArrayList;

public interface Subject {
	public void addObserver(Observer o);
	public void removeObserver(Observer o);
	public void notifyObserver();
	
}

public class WeatherStation implements Subject {

	private ArrayList<Observer> observers = new ArrayList<>();
	private double temperature;
	
	@Override
	public void addObserver(Observer o) {
		observers.add(o);
	}
	@Override
	public void removeObserver(Observer o) {
		observers.remove(o);
	}

	@Override
	public void notifyObserver() {
		for(Observer o : observers)
		{	
			//pull 방식
			o.update(this);
		}
	}
	//pull 방식의 경우 getter 메소드를 생성해줘야함
	public double getTemperature()
	{
		return temperature;
	}
	
	public void setTemperature(double d)
	{
		temperature = d;
		notifyObserver();
	}

}

```


```java
	
public interface Observer {
	//pull 방식 - subject객체 자체를 넘김
	public void update(Subject s);
}

public class NewsClient implements Observer {

	@Override
	public void update(Subject s) {
		WeatherStation ws = (WeatherStation)s;
		System.out.printf("현재 온도 :" + ws.getTemperature());
	}

}


```


```java
public class Test {

	public static void main(String[] args) {
		WeatherStation ws = new WeatherStation();
		Observer o = new NewsClient();
		ws.registerObserver(o);
		ws.setMeasurement(20.3);
		ws.removeObserver(o);
		ws.setMeasurement(30.3);
	}

}
```




### Java 에서 제공하는 Observer 패턴 

- Subject를 Observable이라는 클래스로 제공!!
- 상속받아 WeatherStation을 구현한다. 
- 왜 interface로 구현하지않고 상속을 받는가? -> 등록, 제거, 알림 3가지 기능을 필수적으로 쓰기때문에 코드작성 안하도록 상속받아 사용
- Setchanged() 메소드를 적절히 사용하면 값이 들어와도 변할때만 보내도록 설정이 가능함

### 옵저버 패턴(Observer Pattern) 코드 - Observable 사용

```java
import java.util.Observable;

public class WeatherStation extends Observable {
	private double temperature;
	public void setMeasurement(double temperature){
		this.temperature = temperature;
		
		setChanged();
		
		//push 방식
		//notifyObservers(temperature); 
			
		//pull 방식 
		notifyObservers(); 
	}
	public double getTemperature() {
		return temperature;
	}
}

```

```java
import java.util.Observable;
import java.util.Observer;

public class NewsClient implements Observer {
	@Override
	//앞 은 pull 용 뒤는 push 용
	//온도,기압,습도 등 여러개의 데이터를 넘겨야할때는 push 방식이 비효율적일수 있음 이 많은 데이터를 object로 넘기면 효율적?
	//다만.. pull 에서 this를 주기 떄문에 tight-coupling 즉 pull 은 가급적 사용x
	//적절하게 사용해야함
	public void update(Observable arg0, Object arg1) {
		
		//push 방식
		//Double temperature = (Double)arg1;
		//System.out.printf("현재온도: %.2f\n", temperature);
		
		
		//pull 방식
		WeatherStation ws = (WeatherStation)arg0;
		System.out.printf("현재온도: %.2f\n", ws.getTemperature());
	}
}

```

```java
import java.util.Observer;

public class Test {

	public static void main(String[] args) {
		WeatherStation ws = new WeatherStation();
		Observer o = new NewsClient();
		ws.addObserver(o);
		ws.setMeasurement(20.3);
		ws.deleteObserver(o);
		ws.setMeasurement(30.3);

	}

}
```


### 옵저버 패턴(Observer Pattern) 코드 - Observable 사용시 상속 문제해결
- Observable을 상속받아 구현하기때문에 다른 클래스를 상속받기가 어려움
- 따라서 멤버로 구현(Has-A)하여 멤버에 위임을 하고 , Protected된 Setchanged만 public()으로 변환해준다.

```java
import java.util.Observable;

public class WeatherStation extends Observable {
	private double temperature;
	public void setMeasurement(double temperature){
		this.temperature = temperature;
		
		setChanged();
		
		//push 방식
		//notifyObservers(temperature); 
			
		//pull 방식 
		notifyObservers(); 
	}
	public double getTemperature() {
		return temperature;
	}
}

```

```java
import java.util.Observable;
import java.util.Observer;

public class NewsClient implements Observer {
	@Override
	//앞 은 pull 용 뒤는 push 용
	//온도,기압,습도 등 여러개의 데이터를 넘겨야할때는 push 방식이 비효율적일수 있음 이 많은 데이터를 object로 넘기면 효율적?
	//다만.. pull 에서 this를 주기 떄문에 tight-coupling 즉 pull 은 가급적 사용x
	//적절하게 사용해야함
	public void update(Observable arg0, Object arg1) {
		
		//push 방식
		//Double temperature = (Double)arg1;
		//System.out.printf("현재온도: %.2f\n", temperature);
		
		
		//pull 방식
		WeatherStation ws = (WeatherStation)arg0;
		System.out.printf("현재온도: %.2f\n", ws.getTemperature());
	}
}

```

```java
import java.util.Observable;
import java.util.Observer;

public interface Subject {
	void registerObserver(Observer o);
	void removeObserver(Observer o);
	void notifyObservers();
}


//WeatherStation이 Class A를 상속받고싶음
class A{
	
}

//setChanged를 public으로 변환시켜 줘야함.
class ImproveObservable extends Observable
{
	public void setChanged()
	{
		super.setChanged();
	}
}


public class WeatherStation extends A implements Subject {
	//Has-A 관계로 observable을 가짐
	private ImproveObservable observable = new ImproveObservable();
	private double temperature;

	public double getTemperature()
	{
		return temperature;
	}
	
	public void setTemperature(double d)
	{
		temperature = d;
		observable.setChanged();
		observable.notifyObservers(d);
	}

	@Override
	public void registerObserver(Observer o) {
		observable.addObserver(o);
	}

	@Override
	public void removeObserver(Observer o) {
		observable.deleteObserver(o);
	}

	@Override
	public void notifyObservers() {
		observable.notifyObservers();
		
	}

}

```

```java
import java.util.Observable;
import java.util.Observer;

public class NewsClient implements Observer {

	@Override
	public void update(Observable o, Object arg) {
		
		System.out.println(arg);
	}

	
}

```

```java

public class Test {

	public static void main(String[] args) {
		WeatherStation ws = new WeatherStation();
		
	   ws.registerObserver(new NewsClient());
		
		ws.setTemperature(25.5);
		ws.setTemperature(26);
		
	}

}

```
Reference: Sang Jin Kim - Object Oriented Development , KOREATECH