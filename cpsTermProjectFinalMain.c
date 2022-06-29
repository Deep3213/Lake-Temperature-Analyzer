#include <stdio.h>
#include <string.h>

//used for indexes in avg value arrays to avoid having too many variables

struct Lake{
    double temps[366];
    double averageTemp;
    double averageSummerTemp;
    double averageWinterTemp;
    int warmestDay;//index of the warmest day
    int coldestDay;//index of the coldest day
    int warmestOccurrences[100];//keeps track of all dates on which max temp occurs
    int coldestOccurrences[100];//keeps track of all dates on which min temp occurs
    int swimAbleDays;
    int frozenDays;
    int aboveOrBelowAverage;
    const char* name;
};
void dateCreator (int day) {
    day++;
        if (day < 32 && day >=1) {

            printf("January %d ", day);
        }

        else if (day >= 32 && day < 61) {

            day = day - 31;

            printf("February %d ", day);



        }

        else if (day >= 61 && day < 92) {

            day = day - 60;

            printf("March %d ", day);

        }

        else if (day >= 92 && day < 122) {

            day = day - 91;

            printf("April %d ", day);


        }

        else if (day >= 122 && day < 153) {

            day = day - 121;

            printf("May %d ", day);

        }

        else if (day >= 154 && day < 183) {

            day = day - 152;

            printf("June %d ", day);


        }

        else if (day >= 183 && day < 214) {

            day = day - 182;

            printf("July %d ", day);


        }

        else if (day >= 214 && day < 245) {

            day = day - 213;

            printf("August %d ", day);

        }

        else if (day >= 245 && day < 275) {

            day = day - 244;

            printf("September %d ", day);

        }

        else if (day >= 275 && day < 306) {

            day = day - 274;

            printf("October %d ", day);

        }

        else if (day >= 306 && day < 336) {

            day = day - 305;

            printf("November %d ", day);
        }

        else if (day >= 336 && day <= 366) {

            day = day - 335;

            printf("December %d ", day);

        }
        else{printf("error\n");}
    }

//checks the amount of days each lake has a temp greater than 20 degrees
void swimableDays(struct Lake *lakes[6]){
    double swimmingTemp = 20;
    for(int j = 0; j < 6; j++){
        lakes[j]->swimAbleDays = 0;//need to initialize value
        for(int i = 0; i < 366; i++){
            if(lakes[j]->temps[i]>=swimmingTemp){
                lakes[j]->swimAbleDays++;
            }
        }
    }
}
//checks number of days each lake is below zero
void frozenDays(struct Lake *lakes[6]) {
    double frozenTemp = 0;
    for (int j = 0; j < 6; j++) {
        lakes[j]->frozenDays = 0;//need to initialize value
        for (int i = 0; i < 366; i++) {
            if (lakes[j]->temps[i] <= frozenTemp) {
                lakes[j]->frozenDays++;
            }
        }
    }
}

//min finder for selection sort, start and end refer to index range of desired subarray
//rather than declaring many functions with extremely similar code, we declare one function that can perform the desired operation for each case
int maxIndexFinder(struct Lake lakes[],int start, int end,char type){
    double max = 0;
    int index;
    if(type == 's'){
        for (int i = start; i < end; i++) {
            if (lakes[i].averageSummerTemp > max) {
                max = lakes[i].averageSummerTemp;
                index = i;
            }
        }
        return index;
    }
    else if(type == 'w'){
        for (int i = start; i < end; i++) {
            if (lakes[i].averageWinterTemp > max) {
                max = lakes[i].averageWinterTemp;
                index = i;
            }
        }
        return index;
    }else {
        for (int i = start; i < end; i++) {
            if (lakes[i].averageTemp > max) {
                max = lakes[i].averageTemp;
                index = i;
            }
        }
        return index;
    }

}
void tempRanking(struct Lake *avgOrder, double overallAvg,int temps){
    int maxIndex;
    struct Lake temp;

    for(int  i = 0; i < temps - 1; i ++) {
        maxIndex = maxIndexFinder(avgOrder, i, temps,'g');
        if(i!=maxIndex){
            temp = avgOrder[maxIndex];
            avgOrder[maxIndex] = avgOrder[i];
            avgOrder[i] = temp;
        }
    }
    for(int i = 0; i <6; i++){
        if(avgOrder[i].averageTemp> overallAvg){
            avgOrder[i].aboveOrBelowAverage = 1;
        }
        else{
            avgOrder[i].aboveOrBelowAverage = 0;
        }
    }
}

void tempSeasonalRanking(struct Lake avgOrder[],int temps,char ranking){
    int maxIndex;
    struct Lake temp;

    for(int  i = 0; i < temps - 1; i ++) {
        maxIndex = maxIndexFinder(avgOrder, i, temps,ranking);
        if(i!=maxIndex){
            temp = avgOrder[maxIndex];
            avgOrder[maxIndex] = avgOrder[i];
            avgOrder[i] = temp;
        }
    }

}


void avgTemp( struct Lake *lakes[6], double *overAllAvg, int start, int end){//unfortunately due to the difference of summer winter and overall average calculations they need different functions to avoid
                                                                            // the extra labour of passing unnecessary values, and avoid case checks
    double sum;
    double amt = end + 1 - start;

//caclulates sum of all temperatures and divides by total number of temperatures for each lake to find average
        for (int j = 0; j < 6; j++) {
            sum = 0;
            for (int i = start - 1; i < end; i++) {
                sum += lakes[j]->temps[i];
            }
            lakes[j]->averageTemp = sum / amt;

        }
        sum = 0;
        //takes average of each lake's average to find the overall average
        for (int i = 0; i < 6; i++) {
            sum += lakes[i]->averageTemp;
        }
        *overAllAvg = (sum/6);
    printf("average temp calc done: General\n");

}
void aboveOrBelow(int status){//used to check if above or below average
    if(status){
        printf("above average\n");
    }
    else{
        printf("below average\n");
    }
}
//finds average temperature of each lake during the summer.
void avgTempSummer(struct Lake *lakes[6],int start, int end,int temps){
    double sum;
    double amt = end - start + 1;//number of data points for mean

    for(int j = 0; j < temps; j++) {//same as regular average calculates but including only summer temperatures
    sum = 0;

        for (int i = start-1; i < end; i++) {
            sum += lakes[j]->temps[i];
        }
        lakes[j]->averageSummerTemp = sum/amt;
    }
    printf("average temp calc done: Summer\n");
}
//finds average winter temperature of each lake, compatible with both years
void avgTempWinter(struct Lake *lakes[6],int start1, int end1,int start2,int end2,int temps){
    //winter essentially has 2 sections in the general temperature array from which we want values, so it's simpler too just use multiple loops
    double sum;
    //takes total amount of temperatures to use when calculating mean
    double amt = end1 - start1 + 1 + end2 - start2 + 1;
    for(int j = 0; j < temps; j++) {//same as summer and general average calculations, however because winter temperatures are in different parts of the arrays we go through each part seperately.
        sum = 0;

        for (int i = start1-1; i < end1; i++) {
            sum += lakes[j]->temps[i];
        }
        for (int i = start2-1; i < end2; i++) {
            sum += lakes[j]->temps[i];
        }
        lakes[j]->averageWinterTemp = sum/amt;
    }
    printf("average temp calc done: Winter\n");
}


//general function for reading files
void data(const char* filename,struct Lake *Sup, struct Lake *Mich, struct Lake *Huron, struct Lake *Erie, struct Lake *Ont, struct Lake * StC){
int i = 0;
FILE *in = fopen(filename,"r");

    while(!feof(in)){
        // reads through formatted given data file and stores all temperatures for each lake in their respective struct
        fscanf(in,"%lf %lf %lf %lf %lf %lf",&Sup->temps[i],&Mich->temps[i],&Huron->temps[i],&Erie->temps[i],&Ont->temps[i],&StC->temps[i]);

        i++;

    }
    fclose(in);
}

void warmestColdest(struct Lake *lakes[6]){

    double maxSuperior = 0, maxMichigan = 0, maxHuron = 0, maxErie = 0, maxOntario = 0, maxStClair = 0,
            minSup = 999, minMic = 999, minHur = 999, minEri = 999, minOnt = 999, minSt = 999;

    int warmSupday, warmMichday, warmHurday, warmErieday, warmOntday, warmStCday, coldSupday, coldMichday, coldHurday, coldErieday, coldOntday, coldStCday;


        for(int i = 0; i < 366; i++){
            if (lakes[0]->temps[i] > maxSuperior) {
                maxSuperior = lakes[0]->temps[i];
                warmSupday = i;												//Stores the day of the warmest Temperature for lake Superior
            }

            else if (lakes[0]->temps[i] < minSup) {
                minSup = lakes[0]->temps[i];
                coldSupday = i;
            }

            if (lakes[1]->temps[i] > maxMichigan) {
                maxMichigan = lakes[1]->temps[i];
                warmMichday = i;												//Stores the day of the warmest Temperature for lake Michigan
            }

            else if (lakes[1]->temps[i] < minMic) {
                minMic = lakes[1]->temps[i];
                coldMichday = i;
            }

            if (lakes[2]->temps[i] > maxHuron) {
                maxHuron = lakes[2]->temps[i];
                warmHurday = i;												//Stores the day of the warmest Temperature for lake Huron
            }

            else if (lakes[2]->temps[i] < minHur) {
                minHur = lakes[2]->temps[i];
                coldHurday = i;
            }

            if (lakes[3]->temps[i] > maxErie) {
                maxErie = lakes[3]->temps[i];
                warmErieday = i;												//Stores the day of the warmest Temperature for lake Erie
            }

            else if (lakes[3]->temps[i] < minEri) {
                minEri = lakes[3]->temps[i];
                coldErieday = i;
            }

            if (lakes[4]->temps[i] > maxOntario) {
                maxOntario = lakes[4]->temps[i];
                warmOntday = i;												//Stores the day of the warmest Temperature for lake Ontario
            }

            else if (lakes[4]->temps[i] < minOnt) {
                minOnt = lakes[4]->temps[i];
                coldOntday = i;

            }

            if (lakes[5]->temps[i] > maxStClair) {
                maxStClair = lakes[5]->temps[i];
                warmStCday = i;												//Stores the day of the warmest Temperature for lake St Clair
            }

            else if (lakes[5]->temps[i] < minSt) {
                minSt = lakes[5]->temps[i];
                coldStCday = i;

            }



    }

    double warmDays[] = {warmSupday, warmMichday, warmHurday, warmErieday, warmOntday, warmStCday};

    double warmLakes[] = {maxSuperior, maxMichigan, maxHuron, maxErie, maxOntario, maxStClair};

    double coldDays[] = {coldSupday, coldMichday, coldHurday, coldErieday, coldOntday, coldStCday};

    double coldLakes[] = {minSup, minMic, minHur, minEri, minOnt, minSt};
    //iterates through temperatures again to find all max temp occurences
    for(int j = 0; j < 6; j++){
        int x = 0;
        for(int i = 0; i < 366; i++){
            if(lakes[j]->temps[i] == warmLakes[j]){
                lakes[j]->warmestOccurrences[x]=i;
                x++;
            }

        }
        lakes[j]->warmestOccurrences[x]=1000;
    }
    for(int j = 0; j < 6; j++){//iterates through temperatures again to find all min temp occurences
        int x = 0;
        for(int i = 0; i < 366; i++){
            if(lakes[j]->temps[i] == coldLakes[j]){
                lakes[j]-> coldestOccurrences[x]=i;
                x++;
            }

        }
        lakes[j]->coldestOccurrences[x]=1000;
    }





    int hotLake, freezeLake;

    double maxLake = 0, maxDate = 0, minLake = 999, minDate = 0;

    for (int w = 0; w < 6; w++) {//finds overall warmest temperature

        if (warmLakes[w] > maxLake) {

            maxLake = warmLakes[w];

            maxDate = warmDays[w];

            hotLake = w;

        }
    }

    for (int c = 0; c < 6; c++) {//finds overall coldest temperature

        if (coldLakes[c] < minLake) {

            minLake = coldLakes[c];

            minDate = coldDays[c];

            freezeLake = c;
        }
    }

    for(int j = 0; j < 6; j++){//prints lakes, their warmest temps and when they occur
        printf("\nLake: %-10s warmest temperature: %-4.2lf Occurrences: ", lakes[j]->name,warmLakes[j]);
        int i = 0;
        do {
            dateCreator(lakes[j]->warmestOccurrences[i]);
            i++;
            if(i == 5) {
                printf("\n");
            }
            if(i == 12) {
                printf("\n");
            }


        }while((lakes[j]->warmestOccurrences[i]!=1000));

    }
    printf("\n");
    for(int j = 0; j < 6; j++){//prints lakes, their coldest temps and when they occur
        printf("\nLake: %-10s coldest temperature: %-4.2lf Occurrences: ", lakes[j]->name,coldLakes[j]);
        int i = 0;
        do {
            dateCreator(lakes[j]->coldestOccurrences[i]);
            i++;
            //new lines improve clarity
            if(i == 3) {
                printf("\n");
            }
            if(i == 11) {
                printf("\n");
            }

        }while((lakes[j]->coldestOccurrences[i]!=1000));

    }
    printf("\n");
    printf("\nThe warmest temperature of all the lakes is %.2lf and it occurs at lake %s on ", maxLake, lakes[hotLake]->name); dateCreator(maxDate);
    printf("\nThe coldest temperature of all the lakes is %.2lf and it occurs at lake %s on ", minLake, lakes[freezeLake]->name); dateCreator(minDate);

}
//calculates% difference of 2020temp from 2019 temp
double difference(double temp2020, double temp2019){
    double returnVal = (temp2020-temp2019)*100/temp2019;
    if(returnVal<0){returnVal = returnVal*-1;}
    return returnVal;
}
//checks if two lake arrays have a matching order
void orderCompare(struct Lake *dataset1,struct Lake *dataset2){
    int same = 0;//keeps track of how many lakes in dataset2 mach order of data set 1
    for(int i = 0; i < 6; i++){
        if(strcmp(dataset1->name,dataset2->name)==0){
            same++;
        }
    }
    if(same == 6){
        printf("Order is the same");
    }
    else{
        printf("Order has deviated");
    }
}
int main() {
    //day will be treated as array index+1
    //year is irrelevant as each file contains data for one year only


    //struct declaration and assignment
    struct Lake superior, Michigan, Huron, Erie, Ontario, StClair;
    superior.name = "Superior";
    Michigan.name = "Michigan";
    Huron.name = "Huron";
    Erie.name = "Erie";
    Ontario.name = "Ontario";
    StClair.name = "St.Clair";
    struct Lake *lakes[6];
    struct Lake lakes2019[6];
    struct Lake avgOrder[6];
    struct Lake summerOrder[6];
    struct Lake winterOrder[6];

    double overallAvg2019,overallAvg2020;
    //2019 data taken in and stored first for later use
    data("/Users/gleblevashov/Desktop/C:C++ Projects/2019data.txt",&superior,&Michigan,&Huron
       ,&Erie,&Ontario,&StClair);
    //passing of lakes to pointer array for easy access
    lakes[0] = &superior;
    lakes[1] = &Michigan;
    lakes[2] = &Huron;
    lakes[3] = &Erie;
    lakes[4] = &Ontario;
    lakes[5] = &StClair;
    avgTemp(lakes, &overallAvg2019, 1, 365);




    for(int i = 0; i < 6; i ++){
        lakes2019[i] = *lakes[i];
    }
    tempRanking(lakes2019,overallAvg2019,6);
    data("/Users/gleblevashov/Desktop/C:C++ Projects/2020Data",&superior,&Michigan,&Huron
            ,&Erie,&Ontario,&StClair);
    lakes[0] = &superior;
    lakes[1] = &Michigan;
    lakes[2] = &Huron;
    lakes[3] = &Erie;
    lakes[4] = &Ontario;
    lakes[5] = &StClair;
    avgTemp(lakes,&overallAvg2020,1,366);

    swimableDays(lakes);
    frozenDays(lakes);
    avgTempSummer(lakes,172,265,6);
    avgTempWinter(lakes,1,79,355,366,6);
    for(int i = 0; i < 6; i ++){
        avgOrder[i] = *lakes[i];
        summerOrder[i] = *lakes[i];
        winterOrder[i] = *lakes[i];
    }
    tempRanking(avgOrder,overallAvg2020,6);

    tempSeasonalRanking(summerOrder,6,'s');

    tempSeasonalRanking(winterOrder,6,'w');




    int run = 1;
    int decision;
    printf("\nWhen using this program, recall that all temperatures are given in degrees celsius.\n");
    while(run){
        printf("Please select one option from the following:\n\n"
               "Enter 1 to view yearly averages ranked from warmest to coldest\n"
               "Enter 2 to view the warmest and coldest lake temperatures as well as their dates\n"
               "Enter 3 to view the summer average temperatures from warmest to coldest compared to yearly averages\n"
               "Enter 4 to view the winter average temperatures from warmest to coldest compared to yearly averages\n"
               "Enter 5 to view the number of swimable days for each lake\n"
               "Enter 6 to view the number of days each lake is frozen\n"
               "Enter 7 to compare 2019 and 2020 averages\n"
               "Enter 8 to close the program\n");
        scanf("%d",&decision);
        switch(decision){

            case 1:
                printf("The following relates to parts one and two of this commission.\n");
                printf("Lake: %-10s was warmest on average, with an average of: %2.2lf which is above the over all average of %2.2lf\n",avgOrder[0].name,avgOrder[0].averageTemp,overallAvg2020);
                for(int i = 1; i < 5; i++){
                    printf("Lake: %-10s had an average of: %2.2lf and was ",avgOrder[i].name,avgOrder[i].averageTemp);
                    aboveOrBelow(avgOrder[i].aboveOrBelowAverage);

                }
                printf("Lake: %-10s was coldest on average, with an average of: %0.2lf which is below the over all average of %0.2lf\n",avgOrder[5].name,avgOrder[5].averageTemp,overallAvg2020);
                break;
            case 2:
                printf("The following relates to parts three and four of this commission.\n");
                //warmest and coldest days + overall warmest and coldest
                warmestColdest(lakes);
                break;
            case 3:printf("The following relates to part five of this commission.\n");
                printf("Comparison of average Summer temperatures to average temperatures\n(Both datasets have been sorted from warmest to coldest)\n\n");
                for(int i = 0; i < 6; i ++){
                    printf("Lake: %-10s Average Summer temp: %2.2lf %-3s Lake: %-10s Average temp: %2.2lf\n",summerOrder[i].name,summerOrder[i].averageSummerTemp,"",avgOrder[i].name,avgOrder[i].averageTemp);
                }
                orderCompare(avgOrder,summerOrder);
                break;
            case 4:printf("The following relates to part six of this commission.\n");
                printf("Comparison of average winter temperatures to average temperatures\n(Both datasets have been sorted from warmest to coldest)\n\n");
                for(int i = 0; i < 6; i ++){
                    printf("Lake: %-10s Average Winter temp: %2.2lf %-3s Lake: %-10s Average temp: %2.2lf\n",winterOrder[i].name,winterOrder[i].averageWinterTemp,"",avgOrder[i].name,avgOrder[i].averageTemp);
                }
                orderCompare(avgOrder,winterOrder);
                break;
            case 5:printf("The following relates to part seven of this commission.\n");
                //swimable days;
                for(int i = 0; i < 6; i++){
                    printf("Lake: %-10s was swim-able for: %-4d days of the year.\n",lakes[i]->name,lakes[i]->swimAbleDays);
                }
                break;
            case 6:
                //frozen days;
                printf("The following relates to part eight of this commission.\n");
                for(int i = 0; i < 6; i++){
                    printf("Lake: %-10s was frozen for: %-4d days of the year.\n",lakes[i]->name,lakes[i]->frozenDays);
                }
                break;
            case 7:
                //compare 2020 and 2019
                printf("The following relates to part nine of this commission.\n");
                printf("Lake     2020 Temperature   2019 Temperature   Change From 2019   Percent Difference From 2019   \n");
                for(int i = 0; i < 6; i ++) {
                    printf("%-19s %-17.2lf  %-19.2lf %-28.2lf %0.2lf%c\n", avgOrder[i].name,avgOrder[i].averageTemp,lakes2019[i].averageTemp,(avgOrder[i].averageTemp-lakes2019[i].averageTemp),
                           difference(avgOrder[i].averageTemp,lakes2019[i].averageTemp),'%');
                }
                printf("%-19s %-17.2lf  %-19.2lf %-28.2lf %0.2lf%c\n","Combined",overallAvg2020,overallAvg2019,(overallAvg2020-overallAvg2019)
                       ,difference(overallAvg2020,overallAvg2019),'%');

                break;
            case 8:
                run = 0;
                break;
            case 69:
                printf("Nice :)\n");
                break;
            default:
                printf("Please choose a valid option\n");
                break;
        }
        //for clarity
        printf("\n\n");
    }

    return 0;
}
