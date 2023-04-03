#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
  
    FILE * outfile = stdout;
    FILE * infile = stdin;

    char s;
    char *kay;

    int debugMode = 0;
    int encodeModePlus = 0;
    int encodeModeMinus = 0;
    int isOutfile = 0;
    int isInfile = 0;

    for(int i=1; i<argc; i++){
      
        if(strcmp(argv[i],"-D")==0)
            debugMode = 0;

        if(debugMode == 1)
            fprintf(stderr, "%s\n",argv[i]);

        if(strcmp(argv[i],"+D")==0)
            debugMode = 1;
        

        if (strncmp(argv[i], "-i", 2) == 0){
            char *infileName =  argv[i] + 2;
            infile = fopen(infileName, "r");
            if(infile == NULL){
                fprintf(stderr, "The file doesnt exist\n");
                exit(1);
            }
            isInfile = 1;
        }

        if (strncmp(argv[i], "-o", 2) == 0){
            char *outfileName =  argv[i] + 2;
            outfile = fopen(outfileName, "w");
            if(outfile == NULL){
                fprintf(stderr, "There is an error\n");
                exit(1);
            }
            isOutfile = 1;
        }

        if (strncmp(argv[i], "+e", 2) == 0){

            encodeModePlus = 1;
            kay = argv[i] + 2;
        }

        if (strncmp(argv[i], "-e", 2) == 0){
            
            encodeModeMinus = 1;
            kay = argv[i] + 2;
        }
    }

    if(encodeModePlus == 1){

        int index = 0;
        while ((s = fgetc(infile)) != EOF){

                if(kay[index] == '\0')
                    index = 0;

                if(s >= 'A' && s <= 'Z'){
                        
                    s = 'A' + (s - 'A' + (kay[index] - '0')) % 26;
                }
                if(s >= '0' && s <= '9'){
                        
                    s = '0' + (s - '0' + (kay[index] - '0')) % 10;
                }
                if(s >= 'a' && s <= 'z'){
                        
                    s = 'a' + (s - 'a' + (kay[index] - '0')) % 26;
                }
                fputc(s, outfile);
                index++;
            }
    }
    else if(encodeModeMinus == 1){

        int index = 0;
        while ((s = fgetc(infile)) != EOF){
            
                if(kay[index] == '\0')
                    index = 0;

                if(s >= 'A' && s <= 'Z'){

                     s = ((s - 'A' - (kay[index] - '0') + 26) % 26) + 'A';
                }
                if(s >= '0' && s <= '9'){
                        
                    s = ((s - '0' - (kay[index] - '0') + 10) % 10) + '0';
                }
                if(s >= 'a' && s <= 'z'){
                        
                     s = ((s - 'a' - (kay[index] - '0') + 26) % 26) + 'a';
                }
                fputc(s, outfile);
                index++;   
        }
        
        
    }
    else{

        printf("NO ENCODER\n");
        exit(0);
    }

    if(isOutfile){
        fclose(outfile);
    }
    if(isInfile){
        fclose(infile);
    }
}