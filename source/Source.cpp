#include "SimulationCore.h"
#include "SearchEngine.h"
#include "statistics.h"

// Objects used
#include "world.h"
#include "agent.h"
#include "reinforcementAgent.h"
#include "AdaptiveQTable.h"
#include "doubleQLearningAgent.h"

void run_reinforcementLearningAgents(){
     srand (time(NULL));

    // Creating simulation obj
    simulationCore::core* sim = new simulationCore::core();

    char mapPath[256] = "./resources/maps/64_by_32_rogue_like_generated_0.map";
    char testingPointsPath[256] = "./resources/test files/64_by_32_map_0_with_1000_testingPoints";

    // agent brain
    FalconAdaptiveQTable table;
    FalconAdaptiveQTable tableB;

    // observed performance 
    statistics::observations* obs = new statistics::observations(40);

    // Creating objects
    double flooding_threshold = 1.0;
    double flooding_step = 0.1;
    Object* world_obj = new world(mapPath, testingPointsPath, FLOOD_NONE, flooding_step, flooding_threshold);
    Object* agent_obj = new agent(world_obj, 0);
    Object* reinf_obj = new reinforcementAgent(table, world_obj, obs, 1);
    Object* doubleQLearning_obj = new doubleQLearningAgent(table, tableB, world_obj, 1);

    // Adding objects
    sim->addObject(&world_obj);
    //sim->addObject(&agent_obj);
    sim->addObject(&reinf_obj);
    //sim->addObject(&doubleQLearning_obj);

    // Starting simulation
    sim->load();

    sim->run();

    bool keep_positive = false;
    double shift = 0.0;
    obs->column_statistics(keep_positive, shift);
    obs->saveCSV("results.csv");

}

int main(int argc, char *argv[]){
    
    return 0;
}