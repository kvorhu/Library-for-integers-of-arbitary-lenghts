//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

// intal is an integer of arbitrary length. It has two fields; s and n.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "intal.h"

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
		n--;
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		//n++; //one extra for the + sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	i->n = n;
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b){
	//printf("%s\t%s\n",a->s,b->s);
	int k1, k2;
	char* res1;
	int* res;
	int i,r;
	int carry = 0;
	k1 = a->n;
	k2 = b->n;
	int m = k1;
	if (k1<k2) m = k2;
	int m2 = m;
	res = (int*)malloc(m + 1);
	res1 = (char*)malloc(m + 2);
	intal *result;
	result = (intal*)malloc(sizeof(struct intal));
	if (a->s[0] == b->s[0]){
		while (k1 > 0 && k2 > 0){
			r = ((a->s[k1] - '0') + (b->s[k2] - '0') + carry);
			if ((r) > 9){ carry = r/10; res[m] = r%10; }
			else { carry = 0; res[m] = r; }
			//printf("\n%d", res[m]);
			//printf("\t%d\n", m);
			k1--; k2--; m--;
			//printf("\n%d",k1);
			
		}
		//printf("\n%d   %d",k1,k2);
		//printf("\n%d\n",m2);
		//for (i = 1; i < m2 + 1; i++){ printf("%d\t", res[i]); }
		while (k1 > 0){
			res[m] = (a->s[k1] - '0') + carry;
			if (res[m] > 9){ carry = res[m]/10; res[m] = res[m]%10; }
			else carry = 0;
			k1--; m--;
		}
		while(k2 > 0){
			res[m] = (b->s[k2] - '0') + carry;
			if (res[m] > 9){ carry = res[m]/10; res[m] = res[m]%10; }
			else carry = 0;
			k2--; m--;
		}
		res[m] = carry;
		m--;
		//for (i = 1; i < m2 + 1; i++){ printf("%d\t", res[i]); }
		res1[0] = a->s[0];
		//printf("\n"); for (i = 1; i < m2 + 1; i++){ printf("%d\t", res[i]); }
		result->n = m2;
		//printf("\n%d\n",m2);
		//for (i = 1; i < m2 + 1; i++){ printf("%d\t", res[i]); }
		//printf("\n");
		for (i = 0; i < m2+1; i++){ res1[i+1] = res[i] + 48; }
		//for (i = 1; i < m2 + 1; i++){ printf("%d\t",res[i]); }
		result->s = res1;
		//printf("\n%d",strlen(res1));
		//printf("\n%s\n", result->s);
		return result;
		
	}
	else{
		intal *result1;
		result1 = (intal*)malloc(sizeof(struct intal));
		if(isLarger_intal(a,b)){
			result1 = b;
			result1->s[0] = a->s[0];
			return subtract_intal(a, result1);
			}
		else{
			result1 = a;
			result1->s[0] = b->s[0];
			return subtract_intal(b, result1);
			}
		
	}
}

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b){
	//printf("%s\t%s\n",a->s,b->s);
	int k1, k2, m2;
	char* res1;
	int* res;
	int i;
	//int borrow = 0;
	k1 = a->n;
	k2 = b->n;
	int m = k1;
	if (k1<k2) m = k2;
	int m1 = m;
	res = (int*)malloc(m+1);
	res1 = (char*)malloc(m+1);
	intal *result;
	result = (intal*)malloc(sizeof(struct intal));
	intal *a1;
	a1 = (intal*)malloc(sizeof(struct intal));
	intal *b1;
	b1 = (intal*)malloc(sizeof(struct intal));
	a1 = a; b1 = b;
	if(a->s[0] == b->s[0]){
		if (isLarger_intal(a,b)){
			res1[0] = a->s[0];
			//printf("\n%d  %d\n", k1, k2);
			while (k1 > 0 && k2 > 0){
				//printf("\n%d  %d\n", k1, k2);
				if (a->s[k1] >= b->s[k2]){
					res[m] = (a->s[k1] - '0') - (b->s[k2] - '0');
					m--; k1--; k2--;
				}
				//printf("\n%d  m %d\n", k1, k2);
				else{
					res[m] = (a->s[k1] - '0') + 10 - (b->s[k2] - '0');
					int i = k1;
					while (a->s[i - 1] == '0'){ a->s[i - 1] = 9 + '0'; i--; }
					int x = a->s[i - 1] - '0'; x--;
					a->s[i-1] = x + '0';
					//printf("\n%d",res[m]);
					//printf("\n%c",a->s[k1]);
					m--; k1--; k2--;
				}//printf("\n%d  %d\n", k1, k2);
			}
			while (k1 > 0){
				if(a->s[k1] == 0){res[m] = 0;}
				else {res[m] = a->s[k1] - '0';}
				//printf("\n%d",res[m]);
				//printf("\n%c",a->s[k1]);
				m--; k1--;
			}
		}
		else {
			res1[0] = b->s[0];
			while (k1 > 0 && k2 > 0){
				if (b->s[k2] >= a->s[k1]){
					res[m] = (b->s[k2] - '0') - (a->s[k1] - '0');
					m--; k1--; k2--;
				}
				else{
					res[m] = (b->s[k2] - '0') + 10 - (a->s[k1] - '0');
					int i = k1;
					while (b->s[i - 1] == '0'){ b->s[i - 1] = 9 + '0'; i--; }
					int x = b->s[i - 1] - '0'; x--;
					b->s[i-1] = x + '0';
					m--; k1--; k2--;
				}
			}
			while (k2 > 0){
				if(b->s[k2] == 0){res[m] = 0;}
				else {res[m] = b->s[k2] - '0';}
				m--; k2--;
			}
		}
	for (i = 1; i < m1+1; i++){ res1[i] = res[i] + 48; }
	result->s = res1;
	result->n = m1;
	a = a1; b = b1;
	return result;
	}
	else{
		intal *result1;
		result1 = (intal*)malloc(sizeof(struct intal));
		
		result1 = b;
		result1->s[0] = a->s[0];
		
		return add_intal(a,result1);
		}
	//for (i = 1; i < m1 + 1; i++){ printf("%d\t",res[i]); }
	//free(res);
}

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b){
	//printf("%s\t%s\n",a->s,b->s);
	int k1, k2, m;
	int i, j;
	int n1, n2;
	int a1, b1;
	int carry = 0;
	int r1 = 0;
	char* res;
	char sign;
	
	if(a->s[0] == b->s[0]){sign = '+' ; }//printf("%c\t%c\n",a->s[0],b->s[0]);}
	else{sign = '-';}
	
	k1 = a->n; k2 = b->n;
	m = k1+k2; 
	n1 = n2 = 0;
	int aa[k1];
	int bb[k2];
	
	int resint[m+1];
	res = (char*)malloc(m+2);
	
	for(i=0;i<m+1;i++){resint[i] = 0;}
	
	intal *result;
	result = (intal*)malloc(sizeof(struct intal));
	
	
	j = 0;
	for(i= k1; i > 0; i--){
		aa[j++] = a->s[i] - '0'; 
		}
	j = 0;
	for(i= k2; i > 0; i--){
		bb[j++] = b->s[i] - '0'; 
		}
	//printf("aaa");	
	for(i = 0; i < k1; i++){
		a1 = aa[i];
		n2 = 0;carry  = 0;
		//printf("aaa");
		for(j=0; j < k2; j++){
			b1 = bb[j]; 
			r1 = (a1 * b1) + resint[n1 + n2] + carry;
			carry = r1/10; 
			resint[n1 + n2] = r1%10;
			//printf("%d\t",resint[n1+n2]);
			n2++;
			}
		if(carry > 0){resint[n1+n2] += carry;}
		n1++;
		}
	//for(i= 0; i<m;i++){printf("%d\t",resint[i]);}
	j = 1;
	for(i = m-1; i >= 0; i--){
		res[j++] = resint[i] + '0';
		//printf("\n%c\n",res[j-1]);
		}
		
	
	//printf("%s",res);
	//printf("\n%c\n",res[0]);
	result->s = res;
	result->n = m;
	
	//
	
	result->s[0] = sign;
	//printf("\n%s\n", result->s);
	
	return result;

}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b){
	intal *result;
	result = (intal*)malloc(sizeof(struct intal));
	intal *result1;
	result1 = (intal*)malloc(sizeof(struct intal));
	char* res;
	long long int ri = 0;
	int k1, k2, m1;
	k1 = a->n; k2 = b->n;
	int m = k1 - k2 + 1;
	m1 = m;
	res = (char*)malloc(m);
	//char *r;
	//print_intal(a);printf("\t");print_intal(b);printf("\n");
	if ((isLarger_intal(a, b)) == 0){
		result->n = 1;
		res[0] = '+';
		res[1] = '0';
		//printf("\naaa\n");
		result->s = res;
		return result;
	}
	result1 = a;
	result1->s[0] = b->s[0];
	//print_intal(result1);
	//printf("");
	//printf("\n%s\n",result1->s);
	//print_intal(result1);
	while(isLarger_intal(result1, b)){
		result1 = subtract_intal(result1, b);
		ri = ri + 1;
		//printf("\n%lld\t",ri);
		//printf("\n%s\t",result1->s);printf("%d\n",isLarger_intal(result1,b));
	}
	//printf("\n%lld\n",ri);
	//sprintf(r, "%lld", ri);
	if (a->s[0] == b->s[0]){ res[0] = '+'; }
	else{ res[0] = '-'; }
	//printf("\n%d\n",m);
	while(ri > 0){
		res[--m] = ri%10 + '0';
		ri = ri/10;
		//printf("\n%c\n",res[m+1]);
		}
	//printf("\n%s\n",res);
	result->s = res;
	result->n = m1;
	return result;
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {
	int i;
	int m2;
	long long int bb;
	intal *result;
	result = (intal*)malloc(sizeof(struct intal));
	if (b->s[0] == '-'){ printf("N-A");return 0; }
	else{
		bb = atoll(b->s);
		//aa = atoll(a->s);
		//r = 1 + bb * log(aa);
		//m1 = b->n;
		m2 = a->n;
		char* res;
		res = (char*)malloc(m2+1);
		res = a->s;
		result->s = res;
		result->n = a->n;
		for (i = 0; i < bb; i++){
			result = multiply_intal(a, result);
		}
		return result;
	}
}

//Checks if the first is a greater number or not
//return 1 if a > b
int isLarger_intal(intal* a, intal* b){
	//print_intal(a);printf("\t");print_intal(b);
	int k1, k2;
	k1 = a->n;
	k2 = b->n;
	int j1=1;
	while(a->s[j1]=='0'){k1--; j1++;} //printf("\n%d",k1);
	int j2 =1;
	while(b->s[j2]=='0'){k2--; j2++;} //printf("\n%d",k2);
	//printf("\n%d  %d",k1,k2);
	//printf("\nhere here\n");
	if (k1 > k2){ return 1; }
	else if (k1 < k2){ return 0; }
	else if (k1 == k2){
		int i = 1;
		//printf("\nhere here\n");
		while (a->s[i+j1-1] == b->s[i+j2-1]){
			i++;
			//printf("\nhere here\n");
		}
		if (a->s[i+j1-1] > b->s[i+j2-1]) return 1;
		else return 0;
	}
}
