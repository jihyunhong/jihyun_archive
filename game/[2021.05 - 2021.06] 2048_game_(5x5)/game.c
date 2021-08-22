#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_TIME 3 * 1000

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard() {
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard(){
	tcsetattr(0, TCSANOW, &initial_settings);
}

int _kbhit() {
	unsigned char ch;
	int nread;
	if (peek_character != -1) return 1;
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);
	if(nread == 1) {
		peek_character = ch;
		return 1;
	}
	return 0;
}

int _getch() {
	char ch;
	if(peek_character != -1) {
		ch = peek_character;
		peek_character = -1;
		return ch;
	}
	read(0,&ch,1);
	return ch;
}

void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}

//보드 그리기 - 2차원 배열
int drawBoard(int board[5][5], double msec){
    int x,y;
    int score = 0;
    for (x=0; x<5; x++) {
        for (y=0; y<5; y++) {
            score += board[x][y];
        }
    }
    
    printf("\033[H");
    int t_min = msec / (60 * 1000);
    int t_sec = (msec - t_min*60*1000) / 1000;
    printf("[REMAIN TIME] %02d:%02d \n", t_min, t_sec);
    printf("[SCORE] %d\n\n", score);
    for (x=0;x<5;x++) {
        for (y=0;y<5;y++) {
            printf("%5d", board[x][y]);
        }
        printf("\n");
        printf("\n");
    }
    printf("\033[A");
    
    return score;
} 

//버튼 누를 때마다 랜덤으로 2만들어주기 위해서
void add2Randomly(int board[5][5]){

	int x,y;
	int r,num=0;
	// uint8_t n;
    int candilist[25][2]; //2 또는 4가 들어갈 수 있는 칸(현재 0인) 의 후보 리스트.
    srand(time(NULL));


	for (x=0;x<5;x++) {
		for (y=0;y<5;y++) {
			if (board[x][y]==0) {
				candilist[num][0] = x;
				candilist[num][1] = y;
				num++;
			}
		}
	}

	if (num>0) {
		r = rand()%num;
		x = candilist[r][0];
		y = candilist[r][1]; //랜덤으로 뽑기

		// 빈칸에 랜덤으로 2, 4 나오게 하기
		int random = rand() % 2;
		if (random == 0){
			board[x][y] = 2; //2 넣어주기
		}
		else{
			board[x][y] = 4; //4 넣어주기
		}
	}
}

void initBoard(int board[5][5], double msec) {
	int x,y;
	for (x=0;x<5;x++) {
		for (y=0;y<5;y++) {
			board[x][y] = 0;
		}
	} //보드 초기화 - 모두 0넣기
	add2Randomly(board);  // 게임 시작이니까 2 또는 4 두개 랜덤으로 들어감
	add2Randomly(board);
	drawBoard(board, msec); 
}

bool gameOver(int board[5][5]) {
    bool over = true;
    int x,y;
    
    //0인 칸이 남아있으면 not over
	for (x=0;x<5;x++) {
		for (y=0;y<5;y++) {
			if (board[x][y]==0){
                over = false;
                break;
                break;
            }
        } 
    }
    
    //좌우 같은 애 있으면 꽉 차 있어도 not over
    for (x=0;x<4;x++) {
        for (y=0;y<5;y++) {
			if (board[x][y]==board[x+1][y]){
                over = false;
                break;
                break;
            }
        }
    } 
    
    //상하 같은 애 있으면 꽉 차 있어도 not over
    for (x=0;x<5;x++) {
        for (y=0;y<4;y++) {
			if (board[x][y]==board[x][y+1]){
                over = false;
                break;
                break;
            }
        }
    } 
	return over;
}

bool gameClear(int board[5][5]) {
    int x, y;
    
    for (x=0; x<5; x++) {
        for (y=0; y<5; y++) {
            if (board[x][y] >= 2048) {
                return true;
            }
        }
    }
    
    return false;
}

void ranking(bool clear, int score, double msec, int move_count, int max_combo) {
    setBufferedInput(true);
    char name[100] = {0,};
    char c;
    printf("Enter Your Name : ");
    fflush(stdin);
    for (int i=0; i<100; i++) {
        c = getchar();
        putchar(c);
        if (c == '\n') {
            break;
        }
        name[i] = c;
    }
    
    char result[20];
    if (clear) {
        strcpy(result, "Success");
    }
    else {
        strcpy(result, "Failure");
    }
    
    int elapsed_time = MAX_TIME - (int) msec;
    int t_min = elapsed_time / (60 * 1000);
    int t_sec = (elapsed_time - t_min*60*1000) / 1000;
    
    FILE *fp;
    fp = fopen("game_result.txt", "a");
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (size == 0) {
        fprintf(fp, "Name,Result,SCORE,Elapsed_Time,Move_Count,Max_Combo\n");
    }
    fclose(fp);
    
    fp = fopen("game_result.txt", "a");
    fprintf(fp, "%s,%s,%d,%d,%d,%d\n", name, result, score, elapsed_time, move_count, max_combo);
    fclose(fp);
}

void rotate(int board[5][5]) { //시계 방향으로 돌리기
	int tmp[5][5];
    int x,y;
  
    for (x=0;x<5;x++) {
		for (y=0;y<5;y++) {
			tmp[x][y] = board[4-y][x]; //임시 어레이에 넣어놓고
		}
	}

    for (x=0;x<5;x++) {
		for (y=0;y<5;y++) {
			board[x][y] = tmp[x][y]; //다시 board에 붙여넣기
		}
	}
}

int moveUp(int board[5][5]) {
    int tmp[5][5]; //임시보드 만들어서 값 옮겨넣기
    int x,y;
    int target = 0;
    int done=0;
    int merge = 0;


    for (y=0;y<5;y++) {
        int target = -1; //임시보드의 0 index부터 채워넣기
        int done=0; //매번 초기화
        for (x=0;x<5;x++) {
            if (board[x][y] == 0) {
                continue; //0이면 임시보드에 넣지 않음
            }
            else if (done==1 && (board[x][y] == tmp[target][y])) {
                // 새로 넣으려는 수가 아까 넣은 수랑 같으면 그 칸 두배
                // done 초기화(또 2배되지 않게 하려고)
                tmp[target][y] *= 2;
                done=0;
                merge = 1;
            }
            else {
                tmp[++target][y]=board[x][y];
                done = 1; //어떤 수 있으면 target +1 해서 그 자리에 넣기
            }
            for (int i=target+1; i<5; i++){
                tmp[i][y] = 0; //나머지 칸들은 0으로 채워
            }
        }
    }

    for (x=0; x<5; x++) {
        for (y=0; y<5; y++) {
            board[x][y] = tmp[x][y]; //board에 붙여넣기
        }
    }
    
    return merge;
}

int moveLeft(int board[5][5]) {
    int merge;
    rotate(board);
    merge = moveUp(board);
    rotate(board);
    rotate(board);
    rotate(board); //rotate 이용해서 moveUp함수 그대로 쓰기
    return merge;
}

int moveRight(int board[5][5]) {
    int merge;
    rotate(board);
    rotate(board);
    rotate(board);
    merge = moveUp(board);
    rotate(board);
    return merge;
}

int moveDown(int board[5][5]) {
    int merge;
    rotate(board);
    rotate(board);
    merge = moveUp(board);
    rotate(board);
    rotate(board);
    return merge;
}

int moveup(int board[5][5]) {
    int merge;
    rotate(board);
    rotate(board);
    merge = moveDown(board);
    rotate(board);
    rotate(board);
    return merge;
} //moveUp함수 그대로 쓰면 에러가 나서 moveDown써서 "moveup"으로 새로 만들었습니다.


int main( ) {
    
    int choice;
    int board[5][5];
    char c;
    bool moved;
    
    int score;
    int move_count = 0;
    int merge = 0;
    int sum_combo = 0;
    int max_combo = 0;
    double msec;
    

    while (true) {
        printf("\nMain Menu\n1. Game Start  2. How to  3. Ranking  4. Exit\nPlease Enter an integer : ");
        scanf("%d", &choice);
        
        if (choice < 1 || choice > 4) {
            printf("Wrong Input.\n");
        }
        else if (choice == 1) {
            init_keyboard();
            msec = MAX_TIME;
            printf("\033[?25l\033[2J");
            // signal(SIGINT, signal_callback_handler);

            initBoard(board, msec); //제일 처음에 보드초기화
            setBufferedInput(false);
            while (true) {
                if (_kbhit()) { // 어떠한 키가 눌리면 진입
                    int c = _getch();
                    switch(c) {
                        case 97:	// 'a' key
                            moved = true;
                            merge = moveLeft(board); 
                            break;
                        case 100:	// 'd' key
                            moved = true;
                            merge = moveRight(board);
                            break;
                        case 119:	// 'w' key
                            moved = true;
                            merge = moveup(board);
                            break;
                        case 115:	// 's' key
                            moved = true;
                            merge = moveDown(board);
                            break;
                        default: moved = false;
                    }

                    if (moved == true) {
                        move_count += 1;
                        if (merge) {
                            sum_combo += 1;
                            if (max_combo < sum_combo) {
                                max_combo = sum_combo;
                            }
                        }
                        else {
                            sum_combo = 1;
                        }

                        score = drawBoard(board, msec);
                        add2Randomly(board);
                        score = drawBoard(board, msec);

                        if (gameOver(board)) {
                            printf("\nGAME OVER\n\n");
                            ranking(false, score, msec, move_count, max_combo);
                            break;
                        }

                        if (gameClear(board)) {
                            printf("\nGAME CLEAR\n\n");
                            ranking(true, score, msec, move_count, max_combo);
                            break;
                        }
                    }
                }

                usleep(10000); // sleep 10 ms

                score = drawBoard(board, msec);
                msec = msec - 10; // 10 ms 차감

                // Time OUT
                if (msec < 0) {
                    printf("\nGAME OVER\n\n");
                    ranking(false, score, msec, move_count, max_combo);
                    break;
                }
            }

            setBufferedInput(true);

            printf("\033[?25h\033[m");
            close_keyboard();
        }
        else if (choice == 2) {
            // how to
            printf("\n< How to Play >\n");
            printf("1. Use your ‘a’, ‘w’, ‘d’, ’s’ to move the tiles. \n2. If the number is same as the one touched, they merge into one. \n3. Add them up to reach 2048 within time limit! \n");
        }
        else if (choice == 3) {
            // If the result file exists
            if (access("game_result.txt", F_OK) == 0) {
                struct data {
                    char name[100];
                    char result[20];
                    int score;
                    int elapsed_time;
                    int move_count;
                    int max_combo;
                };
                struct data data_list[1000];
                struct data data_temp;
                
                int first = 1;
                int i = 0;
                char temp[1000] = {0,};
                char *elt;
                
                FILE *fp = fopen("game_result.txt", "r");
                while (fscanf(fp, "%s", temp) != EOF) {
                    if (!first) {
                        elt = strtok(temp, ",");
                        strcpy(data_list[i].name, elt);
                        elt = strtok(NULL, ",");
                        strcpy(data_list[i].result, elt);
                        elt = strtok(NULL, ",");
                        data_list[i].score = atoi(elt);
                        elt = strtok(NULL, ",");
                        data_list[i].elapsed_time = atoi(elt);
                        elt = strtok(NULL, ",");
                        data_list[i].move_count = atoi(elt);
                        elt = strtok(NULL, ",");
                        data_list[i].max_combo = atoi(elt);
                        i += 1;
                    }
                    first = 0;
                }
                int num_row = i;
                fclose(fp);
                
                for (i=0; i<num_row-1; i++) {
                    for (int j = i+1; j<num_row; j++){
                        if (data_list[i].score < data_list[j].score){
                            data_temp = data_list[i];
                            data_list[i] = data_list[j];
                            data_list[j] = data_temp;   
                        }
                    }
                }
                
                printf("\n<Ranking> (Sorted by SCORE)\n");
                for (i=0; i<num_row; i++) {
                    printf("Name : %s, Result : %s, Score : %d, ", data_list[i].name, data_list[i].result, data_list[i].score);
                    printf("Elapsed Time : %d, Move Count : %d, Max Combo : %d\n", data_list[i].elapsed_time, data_list[i].move_count, data_list[i].max_combo);
                }
                
            }
            // If the result file does not exist
            else {
                printf("No Data\n");
            }
        }
        else {
            printf("Bye~\n");
            break;
        }
    }
}

