/* 
   Jonas da Silva
   119289334
   jdasilva
*/
#include <stdio.h>
#include <string.h>
#include <sysexits.h>
#include <stdlib.h>
#include <ctype.h>
#include "document.h"
#define MAX_LINE_LEN 1024

int main(int argc, char *argv[]){
  FILE *input;
  Document doc;
  char line[MAX_LINE_LEN], func[MAX_LINE_LEN],
    paragraph_number_string[MAX_LINE_LEN], line_number_string[MAX_LINE_LEN],
    doc_line[MAX_LINE_LEN], test[MAX_LINE_LEN], *doc_line_pointer, 
    file_name[MAX_LINE_LEN], replacement[MAX_LINE_LEN + 2], 
    target[MAX_LINE_LEN + 2];
  int paragraph_number, line_number, i, j, k;

  /*initializes document*/
  init_document(&doc, "main_document");
  if(argc == 1){
    input = stdin;
  }
  else if(argc == 2){
    input = fopen(argv[1], "r");
    if(input == NULL){
      fprintf(stderr, "%s cannot be opened.\n", argv[1]);
      return EX_OSERR;
    }
  }
  else{
    fprintf(stderr, "Usage: user_interface\nUsage: user_interface <filename>");
    return EX_USAGE;
  }

  while(fgets(line, MAX_LINE_LEN + 1, input) != NULL){
    if(argc == 1){
      printf("> ");
    }
    sscanf(line, "%s %s", func, paragraph_number_string);
    /*determines if blank line*/
    for(i = 0; line[i]; i++){
      if(!isspace(line[i])){
	i = -1;
	break;
      }
    }
    /*does not process comments or blank lines*/
    if(*func == '#' || i > 0){            
      continue;
    }

    /*replaces \n with null character*/
    line[strlen(line) - 1] = '\0';
    /*adds paragraph to document*/
    if(strcmp(func, "add_paragraph_after") == 0){
      sscanf(line, "%s %s", func, paragraph_number_string);
      /* checks if paragraph number is a integer*/
      for(i = 0; i < strlen(paragraph_number_string); i++){
	if(!isdigit(paragraph_number_string[i])){
	  printf("Invalid Command\n");
	  i = -1;
	  break;
	}
      }
      if(i == -1){
	continue;
      }
      /*checks if right amount of values are read, paragraph number is
	not negative and if add paragraph function was successful*/
      paragraph_number = atoi(paragraph_number_string);
      if(sscanf(line, "%s %s %s", func, paragraph_number_string, test)
	 != 2 || paragraph_number < 0){
	printf("Invalid Command\n");
      }
      else if(add_paragraph_after(&doc, paragraph_number) == FAILURE){
	printf("add_paragraph_after failed\n");
      }
           
    }

    /*adds line after specified line*/
    else if(strcmp(func, "add_line_after") == 0){
      sscanf(line, "%s %s %s %s", func, paragraph_number_string,
	     line_number_string, doc_line);
      /*checks if paragraph number and line number are integers*/
      for(i = 0; i < strlen(paragraph_number_string); i++){
	if(!isdigit(paragraph_number_string[i])){
	  printf("Invalid Command\n");
	  i = -1;
	  break;
	}
      }
      if(i == -1){
	continue;
      }
      for(i = 0; i < strlen(line_number_string); i++){
	if(!isdigit(paragraph_number_string[i])){
	  printf("Invalid Command\n");
	  i = -1;
	  break;
	}
      }
      if(i == -1){
	continue;
      }

      paragraph_number = atoi(paragraph_number_string);
      line_number = atoi(line_number_string);
      doc_line_pointer = strstr(line, doc_line);
      /*checks if paragraph number isn't 0 or negative, line number is 
	positive, if any values are missing, and if '*' is missing*/
      if(paragraph_number < 1 || line_number < 0 || *doc_line_pointer != '*'){
	printf("Invalid Command\n");
      }
      else if(add_line_after(&doc, paragraph_number, line_number, 
			     doc_line_pointer + 1) == FAILURE){
	printf("add_line_after failed\n");
      }
    }

    else if(strcmp(func, "print_document") == 0){
      /*checks for anything after command*/
      if(sscanf(line, "%s %s", func, test) != 1){
	printf("Invalid Command\n");
      }
      else{
	print_document(&doc);
      }
    }

    /*exits function if there are no strings after the command*/
    else if(strcmp(func, "quit") == 0){
      if(sscanf(line, "%s %s", func, paragraph_number_string) == 1){
	return 0;
      }
      else{
	printf("Invalid Command\n");
      }
    }
    /*same as quit*/
    else if(strcmp(func, "exit") == 0){
      if(sscanf(line, "%s %s", func, paragraph_number_string) == 1){
	return 0;
      }
      else{
	printf("Invalid Command\n");
      }
    }

    /*appends line to the specified paragraph*/
    else if(strcmp(func, "append_line") == 0){
      sscanf(line, "%s %s %s", func, paragraph_number_string, doc_line);
      /*checks if paragraph number is a integer*/
      for(i = 0; i < strlen(paragraph_number_string); i++){
	if(!isdigit(paragraph_number_string[i])){
	  printf("Invalid Command\n");
	  i = -1;
	  break;
	}
      }
      if(i == -1){
	continue;
      }
      paragraph_number = atoi(paragraph_number_string);
      doc_line_pointer = strstr(line, doc_line);

      /*checks if any values are missing, paragraph number isn't
	negative or 0, and if '*' is missing*/
      if( paragraph_number < 1 || *doc_line_pointer 
	  != '*'){
	printf("Invalid Command\n");
      }
      else if(append_line(&doc, paragraph_number, doc_line_pointer + 1)
	      == FAILURE){
	printf("append_line failed\n");
      }
    }

    else if(strcmp(func, "remove_line") == 0){
      sscanf(line, "%s %s %s", func, paragraph_number_string,
	     line_number_string);
      /*checks if paragraph number and line number are integers*/
      for(i = 0; i < strlen(paragraph_number_string); i++){
	if(!isdigit(paragraph_number_string[i])){
	  printf("Invalid Command\n");
	  i = -1;
	  break;
	}
      }
      if(i == -1){
	continue;
      }
      for(i = 0; i < strlen(line_number_string); i++){
	if(!isdigit(paragraph_number_string[i])){
	  printf("Invalid Command\n");
	  i = -1;
	  break;
	}
      }
      if(i == -1){
	continue;
      }

      paragraph_number = atoi(paragraph_number_string);
      line_number = atoi(line_number_string);
      /*checks if correct amount of values are present, nothing appears 
	after line number and the paragraph and line number are not 
	negative or 0*/
      if(sscanf(line, "%s %s %s %s", func, paragraph_number_string, 
		line_number_string, test) != 3 || paragraph_number < 1 ||
	 line_number < 1){
	printf("Invalid Command\n");
      }
      else if(remove_line(&doc, paragraph_number, line_number) == FAILURE){
	printf("remove_line failed\n");
      }

    }

    /*loads specified file to current document*/
    else if(strcmp(func, "load_file") == 0){
      sscanf(line, "%s %s", func, file_name);
      /*checks if file name is missing or value after file name appears*/
      if(sscanf(line, "%s %s %s", func, file_name, test) != 2){
	printf("Invalid Command\n");
      }
      else if(load_file(&doc, file_name) == FAILURE){
	printf("load_file failed\n");
      }
    }

    /*replaces target text with replacement text*/
    else if(strcmp(func, "replace_text") == 0){
      /*checks if target or replacement is missing and adds them to 
	arrays*/
      for(i = strlen(func), j = 0; line[i]; i++){
	if(j == 1){
	  target[k] = line[i];
	  k++;
	}
	if(j == 3){
	  replacement[k] = line[i];
	  k++;
	}
	if(line[i] == '\"'){
	  j++;
	  k = 0;
	}
      }
      if(j != 4){
	printf("Invalid Command\n");
	continue;
      }
      target[strlen(target) - 1] = '\0';
      replacement[strlen(replacement) - 1] = '\0';
          
      if(replace_text(&doc, target, replacement) == FAILURE){
	printf("replace_text failed\n");
      }
    }

    /*highlights specified text*/
    else if(strcmp(func, "highlight_text") == 0){
      /*checks if target is missing and adds it to an array*/
      for(i = strlen(func), j = 0, k = 0; line[i]; i++){
	if(j == 1){
	  target[k] = line[i];
	  k++;
	}
	if(line[i] == '\"'){
	  j++;
	}
      }
      if(j != 2){
	printf("Invalid Command\n");
	continue;
      }
      target[strlen(target) - 1] = '\0';
      highlight_text(&doc, target);

    }

    /*removes specified text*/
    else if(strcmp(func, "remove_text") == 0){
      /*checks if target is missing and adds it to an array*/
      for(i = strlen(func), j = 0, k = 0; line[i]; i++){
	if(j == 1){
	  target[k] = line[i];
	  k++;
	}
	if(line[i] == '\"'){
	  j++;
	}
      }
      if(j != 2){
	printf("Invalid Command\n");
	continue;
      }
      target[strlen(target) - 1] = '\0';
      remove_text(&doc, target);
    }

    /*saves document to specified file*/
    else if(strcmp(func, "save_document") == 0){
      /*checks if there are the right amount of arguments*/
      if(sscanf(line, "%s %s %s", func, file_name, test) != 2){
	printf("Invalid Command\n");
	continue;
      }
      else if(save_document(&doc, file_name) == FAILURE){
	printf("save_document failed\n");
      }
    }

    /*resets document*/
    else if(strcmp(func, "reset_document") == 0){
      sscanf(line, "%s", func);
      if(sscanf(line, "%s %s", func, test) != 1){
	printf("Invalid Command\n");
      }
      else{
	reset_document(&doc);
      }
    }
  }

  return 0;
}

