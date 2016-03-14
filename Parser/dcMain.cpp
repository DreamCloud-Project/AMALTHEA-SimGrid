// AmApplication.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <iomanip>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <set>
#include <cstdio>
#include "dcAmaltheaParser.h"
#include "AmApplication.h"
#include "dcApplication.h"
#include "dcConfigurations.h"
#include <time.h> 


/*****************************/
//#include "msg/msg.h"          /* Yeah! If you want to use msg, you need to include msg/msg.h  : use this for the older versions of simgrid
#include "simgrid/msg.h"        // Use this for the most recent version of simgrid
#include "xbt/sysdep.h"         /* calloc, printf */
#include <xbt.h>
/* Create a log channel to have nice outputs. */
#include "xbt/log.h"
#include "xbt/asserts.h"
#include "xbt/dict.h"
//#include "xbt/synchro_core.h"
#include "simgrid/plugins.h"
#include "xbt/synchro_core.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(msg_test,
                             "Messages specific for this msg example");

// Older versions of simgrid use "_XBT_GNUC_UNUSED int res ". Newer versions of simgrid use "XBT_ATTRIB_UNUSED int res" !!

/*****************************/

using namespace std; 
using namespace DCApplication;

// determine which platform
#ifdef _WIN32 
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif



#define FINALIZE ((void*)221297)        /* a magic number to tell people to stop working */

typedef std::pair <char*, int> pair_runnable_name_size;

typedef struct
{
  char  label[50];
  int   size;
}labelAccess;

typedef struct
{
  char  label[50];
  char* memory;
}labelAddress;

typedef struct
{
  int nb_activatees;
  int nb_activators;
  char **activatees;
  char **activators;
  
  int nb_rd_labels;
  int nb_wr_labels;
  std::vector<pair_runnable_name_size> rd_labels;
  std::vector<pair_runnable_name_size> wr_labels;
  
  double compute_duration;
  double message_size;
}depActivation; //Data structure for specifying the dependancies of a Task 


typedef struct
{
  msg_task_t task;
  int* stop;
  char marker[30];
}ARG;


typedef struct
{
  int nb_processes;
  int* stop;
}ARG_supervise;



// Test the presence of a string in a vector of strings
int Is_Label_in_vector(const char * Label, char ** Vector, int labels_index)
{			
  int size = labels_index;
  for(int i = 0;i<size;i++)
    {
      if(!strcmp(Label,Vector[i]))
	{
	  return i;
	}
    }
  return -1;
}
      
      

int Get_Label_index(const char * Label, char ** Vector, int labels_index)
{			
  int i = 0;
  while((strcmp(Label,Vector[i])!=0))
    {	
      i++;
    }
  return i;
}
 

typedef struct
{
  char ** Label_Vector;
  int number_of_labels;
  int number_of_tasks;
  int slaves_count;
  msg_storage_t *storages;
  int * Labels_Storage_Table;
}Host_data;





xbt_mutex_t mutex = NULL;


int slave_supervise(int argc, char *argv[])
{
  //_XBT_GNUC_UNUSED int res;
  XBT_ATTRIB_UNUSED int res;
  msg_task_t task_mail = NULL;
  XBT_INFO("Supervisor started");
  int * local_stop;
  ARG_supervise* ARG_sup;
  int tasks;
  ARG_sup = (ARG_supervise* )MSG_process_get_data(MSG_process_self()); //cast and dereference
  local_stop = ARG_sup->stop; //cast and dereference
  tasks = ARG_sup->nb_processes;
  char* marker;
  int tasks_done=0;
  
  
  while(tasks!=tasks_done) // wait for activating tasks to finish
    {
      XBT_INFO("Receiving task");
      res = MSG_task_receive(&(task_mail),"Mailbox_Slaves_process_to_Master"); //receive is blocking
      xbt_assert(res == MSG_OK, "MSG_task_get failed");
      marker = (char*)MSG_task_get_data(task_mail);    
      XBT_INFO("Received task %s",marker);
      tasks_done++;
    }
  *local_stop = 1;
  return 0;
}  






//int main(int argc, char *argv[])
int master(int argc, char *argv[])
{
  
  //****************************************************************************************//
  //*                                                                                      *//
  //*                        Start Parser                                                  *//
  //*              Extraction of application information                                   *//
  //*                                                                                      *//
  //****************************************************************************************//

  dcAmaltheaParser MyAmaltheaParser;
  AmApplication* MyAmApplication = new AmApplication();
  dcApplication* MyApplicaton = new dcApplication();
  dcTaskGraph* MyTaskGraph = MyApplicaton->createGraph("dcTaskGraph");
  
  vector<dcTask*> Tasks;
  vector<dcRunnable*> Runnables;
  vector<dcLabel*> Labels;
  
  char filePath[200];
  string strDirPath = "";	
  
  int scale_size_Label = 1;
  int scale_size_Computation = 10000000;

  // get current directory
  if(!GetCurrentDir(filePath, sizeof(filePath)))
    {
      cout<<"** ERROR - Something went wrong, exiting...\n";
    }
  else
    {
      strDirPath = filePath;
    }
	
  string strName = strDirPath+"/Parser/ApplicationModels/"+INPUT_APPLICATION_MODEL;
  MyAmaltheaParser.ParseAmaltheaFile(strName, MyAmApplication);
  
  MyApplicaton->CreateGraphEntities(MyTaskGraph, MyAmApplication);
  
  Tasks = MyApplicaton->GetAllTasks(MyTaskGraph);
  Runnables = MyApplicaton->GetAllRunnables(MyTaskGraph);
  Labels = MyApplicaton->GetAllLabels(MyAmApplication);
  
  FILE *fp_w_1;
  FILE *fp_w_2;
  
  fp_w_1 = fopen("./OUTPUT_FILES/Simmulation_summary.out" , "w");
  if(fp_w_1 == NULL) 
    {
      perror("Simmulation_summary.out not found in the specified directory");
      return (-1);
    }
  fprintf(fp_w_1, "*****************************************************************************************************\n");
  fprintf(fp_w_1, "*                                                                                                   *\n");
  fprintf(fp_w_1, "*                                                                                                   *\n");
  fprintf(fp_w_1, "*                                   Simulation summary                                              *\n");
  fprintf(fp_w_1, "*                                                                                                   *\n");
  fprintf(fp_w_1, "*                                                                                                   *\n");
  fprintf(fp_w_1, "*****************************************************************************************************\n");
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "\n");
  
  fprintf(fp_w_1, "### INPUT SYSTEM CONFIGURATION ###\n");
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "    Application features: \n");
  fprintf(fp_w_1, "         No of Tasks: %lu\n",Tasks.size());
  fprintf(fp_w_1, "         No of Runnables: %lu\n",Runnables.size());
  fprintf(fp_w_1, "         No of Labels: %lu\n",Labels.size());
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "    Hardware platform charateristics: \n");
  fprintf(fp_w_1, "    (For more details see ../Parser/DeploymentFiles/msg_platform_dev.xml) \n");
  fclose(fp_w_1);
  
  int slaves_count = 0;
  msg_host_t *slaves = NULL;
  msg_task_t *todo = NULL;
  msg_storage_t *storages = NULL;
  int number_of_tasks = 0;
  int number_of_labels = 0;
  
  int i;
  //int res;
  //XBT_ATTRIB_UNUSED int res = sscanf(argv[1], "%d", &number_of_tasks); //Added  XBT_ATTRIB_UNUSED to avoid compilation warnings with NDEBUG
  //xbt_assert(res,"Invalid argument %s\n", argv[1]);
  number_of_tasks = Runnables.size();
  number_of_labels = Labels.size();
  

  for(unsigned int iT = 0; iT < Tasks.size(); iT++)
    {
      vector<dcRunnable*> Runnables_Temp = MyApplicaton->GetTaskRunnables(MyTaskGraph, Tasks.at(iT));
      for(unsigned int iR = 0; iR < Runnables_Temp.size(); iR++)
	{
	  vector<dcRunnable*> Runnables_Edges_Temp = MyApplicaton->GetdcRunnableEdges(MyTaskGraph, Tasks.at(iT), Runnables_Temp.at(iR));
	  for(unsigned int enabler=0; enabler < Runnables_Edges_Temp.size(); enabler++)
	    {
	      Runnables_Edges_Temp.at(enabler)->SetActivators(Runnables_Temp.at(iR));
	    }
	}
	 
    }

  int nb_edges=0;
  for(unsigned int R_index; R_index < Runnables.size(); R_index++)
    nb_edges = nb_edges + Runnables.at(R_index)->GetActivators().size();
	 
  typedef std::pair <depActivation, string> pair_runnable_name;
  std::vector<pair_runnable_name> Task_Vector;
  char **Label_Vector = (char**)calloc(sizeof(char *),number_of_labels);
  int labels_index = 0; // index in the array Label_Vector of the lat aded Label name. labels_index is bqsically the number of Labels written in Label_Vector.
	

  for(unsigned int iT = 0; iT < Tasks.size(); iT++)
    {
      pair_runnable_name pair_temp;
      depActivation depActivation_temp;
      string name_temp;
		
      vector<dcRunnable*> Runnables_Temp = MyApplicaton->GetTaskRunnables(MyTaskGraph, Tasks.at(iT));
      for(unsigned int iR = 0; iR < Runnables_Temp.size(); iR++)
	{
	  //Start : Check inter Runnable Dependency
	  vector<dcRunnable*> Runnables_Edges_FROM_IT_Temp = MyApplicaton->GetdcRunnableEdges(MyTaskGraph, Tasks.at(iT), Runnables_Temp.at(iR));
	  depActivation_temp.nb_activatees = Runnables_Edges_FROM_IT_Temp.size();//number of tasks to be activated by that task (here Adapt_State)
	  depActivation_temp.activatees = (char**)calloc(depActivation_temp.nb_activatees, sizeof(char *));
	  for(int i=0; i<depActivation_temp.nb_activatees; i++)
	    {
	      string MB_name;
	      MB_name = Runnables_Temp.at(iR)->GetName() + "_To_" + Runnables_Edges_FROM_IT_Temp.at(i)->GetName();
	      char *_MB_name = new char[MB_name.length() + 1];
	      strcpy(_MB_name, MB_name.c_str());
	      depActivation_temp.activatees[i] = _MB_name;
	    }

	  vector<dcRunnable*> Runnables_Edges_TO_IT_Temp = Runnables_Temp.at(iR)->GetActivators();
	  depActivation_temp.nb_activators = Runnables_Edges_TO_IT_Temp.size();//number of tasks that activate Adapt State
	  depActivation_temp.activators = (char**)calloc(depActivation_temp.nb_activators, sizeof(char *));

	  for(int i=0; i<depActivation_temp.nb_activators; i++)
	    {
	      string MB_name;
	      MB_name = Runnables_Edges_TO_IT_Temp.at(i)->GetName() + "_To_" + Runnables_Temp.at(iR)->GetName();
	      char *_MB_name = new char[MB_name.length() + 1];
	      strcpy(_MB_name, MB_name.c_str());
	      depActivation_temp.activators[i] = _MB_name;
	    }
	  //Done : Check inter Runnable Dependency
			
	  //Start : Label Dependency AND Computation and Communication Sizes
	  depActivation_temp.compute_duration = 0;
	  depActivation_temp.message_size = 0;
			
	  int nb_instructions = Runnables_Temp.at(iR)->GetAllInstructions().size();
	  int _mesage_size = 0;
			
	  for(int i=0; i < nb_instructions; i++)
	    {
	      string instrName = Runnables_Temp.at(iR)->GetAllInstructions().at(i)->GetName();
	      if(instrName == "sw:LabelAccess")
		{
		  dcInstruction* inst = Runnables_Temp.at(iR)->GetAllInstructions().at(i);
		  dcRemoteAccessInstruction *rinst = dynamic_cast<dcRemoteAccessInstruction*>(inst);
		  string labelName = rinst->GetLabel()->GetName();
		  const char * labelName_c = labelName.c_str();
					
		  //Check if Label already in the Vector. If no, add the Label name into the vector. If yes, do nothing
		  if ((Is_Label_in_vector(labelName_c, Label_Vector, labels_index)==-1))
		    {
		      Label_Vector[labels_index] = (char *)labelName_c;
		      labels_index++;
		    }
		
		  int labelSize = (rinst->GetLabel()->GetSize())*scale_size_Label;
		  _mesage_size = _mesage_size + labelSize;
					
		  char *_label_name = new char[labelName.length() + 1];
		  strcpy(_label_name, labelName.c_str());
		  pair_runnable_name_size _pair_runnable_name_size = std::make_pair (_label_name, labelSize);
					
		  if(rinst->GetWrite())
		    {
		      //write instruction
		      depActivation_temp.wr_labels.push_back(_pair_runnable_name_size);
		    }
		  else
		    {
		      //read instruction
		      depActivation_temp.rd_labels.push_back(_pair_runnable_name_size);
		    }
		}
	      else
		if(instrName == "sw:InstructionsConstant")
		  {
		    dcInstruction* inst = Runnables_Temp.at(iR)->GetAllInstructions().at(i);
		    dcExecutionCyclesConstantInstruction* einst = dynamic_cast<dcExecutionCyclesConstantInstruction*>(inst);
		    if(einst)
		      {
			depActivation_temp.compute_duration = depActivation_temp.compute_duration + (einst->GetValue())*scale_size_Computation;
		      }
		  }
		else
		  if(instrName == "sw:InstructionsDeviation")
		    {
		      //Instruction deviations are modelled using different types of distributions. For the moment we'll focus of Boundaries distribution with upper and lower bounds
		      dcExecutionCyclesDeviationInstruction* einst = dynamic_cast<dcExecutionCyclesDeviationInstruction*>(Runnables_Temp.at(iR)->GetAllInstructions().at(i));
		      if (einst)
			{
			  //Get lower and upper bound if they are valid
			  double UpperBound = 0.0;
			  double LowerBound = 0.0;
			  if (einst->GetUpperBoundValid())
			    {
			      UpperBound = einst->GetUpperBound();
				}
			  if (einst->GetLowerBoundValid())
			    {
			      LowerBound = einst->GetLowerBound();
			    }
			  //Generate your random number here
			  std::random_device rd; // obtain a random number from hardware
			  std::mt19937 eng(rd()); // seed the generator
			  std::uniform_int_distribution<> distr(LowerBound, UpperBound); // define the range //Caution std::uniform_int_distribution<> is returning integers (int type with its range of max 4 bytes, take care of the overflow possibly resulting in the presence of negative values!)!!!
			  //distr(eng)// generate numbers
			  depActivation_temp.compute_duration = depActivation_temp.compute_duration + ((double)(distr(eng)))*scale_size_Computation;
			}
		    }
	    }
	  depActivation_temp.nb_rd_labels = depActivation_temp.rd_labels.size();
	  depActivation_temp.nb_wr_labels = depActivation_temp.wr_labels.size();
	  depActivation_temp.message_size = _mesage_size;

	  // Done : Label Dependency AND Computation and Communication Sizes 
	  name_temp = Runnables_Temp.at(iR)->GetName();
	  pair_temp = make_pair(depActivation_temp, name_temp);
	  Task_Vector.push_back(pair_temp);		
	}
    }
	

  //****************************************************************************************//
  //*                                                                                      *//
  //*                        Stop Parser                                                   *//
  //*              Application information extracted                                       *//
  //*                                                                                      *//
  //****************************************************************************************//

  // TASKS : Create Tasks. Put the runnables in a vector. For SimGrid a runnable is called a task
  todo = xbt_new0(msg_task_t, number_of_tasks); //Allocates mameory like calloc

  for (i = 0; i < number_of_tasks; i++)
    {
      const char * R_name = Task_Vector.at(i).second.c_str();
      todo[i] = MSG_task_create(R_name, Task_Vector.at(i).first.compute_duration, Task_Vector.at(i).first.message_size, &(Task_Vector.at(i).first));
    }

  // SLAVES : Extract slaves from input file. Put the slaves in a vector		  
  XBT_ATTRIB_UNUSED int res1 = sscanf(argv[1], "%d", &slaves_count); //Added  XBT_ATTRIB_UNUSED to avoid compilation warnings with NDEBUG
  xbt_assert(res1,"Invalid argument %s\n", argv[1]);		  

  slaves = xbt_new0(msg_host_t, slaves_count);
  //int pstate = 2;
  for (i = 0; i < slaves_count; i++)
    {
      slaves[i] = MSG_get_host_by_name(argv[i+2]); // ARGV[1] Representsnts the number of slaves.
      xbt_assert(slaves[i] != NULL, "Unknown host %s. Stopping Now! ", argv[i+2]);
      //MSG_host_set_pstate(slaves[i], pstate);
    }
  for (i = 0; i < slaves_count; i++)
    XBT_DEBUG("%s", MSG_host_get_name(slaves[i])); //Log an event at the DEBUG priority on the default category with these args.

  //STORAGE : Before dispathing the tasks, dispatch the datas to storage elements !!!
  //Storage managemenet
  //Cautions:
  //            You need to write the file before you read it!! 
  //            When you read some amount of data from a file, the file should initially contain a higher amount of data than what you want to read!!! 
  //            The read operation doesn't change the amount stored in the file!!! 
  //            If you try to read/write 0 bits from/to a file, the system produces an error! You have to read/write a non zero amount of data!!!

  int nb_storage_elements = argc - (slaves_count+2);
  storages = xbt_new0(msg_storage_t, nb_storage_elements);

  fp_w_1 = fopen("./OUTPUT_FILES/Simmulation_summary.out" , "a");
  if(fp_w_1 == NULL) 
    {
      perror("Simmulation_summary.out not found in the specified directory");
      return (-1);
    }

  fprintf(fp_w_1, "         STORAGE: %d\n",nb_storage_elements);
  for (i = 0; i < nb_storage_elements; i++)
    {
      storages[i] = MSG_storage_get_by_name(argv[i+slaves_count+2]);
      xbt_assert(storages[i] != NULL, "Unknown storage %s. Stopping Now! ", argv[i+slaves_count+2]);

      fprintf(fp_w_1, "         %s\n",argv[i+slaves_count+2]);
    }
  for (i = 0; i < nb_storage_elements; i++)
    XBT_DEBUG("%s", MSG_storage_get_name(storages[i])); //Log an event at the DEBUG priority on the default category with these args.
	

  fprintf(fp_w_1, "\n");
  for (i = 0; i < nb_storage_elements; i++)
    {
      //sg_size_t free_size = MSG_storage_get_free_size(storages[i]);
      //sg_size_t used_size = MSG_storage_get_used_size(storages[i]);
      sg_size_t total_size = MSG_storage_get_size(storages[i]);
      fprintf(fp_w_1, "         %s has TOTAL SIZE: %llu bytes\n",MSG_storage_get_name(storages[i]), total_size);
    }
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "         HOSTS: %d\n",slaves_count);
  for (i = 0; i < slaves_count; i++)
    {
      fprintf(fp_w_1, "         %s\n",MSG_host_get_name(slaves[i]));
    }

  fprintf(fp_w_1, "\n");
  for (i = 0; i < slaves_count; i++)
    {
      fprintf(fp_w_1, "         %s has speed %0.0f flop/second\n",MSG_host_get_name(slaves[i]),MSG_get_host_speed (slaves[i]));
    }

  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "### MAPPING OF APPLICATION ON HARDWARE PLATFORM ###\n");
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "         See file Mapping_details.out\n");
  fprintf(fp_w_1, "\n");
  fclose(fp_w_1);
	
	
  fp_w_2 = fopen("./OUTPUT_FILES/Mapping_details.out" , "w");
  if(fp_w_2 == NULL) 
    {
      perror("Mapping_details.out not found in the specified directory");
      return(-1);
    }
        
  fprintf(fp_w_2, "*****************************************************************************************************\n");
  fprintf(fp_w_2, "*                                                                                                   *\n");
  fprintf(fp_w_2, "*                                                                                                   *\n");
  fprintf(fp_w_2, "*                        Mapping of Labels and Runnables to storage and hosts                       *\n");
  fprintf(fp_w_2, "*                                                                                                   *\n");
  fprintf(fp_w_2, "*                                                                                                   *\n");
  fprintf(fp_w_2, "*****************************************************************************************************\n");
  fprintf(fp_w_2, "\n");
  fprintf(fp_w_2, "\n");

  // MAPPING of LABELS	
  fprintf(fp_w_2, "### MAPPING OF LABELS ###\n");
  fprintf(fp_w_2, "\n");
  // Build correspondance table Labels - Storages
  // The i-th Label (as read from the vector Label_Vector (ie the Label : Label_Vector[i])) is mapped to the storage: storages[Labels_Storage_Table[i]]
  int * Labels_Storage_Table = (int *)calloc(sizeof(int),number_of_labels);
  for (i = 0; i < number_of_labels; i++)
    {
      Labels_Storage_Table[i] = (i % nb_storage_elements);
      fprintf(fp_w_2, "         Label %s mapped to storage %s\n",Label_Vector[i], MSG_storage_get_name(storages[i % nb_storage_elements]));
    }	
  fprintf(fp_w_2, "\n");
  fclose(fp_w_2);	

  // Associate the "Host_data" to each host
  Host_data H_data;
  H_data.Label_Vector=Label_Vector;
  H_data.number_of_labels=number_of_labels;
  H_data.number_of_tasks=number_of_tasks;
  H_data.slaves_count=slaves_count;
  H_data.storages=storages;
  H_data.Labels_Storage_Table=Labels_Storage_Table;
	
  for (i = 0; i < slaves_count; i++)
    {
      MSG_host_set_data(slaves[i],&H_data); 	
    }

  // START THE SUPERVISER : it will check if all the created processes finished
  int application_executed = 0; //Not protected by any mutex since the wort that can happen is to execute MSG_process_sleep(0.000001) a few more times.
  ARG_supervise ARG_sup;
  ARG_sup.nb_processes = number_of_tasks;
  ARG_sup.stop = &application_executed;  
  MSG_process_create("Superviser", slave_supervise, (void*) (&ARG_sup) , MSG_host_self());

  fp_w_2 = fopen("./OUTPUT_FILES/Mapping_details.out", "a");
  if(fp_w_2 == NULL) 
    {
      perror("Mapping_details.out not found in the specified directory");
      return(-1);
    }
  fprintf(fp_w_2, "### MAPPING OF RUNNABLES ###\n");
  fprintf(fp_w_2, "\n");

  //MAPPING of RUNNABLES
  for (i = 0; i < number_of_tasks; i++)
    {
      //Check availability of hosts (slaves);
      //Use mailboxes and MSG_task_get_data(msg_task_t task) to get the informs about activations/read/write accesses from the Hosts-Storages
      //Consider the Hosts characteristics (Power in Gf...) and the Tasks characteristics (required FLOPS)
      //Deduce a reasonable allocation of tasks on available hosts
      //Do the allocation
      //Update the Host-Storage bookkeeping
    
      fprintf(fp_w_2, "         Runnable %s mapped to host %s\n",todo[i]->name,MSG_host_get_name(slaves[i % slaves_count]));
      XBT_INFO("Sending task %s to host %s",MSG_task_get_name(todo[i]),MSG_host_get_name(slaves[i % slaves_count]));
      MSG_task_send(todo[i], MSG_host_get_name(slaves[i % slaves_count]));//slaves_count
      XBT_INFO("Sent task %s to host %s",MSG_task_get_name(todo[i]),MSG_host_get_name(slaves[i % slaves_count]));
    }
  fprintf(fp_w_2, "\n");
  fclose(fp_w_2);

  XBT_INFO("Start waiting for processes completion");
  // Wait till all processes have finished execution
  XBT_INFO("Sleeping");
  while(application_executed!=1)
    {
      MSG_process_sleep(0.000001);
    }
  XBT_INFO("Slept");
	
  // STOP EACH HOST : Dispatch finalize to each Host
  char marker[30];
  XBT_INFO("All processes completed. Stop the slaves.");
  for (i = 0; i < slaves_count; i++)
    {
      strcpy(marker,"finalize_to_");//strcpy is overwriting !!!
      strcat(marker,MSG_host_get_name(slaves[i]));
      msg_task_t finalize = MSG_task_create("finalize", 0, 0, marker);//FINALIZE
      MSG_task_set_category (finalize, "finalize");
      XBT_INFO("Sending task %s to host %s",marker,MSG_host_get_name(slaves[i]));
      MSG_task_send(finalize, MSG_host_get_name(slaves[i]));
      XBT_INFO("Sent task %s to host %s",marker,MSG_host_get_name(slaves[i]));
    }
	
  XBT_INFO("Master completed.\nSimulation done.\n");
  free(slaves);
  free(todo); 
  cout<<"End_marker_1"<<endl;
  return 0;
}





int slave_th(int argc, char *argv[])
{
  ARG* argument;
  XBT_ATTRIB_UNUSED int res;
  msg_task_t task = NULL;
  msg_task_t task_mail = NULL;
  argument = (ARG* )MSG_process_get_data(MSG_process_self()); //cast and dereference
  task = argument->task;

  int n_activators = 0;
  int n_activatees = 0;
  int n_activators_count = 0;
  int n_activatees_count = 0;
  int n_rd_lab = 0;
  int n_wr_lab = 0;
  
  int idx_Label;
  char *read;
  char *write;
  int Label_size;
  const char * fullpath;
  msg_file_t file;

  depActivation* inter_task_data;
  inter_task_data = (depActivation*)MSG_task_get_data(task); //extract proper data of the task

  //if we get Run_Adapt_State, do not do "n_activators=(*inter_task_data).nb_activators". If we do not get Run_Adapt_State then execute "n_activators=(*inter_task_data).nb_activators".
  if (strcmp(MSG_task_get_name(task), "Run_Adapt_State")) 
    n_activators=(*inter_task_data).nb_activators;
  
  n_activators_count = n_activators;
  // wait for activating tasks to finishœ
  while(n_activators_count>0) 
    {
      //msg_task_t task_mail = NULL;	
      XBT_INFO("Receiving task");	
      res = MSG_task_receive(&(task_mail),(*inter_task_data).activators[n_activators - n_activators_count]); //receive is blocking
      XBT_INFO("Received task %s",(*inter_task_data).activators[n_activators - n_activators_count]);   
      xbt_assert(res == MSG_OK, "MSG_task_receive failed");
      n_activators_count = n_activators_count-1;
    }
  
  //Determine the number of Labels to read
  n_rd_lab = (*inter_task_data).nb_rd_labels; 
  idx_Label = 0;	    
  Host_data *H_data = (Host_data *)MSG_host_get_data(MSG_host_self()); 
  
  if (!strcmp(MSG_task_get_name(task), "Run_Adapt_State"))
    n_rd_lab=0;

  // Read Labels
  while(n_rd_lab>0) 
    {
      read = ((*inter_task_data).rd_labels)[n_rd_lab-1].first;
      Label_size = ((*inter_task_data).rd_labels)[n_rd_lab-1].second;
      //read
      idx_Label = Is_Label_in_vector(read,(*H_data).Label_Vector,(*H_data).number_of_labels);
      fullpath = MSG_storage_get_name((*H_data).storages[(*H_data).Labels_Storage_Table[idx_Label]]);
      XBT_INFO("Reading label : %s, size : %d",read, Label_size);
      file =  MSG_file_open(fullpath, NULL);
      //MSG_file_dump(file);
      MSG_file_seek(file, 0, SEEK_SET);
      //file_pointer = MSG_file_tell(file_test);
      MSG_file_read(file,Label_size);//Label_size
      MSG_file_close(file);
      XBT_INFO("Read label : %s, size : %d",read, Label_size);
      n_rd_lab--;	
    }
  
  XBT_INFO("Executing %s",MSG_task_get_name(task));
  MSG_task_execute(task);
  XBT_INFO("Executed %s", MSG_task_get_name(task));
  
  
  //Determine the number of Labels to write
  n_wr_lab = (*inter_task_data).nb_wr_labels; 
  // Write Labels
  while(n_wr_lab>0) 
    {
      write = ((*inter_task_data).wr_labels)[n_wr_lab-1].first;
      Label_size = ((*inter_task_data).wr_labels)[n_wr_lab-1].second;

      //write
      idx_Label = Is_Label_in_vector(write,(*H_data).Label_Vector,(*H_data).number_of_labels);
      fullpath = MSG_storage_get_name((*H_data).storages[(*H_data).Labels_Storage_Table[idx_Label]]);
      XBT_INFO("Writing label : %s, size : %d",write,Label_size);
      msg_file_t file =  MSG_file_open(fullpath, NULL);
      MSG_file_seek(file, 0, SEEK_SET);
      //file_pointer = MSG_file_tell(file_test);
      MSG_file_write(file,Label_size);//Label_size
      MSG_file_close(file);
      XBT_INFO("Written label : %s, size : %d",write,Label_size);
      n_wr_lab--;
    }
  
  
  
  if (strcmp(MSG_task_get_name(task), "Run_Check_Termination"))
    n_activatees=(*inter_task_data).nb_activatees;
  else
    n_activatees=0;
  
  n_activatees_count = n_activatees;
  while(n_activatees_count>0) // activate subsequent tasks
    {
      //Once the task is executed, write to storage and only then write to mailboxes to activate dependent taslks !!
      task_mail = MSG_task_create("",0,0,NULL); //instead null we should send the location of the label (in a storage) where to read from  
      XBT_INFO("Sending task %s",(*inter_task_data).activatees[n_activatees - n_activatees_count]);
      res = MSG_task_send(task_mail,(*inter_task_data).activatees[n_activatees - n_activatees_count]); //send is blocking, possibly use isend (for non blocking send)
      XBT_INFO("Sent task %s",(*inter_task_data).activatees[n_activatees - n_activatees_count]);
      xbt_assert(res == MSG_OK, "MSG_task_send failed");
      //MSG_task_destroy(task_mail); ///? comment it if problems occur ??
      n_activatees_count = n_activatees_count-1; 		    
    }

  // Send message to the master for notifying the end of the execution (use mailboxes for this communication)!!
  task_mail = MSG_task_create("",0,0,argument->marker);
  xbt_mutex_acquire(mutex); // take mutex
  XBT_INFO("Sending task %s",argument->marker);
  res = MSG_task_send(task_mail,"Mailbox_Slaves_process_to_Master"); //send is blocking, possibly use isend (for non blocking send)
  XBT_INFO("Sent task %s",argument->marker);
  xbt_mutex_release(mutex);// free mutex

  MSG_task_destroy(task);
  MSG_task_destroy(task_mail);
  
  return 0;
}               





//Original slave from dcMain.cpp
int slave(int argc, char *argv[])
{
  XBT_ATTRIB_UNUSED int res;
  msg_task_t task = NULL;
  while (1)
    {
      XBT_INFO("Receiving task");
      res = MSG_task_receive(&(task),MSG_host_get_name(MSG_host_self())); // the execution is blocked till the task is received; use MSG_task_irecv for receiving tasks asynchronously !
      xbt_assert(res == MSG_OK, "MSG_task_get failed");
      XBT_INFO("Received task %s",MSG_task_get_name(task));     
      if (!strcmp(MSG_task_get_name(task), "finalize"))
	{
	  XBT_INFO("Received task %s",(char*)MSG_task_get_data(task));
	  MSG_task_destroy(task);
	  break;
	}      
      else
	{
	  char Thread_name[30];
	  char c[10];
	  int th_count=0;
	  string str;
	  void* arg;
	  ARG argument;//argument to pass to the created process (actually this is the task that is passed to the process)
	  strcpy(c,"Thread");//strcpy is overwriting !!!
	  th_count++;
	  strcpy(Thread_name,MSG_host_get_name(MSG_host_self()));//strcpy is overwriting !!!
	  strcat(Thread_name,"_");
	  str = to_string(th_count);
	  strcat(Thread_name,str.c_str());
	  strcat(Thread_name,"_to_Master");
	  argument.task = task;	  
	  strcpy(argument.marker,Thread_name);
	  arg = (void*) (&argument);
	  MSG_process_create(c, slave_th, arg , MSG_host_self());
	}
    }    
  XBT_INFO("Slave %s is done.", MSG_host_get_name(MSG_host_self()));
  return 0;                            
}
  


msg_error_t test_all(const char *platform_file, const char *application_file)
{
  msg_error_t res = MSG_OK;
  FILE* fp_w_1;
  FILE* fp_r_1;
  int size_line = 200;
  char line[200];
  float parse_time;
  /* MSG_config("workstation/model","KCCFLN05"); */
  {                             /*  Simulation setting */
    MSG_create_environment(platform_file);
  }
	
  {                             /*   Application deployment */
    MSG_function_register("master", master);
    MSG_function_register("slave", slave);

    cout<<"Start_marker_1"<<endl;
    cout<<"*****************************************************************************************************"<<endl;
    cout<<"*                                                                                                   *"<<endl;
    cout<<"*                                                                                                   *"<<endl;
    cout<<"*                              Detailed execution trace of the system                               *"<<endl;
    cout<<"*                                                                                                   *"<<endl;
    cout<<"*                                                                                                   *"<<endl;
    cout<<"*****************************************************************************************************"<<endl;
    cout<<endl;
    cout<<endl;
		
		
    MSG_launch_application(application_file);
  }
  res = MSG_main();
	

  fp_r_1 = fopen("./Buffer/Buffer.out" , "r");
  if(fp_r_1 == NULL) 
    {
      perror("Buffer.out not found in the specified directory");
    }
  fgets (line, size_line, fp_r_1);
  sscanf(line, "%*s %*s %*s %f",&parse_time);
  fclose(fp_r_1);

  fp_w_1 = fopen("./OUTPUT_FILES/Simmulation_summary.out" , "a");
  if(fp_w_1 == NULL) 
    {
      perror("Simmulation_summary.out not found in the specified directory");
    }
  fprintf(fp_w_1, "### OUTPUT TIMING INFORMATION ###\n");
  fprintf(fp_w_1, "\n");
  fprintf(fp_w_1, "         Application parse time: %f seconds\n", parse_time);
  fprintf(fp_w_1, "         Execution time: %g seconds\n", MSG_get_clock());
  fclose(fp_w_1);
	
  cout<<endl;
  cout<<endl;
  cout<<"Start_marker_2"<<endl;		
  cout<<"*****************************************************************************************************"<<endl;
  cout<<"*                                                                                                   *"<<endl;
  cout<<"*                                                                                                   *"<<endl;
  cout<<"*                                   Energy consumptions of hosts                                    *"<<endl;
  cout<<"*                                                                                                   *"<<endl;
  cout<<"*                                                                                                   *"<<endl;                                          
  cout<<"*****************************************************************************************************"<<endl;
  cout<<endl;
  cout<<endl;
  return res;	
}                               




int main(int argc, char *argv[])
{
  clock_t start, end;
  start = clock();
  
  FILE* fp_w_1;

  msg_error_t res = MSG_OK;
  sg_energy_plugin_init();
  MSG_init(&argc, argv);
  	
  mutex = xbt_mutex_init();
  const char *platform_file = "./Parser/DeploymentFiles/msg_platform_dev.xml";
  const char *application_file = "./Parser/DeploymentFiles/msg_deployment_dev.xml";
  res = test_all(platform_file, application_file);
  xbt_mutex_destroy(mutex);

  end = clock();

  fp_w_1 = fopen("./OUTPUT_FILES/Simmulation_summary.out" , "a");
  if(fp_w_1 == NULL) 
    {
      perror("Simmulation_summarys.out not found in the specified directory");
    }

  fprintf(fp_w_1, "         Simulation time: %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
  fprintf(fp_w_1, "\n");
  fclose(fp_w_1);

  if (res == MSG_OK)
    return 0;
  else
    return 1;


}                               




