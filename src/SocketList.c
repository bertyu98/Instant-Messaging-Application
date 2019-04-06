#include "SocketList.h"
SocketNode* CreateSocket(char *username,int Port)
{
        SocketNode *newNode=malloc(sizeof(SocketNode));
        newNode->Port=Port;
        newNode->username=username;
        newNode->next=NULL;
        newNode->prev=NULL;
        return newNode;
}
void ClearSet(SocketSet *Set)
{
        SocketNode *currNode=Set->First;
        SocketNode *tempNode;
        if(Set->First==NULL)
                return;
        while(currNode->next!=NULL)//Get to the last element
        {
                currNode=currNode->next;
        }
        while(currNode->prev!=NULL)
        {
            currNode->Port=0;
            currNode->next=NULL;
            tempNode=currNode->prev;
            currNode->prev=NULL;
            free(currNode);
            currNode=tempNode;
        }
        Set->First->next=NULL;
        Set->First->prev=NULL;
        Set->First->Port=0;
        free(Set->First);
        Set->First=NULL;
        Set->NSockets=0;
}
void DeleteSet(SocketSet *Set)
{
        ClearSet(Set);
        Set->First=NULL;
        Set->NSockets=0;
        free(Set);
}
void RemoveSocket(SocketNode *node)//This wont handle taking one from the list of sockets integer of  Set, Shouldnt be called by user, only for linkedlist declaration
{
        if(node==NULL)
                return;
        if(node->prev!=NULL)
                node->prev->next=node->next;
        if(node->next!=NULL)
                node->next->prev=node->prev;
        node->next=NULL;
        node->prev=NULL;
        free(node);
}
void RemoveSocketUser(char* username,SocketSet *Set)
{
        SocketNode *currNode;
        currNode=Set->First;
        while(currNode!=NULL)
        {
                if(strcmp(username,currNode->username)==0)
                {
                        
                        if(currNode->prev!=NULL)//If there exists a previous
                        {
                                currNode->prev->next=currNode->next;//Set the previous node equals to the next of current

                        }
                        if(currNode->next!=NULL)//If there exists a next node
                        {
                                currNode->next->prev=currNode->prev;
                        }
                        Set->NSockets=Set->NSockets-1;
                        currNode->prev=NULL;
                        currNode->next=NULL;
                        currNode->username=NULL;
                        free(currNode);
                        
                }
                currNode=currNode->next;
        }
}
SocketSet *CreateSet() //Will create a new set to hold ports
{
        SocketSet *set=malloc(sizeof(SocketSet));
        assert(set);
        set->NSockets=0;
        set->First=NULL;
        return set;
}
int PortMatch(int port,SocketSet *Set) //Returns some port of username, -1 if no match found
{
        if(Set->First==NULL)
            return 0;
        SocketNode *currNode=Set->First;
        while(currNode!=NULL)
        {
                if(currNode->Port==port)
                {
                        return 1;
                }
                currNode=currNode->next;
        }
        return 0; //In case that there was no match
}
void AppendSocket(char *username, int port, SocketSet *Set)//Appens some port to the list
{
        if(PortMatch(port,Set))
		return;//We dont want to append if the socket already exists
	if( GetPort(username,Set) != -1) //If it returns something else than -1 means that the username already exists
	    return; //in that given case, we don't want to create a repeated username
	SocketNode *newNode=CreateSocket(username,port);
        if(Set->First==NULL)/*In case that this is the first socket appended*/
        {
                Set->First=newNode;
                Set->NSockets=Set->NSockets+1;
                return;
        }
        SocketNode *currNode=Set->First;
        while(currNode->next!=NULL)//Get to the last element
        {
                currNode=currNode->next;
        }
        newNode->prev=currNode;
        currNode->next=newNode;
        Set->NSockets=Set->NSockets+1;
}
char *GetUsername(int Port, SocketSet *Set)
{
        if(!Set)
            return NULL; //in case that set has not been initialized
        if(Set->First==NULL)
            return NULL;
        SocketNode *currNode=Set->First;
        while(currNode!=NULL)
        {
                if(currNode->Port==Port)
                {
                        return currNode->username;

                }
                currNode=currNode->next;
        }
        return NULL; //In case that there was no match
}
int GetPort(char *username,SocketSet *Set) //Returns some port of username, -1 if no match found
{
        if(Set->First==NULL)
            return -1;
        SocketNode *currNode=Set->First;
        while(currNode!=NULL)
        {
                if(strcmp(username,currNode->username)==0)
                {
                        return currNode->Port;
                        
                }
                currNode=currNode->next;
        }
        return -1; //In case that there was no match
}
int IterateSet(int number, SocketSet* Set)
{
    SocketNode *currNode;
    currNode=Set->First;
    int i=0;
    if(number>Set->NSockets)
        return -1;
    while(currNode!=NULL)
    {
        if(i==number)
            return currNode->Port;
        i++;
        currNode=currNode->next;
    }
    return -1; //outof bounds probably
}
SocketNode* CreatePort(int Port)
{
        SocketNode *newNode=malloc(sizeof(SocketNode));
        newNode->Port=Port;
        newNode->username="noname";
        newNode->next=NULL;
        newNode->prev=NULL;
        return newNode;
}
void AppendPort(int port, SocketSet *Set)//Appends some port to list, with no need of a username
{
        if(Set==NULL) return; //Dont append if set has not been initialized
        SocketNode *newNode=CreatePort(port);
        if(Set->First==NULL)/*In case that this is the first socket appended*/
        {
                Set->First=newNode;
                Set->NSockets=Set->NSockets+1;
                return;
        }
        SocketNode *currNode=Set->First;
        while(currNode->next!=NULL)//Go to the last element
        {
                currNode=currNode->next;
        }
        newNode->prev=currNode;
        currNode->next=newNode;
        Set->NSockets=Set->NSockets+1;
}
void RemoveSocketPort(int port,SocketSet *Set)//Same as RemoveSocketUser, but this will require a socket number to remove a socket
{
        SocketNode *currNode;
        currNode=Set->First;
        while(currNode!=NULL)
        {
                if(currNode->Port==port)
                {
                        
                        if(currNode->prev!=NULL)//If there exists a previous
                        {
                                currNode->prev->next=currNode->next;//Set the previous node equals to the next of current

                        }
                        if(currNode->next!=NULL)//If there exists a next node
                        {
                                currNode->next->prev=currNode->prev;
                        }
                        Set->NSockets=Set->NSockets-1;
                        currNode->prev=NULL;
                        currNode->next=NULL;
                        currNode->username=NULL;
                        free(currNode);
                        
                }
                currNode=currNode->next;
        }
}
