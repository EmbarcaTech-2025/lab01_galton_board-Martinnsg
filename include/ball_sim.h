#ifndef BALL_SIM_H
#define BALL_SIM_H

#define MAX_BALLS 20
#define MAX_STEPS 10
#define MAX_BINS 32

#include <stdbool.h>

typedef struct {
    int x, y;
    int progress;
    bool enabled;
} Particle;

void particle_system_init();
void particle_emit();
void particle_update_all();
void particle_render();
int *histogram_access();
int total_particles_counted();

#endif
