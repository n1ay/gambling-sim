#include <stdio.h>
#include <sodium.h>

static double WIN_OUTCOME_MULTIPLIER = 1.9;
static double STARTING_MONEY = 500;

static double LOSE_BET_MULTIPLIER = 2;
static double STARTING_BET = 10;
static double MAX_BET = 100000;
static int ROUNDS_LIMIT = 1000;

int roll_dice() {
    //return (rand() % 6) + 1;
    return randombytes_uniform(6) + 1;
}

int is_dice_high(int dice_outcome) {
    if (dice_outcome > 3) {
        return 1;
    } else {
        return 0;
    }
}

int is_game_won(int dice_outcome) {
    return (is_dice_high(dice_outcome));
}

int max_streak(int results[], int length, int value) {
    int longest_streak = 0;
    for (int i = 0; i < length; ++i) {
        if (results[i] != value) {
            continue;
        }
        int j = i;
        while((j < length) && (results[j] == results[i])) {
            if ((j - i + 1) > longest_streak) {
                longest_streak = (j - i + 1);
            }
            ++j;
        }
    }

    return longest_streak;
}

int main(int argc, char** argv) {

    int round = 0;
    double money = STARTING_MONEY;
    int last_game_lost = 0;
    
    int dice_result;
    int game_won;
    double bet;

    int wins = 0;
    int losts = 0;
    double max_money = STARTING_MONEY;
    int results[ROUNDS_LIMIT];
    int max_win_streak;
    int max_lose_streak;

    while (round < ROUNDS_LIMIT && money > 0) {
        if (last_game_lost) {
            if (money >= (bet * LOSE_BET_MULTIPLIER)) {
                bet *= LOSE_BET_MULTIPLIER;
                if (bet > MAX_BET) {
                    bet = MAX_BET;
                }
            } else {
                bet = money;
                if (bet > MAX_BET) {
                    bet = MAX_BET;
                }
            }
        } else {
            bet = STARTING_BET;
        }

        money -= bet;

        dice_result = roll_dice();
        game_won = is_game_won(dice_result);
        results[round] = game_won;
        if (game_won) {
            last_game_lost = 0;
            money += WIN_OUTCOME_MULTIPLIER * bet;
            if (money > max_money) {
                max_money = money;
            }
            ++wins;
        } else {
            last_game_lost = 1;
            ++losts;
        }

        ++round;
        printf("[ROUND %d]: bet: %lf, game result: %d (dice_outcome: %d), balance: %lf, round balance: %lf\n", round, bet, game_won, dice_result, money, (-bet + (game_won ? WIN_OUTCOME_MULTIPLIER * bet : 0.0)));
    }
    
    max_win_streak = max_streak(results, round, 1);
    max_lose_streak = max_streak(results, round, 0);
    printf("[END] wins: %d, losts: %d, max balance: %lf, max win streak: %d, max lost streak: %d\n", wins, losts, max_money, max_win_streak, max_lose_streak);

    return 0;
}
