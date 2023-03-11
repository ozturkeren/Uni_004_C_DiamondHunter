// Eren Öztürk METU NCC 140 PA3
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 100//n's will change after taking the size of board

int generate_board_size();
void populate_board(char [n][n], int sizeOfBoard);
int toss_coin();
int check_guess_computer(char [n][n], int sizeOfBoard, int *);
void computer_guess(int row, int column, int *);
int check_guess_user(char [n][n], int sizeOfBoard);
void display_results(int user_score, int computer_score);

int main(){
    srand(time(NULL));
    int whoStarts, sizeOfBoard=100, roundNumber, roundCounter, *GuessOfComputer, user_score=0, computer_score=0;
    char game_board[sizeOfBoard][sizeOfBoard];
    GuessOfComputer=(int*)malloc(2*sizeof(int));

    printf("*Game to play for an Exam?*\nLet's get started and toss a coin!\n");
    whoStarts=toss_coin();
    switch(whoStarts){
        case 0://User will start
            printf("User will start!\nEnter the number of rows: ");
            fflush(stdin);
            scanf("%d",&sizeOfBoard);
            populate_board(game_board, sizeOfBoard);
            printf("How many rounds would you like to play? ");
            scanf("%d",&roundNumber);
            for(roundCounter=1;roundCounter<=roundNumber;roundCounter++){
                printf("\nRound %d\n========\nUser Turn!\n",roundCounter);
                user_score+=check_guess_user(game_board, sizeOfBoard);
                printf("\nComputer turn!\n");
                computer_score+=check_guess_computer(game_board, sizeOfBoard, GuessOfComputer);
                printf("\nRound %d scores:\nUser: %d \nComputer: %d \n",roundCounter, user_score, computer_score);
            }
            break;
        case 1://Computer will start
            printf("Computer will start!\n");
            sizeOfBoard=generate_board_size();
            populate_board(game_board, sizeOfBoard);
            roundNumber=10;
            for(roundCounter=1;roundCounter<=roundNumber;roundCounter++){
                printf("\nRound %d\n========\nComputer Turn!\n",roundCounter);
                computer_score+=check_guess_computer(game_board, sizeOfBoard, GuessOfComputer);
                printf("\nUser turn!\n");
                user_score+=check_guess_user(game_board, sizeOfBoard);
                printf("\nRound %d scores:\nUser: %d \nComputer: %d \n",roundCounter, user_score, computer_score);
            }
            break;
    }
    display_results(user_score, computer_score);
    free(GuessOfComputer);
    return 0;
}

int generate_board_size(){
    return rand()%91 +10;//+10 because its between 10 and 100
}

void populate_board(char game_board[n][n], int sizeOfBoard){
    int counterForRow, counterForColumn;
    for(counterForRow=0;counterForRow<sizeOfBoard;counterForRow++){
        for(counterForColumn=0;counterForColumn<sizeOfBoard;counterForColumn++){
            if(toss_coin()==1)
                game_board[counterForRow][counterForColumn]='*';
        }
    }
    printf("Board is generated!\n");
}

int toss_coin(){
    return rand()%2;
}

int check_guess_computer(char game_board[n][n], int sizeOfBoard, int *GuessOfComputer){
    int numberOfStars=0, counter;
    computer_guess(sizeOfBoard, sizeOfBoard, GuessOfComputer);
    for(counter=0;counter<sizeOfBoard;counter++){
        if(game_board[GuessOfComputer[0]][counter]=='*')
            numberOfStars++;
    }
    printf("I will make a guess on row %d! \nI guess there are %d *s!\n",GuessOfComputer[0]+1, GuessOfComputer[1]+1);
    if(numberOfStars==GuessOfComputer[1]){
        printf("Correct guess!\n");
        return 1;
    }
    else{
        printf("Wrong guess!\n");
        return 0;
    }
}

void computer_guess(int row, int column, int *GuessOfComputer){
    GuessOfComputer[0]=rand()%row;
    GuessOfComputer[1]=rand()%column;//guess of stars
}

int check_guess_user(char game_board[n][n], int sizeOfBoard){
    int guessed_row, guessed_column, counter, numberOfStars=0;
    do{
        printf("Enter the row you want to make a guess? ");
        scanf("%d",&guessed_row);
        guessed_row--;//because row starts from 0
        if(guessed_row>=sizeOfBoard)
            printf("Come on! You have only %d rows, should be smaller than %d!\n",sizeOfBoard, sizeOfBoard);
    }while(guessed_row>=sizeOfBoard);
    do{
        printf("Enter the total *s in that row? ");
        scanf("%d",&guessed_column);
        guessed_column--;//because column starts from 0
        if(guessed_column>=sizeOfBoard)
            printf("Come on! You have only %d columns, should be smaller than %d!\n",sizeOfBoard, sizeOfBoard);
    }while(guessed_column>=sizeOfBoard);
    for(counter=0;counter<sizeOfBoard;counter++){
        if(game_board[guessed_row][counter]=='*')
            numberOfStars++;
    }
    if(numberOfStars==guessed_column){
        printf("Correct guess!\n");
        return 1;
    }
    else{
        printf("Wrong guess!\n");
        return 0;
    }
}

void display_results(int user_score, int computer_score){
    if(user_score==computer_score){
        user_score ? printf("\n\nNo winner, it is a draw!\n\n"):printf("\n\nYou both unlucky!\n\n");
    }
    else if(user_score>computer_score)
        printf("\n\n“Winner is User!\n\n");
    else
        printf("\n\nWinner is Computer!\n\n");
}
