#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void leaf_node()
{   
    char filename[20];
    sprintf(filename, "%d.txt", getpid()); 

    FILE *fp = fopen(filename,"w");
    srand(getpid());
	int random = rand()%100;
    fprintf(fp,"%d",random);
    
    fclose(fp);
}

int read_file(int pid){ 	
	char filename[20];
	int value;
	sprintf(filename,"%d.txt",pid);
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d",&value);
	fclose(fp);
	return value;
}

int parent(int pidleft,int pidright)
{
    wait(NULL);
	int left = read_file(pidleft);
	int right = read_file(pidright);
	char filename[20];
	sprintf(filename,"%d.txt",getpid());
	
	FILE *fp = fopen(filename,"w");
	fprintf(fp,"%d",(left+right));
	
	fclose(fp);
	return right+left;
}

void create_tree(int height){ 
    
    if(height<=0) {leaf_node(); return;}

    int left = fork();

    if (left != 0) //parent
    {                            
        printf("root - pid : %d - height :  %d\n",getpid(),height); 

        waitpid(left, NULL, 0);
        int right = fork();
        waitpid(right, NULL, 0);

        if (right == 0) //right child
        { 
            printf("right - pid : %d - height :  %d\n",getpid(),height); 
                             
            create_tree(height-1);

        }
        else if (right!=0) 
        {
            int result = parent(left,right);
        }
    } 
    else   //left child
    { 
        printf("left - pid : %d - height :  %d\n",getpid(),height); 
        
        create_tree(height-1);

    }
}


int main(int argc,char* argv[])
{       
    if(argc!=2){
        printf("Usage: %s <height>\n",argv[0]);
        return 1;
    }
    else{
        create_tree(atoi(argv[1]));
    }
}






