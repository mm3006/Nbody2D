#include "System.hpp"

int main(int argc, char *argv[]){

	//default values
	std::string inputName = "inputs/solarsystem.csv";
	std::string outputName ="outputs/coordsSolar10.csv";
	int N = 1000000;
	double dt = 10;
	int saveStep = 1000;
	int index = -1;
	bool doRK4 = false;
	bool doAllinteractions = false;

	if (argc>1){
		try{
			inputName = argv[1];
			if(argc>2){
				outputName = argv[2];
				if(argc>3){
					N = atoi(argv[3]);
					if(argc>4){
						dt =atof(argv[4]);
						if(argc>5){
							saveStep = atoi(argv[5]);
							if(argc>6){
								index = atoi(argv[6]);
								if(argc>7){
									doRK4 = (bool)atoi(argv[7]);
									if(argc>8){
										doAllinteractions = (bool)atoi(argv[8]);
									}
								}
							}
						}
					}
				}
			}
		} catch (const char* msg) {
        	std::cout << "Exception Caught: " << msg;
			std::cout << "Correct usage\n./main inputName outputName NSteps stepSize saveStep referenceObjectIndex doRK4 doAllInteractions\n";
    	}
	}

	std::cout << "Starting the simulation with following parameters:\n" << "Input name: " <<  inputName << "\nOutput name: " << outputName << "\nNumber of steps: " << N <<"\nStep size (in seconds):" << dt <<"\nSave step: " << saveStep <<"\nFrame of reference object index: " << index << "\nSimulate using RK4 algorithm?: " << doRK4 << "\nAccount for all interactions?: " << doAllinteractions <<"\n"; 
	//simulation execution

	Space::System* syst = new Space::System();
	// Space::readFile(*syst,inputName); //default: solarsystem.csv
	syst->readFile(inputName);

	if(doAllinteractions)
		syst->calculateRelevantBodiesAll();
	
	else
		syst->calculateRelevantBodies();
		

	// syst->printObjects(); //info
	syst->evolve(N,dt,saveStep,index,outputName,doRK4); //evolution

	delete(syst);


	return 0;
}
