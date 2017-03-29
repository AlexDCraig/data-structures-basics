#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct animalTree
{
	char** questions;
	// The root of the tree is the string at questions[0]
};

void _initializeTree(struct animalTree* myTree)
{
	myTree->questions = malloc(sizeof(char*) * 15);
	char** temp = myTree->questions;
	temp[0] = "Can it fly?";
	temp[1] = "Does it have feathers?";
	temp[2] = "Is it very small?";
	temp[3] = "Is it a bird?";
	temp[4] = "Is it a biological specimen?";
	temp[5] = "Is it a dog?";
	temp[6] = "Is it a dinosaur?";
	temp[7] = "Is it a pigeon?";
	temp[8] = "Is it an owl?";
	temp[9] = "Is it a non-bird but a bird-like creature?";
	temp[10] = "Is it an alien organism?";
	temp[11] = "Is it a pitbull?";
	temp[12] = "Is it a cat?";
	temp[13] = "Is it a T-Rex?";
	temp[14] = "Is it a squirrel?";
	temp[15] = "You're thinking of a pigeon!";
	temp[16] = "You're thinking of an eagle!";
	temp[17] = "You're thinking of an owl!";
	temp[18] = "You're thinking of an owl-like creature!";
	temp[19] = "You're thinking of a non-bird bird-like creature!";
	temp[20] = "You're thinking of an alien creature.";
	temp[21] = "You're thinking of Predator!";
	temp[22] = "You're thinking of a creature yet to be discovered.";
	temp[23] = "You're thinking of a pitbull!";
	temp[24] = "You're thinking of a boxer!";
	temp[25] = "You're thinking of a cat!";
	temp[26] = "You're thinking of a Traflamadorian!";
	temp[27] = "You're thinking of a T-Rex!";
	temp[28] = "You're thinking of a velociraptor!";
	temp[29] = "You're thinking of a squirrel!";
	temp[30] = "You're thinking of a chipmunk!";
}

struct animalTree* createTree()
{
	struct animalTree* myTree = malloc(sizeof(struct animalTree));
	_initializeTree(myTree);
	return myTree;
}

int jumpToLeftChild(int index)
{
	return (index * 2) + 1;
}

int jumpToRightChild(int index)
{
	return (index * 2) + 2;
}

void playGame(struct animalTree* myTree)
{
	int index = 0; // there are 15 possible indices (up to 14)
	int answer;

	printf("\n***** ANIMAL GAME: *****");
	printf("\nRULES: Enter 1 for Yes, 0 for No.");
	printf("\n");

	while (index <= 30)
	{
		printf("%s", myTree->questions[index]);
		printf("\n");

		if (index > 14)
			break;

		printf("\n");
		scanf("%d", &answer);

		if (answer == 1)
			index = jumpToLeftChild(index);
	
		else if (answer == 0)
			index = jumpToRightChild(index);

		else
		{
			printf("\nInvalid answer. Exiting program...\n");
			exit(1);
		}		
	}	
			
}

int main()
{
	struct animalTree* myTree = createTree();
	playGame(myTree);
	return 0;
}	
