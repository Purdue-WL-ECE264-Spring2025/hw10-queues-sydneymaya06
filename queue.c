#include "queue.h"
#include "tile_game.h"

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
    //printf("serialized: %d\n", (int)serialize(start)); // 87097344
    struct queue q;
    int count = 0;
    int tier = 1;
    int queue_count = 0;
    q.data.head = NULL;
    int success = 0;
    enqueue(&q, start);
    printf("queue item: %ld\n", q.data.head->value);
    //enqueue(&q, start);
    //printf("queue item: %d\n", (int)q.data.head->next->value);
    //size_t val;
    struct game_state next_grid; // = dequeue(&q);
    
    

    while(success == 0)
    {
        // int length = 1;
        // struct list_node * p = q.data.head;
        // //printf("%d\n", (int)p->value);
        // while((p->next != NULL))
        // {
        //     p = p->next;
        //     length++;
        // }
        // //printf("length: %d\n", length);
        for(int ind = 0; ind < tier; ind++)
        {
            next_grid = dequeue(&q);
            if(serialize(next_grid) == 81985526993846272)
            {
                success = 1;
                printf("SUCCESS");
                break;
            }
            struct game_state grid_copy = next_grid;
        // printf("next grid: %d, %d\n", next_grid.empty_col, next_grid.empty_row);
        // printf("next grid: %d\n", next_grid.tiles[next_grid.empty_row + 1][next_grid.empty_col]);
        // printf("next grid: %d\n", next_grid.tiles[next_grid.empty_row][next_grid.empty_col]);

        // MOVE UP
        if(next_grid.empty_row < 3)
        {
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row + 1][next_grid.empty_col];
            next_grid.tiles[next_grid.empty_row + 1][next_grid.empty_col] = 0;
            enqueue(&q, next_grid);
            queue_count++;
            //printf("up ");
        }

        // MOVE DOWN
        if(next_grid.empty_row > 0)
        {
            next_grid = grid_copy;
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row - 1][next_grid.empty_col];
            next_grid.tiles[next_grid.empty_row - 1][next_grid.empty_col] = 0;
            enqueue(&q, next_grid);
            queue_count++;
            //printf("down ");
    
        }
        
        // MOVE LEFT
        if(next_grid.empty_col < 3)
        {
            next_grid = grid_copy;
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col + 1];
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col + 1] = 0;
            enqueue(&q, next_grid);
            queue_count++;
            //printf("left ");
        }

        // MOVE RIGHT
        if(next_grid.empty_col > 0)
        {
            next_grid = grid_copy;
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col] = next_grid.tiles[next_grid.empty_row][next_grid.empty_col - 1];
            next_grid.tiles[next_grid.empty_row][next_grid.empty_col - 1] = 0;
            enqueue(&q, next_grid);
            queue_count++;
            //printf("right ");
        }
        
        
        }
        if(success == 1)
        {
            printf("\nCOUNT: %d\n", count);
            break;
        }
        printf("tier %d\n", tier);
        tier = queue_count;
        printf("tier %d\n", tier);
        queue_count = 0;
        count++;
        printf("count %d\n", count);
        if(count > 9)
        {
            break;
        }
    }
        
    //     if(count == 2)
    //     {
    //         break;
    //     }
    // }
    free_list(q.data);
    return count; 
}
