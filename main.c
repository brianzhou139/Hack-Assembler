#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000

void Tester(int o,int Out[],int In[],int i);
int InstructionType(char c);
void WriteAInstruction(int num,int final[]);
void WriteCInstruction(char instruction[],int final[]);
void WriteComp(int instruction_out[],int Comp_input[]);
void WriteDest(int instruction_out[],int Dest_input[]);
void WriteJump(int instruction_out[],int Jump_input[]);
int getInstructionType(char instruction[],int n);

int main()
{
    int Instruction[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "test.txt";
    fp = fopen(filename, "r");
    FILE *out_file = fopen("hack.txt", "w"); // write only

    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    /*
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);*/

    while (fgets(str, MAXCHAR, fp) != NULL){
        if(InstructionType(str[0])==0){
            str[0]='0';
            int val=atoi(str);
            WriteAInstruction(val,Instruction);

            /*Write inctruction to file here*/
            //printf alal A instrcution here yes
            //printf("ins : %s : ",str);
            int i;
            for(i=0;i<16;++i){
                //printf("%d",Instruction[i]);
                fprintf(out_file, "%d",Instruction[i]);
            }
            fprintf(out_file, "\n");

        }else{
            int sz=strlen(str);
            //printf("%s\t : C-Instruction : %d\n", str,getInstructionType(str,sz));
            WriteCInstruction(str,Instruction);
            int a;
            for(a=0;a<16;++a){
                fprintf(out_file, "%d",Instruction[a]);
            }
            fprintf(out_file, "\n");
        }


    }

    printf("Done successfully !!!\n");
    printf("Check output_file\n");

    fclose(fp);
    fclose(out_file);

    return 0;
}

void Tester(int o,int Out[],int In[],int i){
    printf("IN below : \n");
    int j;
    for(j=0;j<i;++j){
        printf("%d",In[j]);
    }
    printf("\n\nOut below\n");
    for(j=0;j<o;++j){
        printf("%d",Out[j]);
    }
    printf("\n");
}

void WriteAInstruction(int num,int final[]){

    int i,res,bin;
    for(i=0;i<16;++i){
        final[i]=0;
    }
    res=num;
    bin=15;
    while(res!=0){
        final[bin]=res%2;
        //printf("## %d\n",res%2);
        --bin;
        res=res/2;
    }
    //printf("Done now yeah\n");
}

int InstructionType(char c){
    if(c=='@'){
        return 0; //0 means its an A-Instruction
    }else{
        return 1;
    }
}
/*
Comp : receives an instruction as argument and fills the comp part with the comp_input
//Tested and tried
*/

void WriteComp(int instruction_out[],int Comp_input[]){
    int i;
    for(i=0;i<7;++i){
        instruction_out[i+3]=Comp_input[i];
        //Tester(16,instruction_out,Comp_input,7);
    }
    //Tester(16,instruction_out,Comp_input,7);
}

void WriteDest(int instruction_out[],int Dest_input[]){
    int i;
    for(i=0;i<3;++i){
        instruction_out[i+10]=Dest_input[i];
    }
    //Tester(16,instruction_out,Dest_input,3);
}

void WriteJump(int instruction_out[],int Jump_input[]){
    int i;
    for(i=0;i<3;++i){
        instruction_out[i+13]=Jump_input[i];
    }
    Tester(16,instruction_out,Jump_input,3);
}

/*
WriteCInstruction: writes a C instrcution be calling the utility functions
//
*/

void WriteCInstruction(char instruction[],int final[]){

  int i;
  int sz=strlen(instruction);
  int instType=getInstructionType(instruction,sz);

  char dest_literal[5]="";
  char comp_literal[5]="";
  char jump_literal[5]="";
  //get it done yeah

  //result values here
  int dest_value[3]={0,0,0};
  int jump_value[3]={0,0,0};
  int comp_value[7]={0,0,0,0,0,0,0};


  if(instType==1){
    int k=0;
    int i=0;

    while(instruction[i]!='='){
        dest_literal[k]=instruction[i];
        ++i;
        ++k;
    }
    ++i;
    k=0;
    while(instruction[i]!=';'){
        comp_literal[k]=instruction[i];
        ++i;
        ++k;
    }
    ++i;
    k=0;
    while(instruction[i]!='\n'){
        jump_literal[k]=instruction[i];
        i++;
        ++k;
    }

  }else if(instType==2){
    int k=0;
    int i=0;

    while(instruction[i]!='='){
        dest_literal[k]=instruction[i];
        ++i;
        ++k;
    }
    //printf("test i : %d",i);
    ++i;
    k=0;
    while(instruction[i]!='\n'){
        comp_literal[k]=instruction[i];
        ++i;
        ++k;
    }
    //printf("here type 2 \n");
  }else if(instType==3){
    int k=0;
    int i=0;

    while(instruction[i]!=';'){
        comp_literal[k]=instruction[i];
        ++i;
        ++k;
    }
    ++i;
    k=0;
    while(instruction[i]!='\n'){
        jump_literal[k]=instruction[i];
        ++i;
        ++k;
    }

  }else{
      printf("Invalid instruction heyyy\n");
  }

  //printf("dest : %s\n",dest_literal);
  //printf("comp : %s\n",comp_literal);
  //printf("jump : %s\n",jump_literal);
  //Firstly set the Destination
  //Stage 1 : destination setting
  if(strcmp(dest_literal,"M")==0){
    dest_value[0]=0;dest_value[1]=0;dest_value[2]=1;
  }else if(strcmp(dest_literal,"D")==0){
    dest_value[0]=0;dest_value[1]=1;dest_value[2]=0;
  }else if(strcmp(dest_literal,"MD")==0){
    dest_value[0]=0;dest_value[1]=1;dest_value[2]=1;
  }else if(strcmp(dest_literal,"A")==0){
    dest_value[0]=1;dest_value[1]=0;dest_value[2]=0;
  }else if(strcmp(dest_literal,"AM")==0){
     dest_value[0]=1;dest_value[1]=0;dest_value[2]=1;
  }else if(strcmp(dest_literal,"AD")==0){
     dest_value[0]=1;dest_value[1]=1;dest_value[2]=0;
  }else if(strcmp(dest_literal,"AMD")==0){
     dest_value[0]=1;dest_value[1]=1;dest_value[2]=1;
  }else if(strcmp(dest_literal,"")==0){
     dest_value[0]=0;dest_value[1]=0;dest_value[2]=0;
  }else{
      printf("Error here : Stage 1 : destination setting  \n");
      printf("inst : %s\n",instruction);
  }

  //stage 2  jump : setting
  if(strcmp(jump_literal,"JGT")==0){
    jump_value[0]=0;jump_value[1]=0;jump_value[2]=1;
  }else if(strcmp(jump_literal,"JEQ")==0){
      jump_value[0]=0;jump_value[1]=1;jump_value[2]=0;
  }else if(strcmp(jump_literal,"JGE")==0){
      jump_value[0]=0;jump_value[1]=1;jump_value[2]=1;
  }else if(strcmp(jump_literal,"JLT")==0){
      jump_value[0]=1;jump_value[1]=0;jump_value[2]=0;
  }else if(strcmp(jump_literal,"JNE")==0){
      jump_value[0]=1;jump_value[1]=0;jump_value[2]=1;
  }else if(strcmp(jump_literal,"JLE")==0){
      jump_value[0]=1;jump_value[1]=1;jump_value[2]=0;
  }else if(strcmp(jump_literal,"JMP")==0){
      jump_value[0]=1;jump_value[1]=1;jump_value[2]=1;
  }else if(strcmp(jump_literal,"")==0){
      jump_value[0]=0;jump_value[1]=0;jump_value[2]=0;
  }else{
      printf("Erorr here >> stage 2  jump : setting ");
      printf("inst : %s\n",jump_literal);
  }


  //stage 3 part : setting comp , a=0
  if(strcmp(comp_literal,"0")==0){
    comp_value[0]=0;
    comp_value[1]=1; comp_value[2]=0; comp_value[3]=1;
    comp_value[4]=0; comp_value[5]=1; comp_value[6]=0;
  }else if(strcmp(comp_literal,"1")==0){
    comp_value[0]=0;
    comp_value[1]=1; comp_value[2]=1; comp_value[3]=1;
    comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
  }else if(strcmp(comp_literal,"-1")==0){
    comp_value[0]=0;
    comp_value[1]=1; comp_value[2]=1; comp_value[3]=1;
    comp_value[4]=0; comp_value[5]=1; comp_value[6]=0;
  }else if(strcmp(comp_literal,"D")==0){
    comp_value[0]=0;
    comp_value[1]=0; comp_value[2]=0; comp_value[3]=1;
    comp_value[4]=1; comp_value[5]=0; comp_value[6]=0;
  }else if(strcmp(comp_literal,"!D")==0){
    comp_value[0]=0;
    comp_value[1]=0; comp_value[2]=0; comp_value[3]=1;
    comp_value[4]=1; comp_value[5]=0; comp_value[6]=1;
  }else if(strcmp(comp_literal,"-D")==0){
    comp_value[0]=0;
    comp_value[1]=0; comp_value[2]=0; comp_value[3]=1;
    comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
  }else if(strcmp(comp_literal,"D+1")==0){
    comp_value[0]=0;
    comp_value[1]=0; comp_value[2]=1; comp_value[3]=1;
    comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
  }else if(strcmp(comp_literal,"D-1")==0){
    comp_value[0]=0;
    comp_value[1]=0; comp_value[2]=0; comp_value[3]=1;
    comp_value[4]=1; comp_value[5]=1; comp_value[6]=0;
  }else if((strcmp(comp_literal,"A")==0) || (strcmp(comp_literal,"M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"A")==0){
        comp_value[0]=0;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=0; comp_value[6]=0;
      }
      //Check if a=1
      if(strcmp(comp_literal,"M")==0){
        comp_value[0]=1;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=0; comp_value[6]=0;
      }
  }else if((strcmp(comp_literal,"!A")==0) || (strcmp(comp_literal,"!M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"!A")==0){
        comp_value[0]=0;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=0; comp_value[6]=1;
      }
      //Check if a=1
      if(strcmp(comp_literal,"!M")==0){
        comp_value[0]=1;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=0; comp_value[6]=1;
      }
  }else if((strcmp(comp_literal,"-A")==0) || (strcmp(comp_literal,"-M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"-A")==0){
        comp_value[0]=0;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=1;
      }
      //Check if a=1
      if(strcmp(comp_literal,"-M")==0){
        comp_value[0]=1;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=1;
      }
  }else if((strcmp(comp_literal,"A+1")==0) || (strcmp(comp_literal,"M+1")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"A+1")==0){
        comp_value[0]=0;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
      }
      //Check if a=1
      if(strcmp(comp_literal,"M+1")==0){
        comp_value[0]=1;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
      }
  }else if((strcmp(comp_literal,"A-1")==0) || (strcmp(comp_literal,"M-1")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"A-1")==0){
        comp_value[0]=0;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=0;
      }
      //Check if a=1
      if(strcmp(comp_literal,"M-1")==0){
        comp_value[0]=1;
        comp_value[1]=1; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=0;
      }
  }else if((strcmp(comp_literal,"D+A")==0) || (strcmp(comp_literal,"D+M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"D+A")==0){
        comp_value[0]=0;
        comp_value[1]=0; comp_value[2]=0; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=0;
      }
      //Check if a=1
      if(strcmp(comp_literal,"D+M")==0){
        comp_value[0]=1;
        comp_value[1]=0; comp_value[2]=0; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=0;
      }
  }else if((strcmp(comp_literal,"D-A")==0) || (strcmp(comp_literal,"D-M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"D-A")==0){
        comp_value[0]=0;
        comp_value[1]=0; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=1;
      }
      //Check if a=1
      if(strcmp(comp_literal,"D-M")==0){
        comp_value[0]=1;
        comp_value[1]=0; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=1; comp_value[6]=1;
      }
  }else if((strcmp(comp_literal,"A-D")==0) || (strcmp(comp_literal,"M-D")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"A-D")==0){
        comp_value[0]=0;
        comp_value[1]=0; comp_value[2]=0; comp_value[3]=0;
        comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
      }
      //Check if a=1
      if(strcmp(comp_literal,"M-D")==0){
        comp_value[0]=1;
        comp_value[1]=0; comp_value[2]=0; comp_value[3]=0;
        comp_value[4]=1; comp_value[5]=1; comp_value[6]=1;
      }
  }else if((strcmp(comp_literal,"D&A")==0) || (strcmp(comp_literal,"D&M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"D&A")==0){
        comp_value[0]=0;
        comp_value[1]=0; comp_value[2]=0; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=0; comp_value[6]=0;
      }
      //Check if a=1
      if(strcmp(comp_literal,"D&M")==0){
        comp_value[0]=1;
        comp_value[1]=0; comp_value[2]=0; comp_value[3]=0;
        comp_value[4]=0; comp_value[5]=0; comp_value[6]=0;
      }
  }else if((strcmp(comp_literal,"D|A")==0) || (strcmp(comp_literal,"D|M")==0)){
      //Check if a=0
      if(strcmp(comp_literal,"D|A")==0){
        comp_value[0]=0;
        comp_value[1]=0; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=1; comp_value[5]=0; comp_value[6]=1;
      }
      //Check if a=1
      if(strcmp(comp_literal,"D|M")==0){
        comp_value[0]=1;
        comp_value[1]=0; comp_value[2]=1; comp_value[3]=0;
        comp_value[4]=1; comp_value[5]=0; comp_value[6]=1;
      }
  }else{
      //there is a mistake in provided machine code ...
      printf("There is an error shame : stage 3 part 1: setting comp , a=0\n");
      printf("inst : %s\n",instruction);
  }

  //set the final ,Array of instruction yes yes
  final[0]=1;final[1]=1;final[2]=1;

  //set comp first
  int a;
  for(a=0;a<7;++a){
    final[a+3]=comp_value[a];
  }

  //set dest second
  int b;
  for(b=0;b<3;++b){
    final[b+10]=dest_value[b];
  }

  int c;
  for(c=0;c<3;++c){
    final[c+13]=jump_value[c];
  }
  //Done this function returns nothing yes yes
  //function that does magic here ...yeah yeah yeah
}

/*
getInstructionType : returns type
  //Determine instruction type
  //type 1 dest=comp;jump
  //type 2 dest=comp
  //type 3 comp;jump
*/

int getInstructionType(char instruction[],int n){
    int i,nequal,ncolon;
    nequal=ncolon=0;

    for(i=0;i<n;++i){
        if(instruction[i]=='='){
            ++nequal;
        }
        if(instruction[i]==';'){
            ++ncolon;
        }
    }//end of for(){} ....

    if(nequal==1 && ncolon==1){
        return 1;
    }else if(nequal==1 && ncolon==0){
        return 2;
    }else if(nequal==0 && ncolon==1){
        return 3;
    }else{
        return 0;
    }//end of if.;l


}
