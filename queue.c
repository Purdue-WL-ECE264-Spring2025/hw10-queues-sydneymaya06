#include "queue.h"
#include "tile_game.h"

int check_list(struct queue *q, size_t serialized_board);

void enqueue(struct queue *q, struct game_state state)
{
    insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q)
{
    struct game_state board;
    board = deserialize(remove_from_head(&q->data));
    return board;
}

int number_of_moves(struct game_state start)
{
    struct queue q;
    q.data.head = NULL;
    
    int count = 0;
    //int tier = 1;
    //int queue_count = 0;
    
    int success = 0;
    
    enqueue(&q, start);
    
    struct game_state next_grid; 
    
    while (success == 0)
    {
        next_grid = dequeue(&q);

        next_grid.num_steps += 1;

        int index = 1;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(next_grid.tiles[i][j] == index)
                {
                    index++;
                    if(index == 16 && next_grid.tiles[3][3] == 0)
                    {
                        printf("success!");
                        success = 1;
                    }
                }
            }
        }
        // MOVE UP
        if (next_grid.empty_row < 3)
        {
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row + 1][next_grid.empty_col];
            next_grid.tiles[next_grid.empty_row + 1][next_grid.empty_col] = 0;
            if(check_list(&q, serialize(next_grid)) == 0)
            {
                enqueue(&q, next_grid);
            }
            next_grid.tiles[next_grid.empty_row + 1][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col]; // reset board
        }

        // MOVE DOWN
        if (next_grid.empty_row > 0)
        {
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row - 1][next_grid.empty_col];
            next_grid.tiles[next_grid.empty_row - 1][next_grid.empty_col] = 0;
            enqueue(&q, next_grid);
            if(check_list(&q, serialize(next_grid)) == 0)
            {
                enqueue(&q, next_grid);
            }
            next_grid.tiles[next_grid.empty_row - 1][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col];
        }

        // MOVE LEFT
        if (next_grid.empty_col < 3)
        {
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col + 1];
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col + 1] = 0;
            enqueue(&q, next_grid);
            if(check_list(&q, serialize(next_grid)) == 0)
            {
                enqueue(&q, next_grid);
            }
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col + 1] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col];
        }

        // MOVE RIGHT
        if (next_grid.empty_col > 0)
        {
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col - 1];
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col - 1] = 0;
            enqueue(&q, next_grid);
            if(check_list(&q, serialize(next_grid)) == 0)
            {
                enqueue(&q, next_grid);
            }
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col - 1] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col];
        }
        
        count++;
        if (count % 10000 == 0)
        {
            printf("count: %d\n", count);
        }
    }
    

    free_list(q.data);
    return next_grid.num_steps - 1;
}

int check_list(struct queue *q, size_t serialized_board)
{
    int duplicate = 0;
    struct list_node *p = q->data.head;
    while(p != NULL)
    {
        if((p->value) == serialized_board)
        {
            duplicate = 1;
            break;
        }
        p = p->next;
    }
    return duplicate;
}
