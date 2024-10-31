```c++
void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
```
```c++
/*
1.如何深入理解，把握递归栈？
2.什么时候需要startIndex?
3.什么时候i=0，什么时候i=startIndex开始？
4.什么时候需要visited?
5.推入temp的条件？
6.什么时候需要backtacking(i+1)？
7.去重（剪枝）的几种操作？
8.回溯需要回溯什么？
*/
```
