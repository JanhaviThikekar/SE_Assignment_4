#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include <unistd.h>
#include <time.h>
#include"trie.h"
#define Filename_Length_Size 100
#define Word_MaxLength 10000
#define Word_Size (26)
#define Char_Index(c) ((int)c - (int)'a')

int count=0;


void progressBar(int progress, int total) 
{

   
    const int barWidth = 70;
    float ratio = (float)progress / (float)total;
    int barProgress = (int)(ratio * barWidth);

    printf("[");
    for (int i = 0; i < barWidth; i++) 
    {

        
        if (i < barProgress) 
        {

            printf("=");

        } 
        else if (i == barProgress) 
        {

            printf(">");

        } 
        else 
        {

            printf(" ");

        }

    }
    
    printf("] %d%%\r", (int)(ratio * 100));
    fflush(stdout);

}



struct TrieNode *getNode(void)
{

    struct TrieNode *newnode = NULL;    
 
    newnode = (struct TrieNode *)malloc(sizeof(struct TrieNode));    
    if (newnode)     
    {

        int i;
 
        newnode->isLeaf = 0;      
 
        for (i = 0; i < Word_Size; i++)     
        {   
         
           newnode->children[i] = NULL;
    
        }
    
    }
 
    return newnode;       
}
 
void insertInTrie(struct TrieNode *root, const char *key)         
{

    int trie_level;
    int index;
    int length;
    struct TrieNode *curr = root;

    length  = strlen(key);        
    
    for (trie_level = 0; trie_level < length; trie_level++)        
    {

        index = Char_Index(key[trie_level]); 

        if (!curr->children[index])
        {

            curr->children[index] = getNode();  

        }

        curr = curr->children[index];           
    }
    
    curr->isLeaf = 1;    

}

void autocorrectWord_swap(struct TrieNode *root,char word[100])        
{
    char demo ;
    char original_word[100];
    
    int i ;
    int j ; 
    int k;
    int length_word;
    
    
    length_word=strlen(word);      
    
    for(i=0;i<length_word;i++)  
    {   

        original_word[i]=word[i];

    }
    
    for(i=0;i<length_word;i++)    
    {

        for(j=i+1;j<length_word;j++)       
        {

            demo=word[i];
            word[i]=word[j];
            word[j]=demo;


            if(searchInTrie(root, word)==1)           
            {

                printf("--> Do you mean %s ?\n",word);  
                count++;

            }
            
            for(k=0;k<length_word;k++)   
            {   

                word[k]=original_word[k];

            }

        }

    }

}




void autocorrectWord_letter(struct TrieNode *root,char word[100])           
{ 
    char c;
    char new_array2[100];
    
    int count=0;
    int i=0;
    int j=0; 
    int length_word;
    
    

    length_word=strlen(word);          
    
    while(count<length_word)           
    {

        j=0;

        while(j<26)         
        {

            i=0;
            while(i<count)    
            {

                new_array2[i]=word[i];
                i++;

            }
            
            
            c = j + 'a';        
            new_array2[i]=c; 

            i++;
            while(i<length_word)        
            {

                new_array2[i]=word[i];
                i++;

            }
            
            new_array2[i]=0;           
            
            if(searchInTrie(root, new_array2)==1)         
            {   

                printf("--> Do you mean %s ?\n",new_array2);
                count++;

            }
            j++;    
              
        }
        count++; 

    } 


}


void autocorrectWord_repeat(struct TrieNode *root,char word[100])          

{

   
    int i;
    int j;
    int count=0 ;
    int length_word;
    char new[101],new_array1[101];
    

    length_word=strlen(word);          
    
    while(count<length_word)         
    {

        i=0;

        while(i<=count)          
        {
            new[i]=word[i];
            i++;
        }
       
        for(j=i-1;i<=length_word;i++,j++)       
        {

            new[i]=word[j];

        }
        for(i=0;i<=length_word;i++)
        {

            new_array1[i]=new[i];

        }
        new_array1[length_word+1]=0;      
        
        if(searchInTrie(root, new_array1)==1)           
        {   

            printf("--> Do you mean %s ?\n",new_array1);
            count++;

        }
        count++;           
    
    }

}


void autocorrectWord_hiddenletter(struct TrieNode *root,char word[100])         
{

    
    
    int i;
    int j ;
    int k;
    int count=0 ;
    int length_word ;
    
    char c;
    char new3[101],new4[101];
    

    length_word=strlen(word);           
    

    while(count<length_word)           
    {

        j=0;

        while(j<26)         
        {

            i=0;

            while(i<count)     
            {

                new3[i]=word[i];
                i++;

            }

            c = j + 'a';       
            new3[i]=c;           
            i++;  


            for(k=i-1;i<=length_word;i++,k++)
            {

                new3[i]=word[k];

            }
            for(i=0;i<=length_word;i++)
            {

                new4[i]=new3[i];

            }
            new4[length_word+1]=0;      
            
            if(searchInTrie(root,new4)==1)            
            {

                printf("--> Do you mean %s ?\n",new4);
                count++;

            }
            j++; 

        }
        count++;  

    }

}

bool searchInTrie(struct TrieNode *root, const char *key)         
{

    
    int trie_level;
    int length ;
    int index;

    struct TrieNode *curr = root;
    
    length = strlen(key);       

    for (trie_level = 0; trie_level < length; trie_level++)         
    {

        index = Char_Index(key[trie_level]);          
        if (!curr->children[index])                 
            return false;
 
        curr = curr->children[index];   

    }
 
    return (curr != NULL && curr->isLeaf); 

}


void findAndReplace_inTrie(FILE *file, struct TrieNode *root) 
{

    char word[Word_MaxLength];
    char replacement[Word_MaxLength];
    char choice;

    
    FILE *correctedFile = fopen("corrected_statement.txt", "w");

    if (correctedFile == NULL) 
    {

        printf("Error creating corrected file.\n");
        return;

    }

    
    while (fscanf(file, "%s", word) != EOF) 
    {
        
        if (!searchInTrie(root, word)) 
        {

            printf("\nIncorrect word found: %s\n", word);
            printf("Do you want to replace it? (y/n) or q to quit: ");
            scanf(" %c", &choice);

            if (tolower(choice) == 'y') 
            {
                printf("Enter the replacement word: ");
                scanf("%s", replacement);

                
                fprintf(correctedFile, "%s ", replacement);

                printf("Word replaced successfully!\n");

            } 

            else if (tolower(choice) == 'n') 
            {

               
                fprintf(correctedFile, "%s ", word);
            } 
            
            else if (tolower(choice) == 'q') 
            {

                break;

            }
        } 
        
        else 
        {

            fprintf(correctedFile, "%s ", word);

        }

        if (strcmp(word, "quit") == 0) 
        {

            printf("Exiting the incorrect word traversal.\n");
            break;

        }

    }

    
    fclose(correctedFile);

    printf("\nCorrected statement saved in 'corrected_statement.txt' file.\n");

}


void count_Incorrect(FILE *file, struct TrieNode *root) 
{

    char word[Word_MaxLength];
    int count = 0;


    while (fscanf(file, "%s", word) != EOF) 
    {
        
        if (!searchInTrie(root, word)) 
        {

            count++;
            printf("%s\n", word);

        }

    }


    fclose(file);

    printf("\nTotal incorrect words: %d\n", count);
}


void display_CorrectFile() 
{
    FILE *correctedFile = fopen("corrected_statement.txt", "r");
    if (correctedFile == NULL) 
    {
        printf("Error opening corrected file.\n");
        return;
    }

    printf("\n--- Corrected Statement ---\n\n");

    int ch;

    while ((ch = fgetc(correctedFile)) != EOF) 
    {
        printf("%c", ch);
    }

    printf("\n\n");

    fclose(correctedFile);
}


void findWithString(const char *filename, struct TrieNode *root) 
{

    char searchInTrieStr[Word_MaxLength];
    char line[Word_MaxLength];
    int lineNumber = 0;
    int wordNumber = 0;
    bool found = false;

printf("Enter the string to search: ");
scanf("%s", searchInTrieStr);

FILE* file = fopen(filename, "r");
if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
}

while (fgets(line, sizeof(line), file)) {
    lineNumber++;
    wordNumber = 0;

    char* token = strtok(line, " \n");
    while (token != NULL) {
        wordNumber++;

        if (strstr(token, searchInTrieStr) != NULL) {
            printf("String found at Line %d, Word %d: %s\n", lineNumber, wordNumber, token);
            found = true;
        }

        token = strtok(NULL, " \n");
    }
}

fclose(file);

if (!found) {
    printf("String not found. The following words are similar:\n");
    autocorrectWord_swap(root, searchInTrieStr);
    autocorrectWord_repeat(root, searchInTrieStr);
    autocorrectWord_letter(root, searchInTrieStr);
    autocorrectWord_hiddenletter(root, searchInTrieStr);
}

    
}



void view_original_wordFile(const char *filename) 
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        return;
    }

    printf("--- File Contents ---\n\n");

    char buffer[Word_MaxLength];
    while (fgets(buffer, Word_MaxLength, file) != NULL) 
    {
        printf("%s", buffer);
    }

    printf("\n");

    fclose(file);
}


void freeTrie(struct TrieNode *node) 
{

    if (node == NULL) 
    {

        return;

    }

    for (int i = 0; i < Word_Size; i++) 
    {

        freeTrie(node->children[i]);

    }


    free(node);

}


void get_Fileinfo(const char *filename, struct TrieNode *root) 
{

    FILE *file = fopen(filename, "r");

    if (file == NULL) 
    {

        printf("Error opening the file.\n");
        return;

    }

    const char *extension = strrchr(filename, '.');

    if (extension == NULL) 
    {

        printf("Invalid file format.\n");
        fclose(file);
        return;

    }

    
    const char *fileFormat = extension + 1;


    
    char word[Word_MaxLength];
    int totalWords = 0;
    int incorrectWords = 0;
    int correctWords = 0;


   
    while (fscanf(file, "%s", word) != EOF) 
    {
        totalWords++;

        
        if (!searchInTrie(root, word)) 
        {

            incorrectWords++;

        }
        else 
        {

            correctWords++;

        }

    }


    // Calculate correctness percentage
    float correctnessPercentage = (float)correctWords / totalWords * 100;


    // Close the file
    fclose(file);


    // Display file information
    printf("\n\nFile Information:\n");
    printf("====================\n\n");


    printf("Filename: %s\n", filename);
    printf("File Format: %s\n", fileFormat);
    printf("Number of Incorrect Words: %d\n", incorrectWords);
    printf("Number of Correct Words: %d\n", correctWords);
    printf("Percentage of Correctness: %.2f%%\n", correctnessPercentage);
    printf("Total Number of Words: %d\n", totalWords);


}

void get_CodeComplexity(const char *filename, struct TrieNode *root) 
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) 
    {

        printf("Error opening the file.\n");
        return;

    }

    
    char word[Word_MaxLength];
    int totalWords = 0;
    int incorrectWords = 0;
    int correctWords = 0;


   
    while (fscanf(file, "%s", word) != EOF) 
    {
        totalWords++;

        
        if (!searchInTrie(root, word)) 
        {

            incorrectWords++;

        }
        else 
        {

            correctWords++;

        }

    }


    // Calculate correctness percentage
    float correctnessPercentage = (float)correctWords / totalWords * 100;


    // Close the file
    fclose(file);


    // Display file information
    printf("\n\nCorrectness Information:\n");
    printf("====================\n\n");

    printf("Percentage of Correctness: %.2f%%\n", correctnessPercentage);
    

    clock_t start, end;
    double cpu_time_used;


    start = clock();


    // Place your code here


    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    printf("Total Execution Time: %.6f seconds\n\n", cpu_time_used);



   


}




void find_with_Character(FILE *file, struct TrieNode *root) 
{

    char searchInTrieChar;
    printf("Enter the character to find: ");
    scanf(" %c", &searchInTrieChar);


    int wordNumber = 0;
    char word[Word_MaxLength];


    char line[Word_MaxLength];

    while (fgets(line, sizeof(line), file)) 
    {
        wordNumber++;

        // Tokenize the line into words
        char *token = strtok(line, " ");
        while (token != NULL) 
        {

            strcpy(word, token);
            for (int i = 0; word[i]; i++) 
            {

                if (word[i] == searchInTrieChar) 
                {

                    printf("'%c' found at Word %d: %s\n", searchInTrieChar, wordNumber, token);
                    break;

                }

            }

            token = strtok(NULL, " \n");

        }


    }


    fclose(file);
}



void Append_inFile(const char *filename) 
{
    
    FILE *file = fopen(filename, "a");

    if (file == NULL) 
    {

        printf("Error opening file %s\n", filename);
        return;

    }


    char content[Word_MaxLength];
    printf("Enter the content to append to the file (max %d characters):\n", Word_MaxLength);


    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    
    }

    
    fgets(content, sizeof(content), stdin);

    // Remove trailing newline character
    
    int len = strlen(content);
    if (len > 0 && content[len - 1] == '\n') 
    {

        content[len - 1] = '\0';

    }

    
    fprintf(file, "%s\n", content);
    fclose(file);


    printf("Content successfully added to the file.\n");

}



void find_With_Substring(const char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    char substring[Word_MaxLength];

    printf("Enter the substring to search (without symbols or spaces): ");
    scanf("%s", substring);

    int substringLength = strlen(substring);
    printf("Words containing the substring '%s':\n", substring);

    char word[Word_MaxLength];
    char line[Word_MaxLength];
    int lineNumber = 0;
    int wordNumber = 0;

    while (fgets(line, sizeof(line), file))
    {
        lineNumber++;
        wordNumber = 0;

        char* token = strtok(line, " \n");
        while (token != NULL)
        {
            wordNumber++;
            if (strstr(token, substring) != NULL)
            {
                printf("Line %d, Word %d: %s\n", lineNumber, wordNumber, token);
            }
            token = strtok(NULL, " \n");
        }
    }

    fclose(file);
}
