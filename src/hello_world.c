#include <pebble.h>

Window *window;
TextLayer *text_layer;

// Setup for s1.png
GBitmap *sprite;
BitmapLayer *layer;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	//text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Load Bitmap
  sprite = gbitmap_create_with_resource(RESOURCE_ID_TESTS1_BLACK);
   
  //Create BitmapLayer to show GBitmap and add to Window
  layer = bitmap_layer_create(GRect(0, 0, 60, 60));
  bitmap_layer_set_bitmap(layer, sprite);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(layer));
	
	// Set the text, font, and text alignment
	/*text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);*/
	
	// Add the text layer to the window
	//layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	//text_layer_destroy(text_layer);
	
  //Destroy GBitmaps
  gbitmap_destroy(sprite); 
  //Destroy BitmapLayers
  bitmap_layer_destroy(layer);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
