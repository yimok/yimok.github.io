---
layout: post
title: "Transaction 이란?"
description: "Transaction 이란?"
modified: 2017-01-03
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

데이터베이스의 기본적인 개념 Transaction에 대해 알아보자.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->


## Transaction 이란?

- Transaction 이란 내가 설정한 작업의 최소단위 이다.
- 아래의 3개의 단계를 하나로 묶어서 트랜잭션으로 정의할 수 있다. 또는 2개만 묶어서, 1개만 묶어서도 트랜잭션으로 정의할 수 있다.
- 즉 Transaction은 단위작업 여러개를 묶어서 논리적인 하나의 작업단위로 만드는 것을 말한다.

1. 홍길동의 계좌에 2000원이 있는지를 먼저 확인(select)
2. 홍길동의 계좌에서 2000원을 차감
3. 이순신의 계좌에 2000원을 더한다.

### Transaction을 왜 사용하는가?

- DBMS(MySql, Oracle, ..)로 부터 ACID를 제공받기 위해서 사용한다.
- Atomicity(원자성) : All or nothing(모든 처리가 완료되거나 혹은 하나도 안되거나) -> ex)위에 써있던 이체작업이 2단계까지 수행하고 전기가나가면 아예 실패로 간주하고 모두 안된걸로 처리하거나, 3단계가 완벽하게 모두 수행되거나 둘중 하나여야 한다.
- Consistency(일치성) : 내 구좌에서 1000원이 빠지면 다른 사람 구좌에서도 1000원이 올라가야 한다.
- Isolation(독립성) : 데이터가 처리될 때 해당 데이터를 보호하는 특성 -> 한 작업이 끝날동안 다른작업이 수행되지 않도록 하는 것
- Durability(영구보존성) : 처리가 끝난 데이터를 안전하게 데이터베이스에 저장하는것을 보장
- 즉 ACID를 제공받기위해 트랜잭션을 사용하고 이 트랜잭션이라는 기능을 DBMS가 제공해준다.

### Java에서 데이터베이스를 사용할 때(JDBC) 어떻게 Transaction을 설정하는가?

- account table을 이용해서 transaction 설정에 대해 알아보자

<figure>
<p style="text-align: center;">	
	<img src="/images/book6.png">
</p>
</figure>


- Conncection 에 Transaction을 설정한다. 즉 Connection에 의한 모든작업이 Transaction에 의해 수행된다.
- 정상 수행되면 commit , 비정상 수행되면 rollback 을 수행하여 ACID를 제공받는다.

```java
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class Main {

	public static void main(String[] args) {
			
		//Transaction을 적용하지 않은 예제
		//총 6단계를 거쳐서 데이터베이스 처리를 합니다.

		try{
			//1. Driver Loading( MySQL에 접속하기 위한 class를 로딩)
			Class.forName("com.mysql.jdbc.Driver");
			System.out.println("Driver loading Success");			
			//2. 실제 데이터베이스에 접속
			String url = "jdbc:mysql://localhost:3306/library";
			String id = "root";
			String pw = "cps431";
			Connection con = DriverManager.getConnection(url, id, pw);
			
			
			//해당 connection에 transaction을 설정
			con.setAutoCommit(false); //★여기서부터 transaction 시작 이라고 알림.
			
			
			
			//3. 실행할 SQL을 작성(PreparedStatement 생성)
			String sql = "update account set balance = balance + 1000 where username='홍길동'";
			PreparedStatement pstmt = con.prepareStatement(sql);
			
			//4. PreparedStatement를 실행
			//update 이므로 executeUpdate();
			//★반환된 정수값은 SQL문에 의해서 영향을 받은 record의 수
			//만약 select면 result set이 리턴됨.
			int result1 = pstmt.executeUpdate();
			//Transaction이 설정되어 있기 때문에 바로 데이터베이스에 적용되지 않는다.
			
	
			
			sql = "update account set balance = balance - 1000";
			pstmt = con.prepareStatement(sql);
			int result2 = pstmt.executeUpdate();
			
			//5. 결과처리
			if(result1==1 && result2 ==1)
			{
				System.out.println("정상처리 되었습니다.!");
				//Transaction이 정상 수행되면 commit
				//commit이 되어야 데이터베이스에 처리결과를 넣는다.
				con.commit();
			}
			else
			{
				System.out.println("이상이 있습니다.");
				//Transaction이 제대로 수행이 안되면 rollback
				con.rollback();
			}
			
			
			
			
			//6.사용한 리소스 해제
			pstmt.close();
			con.close();
			
			
		}catch(Exception e){
			System.out.println(e);
		}
		
		
	}

}



```
