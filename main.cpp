#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

/*  READ ME
 *  Final project: Craps game
 *  Names: Luciana Valdivieso, Gustavo Ter�n
 *  Student code: 00320684, 00324422
 */

using namespace std;

enum Spot{FILLED, UNFILLED};
enum Order{FIRST, SECOND, THIRD, FOURTH, LAST};

int winning_number; //variable para el valor ganador del jugador 1 

int check_tie(int turns[], int numPlayers){ //check tie between players
    int i;
    int tie = 0;
    //sort array
    std::sort(turns, turns + numPlayers); //order the turns with players 
    //Check for ties
    for (i = 0; i < (numPlayers - 1); ++i){ //loop for check ties
        if (turns[i] == turns[i + 1]){
            cout << "There is a tie, lets roll again\n";
            tie = 1;
        }
    }
    return tie;
}

void youWin (){ //print this if you win
    cout << "Congratulations! You win" << endl << endl;
}

void youLose (){ //print this if you lose
    cout << "Sorry, you lost" << endl << endl;
}

void Continue (){ //print this if did not win or lose
    cout << "You did not win or lose, next player's turn" << endl << endl;
}

class PlayerSpot{ //class for the players. 
public:
    PlayerSpot(){ //define the attributes for players
        status = UNFILLED;
        turn = FIRST;
        loses = 0;
        winnings = 0;
        betAmount = 0;
    }

    Spot getSpotStatus(){ //get the players's status
        return status;
    }
    void setSpotStatus(Spot definedStatus){ //set the player's status
        status = definedStatus;
    }
    void setTurn(Order definedOrder){ //set the order
        turn = definedOrder;
    }
    Order getOrder(){ //get the order
        return turn;
    }
    double getBetAmount(){ //get bettings
        return betAmount;
    }
    void setBetAmount(double dollars){ //set bettings
        betAmount = dollars;
    }
    int rollDice (){ //first drop for see the order
        int throw_1 = 1 + rand() % 6;
        int throw_2 = 1 + rand() % 6;
        int dice_sum = throw_1 + throw_2;
        cout << "Player rolled " << throw_1 << " + " << throw_2 << " = " << dice_sum << "\n";
        return dice_sum;
    }
    int First_rollDice(int total_bet_amount){ //first roll only for first player
        int result; //lost_bet_amount(total_bet_amount); //won_bet_amount(total_bet_amount);
        int dice_sum = rollDice();
        if (dice_sum == 7 || dice_sum == 11){ //condition for win
            result = 1;
            youWin();//the game ends, the report is displayed
            won_bet_amount(total_bet_amount); //total of bettings
            report(); //print the report 
            return result;
        }
        else if (dice_sum == 2 || dice_sum == 3 || dice_sum == 12){ //conditions for lose
            result = 2;
            youLose();//the game ends, the report is displayed
            lost_bet_amount(total_bet_amount); //total of bettings
            report(); //print the report
            return result;
        }
        else{ //if the return is diferent of the before conditions
            result = 3;
            Continue();//the game continues, next player's turn
            return result;
        }
    }
    int Second_rollDice (int total_bet_amount, int winning_number){ //condition only for the second and more players, without the first player
        int result;
        int dice_sum = rollDice(); 
        if (dice_sum == winning_number){ //value for win
            result = 1;
            youWin();//the game ends, the report is displayed
            won_bet_amount(total_bet_amount); //total bettings
            report();//print the report
            return result;
        }
        else if (dice_sum == 7){
            result = 2;
            youLose();//the game ends, the report is displayed
            lost_bet_amount(total_bet_amount);
            report();//print the report
            return result;
        }
        else {
            result = 3;
            Continue();//the game continues, next player's turn
            return result;
        }
    }
    void report (){ //report for each player depending on the case
        cout << "REPORT" << endl;
        cout << "Winnings : " << winnings << endl;
        cout << "Loses : " << loses << endl << endl;
    }
    void won_bet_amount(int bet_total){ //bettings if you win
        int personal_bet = getBetAmount();
        int final_amount = bet_total - personal_bet;
        winnings = final_amount;
    }
    void lost_bet_amount(int bet_total){ //betting if you lose
        int personal_bet = getBetAmount();
        int final_amount = bet_total - personal_bet;
        loses = final_amount;
    }
    bool isNumeric(char text[100]){ //parte para validar las entradas del usuario 
		int val, cont, comp;
		string suplente;
		char letra;
		
		suplente = text;
		comp = suplente.length(); //ve el tama�o de los caracteres
		
		int i, j;
		int begin = 50;
		int finish = 53;
	
		for( int i = 0; i <= comp; i++){
			letra = text[i];
			val = letra;
			for( int j = begin; j <= finish; j++){ //me recorre todos los valores de 50 a 57
				if(val == j){
					cont ++;
				}
			}
		}
		
		if(comp == cont){
			return true;
		}else{
			return false;
		}
	}

private: //private part
    Spot status;
    Order turn;
    double loses;
    double winnings;
    double 	betAmount;
};

int main(){ //begin main

	cout << "\tWelcome to Craps game" << endl;

    srand( time(0)); //randomize the seed
    int numPlayers;
    double betAmountInput;
    int i = 0;

    PlayerSpot playerSpot1, playerSpot2, playerSpot3, playerSpot4, playerSpot5;
    PlayerSpot playerSpots [5] = {playerSpot1, playerSpot1, playerSpot1, playerSpot1, playerSpot1};

    //get the number of players for the game
    char escribe[100];
	
	cout << "Enter the number of players for the game: " << endl; 
	cin >> escribe;
	if(playerSpots[i].isNumeric(escribe)){
		cout << "The number of players is correct" << endl;
		numPlayers = atoi(escribe); //atoi permite cambiar de char a int 
	}else{
		cout << "Invalid character. Please enter only one number between 2 and 5" << endl;
		return main();
	}

    int turns[numPlayers];
    int rolls[numPlayers];
    for (int i = 0; i < numPlayers; ++i){
        // First dice roll for turns
        rolls[i] = playerSpots[i].rollDice();
        turns[i] = rolls[i];
    }
    //check for a tie
	check_tie(turns, numPlayers);
    
    //Assign turns
    for (int i = 0; i < numPlayers; ++i){
        for (int j = 0; j < numPlayers; ++j){
            if (rolls[i] == turns[j]){
                int index_turn = j + 1;
                if (index_turn == 1){
                    playerSpots[i].setTurn(LAST);
                }
                if (index_turn == 2){
                    playerSpots[i].setTurn(FOURTH);
                }
                if (index_turn == 3){
                    playerSpots[i].setTurn(THIRD);
                }
                if (index_turn == 4){
                    playerSpots[i].setTurn(SECOND);
                }
                if (index_turn == 5){
                    playerSpots[i].setTurn(FIRST);
                }
            }
        }
    }
    //The game begins
    int total_bet_amount = 0;
    for (int i = 0; i < numPlayers; ++i){
        if(playerSpots[i].getSpotStatus() == UNFILLED){
            playerSpots[i].setSpotStatus(FILLED);
            cout << "Player " << i + 1 << " how much are you betting? \n";
            cin >> betAmountInput;
            playerSpots[i].setBetAmount(betAmountInput);
            total_bet_amount += betAmountInput;
        }
	}
	
    //Throw dice in order
    for (int i = 0; i < numPlayers; ++i){
        if (playerSpots[i].getOrder() == FIRST){ //first player
            cout << "Player's " << i + 1 << " turn\n";
            int result1 = playerSpots[i].First_rollDice(total_bet_amount);
            if (result1 == 1 ||result1 == 2){
                return  main();
            }
            else if (result1 == 3){
                winning_number = result1;
            }
        }
    }
    for (int i = 0; i < numPlayers; ++i){
        if (playerSpots[i].getOrder() == SECOND){ //second player
            cout << "Player's " << i + 1 << " turn\n";
            int result2 = playerSpots[i].Second_rollDice(total_bet_amount, winning_number);
            if (result2 == 1 || result2 == 2){
                return  main();
            }
        }
    }
    for (int i = 0; i < numPlayers; ++i){
        if (playerSpots[i].getOrder() == THIRD){ //third player
            cout << "Player's " << i + 1 << " turn\n";
            int result3 = playerSpots[i].Second_rollDice(total_bet_amount, winning_number);
            if (result3 == 1 ||result3 == 2){
                return  main();
            }
        }
    }
    for (int i = 0; i < numPlayers; ++i){
        if (playerSpots[i].getOrder() == FOURTH){ //fourth player
            cout << "Player's " << i + 1 << " turn\n";
            int result4 = playerSpots[i].Second_rollDice(total_bet_amount, winning_number);
            if (result4 == 1 ||result4 == 2){
                return  main();
            }
        }
    }
    for (int i = 0; i < numPlayers; ++i){
        if (playerSpots[i].getOrder() == LAST){ //last player
            cout << "Player's " << i + 1 << " turn\n";
            int result5 = playerSpots[i].Second_rollDice(total_bet_amount, winning_number);
            if (result5 == 1 ||result5 == 2){
                return  main();
            }
        }
    }
    return 0; //finish main
}
