//
//  main.cpp
//  CTest
//
//  Created by fengshaobo on 13-4-2.
//  Copyright (c) 2013年 fengshaobo. All rights reserved.
//

#include <iostream>
#include <csetjmp>
#include <strings.h>

#include "sort.h"

using namespace std;


/*
原题：

用户输入M,N值，从1至N开始顺序循环数数，每数到M输出该数值，直至全部输出。写出C程序。（约瑟夫环问题 Josephus）

提示：

由于当某个人退出圆圈后，报数的工作要从下一个人开始继续，剩下的人仍然是围成一个圆圈的，可以使用循环表，由于退出圆圈的工作对应着表中结点的删除操作，对于这种删除操作频繁的情况，选用效率较高的链表结构，为了程序指针每一次都指向一个具体的代表一个人的结点而不需要判断，链表不带头结点。所以，对于所有人围成的圆圈所对应的数据结构采用一个不带头结点的循环链表来描述。设头指针为p，并根据具体情况移动。
为了记录退出的人的先后顺序，采用一个顺序表进行存储。程序结束后再输出依次退出的人的编号顺序。由于只记录各个结点的number值就可以，所以定义一个整型一维数组。如：int  quit[n];n为一个根据实际问题定义的一个足够大的整数。


代码：
*/

/* 结构体和函数声明 */
typedef struct _node_t
{
    int n_num;
    struct _node_t *next;
} node_t;

node_t *node_t_create(int n);
node_t *node_t_get(node_t **pn, int m);

/* 功能函数实现 */

/*
 *  name: node_t_create
 *  params:
 *    n         [in]        输入要构造的链表的个数
 *  return:
 *    返回构造成功的环形单向链表指针
 *  notes:
 *    构造节点数量为 n 的环形单向链表
 *
 *  author: A.TNG 2006/06/14 17:56
 */
node_t * node_t_create(int n)
{
    node_t *p_ret   = NULL;
    
    if (0 != n)
    {
        int     n_idx   = 1;
        node_t *p_node  = NULL;
        
        /* 构造 n 个 node_t */
        p_node = (node_t *) malloc(n * sizeof(node_t));
        if (NULL == p_node)
            return NULL;
        else
            memset(p_node, 0, n * sizeof(node_t));
        
        /* 内存空间申请成功 */
        p_ret = p_node;
        for (; n_idx < n; n_idx++)
        {
            p_node->n_num = n_idx;
            p_node->next = p_node + 1;
            p_node = p_node->next;
        }
        p_node->n_num = n;
        p_node->next = p_ret;
    }
    
    return p_ret;
}

/*
 *  name: main
 *  params:
 *    none
 *  return:
 *    int
 *  notes:
 *    main function
 *
 *  author: A.TNG 2006/06/14 18:11
 */


// test


#define N 8
#define BITSPERWORD 8
#define SHIFT 3
#define MASK 0x08

/*
 Note: int型数组a[1 + N/BITSPERWORD]，即a[1+312500]，(1+312500)*32=10000032 bit，
 比如：a[0]表示0~31 bit，a[1]表示32~63 bit，依此类推，所以a[1 + N/BITSPERWORD]表示
 0~10000031 bit，一共有10000032 bit。
 假设首先输入一个1，则数组a的存储情况为：(前面将a[0]展开)
 00000000 00000000 00000000 00000010 a[1] a[2] ...
 再输入一个3，则数组a的存储情况为：(前面将a[0]展开)
 00000000 00000000 00000000 00001010 a[1] a[2] ...
 再输入一个32，则数组a的存储情况为：(前面将a[0]、a[1]展开)
 00000000 00000000 00000000 00001010 | 000000000 00000000 00000000 00000001 a[2] ...
 因此不难发现，假设要输入的数为m，那么在输入m后，就将数组a中的第m bit位变为1。
 由此，所输入的最大数字为10000032-1=10000031，否则出现访问数组越界，将不能输出超出此
 范围的数字。
 wcdj于2010-1-14 晚
 */

//i>>SHIFT相当于i/32，i&MASK相当于i%32.
int arr[1+ N/BITSPERWORD];

void set(int i)
{
    arr[i>>SHIFT] |= (1<<(i&MASK));
}

int test(int i)
{
    return arr[i>>SHIFT] & (1<<(i&MASK));
}

int main()
{
    int     n, m;
    node_t *p_list, *p_iter;
    
    n = 20; m = 6;
    
    /* 构造环形单向链表 */
    p_list = node_t_create(n);
    
    /* Josephus 循环取数 */
    p_iter = p_list;
    m %= n;
    while (p_iter != p_iter->next)
    {
        int i   = 1;
        
        /* 取到第 m-1 个节点 */
        for (; i < m - 1; i++)
        {
            p_iter = p_iter->next;
        }
        
        /* 输出第 m 个节点的值 */
        printf("%d\n", p_iter->next->n_num);
        
        /* 从链表中删除第 m 个节点 */
        p_iter->next = p_iter->next->next;
        p_iter = p_iter->next;
    }
    printf("%d\n", p_iter->n_num);
    
    /* 释放申请的空间 */
    free(p_list);
    
    
    
///////
    
    return 0;
}

