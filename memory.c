#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"../headers/memory.h"


/*Function to move the memory bytes from the source to the destination for the length specified*/
uint8_t my_memmove(uint8_t* src, uint8_t* dst, uint32_t length)
{
   
   uint32_t index;                                                       //32 bit unsigned index to track 32 bit max data length                                                                   
   if(src==NULL)                                    //tests for input data.  Cannot detect if length exceeds 2^32-1
   {
       printf("\n\n\t\tError, move failed. Recheck Source pointer and/or the length");
       return 1;
   }    
   if(length>abs(dst-src))
       printf("\n\n\t\tThere's an overlap. Source data will be corrupted. However, the move can occur and source data will be present in the destination.");

//the following lines are written assuming there's an overlap. Works just fine if there isn't one.
   if(dst-src>0)                                                                                                          
   {   
       for(index=1; index<=length; index++)                              //this will cover overlap cases like dst=src+k |k<length 
       {                                                                 //start from the top
          *(dst+length-index)=*(src+length-index);                  
       }
     
   }
   else if(dst-src<0)                      
   {   
       for(index=0; index<length; index++)                               //this will cover overlap cases like src=dst+k |k<length
       {                                               			 //start from the bottom
         *(dst+index)=*(src+index);       
       }
    }
   else                                                              
       dst=src;
   return 0;                                                              //succesful move
}





/*Function to initialize the memory to zero from the source address to the length specified*/
uint8_t my_memzero(uint8_t* src, uint32_t length)
{
    if(src==NULL)                                      //tests for input data.
   {
       printf("\n\n\t\tError, move failed. Recheck Source pointer");
       return 1;
   }
   uint32_t index;
   for(index=0; index<length; index++)
   {
      *(src+index)=0;
   }
} 






/*Function to reverse the consecutive memory bytes starting from the source address till the length specified*/
uint8_t my_reverse(uint8_t* src, uint32_t length)
{

        if(src==NULL) //Failure. The length and/or the address passed are incorrect.
                return 2;
        uint32_t index; //index to run the For loop below.
        uint8_t temp; //temp variable to facilitate exchange
      
       
        for(index=0;index<length/2;index++) //method to reverse the string; exchange elements //about the mid-point
        {
                temp=*(src+index);
                *(src+index)=*(src+length-(index+1));
                *(src+length-(index+1))=temp;
        }
        return 0;
}
