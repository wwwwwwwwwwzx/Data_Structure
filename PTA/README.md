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

   



### save007

> DFS/BFS的具体实现，可以先把伪代码写出来，然后再根据实际情况换成对应的内容

> 读取一行输入：用`fgets`
>
> `fgets(char*, num, stdin);`

> 