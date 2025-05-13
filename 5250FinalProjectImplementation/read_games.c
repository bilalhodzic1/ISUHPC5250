#include "csvutils.h"

/**
 * Parses a line of game data from a CSV file into a game_t struct.
 *
 * @param string_array An array of strings representing the fields of the game
 * data.
 * @return A game_t struct containing the parsed game data.
 */
game_t parse_game_line(char **string_array) {
  game_t game;
  game.player_id = atoi(string_array[0]);
  game.game_id = atoi(string_array[2]);
  game.season = atoi(string_array[3]);
  strncpy(game.team_abbreviation, string_array[4],
          sizeof(game.team_abbreviation) - 1);
  game.team_abbreviation[sizeof(game.team_abbreviation) - 1] = '\0';
  game.pts = atoi(string_array[5]);
  game.reb = atoi(string_array[6]);
  game.ast = atoi(string_array[7]);
  game.stl = atoi(string_array[8]);
  game.blk = atoi(string_array[9]);
  game.turnover = atoi(string_array[10]);
  game.fgm = atoi(string_array[11]);
  game.fga = atoi(string_array[12]);
  game.ftm = atoi(string_array[13]);
  game.fta = atoi(string_array[14]);
  game.min = atof(string_array[15]);
  game.pf = atoi(string_array[16]);
  game.oreb = atoi(string_array[17]);
  game.dreb = atoi(string_array[18]);
  return game;
}

/**
 * Reads game data from a CSV file into an array of game_t structs.
 *
 * @param file A pointer to the file to read from.
 * @param num_games A pointer to an integer that will be set to the number of
 * games read.
 * @return An array of game_t structs containing the parsed game data.
 */
game_t *read_games(FILE *file, int *num_games) {
  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  rewind(file);

  size_t record_size = sizeof(game_t);
  *num_games = filesize / record_size;

  game_t *records = malloc(*num_games * record_size);

  fread(records, record_size, *num_games, file);
  return records;
}

/**
 * Get the number of games in a file
 *
 * @param record_size size of each record in bytes
 * @param num_games A pointer to an integer that will be set to the number of
 * games read.
 */
void get_num_games(size_t record_size, int *num_games) {
  FILE *file = fopen("1.bin", "rb");
  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  fclose(file);
  *num_games = filesize / record_size;
}
