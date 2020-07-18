#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

/*This function is used to generate new questions 
if the user wants to try any other question of the 
same difficulty level*/
int generateNewQues(int n, int sudoku[n][n])           
{
	int i,r,c;
	int flag = (6*n*n)/10;
	for(i=0;i<flag;i++)
	{
		r = rand() % n;
		c = rand() % n;
		sudoku[r][c] = 0;
	}
	return sudoku[n][n];
}

/*This function is used to check whether 
the soltuion entered by the user is correct or not*/
int areEqual(int n, int larr[n][n], int rarr[n][n])
{
	int i,j,flag = 1;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(larr[i][j] != rarr[i][j])
			flag = 0;
		}
	}
	if(flag == 0){
		return false;	
	}
	return true;
}

 /*This function checks if the row,columnn 
which is to be solved is an empty cell or not*/
int checkEmpty(int row, int col, int n, int sudoku[n][n])       
{
    if(sudoku[row][col] != 0){
        return false;
    }
    return true;
}

/* This function checks if the sudoku is 
solved by the user or not. If its not it 
returns false. */
int checkZero(int n, int sudoku[n][n])
{
	int i,j,flag = 1;
	for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(sudoku[i][j]==0)
				flag = 0;
			}
		}
	if(flag == 0){
		return false;
	}
	return true;
}

/*This function checks whether the 
number can be entered in the row or not*/
int checkRow(int row, int col, int n, int sudoku[n][n], int num)    
{
    for(int i=0;i<n;i++)
    {
        if(sudoku[row][i]==num)
        return false;
    }
    return true;
}

/*This function checks whether the 
number can be entered in the column or not*/
int checkColumn(int row,int col, int n, int sudoku[n][n],int num)    
{
    for(int i=0;i<n;i++)
    {
        if(sudoku[i][col]==num)
        return false;
    }
    return true;
}

/*This function checks whether the 
number can be entered in the subgrid or not*/
int checkSquare(int row, int col, int n, int sudoku[n][n],int num)         
{
	int flag = (int)sqrt(n);
    row = row - row%flag;
    col = col - col%flag;

    for(int i=row;i<row+flag;i++)
    {
        for(int j=col;j<col+flag;j++)
        {
            if(sudoku[i][j]==num)
            return false;
        }
    }
    return true;
}

/*This function solves the sudoku using rescursion,
the main algorithm involved is the backtracking algorithm
which solves the cell one by one and backtracks to the previous 
cell and changes its value if it can't be solved further.
This continues until the whole sudoku is solved.*/
int solve(int n, int sudoku[n][n], int row, int col)
{
    if(row == n){
        return true;
    }
    if(col == n){
        return solve(n,sudoku,row+1,0);
    }
    if(checkEmpty(row,col,n,sudoku)==false){
        return solve(n,sudoku,row,col+1);
    }
    for(int i=1;i<=n;i++)
    {
        if(checkColumn(row,col,n,sudoku,i) && checkRow(row,col,n,sudoku,i) && checkSquare(row,col,n,sudoku,i) == true){
            sudoku[row][col] = i;
            bool success = solve(n,sudoku,row,col+1);
            if(success == true) return true;        //This is the main step 	
            sudoku[row][col] = 0;						//of the algorithm
        }
    }
    return false;
}

/*This function is used to print the unsolved 
puzzle to the user*/
void printSudokuQues(int n, int sudoku[n][n])     
{
    int i,j;
    for(i=0;i<n;i++)                        
    {
        for(j=0;j<n;j++)
        {
            printf("%2d ",sudoku[i][j]);
        }
        printf("\n");
    }
}

/*This function is used to print the solution or
the solved puzzle to the user*/
void printSudokuSolved(int n, int sudoku[n][n])
{
    int i,j;
    for(i=0;i<n;i++)                        
    {
        for(j=0;j<n;j++)
        {
            printf("%2d ",sudoku[i][j]);
        }
        printf("\n");
    }
}

/*This function is used to get the input values 
which the user will enter while solving the puzzle*/
int inputByUser(int n, int sudoku[n][n])
{
	int r;
    int c,i,j;
    int inp;
	char ch;
	char a = 'n';
	printSudokuQues(n, sudoku);
	printf("Generate any other question in the same difficulty level? (y/n)");
	scanf("%s",&ch);
	if(ch == 'y')
	{
		return 2;
	} 
	label: printf("Enter the cell(row,column) you want to solve:\n");
	scanf("%d",&r);
    scanf("%d",&c);
	printf("Enter the value from 1 to %d: ",n);
	scanf("%d",&inp);
	sudoku[r-1][c-1] = inp;
	while(a != 'y')
	{
		printSudokuQues(n, sudoku);
		printf("Want to quit? (y/n)\n");
		scanf("%s",&a);
		if(a=='y') break;
		label1: printf("Enter the cell(row,column) you want to solve:\n");
		scanf("%d",&r);
        scanf("%d",&c);
		printf("Enter the value from 1 to %d: ",n);
		scanf("%d",&inp);
		sudoku[r-1][c-1] = inp;
		if(checkZero(n,sudoku)){
			return true;
		}
	}
	return 0;
}


int main()
{
    int ch1,ch2,size,i,j;
	srand(time(NULL));
	int isDone;
	printf("******Welcome to SUDOKU******\n");
    printf("Select your difficulty level\n1) Easy(4X4)\n2) Medium(9X9)\n3) Hard(16X16)\n");
	scanf("%d",&ch1);
	printf("If you want to quit any time you can press 'n'\n");
	int ans_4[4][4] = {
							{3,0,4,0},
							{0,1,0,2},
							{0,4,0,3},
							{2,0,1,0}
					  };
    int ques_4[4][4] = {
							{3,0,4,0},
							{0,1,0,2},
							{0,4,0,3},
							{2,0,1,0}
					  };	 
                            
	int ans_9[9][9] = {
                            {0,0,8,9,5,7,0,3,0},
                            {0,0,3,0,0,0,0,0,0},
                            {4,0,7,0,3,2,0,6,9},
                            {0,0,1,0,0,0,0,0,0},
                            {9,0,0,5,0,1,0,0,7},
                            {8,0,0,2,6,3,0,0,0},
                            {0,0,0,6,1,0,4,0,2},
                            {7,0,0,0,0,0,0,1,6},
                            {6,0,5,7,2,0,8,0,3}
                    };
	int ques_9[9][9] = {
                            {0,0,8,9,5,7,0,3,0},
                            {0,0,3,0,0,0,0,0,0},
                            {4,0,7,0,3,2,0,6,9},
                            {0,0,1,0,0,0,0,0,0},
                            {9,0,0,5,0,1,0,0,7},
                            {8,0,0,2,6,3,0,0,0},
                            {0,0,0,6,1,0,4,0,2},
                            {7,0,0,0,0,0,0,1,6},
                            {6,0,5,7,2,0,8,0,3}
                    };
	int ans_16[16][16] = {
                            {1,0,0,2,3,4,0,0,12,0,6,0,0,0,7,0},
                            {0,0,8,0,0,0,7,0,0,3,0,0,9,10,6,11},
                            {0,12,0,0,10,0,0,1,0,13,0,11,0,0,14,0},
                            {3,0,0,15,2,0,0,14,0,0,0,9,0,0,12,0},
                            {13,0,0,0,8,0,0,10,0,12,2,0,1,15,0,0},
                            {0,11,7,6,0,0,0,16,0,0,0,15,0,0,5,13},
                            {0,0,0,10,0,5,15,0,0,4,0,8,0,0,11,0},
                            {16,0,0,5,9,12,0,0,1,0,0,0,0,0,8,0},
                            {0,2,0,0,0,0,0,13,0,0,12,5,8,0,0,3},
							{0,13,0,0,15,0,3,0,0,14,8,0,16,0,0,0},
							{5,8,0,0,1,0,0,0,2,0,0,0,13,9,15,0},
							{0,0,12,4,0,6,16,0,13,0,0,7,0,0,0,5},
							{0,3,0,0,12,0,0,0,6,0,0,4,11,0,0,16},
							{0,7,0,0,16,0,5,0,14,0,0,1,0,0,2,0},	
							{11,1,15,9,0,0,13,0,0,2,0,0,0,14,0,0},
							{0,14,0,0,0,11,0,2,0,0,13,3,5,0,0,12},
                    };
	int ques_16[16][16] = {
                            {1,0,0,2,3,4,0,0,12,0,6,0,0,0,7,0},
                            {0,0,8,0,0,0,7,0,0,3,0,0,9,10,6,11},
                            {0,12,0,0,10,0,0,1,0,13,0,11,0,0,14,0},
                            {3,0,0,15,2,0,0,14,0,0,0,9,0,0,12,0},
                            {13,0,0,0,8,0,0,10,0,12,2,0,1,15,0,0},
                            {0,11,7,6,0,0,0,16,0,0,0,15,0,0,5,13},
                            {0,0,0,10,0,5,15,0,0,4,0,8,0,0,11,0},
                            {16,0,0,5,9,12,0,0,1,0,0,0,0,0,8,0},
                            {0,2,0,0,0,0,0,13,0,0,12,5,8,0,0,3},
							{0,13,0,0,15,0,3,0,0,14,8,0,16,0,0,0},
							{5,8,0,0,1,0,0,0,2,0,0,0,13,9,15,0},
							{0,0,12,4,0,6,16,0,13,0,0,7,0,0,0,5},
							{0,3,0,0,12,0,0,0,6,0,0,4,11,0,0,16},
							{0,7,0,0,16,0,5,0,14,0,0,1,0,0,2,0},	
							{11,1,15,9,0,0,13,0,0,2,0,0,0,14,0,0},
							{0,14,0,0,0,11,0,2,0,0,13,3,5,0,0,12},
                    };
	switch(ch1)
	{
        case 1: solve(4,ans_4,0,0);
                label1: isDone = inputByUser(4,ques_4); 
				if(isDone == 1)
				{
					if(areEqual(4,ques_4,ans_4))
					printf("\n*****Congratulations! You have solved the puzzle!*****\n");
					else
					{
						printf("*****Sorry, Wrong Answer!*****\n");
						label4: printf("1) Solve Again?\n2) Just show me the solution.\n");
						scanf("%d",&ch2);
						switch(ch2)
						{
							case 1: goto label1;
									break;
							case 2: printf("-----SOLUTION-----\n");
									printSudokuSolved(4,ans_4);
									break;
							default:printf("Invalid input");
									exit(0);	
						}		 
						return 0;  
					}
				}
				else if(isDone == 2)
				{
					generateNewQues(4,ans_4);
					for(i=0;i<4;i++)
					{	
						for(j=0;j<4;j++)
						{
							ques_4[i][j] = ans_4[i][j];
						}
					}
					solve(4,ans_4,0,0);
					goto label1;
				}
				else
				goto label4;	
				break;

		case 2: solve(9,ans_9,0,0);
                label2: isDone = inputByUser(9,ques_9); 
				if(isDone == 1)
				{
					if(areEqual(9,ques_9,ans_9))
					printf("\n*****Congratulations! You have solved the puzzle!*****\n");
					else
					{
						printf("*****Sorry, Wrong Answer!*****\n");
						label5: printf("1) Solve Again?\n2) Just show me the solution.\n");
						scanf("%d",&ch2);
						switch(ch2)
						{
							case 1: goto label2;
									break;
							case 2: printf("-----SOLUTION-----\n");
									printSudokuSolved(9,ans_9);
									break;
							default:printf("Invalid input");
									exit(0);	
						}
						return 0;    
					}
				}
				else if(isDone == 2)
				{
					generateNewQues(9,ans_9);
					for(i=0;i<9;i++)
					{	
						for(j=0;j<9;j++)
						{
							ques_9[i][j] = ans_9[i][j];
						}
					}
					solve(9,ans_9,0,0);
					goto label2;
				}		
				else
				goto label5;
				break;

		case 3: solve(16,ans_16,0,0);
                label3: isDone = inputByUser(16,ques_16); 
				if(isDone == 1)
				{
					if(areEqual(16,ques_16,ans_16))
					printf("\n*****Congratulations! You have solved the puzzle!*****\n");
					else
					{
						printf("*****Sorry, Wrong Answer!*****\n");
						label6: printf("1) Solve Again?\n2) Just show me the solution.\n");
						scanf("%d",&ch2);
						switch(ch2)
						{
							case 1: goto label3;
									break;
							case 2: printf("-----SOLUTION-----\n");
									printSudokuSolved(16,ans_16);
									break;
							default:printf("Invalid input");
									exit(0);	
						}
						return 0;
					}
				}
				else if(isDone == 2)
				{
					generateNewQues(16,ans_16);
					for(i=0;i<16;i++)
					{	
						for(j=0;j<16;j++)
						{
							ques_16[i][j] = ans_16[i][j];
						}
					}
					solve(16,ans_16,0,0);
					goto label3;
				}		
				else
				goto label6;
				break;

		default: printf("Not a valid input");
				 exit(0);
	}                
}
