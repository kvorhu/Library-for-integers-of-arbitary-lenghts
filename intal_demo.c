//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "intal.h"

int main() {
	int i = 1;       
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal* i3 = create_intal();
	
	read_intal(i1, "+1234");  //Enter Numbers here....
	read_intal(i2, "+12");
	
	printf("i1 = ");
	print_intal(i1);
	printf("\n");
	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	while(i){
		printf("Enter 1->Add\t2->Subtract\t3->Divide\t4->Multiply\t5->Power : ");
		scanf("%d",&i);
		printf("\n");
		switch(i){
			case 1:{printf("Addition : ");
				i3 = add_intal(i1, i2);
				print_intal(i3);
				printf("\n");}
				break;
	
			case 2:{printf("Subtraction : ");
				i3 = subtract_intal(i1, i2);
				print_intal(i3);
				printf("\n");}
				break;
	
			case 3:{printf("Division : ");
				i3 = divide_intal(i1, i2);
				print_intal(i3);
				printf("\n");}
				break; 
	
			case 4:{printf("Multiplication : ");
				i3 = multiply_intal(i1, i2);
				print_intal(i3);
				printf("\n");}
				break;
	
			case 5:{printf("pow : ");
				i3 = pow_intal(i1, i2);
				print_intal(i3);
				printf("\n");}
				break;
				
			default: {printf("Exiting Program\n");} return -1;
			}
		}

	delete_intal(&i1);
	delete_intal(&i2);
	delete_intal(&i3);
	return 0;
}
