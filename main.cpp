#include "classes/parser/Parser.cpp"
#include "classes/NewtonianForce.cpp"
#include <filesystem>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <run_name> <input.txt> <config.txt>" << std::endl;
        return 1;
    }
    std::string runName = argv[1];
    std::string inputFile = argv[2];
    std::string configFile = argv[3];
    try
    {
        Parser parser(inputFile);
        std::unique_ptr system = parser.parse();
        NewtonianForce gravity;

        auto configMap = parseConfig(configFile);
        double dt = std::stod(configMap["dt"]);
        int steps = std::stoi(configMap["steps"]);
        int printingStepsPositions = std::stoi(configMap["printingStepsPositions"]);
        int printingStepsEnergies = std::stoi(configMap["printingStepsEnergies"]);
        bool useLeapfrog = (configMap["useLeapfrog"] == "True");
        std::string originVal = configMap["origin"];
        try
        {
            Vector origin = parseOriginVector(originVal);
            system->setReferencePosition(origin);
        }
        catch (const std::exception &e)
        {
            bool found = false;
            for (Object *obj : system->getAllObjects())
            {
                if (obj->getName() == originVal)
                {
                    system->setReferenceObject(obj);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                std::cerr << "Warning: origin '" << originVal
                          << "' not recognized; using default (0,0)\n";
            }
        }
        std::cout << "Run name: " << runName << std::endl;
        std::cout << "Input file: " << inputFile << std::endl;
        std::cout << "Time step: " << dt << std::endl;
        std::cout << "Number of steps: " << steps << std::endl;
        std::cout << "Printing steps for positions: " << printingStepsPositions << std::endl;
        std::cout << "Printing steps for energies: " << printingStepsEnergies << std::endl;
        std::cout << "Use leapfrog: " << (useLeapfrog ? "true" : "false") << std::endl;
        std::cout << "Origin: " << originVal << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Running simulation..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        // removing the files if they exist
        std::string path = runName + "/energies.txt";
        if (std::filesystem::exists(path))
        {
            std::filesystem::remove(path);
        }
        path = runName + "/positions.txt";
        if (std::filesystem::exists(path))
        {
            std::filesystem::remove(path);
        }

        system->setAllRelevantHillRadius();
        for (int i = 0; i <= steps; ++i)
        {
            
            system->evolveAll(dt, gravity, useLeapfrog);
            if (i % printingStepsPositions == 0)
            {
                system->positionsToFile(runName, "positions.txt");
            }
            if (i % printingStepsEnergies == 0)
            {
                system->energyToFile(runName, "energies.txt", i);
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    std::cout << "Simulation finished." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    return 0;
}
