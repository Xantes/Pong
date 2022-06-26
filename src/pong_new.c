#include <stdio.h>
#include <stdlib.h>

int find_middle(int number);

int main() {
  char ch;

  struct Ball {
    int pos_x;
    int pos_y;
    int direction;
  };

  struct Player {
    int pos_y0;
    int pos_y1;
    int pos_y2;
    int pos_x;
  };

  struct ScoreTable {
    int score_l;
    int score_r;
  };

  struct Field {
    int height;
    int width;
    int middle_height;
    int middle_width;
  };

  void set_direction(struct Ball * p_ball, int direction) {
    p_ball->direction = direction;
  }

  void move_ball(struct Ball * p_ball) {
    switch (p_ball->direction) {
      case 1:
        p_ball->pos_x -= 1;
        p_ball->pos_y += 1;
        break;
      case 2:
        p_ball->pos_x -= 1;
        break;
      case 3:
        p_ball->pos_x -= 1;
        p_ball->pos_y -= 1;
        break;
      case 4:
        p_ball->pos_x += 1;
        p_ball->pos_y += 1;
        break;
      case 5:
        p_ball->pos_x += 1;
        break;
      case 6:
        p_ball->pos_x += 1;
        p_ball->pos_y -= 1;
        break;
    }
  }

  void move_player(struct Player * player, struct Field * p_field, int move) {
    if ((player->pos_y0 < p_field->height - 1) && (player->pos_y2 > 1)) {
      player->pos_y0 += move;
      player->pos_y1 += move;
      player->pos_y2 += move;
    }
  }

  void bounce_wall(struct Ball * p_ball) {
    switch (p_ball->direction) {
      case 1:
        p_ball->direction = 3;
        break;
      case 3:
        p_ball->direction = 1;
        break;
      case 4:
        p_ball->direction = 6;
        break;
      case 6:
        p_ball->direction = 4;
        break;
    }
  }

  void bounce_player(struct Ball * p_ball) {
    switch (p_ball->direction) {
      case 1:
        p_ball->direction = 4;
        break;
      case 3:
        p_ball->direction = 6;
        break;
      case 4:
        p_ball->direction = 1;
        break;
      case 6:
        p_ball->direction = 3;
        break;
      case 2:
        p_ball->direction += p_ball->pos_y % 2 ? 2 : 4;
        break;
      case 5:
        p_ball->direction -= p_ball->pos_y % 2 ? 2 : 4;
        break;
    }
  }

  void set_random_direction(struct Ball * p_ball) {
    if (p_ball->direction) {
      p_ball->direction = 7 - p_ball->direction;
    } else {
      p_ball->direction = 3;
    }
  }

  void increase_score(struct ScoreTable * score_table, int player) {
    if (!player) {
      score_table->score_l += 1;
    } else {
      score_table->score_r += 1;
    }
  }

  void start_round(struct Ball * p_ball, struct Player * p_player_l,
                   struct Player * p_player_r, struct Field * p_field) {
    p_ball->pos_x = p_field->middle_width;
    p_ball->pos_y = p_field->middle_height;
    set_random_direction(p_ball);
    p_player_l->pos_y0 = find_middle(p_field->height) + 1;
    p_player_l->pos_y1 = find_middle(p_field->height);
    p_player_l->pos_y2 = find_middle(p_field->height) - 1;
    p_player_r->pos_y0 = find_middle(p_field->height) + 1;
    p_player_r->pos_y1 = find_middle(p_field->height);
    p_player_r->pos_y2 = find_middle(p_field->height) - 1;
  }

  void print_diagnostic(struct Ball * p_ball, struct Player * p_player_l,
                        struct Player * p_player_r) {
    printf("\n");
    printf("B_pos_x %d\n", p_ball->pos_x);
    printf("B_pos_y %d\n", p_ball->pos_y);
    printf("\n");
    printf("L_player_pos_x %d\n", p_player_l->pos_x);
    printf("R_player_pos_x %d\n", p_player_r->pos_x);
    printf("\n");
    printf("L_player_pos_y0 %d\n", p_player_l->pos_y0);
    printf("L_player_pos_y1 %d\n", p_player_l->pos_y1);
    printf("L_player_pos_y2 %d\n", p_player_l->pos_y2);
    printf("\n");
    printf("R_player_pos_y0 %d\n", p_player_r->pos_y0);
    printf("R_player_pos_y1 %d\n", p_player_r->pos_y1);
    printf("R_player_pos_y2 %d\n", p_player_r->pos_y2);
  }
  int draw_field(struct Field * p_field, struct Ball * p_ball,
                 struct Player * p_player_l, struct Player * p_player_r,
                 struct ScoreTable * p_score_table) {
    int height_max = p_field->height;
    system("clear");
    for (int temp_height = p_field->height; temp_height >= 0; temp_height--) {
      printf("\n");
      for (int cursor = 0; cursor <= p_field->width; cursor += 1) {
        if ((cursor == 0) || (cursor == p_field->width) ||
            (cursor == p_field->middle_width)) {
          printf("|");
        }
        if ((cursor == p_ball->pos_x) && (temp_height == p_ball->pos_y)) {
          printf("*");

        } else if (temp_height == 0) {
          if ((cursor >= 0) && (cursor < p_field->width - 2)) {
            if (cursor == p_field->middle_width - 2) {
              printf("%02d", p_score_table->score_l);
            } else if (cursor == p_field->middle_width + 1) {
              printf("%02d", p_score_table->score_r);
            } else {
              printf("_");
            }
          }

        } else if (temp_height == height_max) {
          if ((cursor >= 0) && (cursor < p_field->width)) {
            printf("¯");
          }
        } else if ((cursor == p_player_l->pos_x) &&
                   ((temp_height == p_player_l->pos_y0) ||
                    (temp_height == p_player_l->pos_y1) ||
                    (temp_height == p_player_l->pos_y2))) {
          printf("l");
        } else if ((cursor == p_player_r->pos_x) &&
                   ((temp_height == p_player_r->pos_y0) ||
                    (temp_height == p_player_r->pos_y1) ||
                    (temp_height == p_player_r->pos_y2))) {
          printf("r");
        } else {
          printf(" ");
        }
      }
    }
    return 0;
  }

  int collision(struct Ball * p_ball, struct Player * p_player) {
    for (int i = p_player->pos_y0; i <= p_player->pos_y2; i++) {
      if (i == p_ball->pos_y) {
        return 1;
        break;
      }
    }
    return 0;
  }
  void check_condition(struct Ball * p_ball, struct Player * p_player_l,
                       struct Player * p_player_r, struct Field * p_field,
                       struct ScoreTable * p_score_table) {
    if ((p_ball->pos_x == p_player_r->pos_x - 1) &&
        (collision(p_ball, p_player_r))) {
      bounce_player(p_ball);
    }
    if ((p_ball->pos_x == p_player_l->pos_x + 1) &&
        (collision(p_ball, p_player_l))) {
      bounce_player(p_ball);
    }
    if ((p_ball->pos_y == 1) || (p_ball->pos_y == p_field->height - 1)) {
      bounce_wall(p_ball);
    }

    if (p_ball->pos_x == 0) {
      increase_score(p_score_table, 1);
      start_round(p_ball, p_player_l, p_player_r, p_field);
    }
    if (p_ball->pos_x == p_field->width) {
      increase_score(p_score_table, 0);
      start_round(p_ball, p_player_l, p_player_r, p_field);
    }
  }

  struct Ball ball = {40, 15, 3};
  struct Player player_l = {13, 14, 15, 1};
  struct Player player_r = {13, 14, 15, 79};
  struct ScoreTable score_table = {0, 0};
  struct Field field = {25, 80, 0, 0};

  field.middle_height = find_middle(field.height);
  field.middle_width = find_middle(field.width);

  do {
    draw_field(&field, &ball, &player_l, &player_r, &score_table);
    ch = getchar();
    if (ch == 97) {
      move_player(&player_l, &field, 1);
    } else if (ch == 122) {
      move_player(&player_l, &field, -1);
    }
    if (ch == 107) {
      move_player(&player_r, &field, 1);
    } else if (ch == 109) {
      move_player(&player_r, &field, -1);
    }
    move_ball(&ball);
    check_condition(&ball, &player_l, &player_r, &field, &score_table);
  } while (ch != 53);
  return 0;
}

int find_middle(int number) {
  int middle;
  middle = number % 2;
  if (number) {
    return number / 2;
  } else {
    return middle > 5 ? number / 2 + 1 : number / 2 - 1;
  }
  return 0;
}
