#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>



#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
  char name[50];//Caution the true size of the name has to be smaller than the size of the char array!!!
  int   alias;
}Name_Alias;

typedef struct
{
  char* host_name;
  char* thread_name;
  char* time_stamp;
  int free;
}Link_source;

const char* a1 = "Receiving";
const char* a2 = "Received";
const char* a3 = "Sending";
const char* a4 = "Sent";
const char* a5 = "Executing";
const char* a6 = "Executed";
const char* a7 = "Writing";
const char* a8 = "Written";
const char* a9 = "Reading";
const char* a10 = "Read";
const char* a11 = "Sleeping";
const char* a12 = "Slept";


int Which_action(char* action){

  if(strcmp(a1,action)==0){
    return 7;
  }
  else{
    if(strcmp(a2,action)==0){
      return -1;
    }
    else{
      if(strcmp(a3,action)==0){
	return 8;
      }
      else{
	if(strcmp(a4,action)==0){
	  return -1;
	}
	else{
	  if(strcmp(a5,action)==0){
	    return 9;
	  }
	  else{
	    if(strcmp(a6,action)==0){
	      return -1;
	    }
	    else{
	      if(strcmp(a7,action)==0){
		return 5;
	      }
	      else{
		if(strcmp(a8,action)==0){
		  return -1;
		}
		else
		  if(strcmp(a9,action)==0){
		    return 6;
		  }
		  else{
		    if(strcmp(a10,action)==0){
		      return -1;
		    }
		    else{
		      if(strcmp(a11,action)==0){
			return 10;
		      }
		      else{
			if(strcmp(a12,action)==0){
			  return -1;
			}
			else{
			  return 0;
			}
		      }
		    }
		  }
	      }
	    }
	  }
	}
      }
    }
  }
}



int main()//int argc, char *argv[]
{
  
  int size_line = 500;
  char line[500];
  FILE *fp_r_1;
  FILE *fp_r_2;
  int j;
  int i;
  int n_h;
  int n_t;
  int n_time;
  int n;
  int Nb_hosts;
  int found = 0;
  int extract_host_Nb=1;
  const char* p1 = "HOSTS:";
  char search_patern[50];
  char action[20];
  char marker[20];
 
  char* host_name;
  char* thread_name;
  char* time_stamp;
  int th_alias=40;
  float time_action;

  //Build a list of host names
  fp_r_1 = fopen("./OUTPUT_FILES/Simmulation_summary.out" , "r");
  if(fp_r_1 == NULL) 
    {
      perror("Simmulation_summary.out not found in the specified directory");
      return(-1);
    }
  // Find the number of hosts
  while(extract_host_Nb)
    {
      fgets (line, size_line, fp_r_1);
      sscanf(line, "%s", search_patern);
      extract_host_Nb = strcmp (search_patern,p1); //strcmp returns 0 if the strings are equal
    }
  sscanf(line, "%*s %d", &Nb_hosts);

  // Create the list of host names
  vector<Name_Alias> List_hosts;
  Name_Alias N_A;
  // Fill the list
  for(i=0;i<Nb_hosts;i++){
    fgets (line, size_line, fp_r_1);
    sscanf(line, "%s", search_patern);
    strcpy(N_A.name,search_patern);
    N_A.alias=i+7;
    List_hosts.push_back(N_A);
  }
  fclose(fp_r_1);
  
  // Record the threads associated to each Host
  vector< vector<Name_Alias> > Threads(Nb_hosts);
  
  fp_r_1 = fopen("./OUTPUT_FILES/Execution_trace.out" , "r");
  if(fp_r_1 == NULL) 
    {
      perror("Execution_trace.out not found in the specified directory");
      return(-1);
    }

  while(fgets (line, size_line, fp_r_1)!=NULL)
    {
      fgets (line, size_line, fp_r_1);
      if((line[0]=='[')&&(line[1]=='H')&&(line[2]=='O')&&(line[3]=='S')&&(line[4]=='T')){
	// Extrace the name of the host 
	n=1;
	while(line[n]!=':'){
	  n++;
	}
	
	n_h = n; //index of the first ':'
        host_name= (char *)calloc(n_h-1,sizeof(char));
	for(i=1;i<n_h;i++){
	  //str.push_back(line[i]);
	  host_name[i-1] = line[i];	  
	}

	// Get index i of the host_name in the List_h list
	i=0;
	while(strcmp(List_hosts[i].name,host_name)!=0){
	  i++;
	}

	// Extract the name of the thread
	while(line[n]!=')'){
	  n++;
	}
	n_t = n; //index of the ')'
        thread_name= (char *)calloc((n_t-n_h),sizeof(char));
	for(j=1;j<=(n_t-n_h);j++){
	  //str.push_back(line[i]);
	  thread_name[j-1] = line[n_h+j];	  
	}
	strcpy(N_A.name,thread_name);
	//Test presence of the thread_name in the list of threads of this host
	if(Threads[i].size()<1){
	  th_alias++;
	  N_A.alias = th_alias;
	  Threads[i].push_back(N_A);
	}
	
	else{
	  n=Threads[i].size();
	  j=0;
	  found=0;
	  while((j<n)&&(!found)){
	    found = (strcmp(Threads[i][j].name,thread_name)==0);
	    j++;
	  }
	  if(!found){
	    th_alias++;
	    N_A.alias = th_alias;
	    Threads[i].push_back(N_A);
	  }
	}
      }
    }

  fclose(fp_r_1);

  int i1=6;
  int i2=0;
  //int i3=7;
  int i4=2;
  int i5=0;

  int act1_push=12;
  int act1_pop=13;
  int act3=4;
  int w_act;
  int act_lsource=15;
  int act_ldest=16;
  int link_type=11;
  int l1=0;
  char lval[]="SR";

  fp_r_1 = fopen("./OUTPUT_FILES/simgrid.trace" , "a");
  if(fp_r_1 == NULL) 
    {
      perror("simgrid.trace not found in the specified directory");
      return(-1);
    }


  //Print the hosts
  for(i=0;i<Nb_hosts;i++){
    fprintf(fp_r_1, "%d %d %d %d %d %s\n", i1, i2, (List_hosts[i].alias), i4, i5, List_hosts[i].name);
  }

  
  //Create threads containers and print the threads
  int nb_th_in_host;
  for(i=0;i<Nb_hosts;i++){
    nb_th_in_host = Threads[i].size();
    j=0;
    while(j<nb_th_in_host){
      fprintf(fp_r_1, "%d %d %d %d %d %s\n", i1, i2,Threads[i][j].alias, i4, List_hosts[i].alias,Threads[i][j].name);
      j++;
    }
  }

  //Go through the Execution trace
  fp_r_2 = fopen("./OUTPUT_FILES/Execution_trace.out" , "r");
  if(fp_r_2 == NULL) 
    {
      perror("Execution_trace.out not found in the specified directory");
      return(-1);
    }


  while(fgets (line, size_line, fp_r_2)!=NULL)
    {
      //fgets (line, size_line, fp_r_2);
      if((line[0]=='[')&&(line[1]=='H')&&(line[2]=='O')&&(line[3]=='S')&&(line[4]=='T')){
	sscanf(line, "%*s %*s %*s %s",action);
	if((strcmp(action,a1)==0)||(strcmp(action,a2)==0)||(strcmp(action,a3)==0)||(strcmp(action,a4)==0)||(strcmp(action,a5)==0)||(strcmp(action,a6)==0)||(strcmp(action,a7)==0)||(strcmp(action,a8)==0)||(strcmp(action,a9)==0)||(strcmp(action,a10)==0)||(strcmp(action,a11)==0)||(strcmp(action,a12)==0)){
	  
	  //Extract name of host
	  n=1;
	  while(line[n]!=':'){
	    n++;
	  }
	  
	  n_h = n; //index of the first ':'
	  host_name= (char *)calloc(n_h-1,sizeof(char));
	  for(i=1;i<n_h;i++){
	    host_name[i-1] = line[i];	  
	  }
	  
	  // Get index i of the host_name in the List_h list
	  i=0;
	  while(strcmp(List_hosts[i].name,host_name)!=0){
	    i++;
	  }
	  
	  //Extract name of thread
	  while(line[n]!=')'){
	    n++;
	  }
	  n_t = n; //index of the ')'
	  thread_name= (char *)calloc((n_t-n_h),sizeof(char));
	  for(j=1;j<=(n_t-n_h);j++){
	    thread_name[j-1] = line[n_h+j];	  
	  }
	  

	  //Extract the time stamp
	  while(line[n]!=']'){
	    n++;
	  }
	  n_time = n;
	  time_stamp= (char *)calloc((n_time-n_t-2),sizeof(char));
	  for(j=1;j<=(n_time-n_t-2);j++){
	    time_stamp[j-1] = line[n_t+1+j];	  
	  }

	  //Find the thread index j in the Treads 2D vector
	  n=Threads[i].size();
	  j=0;
	  found=0;
	  while((j<n)&&(!found)){
	    found = (strcmp(Threads[i][j].name,thread_name)==0);
	    j++;
	  }
	  j--;

	  //Determine the time stamp
	  time_action=atof(time_stamp);

	  //Determine action
	  w_act = Which_action(action);

	  if(w_act==0){//error
	    cout<<"error in Which_action"<<endl;
	    return 1;
	  }
	  else{
	    if(w_act==-1){//pop
	      fprintf(fp_r_1, "%d %0.6f %d %d\n", act1_pop, time_action, act3, Threads[i][j].alias);
	    }
	    else{//push
	      fprintf(fp_r_1, "%d %0.6f %d %d %d\n", act1_push, time_action, act3, Threads[i][j].alias, w_act);
	    }
	  }
	}

	if(strcmp(action,a3)==0){//sending	  
	  sscanf(line, "%*s %*s %*s %*s %*s %s",marker);
	  fprintf(fp_r_1, "%d %0.6f %d %d %s %d %s\n", act_lsource, time_action, link_type, l1, lval, Threads[i][j].alias, marker);//source of the arrow
	}
	
	if(strcmp(action,a2)==0){//received
	  sscanf(line, "%*s %*s %*s %*s %*s %s",marker);
	  fprintf(fp_r_1, "%d %0.6f %d %d %s %d %s\n", act_ldest, time_action, link_type, l1, lval, Threads[i][j].alias, marker);//destination of the arrow
	}	
      }
    }
  fclose(fp_r_2);
  fclose(fp_r_1); //simgrid trace file for vite
  //Test
  /*
    for(i=0;i<Nb_hosts;i++){
    n=Threads[i].size();
    cout<<"Host: "<<List_hosts[i]<<endl;
    for(j=0;j<n;j++){
      cout<<" Thread: "<<Threads[i][j]<<endl;
    }
  }
  */
return 0;
}
