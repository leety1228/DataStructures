#include <stdio.h>  
#include <stdbool.h>  
#include <string.h>  
  
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
  
// (2) StrInsert: 在串S的第pos个字符之前插入串T  
bool StrInsert(SString *S, int pos, SString T) {  
    if (pos < 1 || pos > S->len + 1) return false;  // 非法位置  
    if (S->len + T.len > MAXLEN - 1) return false;  // 插入后长度超过最大长度  
  
    for (int i = S->len; i >= pos - 1; i--) {  
        S->ch[i + T.len] = S->ch[i];  
    }  
  
    for (int i = 0; i < T.len; i++) {  
        S->ch[pos - 1 + i] = T.ch[i];  
    }  
  
    S->len += T.len;  
    return true;  
}  
  
// (3) StrDelete: 从串S中删除第pos个字符起长度为len的子串  
bool StrDelete(SString *S, int pos, int len) {  
    if (pos < 1 || pos + len - 1 > S->len) return false;  // 非法位置  
  
    for (int i = pos - 1; i < S->len - len; i++) {  
        S->ch[i] = S->ch[i + len];  
    }  
  
    S->len -= len;  
    S->ch[S->len] = '\0';  // 确保字符串以'\0'结尾  
    return true;  
}  
  
// (4) StrCopy: 由串T复制得串S  
void StrCopy(SString *S, SString T) {  
    for (int i = 0; i < T.len; i++) {  
        S->ch[i] = T.ch[i];  
    }  
    S->len = T.len;  
    S->ch[S->len] = '\0';  // 确保字符串以'\0'结尾  
}  
  
// (5) StrEmpty: 若串S为空串，则返回TRUE，否则返回FALSE  
bool StrEmpty(SString S) {  
    return S.len == 0;  
}  
  
// (6) StrCompare: 若S>T，则返回值大于0，若S=T则返回值为0，若S<T则返回值小于0  
int StrCompare(SString S, SString T) {  
    for (int i = 0; i < S.len && i < T.len; i++) {  
        if (S.ch[i] > T.ch[i]) return 1;  
        if (S.ch[i] < T.ch[i]) return -1;  
    }  
    return S.len - T.len;  
}  
  
// (7) StrLength: 返回串S的长度  
int StrLength(SString S) {  
    return S.len;  
}  
  
// (8) StrClear: 将S清为空串  
void StrClear(SString *S) {  
    S->len = 0;  
    S->ch[0] = '\0';  
}  
  
// (9) StrCat: 将串T的值链接在串S的后面  
bool StrCat(SString *S, SString T) {  
    if (S->len + T.len > MAXLEN - 1) return false;  // 连接后长度超过最大长度  
  
    for (int i = 0; i < T.len; i++) {  
        S->ch[S->len + i] = T.ch[i];  
    }  
  
    S->len += T.len;  
    S->ch[S->len] = '\0';  // 确保字符串以'\0'结尾  
    return true;  
}  
  
// (10) SubString: 返回串S的第pos个字符串起长度为len的子串  
bool SubString(SString *Sub, SString S, int pos, int len) {  
    if (pos < 1 || pos + len - 1 > S.len) return false;  // 非法位置  
  
    for (int i = 0; i < len; i++) {  
        Sub->ch[i] = S.ch[pos - 1 + i];  
    }  
  
    Sub->len = len;  
    Sub->ch[len] = '\0';  // 确保字符串以'\0'结尾  
    return true;  
}  
  
// (11) StrIndex: 若串S中存在和串T相同的子串，则返回它在串S中第pos个字符之后第一次出现的位置，否则返回0  
int StrIndex(SString S, SString T, int pos) {  
    if (pos < 1 || T.len == 0) return 0;  // 非法位置或空串T  
  
    for (int i = pos - 1; i <= S.len - T.len; i++) {  
        bool found = true;  
        for (int j = 0; j < T.len; j++) {  
            if (S.ch[i + j] != T.ch[j]) {  
                found = false;  
                break;  
            }  
        }  
        if (found) return i + 1;  
    }  
    return 0;  
}  
  
// (12) StrReplace: 用V替换串S中出现的所有与T相等的不重叠的子串  
bool StrReplace(SString *S, SString T, SString V) {  
    int pos = StrIndex(*S, T, 1);  
    while (pos != 0) {  
        if (!StrDelete(S, pos, T.len) || !StrInsert(S, pos, V)) {  
            return false;  // 替换失败  
        }  
        pos = StrIndex(*S, T, pos + V.len);  // 更新查找位置  
    }  
    return true;  
}  
  
// (13) StrDestroy: 销毁串S（此处仅作简单处理，不实际释放内存）  
void StrDestroy(SString *S) {  
    S->len = 0;  
    S->ch[0] = '\0';  
}  
  
// 测试函数    
int main() {    
    SString S, T, V, Sub;    
      
    // 初始化字符串  
    StrAssign(&S, "hello world");    
    StrAssign(&T, "world");    
    StrAssign(&V, "universe");    
    
    // 打印初始字符串  
    printf("S: %s\n", S.ch);    
    printf("T: %s\n", T.ch);    
    printf("V: %s\n", V.ch);    
    
    // 在S的第6个字符前插入T  
    if (StrInsert(&S, 6, T)) {    
        printf("After inserting T into S: %s\n", S.ch);  // 应输出 "hello worldworld"  
    }    
    
    // 从S的第7个字符开始删除5个字符  
    if (StrDelete(&S, 7, 5)) {    
        printf("After deleting 5 chars from S: %s\n", S.ch);  // 应输出 "hello world"  
    }    
    
    // 复制S到Sub  
    StrCopy(&Sub, S);    
    printf("Copied S to Sub: %s\n", Sub.ch);  // 应输出 "hello world"  
    
    // 检查S是否为空  
    printf("Is S empty? %s\n", StrEmpty(S) ? "TRUE" : "FALSE");  // 应输出 "FALSE"  
    
    // 比较S和T  
    printf("Comparing S and T: %d\n", StrCompare(S, T));  //输出 应 -1，因为 "hello world" < "world" 在字典序上  
    
    // 获取S的长度  
    printf("Length of S: %d\n", StrLength(S));  // 应输出 11  
    
    // 清空S  
    StrClear(&S);    
    printf("After clearing S: %s\n", S.ch);  // 应输出空字符串  
    
    // 将T连接到S  
    if (StrCat(&S, T)) {    
        printf("After concatenating T to S: %s\n", S.ch);  // 应输出 "world"  
    }    
    
    // 获取S从第1个字符开始长度为3的子串  
    if (SubString(&Sub, S, 1, 3)) {    
        printf("Substring of S from pos 1, len 3: %s\n", Sub.ch);  // 应输出 "wor"  
    }    
    
    // 在S中查找T的索引位置  
    int index = StrIndex(S, T, 1);    
    printf("Index of T in S: %d\n", index);  // 应输出 1，因为T在S的开始位置  
    
    // 用V替换S中所有出现的T  
    if (StrReplace(&S, T, V)) {    
        printf("After replacing T with V in S: %s\n", S.ch);  // 应输出 "universe"  
    }    
  
    // 销毁S（此处仅作简单处理，不实际释放内存）  
    StrDestroy(&S);  
    printf("After destroying S: %s\n", S.ch);  // 应输出空字符串，但此函数实际只是清空内容  
  
    return 0;  
}