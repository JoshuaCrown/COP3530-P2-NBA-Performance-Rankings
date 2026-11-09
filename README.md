<H1> COP3530 - Project 2 </h1>

Description of data:

For this project, we used a dataset which contained
around 100,000 individual NBA player-game
performances from Hugging Face’s NBA Games
dataset, which includes information about
individual NBA games. Each row represents a player
and it contains information about the player like
the name and ID, the game like game ID and
performance statistics like points scored and
rebounds.

We specifically selected player_name, player_id,
game_id, team_abbreviation, pts, reb, and ast
which contain the player name, identification
number, game identification number, team
abbreviation, points scored, rebounds, and
assists. These selected columns have the
information needed to rank players by points,
rebounds and assists while including necessary
information to identify each player.

<h2> Instructions </h2>

1. Select one metric to sort by, descendingly.
2. Select either heap sort or merge sort for the
sorting algorithm
3. If you want the players with only 30+ points,
select the filter button at the top.
4. Click "Sort" when both a metric and algorithm
have been selected.
5. A new window will appear with a table showing
the players sorted in descending order.

The `font.ttf` and `games_details.csv` files will
be copied from the `resources` folder located in
the repository into `cmake-build-debug/resources`
folder; the program uses relative addressing from
its running location. Please check lines 85-87 in
main.cpp to see its implementation.

If you're customizing the data, ensure that it
follows the same column format in the current
`games_details.csv` file.

<h2> Resources </h2>

- [Database](https://huggingface.co/datasets/davdsdfd/nba-games/viewer/games_details)