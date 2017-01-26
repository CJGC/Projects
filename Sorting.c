#include <stdio.h>

#define lenLine 255 /* lenght line */
#define textLines 5000 /* total lines */

/* --------------- will clear jumps vector --------------- */
void clearJumps(int jumps[],int size){
	for(int i=0 ;i<size ;i++) jumps[i] = 0;
}

/* --------------- will clear text file matrix --------------- */
void clearTextFile(char TextFile[][lenLine]){
	for(int i=0 ;i<textLines; i++)
		for(int j=0 ;j<lenLine; j++) TextFile[i][j] = ' ';
}

/* ---------------  will open text file --------------- */
FILE * openFile(FILE *p){
	char fileName[20];
   do{
      printf("file name: ");
      scanf("%s",fileName);
      p = fopen(fileName,"r");
   }while(!p);
	return p;
}

/* --------------- will load text on memory --------------- */
void upper(char &readChar){readChar -= 32;} /* upper case char */
void lower(char &readChar){readChar += 32;} /* lower case char */
void loadText(FILE *text,char M[][lenLine],int &loadedLines){ /* will load text */
	char readChar = ' ';
	for(int i=0; i<textLines; i++)
		for(int j=0; j<lenLine; j++){
			readChar = fgetc(text);
			if(!j && readChar >= 97 && readChar <= 122) upper(readChar);
			else if(j && readChar >= 65 && readChar <= 90) lower(readChar);
			else if(!j && readChar == ' ') readChar = '@';
			else if(!j && readChar == '\n'){i--;break;}
			M[i][j] = readChar;
			if(feof(text)) return;
			if(readChar == '\n'){loadedLines++; break;}
		}
}

/* --------------- will sort text with quicksort method --------------- */
void swap(char M[][lenLine],int left,int right){ /* will swap two lines on M[]*/
	char readChar = ' ';
	for(int j=0; j<lenLine; j++){
		readChar = M[left][j];
		M[left][j] = M[right][j];
		M[right][j] = readChar;
	}
}
void getPivot(char M[][lenLine],char pivot[],int left,int right){ /* will get pivot from M[] */
	int indexPivot = (left+right)/2;
	for(int j=0; j<lenLine; j++) pivot[j] = M[indexPivot][j];
}
bool lesserPivot(char M[][lenLine],char pivot[],int left){ /* check if a word is lesser than pivot */
	for(int j=0; j<lenLine; j++)
		if(M[left][j] == '\n' && pivot[j] == '\n') return false;
		else if(M[left][j] < pivot[j]) return true;
		else if(M[left][j] > pivot[j]) return false;
}
bool greaterPivot(char M[][lenLine],char pivot[],int right){ /* check if a word is greater than pivot */
	for(int j=0; j<lenLine; j++)
		if(M[right][j] == '\n' && pivot[j] == '\n') return false;
		else if(M[right][j] > pivot[j]) return true;
		else if(M[right][j] < pivot[j]) return false;
}
void quickSort(char M[][lenLine],int left,int right){ /* quick sort method */
	if(left >= right) return;
	int l = left, r = right;
	char pivot[lenLine];
	getPivot(M,pivot,left,right);
	while(l <= r){
		while(lesserPivot(M,pivot,l)) l++;
		while(greaterPivot(M,pivot,r)) r--;
		if(l < r){
			swap(M,l,r);
			l++;r--;
		}else if(l == r){l++;r--;}
	}
	quickSort(M,left,r);
	quickSort(M,l,right);
}

/* --------------- will detect repeated words --------------- */
void getWord(char M[][lenLine],char word[],int position){
	for(int j=0 ;j<lenLine; j++) word[j] = M[position][j];
}
bool repeatedWords(char word1[],char word2[]){
	for(int j=0 ;j<lenLine; j++) if(word1[j] != word2[j]) return false;
	return true;
}
void findRepeatedWords(char M[][lenLine],int jumps[],int loadedLines){
	char word1[lenLine], word2[lenLine];
	for(int i=0; i<loadedLines; i++){
		getWord(M,word1,i);
		for(int z=i+1; z<loadedLines;){
			getWord(M,word2,z);
			if(repeatedWords(word1,word2)){
				jumps[i] += 1;
				z++;
			}else break;
		}
		i += jumps[i];
	}
}

/* --------------- will write words on hard drive --------------- */
void diskWriting(FILE *disk,char M[][lenLine],int jumps[],int loadedLines){
	for(int i=0; i<loadedLines; i++){
		for(int j=0; j<lenLine; j++){
			fputc(M[i][j],disk);
			if(M[i][j] == '\n') break;
		}
		i += jumps[i];
	}
}

int main(){
	char textFile[textLines][lenLine];
	FILE *text=openFile(text), *disk=fopen("output.txt","w");
	int loadedLines=0, jumps[textLines];
	clearTextFile(textFile);
	clearJumps(jumps,textLines);
	loadText(text,textFile,loadedLines);
	quickSort(textFile,0,loadedLines-1);
	findRepeatedWords(textFile,jumps,loadedLines);
	diskWriting(disk,textFile,jumps,loadedLines);
	fclose(text);
	fclose(disk);
}
