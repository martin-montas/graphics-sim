#pragma once

#define WIDTH  800
#define HEIGHT 600

#define _NUM_TYPE 5

extern float force_matrix[_NUM_TYPE][_NUM_TYPE]; /* matrix holding force amount between particles */
extern float min_distance_matrix[_NUM_TYPE]
                                [_NUM_TYPE];     /* matrix holding min distance between particles */
extern float radii_matrix[_NUM_TYPE][_NUM_TYPE]; /* matrix holding max distance between particles */
