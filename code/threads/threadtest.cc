#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "person.h"

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < which; num++) {
        printf("*** thread %d looped %d times\n", which, num);
	// ---- Lab Assignment 1 ---
        kernel->currentThread->Yield();
    }
}

int compare(Person p1, Person p2){
    if(p1.getPriority() > p2.getPriority())
        return 1;
    else if(p1.getPriority() < p2.getPriority())
        return -1;
    else return 0;
}

Person highestPriority(List<Person> *list){
    int highest = 20;
    Person high;
    List<Person> *temp = list;
    ListIterator<Person> li1 = temp;

    while (!li1.IsDone()) {
        Person p = li1.Item();
        if (p.getPriority() <= highest) {
		high = p;
		highest = p.getPriority();
        }
	li1.Next();
    }
        return high;
}

void print(Person p){
    std::cout << "Person with sequence " << p.getSequence() << ", priority " << p.getPriority() << ", number of clothes " << p.getClothes() << " and time to wash clothes " << p.getWashTime() << "\n";
}

void sim1(int number){
    SortedList<Person> *sPersons = new SortedList<Person>(compare);
    int sequence = 0;
    int totalTime = 0;
    //generate 20 persons
    for(int i=0; i<number; i++){
        Person p(sequence++, rand()%20, rand()%30, rand()%50);
        sPersons->Insert(p);
    }
    //print order
    std::cout << "\n---------- Running Simulation 1 ----------\n";
    std::cout << "Line up outside laundry as per priority:\n";
    ListIterator<Person> li = sPersons;
    sPersons->Apply(print);
    std::cout << "\nSimulation begins.....\n\n";
    int order = 0;
    Person prev;
    while (!li.IsDone()){
        Person p = sPersons->Front();
	totalTime += p.getWashTime();
        std::cout << "order " << order++ << ": ";
        print(p);
        if(prev.getSequence() != NULL)
            std::cout << ". Person with sequence " << prev.getSequence() << " leaves the room having taken " << prev.getWashTime() << " time.\n";
        else
            std::cout << "\n";

        prev = p;
	li.Next();
        sPersons->RemoveFront();
    }
    std::cout << "\nTotal wash time: " << totalTime << "\n";

}

void sim2(int number){
    List<Person> *persons = new List<Person>();
    int sequence = 0;
    int totalTime = 0;
    for(int i=0; i<number; i++){
        Person p(sequence++, rand()%20, rand()%30, rand()%50);
        persons->Append(p);
    }
    std::cout << "\n---------- Running Simulation 2 ----------\n";
    std::cout << "Line up outside laundry as per priority:\n";
    ListIterator<Person> li = persons;
    persons->Apply(print);
    std::cout << "\nSimulation begins.....\n\n";
    int order = 0;
    Person prev;
    while(!li.IsDone() && persons->NumInList()!=0){
        Person curr = highestPriority(persons);
	totalTime += curr.getWashTime();
        std::cout << "order " << order++ << ": ";
        print(curr);
        if(prev.getSequence() !=NULL)
            std::cout << ". Person with sequence " << prev.getSequence() << " leaves the room having taken " << prev.getWashTime() << " time.\n";
        else
            std::cout << "\n";
	prev = curr;
        persons->Remove(curr);
	//li.Next();
    }
    std::cout << "\nThe total time taken for wash: " << totalTime << "\n";
}

void
ThreadTest()
{
   // Thread *t = new Thread("forked thread");
   // t->Fork((VoidFunctionPtr) executeSim1, (void *) 20);
    //SimpleThread(0);
    sim1(20);
    sim2(20);
}
