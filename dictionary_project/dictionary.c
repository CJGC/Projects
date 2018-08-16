#include <stdio.h>

/* lenght line */
#define lenLine 255

/* total lines */
#define textLines 10000 

/* --------------- it will load text on memory --------------- */
 /* turn to uppercase char */
void upper(char &readChar){readChar -= 32;}

/* turn to lowercase char */
void lower(char &readChar){readChar += 32;}

/* check if is a valid line */
bool isValidLine(char M[][lenLine],int i, int j) {
  for(int k=0; k<=j; k++) {
    if(M[i][k] == ' ') continue;
    if(M[i][k] == '\n') return false; 
    return true;
  } 
}

/* it will load text into system memory */
void loadText(FILE *text,char M[][lenLine],int &loadedLines) {
  for(int i=0,j=0; (i<textLines && !feof(text));) { 
    char readChar = ' ';
    int k = 0;
    for(j=0; (j<lenLine && !feof(text) && readChar != '\n'); j++) {
      readChar = fgetc(text);
      if(readChar >= 65 && readChar <= 90) lower(readChar);
      M[i][j] = readChar;
      k = j;
    } 

    if(isValidLine(M,i,k)) {
      loadedLines++; 
      if(M[i][0] >= 97 &&  M[i][0] <= 122) upper(M[i][0]);
      i++;
    }
 
  }

  loadedLines --; //extra line
}

/* --------------- it will sort text with quicksort method --------------- */
/* it will swap two lines on M[]*/
void swap(char M[][lenLine],int left,int right) {
  char readChar = ' ';
  for(int j=0; j<lenLine; j++) {
    readChar = M[left][j];
    M[left][j] = M[right][j];
    M[right][j] = readChar;
  }
}

/* it will set the pivot from M[] */
void setPivot(char M[][lenLine],char pivot[],int left,int right) {
  int indexPivot = (left+right)/2;
  for(int j=0; j<lenLine; j++) pivot[j] = M[indexPivot][j];
}

/* it will check if a word is lesser than pivot */
bool lesserPivot(char M[][lenLine],char pivot[],int left) { 
  for(int j=0; j<lenLine; j++) {
    if(M[left][j] < pivot[j]) return true;
    if(M[left][j] > pivot[j] || 
       M[left][j] == '\n' || pivot[j] == '\n') 
      return false;
  }
}

/* it will check if a word is greater than pivot */
bool greaterPivot(char M[][lenLine],char pivot[],int right) {
  for(int j=0; j<lenLine; j++) {
    if(M[right][j] > pivot[j]) return true;
    if(M[right][j] < pivot[j] ||
       M[right][j] == '\n' || pivot[j] == '\n')
      return false;
  }
}

/* it will perform quick sort algorithm */
void quickSort(char M[][lenLine],int left,int right) {
  if(left >= right) return;
  int l = left, r = right;
  char pivot[lenLine];
  setPivot(M,pivot,left,right);

  while(l <= r) {
    while(lesserPivot(M,pivot,l)) l++;
    while(greaterPivot(M,pivot,r)) r--;
    if(l < r) {
      swap(M,l,r);
      l++;r--;
    }
    else if(l == r) {l++;r--;}
  }

  quickSort(M,left,r);
  quickSort(M,l,right);
}

/* --------------- it will write words on hard drive --------------- */
/* it will clear line array */
void clearLine(char line[]) {
  for(int j=0; j<lenLine; j++)
    line[j] = ' ';
}

/* it will compare two lines */
bool areEqual(char M[][lenLine],int i,char line2[]) {
  for(int j=0; j<lenLine; j++) {
    if(M[i][j] != line2[j]) return false;
    if(M[i][j] == '\n' && line2[j] == '\n') return true;
  }
}

/* it will write a line on hard drive */
void writeToDisk(FILE *disk,char M[][lenLine],int i) {
  for(int j=0; j<lenLine; j++) {
    fputc(M[i][j],disk);
    if(M[i][j] == '\n') break;
  }
}

/* it will swap two lines */
void swapLine(char M[][lenLine],int i,char line2[]) {
  for(int j=0; j<lenLine; j++) {
    line2[j] = M[i][j];
    if(M[i][j] == '\n') break;
  }
}

/* it will manage the process for hard drive writing */
void diskWriting(FILE *disk,char M[][lenLine],int loadedLines) {
  char previousLine[lenLine];
  clearLine(previousLine);
  for(int i=0; i<loadedLines; i++) { 
    if(!areEqual(M,i, previousLine)) {
      writeToDisk(disk,M,i); 
      swapLine(M,i,previousLine);
    }
  }
}

void printLine(char M[][lenLine],int i) {
  for(int j=0; j<lenLine; j++) 
    printf("%c",M[i][j]);
  printf("\n");
}

int main(int argc, char **argv) {
  if(argc != 2) {
    printf("Enter a valid filename <<%s filename.txt>>\n",argv[0]);
    return -1;
  }
  
  char textFile[textLines][lenLine];
  FILE *text=fopen(argv[1],"r"), *disk=fopen("output.txt","w");
  
  if(!text) {
    printf("Was not possible open the file\n");
    fclose(disk);
    return -1;
  }

  int loadedLines=0;
  loadText(text,textFile,loadedLines);
  printf("%d\n",loadedLines);
  quickSort(textFile,0,loadedLines-1);
  //clearMatrix(textFile,loadedLines);
  diskWriting(disk,textFile,loadedLines);
  fclose(text);
  fclose(disk);
}
