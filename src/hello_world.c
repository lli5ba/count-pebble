#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_output_layer;
static int count = 0;
static char buf[] = "123456";


static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  count = count + 1;
  snprintf(buf, sizeof(buf), "\n%d", count);
  text_layer_set_text(s_output_layer, buf);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    count = 0;
    snprintf(buf, sizeof(buf), "\n%d", count);
    text_layer_set_text(s_output_layer, buf);
}


void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  /*text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  snprintf(buf, sizeof(buf), "\nSaving %d", count);
  text_layer_set_text(s_output_layer, buf);
  */
}

void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  /*text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  count = 0;
  snprintf(buf, sizeof(buf), "\n%d", count);
  text_layer_set_text(s_output_layer, buf);
  */
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (count >= 1) {
    count = count - 1;
    snprintf(buf, sizeof(buf), "\n%d", count);
    text_layer_set_text(s_output_layer, buf);
  }
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 500, select_long_click_handler, select_long_click_release_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
   snprintf(buf, sizeof(buf), "\n%d", count);
  // Create output TextLayer
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text(s_output_layer, buf);
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
}

static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_output_layer);
}

static void init() {
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_click_config_provider(s_main_window, click_config_provider);
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}