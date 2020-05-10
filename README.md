# basicCheckersGame
checkers game with c

You will program a checkers (dama) game using a random access file.

Your file consists of 8 records +1 (+1 is for the turn determination. 9th record consists of only one field) each one has 8 fields ( Dama tahtasının 8x8 kare olması dolayısıyla 8 kayıt ve her kaydın 8 alanı var)

There is 2 team, one is black, the other is white

If a tile(kare) isn’t occupied you left it empty. If a black stamp (dama taşı) is present on the tile you put ‘B’ if white ‘W’ and if it is a white transformed to a checker you put ‘WW’ if black ‘BB’ (Taşınız damaya dönüşmüşse siyah taş için BB, beyaz taş için ‘WW’ yazdıracaksınız)

Every time White plays first. You will put the 9th record to save the turn (Oyun sırasının kimde olduğunu belirlemek için 9.kayıtta sadece W veya B bilgisi saklanacak. Böylece oyuna devam etmek istendiğinde sıranın kimde olduğu belirlenecek)

Always white will start the game. All teams wil be played by a human. So idont want you to write an AI.

The main menu will be:

1.New game

2.Continue game

3.End Game



1.New game: You will initialize the file like this:



							
w	w	w	w	w	w	w	w
w	w	w	w	w	w	w	w
							
							
b	b	b	b	b	b	b	b
b	b	b	b	b	b	b	b
							
w							


And pc will ask the turn holder team which stamp will play like below

“Team White please enter your command.”

and the player should enter something like this:

a2a3

the first 2 character is the source the 2nd 2 characters is destination. You will map the board like the chess board. Horizontal tiles will be named from A to H, vertical tiles from 1 to 8. So a2a3 means front row leftmost tile of black will forward one tile.

Find the rules of the checkers game, the full rules will not be explained here .(there is only a handful rules so it is easy)
 
You should check if a movement command is legal, if it is, update the file if not list a message and ask again. A tile that can move forward to the last row of the board it become a checker and it can move horizontally or vertically as many tile as it want.

After each turn,9th record will alternate between w and b.



You will list the new status of the board to the screen and update the file. You will clear the screen and print the current status of the board like this:


8		ww				ww		
7								
6								
5	w	b		w				
4	b	W		b		b	w	
3								
2								
1	bb							bb
	A	B	C	D	E	F	G	H


You may separate with one or two tabs tab after each tile.



2.Continue game: This will continue the game from the file.

3.Exit Game: End the program.


 
You will also add a new feature as to write each turn’s player command into an additional sequential access file. The file’s content is going to be like this(first 2 characters are the team color and a colon- 4 characters for command) :



w:a3a4

b:	f5e5

….

…

…
