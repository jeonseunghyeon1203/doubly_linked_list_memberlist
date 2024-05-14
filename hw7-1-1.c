#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Member {
int id; // 회원 번호
char name[30]; // 회원 이름
char tel[30]; // 회원 연락처
struct Member *prev, *next;
} Member;

typedef struct MemberList {
int members; // 회원 인원수
int LastId; // 마지막 회원번호
} MemberList;

Member *head, *tail;


int menu_input(void)
{
    int menu;

    while (1) {
        printf("\n\n[1.회원등록  2.회원조회  3.회원탈퇴  4.회원목록  5.종료] : ");
        scanf("%d", &menu);
        fflush(stdin);
        if (menu >= 1 && menu <= 5)
            return menu;
    }
}

Member *create_Member(void)
{
    Member *tmp;

    tmp = (Member *)malloc(sizeof(Member));
    if (tmp == NULL) {
        fprintf(stderr, ">> Memory Allocation Error\n\n");
        exit(1);
    }

    printf("\n신규회원명: ");
    gets(tmp->name);
    printf("회원 전화번호 : ");
    gets(tmp->tel);
    fflush(stdin);
    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}

void insert_last(Member *tmp)
{
    if(tail==NULL){
        head=tail=tmp;
    }
    else {
        tail->next=tmp;
        tmp->prev=tail;
        tail=tmp;
    }
    if(tmp==head)
        tmp->id=1;
    else
        tmp->id=(tmp->prev->id)+1;

}

void mdelete(Member*head,Member *removed)
{
    if(removed==head){
        head=removed->next;
        removed->next->prev=NULL;
        free(removed);
    }
    else if(removed==tail){
        tail=removed->prev;
        removed->prev->next=NULL;
        free(removed);
    }
    else{
        removed->prev->next=removed->next;
        removed->next->prev=removed->prev;
        free(removed);
    }

}

void start(void)
{
    FILE *fp;
    Member *tmp;

    head = tail = NULL;
    printf(">> 프로그램을 시작합니다.\n");
    fp = fopen("MemberList7.bin", "rb");
    if (fp == NULL) {
        printf("기존 파일 정보는 없습니다.\n");
    } else {
        while (1) {
            tmp = (Member *)malloc(sizeof(Member));
            if (tmp == NULL) {
                fprintf(stderr, ">> Memory Allocation Error\n\n");
                exit(1);
            }
            if (fread(tmp, sizeof(Member), 1, fp) != 1)
                break;
            insert_last(tmp);
        }

        printf("기존 회원정보를 읽어왔습니다.\n");
    }

}

void stop(void)
{
    FILE *fp;
    Member *tmp;

    fp = fopen("MemberList7.bin", "wb");
    if (fp == NULL) {
        printf(">> 파일열기 오류로 회원정보를 저장하지 못하였습니다.\n");
    } else {
        for (tmp = head; tmp != NULL; tmp = tmp->next)
            fwrite(tmp, sizeof(Member), 1, fp);
        fclose(fp);
        printf(">> 현재 회원정보를 저장하였습니다.\n");
    }
    printf(">> 프로그램을 종료합니다.\n");

}



int main()
{
    Member *tmp;
    int menu;
    int n;
    char m_name[30];
    start();
    while (1) {
        menu = menu_input();
        switch (menu) {
        case 1:
            printf("회원등록\n");
            tmp = create_Member();
            insert_last(tmp);
            printf(">> 새로운 회원이 등록되었습니다.\n");
            break;
        case 2:
            printf("회원조회 \n");
            printf("회원명: ");
            gets(m_name);
            for (tmp = head; tmp != NULL; tmp = tmp->next)
                if (strstr(tmp->name, m_name)) {
                    printf("\n==>회원번호:%d [%s %s]\n",tmp->id, tmp->name, tmp->tel);
                    break;
                }
            if (tmp == NULL)
                printf("\n==> 해당 회원이 없습니다.\n");
            break;

        case 3:
            printf("회원탈퇴 \n");
            printf("탈퇴 회원번호:");
            scanf("%d",&n);
            for (tmp = head; tmp != NULL; tmp = tmp->next){
                if(tmp->id==n){
                mdelete(head,tmp);
                break;
                }
           }
           printf("탈퇴하였습니다\n");
           break;

        case 4:
            printf("회원목록 출력 \n");
             for (tmp = head; tmp != NULL; tmp = tmp->next)
                printf("[회원번호 %d %s 전화번호 %s]\n",tmp->id, tmp->name, tmp->tel);
            break;

        case 5:
            printf("종료 \n");
            stop();
            return 0;
        }
    }
    return 0;
}
