#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_for_keyword(char s[]){
    char key[32][10]={"auto","double", "int", "struct", "int", "break", "else", "long", "switch", "case", "enum", "register",
                         "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void",
                         "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};
    int flag=1, i, kw;

    for(i=0; i<32; i++){
        kw=strcmp(s, key[i]);
        if(kw==0){
            return 1;
        }
    }
    return 0;
}

void check_headers(char headers[10][20]){
    FILE *p1,*p2;
    char c, y[5], header_name[10];
    int i=1, header=0, no_headers=0;

    p1 = fopen("input.txt", "r");
    p2 = fopen("assignment_output.txt","w");
    ///Header Names and Line Number
    itoa(i,y,10);
    fputs(y, p2);
    fputc('.', p2);
    i++;

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	while((c = fgetc(p1)) != EOF)
      	{
      	    if(header==1 && c=='<'){
                int i=0;
                fputc(c, p2);
                while((c = fgetc(p1)) != '>'){
                    header_name[i]=c;
                    i++;
                    fputc(c, p2);
                }
                header_name[i]='\0';
                strcpy(headers[no_headers], header_name);
                no_headers++;
                header=0;
      	    }

      	    if(c=='\n'){
                fputc('\n',p2);
                itoa(i,y,10);
                fputs(y, p2);
                fputc('.', p2);
                i++;
                header=0;
                continue;
      	    }
      	    if(c=='#'){
                header++;
      	    }
            fputc(c,p2);
        }
    }
    fclose(p1);
    fclose(p2);


    FILE *p5;
    p5 = fopen("assignment_output.txt", "a");
    if(!p5){
        printf("File can not be opened!");
    }else{
        fputc('\n', p5);
        fputc('\n', p5);
        fputs("Headers: ", p5);
        fputc('\n', p5);
        int k=0;
        for(k=0; k<no_headers; k++){
            //printf("\n%s", headers[k]);
            fputs(headers[k], p5);
            fputc('\n', p5);
        }
    }
    fclose(p5);
}

int check_for_datatypes(char s[]){
    char key[7][10]={"double", "int", "struct", "int", "char", "float", "bool"};
    int flag=1, i, kw;

    for(i=0; i<7; i++){
        kw=strcmp(s, key[i]);
        if(kw==0){
            return 1;
        }
    }
    return 0;
}

void check_identifiers(char identifiers[20][30], char functions[20][30]){
    FILE *p1;
    char c, temp[30];
    int no_identifiers=0, i=0, j, id=0;
    int no_functions=0, func=0;

    p1 = fopen("input.txt", "r");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	while((c = fgetc(p1)) != EOF)
      	{
      	    //printf("%c ", c);
      	    if(id==1){
      	        int o=0;
                while(1){
                    if(c=='('){
                        func=1;
                        break;
                    }
                    if(c==' ' || c==';' || c=='=' || c=='\n'){
                        break;
                    }else{
                        temp[o]=c;
                        o++;
                    }
                    c=fgetc(p1);
                }
                temp[o]='\0';
                if(func==1){
                    strcpy(functions[no_functions], temp);
                    no_functions++;
                }
                else{
                    strcpy(identifiers[no_identifiers], temp);
                    no_identifiers++;
                }
                for(j=0; j<o; j++){
                    temp[j]='\0';
                }
                id=0;
                func=0;
      	    }
      	    if(c=='\n'){
                for(j=0; j<i; j++){
                    temp[j]='\0';
                }
                i=0;
                continue;
      	    }
      	    if(c==' '){
                temp[i]='\0';
                int res=check_for_datatypes(temp);
                if(res==1){
                    id=1;
                }else{
                    id=0;
                }
                for(j=0; j<i; j++){
                    temp[j]='\0';
                }
                i=0;
      	    }else{
      	        temp[i]=c;
      	        i++;
      	    }
        }
    }
    fclose(p1);

    FILE *p5;
    p5 = fopen("assignment_output.txt", "a");
    if(!p5){
        printf("File can not be opened!");
    }else{
        fputc('\n', p5);
        fputs("Identifiers: ", p5);
        fputc('\n', p5);
        int k=0;
        for(k=0; k<no_identifiers; k++){
            //printf("\n%s", identifiers[k]);
            fputs(identifiers[k], p5);
            fputc('\n', p5);
        }
        fputc('\n', p5);
        fputs("Functions: ", p5);
        fputc('\n', p5);
        k=0;
        for(k=0; k<no_functions; k++){
            //printf("\n%s", functions[k]);
            fputs(functions[k], p5);
            fputc('\n', p5);
        }
    }
    fclose(p5);
}


void check_keywords(char keywords[20][30]){
    FILE *p1;
    char c, temp[30];
    int no_keywords=0, i=0, j;

    p1 = fopen("input.txt", "r");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	while((c = fgetc(p1)) != EOF)
      	{
      	    //printf("%c ", c);
      	    if(c=='\n'){
                for(j=0; j<i; j++){
                    temp[j]='\0';
                }
                i=0;
                continue;
      	    }
      	    if(c==' '){
                temp[i]='\0';
                int res=check_for_keyword(temp);
                if(res==1){
                    strcpy(keywords[no_keywords], temp);
                    no_keywords++;
                }
                for(j=0; j<i; j++){
                    temp[j]='\0';
                }
                i=0;
      	    }else{
      	        temp[i]=c;
      	        i++;
      	    }
        }
    }
    fclose(p1);

    FILE *p5;
    p5 = fopen("assignment_output.txt", "a");
    if(!p5){
        printf("File can not be opened!");
    }else{
        fputc('\n', p5);
        fputs("Keywords: ", p5);
        fputc('\n', p5);
        int k=0;
        for(k=0; k<no_keywords; k++){
            //printf("\n%s", keywords[k]);
            fputs(keywords[k], p5);
            fputc('\n', p5);
        }
    }
    fclose(p5);
}

void check_errors(){
    FILE *p1, *p5;
    char c, temp[30], temp1[4];
    int parenthesis=0, second_bracket=0, colon=0, line=1;

    p1 = fopen("input.txt", "r");
    p5 = fopen("assignment_output.txt", "a");
    fputc('\n', p5);
    fputs("Errors: ", p5);
    fputc('\n', p5);

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	while((c = fgetc(p1)) != EOF)
      	{
      	    if(c=='\n'){
                line++;
      	    }

      	    if(c=='('){
                parenthesis++;
            }else if(c==')'){
                parenthesis--;
                if(parenthesis<0){
                    //printf("\nMisplaced parenthesis at line %d!", line);
                    fputc('\n', p5);
                    fputs("Misplaced parenthesis at line ", p5);
                    itoa(line, temp1, 10);
                    fputs(temp1, p5);
                    fputc('\n', p5);
                    parenthesis=0;
                }
            }

      	    if(c=='{'){
                second_bracket++;
            }else if(c=='}'){
                second_bracket--;
                if(second_bracket<0){
                    //printf("\nMisplaced parenthesis at line %d!", line);
                    fputc('\n', p5);
                    fputs("Misplaced Curly Bracket at line ", p5);
                    itoa(line, temp1, 10);
                    fputs(temp1, p5);
                    fputc('\n', p5);
                    second_bracket=0;
                }
            }

            if(c=='f'){
                if((c=fgetc(p1))=='o'){
                    if((c=fgetc(p1))=='r'){
                        while((c=fgetc(p1))!=')'){
                            if(c==';')
                                colon++;
                        }
                        if(colon!=2){
                            //printf("\nDeclaration of for loop not correct at line %d", line);
                            fputc('\n', p5);
                            fputs("Declaration of for loop not correct at line ", p5);
                            itoa(line, temp1, 10);
                            fputs(temp1, p5);
                            fputc('\n', p5);
                        }
                        colon=0;
                    }
                }
            }
        }
    }
    fclose(p1);
    fclose(p5);
}

void output(){
    printf("\n\n\nFINAL OUTPUT:\n\n");
    FILE *p1;
    p1 = fopen("assignment_output.txt", "r");
    if(!p1){
        printf("File can not be opened");
    }else{
        char c;
        while((c=fgetc(p1))!=EOF){
            printf("%c", c);
        }
    }
    fclose(p1);
}

int main(void)
{
    FILE *p1;
    char c;
    char headers[10][20], keywords[20][30], identifiers[20][30], functions[20][30];

    printf("Original File: \n");
    p1 = fopen("input.txt","r");
    while((c=fgetc(p1))!=EOF)
		printf("%c",c);
    fclose(p1);

    check_headers(headers);
    check_identifiers(identifiers, functions);
    check_keywords(keywords);
    check_errors();
    output();

    return 0;
}


