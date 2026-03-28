#include <iostream>   
#include <string>     
using namespace std;

enum enPlayChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinnerGame { Palyer = 1, Computer = 2, Drow = 3 };

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinnerGame Winner;
    string WinnerName = "";
};

struct stRoundInfo
{
    short RoundName;
    enPlayChoice PalyerChoice;
    enPlayChoice ComputerChoice;
    enWinnerGame Winner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short HowManyRounds()
{
    short length = 1;
    do
    {
        cout << "How Many Rounds 1 to 10 ? ";
        cin >> length;

    } while (length < 1 || length > 10);

    return length;
}

enPlayChoice ReadPalyerChoice()
{
    short Palyer;
    do
    {
        cout << ("\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ");
        cin >> Palyer;
    } while (Palyer < 1 || Palyer > 3);

    return (enPlayChoice)Palyer;
}

enPlayChoice GetComputerChoice()
{
    return(enPlayChoice)RandomNumber(1, 3);
}

string PirntChoice(enPlayChoice PlayChoice)
{
    string Choice[3] = { "Stone", "Paper", "Scissors" };
    return Choice[PlayChoice - 1];
}

string WinnerName(enWinnerGame Winner)
{
    string Choice[3] = { "Palyer", "Computer", "No Winner" };
    return Choice[Winner - 1];
}

enWinnerGame WinnerGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinnerGame::Palyer;
    else  if (ComputerWinTimes > Player1WinTimes)
        return enWinnerGame::Computer;
    else
        return enWinnerGame::Drow;
}

enWinnerGame WhoWonRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PalyerChoice == RoundInfo.ComputerChoice)
        return enWinnerGame::Drow;

    switch (RoundInfo.PalyerChoice)
    {
    case (enPlayChoice::Stone):
        if (RoundInfo.ComputerChoice == enPlayChoice::Paper)
        {
            return enWinnerGame::Computer;
        }
        break;
    case (enPlayChoice::Paper):
        if (RoundInfo.ComputerChoice == enPlayChoice::Scissors)
        {
            return enWinnerGame::Computer;
        }
        break;

    case (enPlayChoice::Scissors):
        if (RoundInfo.ComputerChoice == enPlayChoice::Stone)
        {
            return enWinnerGame::Computer;
        }
        break;
    }

    return enWinnerGame::Palyer;
}

stGameResults FillGameResult(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.Winner = WinnerGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.Winner);
    return GameResults;
}

void ShowFinalGameResult(stRoundInfo RoundInfo)
{
    cout << "\n____________________ Rounds [" << RoundInfo.RoundName << "] ___________________\n\n";
    cout << "Player1 Choice : " << PirntChoice(RoundInfo.PalyerChoice) << endl;
    cout << "Computer Choice: " << PirntChoice(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
    cout << "___________________________________________________\n\n";
}

void GenretColor(stRoundInfo RoundInfo)
{
    if (RoundInfo.Winner == enWinnerGame::Palyer)
    {
        system("color 2f");
    }
    else if (RoundInfo.Winner == enWinnerGame::Computer)
    {
        system("color 4f");
        cout << "\a";
    }
    else
    {
        system("color 6f");
    }
}

string Tabs(short NumberOfTab)
{
    string t = "\t";
    for (int i = 0; i < NumberOfTab; i++)
    {
        t = t + "\t";
    }
    return t;
}

stGameResults PalyGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
    {

        RoundInfo.RoundName = GameRounds;
        RoundInfo.PalyerChoice = ReadPalyerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        cout << "\nRounds [" << GameRounds << "] begins:\n";

        ShowFinalGameResult(RoundInfo);
        GenretColor(RoundInfo);
        if (RoundInfo.Winner == enWinnerGame::Palyer)
            Player1WinTimes++;
        else  if (RoundInfo.Winner == enWinnerGame::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;
    }
    return FillGameResult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void PirntGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_________________________________[Game Results ] _________________________________\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Playeri won times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Droa times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "__________________________________________________________________________________\n";
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "----------------------------------------------------------------------------------\n\n";
    cout << Tabs(2) << "                      +++ G a m e  O v e r +++\n\n";
    cout << Tabs(2) << "----------------------------------------------------------------------------------\n\n";
}

void ResretScreen()
{
    system("cls");
    system("color 0f");
}

void StartGame()
{
    char PlayAgen = 'Y';
    do
    {
        ResretScreen();

        stGameResults GameResults = PalyGame(HowManyRounds());

        ShowGameOverScreen();
        PirntGameResults(GameResults);
        cout << Tabs(3) << "Do you want to paly again? Y/N ? ";
        cin >> PlayAgen;

    } while (PlayAgen == 'Y' || PlayAgen == 'y');
}

int main()
{

    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}