The fight for the best number in the globe is going to finally come to an end.The top two contenders for the best number are number 2 and number 3.It's the final the entire world was waiting for. Expectorates from all across the globe came to witness the breath taking finals.

The finals began in an astonishing way.A common problem was set for both of them which included both these number.The problem goes like this.

Given a binary string (that is a string consisting of only 0 and 1). They were supposed to perform two types of query on the string.

Type 0: Given two indices l and r.Print the value of the binary string from l to r modulo 3.

Type 1: Given an index l flip the value of that index if and only if the value at that index is 0.

The problem proved to be a really tough one for both of them.Hours passed by but neither of them could solve the problem.So both of them wants you to solve this problem and then you get the right to choose the best number in the globe.

Input:

The first line contains N denoting the length of the binary string .The second line contains the N length binary string.Third line contains the integer Q indicating the number of queries to perform.This is followed up by Q lines where each line contains a query.

Output:

For each query of Type 0 print the value modulo 3.

Constraints:

1<= N <=10^5

1<= Q <= 10^5

0 <= l <= r < N

Sample Input(Plaintext Link)
 5
10010
6
0 2 4
0 2 3
1 1
0 0 4
1 1
0 0 3
Sample Output(Plaintext Link)
 2
1
2
1
Explanation
Query 1 : This is of type 0. The binary string is 010 which is equal to 2 and 2%3=2. So answer is 2.

Query 2 : This is of type 0. The binary string is 01 which is equal to 1 ( (2^1) * 0 +(2^0) * 1 ) =0 + 1 =1) and 1%3=1. So answer is 1.

Query 3 : This is of type 1. The value at index 1 is 0 so we flip it .The new string is 11010.

Query 4 : This is of type 0. The binary string is 11010 ( (2^0) * 0 +(2^1) * 1 +(2^2) * 0 +(2^3) * 1 +(2^4) * 1 = 2 + 8 +16 =26 ) which is equal to 26 and 26%3=2. So answer is 2.

Query 5 : This is of type 1. The value at index 1 is 1 so we do nothing .The new string is 11010.

Query 6 : This is of type 0. The binary string is 1101 ( (2^0) * 1 +(2^1) * 0 +(2^2) * 1 +(2^3) * 1 = 1 + 4+ 8 =13 ) which is equal to 13 and 13%3=1. So answer is 1.


-----------------------------------------------------code---------------------------------------------------------------
Problem 2 vs 3
Subproblem: How to compute the value of binary string S[0..9] modulo 3 efficiently if we know the corresponding value for S[0..4] and S[5..9] ?
Solution: let value of S[0..4] be x and S[5..9] be y. Then value of S[0..9] will be x*(25)+y.
Complete Solution Approach
Maintain a segment tree : tree[i] stores the value of the binary substring si to sj modulo 3.
Updates:
How to modify qth bit to 1. When modifying tree[i], update the corresponding child (i.e. tree[2i] responsible for [si..mid]or tree[2i+1] responsible for [mid+1..sj] ). When we have modified the child, now we want to calculate correct value of [si..sj]. Remember we have value of [si..mid] and [mid+1...sj].
Therefore, by our subproblem, tree[i] = tree[2i] * 2sj-mid + tree[2i+1] mod 3.
Queries:
Queries can be answered similarly by this divide and conquer approach.
Time Complexity
O(log N) update and O(log N) query. => O(Q*log N)

---------------------------------------------------------------code------------------------------------------------------------------------------------
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int arr[1010000];


struct abc
{
  int count ;
  int val;
}  tree[1010000];
/* Function to calculate x raised to the power y in O(logn)*/
int power(int x,  int y)
{
    int temp;
    if( y == 0)
        return 1;
    temp = power(x, y/2);
    temp%=3;
    if (y%2 == 0)
        return (temp*temp)%3;
    else
        return (x*temp*temp)%3;
}

abc query(int node,int start,int end,int r1,int r2)
 {
   //cout<<start<<"      "<<end<<endl;
  if(start>end || r1>end || r2<start) 
  {
   abc no;
   no.count=0;
   no.val=0;
   return no;
  }
   
   if(r1<=start && r2>=end)
    {
     // cout<<"  returnss "<<tree[node].count<<" "<<tree[node].val<<endl;
     return tree[node];
     
    }
    else
    {
     abc q1=query(2*node,start,(start+end)/2,r1,r2);
     abc q2=query(2*node+1,((start+end)/2)+1,end,r1,r2);
      abc d;
    
    d.count=q1.count+q2.count;
    d.val=(q1.val*power(2,q2.count)+q2.val);
    d.val%=3;
    if(d.val<0)d.val+=3;
   // cout<<"  return "<<d.count<<" "<<d.val<<endl;
    return d;
    }
 }
void update(int node ,int start,int end,int r1,int r2,int val)
 {
   //cout<<"update "<<start<<" "<<end<<endl;
  if(r1>end  || r2<start   || start>end) return  ;
  
  
  if(r1<=start && r2>=end)
   {
     tree[node].count=1;
     tree[node].val=1;
    
   }
   else
   {
    update(2*node, start,(start+end)/2,r1,r2,val);
    update(2*node+1, ((start+end)/2)+1,end,r1,r2,val);
      tree[node].count=tree[2*node].count+tree[2*node+1].count;
          tree[node].val=tree[2*node].val*power(2,tree[2*node+1].count)+tree[2*node+1].val;
          tree[node].val%=3;
    if(tree[node].val<0) tree[node].val+=3;
          
   }
    
   
 }  

void build(int node , int start,int end)
 {
 // cout<<start<<"            "<<end<<endl;
  if(start==end) 
  {
   
   tree[node].count=1;
   
   tree[node].val=arr[start];
  //  cout<<"  node "<<node<<" count "<<tree[node].count<<" val "<< tree[node].val<<endl;
  }
  else if(start>end) return ;
  else
   {
    
    build(2*node,start,(start+end)/2);
    build(2*node+1,((start+end)/2)+1,end);
    
    tree[node].count=tree[2*node].count+tree[2*node+1].count;
    tree[node].val=(tree[2*node].val*power(2,tree[2*node+1].count)+tree[2*node+1].val);
    tree[node].val%=3;
    if(tree[node].val<0) tree[node].val+=3;
//    cout<<"  node "<<node<<" count "<<tree[node].count<<" val "<< tree[node].val<<endl;
   }
   
 }
int main()
 {
  //freopen("abc.txt","w",stdout);
   int n;
    cin>>n;
     char cc[1000+n];
      cin>>cc;
      int pp=0;
      for(int i=0;i<n;i++)
      {
       if(cc[i]=='0') arr[i]=0;
       else arr[i]=1;
   }
    // for(int i=0;i<n;i++) cout<<arr[i]<<" ";
     // cout<<endl;
     for(int i=0;i<3*n;i++)
      {
       tree[i].count=0;
       tree[i].val=0;
   }
       build(1,0,n-1);

       
      int q;
       cin>>q;
        while(q--)
         {
          int inp;
           cin>>inp;
           if(inp==1)
           {
            int index;
             cin>>index;
             if(arr[index]==0)
             {
              arr[index]=1;
              update(1,0,n-1,index,index,1);
    }
     }
     else
     
             {
              int r1,r2;
               cin>>r1>>r2;
              //  cout<<"call"<<(n-1-r2)<<" "<<(n-1-r1)<<endl;
              abc res= query(1,0,n-1,r1,r2);
              
               cout<<res.val%3<<endl;
             }
         }
       
  return 0;
 }
