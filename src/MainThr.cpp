
#include "MainThr.h"
#include "Thread.h"
#include "PCB.h"
#include "System.h"
#include "List.h"

int userMain(int argc, char* argv[]);
void MainThr::run() {

    ret = userMain(argc, argv);



}
