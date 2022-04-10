/*
    Patrik Richard Szilagyi R00198735
    MTU SOFT7019 - C Programming Module
    Assignment 1 - "The Mountain"
    Gradient-based hill climbing algorithm
*/
#include "gradient.h"

int peak_found, tries;
int up_direction, right_direction, down_direction, left_direction;
float view[VIEW_SIZE][VIEW_SIZE];
float elev, prev_elev, highest_elev, up_elev, left_elev, down_elev, right_elev;
path_point landscape_pos, prev_pos, local_pos, up_pos, left_pos, down_pos, right_pos;

/* Set a point in the landscape (x: {0 - INFINITY}, y: {0 - INFINITY}) */
path_point set_landscape_point(int y, int x)
{
    path_point landscape_point;
    landscape_point.x = x;
    landscape_point.y = y;
    return landscape_point;
}
/* END function */

/* Set a point in the view (x: {0 - VIEW_SIZE}, y: {0 - VIEW_SIZE}) */
path_point set_local_point(int y, int x)
{
    path_point view_point;
    view_point.x = x;
    view_point.y = y;
    return view_point;
}
/* END function */

/* Create a random point in the landscape */
path_point set_random_point()
{
    path_point point;
    int rand_x = random() % 100;
    int rand_y = random() % 100;
    point.x = rand_x;
    point.y = rand_y;
    return point;
}
/* END function */

/* Set the elevation values of the adjacent positions */
void set_adjacent_elevations()
{
    /* Up, right, left, down positions */
    up_pos = set_local_point(local_pos.y - 1, local_pos.x);
    right_pos = set_local_point(local_pos.y, local_pos.x + 1);
    left_pos = set_local_point(local_pos.y, local_pos.x - 1);
    down_pos = set_local_point(local_pos.y + 1, local_pos.x);

    /* Up, right, left, down elevation values */
    if (up_pos.y != -1)
        up_elev = view[up_pos.y][up_pos.x];
    else
        up_elev = 0;
    if (right_pos.x != VIEW_SIZE)
        right_elev = view[right_pos.y][right_pos.x];
    else
        right_elev = 0;
    if (down_pos.y != VIEW_SIZE)
        down_elev = view[down_pos.y][down_pos.x];
    else
        down_elev = 0;
    if (left_pos.x != -1)
        left_elev = view[left_pos.y][left_pos.x];
    else
        left_elev = 0;
}
/* END function */

/* Find the highest adjacent elevation */
void find_highest_elevation()
{
    /* Set the upward position's elevation as highest */
    if (highest_elev < up_elev)
        highest_elev = up_elev;
    /* END if */
    /* Set the rightward position's elevation as highest */
    if (highest_elev < right_elev)
        highest_elev = right_elev;
    /* END if */
    /* Set the downward position's elevation as highest */
    if (highest_elev < down_elev)
        highest_elev = down_elev;
    /* END if */
    /* Set the leftward position's elevation as highest */
    if (highest_elev < left_elev)
        highest_elev = left_elev;
    /* END if */
    /* Set current position's elevation as highest */
    if (highest_elev == elev)
        highest_elev = elev;
    /* END if */
    /* Print the highest elevation value */
    printf("Highest elevation: %f\n", highest_elev);
}

/* Move to the position with the highest elevation in the view */
void move()
{
    /* Move up */
    if (highest_elev == up_elev && up_pos.y != -1)
        local_pos.y--;
    /* END if */
    /* Move right */
    else if (highest_elev == right_elev && right_pos.x != VIEW_SIZE)
        local_pos.x++;
    /* END else-if */
    /* Move down */
    else if (highest_elev == down_elev && down_pos.y != VIEW_SIZE)
        local_pos.y++;
    /* END else-if */
    /* Move left */
    else if (highest_elev == left_elev && left_pos.x != -1)
        local_pos.x--;
    /* END else-if */
    /* Print out the current position in the view matrix */
    printf("Moved to %d-%d\n", local_pos.y, local_pos.x);
}
/* END function */

/* Display the view */
void display_view(float view[VIEW_SIZE][VIEW_SIZE])
{
    printf("\nLandscape position: %d-%d, tries: %d\n", landscape_pos.y, landscape_pos.x, ++tries);
    for (int y_pos = 0; y_pos < VIEW_SIZE; y_pos++)
    {
        for (int x_pos = 0; x_pos < VIEW_SIZE; x_pos++)
        {
            if (y_pos == VIEW_RADIUS && x_pos == VIEW_RADIUS)
            {
                printf("(%f) ", view[y_pos][x_pos]);
            }
            else
            {
                printf(" %f  ", view[y_pos][x_pos]);
            }
        }
        printf("\n");
    }
}
/* END function */

/* Print the the current and adjacent position's values */
void print_elevations()
{
    /* Print the elevation value at the starting position */
    printf("\nCurrent elevation: %f, Previous elevation: %f\n", elev, prev_elev);
    /* Print the elevation value at the adjacent positions */
    printf(
        "U: %f (%d-%d)\tR: %f (%d-%d)\tD: %f (%d-%d)\tL: %f (%d-%d)\n",
        up_elev, up_pos.y, up_pos.x,
        right_elev, right_pos.y, right_pos.x,
        down_elev, down_pos.y, down_pos.x,
        left_elev, left_pos.y, left_pos.x);
}
/* END function */

/* Search for the highest point in a matrix */
path_point find_highest_point()
{
    landscape_pos = set_landscape_point(69, 69);
    prev_pos = landscape_pos;
    peak_found = 0;
    tries = 0;
    int plateau_count = 0;

    /* Loop until the peak is found */
    while (!peak_found)
    {
        /* Generate the view and load it into the view matrix */
        generate_view(view, landscape_pos.y, landscape_pos.x);
        /* Starting position in the view matrix */
        local_pos = set_local_point(VIEW_RADIUS, VIEW_RADIUS);
        /* The elevation value at the starting position */
        elev = view[local_pos.y][local_pos.x];
        /* Assign the highest elevation */
        highest_elev = 0;

        /* Print view to the console */
        display_view(view);

        /* Loop until the boundary of the view has been reached */
        while (local_pos.y != 0 || local_pos.x != VIEW_SIZE - 1 || local_pos.y != VIEW_SIZE - 1 || local_pos.x != 0)
        {
            set_adjacent_elevations();
            print_elevations();

            /* In case of a peak */
            if (elev > up_elev && elev > right_elev && elev > down_elev && elev > left_elev)
            {
                // printf("Peak\n");
                prev_pos = set_landscape_point(landscape_pos.y, landscape_pos.x);
                landscape_pos.y += local_pos.y - VIEW_RADIUS;
                landscape_pos.x += local_pos.x - VIEW_RADIUS;
                printf("Current: %d-%d, Prev: %d-%d\n", landscape_pos.y, landscape_pos.x, prev_pos.y, prev_pos.x);

                /* Check if true peak has been reached */
                if (
                    (up_elev == right_elev && up_elev == down_elev) ||
                    (right_elev == down_elev && right_elev == left_elev) ||
                    (down_elev == left_elev && left_elev == up_elev) ||
                    (left_elev == up_elev && left_elev == right_elev) ||
                    (up_elev == right_elev && down_elev == left_elev) ||
                    (right_elev == down_elev && left_elev == up_elev))
                {
                    peak_found = declare_peak(landscape_pos.x, landscape_pos.y);
                    printf("Peak? %d\n", peak_found);
                    if (peak_found)
                        return landscape_pos;
                    path_point random_pos = set_random_point();
                    /* New random position */
                    landscape_pos = set_landscape_point(random_pos.y, random_pos.x);
                    break;
                }
                /* END if */

                /* Peak is near edge */
                if (
                    elev > 0 &&
                    (up_elev == right_elev || right_elev == down_elev || down_elev == left_elev || left_elev == up_elev) && (up_elev == -1 || right_elev == -1 || down_elev == -1 || left_elev == -1))
                {
                    peak_found = declare_peak(landscape_pos.x, landscape_pos.y);
                    printf("Peak? %d\n", peak_found);
                    if (peak_found)
                        return landscape_pos;
                    path_point random_pos = set_random_point();
                    /* New random position */
                    landscape_pos = set_landscape_point(random_pos.y, random_pos.x);
                    break;
                }

                /* Peak is on view boundary */
                if (up_elev == 0 || right_elev == 0 || down_elev == 0 || left_elev == 0)
                {
                    /* Skip up */
                    if (landscape_pos.y < prev_pos.y)
                    {
                        prev_pos.y = landscape_pos.y;
                        landscape_pos.y -= VIEW_RADIUS;
                    }
                    /* END if */
                    /* Skip right */
                    if (landscape_pos.x > prev_pos.x)
                    {
                        prev_pos.x = landscape_pos.x;
                        landscape_pos.x += VIEW_RADIUS;
                    }
                    /* END if */
                    /* Skip down */
                    if (landscape_pos.y > prev_pos.y)
                    {
                        prev_pos.y = landscape_pos.y;
                        landscape_pos.y += VIEW_RADIUS;
                    }
                    /* END if */
                    /* Skip left */
                    if (landscape_pos.x < prev_pos.x)
                    {
                        prev_pos.x = landscape_pos.x;
                        landscape_pos.x -= VIEW_RADIUS;
                    }
                    /* END if */
                    printf("Current: %d-%d, Prev: %d-%d\n", landscape_pos.y, landscape_pos.x, prev_pos.y, prev_pos.x);
                    break;
                }
                /* END if */

                peak_found = declare_peak(landscape_pos.x, landscape_pos.y);
                printf("Peak? %d\n", peak_found);
                if (peak_found)
                    return landscape_pos;
                /* In case previous tests fail check if it's the peak to be sure */
                path_point random_pos = set_random_point();
                /* New random position */
                landscape_pos = set_landscape_point(random_pos.y, random_pos.x);
                break;
            }
            /* END if */

            /* In case of a plateau */
            if (elev == up_elev || elev == right_elev || elev == down_elev || elev == left_elev)
            {
                /* An edge (value of -1) */
                if (elev == -1)
                {
                    // printf("Edge!!\n");
                    find_highest_elevation();
                    int distance = 1;
                    float up_elev_edge, right_elev_edge, down_elev_edge, left_elev_edge;
                    while (distance <= VIEW_RADIUS)
                    {
                        up_elev_edge = view[local_pos.y - distance][local_pos.x];
                        right_elev_edge = view[local_pos.y][local_pos.x + distance];
                        down_elev_edge = view[local_pos.y + distance][local_pos.x];
                        left_elev_edge = view[local_pos.y][local_pos.x - distance];
                        if (up_elev_edge != -1)
                        {
                            local_pos.y -= distance;
                            break;
                        }
                        /* END if */
                        if (right_elev_edge != -1)
                        {
                            local_pos.x += distance;
                            break;
                        }
                        /* END if */
                        if (down_elev_edge != -1)
                        {
                            local_pos.y += distance;
                            break;
                        }
                        /* END if */
                        if (left_elev_edge != -1)
                        {
                            local_pos.x -= distance;
                            break;
                        }
                        /* END if */
                        distance++;
                    }
                    /* END while */
                    printf("Escaped to: %d-%d\n", local_pos.y, local_pos.x);
                    set_adjacent_elevations();
                    move();
                    if (local_pos.x - VIEW_RADIUS == 0 && local_pos.y - VIEW_RADIUS == 0)
                    {
                        path_point random_pos = set_random_point();
                        /* New random position */
                        landscape_pos = set_landscape_point(random_pos.y, random_pos.x);
                        break;
                    }
                    print_elevations();
                }
                /* END if */

                plateau_count++;
                /* A positive plateau */
                if (elev > 0)
                {
                    printf("Plateau!!\n");
                    find_highest_elevation();
                    if (plateau_count > 10)
                    {
                        plateau_count = 0;
                        path_point random_pos = set_random_point();
                        /* New random position */
                        landscape_pos = set_landscape_point(random_pos.y, random_pos.x);
                        break;
                    }
                    landscape_pos.y += local_pos.y - VIEW_RADIUS;
                    landscape_pos.x += local_pos.x - VIEW_RADIUS;
                    /* Keep Skip over the plateau */
                    /* Skip up */
                    if (landscape_pos.y < prev_pos.y || local_pos.y < VIEW_RADIUS)
                    {
                        prev_pos.y = landscape_pos.y;
                        landscape_pos.y -= VIEW_RADIUS;
                        printf("Skip up\n");
                    }
                    /* END if */
                    /* Skip right */
                    if (landscape_pos.x > prev_pos.x || local_pos.x > VIEW_RADIUS)
                    {
                        prev_pos.x = landscape_pos.x;
                        landscape_pos.x += VIEW_RADIUS;
                        printf("Skip right\n");
                    }
                    /* END if */
                    /* Skip down */
                    if (landscape_pos.y > prev_pos.y || local_pos.y > VIEW_RADIUS)
                    {
                        prev_pos.y = landscape_pos.y;
                        landscape_pos.y += VIEW_RADIUS;
                        printf("Skip down\n");
                    }
                    /* END if */
                    /* Skip left */
                    if (landscape_pos.x < prev_pos.x || local_pos.x < VIEW_RADIUS)
                    {
                        prev_pos.x = landscape_pos.x;
                        landscape_pos.x -= VIEW_RADIUS;
                        printf("Skip left\n");
                    }
                    /* END if */

                    prev_elev = elev;
                    break;
                }
                /* END if */
            }
            /* END if */

            /* Find which position's elevation is highest */
            find_highest_elevation();

            /* Move in the view matrix when highest elevation is in an adjacent position */
            if (highest_elev > elev)
                move();

            /* Save the evelation value */
            prev_elev = elev;
            /* Set the evelation value to the highest adjacent's value */
            elev = view[local_pos.y][local_pos.x];
        }
        /* END while */
    }
    /* END while */
}
/* END function */
