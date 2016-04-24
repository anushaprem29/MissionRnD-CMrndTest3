/*
Given a Tree which consists of operands and operators ,Solve the Tree and return the result
The tree will have special nodes of type enode which will have 3 fields
data => String of 5 chars .which can be either a operator or operand 
If its a operator its values will be one of the 3 following strings "+" , "-" , "*".
If its a operand its values will be any number from -9999 to 99999 in its respective string format;
Left and Right pointers will point to either NULL or another enode
Only the leaf nodes will have operand values .

Example 1:
    +
   / \
  4   5 
The Result expression is : 4+5 ,Ans is 9

Example 2:
        *
       / \
      -   5
     / \
    7   2

The Result expression is : (7-2) * 5  ,Ans is 25

Example 3:
       +
     /   \
    *     -  
   / \   / \
  7   2  4  *
           / \
          2   1
  
The Result expression is : (7*2) + (4-(2*1)) =>14+2 =>16 ,Ans is 16 

Constraints : 
Total number of enodes will be <=20 for 50% of Test cases
Data value will only have "0"<=data<="99999" values for 50% of cases .
Data value for operators will have sign as first character and \0 as next character .

Input :
Root node of a Tree of type enode
Output :
Return Final answer or -1 for Null inputs

Note :
->Dont Create an Extra Array/String ,or else your solution would receive 20%-40% Cut in the Marks you got .

Difficulty : Medium
*/
#include <stdlib.h>
#include <stdio.h>

//data can be accessed using root->data;
struct enode{
	char data[6];
	struct enode *left;
	struct enode *right;
};

/*
Helper Functions are optional to write 
*/
//Helper Functions Start
int isOperator(char *data){
	if ((data[0] == '*' || data[0] == '-' || data[0] == '+') && data[1]=='\0' )	return 1;
	return 0;
}
int isOperand(char *data){
	//for negative numbers
	if (data[0] == '-' && (data[1] >= '0' && data[1] <= '9'))	return 1;
	if (data[0] >= '0' && data[0] <= '9')	return 1;
	return 0;
}
int getOperand(char *data){
	//converts data string to an integer "123" => 123
	//only for integers.not for float points
	int iter,val=0,start=0;
	//Since it's a negative value, the value is been calculated from data[1]
	if (data[0] == '-')	start = 1;
	for (iter = start; data[iter] != '\0'; iter++){
		val = (val * 10) + (data[iter] - '0');
	}
	//if it is a negative value
	if (start)	val *= (-1);
	return val;
}
int calAns(struct enode *root){
	if (root == NULL)	return 0;
	int l_val, r_val;
	if (isOperator(root->data)){
		//Calculation of left and right values
		if (isOperand(root->left->data))
			l_val = getOperand(root->left->data);
		else l_val = calAns(root->left);
		if (isOperand(root->right->data))
			r_val = getOperand(root->right->data);
		else r_val = calAns(root->right);
		if (root->data[0] == '+'){
			return l_val + r_val;
		}
		else if (root->data[0] == '-'){
			return l_val - r_val;
		}
		if (root->data[0] == '*'){
			return l_val * r_val;
		}
	}
	return 0;
}
//Helper Functions end

int solve_tree(struct enode *root){
    if(root==NULL)	return -1;
	//solve_tree_wrapp()
	return calAns(root);
}

