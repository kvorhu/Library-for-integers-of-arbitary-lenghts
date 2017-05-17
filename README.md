# Library-for-integers-of-arbitary-lenghts
A C library that does basic arithmetic operations (add, sub, multiply, divide and exponents) on Integers of arbitary lenghts
# Addition: 
  - The numbers are added by a brute force method.
  - Each element of the two numbers are added with the carry(which is zero initially).  
  - The sum is then appended to the char array, starting from the last element as sum%10. 
  - Carry is calculated as sum/10. This goes on till number of digits on both numbers are exhausted. 
  - If the signs vary, then it modifies the sign of the smaller number to that of the larger and returns the subtraction. 
# Subtraction: 
  - The two numbers are subtracted by brute force. 
  - As done in addition, each element of the two numbers are subtracted while adding the carry.(called the diff) 
  - Then it is appended to the result array as. The difference between the larger and smaller number is calculated. If the digit of the larger number is smaller, then, it borrows from the adjacent left digit. 
  - Borrowing is done by adding 10 to the number, while 1 is subtracted from the left index. Zero condition is taken care of too. 
  - It is passed on to add function if signs are different. (Passing the second intal by changing it's sign to that of the first. ) 
# Divison: 
  - The two numbers are divided by repeated subtraction brute force approach. 
  - The two numbers are repeatedly subtracted until it reaches zero or the second number is larger than the first. 
  - The number of subtractions are kept track of. This is the quotient. 
  - The sign of the result is '+' if signs of and b are the same. "-" , if signs of a and b are different. 
# Multiplication: 
  - Multiplication is done by Pen and Paper method. 
  - Each digit of the first intal is multiplied with every digit of the second intal and appended to result array with carry. 
  - This continues all the while shifting the appending index by 1, and adding to previous index value each time. 
  - The array is then reversed and passed to the resultant intal. 
# Exponentiation: 
  - The power of the integer is calculated by brute force. i.e by repeatedly multiplying the base number. 
  - The number of times it is multiplied is fixed by counting down the power, I.e 'b' intal. 
  - The number b is typecasted into integer. Therefore power cannot be calculated for very high numbers.  
 
