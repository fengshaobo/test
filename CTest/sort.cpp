//
//  sort.cpp
//  CTest
//
//  Created by fengshaobo on 13-8-14.
//  Copyright (c) 2013年 fengshaobo. All rights reserved.
//

#include "sort.h"


void sort_bubble(int arr[], int n)
{
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            
            if (arr[j]<arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


//快速排序
void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];
        
            
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        
        quick_sort(s, l, i - 1); // 递归调用
        quick_sort(s, i + 1, r);
    }
}


void sort_print(int arr[], int n)
{
    for (int i=0; i<n; i++) {
        printf("%d \n",arr[i]);
    }
}






