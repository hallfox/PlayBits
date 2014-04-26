/*

   Demonstrate how to display an image with black, white and transparent sections.

   To achieve this effect you need to use a `RotBmpPairContainer` which contains
   two bitmaps: one is black and transparent, the other is white and transparent.

   The two bitmaps are created during the build process from a RGBA format PNG file.

   The image can also be rotated at runtime.

   The demonstration image is a modified version of the following SVG
   exported from Inkscape:

       <http://openclipart.org/detail/48919/panda-with-bamboo-leaves-by-adam_lowe>

 */

#include "pebble.h"

static Window *window;

static GBitmap *bittlet_white_img;
static GBitmap *bittlet_black_img;
static GBitmap *upp_arm_white_img;
static GBitmap *upp_arm_black_img;
static GBitmap *low_arm_white_img;
static GBitmap *low_arm_black_img;
static GBitmap *mouth_white_img;
static GBitmap *mouth_black_img;

/*// Allows us to make functionalize things without malloc DONT DELETE
static BitmapLayer **generic_layer_ppointer_w;
static BitmapLayer **generic_layer_ppointer_b;

static GBitmap **generic_img_ptr_w;
static GBitmap **generic_img_ptr_b;*/

static BitmapLayer *bittle_img_layr_white;
static BitmapLayer *bittle_img_layr_black;

static BitmapLayer *upp_arm_img_layr_white;
static BitmapLayer *upp_arm_img_layr_black;

static BitmapLayer *low_arm_img_layr_white;
static BitmapLayer *low_arm_img_layr_black;

static BitmapLayer *mouth_img_layr_white;
static BitmapLayer *mouth_img_layr_black;

/*static inline void add_layer_a(BitmapLayer ** generic_white_layer, BitmapLayer ** generic_black_layer, Layer * window_lyr, GRect * img_frm_ptr,
	GBitmap ** img_pptr_w, GBitmap ** img_pptr_b);
*/
static void window_load(Window *window);

static void window_unload(Window *window);

static void init(void);

static void deinit(void);

static void window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

// We do this to account for the offset due to the status bar
// at the top of the app window.

	upp_arm_white_img = gbitmap_create_with_resource(RESOURCE_ID_UPP_ARM_WHITE);
	upp_arm_black_img = gbitmap_create_with_resource(RESOURCE_ID_UPP_ARM_BLACK);

	low_arm_white_img = gbitmap_create_with_resource(RESOURCE_ID_LOW_ARM_WHITE);
	low_arm_black_img = gbitmap_create_with_resource(RESOURCE_ID_LOW_ARM_BLACK);

	mouth_white_img = gbitmap_create_with_resource(RESOURCE_ID_MOUTH_WHITE);
	mouth_black_img = gbitmap_create_with_resource(RESOURCE_ID_MOUTH_BLACK);

	bittlet_white_img = gbitmap_create_with_resource(RESOURCE_ID_SPRITE6_WHITE);
	bittlet_black_img = gbitmap_create_with_resource(RESOURCE_ID_SPRITE6_BLACK);

	const GPoint center = grect_center_point(&bounds);
	GRect image_frame = (GRect) { .origin = center, .size = bittlet_white_img->bounds.size };
	//GRect * rect_img_frm_ptr = &image_frame;
	image_frame.origin.x -= bittlet_white_img->bounds.size.w/2;
	image_frame.origin.y -= bittlet_white_img->bounds.size.h/2;

	/**generic_layer_ppointer_w = bittle_img_layr_white;
	*generic_layer_ppointer_b = bittle_img_layr_black;

	*generic_img_ptr_w = bittlet_white_img;
	*generic_img_ptr_b = bittlet_black_img;*/

	//Start with the white frame
	bittle_img_layr_white = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(bittle_img_layr_white, bittlet_white_img);
	bitmap_layer_set_compositing_mode(bittle_img_layr_white, GCompOpOr);
	layer_add_child(window_layer, bitmap_layer_get_layer(bittle_img_layr_white));

	// Use GCompOpClear to display the black portions of the image
	bittle_img_layr_black = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(bittle_img_layr_black, bittlet_black_img);
	bitmap_layer_set_compositing_mode(bittle_img_layr_black, GCompOpClear);
	layer_add_child(window_layer, bitmap_layer_get_layer(bittle_img_layr_black));

	//add features
	upp_arm_img_layr_white = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(upp_arm_img_layr_white, upp_arm_white_img);
	bitmap_layer_set_compositing_mode(upp_arm_img_layr_white, GCompOpOr);
	layer_add_child(window_layer, bitmap_layer_get_layer(upp_arm_img_layr_white));

	//add black components of features
	upp_arm_img_layr_black = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(upp_arm_img_layr_black, upp_arm_black_img);
	bitmap_layer_set_compositing_mode(upp_arm_img_layr_black, GCompOpClear);
	layer_add_child(window_layer, bitmap_layer_get_layer(upp_arm_img_layr_black));

	//add features
	low_arm_img_layr_white = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(low_arm_img_layr_white, low_arm_white_img);
	bitmap_layer_set_compositing_mode(low_arm_img_layr_white, GCompOpOr);
	layer_add_child(window_layer, bitmap_layer_get_layer(low_arm_img_layr_white));

	//add black components of features
	low_arm_img_layr_black = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(low_arm_img_layr_black, low_arm_black_img);
	bitmap_layer_set_compositing_mode(low_arm_img_layr_black, GCompOpClear);
	layer_add_child(window_layer, bitmap_layer_get_layer(low_arm_img_layr_black));

/*Mouth is disabled for now, becuase it looks stupid*/
/*	//add features
	mouth_img_layr_white = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(mouth_img_layr_white, mouth_white_img);
	bitmap_layer_set_compositing_mode(mouth_img_layr_white, GCompOpOr);
	layer_add_child(window_layer, bitmap_layer_get_layer(mouth_img_layr_white));

	//add black components of features
	mouth_img_layr_black = bitmap_layer_create(image_frame);
	bitmap_layer_set_bitmap(mouth_img_layr_black, mouth_black_img);
	bitmap_layer_set_compositing_mode(mouth_img_layr_black, GCompOpClear);
	layer_add_child(window_layer, bitmap_layer_get_layer(mouth_img_layr_black));*/

	//add_layer_a(generic_layer_ppointer_w, generic_layer_ppointer_b, window_layer, rect_img_frm_ptr, generic_img_ptr_w, generic_img_ptr_b);
}

/*static inline void add_layer_a(BitmapLayer ** generic_white_layer, BitmapLayer ** generic_black_layer, Layer * window_lyr, GRect * img_frm_ptr,
	GBitmap ** img_pptr_w, GBitmap ** img_pptr_b)
{
	//Start with the white frame
	*generic_white_layer = bitmap_layer_create(*img_frm_ptr);
	bitmap_layer_set_bitmap(*generic_white_layer, *img_pptr_w);
	bitmap_layer_set_compositing_mode(*generic_white_layer, GCompOpOr);
	layer_add_child(window_lyr, bitmap_layer_get_layer(*generic_white_layer));

	// Use GCompOpClear to display the black portions of the image
	*generic_black_layer = bitmap_layer_create(*img_frm_ptr);
	bitmap_layer_set_bitmap(*generic_black_layer, *img_pptr_b);
	bitmap_layer_set_compositing_mode(*generic_black_layer, GCompOpClear);
	layer_add_child(window_lyr, bitmap_layer_get_layer(*generic_black_layer));
}*/

static void window_unload(Window *window) {
	bitmap_layer_destroy(bittle_img_layr_white);
	bitmap_layer_destroy(bittle_img_layr_black);

	gbitmap_destroy(bittlet_white_img);
	gbitmap_destroy(bittlet_black_img);

}

static void init(void) {
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload
	});
window_stack_push(window, true /* Animated */);
}

static void deinit(void) {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}