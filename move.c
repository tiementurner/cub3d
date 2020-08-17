#include "header.h"

void    move_up(t_data *new_game)
{
    if (new_game->grid[(int)(new_game->player_X + 0.2 * new_game->raydir_X)][(int)new_game->player_Y] != '1')
        new_game->player_X += 0.1 * new_game->dir_X;
    if (new_game->grid[(int)new_game->player_X][(int)(new_game->player_Y + 0.2 * new_game->raydir_Y)] != '1')
        new_game->player_Y += 0.1 * new_game->dir_Y;
}

void    move_down(t_data *new_game)
{
    if (new_game->grid[(int)(new_game->player_X - 0.2)][(int)new_game->player_Y] != '1')
        new_game->player_X -= 0.1 * new_game->dir_X;
    if (new_game->grid[(int)new_game->player_X][(int)(new_game->player_Y - 0.2)] != '1')
        new_game->player_Y -= 0.1 * new_game->dir_Y;
}

void    move_right(t_data *new_game)
{
    if (new_game->grid[(int)(new_game->player_X + 0.2)][(int)new_game->player_Y] != '1')
        new_game->player_X += 0.1 * new_game->dir_Y;
    if (new_game->grid[(int)new_game->player_X][(int)(new_game->player_Y + 0.2)] != '1')
        new_game->player_Y += 0.1 * (-1 * new_game->dir_X);
}

void    move_left(t_data *new_game)
{
    if (new_game->grid[(int)(new_game->player_X - 0.2)][(int)new_game->player_Y] != '1')
        new_game->player_X += 0.1 * (-1 * new_game->dir_Y);
    if (new_game->grid[(int)new_game->player_X][(int)(new_game->player_Y - 0.2)] != '1')
        new_game->player_Y += 0.1 * new_game->dir_X;
}
