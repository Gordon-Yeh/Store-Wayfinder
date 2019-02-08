#ifndef SCREENS_H_   /* Include guard */
#define SCREENS_H_

void ResetScreen(void);
void HomeScreen(void);
void CategoryScreen(void);
void ItemScreen(char category[]);

//Widgets
void BackButton(void);
void SidebarList(char *list[], int list_size);

#endif
