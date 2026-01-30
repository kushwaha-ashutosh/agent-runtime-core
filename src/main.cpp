#include <iostream>

using namespace std;

std::string agent_step(int step);
void run_search_tool();
void run_summary_tool();

int main(){
    

    cout<<"The runtime started"<<endl;

    for(int tick=1;tick<=3;tick++){
        std::string action =agent_step(tick);
        std::cout<<"agent says:"<<action<<std::endl;

        if(action=="search"){
            run_search_tool();

        }
        else if(action=="summarize"){
            run_summary_tool();
        }

        else if(action=="done"){
            break;
        }

    }

   std::cout<<"Runtime Stopped"<<endl;
   return 0;


}