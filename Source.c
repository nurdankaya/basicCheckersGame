#include <stdio.h>

FILE* fp;
FILE* fs;

void show();
void menu();
char player();
void changeLocation(char, char, char, char, char);
void end();
int checkValid(char, int, int);
void new();

int main(){            //w ve b normal ta�, W ve B dama ta�� olarak ayarlanm��t�r
    int state;
    char command[4];
    char playerColor;

   fs = fopen("allCommands.txt", "w");

    menu();
    scanf("%s", command);
    if (command[0] == '3')
        end();
    else if (command[0] == '1')
        new();

        while (1) {    // 3 girilene kadar (exit) komut almaya devam eder
            
            show();
            playerColor = player();
            scanf("%s", command);
            if (command[0] == '3')
                end();
            else if (command[0] == '1')
                new();
             
           changeLocation(command[0], command[1], command[2], command[3], playerColor);
           if (command[0] != 1 && command[0] != 2 && command[0] != 3) {   //girilen komutlar� allCommand.txt adl� dosyaya kaydeder
               fprintf(fs, "%c:%s\n", playerColor,command);               // !!!!!!! 3(exit) ile ��k�lmad��� zaman kaydetmez !!!!!!!!!
            }
        }
    fclose(fs);
    return 0;
}

void new(){                            // new game se�ildi�inde dosyay� ba�tan yazar
    fp = fopen("checkersGame.txt", "w+");
    fputs("                             \n", fp);
    fputs("w   w   w   w   w   w   w   w\n", fp);
    fputs("w   w   w   w   w   w   w   w\n", fp);
    fputs("                             \n", fp);
    fputs("                             \n", fp);
    fputs("b   b   b   b   b   b   b   b\n", fp);
    fputs("b   b   b   b   b   b   b   b\n", fp);
    fputs("                             \n", fp);
    fputs("w", fp);
    fclose(fp);
}
void end() {                 // menude 3 girildi�i zaman ��k�� yapar
    printf("\n the game is exited...");
    exit(0);
}

int checkValid(char color, int j, int m) {         //dama olmayan normal ta�lar�n kendi y�n�nden geriye gitmesini engeller
    if (color == 'w') {
        if (j > m) {
            printf("\n  You cannot go this way...\n");
            return 0;
        }
    }
    else if (color == 'b') {
        if (j < m) {
            printf("\n  You cannot go this way...\n");
            return 0;
        }
    }
    else if (color == 'W' || color == 'B')
        return 1;
    return 1;
}
int destIsBlank(int destOffset) {             //ta��n gitmek istedi�i konumun bo� olup olmad���n� kontrol eder
    fseek(fp, destOffset, 0);
    if (fgetc(fp) != ' ') {
        printf("Destination is not blank!");
        return 0;
    }
    return 1;
}
int truePlayer(int sourceOffset) {             // kaynak konumu ve oynamas� gereken oyuncuyu kar��la�t�rarak
    fp = fopen("checkersGame.txt", "r");          // do�ru oyuncunun oynay�p oynamad���n� kontrol eder
    fseek(fp, sourceOffset, 0);
    char x = fgetc(fp);
    fseek(fp, -1, SEEK_END);
    char end = fgetc(fp);

    if ((x == 'w' || x == 'W' )&& end == 'w') {
        return 1;
    }
    else if ((x == 'b' || x=='B') && end == 'b') {
        return 1;
    }
    printf("\nwrong player!\n");
    return 0;
}

void changeLocation(char source1, char source2, char destination1, char destination2, char color) {

    char h[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char v[8] = { '8', '7', '6', '5', '4', '3', '2', '1' };

    int i = 1;
    while (source1 != h[(i - 1)]) {
        i++;
    }
    int j = 1;
    while (source2 != v[(j - 1)]) {
         j++;
    }
    int k = 1;
    while (destination1 != h[(k - 1)]) {
        k++;
    }
    int m = 1;
    while (destination2 != v[(m - 1)]) {
        m++;
    }

    int offset1;             // source offset
    int first = (31 * (j - 1));
    int others = ((31 * (j - 1)) + (i - 1) + ((i - 1) * 3));
    offset1 = (i == 1) ? first : others;

    int offset2;             //destination offset
    first = (31 * (m - 1));
    others = ((31 * (m - 1)) + (k - 1) + ((k - 1) * 3));
    offset2 = (k == 1) ? first : others;

    int offsetBottom;
    fseek(fp, offset1, 0);
    char temp = fgetc(fp);

    if ((truePlayer(offset1) == 1) && (checkValid(temp, j, m) == 1) && (destIsBlank(offset2) == 1)) {  // ge�erlilik kontrolleri
        FILE* fp = fopen("checkersGame.txt", "r+");
        fseek(fp, offset1, 0);
        fputs(" ", fp);        
        if ((i == k) && (temp == 'W' || temp == 'B') ){  //(dama ta�� i�in)e�er yer de�i�tirme b1b6 (a�a�� do�ru)gibi row 
            char bottom = (temp == 'W') ? 'b' : 'w';      //de�i�tiriyorsa aradaki ta�lara bakar arada bir tane varsa onu siler
            printf("%c", bottom);
            int counter = 0;
            int delOffset;
            offsetBottom = offset2 + 31;
            if (offset1 > offset2) {
                while (offsetBottom < offset1) {
                    
                    fseek(fp, offsetBottom,SEEK_SET);
                    char ne = fgetc(fp);
                    if (ne == bottom) {
                        counter++;
                        delOffset = offsetBottom;
                    } 
                    offsetBottom += 31;
                }
            }   
            else if (offset2 > offset1) {               //(dama ta�� i�in)e�er yer de�i�tirme b6b1 (yukar� do�ru)gibi row 
                while (offsetBottom > offset1) {         //de�i�tiriyorsa aradaki ta�lara bakar arada bir tane varsa onu siler

                    fseek(fp, offsetBottom, SEEK_SET);
                    char ne = fgetc(fp);
                    if (ne == bottom) {
                        counter++;
                        delOffset = offsetBottom;
                    }
                    offsetBottom -= 31;
                }
            }
            if (counter == 1) {              //dama ta�� bir ta�� yer
                fseek(fp, delOffset, SEEK_SET);
                fputs(" ", fp);
            }
            else if (counter > 1) {
                printf("Invalid command!");             //dama ta�� birden fazla ta� yemeye �al���yorsa ge�ersiz
            }
       
        }
        else if ((j == m) && (temp == 'W' || temp == 'B')) {  //(dama ta�� i�in)e�er yer de�i�tirme b6h6 (sola do�ru)gibi row 
            char bottom = (temp == 'W') ? 'b' : 'w';      //de�i�tiriyorsa aradaki ta�lara bakar arada bir tane varsa onu siler
            int counter = 0;
            int delOffset;
            offsetBottom = offset2 + 4;
            if (offset1 > offset2) {
                while (offsetBottom < offset1) {

                    fseek(fp, offsetBottom, SEEK_SET);
                    char ne = fgetc(fp);
                    if (ne == bottom) {
                        counter++;
                        delOffset = offsetBottom;
                    }
                    offsetBottom += 4;
                }
           
            }
            else if (offset2 > offset1) {               //(dama ta�� i�in)e�er yer de�i�tirme b6h6 (sa�a do�ru)gibi row 
                while (offsetBottom > offset1) {         //de�i�tiriyorsa aradaki ta�lara bakar arada bir tane varsa onu siler
                    fseek(fp, offsetBottom, SEEK_SET);
                    char ne = fgetc(fp);
                    if (ne == bottom) {
                        counter++;
                        delOffset = offsetBottom;
                    }
                    offsetBottom -= 4;
                }
            }
        if (counter == 1) {                         //dama ta�� bir ta�� yer
            fseek(fp, delOffset, SEEK_SET);
            fputs(" ", fp);
            }
        else if (counter > 1) {
            printf("invalid command");             //dama ta�� birden fazla ta� yemeye �al���yorsa ge�ersiz
        }
        }
         if (k - i == 2 || i-k==2 || j-m ==2 || m-j == 2) {  //normal ta�larda ortadaki ta�� siler
             offsetBottom = (offset1 + offset2) / 2;
             fseek(fp, offsetBottom, SEEK_SET);
             fputs(" ", fp);

         }
        fseek(fp, offset2, 0);
        if (color == 'w') {                  //oynayan ta�a uygun olarak hedef konuma yerle�tirir
            if (m == 8 || temp == 'W')
                fputs("W", fp);
            else
                fputs("w", fp);
            fseek(fp, -1, SEEK_END);
            fputs("b", fp);
        }
        else {
            if (m == 1 || temp == 'B')
                fputs("B", fp);
            else
                fputs("b", fp);
            fseek(fp, -1, SEEK_END);
            fputs("w", fp);
        }
        fclose(fp);
    }
}

char player() {                             //oynamas� gereken oyuncunun bilgisini verir
    fp = fopen("checkersGame.txt", "r");
    fseek(fp, -1, SEEK_END);
    char x = fgetc(fp);
    printf("\n(1 for new game, 2 for continue game, 3 for exit)\n");
    if (x == 'w') {
        printf("\n\nTeam White please enter your command.\n");
        return x;
    }
    else {
        printf("\n\nTeam Black please enter your command.\n");
        return x;
    }
    fclose(fp);
}

void show() {         
    char c;
    int countWhite = 0;
    int countBlack = 0;
    int last = 249;
    fp = fopen("checkersGame.txt", "r");
    fseek(fp, 0, SEEK_SET);
    printf("\nA   B   C   D   E   F   G   H\n");
    printf("-----------------------------\n");
    int i = 8;
    while (1) {
        c = fgetc(fp);
        if (ftell(fp) % 31 == 0){
            printf("|%d", i);      // sat�rlar� numarand�rmak i�in
            i--;
        }
        if (ftell(fp) == last) {
            break;
        }
        printf("%c", c);
        if (c == 'w' || c == 'W') {
            countWhite++;
        }
        else if (c == 'b' || c == 'B') {
            countBlack++;
        }
    }
    printf("-----------------------------");
    if (countWhite == 0) {              //ta�� bitmeyen tak�m kazan�r
        printf("\n\n BLACK IS THE WINNER\n\n");
        exit(0);
    }else if (countBlack == 0) {
        printf("\n\n WHITE IS THE WINNER\n\n");
        exit(0);
    }
    fclose(fp);
}

void menu() {
    printf("\n\n*******************************\n");
    printf("CHECKERS GAME\n");
    printf("\n*******************************\n\n");

    printf("1.New game\n");
    printf("2.Continue game\n");
    printf("3.End Game\n");
}