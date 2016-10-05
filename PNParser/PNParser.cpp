#include "stdafx.h"
#include <iostream>
//next three lines are necessary
//for detecting memory leaks
#define _CRTDBG_MAP_ALLOC	
#include <stdlib.h>
#include <crtdbg.h>

//my class that binds objects for running polish notation parser
#include "Evaluator.h"


int _tmain(int argc, _TCHAR* argv[])
{

	{						//point where parser is initialized and started	
		Evaluator ev;		//it is enclosed in curly brackets 
		ev.startParser();	//to ensure proper functioning of 						
	}						//"_CrtDumpMemoryLeaks"	tool

	system("pause");
	_CrtDumpMemoryLeaks();	//function to find memory leaks
	//if theres any leak it will be printed in the
	//output terminal

	return 0;
}

