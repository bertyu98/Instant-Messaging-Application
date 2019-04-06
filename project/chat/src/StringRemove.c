#include<stdio.h>
#include<string.h>
void StringRemove(char str[],char word[]){
    int i, j = 0, k = 0,n = 0;
    int flag = 0;
 
   /* char str[100]*/ 
   char new[100];

    

    for(i = 0 ; str[i] != '\0' ; i++)
    {
        k = i;
     
        while(str[i] == word[j])
        {
            i++,j++;
            if(j == strlen(word))
            {
                flag = 1;
                break;
            }
        }
    j = 0;

    if(flag == 0)
        i = k;      
    else
        flag = 0;

    new[n++] = str[i];
    }

    new[n] = '\0';
    
    printf("\n\nAfter Removing Word From String: %s\n",new);
}
void main()
{
    char str[100], word[100];
    printf("\n\nEnter Any String: ");
    gets(str);

    printf("\n\nEnter Any Word You Want to be Removed: ");
    gets(word);
    StringRemove(str,word);
}

