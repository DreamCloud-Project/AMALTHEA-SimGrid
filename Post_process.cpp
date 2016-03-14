#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


int main()//int argc, char *argv[]
{
  
  int size_line = 200;
  char line[200];
  FILE *fp_r_1;
  FILE *fp_w_1;

  int start_marker1_found=0;
  int end_marker1_found=0;
  int start_marker2_found=0;

  const char*m1 = "Start_marker_1";
  const char* m2 = "End_marker_1";
  const char* m3 = "Start_marker_2";
  char search_marker[50];
  //char s1[50];
  //char s2[50];
  char s3[50];
  char s4[50];
  char s5[50];
  char s6[50];
  char s7[50];
  char s8[50];
  char s9[50];
  char time_stmp;;



  fp_r_1 = fopen("./Buffer/Output.out" , "r");
  if(fp_r_1 == NULL) 
    {
      perror("Output.out not found in the specified directory");
      return(-1);
    }

  while(!start_marker1_found)
    {
      fgets (line, size_line, fp_r_1);
      sscanf(line, "%s", search_marker);
      start_marker1_found = !strcmp (search_marker,m1); //strcmp returns 0 if the strings are equal
    }


  //Execution traces
  fp_w_1 = fopen("./OUTPUT_FILES/Execution_trace.out" , "w");
  if(fp_w_1 == NULL) 
    {
      perror("Execution_trace.out not found in the specified directory");
      return(-1);
    }

   while(!end_marker1_found)
    {
      fgets (line, size_line, fp_r_1);
      sscanf(line, "%s", search_marker);
      end_marker1_found = !strcmp (search_marker,m2); //strcmp returns 0 if the strings are equal
      if(!end_marker1_found){
	fprintf(fp_w_1, "%s",line);
      }
      
    }
  fclose(fp_w_1);
  

  //Energy
  fp_w_1 = fopen("./OUTPUT_FILES/Energy.out" , "w");
  if(fp_w_1 == NULL) 
    {
      perror("Energy.out not found in the specified directory");
      return(-1);
    }
  while(!start_marker2_found)
    {
      fgets (line, size_line, fp_r_1);
      sscanf(line, "%s", search_marker);
      start_marker2_found = !strcmp (search_marker,m3); //strcmp returns 0 if the strings are equal
    }

  while(fgets(line, size_line, fp_r_1)!=NULL)
    {

      sscanf(line,"%c", &time_stmp);
      if(time_stmp=='['){
	sscanf(line, "%*s %*s %s %s %s %s %s %s %s", s3, s4, s5, s6, s7, s8, s9);
	if(s7[5]!='M'){
	  fprintf(fp_w_1, "%s %s %s %s %s %s %s\n", s3, s4, s5, s6, s7, s8, s9);
	}
      }
      else{
	fprintf(fp_w_1, "%s", line);
      }
    }
  
  /*
   time_t rawtime;
   struct tm *info;
   int UTC2 = 2;
   time(&rawtime);
   // Get GMT time 
   info = gmtime(&rawtime );
   
   printf("File generated on %d/%d/%d at %2d:%02d:%02d\n",info->tm_mday, info->tm_mon,info->tm_year,(info->tm_hour+UTC2)%24, info->tm_min, info->tm_sec);
   //printf("Montpellier : %2d:%02d\n", (info->tm_hour+UTC1)%24, info->tm_min);
   //printf("Montpellier : %2d:%02d\n", (info->tm_hour+BST)%24, info->tm_min);
   //printf("China  : %2d:%02d\n", (info->tm_hour+CCT)%24, info->tm_min);
   */
  fclose(fp_w_1);
  fclose(fp_r_1);
  
  return 0;
}
