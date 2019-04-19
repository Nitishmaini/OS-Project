#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

struct Mess
{
int stu_id;
int food_taken_time;
int waiting_time;
int arrival_time;
int completion_time;
int total_time;
int ftk;
}s[3];

int totaltime=0;
int T=0;  // total time required to complete eating

int maximum_eat_Time(int at)  // tells which process will get execute after 
{ 
    int max = 0, i; 
    for (i = 0; i < 3; i++) 
    { 
        if (s[i].arrival_time <= at)           // compares arrival time
	{                     
          if (s[i].food_taken_time > s[max].food_taken_time)  // food eating time
           max = i;                                          
           else if(s[max].food_taken_time==s[i].food_taken_time)  // used when all the processes have same food_eating_time left
           {
            if(s[max].stu_id>s[i].stu_id)
            max=i;
	    }
        } 
     } 
return max;
}
// tells us the flow of execution
int execution() 
{ 
  
    int index; 
    int i = s[0].arrival_time; 
    while (1) { 
        if (i <= 3) { 
            index = maximum_eat_Time(i); } 
	else
            index = maximum_eat_Time(3); 
        printf("Process executing at time : %d is P%d",totaltime,index);
        s[index].food_taken_time -= 1; 
        totaltime += 1; 
        i++;   
	 // tells us at which time which process is getting completed
        if (s[index].food_taken_time == 0) 
	{ 
           s[index].completion_time = totaltime;
           printf("\tProcess P%d is completed at:%d",index,totaltime);
        } 
        printf("\n");  
        // loop termination condition 
        if (totaltime == T) 
            break; 
    } 
}
int main()
{
int i;
//assigning values to students
s[0].stu_id=2132;
s[1].stu_id=2102;
s[2].stu_id=2453;

s[0].food_taken_time=2;
s[1].food_taken_time=4;
s[2].food_taken_time=8;		

//displaying initial state
printf ("STUDENT NO.\t\t\tStudent_id\t\t\t Arrival_TIME\t\t\tfood_taken_time\n"); 
for(i=0;i<3;i++)
{
printf ("S%d\t\t\t\t%d\t\t\t\t %d\t\t\t\t %d\n",i,s[i].stu_id,s[i].arrival_time,s[i].food_taken_time); 
}
	
//backup for food_taken_time so that to print it in end
for(i=0;i<3;i++)
{
	s[i].ftk=s[i].food_taken_time;
}
	
//calculating total time T 
for(i=0;i<3;i++)
{
	T+=s[i].food_taken_time;
}
printf("\n");

//executing processes
execution();
	
//calculating values for Total Waiting time
int Twt=0;
for(i=0;i<3;i++)
{
	//Total time taken=completion time-arrival time
	s[i].total_time=s[i].completion_time - s[i].arrival_time;
	
	// waiting time= total time taken - burst time
	s[i].waiting_time= s[i].total_time -s[i].ftk;
	
	//calculating Total Waiting Time
	Twt= Twt+s[i].waiting_time;
}
 
//calculating value for turn around time
int totalTAT=0;
for(i=0;i<3;i++)
{
	totalTAT= totalTAT +s[i].total_time;
}

// displaying final scenario
printf ("\nSTUDENT NO.\tID\t AT\tFTT\tWT\tTAT\tCT\n"); 
for(i=0;i<3;i++)
{
printf ("S%d\t\t%d\t %d\t %d\t %d\t %d\t %d\n",i,s[i].stu_id,s[i].arrival_time,s[i].ftk,s[i].waiting_time,s[i].total_time,s[i].completion_time); 
}
  
printf("\nTOTAL WAITING TIME:%d\n",Twt);
// average total waiting time
float aTwt=(float)Twt/3;   
printf("AVERAGE WAITING TIME:%f\n",aTwt);
printf("TURN AROUND TIME:%d\n",totalTAT);
float atotalTAT=(float)totalTAT/3;
printf("AVERAGE TURN AROUND TIME:%f\n",atotalTAT);
}
