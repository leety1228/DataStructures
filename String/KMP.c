#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>  

#define MAXLEN 40  // 字符串的最大长度  
  
typedef struct {  
    char ch[MAXLEN];  
    int len;  
} SString;  
  
// (1) StrAssign: 生成一个值等于chars的串S  
void StrAssign(SString *S, const char *chars) {  
    int i = 0;  
    while (chars[i] != '\0' && i < MAXLEN - 1) {  
        S->ch[i] = chars[i];  
        i++;  
    }  
    S->len = i;  
    S->ch[i] = '\0';  // 确保字符串以'\0'结尾  
}   

void GetNext(SString t,int next[]) //由模式串t求出next数组。默认字符串第一位存储在t.ch下标为0的这个位置
{
    int j = 0,k = -1;
    next[0]=-1;//第一个字符前无字符串，给值-1
    //因为next数组中j最大为t.len-1,而每一步next数组赋值都是在j++之后
    //所以最后一次经过while循环时j为t.len-2，故next赋值的下标为t.len-1正是最后一位
    while (j<t.len-1) { 
        if (k==-1 || t.ch[j]==t.ch[k]) {  //第一次或比较的字符相等时
        next[++j]=++k;//对应字符匹配情况下，s与t指向同步后移
        } else {
        k=next[k];
        //我们现在知道next[k]的值代表的是下标为k的字符前面的字符串最长相等前后缀的长度
        //也表示该处字符不匹配时应该回溯到的字符的下标
        //这个值给k后又进行while循环判断，此时t.ch[k]即指最长相等前缀后一个字符
        //为什么要回退此处进行比较，我们往下接着看。其实原理和上面介绍的KMP原理差不多
        }
    }
}
int KMPIndex(SString s,SString t)//s是主串，t是模式串，next是模式串对应的右移数组
{
    int next[MAXLEN], i=0,j=0;//i是用于主串的指针，j是用于模式串的指针
    GetNext(t, next);
    printf("The Next array is: ");
    for (int i = 0; i < t.len; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");

    while (i<s.len && j<t.len) 
    {
        if (j==-1 || s.ch[i]==t.ch[j]) {//第一次匹配或者主串模式串相同时，比较下一字符
            i++;j++;        //i,j各增1
        } else j=next[j];     //i不变,j后退，实现模式串右移
    }

    if (j>=t.len)
        return(i-t.len);   //返回匹配模式串的首字符下标
    else  
        return(-1);           //返回不匹配标志
}
  
// 测试代码  
int main() {  
    SString S, T;
    // StrAssign(&S, "aaaaab");
    // StrAssign(&T, "aaab");  
    // int index = KMPIndex(S, T);  
    // printf("Pattern found at index: %d\n", index); // 应该输出2  
    
    StrAssign(&S, "abaacacaabaababaabcc");
    StrAssign(&T, "abaabc");  
    int index = KMPIndex(S, T);  
    printf("Pattern found at index: %d\n", index); // 应该输出13  
  
    //StrAssign(&S, "abcabcabc");
    //StrAssign(&T, "abcabc");  
    // index = KMPIndex(text3, pattern3);  
    // printf("Pattern found at index: %d\n", index); // 应该输出0，因为"abcabc"从文本串的第0个字符开始  
  
    //StrAssign(&S, "abcd");
    //StrAssign(&T, "efg");  
    // index = KMPIndex(text4, pattern4);  
    // printf("Pattern found at index: %d\n", index); // 应该输出-1，因为模式串在文本串中未找到    
  
    return 0;  
}