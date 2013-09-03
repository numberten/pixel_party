#ifndef COLORS_H
#define COLORS_H

#define U_SHORT unsigned short

//Variable used for calculating the hue of pixels.
extern float hue;
void initialize_hue();

//Prototypes for generating pixel colours.
void hsv_to_rgb(U_SHORT*, U_SHORT*, U_SHORT*, float, float, float);
void generate_rgb(U_SHORT*, U_SHORT*, U_SHORT*);

#endif /* COLORS_H */
