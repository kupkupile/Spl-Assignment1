#include "src/Restaurant.h"
#include <iostream>

using namespace std;

Restaurant* backup = nullptr;

int main(int argc, char** argv){
    /*if(argc!=2){
        std::cout << "usage: rest <config_path>" << std::endl;
        return 0;
    }
     */
    /*
    string configurationFile = argv[1];
    */
    ///home//levletom//CLionProjects//SPL_Assignment1

    freopen("/home//levletom//CLionProjects//SPL_Assignment1//input_example3.txt","r",stdin);
    freopen ("/home//levletom//CLionProjects//SPL_Assignment1//file3.txt","w",stdout);
    Restaurant rest("configFile.txt");
    rest.start();
    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
    }
    fclose (stdout);
    return 0;
}