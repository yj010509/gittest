#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void gameStart(int* record); //게임 시작 함수
void initbingo(int* bingo); // 빙고 초기화 함수
void bingoBoard(int* bingo); // 빙고판을 만드는 함수
int checking(int* bingo); //빙고 유무 체크 함수
void inputNumber(int* user, int* com); //사용자가 숫자를 입력하는 함수
void randomNubmer(int* user, int* com); // 컴퓨터가 숫자를 지정하는 함수

int main()
{
    int menu;
    int record[3] = { 0 };

    printf("-------- BINGO GAME --------\n");
    
    while (1)
    {
        printf("1. GAME START\n");
        printf("2. GAME END\n");
        printf("게임을 시작하시려면 1번을, 게임을 종료하시려면 2번을 입력하세요: ");
        scanf_s("%d", &menu);

        switch (menu)
        {
        case 1:
            gameStart(record);
            break;
        case 2:
            printf("\n게임을 종료합니다.");
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
    // 사용자와 컴퓨터의 빙고판, 빙고수, 순서를 위한 변수

    srand((unsigned int)time(NULL));
    initbingo(user);
    initbingo(com);
    // 사용자와 컴퓨터의 빙고판을 숫자가 섞인 채로 배열

    while (1)
    {
        userCount = checking(user);
        comCount = checking(com);
        bingoBoard(user);
        //사용자와 컴퓨터의 빙고수를 체크하고 유저의 빙고판을 보여줌

        printf("\n현재 %d 빙고입니다.\n", userCount);

        if ((userCount >= 5 && turn) || (userCount >= 5 && comCount < 5))
        {
            printf("\n승리하였습니다.\n");
            break;
        }
        // 사용자의 빙고수가 5 이상일 때, 사용자의 순서이거나 컴퓨터의 빙고수가 5 이상이 되지 않을 경우
        else if (comCount >= 5)
        {
            printf("\n패배하였습니다.\n");
            break;
        }
        turn = !turn;
        // 사용자와 컴퓨터의 순서를 바꿈

        if (turn)
        {
            inputNumber(user, com);
        }
        else
        {
            randomNubmer(user, com);
        }
    }

    printf("\n컴퓨터의 빙고판\n");
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

        // 숫자를 교환하여 빙고판의 숫자들을 섞음
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
                printf("%c  X", 5); // 입력 혹은 지정된 숫자를 X로 바꿈
            else
                printf("%c %2d", 5, bingo[(i * 5) + j]);
        }
        printf("%c\n", 5);
    }
    printf("---------------------\n");
}

int checking(int* bingo)
{
    int check[12] = { 0 }; //빙고 체크 수를 초기화
    int count = 0;
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (bingo[i * 5 + j] == 88)
                check[i]++;
            // 가로 빙고 체크
            if (bingo[j * 5 + i] == 88)
                check[i + 5]++;
            // 세로 빙고 체크
        }
        for (j = i; j <= i; j++)
            if (bingo[i * 5 + j] == 88)
                check[10]++;
        // 대각선 빙고 체크(왼에서 오)
    }
    for (i = 4; i >= 0; i--)
    {
        for (j = 4 - i; j >= 4 - i; j--)
            if (bingo[i * 5 + j] == 88)
                check[11]++;
    }
    // 대각선 빙고 체크(오에서 왼)

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
        printf("숫자를 입력하세요: ");
        scanf_s("%d", &number);
        if (number < 1 || number>25)
            printf("1~25 사이의 숫자만을 입력하실 수 있습니다. ");
        // 사용자가 입력한 수가 1~25 범위의 숫자가 아닌 경우 오류 메세지 출력
        else // 사용자가 입력한 수가 1~25의 범위인 경우
        {
            for (int i = 0; i < 25; i++)
            {
                if (user[i] == number)
                {
                    user[i] = 88;
                    check = 1;
                    // 입력 받은 수를 X의 아스키코드 값인 88로 바꾸고 체크함
                }
                if (com[i] == number)
                {
                    com[i] = 88;
                    // 컴퓨터의 빙고판에도 똑같이 체크
                }
            }
            if (check)
                break;
            else
                printf("이미 입력된 숫자입니다.\n");
            // 이미 입력한 숫자를 입력한 경우 오류 메세지 출력
        }
    }
}

void randomNubmer(int* user, int* com)
{
    int number;
    int check;
    printf("컴퓨터의 순서입니다.\n");
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
                // 입력 받은 수를 X의 아스키코드 값인 88로 바꾸고 체크함
            }
            if (com[i] == number)
            {
                com[i] = 88;
                // 컴퓨터의 빙고판에도 똑같이 체크
            }
        }
        if (check)
            break;
    }

    Sleep(1000);
    printf("컴퓨터가 선택한 숫자는 %d 입니다\n\n", number);
}