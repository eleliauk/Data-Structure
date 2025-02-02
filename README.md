# ccnu-data-structures

《数据结构及应用算法教程》（严蔚敏 陈文博 编著）
沈老师实验课上机题目 <br>
使用clang++ -std=c++11 name -o name 的方式编译

## 实验一
利用线性表实现集合交、并、差运算

## 实验二
利用双向循环链表实现学生信息排序
假设一学生信息文件中每个学生信息包括：
学号（8位字符）、姓名（10个字符）、成绩（整
型）及所用时间（整型），要求从该文件中读取每
个学生的信息存入一双向循环链表中，然后按
快速排序算法对其排序；排序的规则是：按成
绩从高到低，成绩相同时所用时间少者在先，
多者在后。要求输出排序后的结果。


## 实验三
利用栈和队列实现停车场管理
设停车场内只有一个可停放几辆汽车的狭长
通道，且只有一个大门可供汽车进出。汽车在
停车场内按车辆到达时的先后顺序，依次由北
向南排列（大门在最南端，最先到达的第一辆
车停放在车场的最北端），若车场内已停满几
辆汽车，则后来的汽车只能在门外的便道上等
候，一旦停车场内有车开走，则排在便道上的
第一辆车即可开入；当停车场内某辆车要离开
时，由于停车场是狭长的通道，在它之后开入
停车场的车辆必须先退出车场为它让路，待该
辆车开出大门外后，为它让路的车辆再按原次
序进入车场。在这里假设汽车不能从便道上开
走。设计一个停车管理程序。

## 实验四
设计一个能够反映域名结构的树，定义并实
现因特网域名的存储。通过树的遍历操作实现
因特网域名查询。
要求从文件中读入因特网域名信息，创建域
名树；对系统中所有的域名可以通过遍历进行
显示、添加、修改和保存；对指定的域名可以
查询。

## 实验五
利用图实现管道铺设的最佳方案
要在某个城市的n个居民区之间铺设煤气管
道，则在这n个居民区之间只要铺设n-1条管道
即可。假设任意两个居民区之间都可以假设管
道，但由于地理环境的不同，所需经费不同。
选择最优的施工方案使得中投资尽可能少
