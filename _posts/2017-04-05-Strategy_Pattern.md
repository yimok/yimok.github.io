---
layout: post
title: "[Design Pattern]Strategy Pattern
description: "[Design Pattern]Strategy Pattern"
modified: 2017-04-05
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

Strategy Pattern 에 대한 이해와 실습

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## 전략 패턴(Strategy Pattern)

### 전략 패턴(Strategy Pattern)

<figure>
<p style="text-align: center;">	
	<img src="/images/strategy1.png">
</p>
</figure>

- 위 처럼 오리관련 프로그램을 만들었다고 가정하자, 새로운 오리가 추가될때마다 Duck 클래스를 상속받아 나는 행위와 소리지르는 행위를 재정의하여 구성함
- 위와 같은 구조로 설계할경우 몇가지 문제점이 발생한다. 
1. 코드들을 중복해서 구현하게 된다.
2. 실행시간에 어떤 행동을 바꾸는게 어렵다.
3. 모든 오리특성을 사전에 알기가 어렵다.
4. 내가 의도하지 않았는데 재정의를 까먹으면 문제가 발생할 수 있다.


### Design Principle 1
- Application에서 행동들이 여러가지 형태로 변하는 부분과 그렇지 않은 부분을 구분해야 한다.
- 즉 Vary한 부분(날기, 소리 지르기)을 유연하게 설계하도록 구현 해야한다.
- 계속 바뀌어야 하는 부분은 Duck에 직접 모델링 하지말고 다른 클래스로 분리하여 만들고 Has-a 관계로 묶어준다.
 
### Design Principle 2
- 구체적인 클래스가지고 프로그램 만들지말고, 추상클래스나 인터페이스를 이용해라

### Design Principle 3
- is-a 관계를 이용하는 것 보다 has-a 관계를 이용하는것이 보다 더 유연한 해결책을 가져다 준다.
- 특히 실행시간에 행위를 변경할 수 있다.
- 위 원칙을 적용한 전랴패턴은 객체의 상태에 따라 행위를 동적으로 바꿀 수 있도록 해준다. 


### 전략 패턴(Strategy Pattern) 코드

```java
//자주 변하는 행위를 inerface로 묶음
public interface Flyable {
	void fly();
}


public class FlyNoWay implements Flyable {
	@Override
	public void fly() {
	}
}


public class FlyWithWings implements Flyable {
	@Override
	public void fly() {
		System.out.println("날개로 날고 있어");
	}
}

```



```java
	
public abstract class Duck {

	//has-a 관계로 날개행위를 멤버변수로 저장
	//동적으로 행위 선택이 가능함
	private Flyable flyStrategy;
	public void setFlyStrategy(Flyable flyStrategy){
		this.flyStrategy = flyStrategy;
	}
	public void quack(){
		System.out.println("꽥꽥");
	}
	public void swim(){
		System.out.println("수영 중");
	}
	public void fly(){
		flyStrategy.fly();
	}
	public abstract void display();
}



public class RubberDuck extends Duck {
	public RubberDuck(){
		setFlyStrategy(new FlyNoWay());
	}
	@Override
	public void quack(){
		System.out.println("삑삑");
	}
	@Override
	public void display() {
		System.out.println("난 고무오리");
	}

}

public class MallardDuck extends Duck {
	public MallardDuck(){
		setFlyStrategy(new FlyWithWings());
	}
	@Override
	public void display() {
		System.out.println("난 청동오리");
	}

}


```


```java
	
public class Test {

	public static void main(String[] args) {
		Duck ducks1 = new MallardDuck();
		Duck ducks2 = new RubberDuck();
		ducks1.display();
		ducks1.fly();
		ducks1.quack();
		ducks2.display();
		ducks2.fly();
		ducks2.quack();
		
	}

}
```





Reference: Sang Jin Kim - Object Oriented Development , KOREATECH