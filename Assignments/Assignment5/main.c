#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"
#include <unistd.h>


int main (int argc, const char * argv[])
{
  //char cmd = ' ';
  DynArr* mainList = createDynArr(10);
  FILE *fp;
  char* fileName = 0;
  char cmd;

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
	cmd = ' ';
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n\n"
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');

	if (cmd == 'l') // load
	{
		if (fileName != 0)
		{
			printf("\nYou have requested a file load with another file already open. The currently opened file will be closed now.\n");
			fclose(fp);
			char* trashCollector = fileName;
			fileName = malloc(100 * sizeof(char));
			free(trashCollector);
		}

		else if (fileName == 0)
			fileName = malloc(100 * sizeof(char));		

		printf("\nPlease enter the name of the file.\n");
		scanf("%s", fileName);
		char* mode = "r"; // open for reading

		if (access(fileName, F_OK) != -1) // file exists
		{
			fp = fopen(fileName, mode); 
			loadList(mainList, fp);
			printf("\n%s has been loaded.\n \n", fileName);
		}

		else
		{
			printf("\nThat file does not yet exist. It will now be created and loaded.\n");
			FILE* fileToSaveTo;	
			char* mode = "w";
			
			char* fileNameForSave = fileName;
			
			fileToSaveTo = fopen(fileNameForSave, mode);

			printf("\n");
		
		}

		 
	}

	else if (cmd == 'p') // print
	{
		if (fileName == 0)
		{
			printf("\nERROR: No file has been loaded. If you would like to print tasks, first load a file in.\n");
			exit(1);
		}

		printf("\n");
		printList(mainList);
	}

	else if (cmd == 'a') // add
	{
		if (fileName == 0)
		{
			printf("\nERROR: No file has been loaded. If you would like to add a new task, first load a file in.\n");
			exit(1);
		}

		TYPE newTaskToAdd;

		printf("\nPlease enter the priority of the task.\n");
		int newTaskPriority;
		scanf("%d", &newTaskPriority);
		printf("\nPlease enter the description of the task.\n");
		char newTaskDescription[128];
		scanf("%s", newTaskDescription);		

		newTaskToAdd = createTask(newTaskPriority, newTaskDescription);	

		addHeap(mainList, newTaskToAdd, compare);

		printf("\nAdded to list: ");
		print_type(newTaskToAdd);
		printf("\n");
	}

	else if (cmd == 's') // save
	{
		if (fileName == 0)
		{
			printf("\nERROR: No file has been loaded. If you would like to save a list, first load a file in.\n");
			exit(1);
		}

		FILE* fileToSaveTo;	
		char* mode = "w";
		printf("\nPlease enter the name of the file to save to.\n");
		char fileNameForSave[100];
		scanf("%s", fileNameForSave);
		fileToSaveTo = fopen(fileNameForSave, mode);

		saveList(mainList, fileToSaveTo);
		printf("\nList has been updated in filename: %s", fileNameForSave);
		printf("\n");
	}

	else if (cmd == 'g') // get first task
	{
		if (fileName == 0)
		{
			printf("\nERROR: No file has been loaded. If you would like to get the first task, first load a file in.\n");
			exit(1);
		}

		printf("\nFirst task by priority in currently loaded file: \n");
		print_type(getMinHeap(mainList));
	}

	else if (cmd == 'r')
	{
		if (fileName == 0)
		{
			printf("\nERROR: No file has been loaded. If you would like to remove from the heap, first load a file in.\n");
			exit(1);
		}

		print_type(getMinHeap(mainList));
		printf("... has been removed from the heap.\n");
		removeMinHeap(mainList, compare);
	}

	else if (cmd != 'e')
		printf("\nYou've entered an invalid command.\n\n");

      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }

  while(cmd != 'e');

	if (fileName != 0);
		fclose(fp);

	printf("\nGoodbye.\n");
  /* delete the list */
 	 deleteDynArr(mainList);

  return 0;
}
