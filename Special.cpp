#include <iostream>

int random(int min, int max){
    int number = min + rand() % (max - min + 1);
    return number;
}

void cellsFill1(char*** cells, bool*** live, int gen){
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            live[gen][i][j] = random(0, 1);
            if(live[gen][i][j] == true){
                cells[gen][i][j] = '*';
            }else{
                cells[gen][i][j] = '-';
            }
        }
    }
}

void printCells(char*** cells, int gen){
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            std::cout << cells[gen][i][j] << "";
        }
        std::cout << std::endl;
    }
}

void changeCell(char*** cells, bool*** live, int i, int j, int gen){
    int count = 0;
    int a = 0;
    int b = 0;
    for(int d = 0; d < 8; d++){
        if(d == 0 || d == 1 || d == 2){
            a = i + 1;
        }else if(d == 3 || d == 7){
            a = i;
        }else{
            a = i - 1;
        }
        if(d == 0 || d == 6 || d == 7){
            b = j - 1;
        }else if(d == 1 || d == 5){
            b = j;
        }else{
            b = j + 1;
        }
        if(a == -1){
            a = 49;
        }else if(a == 50){
            a = 0;
        }
        if(b == -1){
            b = 49;
        }else if(b == 50){
            b = 0;
        }
        if(live[gen][a][b] == true){
            count++;
        }
        if(count == 4 && live[gen][i][j] == true){
            cells[gen][i][j] = '-';
            live[gen][i][j] = false;
            break;
        }
    }
    if(count <= 1 && live[gen][i][j] == true){
        cells[gen][i][j] = '-';
        live[gen][i][j] = false;
    }else if((count == 2 || count == 3) && live[gen][i][j] == false){
        cells[gen][i][j] = '*';
        live[gen][i][j] = true;
    }
}

void changedGen(char*** cells, bool*** live, int gen){
    cells[gen] = cells[gen - 1];
    live[gen] = live[gen - 1];
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            changeCell(cells, live, i, j, gen);
        }
    }
}

void comparison(bool*** live, int gen, bool off){
    for(int i = 0; i < gen; i++){
        int count = 0;
        int countDead = 0;
        for(int j = 0; j < 50; j++){
            for(int l = 0; l < 50; l++){
                if(live[gen][j][l] == live[i][j][l]){
                    count++;
                }else{
                    break;
                }
                if(live[gen][j][l] == false){
                    countDead++;
                }else{

                }
            }
            if(count != 50){
                break;
            }
        }
        if(count == 2500){
            off = true;
            break;
        }
    }
    for(int i = 0; i < gen; i++){
        int countDead = 0;
        for(int j = 0; j < 50; j++){
            for(int l = 0; l < 50; l++){
                if(live[gen][j][l] == false){
                    countDead++;
                }else{
                    break;
                }
            }
            if(countDead != 50){
                break;
            }
        }
        if(countDead == 2500){
            off = true;
            break;
        }
    }
}

int main(){
    srand(time(NULL));
    char ***cells = new char**[100000];
    bool ***live = new bool**[100000];
    bool off = false;
    for(int i = 0; i < 50; i++){
        cells[i] = new char*[50];
        live[i] = new bool*[50];
        for(int j = 0; j < 50; j++){
            cells[i][j] = new char[50];
            live[i][j] = new bool[50];
        }
    }
    int gen = 0;
    cellsFill1(cells, live, gen);
    std::cout << gen + 1 << " generation:\n" << std::endl;
    printCells(cells, gen);
    gen++;
    while(off != true){
        std::cout << "\nInput anything to continue: ";
        std::string anyth = "Nice";
        std::cout << std::endl;
        changedGen(cells, live, gen);
        std::cout << gen + 1 << " generation:\n" << std::endl;
        printCells(cells, gen);
        comparison(live, off, gen);
        gen++;
    }
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            delete[] cells[i][j];
        }
    }
    delete[] cells;
}