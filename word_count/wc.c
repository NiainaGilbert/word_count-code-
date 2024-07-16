#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int wc_line (char *option)
{
	char chara ;
	int line =0;
	FILE *fichier;
	fichier=fopen ( option, "r");
	do
		{
			chara=fgetc(fichier);
			if (chara=='\n')
				{
					line++;
				}
		}
	while (chara!=EOF);	
	fclose(fichier);
	return (line);
}
int wc_char (char *option)
{
	char chara ;
	int i =0;
	FILE *fichier;
	fichier=fopen ( option, "r");
	do
		{
			chara=fgetc(fichier);
			i++;
		}
	while (chara!=EOF);	
	fclose(fichier);
	return (i);
}
int wc_word (char *option)
{
	char chara , *str;
	int j=0, k=0, word=0;
	FILE *fichier;
	str=(char *)malloc(500*sizeof(char));
	fichier=fopen ( option, "r");
	do
		{	
			str=fgets(str, 500, fichier);
			for (k=0;k<strlen(str);k++)
				{
					if ((str[k]==' ' || str[k]=='\t' || str[k]=='\n' )&& str[k+1]!=' ')
						word++;
				}
			j++;
		}
	while (j<wc_line (option));
	free(str);
	fclose(fichier);
	return (word);
}
int wc_line_length (char *option)
{
	char chara , *str, *max;
	int j=0, k=0, word=0;
	FILE *fichier;
	str=(char *)malloc(500*sizeof(char));
	max=(char *)malloc(500*sizeof(char));
	fichier=fopen ( option, "r");
	max=fgets(str, 500, fichier);
	rewind(fichier);
	for (j=0;j<wc_line (option);j++)
		{	
			str=fgets(str, 500, fichier);
			if(strlen(str)>=strlen(max))
				k=strlen(str);

		}
	free(str);
	fclose(fichier);
	return (k);
}
void wc_files (char *option)
{
	char chara ;
	int line =0;
	FILE *fichier;
	fichier=fopen ( option, "r");
	do
		{
			chara=fgetc(fichier);
			if (chara=='\n')
				{
					line++;
				}
		}
	while (chara!=EOF);	
	fclose(fichier);
}
void word_count(int nb_option, char *options[])
{
	int i=0, k=0, sum_line=0, sum_word=0, sum_char=0;
	if(nb_option==2)
		{
			if (strcmp(options[1],"--help")==0)
				printf("Usage: wc [OPTION]... [FILE]...\n  or:  wc [OPTION]... --files0-from=F\nPrint newline, word, and byte counts for each FILE, and a total line if\nmore than one FILE is specified.  A word is a non-zero-length sequence of\ncharacters delimited by white space.\n\nWith no FILE, or when FILE is -, read standard input.\n\nThe options below may be used to select which counts are printed, always in\nthe following order: newline, word, character, byte, maximum line length.\n  -c, --bytes            print the byte counts\n  -m, --chars            print the character counts\n  -l, --lines            print the newline counts\n      --files0-from=F    read input from the files specified by\n                           NUL-terminated names in file F;\n                           If F is - then read names from standard input\n  -L, --max-line-length  print the maximum display width\n  -w, --words            print the word counts\n      --help     display this help and exit\n      --version  output version information and exit\n");
			else if (strcmp(options[1],"--version")==0)
				printf("This is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Rakotoarison Niaina Gilbert.\n");
			else
				printf("%d %d %d %s\n",wc_line(options[1]), wc_word(options[1]), (wc_char(options[1])-1), options[1]);
		}

	else if (nb_option==3 && (strcmp(options[1],"-c")==0 || strcmp(options[1],"--bytes")==0))
			printf("%d %s\n",(wc_char(options[2])-1), options[2]);
	else if (nb_option==3 && (strcmp(options[1],"-m")==0 || strcmp(options[1],"--chars")==0))
			 printf("%d %s\n",(wc_char(options[2])-1), options[2]);
	else if (nb_option==3 && (strcmp(options[1],"-l")==0 || strcmp(options[1],"--lines")==0))
			 printf("%d %s\n",(wc_line(options[2])-1), options[2]);
	else if (nb_option==3 && (strcmp(options[1],"-w")==0 || strcmp(options[1],"--words")==0))
			 printf("%d %s\n",(wc_word(options[2])-1), options[2]);
	else if (nb_option==3 && (strcmp(options[1],"-L")==0 || strcmp(options[1],"--max-line-length")==0))
			 printf("%d %s\n",wc_line_length(options[2])+1, options[2]);
	else if (nb_option==3 && (strcmp(options[1],"--files0-from=")==0 || strcmp(options[1],"--files0-from")==0))
			 wc_files (options[2]);
	else if (nb_option>=3)
			{
				for (k=2;k<nb_option;k++)
					{
						for (i=0;i<strlen(options[1]);i++)
							{
							switch(options[1][i]) 
								{
									case 'c' :
										printf(" %d", wc_char(options[k]));
										break;
									case 'm' :
										printf(" %d", wc_char(options[k]));
										break;
									case 'l' :
										printf(" %d", wc_line(options[k]));
										break;
									case 'w' :
										printf(" %d ", wc_word(options[k]));
										break;
									case 'L' :		
										printf(" %d ", wc_line_length(options[k])+1);
										break;
								}
							
							}
							printf(" %s\n",options[k]);
					}
		}
	else if(nb_option>=3)
		{
			for (i=1; i<nb_option; i++)
				{
					printf("%d %d %d %s\n",wc_line(options[i]), wc_word(options[i]), (wc_char(options[i])-1), options[i]);
					sum_line+=wc_line(options[i]);
					sum_word+=wc_word(options[i]);
					sum_char+=(wc_char(options[i])-1);
				}
			printf("%d %d %d total\n",sum_line, sum_word, sum_char);
		}
	else 
		printf("Enter wc --help\n");
}
