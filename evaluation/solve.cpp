#include <bits/stdc++.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

using namespace std;
const string BASE_DIR = "./";
const string LEVEL_DIR = BASE_DIR + "level/";
const string ASTAR_DIR = BASE_DIR + "astar/";
const string ASTAR_RES_DIR = BASE_DIR + "astar_result/";
const string PROMPTS_DIR = BASE_DIR + "prompts/";

int L = 1, R = 80;
int numLevel = R-L+1;
double calcPercent(int x, int y) {
    return 100.0 * x / y;
}
struct Prompt {
    string pipe;
    string enemy;
    string block;
    string elevaion;
    Prompt() {}
    Prompt(string s) {
        stringstream ss(s);
        getline(ss, pipe, ',');
        getline(ss, enemy, ',');
        if (enemy.size() >= 1)
            enemy = enemy.substr(1);
        getline(ss, block, ',');
        if (block.size() >= 1)
            block = block.substr(1);
        getline(ss, elevaion, ',');
        if (elevaion.size() >= 1)
            elevaion = elevaion.substr(1);
    }

    void print() {
        cout << "{" << pipe << '|' << enemy << '|' << block << '|' << elevaion << "}\n";
    }
};

void solvePrompt(string dir) {
    int numPipe = 0, numEnemy = 0, numBlock = 0, numElevation = 0;    
    for (int i = L; i <= R; i++) {
        string filename = to_string(i) + ".txt";
        string filepath = dir + filename;
        string l1, l2;
        ifstream fin(filepath);
        getline(fin, l1);
        getline(fin, l2);
        Prompt p1, p2;
        p1 = Prompt(l1);
        p2 = Prompt(l2);
        if (p1.pipe == p2.pipe)
            numPipe++;
        if (p1.enemy == p2.enemy)
            numEnemy++;
        if (p1.block == p2.block)
            numBlock++;
        if (p1.elevaion == p2.elevaion)
            numElevation++;
    }

    cout << "**************************\n";
    cout << "Pipe: " << calcPercent(numPipe, numLevel) << "%\n";
    cout << "Enemy: " << calcPercent(numEnemy, numLevel) << "%\n";
    cout << "Block: " << calcPercent(numBlock, numLevel) << "%\n";
    cout << "Elevation: " << calcPercent(numElevation, numLevel) << "%\n";
}

void solvePlayable(string dir) {
    int numWin = 0;
    for (int i = L; i <= R; i++) {
        string filename = to_string(i) + ".txt";
        string filepath = dir + filename;
        ifstream fin(filepath);
        string state;
        fin >> state;
        if (state == "WIN")
            numWin++;
    }

    cout << "**************************\n";
    cout << "Playable percent: " << calcPercent(numWin, numLevel) << "%" << endl;
}

vector <string> readMatrix(const string &dir) {
    vector <string> res;
    ifstream fin(dir);
    string x;
    while(getline(fin, x))
        res.push_back(x);
    fin.close();
    return res;
}

const char CP = 'x', CA = 'A';
void solveMAE() {
// Playable, NotPlayable, All
    vector <double> levelDiff;
    vector <int> isPlayable;
    for (int i = L; i <= R; i++) {
        string filename = to_string(i) + ".txt";
        
        string levelPath = LEVEL_DIR + filename;
        string astarPath = ASTAR_DIR + filename;
        string resultPath = ASTAR_RES_DIR + filename;

        ifstream fin(resultPath);
        string res;
        fin >> res;
        isPlayable.push_back(res == "WIN");
        fin.close();

        vector <string> levelMat = readMatrix(levelPath);
        vector <string> astarMat = readMatrix(astarPath);
        // for (auto x: levelMat)
        //     cout << x << endl;
        // cout << endl;
        // for (auto x: astarMat)
        //     cout << x << endl;
        // cout << endl;

        vector <int> diff;

        int c = levelMat[0].length();
        int r = levelMat.size();

        for (int j = 0; j < c; j++) {
            vector <int> posP;
            vector <int> posA;
            bool haveP = false, haveA = false;
            for (int i = 0; i < r; i++) {
                if (levelMat[i][j] == CP) {
                    posP.push_back(i);
                    haveP = true;
                }
                if (astarMat[i][j] == CA) {
                    posA.push_back(i);
                    haveA = true;
                }
            }
            // if (!(haveA && haveP)) break;
            int curDiff = INT_MAX;
            for (int x : posA) for (int y : posP) {
                curDiff = min(curDiff, abs(x - y));
            }

            if (isPlayable.back()) {
                // ufcurDiff = 0;
            } else {
                if (posA.empty()) {
                    if (!posP.empty())
                        curDiff = *max_element(posP.begin(), posP.end());
                } else {
                    curDiff = *max_element(posA.begin(), posA.end());
                }
            }
            if (curDiff == INT_MAX) curDiff = 0;
            diff.push_back(curDiff);
        }

        if (diff.size() == 0) continue;
        levelDiff.push_back(accumulate(diff.begin(), diff.end(), 0) / (1.0 * diff.size()));
        
    }


    // for (auto x:levelDiff) cout << x << ' ';
    double MAEAll = accumulate(levelDiff.begin(), levelDiff.end(), 0) / (1.0 * levelDiff.size());
    double MAEPlayable, MAENotplayable;
    {
        double sumPlayable = 0, numPlayable = 0;
        double sumNotplayable = 0, numNotplayable = 0;
        for (int i = 0; i < levelDiff.size(); i++) {
            if (isPlayable[i]) {
                numPlayable++;
                sumPlayable += levelDiff[i];
            } else {
                numNotplayable++;
                sumNotplayable += levelDiff[i];
            }
        }
        MAEPlayable = numPlayable != 0 ? sumPlayable / numPlayable : 0;
        MAENotplayable = numNotplayable != 0 ? sumNotplayable / numNotplayable : 0;
    }
    
    cout << "**************************\n";
    cout << "MAE\n";
    cout << "All: " << MAEAll << endl;
    cout << "Playable: " << MAEPlayable << endl;
    cout << "Not Playable: " << MAENotplayable << endl;
}


int main(int argc, char** argv) { 
    solvePrompt(PROMPTS_DIR);
    solvePlayable(ASTAR_RES_DIR);
    solveMAE();
}

