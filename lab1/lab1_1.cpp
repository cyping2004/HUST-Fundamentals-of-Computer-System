#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
using namespace std;
#define N 5


struct student {
    char  name[8];  //以’0’结尾，最多7个有效字符
    short  age;
    float  score;
    char  remark[200];  // 备注信息，以’0’结尾
};

student new_s[N], old_s[N];
char message[N * 220];

int  pack_student_bytebybyte(student* s, int sno, char* buf) {
    int cnt = 0;
    int ptr = 0;
    while (cnt < sno) {
        //char 8 name
        char* tmp = (s + cnt)->name;
        while (*tmp != '\0') {
            buf[ptr++] = *tmp;
            tmp++;
        }
        buf[ptr++] = *tmp;
        //short age
        tmp = (char*)(s + cnt) + 8;
        buf[ptr++] = *tmp++;
        buf[ptr++] = *tmp++;
        //float score
        tmp = (char*)(s + cnt) + 12;
        buf[ptr++] = *tmp++;
        buf[ptr++] = *tmp++;
        buf[ptr++] = *tmp++;
        buf[ptr++] = *tmp++;
        //char 200 remark
        tmp = (char*)(s + cnt) + 16;
        while (*tmp != '\0')buf[ptr++] = *tmp++;
        buf[ptr++] = *tmp;
        cnt++;
    }
    return ptr;
}

int  pack_student_whole(student* s, int sno, char* buf) {
    int cnt = 0;
    int ptr = 0;
    while (cnt < sno) {
        //char 8 name
        strcpy((buf + ptr), (const char*)(s + cnt)->name);
        ptr += (int)strlen((s + cnt)->name) + 1;
        //short age
        *(short *)(buf + ptr) = (s + cnt)->age;
        ptr += 2;
        //float score
        *(float*)(buf + ptr) = (s + cnt)->score;
        ptr += 4;
        //char 200 remark
        strcpy((buf + ptr), (const char*)(s + cnt)->remark);
        ptr += (int)strlen((s + cnt)->remark) + 1;
        cnt++;
    }
    return ptr;
}

int restore_student(char* buf, int len, student* s) {
    int cnt = 0;
    int ptr = 0;
    while (ptr < len) {
        //char 8 name
        char* tmp = buf + ptr;
        while (*tmp != '\0') {
            s[cnt].name[ptr] = *tmp;
            ptr++;
            tmp++;
        }
        s[cnt].name[ptr++] = *tmp;
        //short age
        tmp = buf + ptr;
        s[cnt].age = *(short *)tmp;
        ptr += 2;
        //float score
        tmp = buf + ptr;
        s[cnt].score = *(float*)tmp;
        ptr += 4;
        //char 200 remark
        tmp = buf + ptr;
        int ptr_f = ptr;
        while (*tmp != '\0') {
            s[cnt].remark[ptr-ptr_f] = *tmp;
            ptr++;
            tmp++;
        }
        s[cnt].remark[ptr - ptr_f] = *tmp;
        ptr++;
        cnt++;
    }
    return cnt;
}

int main(void) {
    int i = 0;
    while (i < N) {
        cin >> old_s[i].name;
        cin >> old_s[i].age;
        cin >> old_s[i].score;
        cin >> old_s[i].remark;
        i++;
    }
    int x = pack_student_bytebybyte(old_s, 2, message);
    cout << x << endl;
    int y = pack_student_whole(old_s + 2, 3, message + x);
    cout << y << endl;
    int z = restore_student(message, x + y, new_s);
    cout << z << endl;
    for (int i = 0; i < 20; i++)printf("%02X ", (unsigned char)message[i]);  
    float test = 52;
    return 0;
}
