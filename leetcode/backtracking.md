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
1.什么时候需要startIndex?
2.什么时候i=0，什么时候i=startIndex开始？
3.什么时候需要visited?
4.推入temp的条件？
5.什么时候需要backtacking(i+1)？
6.去重的几种操作？
*/
```
