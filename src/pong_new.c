#include <stdio.h>

int find_middle(int number);
int draw_field();

int main() {
  int height;
  int width;
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

  void move_player(struct Player * player, int move) {
    player->pos_y0 += move;
    player->pos_y1 += move;
    player->pos_y2 += move;
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
                   struct Player * p_player_r, int height, int width) {
    p_ball->pos_x = find_middle(width);
    p_ball->pos_y = find_middle(height);
    p_player_l->pos_y0 = find_middle(height) + 1;
    p_player_l->pos_y1 = find_middle(height);
    p_player_l->pos_y2 = find_middle(height) - 1;
    p_player_r->pos_y0 = find_middle(height) + 1;
    p_player_r->pos_y1 = find_middle(height);
    p_player_r->pos_y2 = find_middle(height) - 1;
  }
  height = 25;
  width = 80;
  struct Ball ball = {0, 0, 3};
  struct Player player_l = {13, 14, 15, 1};
  struct Player player_r = {13, 14, 15, 79};
  struct ScoreTable score_table = {0, 0};

  while ((ch = getchar()) != 53) {
    draw_field(height, width, &ball, &player_l, &player_r, &score_table);
  }
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

int draw_field(int width, int height, struct Ball *p_ball,
               struct Player *p_player_l, struct Player *p_player_r,
               struct ScoreTable *p_score_table) {
  int height_max = height;

  for (height; height >= 0; height--) {
    printf("\n");

    for (int cursor = 0; cursor <= width; cursor += 1) {
      if ((cursor == 0) || (cursor == width) ||
          (cursor == find_middle_line(width))) {
        printf("|");
      }

      if ((cursor == p_ball->pos_x) && (height == p_ball->pos_y)) {
        printf("*");

      } else if (height == 0) {
        if ((cursor >= 0) || (cursor <= width)) {
          printf("_");
        }

      } else if (height == height_max) {
        if ((cursor >= 0) || (cursor <= width)) {
          printf("¯");
        }

      } else {
        printf(" ");
      }
    }
  }
  return 0;
}
