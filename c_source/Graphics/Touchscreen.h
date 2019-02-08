#ifndef TOUCHSCREEN_H_   /* Include guard */
#define TOUCHSCREEN_H_

/* a data type to hold a point/coord */
typedef struct { int x, y; } UnscaledPoint ;

typedef struct { int x, y; } Point ;

void Init_Touch(void);
Point GetPress(void);
Point GetRelease(void);
Point ScalePoint(UnscaledPoint unsca_p);

#endif // TOUCHSCREEN_H_
