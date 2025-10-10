# README

这个文档用来记录写这些代码获得的启发

但是250927才创建 之前写的有一些没保存下来:(



### Tree Traversals Again

> 读取数字的时候最好还是用`scanf`，如果用字符串再取出来的话，位数容易搞错
>
> 所以如果要取数，一般不要用`fgets()`，用`scanf()`





### 前+中生成树

> 想要除最后一次，每次输出后面都带空格，有两种做法：

1. 用计数器控制空格的输出

   ```c
   int cnt = time;
   // 可以是添加数据的时候cnt++
   printf(content);
   cnt--;
   if (cnt != 0)
   {
   	// 用cnt控制空格输出
   	printf(" ");
   }
   ```

2. 先保存，最后统一输出

   ```c
   int buff[MAXSIZE];
   int len;
   for ()
   {
   	buff[i] = data[i];
   	len++;
   }
   
   // 最后统一输出
   for()
   {
   	printf("%d%c", buff[i], " \n"[i == len-1]);
   	// 输出的%c由" \n"[i == len-1]决定
   	// 当i!=len-1 返回的是字符串[0]:空格
   	// 当i==len-1 返回的是字符串[1]:换行
   }
   ```


```
发现还有一种写法，和上面一个很相似
    for (int i = 0; i < N; ++i) {
        std::cout << cbt[i] << (i == N - 1 ? "" : " ");
                               ~~~~~~~~~~~~~~~~~~~~~~~~~
    }
```





### save007

> DFS/BFS的具体实现，可以先把伪代码写出来，然后再根据实际情况换成对应的内容

> 读取一行输入：用`fgets`
>
> `fgets(char*, num, stdin);`



### six_degrees_of_separation (3h59min)

>(*p)++和\*p++不一样，++优先级比\*高

> SDOS算法思路上好像就错了。我想的是，遍历开始的人start(1-vtxnum+1)，看start与target_person(也是遍历1-vtxnum+1)有没有在六度之内
>
> 但是实际上只需要遍历六层，看看六层里面有多少人就行了。我把这个问题想的复杂了好多

> 做到一半把六度忘了。要在入队前判断有没有满六层。满六层了要用continue继续处理队列中的元素，而不是break，这样子会丢元素（队列里面的还没处理好）。



### complete_binary_search_tree

> 根本没思路啊 看了视频才知道怎么写

> 有一个重要性质：**对一棵 BST 进行中序遍历，得到的一定是一个升序序列**