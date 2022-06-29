#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//testing testing 

typedef struct Node   //operator stack (for infix-prefix, postfix-infix,evaluation)
{ 
    char cell;
    struct Node *next;
} Node;
typedef Node *Nodeptr;  //Nodeptr will be equivalent to Node* 

typedef struct Node2    //stack for  prefix-infix & postfix-infix operations
{ 
    char cell[40];
    struct Node2 *next;
} Node2;
typedef Node2 *Node2ptr;   //Node2ptr will be equivalent to Node2*

typedef struct Node3      //operand stack (for evaluation)
{ 
    int operand;
    struct Node3 *next;
} Node3;
typedef Node3 *Node3ptr;    //Node3ptr will be equivalent to Node3*

int checkexp(char expr[]);
int det(char expr[40]);
int parentheses(char expr[], int type);
void infixpostfix(char expr[], char post[40]);
void infixprefix(char expr[], char post[40]);
void prefixinfix(char expr[], char post[40]);
void postfixinfix(char expr[], char post[40]);
int eval(char expr[]);                                            //function prototype
void push(char new, Nodeptr* sptr);
void push2(char new[], Node2ptr* sptr);
void pushv(int new, Node3ptr* sptr);
void pop(Nodeptr* sptr);
void pop2(Node2ptr* sptr);
void popv(Node3ptr* sptr);
int precedence(char operand);

int main()
{
	int x=1;
	FILE *fileptr;  //file pointer
	 printf("!!!: Expression must have space between operand and operators.\n");
	 printf("!!!: Expression must have not more than 5 operators and/or 6 operands\n");
	 printf("!!!: Failure to comply will result in error during conversion or calculation or termination of program\n\n");
	 fileptr = fopen("output.txt","w");
	 if(fileptr == NULL)
     {
             printf("Error!File cannot be opened");         //if file cannot be opened. error.    
     }
	 while(x==1)  //loop while x==1
	 {
		 int check,detm, parent,result=0,loop;
	     char selection;  
	     int convert;
	     char expr[40]={'\0'};
	     char preinfix[40]={'\0'}; //string for the prefix-infix conversion
	     char prepostfix[40]={'\0'};  //string for the prefix-postfix conversion
	     char inprefix[40]={'\0'};    //string for the infix-prefix conversion
	     char inpostfix[40]={'\0'};   // string for the infix-postfix conversion
	     char postinfix[40]={'\0'};   //string for the postfix-infix conversion
	     char postprefix[40]={'\0'};   //string for the postfix-prefix conversion

		 printf("Enter an expression: ");       // prompt user for input
         fflush(stdin);                         //clear input buffer
		 fgets(expr, 40, stdin);                //get the expression
        check=checkexp(expr);                   //check for any invalid characters
		if(check==0)
		{
			break;          //if there is invalid character checkexp function will return 0 and will break off the while loop
		}
		detm=det(expr);     //check expression type/number of operand &operator/if there is space between operand & operator
		if(detm==0)
		{
			break;         //if there is error, det function will return 0 and will break off the while loop
		}
		parent=parentheses(expr,detm); //check for any imbalance parentheses
		if(parent==0)
		{
			break;  //if there is error parentheses function will return 0 and will break off the while loop
		}
		if(detm==1) //if detm returns 1 (prefix expression)
	    {
		    printf("Expression is an Prefix expression. Do you wish to : \n");
			printf("A-Convert expression\n");
			printf("B-Evaluate Expression\n");
			printf("C-Exit\n");
		  scanf("%c",&selection);  
		  if(selection=='a'||selection=='A')
		  {
			     printf("Do you wish to: \n");
			     printf("1-Convert to infix\n");
			     printf("2-Convert to postfix?\n");
			     scanf("%d",&convert);
			     if(convert==1)   //convert prefix to infix
			     {
					      fprintf(fileptr,"Prefix Expression: %s", expr); //write input int1o file 
					      prefixinfix(expr,preinfix); //conversion function
					      printf("Infix Expression : %s \n", preinfix);
						  fprintf(fileptr,"Converted from prefix to infix : %s \n\n", preinfix); //store output into file
				 }
				else if(convert==2)   //convert prefix to postfix
			    {
					      fprintf(fileptr,"Prefix Expression: %s", expr);  //store input into file
					      prefixinfix(expr,preinfix);          //convert prefix to infix before convert to postfix
						  infixpostfix(preinfix,prepostfix);
						  printf("Postfix Expression : %s \n", prepostfix);
						  fprintf(fileptr, "Converted from prefix to postfix : %s \n\n", prepostfix);  //store output into file
				}
				else
				{
					printf("Invalid input\n"); //error terminates program
					break;
				}
						 
		  }		
          else if(selection=='b'||selection=='B')   //evaluation
		  {
			     fprintf(fileptr,"Prefix Expression: %s", expr);  //store input into file
			     prefixinfix(expr,preinfix);            //evaluation requires the input to be an infix expression
				 result=eval(preinfix);                 //evaluation function
				 printf("Result: %d\n", result); 
				 fprintf(fileptr,"Result of Prefix expression: %d \n\n",result);  //store result to file
		  }
		  else if(selection=='c'||selection=='C')   // exit
		  {
			     return 0;  //terminates program
		  }
		  else
		  {
			  printf("Invalid input");   //error. terminates program
			  return 0;
		  }
		  
	    }
		else if (detm==2)
		{
			printf("Expression is an infix expression. Do you wish to : \n");
			printf("A-Convert expression\n");
			printf("B-Evaluate Expression\n");
			printf("C-Exit\n");
		    scanf("%c",&selection);
		    if(selection=='a'||selection=='A') //conversion
		    {
			
			   printf("Do you wish to: \n");
			   printf("1-Convert to prefix\n");
			   printf("2-Convert to postfix?\n");
			   scanf("%d", &convert);
			   
			   if(convert==1)   //convert infix to prefix
			   {
				   fprintf(fileptr,"Infix Expression: %s", expr);  //store input into file
				   infixprefix(expr,inprefix);     //conversion function
			       printf("Infix Expression : %s \n", inprefix);
				   fprintf(fileptr,"Converted from infix to prefix : %s \n\n", inprefix);  //store output to file
				   		  
			   }
	           else if(convert==2) 	 //convert infix to postfix
			  {   
				  fprintf(fileptr,"Infix Expression: %s", expr);   //store input into file
				  infixpostfix(expr,inpostfix);     //conversion function
				  printf("Postfix Expression : %s \n", inpostfix);
				  fprintf(fileptr,"Converted from infix to postfix : %s  \n\n", inpostfix);		//store output to file  
			   }
			   else
			   {   
				   printf("Invalid Input\n");  //error. terminates program
				   break;	   
			   }
			   
   
		    }
            else if(selection=='b'||selection=='B') //evaluation
		    {
				 fprintf(fileptr,"Infix Expression: %s", expr);  //stores input into file
				 result=eval(expr);                   //evaluation function
				 printf("Result: %d\n", result);
                 fprintf(fileptr,"Result of Infix expression: %d \n\n",result); //store result in file
		    }
			else if(selection=='c'||selection=='C')   //exit
		    {
			     return 0;     //terminates program
		    }	
			else
			{
				printf("Invalid Input\n");    //error. teminates program
				return 0;
			}
			
		}
		else if (detm==3)
		{
			printf("Expression is an Postfix expression. Do you wish to : \n");
			printf("A-Convert expression\n");
			printf("B-Evaluate Expression\n");
			printf("C-Exit\n");
			
		    scanf("%c",&selection);
		    if(selection=='a'||selection=='A')  //conversion
		    {
			     printf("Do you wish to: \n");
			     printf("1-Convert to infix\n");
			     printf("2-Convert to prefix?\n");
			     scanf("%d",&convert);
			     if(convert==1)  //convert postfix to infix
			     {
				          fprintf(fileptr,"Postfix Expression: %s", expr); //store input into file
					      postfixinfix(expr,postinfix);   //conversion function
					      printf("Infix Expression : %s \n", postinfix);
						  fprintf(fileptr,"Converted from postfix to infix : %s \n\n",postinfix);  //store output to file
				 }
				 else if(convert==2)    //convert postfix to prefix
				 {
					      fprintf(fileptr,"Postfix Expression: %s", expr);  //store input to file
					      postfixinfix(expr,postinfix);       //convert postfix to infix before converting into prefix
						  infixprefix(postinfix,postprefix);
						  printf("Postfix Expression : %s \n", postprefix);
						  fprintf(fileptr,"Converted from postfix to prefix : %s \n\n",postprefix);  //store output in file
			     }
				 else
				 {
					 printf("Invalid input\n");   //error. terminates program
					 break;
				 }
				 
		    }
		    else if (selection=='b'||selection=='B')   //conversion
            {
				 fprintf(fileptr,"Postfix Expression: %s", expr);    //stores input into file
			     postfixinfix(expr,postinfix);      //conversion from postfix to infix as evaluation function can only evaluate infix
				 result=eval(postinfix);
				 printf("Result: %d\n", result);
				 fprintf(fileptr,"Result of Postfix expression: %d \n\n",result); //stores result to file
				 
		     }
			 else if(selection=='c'||selection=='C')   //exit 
		     {
			     return 0;   //return 0 teminates program
		     }
			 else
			 {
				 printf("Invalid input\n");  //error. terminates program
				 return 0;
			 }
			 
		}
		printf("Do you wish to 1-Continue or 2-Exit\n");
		scanf("%d",&loop);
		if(loop==1)
		{
		   x=1;          //loop back while
		}
		else if (loop==2)
		{
           return 0;   //exit.terminates
		}
	 }
	fclose(fileptr);  //close file
    return 0;    //terminates
}

//check for invalid characters
int checkexp(char expr[])
{
    int i;
    for (i=0; i<=strlen(expr); i++)
    { 
        if (!isspace(expr[i]) && !isdigit(expr[i])&&expr[i]!='('&&expr[i]!=')'&& expr[i]!='\0')
        {
            if (expr[i]!='+'&&expr[i]!='-'&&expr[i]!='/'&&expr[i]!='*'&&expr[i]!='^')
            {
                printf("Invalid input characters.\n");   //if not numerical, not spcae, not parentheses, or any operators then invalid input
                return 0;   
            } 
        } 
    } 
   
}

//Determine/check expression
int det(char expr[40])
{
	int i,j, countopr=0, countopd=0,count=0;
	char exprc[40]={'\0'};
	char type[40]={'\0'};

	for(i=0,j=0;i<strlen(expr);i++)
	{
		if(expr[i]!='('&&expr[i]!=')'&&expr[i]!='\0')
		{
			exprc[j]=expr[i];        //get rid of the parentheses to check the operators and operands only
			j++;                       //string without the parentheses will be known as exprc
		}
	}
	for(i=0, j=0;i<strlen(exprc);i++) //loop the exprc string
	{
	    if((exprc[i]==' '))
        {
        	type[j]='s';
        }
		else if(exprc[i]=='+'||exprc[i]=='*'||exprc[i]=='/'||exprc[i]=='^')
		{
			type[j]='m';   //if exprc[i] is operator the letter m will be assigned to type[j]
			j++;
		}
		else if (exprc[i]=='-')   //check negative  numbers
		{
			if(isdigit(exprc[i+1]))    //eg '-1'
			{
			    if(isdigit(exprc[i+2]))   //eg '-11'
			    {
			        if(isdigit(exprc[i+3]))   //eg. '-111'
			        {
			            printf("Error. Operand must be 2 digits at most\n");    //error since this means number is greater than 99 
			            return 0;
			        }
					type[j]='n';   //if operand letter n will be assigned to type[j]
					j++;
					i+=2;  //since the next 2 numbers are already checked
			    }
			    else 
			    {
			    	type[j]='n';     //if operand letter n will be assigned to type[j]
					j++;
					i+=1;   //since the next number is already checked
			    }	
			}
		    else if (isspace(exprc[i+1]))   //eg '- ' 
		    {
			    type[j]='m';    //meaning the - is not assigned to a negative number. it is an operator. letter m is assigned
			    j++;   
		    }
		}
        else if(isdigit(exprc[i]))  // eg '1'  check double digits  
        {
            if(isdigit(exprc[i+1]))   //eg '11'
            {
                if(isdigit(exprc[i+2]))  //eg '111'
                {
                    printf("Error. Operand must be 2 digits at most\n");   //error sine the num
                }
        	    type[j]='n';    //if valid operand letter n will be assigned to type[j]
        	    j++;
        	    i++;   //since next number is already checked
            }
            else
            {
               type[j]='n';     //if valid operand letter n will be assigned to type[j]
        	   j++;
            }
        }
        
	}
	for(i=0,j=0;i<strlen(exprc);i++)   //loop the exprc again to check for the spacing
	{
		if(exprc[i]==' ')
		{
			count++;
		}
	}
	if(count<(strlen(type)-1))    //if error in spacing, eg. 1+1 (strlen of 3 ) must have 2 spcaing
	{
		printf("Error. There must be space between the operator and operand");   //error. terminates
		return 0;
	}
	for(i=0;i<strlen(type);i++)   //check for number of operators and operand
	{
	    if(type[i]=='n')
	    {
	        countopd++;    //operand ++
	    }
	    else if(type[i]=='m')
	    {
	        countopr++;   //operator ++
	    }
	}
	if(countopd!=(countopr+1))
	{
		printf("Error in expression\n");     //usually the operator will be 1 less than the operand
		return 0;
	}
	if(countopd>6||countopr>5||countopd==0||countopr==0) //make sure the operand is not more than 6 and operator not more than 5
	{                                                     //operand and operator must also not be 0
	    printf("Error. Operand must be not more than 6 and operator mut be not more than 5\n");
	    return 0;
	}
	 
	 if(type[0]=='n')
	 {
		if(type[1]=='m')
		{
			if(type[2]=='n')   //this means eg.  "1 + 1"  "operand operator operand"
			 {
				 
				return (2); //infix expression
			 }
			 
		}
		else if (type[1]=='n')  //this means eg. "1 11" "operand operand"
		{
		    return (3);      //postfix expression
		}
    
     }
     else if(type[0]=='m')    //this means operator is in front
     {
        if(type[1]=='m')     //"operator operator"
        {
        	
			return (1);     //prefix expression
        }
        return(1); //prefix expression
	 } 
	 else
	 {
		 return 0;   //none of the above means error. return 0 terminates
	 }
	     	
}

//check balance parentheses
int parentheses(char expr[], int type)
{
	int countc=0, counto=0,i;
	
	  for(i=0;i<strlen(expr);i++)    //loop the expression and check the number of opening and closing parentheses
	  {
		if(expr[i]==')')
		{
			countc++;
		}
		else if(expr[i]=='(')
		{
			counto++;
		}
	  }
	  if(type==2)   //if it is an infix expression
	  {
	    if(counto!=countc)    //number of opening and closing parentheses  not the same
	    {
			if(countc<counto)
			{
				printf("Imbalanced parentheses. Missing a closing parentheses. Restart program.\n");  //error return 0 will terminate
			}
			else if (counto<countc)
			{
				printf("Imbalanced parentheses. Missing an opening parentheses. Restart Program\n");
			}
		    return 0;
		 
	    }
	    else
	    {
		  return (1);   //else if opening and closing parentheses are equal, then return 1
		}	
	  }
	  else if (type==1||type==3)   //if expression entered is prefix or postfix
	  {
		  if(counto!=0||countc!=0)    //should not have any parenthsese
		  {
			  printf("Error. Prefix or Postfix expression must not have parentheses\n");
			  return 0;        //if there is parentheses in the expression return 0, will terminate program
		  }
		  else
		  {
			  return (1);   //if no parentheses return 1
		  }
		  
	  }
}

 //infix to postfix
void infixpostfix(char expr[], char post[40])   //post will be the output expression
{
	 Nodeptr stacktop=NULL;    //pointer to top of stack
	 int i,j;
	 char a='(';              
	 push(a, &stacktop);               //push '(' onto the top of stack               
	 strcat(expr,")");                 //add ")" to the end of the expression
	 
	 for(i=0,j=0;i<strlen(expr);i++)   //loop the expression
	 { 
		 if(isdigit(expr[i]))
		 {
			 if(isdigit(expr[i+1]))   //check for double digits eg. '1' or '11'
			 {
				 
					 post[j]=expr[i];
					 post[j+1]=expr[i+1];        //assign post with eg. '11 ' eg. 'operandoperandspace'
					 post[j+2]=' ';
					 j+=3;   // 3 element already filled
				     i+=1;	 //next element already checked
			 }
			 else     //if single digit eg. '1'
			 {
				 post[j]=expr[i];
				 post[j+1]=' ';              //assign post with eg. '1 ' eg. 'operandspace'
				 j+=2;	        //2 elements already filled
			 }
		 }
		 else if(expr[i]=='-')    //check for negative numbers
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isdigit(expr[i+2]))    //check for negative double digits eg. '-11'
				 {
					 
						post[j]=expr[i];
					    post[j+1]=expr[i+1];     //assign post with eg. '-11 ' eg. 'operatoroperandoperandspace'
					    post[j+2]=expr[i+2];
					    post[j+3]=' ';
					    j+=4;                   //4 elements already filled
				        i+=2; 	      //next 2 elements already checked
				 }
				 else        //if negative single digit
				 {
					 post[j]=expr[i];
					 post[j+1]=expr[i+1];       //assign post with eg. '-1 ' eg. 'operatoroperandspace'
					 post[j+2]=' ';
					 j+=3;            //3 elements already filled
					 i+=1;            //next element already checked
				 }
			 }
			 else if (expr[i+1]==' ')   //if the - is not assigned to any digits it is an operator
			 {
				 while(stacktop!=NULL&&precedence(stacktop->cell)>=precedence(expr[i])&&stacktop->cell!='(')
			     {       //while  the stacktop is not an opening parentheses 
					      //while the stacktop operator precedence is greater than the current operator precedence & stack is not empty
					 post[j]=stacktop->cell;   
				     post[j+1]=' ';              //assign post with the oprator at the s8 8tacktop and a space eg. '^ ' 'operator space'
				     pop(&stacktop);        //pop the operator at the stacktop
				     j+=2;               //2 elements already filled
			     }
				 push('-', &stacktop);   //push the current operator into the stack
			 } 
			 
		 }
		 else if(expr[i]=='+'||expr[i]=='/'||expr[i]=='*'||expr[i]=='^') //if operator is encountered
		 {
			 while(stacktop!=NULL&&precedence(stacktop->cell)>=precedence(expr[i])&&stacktop->cell!='(')
			 {          //while  the stacktop is not an opening parentheses 
					      //while the stacktop operator precedence is greater than the current operator precedence & stack is not empty
				 post[j]=stacktop->cell;    
				 post[j+1]=' ';                //assign post with the operator at the stacktop and a space eg. '^ ' 'operator space'
				 pop(&stacktop);               //pop the operator at the stacktop
				 j+=2;                       //2 elements already filled
			 }
			 push(expr[i],&stacktop);         //push current operator to stack

		 }
		 else if(expr[i]=='(')    //if (  is encountered
		 {
			 push(expr[i], &stacktop);   //push it into the stack
		 }
		 else if(expr[i]==')')         //if ) is encountered
		 {
			 while(stacktop->cell!='(')       //pop all operators in stack to the postfix exp untill ( is encountered in the operator stack
			 {
				 post[j]=stacktop->cell;      //assign post with the operator at the stacktop and a space eg. '^ ' 'operator space'
				 post[j+1]=' ';              
				 j+=2;                       //2 elements already filled
				 pop(&stacktop);
			 }
			 pop(&stacktop);  //when ( is encountered pop it from the stack
		 }
		 
	 }  //end for loop
	
}

//infix to prefix
void infixprefix(char expr[], char post[40])    //post will be the output expression
{
	 Nodeptr stacktop=NULL;       //pointer to top of stack
	 int i,j;
	 char a=')';
	 push(a, &stacktop);         //push ')' onto the top of stack                                          
	 strrev(expr);               //reverse the expression
	 strcat(expr,"(");           //add "(" to the end of the expression
	 
	 for(i=0,j=0;i<strlen(expr);i++)   //loop the expression
	 { 
		 if(isdigit(expr[i]))
		 {
			 if(isdigit(expr[i+1]))   //check for double digits eg. '1' or '11'
			 {	 
					 post[j]=expr[i];
					 post[j+1]=expr[i+1];
					 post[j+2]=' ';              //assign post with eg. '11 ' eg. 'operandoperandspace'
					 j+=3;                   // 3 element already filled
				     i+=1;	               //next element already checked
			 }
			 else  //if single digit eg. '1'
			 {
				 post[j]=expr[i];
				 post[j+1]=' ';              //assign post with eg. '1 ' eg. 'operandspace'
				 j+=2;                     ////2 elements already filled
			 }
		 }
		 else if(expr[i]=='-')      //check for negative numbers
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isdigit(expr[i+2]))        //check for negative double digits eg. '-11'
				 { 
		            	post[j]=expr[i];
					    post[j+1]=expr[i+1];
					    post[j+2]=expr[i+2];       //assign post with eg. '-11 ' eg. 'operatoroperandoperand'
					    post[j+3]=' ';
					    j+=4;                   //4 elements already filled
				        i+=2; 	               //next 2 elements already checked
				 }
				 else                        //if negative single digit
				 {
					 post[j]=expr[i];
					 post[j+1]=expr[i+1];
					 post[j+2]=' ';              //assign post with eg. '-1 ' eg. 'operatoroperandspace'
					 j+=3;                       //3 elements already filled
					 i+=1;                       //next element already checked
				 }
			 }
			 else if (expr[i+1]==' ')             //if the - is not assigned to any digits it is an operator
			 {
				 while(stacktop!=NULL&&precedence(stacktop->cell)>=precedence(expr[i])&&stacktop->cell!=')')
			     {       //while  the stacktop is not an closing parentheses 
					      //while the stacktop operator precedence is greater than the current operator precedence & stack is not empty
					 post[j]=stacktop->cell;
				     post[j+1]=' ';            //assign post with the oprator at the stacktop and a space eg. '^ ' 'operator space'
				     pop(&stacktop);            //pop the operator at the stacktop
				     j+=2;                       //2 elements already filled
				     //i++;                      //next element already checked
			     }
				 push('-', &stacktop);     //push the current operator into the stack
			 }
			 
		 }
		 else if(expr[i]=='+'||expr[i]=='/'||expr[i]=='*'||expr[i]=='^')  //if operator is encountered
		 {
			 while(stacktop!=NULL&&precedence(stacktop->cell)>=precedence(expr[i])&&stacktop->cell!=')')
			 {        //while  the stacktop is not an closing parentheses 
					//while the stacktop operator precedence is greater than the current operator precedence & stack is not empty	 
				 post[j]=stacktop->cell;
				 post[j+1]=' ';                  //assign post with the operator at the stacktop and a space eg. '^ ' 'operator space'
				 pop(&stacktop);                //pop the operator at the stacktop
				 j+=2;                          //2 elements already filled
			 }
			 push(expr[i],&stacktop);            //push current operator to stack

		 }
		 else if(expr[i]==')')     //if )  is encountered
		 {
			 push(expr[i], &stacktop);     //push it into the stack
		 }
		 else if(expr[i]=='(')         //if ( is encountered
		 {
			 while(stacktop->cell!=')')      //pop all operators in stack to the postfix exp untill ) is encountered in the operator stack
			 {
				 post[j]=stacktop->cell;
				 post[j+1]=' ';                //assign post with the operator at the stacktop and a space eg. '^ ' 'operator space'
				 j+=2;                         //2 elements already filled
				 pop(&stacktop);
			 }
			 pop(&stacktop);
		 }
	 }
	 strrev(post);	
}
     
//prefix to infix
void prefixinfix(char expr[], char post[40])
{
	 Node2ptr stacktop=NULL;   //stacktop pointer
	 char str[40];
	 char str1[40];
	 char str2[40];
	 char str3[40];
	 char s1[40]={'\0'};
	 char s2[40]={'\0'};
	 int i, count=0;  
	 strrev(expr);              //reverse the expression               

	 for(i=0;i<strlen(expr);i++)   //loop the reversed expression
	 {
		 if(isdigit(expr[i]))
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isspace(expr[i+2]))   //check for double digits and a space
				 {
					 str[0]=expr[i];
					 str[1]='\0';
					 str1[0]=expr[i+1];
					 str1[1]='\0';            //combined each element to a string eg. '11 '
					 str2[0]=expr[i+2];
					 str2[1]='\0';
					 strcat(str,str1);
					 strcat(str,str2);
					 push2(str,&stacktop);   //push the string to the stack
					 count++;			  //update the number of operands		 
				     i+=2;               //next 2 elements already checked
				 }
			 }
			 else if(isspace(expr[i+1]))   //if single digit and a space
			 {
				 str[0]=expr[i];
				 str[1]='\0';
				 str1[0]=expr[i+1];       //combine each element to a string eg. '1 '
				 str1[1]='\0';
				 strcat(str,str1);
				 push2(str,&stacktop);    //push the string to the stack
				 count++;                 //update operand counter
				 i+=1;                     //next element already checked
			 }
		 }
		 else if(expr[i]=='-')        //check for negative numbers
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isdigit(expr[i+2]))
				 {
					 if(isspace(expr[i+3]))   //if negative double digits and a space
					 {
						 str[0]=expr[i];
					     str[1]='\0';
					     str1[0]=expr[i+1];
					     str1[1]='\0';
					     str2[0]=expr[i+2];    //combine each element to form a string eg. '-11 '
					     str2[1]='\0';
						 str3[0]=expr[i+3];
					     str3[1]='\0';
					     strcat(str,str1);
					     strcat(str2,str3);
						 strcat(str,str2);
					     push2(str,&stacktop);    //push the string to the stack
						 count++;     //update operand counter
				         i+=3;        //next 3 elements already checked
					 }
				 }
				 else if(isspace(expr[i+2]))   //if negative single digit and a space
				 {
					 str[0]=expr[i];
				     str[1]='\0';
				     str1[0]=expr[i+1];      //combine each element to form a string eg. '-1 '
				     str1[1]='\0';
					 str2[0]=expr[i+2];
					 str2[1]='\0';
					 strcat(str,str1);
					 strcat(str,str2);
					 push2(str,&stacktop);    //push the string to the stack
					 count++;      //update operand counter
					 i+=2;         //next 2 element s already checked
				 }
			 }
			 else if (isspace(expr[i+1]))   //if the - is not assigned to any number, it is an operator
			 {
				 if(count>=2)    //if there is more than or 2 operands in the stack
			    {
				    strcpy(s2,stacktop->cell);     //pop the stacktop twice
				    pop2(&stacktop);
				    strcpy(s1,stacktop->cell);
				    pop2(&stacktop);
				    str[0]=expr[i];
				    str[1]=' ';
				    str[2]='\0';
				    str1[0]='(';
				    str1[1]=' ';         //combine the 2 operand from the stacktop with the operator and parentheses eg.'( 2 + 2 ) '
				    str1[2]='\0';
				    str2[0]=')';
				    str2[1]=' ';
				    str2[2]='\0';
				    strcat(str1,s2);
				    strcat(str,s1);
				    strcat(str1,str);
				    strcat(str1,str2);
				    push2(str1,&stacktop);	 //push the entire string to the stack 
				    i++;                     //next element already checked
				    count--;                 //decrease the number of operands by 1
				}
			 }
			else
			{
				if(count>=2)    //if there is more than or 2 operands in the stack
			    {
				    strcpy(s2,stacktop->cell);     //pop the stacktop twice
				    pop2(&stacktop);
				    strcpy(s1,stacktop->cell);
				    pop2(&stacktop);
				    str[0]=expr[i];
				    str[1]=' ';
				    str[2]='\0';
				    str1[0]='(';
				    str1[1]=' ';         //combine the 2 operand from the stacktop with the operator and parentheses eg.'( 2 + 2 ) '
				    str1[2]='\0';
				    str2[0]=')';
				    str2[1]=' ';
				    str2[2]='\0';
				    strcat(str1,s2);
				    strcat(str,s1);
				    strcat(str1,str);
				    strcat(str1,str2);
				    push2(str1,&stacktop);	 //push the entire string to the stack 
				    i++;                     //next element already checked
				    count--;                 //decrease the number of operands by 1
				}

			}
				 
			 
			 
		 }
		 else if (expr[i]=='+'||expr[i]=='/'||expr[i]=='*'||expr[i]=='^') //if it is an operator
		 {
			 if(count>=2)   // //if there is more than or 2 operands in the stack
			 {
				 strcpy(s2,stacktop->cell);
				 pop2(&stacktop);
				 strcpy(s1,stacktop->cell);   
				 pop2(&stacktop);            //pop the stacktop twice
				 str[0]=expr[i];
				 str[1]=' ';
				 str[2]='\0';
				 str1[0]='(';
				 str1[1]=' ';          //combine the 2 operand from the stacktop with the operator and parentheses eg.'( 2 + 2 ) '
				 str1[2]='\0';
				 str2[0]=')';
				 str2[1]=' ';
				 str2[2]='\0';
				 strcat(str1,s2);
				 strcat(str,s1);
				 strcat(str1,str);
				 strcat(str1,str2);
				 push2(str1,&stacktop);	 //push the entire string to the stack 
				 count--;                //decrease the number of operands by 1
			 }

		 }	 
	}
	while(stacktop!=NULL)   //while the stack is not empty
	{
		strcat(post,stacktop->cell);   //add the operand at the stacktop to the output expression
		pop2(&stacktop);                //pop the operand
	}
}

//postfix to infix
void postfixinfix(char expr[], char post[40])
{
	 Node2ptr stacktop=NULL;  //stacktop pointer
	 char str[40];
	 char str1[40];
	 char str2[40];
	 char str3[40];
	 char s1[40]={'\0'};
	 char s2[40]={'\0'};
	 int i, count=0;                              

	 for(i=0;i<strlen(expr);i++)   //loop the  expression
	 {
		 if(isdigit(expr[i]))
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isspace(expr[i+2]))   //check for double digits and a space
				 {
					 str[0]=expr[i];
					 str[1]='\0';
					 str1[0]=expr[i+1];
					 str1[1]='\0';
					 str2[0]=expr[i+2];
					 str2[1]='\0';                //combined each element to a string eg. '11 '
					 strcat(str,str1);
					 strcat(str,str2);
					 push2(str,&stacktop);         //push the string to the stack
					 count++;					 //update the number of operands
				     i+=2;                      //next 2 elements already checked
				 }
			 }
			 else if(isspace(expr[i+1]))       //if single digit and a space
			 {
				 str[0]=expr[i];
				 str[1]='\0';
				 str1[0]=expr[i+1];
				 str1[1]='\0';                          //combine each element to a string eg. '1 '
				 strcat(str,str1);
				 push2(str,&stacktop);        //push the string to the stack
				 count++;                      //update operand counter
				 i+=1;                         //next element already checked
			 }
		 }
		 else if(expr[i]=='-')        //check for negative numbers
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isdigit(expr[i+2]))
				 {
					 if(isspace(expr[i+3]))        //if negative double digits and a space
					 {
						 str[0]=expr[i];
					     str[1]='\0';
					     str1[0]=expr[i+1];
					     str1[1]='\0';
					     str2[0]=expr[i+2];         //combine each element to form a string eg. '-11 '
					     str2[1]='\0';
						 str3[0]=expr[i+3];
					     str3[1]='\0';
					     strcat(str,str1);
					     strcat(str2,str3);
						 strcat(str,str2);
					     push2(str,&stacktop);        //push the string to the stack
						 count++;                   //update operand counter
				         i+=3;                        //next 3 elements already checked
					 }
				 }
				 else if(isspace(expr[i+2]))        //if negative single digit and a space
				 {
					 str[0]=expr[i];
				     str[1]='\0';
				     str1[0]=expr[i+1];
				     str1[1]='\0';
					 str2[0]=expr[i+2];                   //combine each element to form a string eg. '-1 '
					 str2[1]='\0';
					 strcat(str,str1);
					 strcat(str,str2);
					 push2(str,&stacktop);             //push the string to the stack
					 count++;                         //update operand counter
					 i+=2;                            //next 2 element s already checked
				 }
			 }
			 else if (isspace(expr[i+1]))           //if the - is not assigned to any number, it is an operator
			 {
				 if(count>=2)             //if there is more than or equal 2 operands in the stack
			    {
				    strcpy(s2,stacktop->cell);
				    pop2(&stacktop);
				    strcpy(s1,stacktop->cell);     //pop the stacktop twice
				    pop2(&stacktop);
				    str[0]=expr[i];
				    str[1]=' ';
				    str[2]='\0';
				    str1[0]='(';
				    str1[1]=' ';
				    str1[2]='\0';      //combine the 2 operand from the stacktop with the operator and parentheses eg.'( 2 + 2 ) '
				    str2[0]=')';
				    str2[1]=' ';
				    str2[2]='\0';
				    strcat(str1,s2);
				    strcat(str,s1);
				    strcat(str1,str);
				    strcat(str1,str2);
				    push2(str1,&stacktop);	 //push the entire string to the stack 
				    i++;                      //next element already checked
				    count--;                //decrease the number of operands by 1
				}
				 
			 }
			 
		 }
		 else if (expr[i]=='+'||expr[i]=='/'||expr[i]=='*'||expr[i]=='^')  //if it is an operator
		 {
			 if(count>=2)      //if there is more than or 2 operands in the stack
			 {
				 strcpy(s2,stacktop->cell);
				 pop2(&stacktop);             //pop the stacktop twice
				 strcpy(s1,stacktop->cell);
				 pop2(&stacktop);
				 str[0]=expr[i];
				 str[1]=' ';
				 str[2]='\0';
				 str1[0]='(';        //combine the 2 operand from the stacktop with the operator and parentheses eg.'( 2 + 2 ) '
				 str1[1]=' ';
				 str1[2]='\0';
				 str2[0]=')';
				 str2[1]=' ';
				 str2[2]='\0';
				 strcat(str1,s2);
				 strcat(str,s1);
				 strcat(str1,str);
				 strcat(str1,str2);
				 push2(str1,&stacktop);	//push the entire string to the stack 
				 count--;               //decrease the number of operands by 1
			 }

		 }	 
	}
	while(stacktop!=NULL)   //while the stack is not empty
	{
		strcpy(post,stacktop->cell);    //the operand at the stacktop would be the output expression
		pop2(&stacktop);              //pop the operand
	}
}

//evaluation
int eval(char expr[])
{
	 Nodeptr stacktop=NULL;  //operator stack pointer
	 Node3ptr stacktopv=NULL;  //operand stack pointer
	 char str[40];
	 char str1[40];
	 char str2[40];
	 int i, count=0,x,n1,n2;                              
	 
	 for(i=0;i<strlen(expr);i++)  //loop expression
	 {
		 if(isdigit(expr[i]))
		 {
			 if(isdigit(expr[i+1]))   //check for double digit
			 {
					 str[0]=expr[i];
					 str[1]='\0';
					 str1[0]=expr[i+1];    
					 str1[1]='\0';               //combine the 2 digits into string 
					 strcat(str,str1);
					 sscanf(str, "%d", &x);     //convert it to integer
					 pushv(x,&stacktopv);            //push the integer to the operand stack
					 i++;            //next element already checked
					 count++;	    //update operand counter
			 }
			 else if(isspace(expr[i+1]))   //if single digit
			 {
				 str[0]=expr[i];
				 str[1]='\0';
				 sscanf(str, "%d", &x);   //convert the digit to integer 
				 pushv(x,&stacktopv);    //push the integer to the operand stack
				 count++;		         //update operand counter
			 }
		 }
		 else if(expr[i]=='-')   //check for negative numbers
		 {
			 if(isdigit(expr[i+1]))
			 {
				 if(isdigit(expr[i+2]))
				 {
					 if(isspace(expr[i+3]))   //if negative double digit eg. '-11 '
					 {
						 str[0]=expr[i];
					     str[1]='\0';
					     str1[0]=expr[i+1];
					     str1[1]='\0';
					     str2[0]=expr[i+2];
					     str2[1]='\0';          //combine the digits into string
					    strcat(str,str1);
						strcat(str,str2);
						sscanf(str, "%d", &x);    //convert to integer
					    pushv(x,&stacktopv);      //push the integer to the operand stack
				        i+=3;     //next 3 elements already checked
						count++;  //update operand counter
					 }
				 }
				 else if(isspace(expr[i+2]))  //if negative single digit eg. '-1 '
				 {
					 str[0]=expr[i];
				     str[1]='\0';
				     str1[0]=expr[i+1];
				     str1[1]='\0';             //combine the digits into string
					 strcat(str,str1);
					 sscanf(str, "%d", &x);   //convert to integers
					 pushv(x,&stacktopv);      //push the integer to the operand stack
					 i+=2;    //next 2 elemetnsalready checked
					 count++;    //update operand counter
				 }
			 }
			 else if(isspace(expr[i+1]))  //if its an operator
			 {
				     while(stacktop!=NULL&&precedence(stacktop->cell)>=precedence(expr[i])&&stacktop->cell!='('&&count>=2)
			        {   //while the stack is not empty, the precedence of the operator stack top operator is higher than the current operator
					     // and the stacktop operator is not an opening parentheses  and the operand count is equal or greater than 2
					     n1=stacktopv->operand;
				         popv(&stacktopv);
				         n2=stacktopv->operand;   //pop the opreand stack twice
				         popv(&stacktopv);
					     if(stacktop->cell=='+')
					     {
						    x=n1+n2;
						    pushv(x,&stacktopv);      
							count--;
					     }
						 else if (stacktop->cell=='*')
						 {
							 x=n1*n2;
						     pushv(x,&stacktopv);
							 count--;
						 }
						 else if (stacktop->cell=='/')            //perform the operation on the two operands with the operator stacktop operator
						 {                                        //push the answer to the operand stack       
							 x=n2/n1;                            // decrease the operand counter by 1
						     pushv(x,&stacktopv);
							 count--;
						 }
						 else if (stacktop->cell=='^')
						 {
							 x=n1^n2;
						     pushv(x,&stacktopv);
							 count--;
						 }
						 pop(&stacktop); //pop the operator stacktop operator
						 
					}
			     push('-',&stacktop);  //push the operator to the operator stack
			     
			 }
			 
		 }
		 else if(expr[i]=='+'||expr[i]=='/'||expr[i]=='*'||expr[i]=='^')  //if its an operator
		 {
			     while(stacktop!=NULL&&precedence(stacktop->cell)>=precedence(expr[i])&&stacktop->cell!='('&&count>=2)
			    {
					    //while the stack is not empty, the precedence of the operator stack top operator is higher than the current operator
					     // and the stacktop operator is not an opening parentheses  and the operand count is equal or greater than 2
					     n1=stacktopv->operand;
				         popv(&stacktopv);
				         n2=stacktopv->operand;         //pop the opreand stack twice
				         popv(&stacktopv);
					     if(stacktop->cell=='+')
					     {
						    x=n1+n2;
						    pushv(x,&stacktopv);
							count--;
					     }
						 if(stacktop->cell=='-')
					     {
						    x=n2-n1;
						    pushv(x,&stacktopv);
							count--;
					     }
						 else if (stacktop->cell=='*')                   //perform the operation on the two operands with the operator stacktop operator
						 {                                               //push the answer to the operand stack  
							 x=n1*n2;
						     pushv(x,&stacktopv);                        // decrease the operand counter by 1
							 count--;
						 }
						 else if (stacktop->cell=='/')
						 {
							 x=n2/n1;
						     pushv(x,&stacktopv);
							 count--;
						 }
						 else if (stacktop->cell=='^')
						 {
							 x=n1^n2;
						     pushv(x,&stacktopv);
							 count--;
						 }
						 pop(&stacktop);  //pop the operator stacktop operator
						 
			    }
				push(expr[i],&stacktop);	 //push the operator to the operator stack
		 }
		 else if (expr[i]=='(')    //if ( is encountered 
		 {
             push(expr[i],&stacktop);	 // push ( to the operator stack
		 }
		 else if(expr[i]==')')         //if ) is encounterd
		 {
			 while(stacktop->cell!='(')   
			 {
				 n1=stacktopv->operand;
				 popv(&stacktopv);          //pop the operand stack twice
			     n2=stacktopv->operand;
		         popv(&stacktopv);
			     if(stacktop->cell=='+')
			     {
 		     	     x=n1+n2;
					 pushv(x,&stacktopv);
				     count--;
				 }
				 if(stacktop->cell=='-')
			     {
 		     	     x=n2-n1;
					 pushv(x,&stacktopv);
				     count--;
				 }
				 else if (stacktop->cell=='*')           //perform the operation on the two operands with the operator stacktop operator
				 {                                       //push the answer to the operand stack  
					 x=n1*n2;                            // decrease the operand counter by 1 
					 pushv(x,&stacktopv);                 //repeast until ( is encountered in the operator stack
					 count--;
				 }
				 else if (stacktop->cell=='/')
				{
					 x=n2/n1;
					 pushv(x,&stacktopv);
					 count--;
				 }
				 else if (stacktop->cell=='^')
				{
				     x=n1^n2;
					 pushv(x,&stacktopv);
					 count--;
			     }
				 pop(&stacktop);
				 
			 }
			 pop(&stacktop);   //pop the operator stacktop when (  is encountered
		 } 
	}
	while(stacktop!=NULL)         //while the stack is not empty
	{
	     n1=stacktopv->operand;
		 popv(&stacktopv);                 //pop the operand stack twice
		 n2=stacktopv->operand;
		 popv(&stacktopv);
		 if(stacktop->cell=='+')            
		 {
 		     x=n1+n2;
			 pushv(x,&stacktopv);
			 count--;
		 }
	     if(stacktop->cell=='-')
		 {
 		     x=n2-n1;
			 pushv(x,&stacktopv);
			 count--;
		 }
		 else if (stacktop->cell=='*')
		 {                                           //perform the operation on the two operands with the operator stacktop operator
			 x=n1*n2;                                //push the answer to the operand stack  
			 pushv(x,&stacktopv);                    // decrease the operand counter by 1 
			 count--;                                //there should be one operand left which is the answer                
		 }
		 else if (stacktop->cell=='/')
		 {
			 x=n2/n1;
			 pushv(x,&stacktopv);
			 count--;
		 }
		 else if (stacktop->cell=='^')
		 {
			 x=n1^n2;
			 pushv(x,&stacktopv);
			 count--;
		 }
		 pop(&stacktop);
	}
	 
	 return stacktopv->operand;   //return the answer 
}

//push to stack
void push(char new, Nodeptr* sptr)      //sptr is the stacktop
{
   Nodeptr newptr=NULL;            
   newptr=malloc(sizeof(Node));
   newptr->cell=new;             //the character received is assigned to the newptr
   
   if(*sptr==NULL)
   {
     newptr->next = NULL;
	 *sptr=newptr;
   }
   else
   {
	  newptr->next=*sptr;
	  *sptr=newptr;
   }

}
//push to stack
void push2(char new[], Node2ptr* sptr)  //sptr points to the stacktop
{
   Node2ptr newptr=NULL;
   newptr=malloc(sizeof(Node2));
   strcpy(newptr->cell,new);    //the string received is assigned to the newptr
   
   if(*sptr==NULL)
   {
     newptr->next = NULL;
	 *sptr=newptr;
   }
   else
   {
	  newptr->next=*sptr;
	  *sptr=newptr;
   }

}
//push to stack (operand stack)
void pushv(int new, Node3ptr* sptr)   //sptr points to the stacktop
{
   Node3ptr newptr=NULL;
   newptr=malloc(sizeof(Node3));
   newptr->operand=new;      //integer received is assigned to the newptr

   if(*sptr==NULL)
   {
     newptr->next = NULL;
	 *sptr=newptr;
   }
   else
   {
	  newptr->next=*sptr;
	  *sptr=newptr;
   }

}

//pop top of stack
void pop(Nodeptr* sptr)  //sptr points to stack top
{
	Nodeptr tmpptr=NULL;   //temporary pointer
    tmpptr=malloc(sizeof(Node));
    tmpptr=*sptr;
    *sptr=(*sptr)->next;
    free(tmpptr);   // free the tmppter

}
//pop top of stack
void pop2(Node2ptr* sptr)  //sptr points to stacktop
{
	Node2ptr tmpptr=NULL;  //temporary pointer
    tmpptr=malloc(sizeof(Node2));
    tmpptr=*sptr;
    *sptr=(*sptr)->next;
    free(tmpptr);        //free the temporary pointer
}
//pop top of stack (operand stack)
void popv(Node3ptr* sptr)  //sptr points to stacktop
{
	Node3ptr tmpptr=NULL;       //temporary pointer
    tmpptr=malloc(sizeof(Node3));
    tmpptr=*sptr;
    *sptr=(*sptr)->next;
    free(tmpptr);  //free the temporary pointer
}

//precedence
int precedence(char operand)
{

	if(operand == '^')      // highest precedence
	{
		return(3);
	}
	else if(operand == '*' || operand == '/')
	{
		return(2);
	}
	else if(operand == '+' || operand == '-')          //lowest precedence 
	{
		return(1);
	}
	else
	{
		return(0);
	}
}



