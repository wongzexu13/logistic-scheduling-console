#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct packages //("Vector of structs initialization", n.d.)
{
    int priority, weight, sequence;
};

struct trucks  //("Vector of structs initialization", n.d.)
{
    int priority, weight, sequence, currentWeight, unusedSpace;
    bool truckStatus;
};

//function to print shorter bar
void printShortBar()
{
    cout<<"----------------"<<endl;
}

//function to print bar
void printBar()
{
    cout<<"------------------------------------------------"<<endl;
}

//function to display starting menu
void displayMenu()
{
    cout<<endl;
    printShortBar();
    cout<<"WeShip2You Inc."<<endl;
    printShortBar();

    cout<<"\n1. Start shipping arrangement"<<endl
        <<"2. Exit program"<<endl;
}

//function to valid input option for menu
int validOption()
{
    int option, check=0;

    do{
        cout<<"\nOption: ";
        cin>>option;

        //input validation
        if(option<1||option>2)
            cout<<"Invalid option\n";
        else
            check=1;

    }while(check!=1);

    return option;
}

//function to obtain maximum weight a truck is allowed to carry
int getMaxWeight()
{
    int maxWeight, check=0;

    do{
        cout<<"\nMaximum weight per truck (kg): ";
        cin>>maxWeight;

        //input validation
        if(maxWeight<50)
            cout<<"\nThe minimum weight requirement is 50kg"<<endl;
        else
            check=1;

    }while(check!=1);

    return maxWeight;

}

//function to obtain number of oversized items of the day
int getNumPackages()
{
    int numPackages, check=0;

    do{
        cout<<"\nNumber of oversized item(s): ";
        cin>>numPackages;

        //input validation
        if(numPackages<1)
            cout<<"\nInvalid input";
        else
            check=1;

    }while(check!=1);

    return numPackages;
}

//function to register all oversized items into the system
vector<packages> regPackages(vector<packages> p, int numPackages, int maxWeight)
{
    int inputPriority, inputWeight;

    printShortBar();
    cout<<"High priority: 3"<<endl
        <<"No priority: 2"<<endl
        <<"Low priority: 1"<<endl;
    printShortBar();

    for(int i=0; i<numPackages; i++){

        //insert new packages
        //("Vector of structs initialization", n.d.)
        p.push_back(packages());

        cout<<"\nOversize item ["<<i+1<<"]"<<endl;

        int check=0;

        do{
            cout<<"Priority: ";
            cin>>inputPriority;

            //input validation for priority
            if(inputPriority<1||inputPriority>3)
                cout<<"\nInvalid priority\n";
            else
                check=1;

        }while(check!=1);

        check=0;

        do{
            cout<<"Weight(kg): ";
            cin>>inputWeight;

            //input validation for weight
            if(inputWeight>maxWeight)
                cout<<"\nOversized item exceed weight limit of "<<maxWeight<<"kg"<<endl;
            else if(inputWeight<50)
                cout<<"\nThe minimum weight requirement is 50kg"<<endl;
            else
                check=1;

        }while(check!=1);

        //assign value of priority, weight, and sequence to the package
        p[i].priority=inputPriority;
        p[i].weight=inputWeight;
        p[i].sequence=i+1;
    }

    return p;
}

//comparator function as parameter to sort oversized items according to their priority followed by the register sequence
//("Sorting an STL vector on two values", n.d.)
bool compare(packages p1, packages p2)
{
    if(p1.priority!=p2.priority)

        //return the package with higher priority if two packages do not have the same priority
        return(p1.priority>p2.priority);

    //return the package that is in the front of the sequence if two of them have got same priority
    return(p1.sequence<p2.sequence);
}

//function to print truck status if the truck is utilized
void printTruckStatus(vector<trucks> t, int index, int truckNum)
{
    cout<<endl<<"Truck "<<truckNum<<": "<<endl;
    if(index>=1){
        cout<<"Oversized items: "<<index<<endl
            <<"Total weight: "<<t[index].currentWeight<<"kg"<<endl
            <<"Unused space: "<<t[index].unusedSpace<<"kg"<<endl;
        printBar();
        cout<<"|Priority"<<"\t|Weight (kg)"<<"\t|Input Sequence|"<<endl;
        printBar();
        for(int i=1; i<=index; i++)
            cout<<"   "<<t[i].priority<<"\t\t\t"<<t[i].weight<<"\t\t"<<t[i].sequence<<endl;
        printBar();
    }
    else{
        cout<<endl<<"Truck "<<truckNum<<" is not utilized"<<endl;
    }
}

//function to display unshipped oversized item(s)
void printUnshippedItem(vector<trucks> t, int index)
{
    if(index>=1){
        cout<<"\nItem(s) that could not be shipped: \n"
            <<"Oversized items: "<<index<<endl
            <<"Total weight: "<<t[index].currentWeight<<"kg"<<endl;
        printBar();
        cout<<"|Priority"<<"\t|Weight (kg)"<<"\t|Input Sequence|"<<endl;
        printBar();
        for(int i=1; i<=index; i++)
            cout<<"   "<<t[i].priority<<"\t\t\t"<<t[i].weight<<"\t\t"<<t[i].sequence<<endl;
        printBar();
        }
    else
        cout<<endl<<"Item(s) that could not be shipped: \n"<<"No item(s)."<<endl;
}

//function to load package into truck
vector<trucks> loadTrucks(vector<trucks> t, vector<packages> p, int index, int i, int maxWeight)
{
    //load package into truck
    //("Vector of structs initialization", n.d.)
    t.push_back(trucks());
    t[index].priority=p[i].priority;
    t[index].weight=p[i].weight;
    t[index].sequence=p[i].sequence;

    //determine current weight of the truck
    t[index].currentWeight=t[index-1].currentWeight+t[index].weight;

    //determine unused space of the truck
    t[index].unusedSpace=maxWeight-t[index].currentWeight;

    return t;
}

//function to update truckStatus
bool setTruckStatus(vector<trucks> t, vector<packages> p, int index, int i, int maxWeight)
{
    if(p[i+1].weight+t[index].currentWeight>maxWeight)

            //return false if loading of the next package will exceed the truck maximum weight limit
            return false;

    else if(p[i+1].weight+t[index].currentWeight<=maxWeight)

        //return true if loading of the next package will not exceed the truck maximum weight limit
        return true;
}

//function to load oversized items into trucks
void loadPackages(vector<packages> p, int maxWeight, int numPackages)
{
    int i=0, a=1, b=1, c=1, d=1, e=1, f=1;

    //initialize 5 trucks with addition 1 for storing of oversized item(s) that could not be shipped in time
    vector<trucks> t1, t2, t3, t4, t5, t6;

    //insert default truck configuration
    //truckStatus=true
    //currentWeight=0
    //("Vector of structs initialization", n.d.)
    t1.push_back(trucks()); t2.push_back(trucks()); t3.push_back(trucks()); t4.push_back(trucks()); t5.push_back(trucks()); t6.push_back(trucks());
    t1[0].truckStatus=true; t2[0].truckStatus=true; t3[0].truckStatus=true; t4[0].truckStatus=true; t5[0].truckStatus=true; t6[0].truckStatus=true;
    t1[0].currentWeight=0; t2[0].currentWeight=0; t3[0].currentWeight=0; t4[0].currentWeight=0; t5[0].currentWeight=0; t6[0].currentWeight=0;

    //loading process of truck 1
    //while loop to allow package loading if truckStatus=true and have got remaining oversized item(s)
    while(t1[a-1].truckStatus!=false&&i<numPackages){

        //function to load package into truck 1
        t1=loadTrucks(t1, p, a, i, maxWeight);

        //function to update truckStatus of truck 1
        t1[a].truckStatus=setTruckStatus(t1, p, a, i, maxWeight);

        a++; i++;
    }

    //loading process of truck 2
    //refer to loading process comments of truck 1
    while(t2[b-1].truckStatus!=false&&i<numPackages){
        t2=loadTrucks(t2, p, b, i, maxWeight);
        t2[b].truckStatus=setTruckStatus(t2, p, b, i, maxWeight);
        b++; i++;
    }

    //loading process of truck 3
    //refer to loading process comments of truck 1
    while(t3[c-1].truckStatus!=false&&i<numPackages){
        t3=loadTrucks(t3, p, c, i, maxWeight);
        t3[c].truckStatus=setTruckStatus(t3, p, c, i, maxWeight);
        c++;
        i++;
    }

    //loading process of truck 4
    //refer to loading process comments of truck 1
    while(t4[d-1].truckStatus!=false&&i<numPackages){
        t4=loadTrucks(t4, p, d, i, maxWeight);
        t4[d].truckStatus=setTruckStatus(t4, p, d, i, maxWeight);
        d++; i++;
    }

    //loading process of truck 5
    //refer to loading process comments of truck 1
    while(t5[e-1].truckStatus!=false&&i<numPackages){
        t5=loadTrucks(t5, p, e, i, maxWeight);
        t5[e].truckStatus=setTruckStatus(t5, p, e, i, maxWeight);
        e++; i++;
    }

    //for loop to store packages that could not be shipped in time
    for(;i<numPackages; i++){

        //function to store unshipped package
        t6=loadTrucks(t6, p, f, i, maxWeight);
        f++;
    }

    int truckNum=1;

    printTruckStatus(t1, a-1, truckNum++); printTruckStatus(t2, b-1, truckNum++); printTruckStatus(t3, c-1, truckNum++); printTruckStatus(t4, d-1, truckNum++); printTruckStatus(t5, e-1, truckNum++);
    printUnshippedItem(t6, f-1);
}

int main()
{
    int option;

    //function to display starting menu
    displayMenu();

    //while loop that allow program to loop for new shipping arrangement
    while(validOption()!=2){
        vector<packages> p;
        int numPackages, maxWeight;

        //function to obtain maximum weight a truck is allowed to carry
        maxWeight=getMaxWeight();

        //function to obtain number of oversized items of the day
        numPackages=getNumPackages();

        //function to register all oversized items into the system
        //require input of priority and weight for each oversized item
        //minimum weight requirement is set to 50kg for each oversized item
        p=regPackages(p, numPackages, maxWeight);

        //function to sort oversized items according to their priority followed by the register sequence using a comparator function as third parameter
        //("Sorting an STL vector on two values", n.d.)
        sort(p.begin(), p.end(), compare);

        //function to load oversized items into trucks
        loadPackages(p, maxWeight, numPackages);

        displayMenu();
    }

    cout<<"\nLogging out"<<endl;

    return 0;
}
