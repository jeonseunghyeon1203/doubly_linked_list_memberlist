#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Member {
int id; // ȸ�� ��ȣ
char name[30]; // ȸ�� �̸�
char tel[30]; // ȸ�� ����ó
struct Member *prev, *next;
} Member;

typedef struct MemberList {
int members; // ȸ�� �ο���
int LastId; // ������ ȸ����ȣ
} MemberList;

Member *head, *tail;


int menu_input(void)
{
    int menu;

    while (1) {
        printf("\n\n[1.ȸ�����  2.ȸ����ȸ  3.ȸ��Ż��  4.ȸ�����  5.����] : ");
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

    printf("\n�ű�ȸ����: ");
    gets(tmp->name);
    printf("ȸ�� ��ȭ��ȣ : ");
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
    printf(">> ���α׷��� �����մϴ�.\n");
    fp = fopen("MemberList7.bin", "rb");
    if (fp == NULL) {
        printf("���� ���� ������ �����ϴ�.\n");
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

        printf("���� ȸ�������� �о�Խ��ϴ�.\n");
    }

}

void stop(void)
{
    FILE *fp;
    Member *tmp;

    fp = fopen("MemberList7.bin", "wb");
    if (fp == NULL) {
        printf(">> ���Ͽ��� ������ ȸ�������� �������� ���Ͽ����ϴ�.\n");
    } else {
        for (tmp = head; tmp != NULL; tmp = tmp->next)
            fwrite(tmp, sizeof(Member), 1, fp);
        fclose(fp);
        printf(">> ���� ȸ�������� �����Ͽ����ϴ�.\n");
    }
    printf(">> ���α׷��� �����մϴ�.\n");

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
            printf("ȸ�����\n");
            tmp = create_Member();
            insert_last(tmp);
            printf(">> ���ο� ȸ���� ��ϵǾ����ϴ�.\n");
            break;
        case 2:
            printf("ȸ����ȸ \n");
            printf("ȸ����: ");
            gets(m_name);
            for (tmp = head; tmp != NULL; tmp = tmp->next)
                if (strstr(tmp->name, m_name)) {
                    printf("\n==>ȸ����ȣ:%d [%s %s]\n",tmp->id, tmp->name, tmp->tel);
                    break;
                }
            if (tmp == NULL)
                printf("\n==> �ش� ȸ���� �����ϴ�.\n");
            break;

        case 3:
            printf("ȸ��Ż�� \n");
            printf("Ż�� ȸ����ȣ:");
            scanf("%d",&n);
            for (tmp = head; tmp != NULL; tmp = tmp->next){
                if(tmp->id==n){
                mdelete(head,tmp);
                break;
                }
           }
           printf("Ż���Ͽ����ϴ�\n");
           break;

        case 4:
            printf("ȸ����� ��� \n");
             for (tmp = head; tmp != NULL; tmp = tmp->next)
                printf("[ȸ����ȣ %d %s ��ȭ��ȣ %s]\n",tmp->id, tmp->name, tmp->tel);
            break;

        case 5:
            printf("���� \n");
            stop();
            return 0;
        }
    }
    return 0;
}
