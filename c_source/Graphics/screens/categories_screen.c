#include "../components/textbox.h"
#include "../Colours.h"
#include "../Text.h"
#include "../Touchscreen.h"

#include "screen.h"

static const int max_buttons_per_col = 5;
static const int max_col = 2;
static const int max_buttons = 10; // buttons_per_col * num_of_col

static const int col_gap = 20;
static const int row_gap = 10;
static const int base_x = 25;
static const int base_y = 60;
static const int button_length = 250;
static const int button_width = 75;

// every shape that should be plotted should go here
static struct {
    TextBox * back_button;
    TextBox * category_buttons[10];
    int num_categories;
    // TODO: add all the component of homescreen here
} _CategoriesScreen;

int categories_screen_init() {
    int num_items = 15;
    char * item_categories[] = {
        "Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical",
        "Floors & Area Rugs", "Furniture", "Hardware", "Paint", "Tools",
        "Kitchen", "Lighting & Fans", "Outdoors", "Storage & Organization", "Windows & Doors"
    };

    int cate_added = 0;
    for (int col = 0; col < max_col; col++) {
        for (int row = 0; row < max_buttons_per_col; row++) {
            TextBox * b = textbox_create(
                base_x + col * (button_length + col_gap),
                base_y + row * (button_width + row_gap),
                button_length,
                button_width);

            textbox_set_box_colour(b, BLUE, FOREST_GREEN);
            textbox_set_text(b, item_categories[cate_added], FONT2, WHITE);

            _CategoriesScreen.category_buttons[cate_added] = b;
            cate_added++;
        }
    }
    _CategoriesScreen.num_categories = cate_added;

    TextBox * bb = textbox_create(base_x, 5, 100, 50);
	textbox_set_box_colour(bb, DARK_GRAY, DIM_GRAY);
	textbox_set_text(bb, "BACK", FONT2, BLACK);
	textbox_draw(bb);
    _CategoriesScreen.back_button = bb;
}

void categories_screen_draw(void) {
    for (int i = 0; i < _CategoriesScreen.num_categories; i++) {
        textbox_draw(_CategoriesScreen.category_buttons[i]);
    }

    textbox_draw(_CategoriesScreen.back_button);
}

screen_t categories_screen_listen(void) {
	Point pp, pr;
    while (1) {
        pp = GetPress();
        pr = GetRelease(); //wait for a getrelease
        if (textbox_within(_CategoriesScreen.back_button, pr)) {
            return HOME;
        }
	}
}
