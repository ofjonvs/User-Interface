/* 
   Jonas da Silva
   119289334
   jdasilva
*/

#include "document.h"
#include <stdio.h>
#include <string.h>

/*Initializes the document to be empty.  
  initialize the document’s name based on the provided parameter value.*/
int init_document(Document *doc, const char *name){
  int i;

  if(doc == NULL || name == NULL || strlen(name) > MAX_STR_SIZE){
    return FAILURE;
  }
  for(i = 0; name[i] != '\0'; i++){
    doc->name[i] = name[i];
  }
  doc->number_of_paragraphs = 0;
  return SUCCESS;
}

/*Sets the number of paragraphs to 0*/
int reset_document(Document *doc){
  if(doc == NULL){
    return FAILURE;
  }
  doc->number_of_paragraphs = 0;
  return SUCCESS;
}

/*Prints the document’s name, number of paragraphs, followed by the paragraphs*/
int print_document(Document *doc){
  int i, j, k;

  if(doc == NULL){
    return FAILURE;
  }

  printf("Document name: \"%s\"\n", doc->name);
  printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
    
  /*Prints out lines letter by letter. Adds space when new paragraph is read*/
  for(i = 0; i < doc->number_of_paragraphs; i++){
    for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
      for(k = 0; doc->paragraphs[i].lines[j][k] != '\0'; k++){
	printf("%c", doc->paragraphs[i].lines[j][k]);
      }
      printf("\n");
    }
    if(j == 0){
      continue;
    }
    if(i < doc->number_of_paragraphs - 1){
      printf("\n");
    }
  }

  return SUCCESS;
}

/*Adds a paragraph after the specified paragraph number*/
int add_paragraph_after(Document *doc, int paragraph_number){
  if(doc == NULL || doc->number_of_paragraphs == MAX_PARAGRAPHS
     || paragraph_number > (doc->number_of_paragraphs)){
    return FAILURE;
  }

  doc->number_of_paragraphs += 1;
  return SUCCESS;
}

/*Adds a new line after the line with the specified line number*/
int add_line_after(Document *doc, int paragraph_number, int line_number,
		   const char *new_line){
  int i, j;

  if(doc == NULL || paragraph_number > (doc->number_of_paragraphs) + 1
     || doc->paragraphs[paragraph_number - 1].number_of_lines < line_number){
    return FAILURE;
  }

  /* creates open line at line number by moving other lines up */
  for(i = line_number; doc->paragraphs[paragraph_number - 1].lines[i][0]
	!= '\0' ;i++){}
  for(; i > line_number; i--){
    for(j = 0; doc->paragraphs[paragraph_number - 1].lines[i - 1][j] != 0
	  ; j++){
      doc->paragraphs[paragraph_number - 1].lines[i][j]
	= doc->paragraphs[paragraph_number - 1].lines[i - 1][j];
      doc->paragraphs[paragraph_number - 1].lines[i - 1][j] = '\0';
    }
    doc->paragraphs[paragraph_number - 1].lines[i][j] = '\0';
  }

  /*if current line is empty, set it equal to new line*/
  if(doc->paragraphs[paragraph_number - 1].lines[line_number][0] == '\0'){
    for(i = 0; new_line[i] != '\0'; i++){
      doc->paragraphs[paragraph_number - 1].lines[line_number][i] = 
	new_line[i];
    }
  }
  /*else copy current to line above and set it equal to new line*/
  else{
    for(i = (doc->paragraphs[paragraph_number - 1].number_of_lines) + 1; 
        i > line_number; i-- ){
      for(j = 0; doc->paragraphs[paragraph_number - 1].lines[i][j] != '\0';
	  j++){
	doc->paragraphs[paragraph_number - 1].lines[i + 1][j] =
	  doc->paragraphs[paragraph_number - 1].lines[i][j];
      }
    }
    for(i = 0; new_line[i] != '\0'; i++){
      doc->paragraphs[paragraph_number - 1].lines[line_number][i] = 
	new_line[i];
    }
  }
  doc->paragraphs[paragraph_number - 1].number_of_lines += 1;

  return SUCCESS;
}

/*Returns the number of lines in a paragraph*/
int get_number_lines_paragraph(Document *doc, int paragraph_number, 
			       int *number_of_lines){
  if(doc == NULL || number_of_lines == NULL || 
     paragraph_number > doc->number_of_paragraphs){
    return FAILURE;
  }

  *number_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
  return SUCCESS;
}

/*Appends a line to the specified paragraph*/
int append_line(Document *doc, int paragraph_number, const char *new_line){
  int i;
  if(doc == NULL || paragraph_number > (doc->number_of_paragraphs) + 1){
    return FAILURE;
  }

  /*sets top line of paragraph to new line*/
  for(i = 0; new_line[i] != '\0'; i++){
    doc->paragraphs[paragraph_number - 1].lines[doc->paragraphs
						[paragraph_number - 1].number_of_lines][i]
      = new_line[i];
  }
  doc->paragraphs[paragraph_number - 1].number_of_lines += 1;
  return SUCCESS;
}

/*Removes the specified line from the paragraph*/
int remove_line(Document *doc, int paragraph_number, int line_number){
  int i, j;

  if(doc == NULL || paragraph_number > MAX_PARAGRAPHS -
     (doc->number_of_paragraphs) || line_number > 
     doc->paragraphs[paragraph_number - 1].number_of_lines){
    return FAILURE;
  }

  /*sets line number to null characters*/
  for(i = 0; doc->paragraphs[paragraph_number - 1].lines[line_number - 1][i]
	!= '\0'; i++){
    doc->paragraphs[paragraph_number - 1].lines[line_number - 1][i] = '\0';
  }
  /*moves above lines down*/
  for(i = line_number - 1; i < doc->paragraphs[paragraph_number - 1].number_of_lines
	; i++){
    for(j = 0; doc->paragraphs[paragraph_number - 1].lines[i + 1][j] != '\0'
	  ; j++){
      doc->paragraphs[paragraph_number - 1].lines[i][j] 
	= doc->paragraphs[paragraph_number - 1].lines[i + 1][j]; 
    }
    while(doc->paragraphs[paragraph_number - 1].lines[i][j] != '\0'){
      doc->paragraphs[paragraph_number - 1].lines[i][j] = '\0';
      j++;
    }
  }
  doc->paragraphs[paragraph_number - 1].number_of_lines -= 1;

  return SUCCESS;
}

/*The function will add the first data lines number of lines from the data 
  array to the document*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines){
  int i, j, k = 1, l = 0;

  if(doc == NULL || data == NULL || data_lines == 0){
    return FAILURE;
  }

  doc->number_of_paragraphs += 1;
    
  /*finding number of paragraphs*/
  for(i = 0; i < data_lines; i++){
    if(strcmp(data[i], "") == 0){
      doc->number_of_paragraphs += 1; 
      k++;
    }
  }

  /*moves paragraphs down for n number of new paragraphs*/
  for(i = 0; i < k ; i++){
    for(j = doc->number_of_paragraphs - 1; j > 0; j--){
      doc->paragraphs[j] = doc->paragraphs[j - 1];
    }
  }

  /*writes data to open paragraphs and seperates by empty string*/
  j = 0;
  doc->paragraphs[j].number_of_lines = 0;
  for(i = 0; i < data_lines; i++){
    if(strcmp(data[i], "") == 0){
      j++;
      doc->paragraphs[j].number_of_lines = 0;
      l = 0;
      continue;
    }
  
    for(k = 0; data[i][k] != '\0'; k++){
      doc->paragraphs[j].lines[l][k] = data[i][k];   
    }
    doc->paragraphs[j].lines[l][k] = '\0';
    l++;
    doc->paragraphs[j].number_of_lines += 1;
       
              
  }


  return SUCCESS;
}

/*replaces a target string with replacement string in specified line*/
void repl_str(char *line, const char *target, const char *replacement) 
{
  int target_len = strlen(target), replace_len = strlen(replacement);
  char buffer[MAX_STR_SIZE];
  char *insert_point = buffer;
  const char *tmp = line;

  /*loops through until target is no longer substring of updated line*/
  while(100){
    const char *p = strstr(tmp, target);
    if (p == NULL) {
      strcpy(insert_point, tmp);
      break;
    }   
    strncpy(insert_point, tmp, p - tmp);
    insert_point += p - tmp;
    strncpy(insert_point, replacement, replace_len);
    insert_point += replace_len;
    tmp = p + target_len;	
  }
  strcpy(line, buffer);

}

/*replace the text target with the text replacement
  everywhere it appears in the document*/
int replace_text(Document *doc, const char *target, const char *replacement){
  int i, j;
    

  if(doc == NULL || target == NULL || replacement == NULL){
    return FAILURE;
  }

  /*loops through every line of document and calls repl_str function*/
  for(i = 0; i < doc->number_of_paragraphs; i++){
    for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
      repl_str(doc->paragraphs[i].lines[j], target, replacement);
    }
  }

  return SUCCESS;
}

/*The function will highlight the text associated with 
  target everywhere it appears in the document*/
int highlight_text(Document *doc, const char *target){
  int i;
  char temp_array[MAX_STR_SIZE + 1] = HIGHLIGHT_START_STR;

  /*creates a string of target string and surrounds 
    it with highlight string*/
  for(i = 0; target[i] != '\0'; i++){
    temp_array[i + 1] = target[i];
  }
  temp_array[i + 1] = HIGHLIGHT_END_STR[0];
    
  /*calls replace text function with surrounded array as replacement
    and target parameter as string to be replaced*/
  replace_text(doc, target, temp_array);

  return SUCCESS;
}



/*The function will remove the text target everywhere it appears in the 
  document*/
int remove_text(Document *doc, const char *target){

  if(doc == NULL || target == NULL){
    return FAILURE;
  }

  /*calls replace text function with target parameter as the target and 
    empty string as replacement*/
  replace_text(doc, target, "");

  return SUCCESS;
}

/*loads document from file*/
int load_file(Document *doc, const char *filename){
  int i, j, blank_line = 0;
  FILE *file;
  char file_array[MAX_PARAGRAPHS * MAX_PARAGRAPH_LINES + MAX_PARAGRAPHS]
    [MAX_STR_SIZE + 1];

  file = fopen(filename, "r");
  if(file == NULL || doc == NULL || filename == NULL){
    return FAILURE;
  }

  /*reads line from file, loops until end of file is detected*/
  fgets(file_array[0], MAX_STR_SIZE + 1, file); 
  for(i = 0; !feof(file); i++){
    /*if a it is a blank line, blank line variable will be 0*/
    blank_line = 0;
    for(j = 0; file_array[i][j]; j++){
      if(!isspace(file_array[i][j])){
        blank_line = 1;
      }
    }
    if(!blank_line){
      strcpy(file_array[i], "");
    }
    else{
      file_array[i][strlen(file_array[i]) - 1] = '\0';
    }
    /*reads next line of file to array*/
    fgets(file_array[i + 1], MAX_STR_SIZE + 1, file); 
  }
  fclose(file);
  /*calls load document using array created from file*/
  load_document(doc, file_array, i);
  return SUCCESS;
}

/*saves document into output file*/
int save_document(Document *doc, const char *filename){
  FILE *output = fopen(filename, "w");
  int i, j;
  char temp_array[MAX_STR_SIZE + 1];

  if(doc == NULL || filename == NULL || output == NULL){
    return FAILURE;
  }

  /*copies line by line into output file in proper format*/
  for(i = 0; i < doc->number_of_paragraphs; i++){
    for(j = 0; j < doc->paragraphs[i].number_of_lines; j++){
      strcpy(temp_array, doc->paragraphs[i].lines[j]);
      fputs(temp_array, output);
      fputs("\n", output);
    }
    fputs("\n", output);
  }

  fclose(output);
  return SUCCESS;
}
