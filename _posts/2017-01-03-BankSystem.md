---
layout: post
title: "MVC Pattern으로 BankSystem 만들기"
description: "MVC Pattern으로 BankSystem 만들기"
modified: 2017-01-03
tags: [blog]
comments: true
image:
  feature: back6.jpg
---

MVC Pattern으로 BankSystem을 만들어 보자.

<section id="table-of-contents" class="toc">
  <header>
    <h3>Overview</h3>
  </header>
<div id="drawer" markdown="1">
*  Auto generated table of contents
{:toc}
</div>
</section><!-- /#table-of-contents -->

## MVC Pattern - BankSystem

### DB 구성

<figure>
<p style="text-align: center;">	
	<img src="/images/book6.png">
</p>
</figure>

### 소스 코드


```java
//Main

import Controller.BankController;

public class Main {

	public static void main(String[] args) {
		
		new BankController();
	}

}



```



```java
//Controller

package Controller;

import java.util.ArrayList;
import java.util.Scanner;

import DTO.BankDTO;
import Service.BankService;



public class BankController {

	//반복 사용되는 자원들은 필드로 잡아서 사용하는게 효율적이다.
	Scanner s;

	public BankController()
	{
		ArrayList<BankDTO> list = new ArrayList<BankDTO>();
		String menu = null;
		s = new Scanner(System.in);
		
		do{
			System.out.println("--- 메뉴입니다. ---");
			System.out.println("1. 입금");
			System.out.println("2. 출금");
			System.out.println("3. 이체");
			System.out.println("4. 종료");
			System.out.print("메뉴를 입력하세요 => ");
			menu = s.nextLine();
			
			if(menu.equals("1"))
			{
				System.out.print("입금할 사람의 이름: ");
				String name = s.nextLine();
				System.out.print("입금할 금액을 입력하세요:");
				int money = s.nextInt();
				
				//DTO를 만들고  데이터를 넣은 후 DTO를 이용해 서비스쪽에 넘김
				BankDTO dto = new BankDTO();
				dto.setUsername(name);
				dto.setBalance(money);
				
				BankService service = new BankService();
				
				//결과처리된 것을 다시 dto로 받음
				dto = service.deposit(dto);
				System.out.println(dto.getUsername() + "의 잔액은" + dto.getBalance() + "입니다.");
				

			}
			else if (menu.equals("2"))
			{
				
				System.out.print("출금할 사람의 이름: ");
				String name = s.nextLine();
				System.out.print("출금할 금액을 입력하세요:");
				int money = s.nextInt();
				
				//DTO를 만들고  데이터를 넣은 후 DTO를 이용해 서비스쪽에 넘김
				BankDTO dto = new BankDTO();
				dto.setUsername(name);
				dto.setBalance(money);
				
				BankService service = new BankService();
				
				//결과처리된 것을 다시 dto로 받음
				dto = service.withdrawal(dto);
				System.out.println(dto.getUsername() + "의 잔액은" + dto.getBalance() + "입니다.");
				
			}
			else if(menu.equals("3"))
			{
				
				System.out.print("이체할 사람의 이름: ");
				String name = s.nextLine();
				System.out.print("누구에게 이체 하시겠습니까:");
				String name2 = s.nextLine();
						
				System.out.print("이체할 금액을 입력하세요:");
				int money = s.nextInt();
				
				//DTO를 만들고  데이터를 넣은 후 DTO를 이용해 서비스쪽에 넘김
				BankDTO dto = new BankDTO();
				dto.setUsername(name);
				dto.setBalance(money);
				
				BankDTO dto2 = new BankDTO();
				dto2.setUsername(name2);
				dto2.setBalance(money);
				
				list.add(dto);
				list.add(dto2);
				BankService service = new BankService();
				
				//결과처리된 것을 다시 dto로 받음
				list = service.transfer(list);
				System.out.println(list.get(0).getUsername() + "의 잔액은" + list.get(0).getBalance() + "입니다.");
				System.out.println(list.get(1).getUsername() + "의 잔액은" + list.get(1).getBalance() + "입니다.");
			}
			

			
		}while(!menu.equals("4"));
		System.out.println("프로그램 종료");
			

		
	}
		
		
}
	



```


```java
//DTO

package DTO;

//DTO는 DB의 테이블을 근간으로 만든다.
public class BankDTO {
	
	String username;
	int balance;
	
	
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public int getBalance() {
		return balance;
	}
	public void setBalance(int balance) {
		this.balance = balance;
	}
	
	
}


```

```java
//Service

package Service;

import java.util.ArrayList;

import DAO.BankDAO;
import DTO.BankDTO;

public class BankService {

	public BankDTO deposit(BankDTO dto) {
		
		//로직 처리를 한다.
		//다만 우리 프로그램은 별다른 로직처리가 없음
		//Database 처리만 하면된다.
		
		
		//DB 처리후 결과를 dto에 저장하고 Controller 쪽으로 리턴 
		BankDAO dao = new BankDAO();
		dto = dao.UpdateDeposit(dto);
		
		return dto;
	}

	public BankDTO withdrawal(BankDTO dto) {
		
		BankDAO dao = new BankDAO();
		dto = dao.UpdateWithdrawal(dto);
		
		
		return dto;
	}

	public ArrayList<BankDTO> transfer(ArrayList<BankDTO> list) {
	
		BankDAO dao = new BankDAO();
		list = dao.UpdateTransfer(list);
		
		
		return list;
	}



}



```

```java
//DAO

package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import DTO.BankDTO;

public class BankDAO {

	public BankDTO UpdateDeposit(BankDTO dto) {
		try{
			//1. 드라이버 로딩
			//자바프로그램이 MySQL에 접근하기 위해서 필요한 라이브러리를 불러들인다.
			//pom.xml 에 MySQL에 대한 dependency를 입력해서 라이브러리를 다운로드 받는다.
			Class.forName("com.mysql.jdbc.Driver");
			
			//2. 실제 데이터베이스에 접속
			//어떤 데이터베이스에 접속할 건지, 아이디와 패스워드가 필요
			String url = "jdbc:mysql://localhost:3306/library";
			String id = "root";
			String pw = "cps431";
			Connection con = DriverManager.getConnection(url,id,pw);	
			
			//3. SQL문을 실행하기 위한 Statement를 생성한다.
			String sql ="update account set balance = balance + ? where username = ?";
			PreparedStatement pstmt = con.prepareStatement(sql);
			
			//sql문에 내가 원하는 문자열을 넣는 작업.
			pstmt.setInt(1, dto.getBalance()); 
			pstmt.setString(2, dto.getUsername()); 
			
			
			//4. Statement 실행!!
			//update 쿼리문 수행
			pstmt.executeUpdate();
			
			//5. 결과처리
			//update한 결과를 가져옴
			sql = "select username,balance from account where username = ?";
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, dto.getUsername()); 
			
			ResultSet rs = pstmt.executeQuery();
			rs.next();
			dto = new BankDTO();
			dto.setUsername(rs.getString("username"));
			dto.setBalance(rs.getInt("balance"));

			//6. 사용한 리소스 정리
			rs.close();
			pstmt.close();
			con.close();
			
			
		}catch(Exception e){
			//만약 오류가 생기면 오류 출력
			System.out.println(e);
		}
		
		
		return dto;
	}

	public BankDTO UpdateWithdrawal(BankDTO dto) {
		try{
			//1. 드라이버 로딩
			Class.forName("com.mysql.jdbc.Driver");
			
			//2. 실제 데이터베이스에 접속
			String url = "jdbc:mysql://localhost:3306/library";
			String id = "root";
			String pw = "cps431";
			Connection con = DriverManager.getConnection(url,id,pw);	
			
			//3. SQL문을 실행하기 위한 Statement를 생성한다.
			String sql ="update account set balance = balance - ? where username = ?";
			PreparedStatement pstmt = con.prepareStatement(sql);
			
			pstmt.setInt(1, dto.getBalance()); 
			pstmt.setString(2, dto.getUsername()); 
			
			
			//4. Statement 실행!!
			pstmt.executeUpdate();
			
			//5. 결과처리
			sql = "select username,balance from account where username = ?";
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, dto.getUsername()); 
			
			ResultSet rs = pstmt.executeQuery();
			rs.next();
			dto = new BankDTO();
			dto.setUsername(rs.getString("username"));
			dto.setBalance(rs.getInt("balance"));

			//6. 사용한 리소스 정리
			rs.close();
			pstmt.close();
			con.close();
			
			
		}catch(Exception e){
			//만약 오류가 생기면 오류 출력
			System.out.println(e);
		}
		
		
		return dto;
	}

	public ArrayList<BankDTO> UpdateTransfer(ArrayList<BankDTO> list) {
	
		try{
			//1. 드라이버 로딩
			Class.forName("com.mysql.jdbc.Driver");
			
			//2. 실제 데이터베이스에 접속
			String url = "jdbc:mysql://localhost:3306/library";
			String id = "root";
			String pw = "cps431";
			Connection con = DriverManager.getConnection(url,id,pw);	
			
			//3. SQL문을 실행하기 위한 Statement를 생성한다.
			//4. Statement 실행!!
			String sql ="update account set balance = balance - ? where username = ?";
			PreparedStatement pstmt = con.prepareStatement(sql);
			pstmt.setInt(1, list.get(0).getBalance()); 
			pstmt.setString(2, list.get(0).getUsername()); 
			pstmt.executeUpdate();
			
			
			sql ="update account set balance = balance + ? where username = ?";
			pstmt = con.prepareStatement(sql);
			pstmt.setInt(1, list.get(1).getBalance()); 
			pstmt.setString(2, list.get(1).getUsername()); 
			pstmt.executeUpdate();
			
			
			
			//5. 결과처리
			sql = "select username,balance from account where username = ?";
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, list.get(0).getUsername());
			ResultSet rs = pstmt.executeQuery();
			rs.next();
			BankDTO dto = new BankDTO();
			dto.setUsername(rs.getString("username"));
			dto.setBalance(rs.getInt("balance"));

			
			
			sql = "select username,balance from account where username = ?";
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, list.get(1).getUsername());
			rs = pstmt.executeQuery();
			rs.next();
			BankDTO dto2 = new BankDTO();
			dto2.setUsername(rs.getString("username"));
			dto2.setBalance(rs.getInt("balance"));

			list.clear();
			list.add(dto);
			list.add(dto2);
			
			//6. 사용한 리소스 정리
			rs.close();
			pstmt.close();
			con.close();
			
			
		}catch(Exception e){
			//만약 오류가 생기면 오류 출력
			System.out.println(e);
		}
		
		
		return list;
	}

		
}



```

### 결과 사진

<figure>
<p style="text-align: center;">	
	<img src="/images/book7.png">
</p>
</figure>

<figure>
<p style="text-align: center;">	
	<img src="/images/book8.png">
</p>
</figure>

