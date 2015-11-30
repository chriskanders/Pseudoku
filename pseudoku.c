#include "pseudoku.h"

int32 main()
{
    uint32 test_grid[81];
    init_grid(test_grid);
    printf("Before fill_grid:\n");
    print_grid(test_grid);
    printf("After fill_grid:\n");
    fill_grid(test_grid, 0);
    print_grid(test_grid);
}

uint32*
get_row(uint32* g, uint32 r)
{// returns row r (0-8) of grid g
    uint32* row = (uint32*)malloc(sizeof(uint32) * 9);
    uint32 i;
    for (i = 0; i < 9; i++)
	row[i] = g[(r * 9) + i];
    return row;
}

uint32*
get_col(uint32* g, uint32 c)
{// returns row c (0-8) of grid g
    uint32* col = (uint32*)malloc(sizeof(uint32) * 9);
    uint32 i;
    for (i = 0; i < 9; i++)
	col[i] = g[(i * 9) + c];
    return col;
}

uint32*
get_box(uint32* g, uint32 b)
{// returns row b (0-8) of grid g
    uint32* box = (uint32*)malloc(sizeof(uint32) * 9);
    uint32 start_row = (b / 3) * 3;
    uint32 start_col = (b % 3) * 3;
    uint32 i;
    for (i = 0; i < 9; i++)
	box[i] =
	    g[((start_row + (i / 3)) * 9) + (start_col + i % 3)];
    return box;
}

uint32*
get_row_ptr(uint32* g, uint32 r)
{
    return &g[r * 9];
}

uint32*
get_col_ptr(uint32* g, uint32 c)
{
    return &g[c];
}

uint32*
get_box_ptr(uint32* g, uint32 b)
{
    return &g[(b / 3 * 3 * 9) + (b % 3 * 3)];
}

peers*
get_peers(uint32* g, uint32 n)
{// returns peers of cell n (0-80) in grid g
    peers* neighbors = (peers*)malloc(sizeof(peers));
    uint32* row = get_row(g, n / 9);
    uint32* col = get_col(g, n % 9);
    uint32* box = get_box(g, (n / 27 * 3 + (n % 9) / 3));
    uint32 i;
    for (i = 0; i < 9; i++)
    {
	neighbors->row[i] = row[i];
	neighbors->col[i] = col[i];
	neighbors->box[i] = box[i];
    }
    free(row); free(col); free(box);
    return neighbors;
}

uint32
is_safe(uint32* g, uint32 n, uint32 v)
{// returns whether or not value v (1-9) in cell n (0-8) in grid g is safe
    peers* neighbors = get_peers(g, n);
    uint32 i;
    for (i = 0; i < 9; i++)
    {
	if (neighbors->row[i] == v ||
	    neighbors->col[i] == v ||
	    neighbors->box[i] == v)
	{
	    free(neighbors);
	    return (0);
	}
    }
    free(neighbors);
    return (1);
}

pos*
get_pos_vals(uint32* g, uint32 n)
{// returns pos struct containing possible values in cell n (0-80) in grid g
    pos* pos_values = (pos*)malloc(sizeof(pos));
    uint32 i, s;
    for (i = 0, s = 0; i < 9; i++)
    {
	if (is_safe(g, n, i + 1))
	{
	    pos_values->vals[s] = i + 1;
	    s++;
	}  
	
    }
    pos_values->size = s;
    return pos_values;
}

uint32
fill_grid(uint32* g, uint32 n)
{// fills cells n (0-80) to end of grid g
    if (n < 81)
    {
	if (g[n] != 0)
	{
	    return fill_grid(g, n + 1);
	}
	else
	{
	    pos *pos_values = get_pos_vals(g, n);
	    uint32 i;
	    for (i = 0; i < pos_values->size; i++)
	    {
		g[n] = pos_values->vals[i];
		if (fill_grid(g, n + 1))
		{
		    free(pos_values);
		    return (1);
		}
		else
		{
		    g[n] = 0;
		}
	    }
	    free(pos_values);
	    return (0);
	}
    }
    else
    {
	return (1);
    }
}

void
copy_grid(uint32* old_values, uint32* new_values)
{// copies new_values to old_values in grid g
    uint32 i;
    for (i = 0; i < 81; i++)
    {
	old_values[i] = new_values[i];
    }
}

void
init_grid(uint32* g)
{// initializes grid g to samp_grid
    uint32 samp_grid[81] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0,
			    0, 0, 0, 0, 0, 0, 0, 0, 0};
    copy_grid(g, samp_grid);
}

void
print_grid(uint32* g)
{// prints grid g in Sudoku format
    uint32 i;
    for (i = 0; i < 81; i++)
    {
	if (i % 9 == 0 && i != 0)
	    printf("\n");
	if (i % 27 == 0 && i != 0)
	    printf("------+-------+-------\n");
	if (i % 3 == 0 && i % 9 != 0)
	    printf("| %d ", g[i]);
	else
	    printf("%d ", g[i]);
    }
    printf("\n");
}
