//knights tour
//ckrausko
//Cody Krauskopf
//this program solve the knights tour at any given space
//it uses a linked list to store the user choices
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <stack>
#include <vector>
#include <fstream>
using namespace std;




//board

 int arr [8][8];
//struct to push onto stack
 struct Location{
    int x;
    int y;
    bool movesArray[8];

 };

 stack <Location> locate;


 int moveX[8] = { -1, 2, 1, -1, -2, -2, 1, 2 };
 int moveY[8] = { -2, 1, 2, 2, 1, -1,  -2, -1 };




//intializes the board
 void board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            arr[i][j] = -1;
        }
    }

 }// end board

//returns true if the move is legal
bool safe(int row, int col) {

        if ((row >= 0 && row < 8) && (col >= 0 && col < 8) && arr[row][col] == -1){

            return true;

            }
            return false;
}// end safe

//prints out the board
void print(){
    ofstream myFile;
    myFile.open ("output.txt", ios::out | ios::app);

    for(int i = 0; i < 8; i++){
        myFile << "\n ------------------------\n";
        for(int j = 0; j < 8; j++){
            myFile << "|";
                myFile << setw(2) << setfill('0') << arr[i][j];

        }

    }

myFile << "\n ------------------------\n";

myFile.close();
}// end print
//counts up the possible moves at any given square and returns the result
int moves(int nextMoveX, int nextMoveY){
    int bestMove = 0;
        for( int j = 0; j < 8; j++){
            if(safe(nextMoveX+moveX[j],nextMoveY+moveY[j])){
                    bestMove += 1;

            }

        }
        return bestMove;

}//end moves







//solves the knights tour for given x and y
void solveBoard(int x, int y){
     board();

    arr[x][y] = 0; // loading array with starting position
    int nextMoveX, nextMoveY; // next move
    Location top;
    top.x = x;// initial start
    top.y = y;//initial start
    for(int i = 0; i < 8; i++){
        top.movesArray[i] = safe(top.x+moveX[i], top.y+moveY[i]);

    }

    locate.push(top); // loading stack with initial position
    int bestMove[8]; // array to sort best move
    int counter = 0; // move counter

    while(counter < 63){


        top = locate.top(); // check top of stack for current position
        x = top.x;
        y = top.y;


            //loops through the 8 move choices


                // using a stack to solve final steps
                if( counter >= 33){


                    for(int i = 0; i < 8; i++){
                            top = locate.top();

                            if(top.movesArray[i]){


                                top.movesArray[i] = false;
                                locate.pop();
                                locate.push(top);


                                counter++;
                                nextMoveX = x + moveX[i];
                                nextMoveY = y + moveY[i];
                                arr[nextMoveX][nextMoveY] = counter;
                                top.x = nextMoveX;
                                top.y = nextMoveY;


                                //loads up array with possible moves
                                for(int j = 0; j < 8; j++){
                                    top.movesArray[j] = safe(nextMoveX+moveX[j], nextMoveY+moveY[j]);

                                }
                                //push location onto stack
                                locate.push(top);


                                break;
                            }
                            //if no more valid moves from this space pop off
                            if(i == 7){

                                arr[top.x][top.y]= -1;
                                locate.pop();
                                counter --;

                                top = locate.top();


                                break;


                            }




                    }
                }

                // heuristics for first 32 moves
                else{
                    for(int i = 0; i < 8; i++){
                        bestMove[i] = -1; // resets # of potential moves at next space


                            // test next position
                        nextMoveX = x + moveX[i];
                        nextMoveY = y + moveY[i];

                        //if safe count number of moves on next space
                        if(safe(nextMoveX,nextMoveY)){


                            //count number of moves available at next space
                            for( int j = 0; j < 8; j++){
                                if(safe(nextMoveX+moveX[j],nextMoveY+moveY[j])){
                                    bestMove[i] += 1;

                                }


                            }


                        }
                        //if on last move check for one with least moves available
                        if(i ==7){

                            int least = 8;
                            int pos = -1;
                            int L;

                            for(L = 0; L < 8; L++){
                                if(bestMove[L] < least && bestMove[L] != -1){
                                    least = bestMove[L];
                                    pos = L;

                                }

                            } // end for



                            nextMoveX = x + moveX[pos];
                            nextMoveY = y + moveY[pos];
                            //if move is legal make the move and update
                            if(safe(nextMoveX,nextMoveY)){
                            counter++;

                            arr[nextMoveX][nextMoveY] = counter;

                            top.x = nextMoveX;
                            top.y = nextMoveY;

                            for(int e = 0; e < 8; e++){
                                top.movesArray[e] = safe(nextMoveX + moveX[e],nextMoveY + moveY[e]);

                            }

                            locate.push(top);


                            }



                        } // end if (i=7)

                    } // end for i
                } // end else

            //if last move has been made print the board
            if(counter == 63){
                    print();

            }


    } // end while


} // end solve






//Linked List class
class List{
    private:
        struct node{
            int x;
            int y;
            node* next;
        };


        struct node* head;
        struct node* curr;
        struct node* temp;
    public:
        List();
        void add(int x, int y);
        void deleteNode(int x, int y);
        void print();
        void solve();


};

List::List(){

head = NULL;
curr = NULL;
temp = NULL;
}
//adds a new node to the end of the list
void List::add(int x, int y){
    struct node* n = new node;
    n->next = NULL;
    n->x = x;
    n->y = y;

    if(head != NULL){
        curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;

    }
    else{
        head = n;

    }

}

void List::deleteNode(int x, int y){
    struct node* delPtr = NULL;
    temp = head;
    curr = head;
    while((curr != NULL) && (curr->x != x) && (curr->y != y) ){
            temp = curr;
            curr = curr->next;

    }

    if(curr == NULL){
    cout << "pair not found";
    delete delPtr;
    }

    else{
        delPtr = curr;
        curr = curr->next;
        temp->next = curr;
        if(delPtr == head){
            head = head->next;
            temp = NULL;

        }
        delete delPtr;
    }





}
//print out
void List::print(){
    curr = head;
    while(curr != NULL){

        cout << curr->x;
        cout << curr->y << endl;
        curr = curr->next;
    }




}
//loops through list solving each initial position
void List::solve(){
    curr = head;
    while(curr != NULL){


        solveBoard(curr->x,curr->y);
        curr = curr->next;
    }


}













int main(){
List initialPos;
ofstream file;
file.open ("output.txt", ios::out | ios::app);
bool userInput = true;
char input;
while(userInput){

    file << "1) Enter additional starting position" << endl;
    file << "2) Print list"<< endl;
    file << "3) Delete ordered pair"<< endl;
    file << "4) Modify ordered pair"<< endl;
    file << "5) Solve for initial positions in list"<< endl;
    file << "6) Exit"<< endl;

    cin >> input;

    switch(input){
    case '1':
        int x;
        int y;
        file << "Enter x coord" << endl;
        cin >> x;
        file << "Enter Y coord" << endl;
        cin >> y;
        if(x >=0 && x <=7 && y >=0 && y<=7){
            initialPos.add(x,y);
        }
        else{
            file << "please enter coords between (0,0) and (7,7)" << endl;
        }
        break;
    case '2':
        initialPos.print();
        break;
    case '3':


        file << "Enter the x coord of ordered pair to delete" << endl;
        cin >> x;
        file << "Enter the y coord of ordered pair to delete" << endl;
        cin >> y;
        initialPos.deleteNode(x,y);
        break;
    case '4':

        file << "Enter the x coord of ordered pair to modify" << endl;
        cin >> x;
        file << "Enter the y coord of ordered pair to modify" << endl;
        cin >> y;

        if(x >=0 && x <=7 && y >=0 && y<=7){
            initialPos.deleteNode(x,y);
            file << "Enter the new x coord" << endl;
            cin >> x;
            file << "enter the new y coord" << endl;
            cin >> y;
            initialPos.add(x,y);
            file << "ordered pair modified and moved to end of list" << endl;
        }
        else{
            file << "please enter coords between (0,0) and (7,7)" << endl;
        }


        break;
    case '5':
        initialPos.solve();
        break;
    case '6':
        userInput = false;
        break;



    }



}


}
