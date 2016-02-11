---
layout: post
title: 알고리즘 - maximum sum subarray
description: maximum sum subarray
modified: 2016-02-09
tags: [algorithm]
comments: true
image:
  feature: algorithm.jpeg
---
Maximum Sum Subarray를 알아내는 Kadane알고리즘은 array의 연속 부분합 중 가장 큰 값을 O(N)시간 복잡도로 알아내는 알고리즘이다. 2D Matrix에서 최대 합을 가진 영역을 알아내는 용도등을 위해 사용된다. 

### 필요한 자료 구조

- 지금까지의 최대 합을 저장하는 max_sum: -987654321로 초기화 
- 현재 계산하는 아이템을 고려했을때의 최대 합을 저장하는 cur_max_sum: -987654321로 초기화

```javascript
    int max_sum = -987654321;
    int cur_max_sum = -987654321;
```

영역이 필요하다면 s_idx와 e_idx와 max_s_idx와 max_d_idx를 사용한다. 영역을 구해야할 필요가 없다면 안써도 된다. 

```javascript
    int s_idx = 0;
    int e_idx = 0;
    int max_s_idx = 0;
    int max_e_idx = 0;
```

### 계산 

입력을 받으면서 즉시 계산한다. 

```ruby
    for(int i = 0; i<size; i++){
        int t;
        scanf("%d", &t);
        if(t < cur_max_sum + t){ 
            cur_max_sum = cur_max_sum + t;
        } else {                
            cur_max_sum = t;
        }
        if(cur_max_sum > max_sum){ 
            max_sum = cur_max_sum;
        }
    }
```

영역을 구해야 할 경우엔 다음과 같이 영역 변수의 값을 갱신한다.  

```javascript
    for(int i = 0; i<size; i++){
        int t;
        scanf("%d", &t);
        if(t < cur_max_sum + t){ //이전 item부터의 합이 연속됨
            cur_max_sum = cur_max_sum + t;
            e_idx = i;
        } else {                //현재 item이 시작
            cur_max_sum = t;
            s_idx = i;
            e_idx = i;
        }
        if(cur_max_sum > max_sum){ //최대값 갱신
            max_sum = cur_max_sum;
            max_s_idx = s_idx;
            max_e_idx = e_idx;
        }
    }
```

### code

```java
#include <iostream>
#include <vector>
using namespace std;
int kadane(vector<int> &In){
    int max_sum = -987654321;
    int cur_max_sum = -987654321;
    int s_idx = 0;
    int e_idx = 0;
    int max_s_idx = 0;
    int max_e_idx = 0;
    int size = (int)In.size();
    for(int i = 0; i<size; i++){
        if(In[i] < cur_max_sum + In[i]){ //이전 item부터의 합이 연속됨
            cur_max_sum = cur_max_sum + In[i];
            e_idx = i;
        } else { //현재 item이 시작
            cur_max_sum = In[i];
            s_idx = i;
            e_idx = i;
        }
        if(cur_max_sum > max_sum){ //최대값 갱신
            max_sum = cur_max_sum;
            max_s_idx = s_idx;
            max_e_idx = e_idx;
        }
    }
    return max_sum;
}
int main(){
    int N;
    scanf("%d", &N);
    vector<int> In(N);
    for(int i = 0; i<N; i++){
        scanf("%d", &In[i]);
    }
    
    int max_sum = -987654321;
    int cur_max_sum = -987654321;
    int s_idx = 0;
    int e_idx = 0;
    int max_s_idx = 0;
    int max_e_idx = 0;
    int size = (int)In.size();
    for(int i = 0; i<size; i++){
        if(In[i] < cur_max_sum + In[i]){ //이전 item부터의 합이 연속됨
            cur_max_sum = cur_max_sum + In[i];
            e_idx = i;
        } else { //현재 item이 시작
            cur_max_sum = In[i];
            s_idx = i;
            e_idx = i;
        }
        if(cur_max_sum > max_sum){ //최대값 갱신
            max_sum = cur_max_sum;
            max_s_idx = s_idx;
            max_e_idx = e_idx;
        }
    }
    
    printf("%d from %d to %d", max_sum, max_s_idx, max_e_idx); //must be 33 from 7 to 8
    return 0;
}
```

### 참고

위키피디아의 [알고리즘 설명](https://en.wikipedia.org/wiki/Maximum_subarray_problem)을 참고하자

### 실전 문제들 

##### [연속합](https://www.acmicpc.net/problem/1912)

- Kadane 알고리즘을 알고 있는지 묻는 문제
- **최대 100000개의 입력**이 들어오므로 O(n)알고리즘을 이용해야 한다.  
- 영역을 필요없으므로 영역 변수는 제외한다. 

