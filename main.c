#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct koor{ /*to hold the values in the matrix*/
	int x_koor;
	int y_koor;
	char value;
};
typedef struct koor Array;
struct stack{ /*the stack we load the values to be printed.*/
    char *result;
    int size;
    int top;
};
typedef struct stack STACK;
STACK s;
void road(Array *matris,int indis,int matris_size);/*The first function we are looking for.*/
void find_key(Array *key,int ,int,char);/*If we do not have a key when we come to the door, we go back to look for him.*/
void key_kontrol(Array *key1,int,int);/*the last key value key will return*/
void write(int);/*write output.txt*/
void push(char);/* for to add to the stack*/
int kok(int);/* for sqrt value*/
int main(int argc,char *argv[]){
	int p;
	s.result = (char*)malloc(sizeof(char)*2);
	s.top=0;
	s.size=2;
	const char* file = NULL;
	file = argv[1];
	int i=0;
	char line[256];
	int j;
	int array_number=0;
	char ch;
	FILE *fp;
	fp=fopen(file,"r");
	while(fgets(line,sizeof(line),fp)){/*calculates the number of rows.*/
		p++;
	}
	array_number=p*p;
	Array array[array_number];
	rewind(fp);/* the demonstrator takes precedence.*/
	do{/* for add value to array. */
    	ch = getc(fp);
    	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='0'||ch=='1'){/*reading characters*/
    		array[i].value=ch;
			i++;
    	}
	}while(ch!=EOF);
	int size=kok(array_number);
	fclose(fp);
	for(j=0;j<size;j++){/* create matris*/
			for(i=0;i<size;i++){
				array[(size*j)+i].x_koor=j;
				array[(size*j)+i].y_koor=i;
	}
	}
	for(i=0;i<array_number;i++){/* find start value */
		if(array[i].value=='S'){
			road(array,i,size);
		}
	}
	return 0;
}
int kok(int a){
int i;
	for (i = 0; i <= a; i++) {
		int y= i*i;
        if (y==a) {
            return i; 
        }
    }
}
void road(Array *matris,int indis,int matris_size){
	if((matris[indis+1].value=='E'&&matris[indis+1].y_koor!=0)||matris[indis+matris_size].value=='E'||(matris[indis-1].value=='E'&&matris[indis-1].y_koor!=6)||matris[indis-matris_size].value=='E'){
		if(matris[indis+1].value=='E'){
			push('E');
		}
		else if(matris[indis+matris_size].value=='E'){
			push('S');
		}
		else if(matris[indis-1].value=='E'){
			push('W');
		}
		else{
			push('N');
		}
		write(s.top);
		exit(1);
	}
	else if(matris[indis+1].value=='3'){/*the way back 3 */
		push('E');
		matris[indis].value='1';
		road(matris,(indis+1),matris_size);
	}
	else if(matris[indis-1].value=='3'){
		push('W');
		matris[indis].value='1';
		road(matris,(indis-1),matris_size);
	}
	else if(matris[indis+matris_size].value=='3'){
		push('S');
		matris[indis].value='1';
		road(matris,(indis+matris_size),matris_size);
	}
	else if(matris[indis-matris_size].value=='3'){
		push('N');
		matris[indis].value='1';
		road(matris,(indis-matris_size),matris_size);
	}
	else if(matris[indis+1].value>='a'&&matris[indis+1].value<='z'&&matris[indis+1].y_koor!=0){/* firstly key kontrol right*/
		push('E');
		matris[indis].value='2';
		char x = matris[indis+1].value;
		push(x);
		road(matris,(indis+1),matris_size);	
	}
	else if(matris[indis+matris_size].value>='a'&&matris[indis+matris_size].value<='z'){/* door kontrol down*/
				push('S');
				char x = matris[indis+matris_size].value;
				push(x);
				matris[indis].value='2';
				road(matris,(indis+matris_size),matris_size);	
	}
	else if(matris[indis-1].value>='a'&&matris[indis-1].value<='z'){/* door kontrol left*/
			push('W');
			char x = matris[indis-1].value;
			push(x);
			matris[indis].value='2';
			road(matris,(indis-1),matris_size);	
		}
	else if(matris[indis-matris_size].value>='a'&&matris[indis-matris_size].value<='z'){/* door kontrol up*/
				push('N');
				char x = matris[indis-matris_size].value;
				push(x);
				matris[indis].value='2';
				road(matris,(indis-matris_size),matris_size);	
	}
			if(matris[indis-1].value>='A'&&matris[indis-1].value<='Z'){/* door kontrol left*/
						int i,control=0;/* control for the proper key if is not again go to kontrol*/
						char x = matris[indis-1].value;
						x=x+32;
						for(i=0;i<s.top;i++){
							if(x==s.result[i]){
								push('W');
								x=x-32;
								control=1;
								push(x);
								matris[indis].value='2';
								road(matris,(indis-1),matris_size);	
							}
						}
						if(control==0){
							find_key(matris,(indis),matris_size,x);
						}
			}
			else if(matris[indis+1].value>='A'&&matris[indis+1].value<='Z'){/* door kontrol right*/
						int i,control=0;
						char x = matris[indis+1].value;
						x=x+32;
						for(i=0;i<s.top;i++){
							if(s.result[i]==x){
								control=1;
								push('E');
								x=x-32;
								push(x);
								road(matris,(indis+1),matris_size);
							}
						}
						if(control==0){
							find_key(matris,(indis),matris_size,x);
						}
				}	
			else if(matris[indis+matris_size].value>='A'&&matris[indis+matris_size].value<='Z'){/* door kontrol down*/
						int i,control=0;
						char x = matris[indis+matris_size].value;
						x=x+32;
						for(i=0;i<s.top;i++){
							if(s.result[i]==x){
								control=1;
								matris[indis].value='1';
								push('S');
								x=x-32;
								push(x);
								road(matris,(indis+matris_size),matris_size);
							}
						}
						if(control==0)	{
								find_key(matris,(indis),matris_size,x);
							}
			}
			else if(matris[indis-matris_size].value>='A'&&matris[indis-matris_size].value<='Z'){/* door kontrol up*/
						int i,control=0;
						char x = matris[indis-matris_size].value;
						x=x+32;
						for(i=0;i<s.top;i++){
							if(s.result[i]==x){
								push('N');
								control=1;
								x=x-32;
								push(x);
								road(matris,(indis-matris_size),matris_size);
							}
						}
						if(control==0){
								find_key(matris,(indis),matris_size,x);
						}
	}
	else{
			if(matris[indis+1].value=='0'&&matris[indis+1].y_koor!=0)/* go to 0 first right and the passed values are 2.*/
				{	
					matris[indis].value='2';
					push('E');
					road(matris,(indis+1),matris_size);
									
				}
			else if(matris[indis+matris_size].value=='0'&&matris[indis+matris_size].x_koor!=0)/* go to 0 first down*/
			{
				if(matris[indis].value=='S'){
					matris[indis].value='1';
				}else{
						matris[indis].value='2';
				}
					push('S');
					road(matris,(indis+matris_size),matris_size);
			}
			else if(matris[indis-1].value=='0'&&matris[indis-1].y_koor!=matris_size-1)/* go to 0 first left*/
			{	
						matris[indis].value='2';
						push('W');
						road(matris,(indis-1),matris_size);
				
				}
			else if(matris[indis-matris_size].value=='0')/* go to 0 first up*/
			{		
					matris[indis].value='2';
					push('N');
					road(matris,(indis-matris_size),matris_size);
			}	
			else if(s.result[s.top-1]>='a'&&s.result[s.top-1]<='z'){/* if the last value in the blocked location is the key */
						key_kontrol(matris,(indis),matris_size);
			}
				else {/*if you enter the exit will wipe */
					matris[indis].value='1';
					if(matris[indis-1].value=='2'){
						pop();
						road(matris,(indis-1),matris_size);
					}
					else if(matris[indis+1].value=='2'&&matris[indis+1].y_koor!=0){
						pop();
						road(matris,(indis+1),matris_size);
					}
					else if(matris[indis+matris_size].value=='2'){
						pop();
						road(matris,(indis+matris_size),matris_size);
					}
					else if(matris[indis-matris_size].value=='2'){
						pop();
						road(matris,(indis-matris_size),matris_size);
					}
					else{/* if no solution */
						printf("No solution");
						exit(1);
					}
				}
			}	
		}
void key_kontrol(Array *matris1,int indis,int matris_size){	/*the last key value key will return*/
		if(matris1[indis+1].value=='0'&&matris1[indis+1].y_koor!=0){/* firtsly 0 kontrol */
			matris1[indis].value='2';
			push('E');
			road(matris1,(indis+1),matris_size);
		}
		else if(matris1[indis-1].value=='0'){
			matris1[indis].value='2';
			push('W');
			road(matris1,(indis-1),matris_size);
		}
		else if(matris1[indis-matris_size].value=='0'){
			matris1[indis].value='2';
			push('N');
			road(matris1,(indis-matris_size),matris_size);
		}
		else if(matris1[indis+matris_size].value=='0'){
			matris1[indis].value='2';
			push('S');
			road(matris1,(indis+matris_size),matris_size);
		}
			else if(matris1[indis+1].value=='2'){ /* secondly 2 kontrol and value close the road*/
				matris1[indis].value='1';
				push('E');
				key_kontrol(matris1,(indis+1),matris_size);
			}
			else if(matris1[indis-1].value=='2'){
				matris1[indis].value='1';
				push('W');
				key_kontrol(matris1,(indis-1),matris_size);
			}
			else if(matris1[indis-matris_size].value=='2'){
				matris1[indis].value='1';
				push('N');
				key_kontrol(matris1,(indis-matris_size),matris_size);
			}
			else if(matris1[indis+matris_size].value=='2'){
				matris1[indis].value='1';
				push('S');
				key_kontrol(matris1,(indis+matris_size),matris_size);
			}
			else{
				road(matris1,indis,matris_size);
		}
}
void find_key(Array *matris2,int indis,int matris_size,char x){/* find the key*/
	if(matris2[indis-1].value>='a'&&matris2[indis-1].value<='z'&&matris2[indis-1].y_koor!=matris_size-1){/* firstly key kontrol*/
			if(matris2[indis-1].value==x){
				push('W');
				matris2[indis].value='3';
				char y = matris2[indis-1].value;
				push(y);
				road(matris2,(indis-1),matris_size);
			}
			else{
				char z = matris2[indis-1].value;
				matris2[indis-1].value='1';
				find_key(matris2,(indis),matris_size,x);
			}
	}
	if(matris2[indis+1].value>='a'&&matris2[indis+1].value<='z'&&matris2[indis+1].y_koor!=matris_size-1){
			if(matris2[indis+1].value==x){
				push('W');
				matris2[indis].value='3';
				char y = matris2[indis+1].value;
				push(y);
				road(matris2,(indis+1),matris_size);
			}
			else{
				char z = matris2[indis+1].value;
				matris2[indis+1].value='1';
				find_key(matris2,(indis),matris_size,x);
			}	
	}
	if(matris2[indis-matris_size].value>='a'&&matris2[indis-matris_size].value<='z'&&matris2[indis-matris_size].y_koor!=matris_size-1){
			if(matris2[indis-matris_size].value==x){/* if find the key, go to road*/
				push('W');
				matris2[indis].value='3';
				char y = matris2[indis-matris_size].value;
				push(y);
				road(matris2,(indis-matris_size),matris_size);
			}
			else{/* close the road*/
				char z = matris2[indis-matris_size].value;
				matris2[indis-matris_size].value='1';
				find_key(matris2,(indis),matris_size,x);
			}
	}
	if(matris2[indis+matris_size].value>='a'&&matris2[indis+matris_size].value<='z'&&matris2[indis+matris_size].y_koor!=matris_size-1){
			if(matris2[indis+matris_size].value==x){
				push('W');
				matris2[indis].value='3';
				char y = matris2[indis+matris_size].value;
				push(y);
				road(matris2,(indis+matris_size),matris_size);
			}
			else{/* close the road*/
				char z = matris2[indis+matris_size].value;
				matris2[indis+matris_size].value='1';
				find_key(matris2,(indis),matris_size,x);
			}
	}
	else if(matris2[indis-1].value=='0'){/* mark path 3 with */
		matris2[indis].value='3';
		push('W');
		matris2[indis-1].value='3';
		find_key(matris2,(indis-1),matris_size,x);
	}
	else if(matris2[indis+1].value=='0'){
		push('E');
		matris2[indis+1].value='3';
		find_key(matris2,(indis+1),matris_size,x);
	}
		else if(matris2[indis-matris_size].value=='0'){
		push('N');
		matris2[indis-matris_size].value='3';
		find_key(matris2,(indis-matris_size),matris_size,x);
	}
	else if(matris2[indis+matris_size].value=='0'){
		matris2[indis].value='3';
		push('S');
		matris2[indis+matris_size].value='3';
		find_key(matris2,(indis+matris_size),matris_size,x);
	}
	else if(matris2[indis-matris_size].value=='2'){/*clogged path.*/
	matris2[indis].value='3';
	matris2[indis-matris_size].value='3';
	pop();
		find_key(matris2,(indis-matris_size),matris_size,x);
	}
	else if(matris2[indis-1].value=='2'&&matris2[indis-1].y_koor!=matris_size-1){
		pop();
		matris2[indis].value='3';
		find_key(matris2,(indis-1),matris_size,x);
	}
	else if(matris2[indis+matris_size].value=='2'&&matris2[indis+matris_size].x_koor!=0){
	pop();
	matris2[indis].value='3';
		find_key(matris2,(indis+matris_size),matris_size,x);
	}
	else if(matris2[indis+1].value=='2'&&matris2[indis+1].y_koor!=0){
		pop();
		matris2[indis].value='3';
		find_key(matris2,(indis+1),matris_size,x);
	}
	else{
		if(matris2[indis-1].value=='3'){/* if not, go back to 3 and call the road. */
		pop();
		matris2[indis].value='1';
		find_key(matris2,(indis-1),matris_size,x);
		}
		else if(matris2[indis+1].value=='3'){
		pop();
		matris2[indis].value='1';
		find_key(matris2,(indis+1),matris_size,x);
		}
		else if(matris2[indis-matris_size].value=='3'){
		pop();
		matris2[indis].value='1';
		find_key(matris2,(indis-matris_size),matris_size,x);
		}
		else if(matris2[indis+matris_size].value=='3'){
		pop();
		matris2[indis].value='1';
		find_key(matris2,(indis+matris_size),matris_size,x);
		}
	}
}
void push(char a){
	if(s.top>=s.size){/*to make room in memory.*/
		char *dizi2 =(char*)malloc(sizeof(char)*s.size*2);/*a new array is created and values are transferred.*/
		int i;
		for(i=0;i<s.size;i++){
			dizi2[i]=s.result[i];
		}
		free(s.result);/*we empty the values in the first row.*/
		s.result=dizi2;/*we are lining up the values first.*/
		s.size*=2;
	}
	s.result[s.top++]=a;
}
int pop(){/* value from the stack.*/
	return s.result[--s.top];
}
void write(int count){
	fflush(stdin);
	printf("It's DONE");
	FILE *fp_write;
	fp_write=fopen("output2.txt","w");
	fprintf(fp_write,"Start ");
	fwrite(s.result,1,count,fp_write);
	fprintf(fp_write," Exit ");
	fclose(fp_write);
}
