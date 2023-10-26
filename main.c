#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "trie.h"
#define Array_Size(a) sizeof(a) / sizeof(a[0])
#define Word_Size (26)
#define Char_Index(c) ((int)c - (int)'a')
#define Filename_Length_Size 100
#define Word_MaxLength 10000000



int main()
{
    
    void progressbar();
    void loadprogressbar();

    FILE *fmain = NULL;
    int choice;
    int countt;
    char *demo_word;
    char ch[100];
    char word[1000];
    char data[100];
    char output[][32] = {"incorrect word ", "correct word"};
    struct TrieNode *root = getNode();
    int choice1= 0;
    int count= 0;
    int totalProgress = 100;

    printf("Loading...\n");

    for (int progress = 0; progress <= totalProgress; progress++)
    {

        progressBar(progress, totalProgress);
        usleep(100000); // Sleep for 100 milliseconds (adjust as needed)
   
    }

    printf("\n\n");    
    
    printf("\t\t||=================================================================================||\n");
    printf("\t\t||             WELCOME TO MIS-SPELLED DETECTOR AND AUTOCORRECT SUGGESTER           ||\n");
    printf("\t\t||=================================================================================||\n\n");

    fmain = fopen("words.txt", "r");
    
    while (fscanf(fmain, "%s", ch) != EOF)
    {
        insertInTrie(root, ch);
    }
    fclose(fmain);
    
    char filename[Filename_Length_Size] ;
    printf(">> Enter the file name (in txt form): ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    
    
    if (file == NULL)
    {

        printf("\n");
        printf(" ____________________________________________________\n");
        printf("|               Error opening the file               |\n");
        printf("|____________________________________________________|\n");
        exit(0);
    
    }
    
    else
    {

        printf("\n");
        printf(" ___________________________\n");
        printf("| File Sucessfully Accepted |\n");
        printf("|___________________________|\n");  
    
    }
    
    
    do 
    {
    

    printf("\n\n");
    printf("\t\t\t                               MAIN MENU                             \n");
    printf("\n\t\t+-----------+---------------------------------------------------------+");
    printf("\n\t\t|   Choice  |                     Functionality                       |");
    printf("\n\t\t+===========+=========================================================+");
    printf("\n\t\t|     1     |         Find Number and Incorrect words                 |");
    printf("\n\t\t|     2     |         Find incorrect words with its Autocorrections   |");
    printf("\n\t\t|     3     |         Add New word in the Word Bank                   |");
    printf("\n\t\t|     4     |         Find and Replace Incorrect Words                |");
    printf("\n\t\t|     5     |         View Contents of Users File                     |");
    printf("\n\t\t|     6     |         View Contents of Corrected File                 |");
    printf("\n\t\t|     7     |         View File Information                           |");
    printf("\n\t\t|     8     |         View File Correctness and Execution Time        |");
    printf("\n\t\t|     9     |         Find Words in file by Character                 |");
    printf("\n\t\t|    10     |         Find Words in File by Substring                 |");
    printf("\n\t\t|    11     |         Find Words in file by String                    |");
    printf("\n\t\t|    12     |         Append Content at Users File                    |");
    printf("\n\t\t|    13     |         Exit                                            |");
    printf("\n\t\t+-----------+---------------------------------------------------------+");


    printf("\n\n\n>> Enter your choice: ");
    scanf("%d", &choice);
    
    
    printf("\n");
    printf("\n\n Your choice is : %d\n\n ",choice);   
    
    
    switch (choice) 
    {
    case 1:
        {

            file = fopen(filename, "r");
            if (file == NULL) 
            {

                printf("Error opening file.\n");
                return 1;   

            }

            count_Incorrect(file, root);
            break;

        }
    
    case 2: 
    {

        FILE *file = fopen(filename, "r");
        
        if (file == NULL) 
        {

            printf("Failed to open the file.\n");
            break;
        }

        char demo_word[100]; // Assuming a maximum word length of 100 characters

        while (fscanf(file, "%s", demo_word) != EOF) 
        {

        char string1[] = "incorrect word ";
        if (strcmp(output[searchInTrie(root, demo_word)], string1) == 0) 
        {

            printf("%s is incorrect\n", demo_word);
        
        }

        if (searchInTrie(root, demo_word) == 0) 
        {

            for (countt = 0; countt <= 3; countt++) 
            {
                if (countt == 0)
                {

                    autocorrectWord_swap(root, demo_word);

                }
                else if (countt == 1)
                {

                    autocorrectWord_hiddenletter(root, demo_word);

                }
                else if (countt == 2)
                { 

                    autocorrectWord_repeat(root, demo_word);

                }
                else
                {

                    autocorrectWord_letter(root, demo_word);

                }
            
            }

            printf("\n");

            if (count == 0) 
            {

                printf("\t ________________________________________________________\n");
                printf("\t|           Suggestion of a word not found !!            |\n");
                printf("\t|________________________________________________________|\n\n");

            }
            count++;
        }
    }

    fclose(file);
    break;
    
    }

    case 3:
    {

    FILE *file = fopen(filename, "r");
    
    while (fscanf(file, "%[^\n]", word) != EOF) 
    {

        demo_word = strtok (word," ,.-\n");
        printf("\n");

        while ( demo_word != NULL)           
        {

            printf("\nDo you want to add any word in our list ('1' for yes '0' for no): ");
            scanf("%d",&choice1); 

            switch(choice1)          
            {

                case 1 :
                {

                printf("\nGive the word which you want to add into list : ");
                scanf("%s",data);  

                if(searchInTrie(root,data)==0)
                {

                    fmain = fopen("words.txt" , "a");            
                    fputs(data , fmain);                         
                    fputs("\n" , fmain);  

                    printf("\n");
                    printf(" ___________________________________________________________\n");
                    printf("|           Your word is successfully entered !!            |\n");
                    printf("|___________________________________________________________|\n");   

                    fclose(fmain);

                }

                else
                {

                    printf("\n");
                    printf(" ____________________________________________\n");
                    printf("|              Word already exist !!         |\n");
                    printf("|____________________________________________|\n");    
                    printf("\nWord already exist !!\n\n");

                }
            }

            break ;
            
            case 0:
            {
                printf("\n");
                printf("\nYou entered '0' to enter main menu\n");

                fclose(fmain); 
                    
                    }  
                    break;         
                
                }
                break;
            
            }
            break;
        
        }
        break;
    
    }
    break;
    

    case 4:
        {

            file = fopen(filename, "r");
            if (file == NULL) 
            {

                printf("Error opening file.\n");
                return 1;

            }

            findAndReplace_inTrie(file, root);
            fclose(file);

            break;

        }


    case 5:
        {

            view_original_wordFile(filename);
            printf("\n\n");
            break;

        }


    case 6:
        {

           display_CorrectFile();
            break;

        }

    case 7:
        {

            get_Fileinfo(filename, root);
            printf("\n\n");
            break;

        }
        
    case 8:
        {

            get_CodeComplexity(filename,root);
            printf("\n\n");
            break;

        }   

    case 9:
        {

            file = fopen(filename, "r");

            if (file == NULL) 
            {
                printf("Error opening the file.\n");
                return 1;
            }

            find_with_Character(file, root);
            break;
        }
        
    case 10:
        {

            find_With_Substring(filename);
            break;
        }

    case 11:
        {

            findWithString(filename, root);
            break;

        }
    

    case 12:
        {

            Append_inFile(filename);
            break;
        }


    
    case 13:
        {
            printf("\n");
            printf("\n\n");

            printf("\t||=========================================================================||\n");
            printf("\t||                          THANKS FOR VISITING                            ||\n");
            printf("\t||=========================================================================||\n");
            printf("\n\n");
            printf("\t\tProject Developed by : ");
            printf("\n\t\t+-----------------------+----------------------------------+");
            printf("\n\t\t|           MIS         |                  Name            |");
            printf("\n\t\t+=======================+==================================+");
            printf("\n\t\t|         142203008     |            RUTUJA INGLE          |");
            printf("\n\t\t|         142203009     |            JANHAVI THIKEKAR      |");
            printf("\n\t\t|         142203016     |            ADITYA RAUL           |");
            printf("\n\t\t+-----------------------+----------------------------------+");
            printf("\n\n\tProject Guide: Prof. Ashwini Matange\n");
            printf("\n\n\n");


            exit(0);
        }
        
    default:
        {
            printf("Invalid choice. Please enter a valid option.\n");
        }
        
        }

    } while (choice != 13);

    return 0;
}
