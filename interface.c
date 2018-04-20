#include <pic32mx.h>
#include <stdint.h>

char print[16];

void convertToChar (char* letters, int number)
{
  int i = 0;
  while (i < 16)
  {
    print[i] = ' ';
    i++;
  }
  i = 0;
  int stop = 0;
  while (*letters && stop < 2){
    print[i] = *letters;
    if(*letters == ' ')
      stop++;
    //else
    //  stop = 0;
    i++;
    letters++;
  }

  int size = number / 10;

  while (size > 0){
    size = size / 10;
    i++;
  }

  int carry = 0;
  do{
    carry = number / 10;
    print[i] = (char) ((number % 10) + 48);
    i--;
    number = carry;
  } while( number != 0 );
}

int interface(int foodCounter, int age, int weight, int score)
{
	display_init();
  convertToChar("food: ", foodCounter);
  display_string(0, print);
  convertToChar("weight(hg): ", weight);
	display_string(1, print);
  convertToChar("age: ", age);
	display_string(2, print);
  convertToChar("score: ", score);
	display_string(3, print);
	display_update();

  while(1){
    volatile int* switches = (volatile int*) getsw();
    if(!(*switches & 0x1)){
      display_init();
      tama(foodCounter,weight,age,score);
    }
  }

	for(;;) ;
	return 0;
}

int gameover(int score3){
  convertToChar("Score: ", score3);
  display_init();
  display_string(0, "GAME OVER");
  display_string(1, print);
  display_string(2, "");
  display_string(3, "");
  display_update();
  delay(10000000);

  char alphabet[4][16] = {
  {'>','A',' ','B',' ','C',' ','D',' ','E',' ','F',' ','G',' ','H'},
  {' ','I',' ','J',' ','K',' ','L',' ','M',' ','N',' ','O',' ','P'},
  {' ','Q',' ','R',' ','S',' ','T',' ','U',' ','V',' ','W',' ','X'},
  {' ','Y',' ','Z',' ',' ',' ',' ',' ',' ',' ','_',' ','_',' ','_'}};

  char name1[5] = {'I','K','E',':',' '};
  char name2[5] = {'A','B','E',':',' '};
  char name3[5] = {' ',' ',' ',':',' '};
  int score1 = 1000;
  int score2 = 800;

  int y = 0;
  int x = 0;

  int pos = 11;
  while(pos < 17){
    display_string(0, alphabet[0]);
    display_string(1, alphabet[1]);
    display_string(2, alphabet[2]);
    display_string(3, alphabet[3]);
    volatile int* buttons = (volatile int*) getbtns();
    volatile int* switches = (volatile int*) getsw();
    if (*buttons & 0x8 && x > 0){
      x -= 2;
      alphabet[y][x] = '>';
      alphabet[y][x+2] = ' ';
      delay(500000);
    }

    if (*buttons & 0x1 && ((x < 14 && y < 3) || (y == 3 && x < 2))){
      x += 2;
      alphabet[y][x] = '>';
      alphabet[y][x-2] = ' ';
      delay(500000);
    }

    if (*buttons & 0x2 && (( y < 2) || (x < 4 && y < 3))){
      y++;
      alphabet[y][x] = '>';
      alphabet[y-1][x] = ' ';
      delay(500000);
    }
    if (*buttons & 0x4 && y > 0){
      y--;
      alphabet[y][x] = '>';
      alphabet[y+1][x] = ' ';
      delay(500000);
    }
    if (*switches & 0x8){
      alphabet[3][pos] = alphabet[y][x+1];
      pos += 2;
      while(*switches & 0x8)
        switches = (volatile int*)getsw();
    }
    display_update();
    delay(100000);
  }

  name3[0] = alphabet[3][11];
  name3[1] = alphabet[3][13];
  name3[2] = alphabet[3][15];

  int casestate = 0;

  if(score3 > score2)
    casestate++;

  if(score3 > score1)
    casestate++;

  display_string(3, "");
  switch (casestate) {
    case 0:
    display_string(0, "IKE: 1000");
    display_string(1, "ABE: 800");
    convertToChar(name3, score3);
    display_string(2, print);
    break;

    case 1:
    display_string(0, "IKE: 1000");
    convertToChar(name3, score3);
    display_string(1, print);
    display_string(2, "ABE: 800");
    break;

    case 2:
    convertToChar(name3, score3);
    display_string(0, print);
    display_string(1, "IKE: 1000");
    display_string(2, "ABE: 800");
    break;
  }
  display_update();

  delay(50000000);
  display_string(0, "");
  display_string(1, "");
  display_string(2, "");
  main();

  return 0;
}


int cheatface(int foodCounter, int weight, int age, int score){

char alphabet[4][16] = {
  {'>','f','o','o','d',':',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ','w','e','i','g','h','t','(','h','g',')',':',' ',' ',' ',' '},
  {' ','a','g','e',':',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ','s','c','o','r','e',':',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

display_init();

int y = 0;

while(1){
  convertToChar(alphabet[0], foodCounter);
  display_string(0, print);
  convertToChar(alphabet[1], weight);
  display_string(1, print);
  convertToChar(alphabet[2], age);
  display_string(2, print);
  convertToChar(alphabet[3], score);
  display_string(3, print);
  volatile int* buttons = (volatile int*) getbtns();
  volatile int* switches = (volatile int*) getsw();
  if (*buttons & 0x8){
    switch (y) {
      case 0: foodCounter += 10;
      break;
      case 1:
        if(weight < 90)
          weight += 10;
        else
          weight = 99;
        break;
      case 2: age += 10;
      break;
      case 3: score += 10;
      break;
    }
    delay(500000);
  }

  if (*buttons & 0x1 ){
    switch (y) {
      case 0:
        if(foodCounter > 9)
          foodCounter -= 10;
        else
          foodCounter = 0;
        break;
      case 1:
        if(weight > 9)
          weight -= 10;
        else
          weight = 0;
        break;
      case 2:
        if(age > 9)
          age -= 10;
        else
          age = 0;
        break;
      case 3:
        if(score > 9)
          score -= 10;
        else
          score = 0;
        break;
    }
    delay(500000);
  }
  if (*buttons & 0x2 && y < 3){
    y++;
    alphabet[y][0] = '>';
    alphabet[y-1][0] = ' ';
    delay(500000);
  }
  if (*buttons & 0x4 && y > 0){
    y--;
    alphabet[y][0] = '>';
    alphabet[y+1][0] = ' ';
    delay(500000);
  }
  display_update();
  delay(100000);

  if(*switches & 0x2){
    display_init();
    tama(foodCounter,weight,age,score);
  }
}
  for(;;) ;
  return 0;
}
