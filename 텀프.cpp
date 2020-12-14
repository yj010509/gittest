#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void gameStart(int* record); //���� ���� �Լ�
void initbingo(int* bingo); // ���� �ʱ�ȭ �Լ�
void bingoBoard(int* bingo); // �������� ����� �Լ�
int checking(int* bingo); //���� ���� üũ �Լ�
void inputNumber(int* user, int* com); //����ڰ� ���ڸ� �Է��ϴ� �Լ�
void randomNubmer(int* user, int* com); // ��ǻ�Ͱ� ���ڸ� �����ϴ� �Լ�

int main()
{
    int menu;
    int record[3] = { 0 };

    printf("-------- BINGO GAME --------\n");
    
    while (1)
    {
        printf("1. GAME START\n");
        printf("2. GAME END\n");
        printf("������ �����Ͻ÷��� 1����, ������ �����Ͻ÷��� 2���� �Է��ϼ���: ");
        scanf_s("%d", &menu);

        switch (menu)
        {
        case 1:
            gameStart(record);
            break;
        case 2:
            printf("\n������ �����մϴ�.");
            return 0;
        default:
            break;
        }
    }

    return 0;
}

void gameStart(int* record)
{
    int user[25];
    int com[25];
    int userCount, comCount;
    int turn = 0;
    // ����ڿ� ��ǻ���� ������, �����, ������ ���� ����

    srand((unsigned int)time(NULL));
    initbingo(user);
    initbingo(com);
    // ����ڿ� ��ǻ���� �������� ���ڰ� ���� ä�� �迭

    while (1)
    {
        userCount = checking(user);
        comCount = checking(com);
        bingoBoard(user);
        //����ڿ� ��ǻ���� ������� üũ�ϰ� ������ �������� ������

        printf("\n���� %d �����Դϴ�.\n", userCount);

        if ((userCount >= 5 && turn) || (userCount >= 5 && comCount < 5))
        {
            printf("\n�¸��Ͽ����ϴ�.\n");
            break;
        }
        // ������� ������� 5 �̻��� ��, ������� �����̰ų� ��ǻ���� ������� 5 �̻��� ���� ���� ���
        else if (comCount >= 5)
        {
            printf("\n�й��Ͽ����ϴ�.\n");
            break;
        }
        turn = !turn;
        // ����ڿ� ��ǻ���� ������ �ٲ�

        if (turn)
        {
            inputNumber(user, com);
        }
        else
        {
            randomNubmer(user, com);
        }
    }

    printf("\n��ǻ���� ������\n");
    bingoBoard(com);
}

void initbingo(int* bingo)
{
    int i;
    int a, b;
    int tmp;

    for (i = 0; i < 25; i++)
    {
        bingo[i] = i + 1;
    }
    for (i = 0; i < 100; i++)
    {
        a = rand() % 25;
        b = rand() % 25;
        tmp = bingo[a];
        bingo[a] = bingo[b];
        bingo[b] = tmp;

        // ���ڸ� ��ȯ�Ͽ� �������� ���ڵ��� ����
    }
}

void bingoBoard(int* bingo)
{
    printf("\n---------------------\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (bingo[(i * 5) + j] == 88)
                printf("%c  X", 5); // �Է� Ȥ�� ������ ���ڸ� X�� �ٲ�
            else
                printf("%c %2d", 5, bingo[(i * 5) + j]);
        }
        printf("%c\n", 5);
    }
    printf("---------------------\n");
}

int checking(int* bingo)
{
    int check[12] = { 0 }; //���� üũ ���� �ʱ�ȭ
    int count = 0;
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (bingo[i * 5 + j] == 88)
                check[i]++;
            // ���� ���� üũ
            if (bingo[j * 5 + i] == 88)
                check[i + 5]++;
            // ���� ���� üũ
        }
        for (j = i; j <= i; j++)
            if (bingo[i * 5 + j] == 88)
                check[10]++;
        // �밢�� ���� üũ(�޿��� ��)
    }
    for (i = 4; i >= 0; i--)
    {
        for (j = 4 - i; j >= 4 - i; j--)
            if (bingo[i * 5 + j] == 88)
                check[11]++;
    }
    // �밢�� ���� üũ(������ ��)

    for (i = 0; i < 12; i++)
    {
        if (check[i] == 5)
            count++;
    }
    return count;
}

void inputNumber(int* user, int* com)
{
    int number;
    int check;
    while (1)
    {
        check = 0;
        printf("���ڸ� �Է��ϼ���: ");
        scanf_s("%d", &number);
        if (number < 1 || number>25)
            printf("1~25 ������ ���ڸ��� �Է��Ͻ� �� �ֽ��ϴ�. ");
        // ����ڰ� �Է��� ���� 1~25 ������ ���ڰ� �ƴ� ��� ���� �޼��� ���
        else // ����ڰ� �Է��� ���� 1~25�� ������ ���
        {
            for (int i = 0; i < 25; i++)
            {
                if (user[i] == number)
                {
                    user[i] = 88;
                    check = 1;
                    // �Է� ���� ���� X�� �ƽ�Ű�ڵ� ���� 88�� �ٲٰ� üũ��
                }
                if (com[i] == number)
                {
                    com[i] = 88;
                    // ��ǻ���� �����ǿ��� �Ȱ��� üũ
                }
            }
            if (check)
                break;
            else
                printf("�̹� �Էµ� �����Դϴ�.\n");
            // �̹� �Է��� ���ڸ� �Է��� ��� ���� �޼��� ���
        }
    }
}

void randomNubmer(int* user, int* com)
{
    int number;
    int check;
    printf("��ǻ���� �����Դϴ�.\n");
    Sleep(1000);

    while (1)
    {
        check = 0;
        number = rand() % 25 + 1;
        for (int i = 0; i < 25; i++)
        {
            if (user[i] == number)
            {
                user[i] = 88;
                check = 1;
                // �Է� ���� ���� X�� �ƽ�Ű�ڵ� ���� 88�� �ٲٰ� üũ��
            }
            if (com[i] == number)
            {
                com[i] = 88;
                // ��ǻ���� �����ǿ��� �Ȱ��� üũ
            }
        }
        if (check)
            break;
    }

    Sleep(1000);
    printf("��ǻ�Ͱ� ������ ���ڴ� %d �Դϴ�\n\n", number);
}